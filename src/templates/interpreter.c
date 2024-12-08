#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>

#include "evaluator.h"

#define INTERPRETER_NAME    EVALUATOR_FAMILY_NAME
#define VERSION_DESCRIPTION "<version TODO>"

#ifdef BUNDLED

#if BUNDLED
extern const char _binary_evaluator_fi_end;
extern const char _binary_evaluator_fi_start;
#endif

#else
#define BUNDLED 0
#endif

#define DEFAULT_COMMAND           NULL
#define DEFAULT_CREATE_IMAGE_PATH NULL
#define DEFAULT_LOAD_IMAGE_PATH   NULL
#define DEFAULT_STORAGE_PATH      NULL

/*{ interpreter_cli_options }*/

static cell *evaluator = NULL;

/* file descriptor of unstructured binary storage */
static int storage_fd = -1;

/* used for composing error in response to getopt_long errors; see process_options() */
static char message_buffer[100];

cell *load_bundled_evaluator(void);
cell *read_image_file(const char *path);
void create_image(cell *e0, int argc, char *argv[]);
int evaluate_file(cell *e, char *path);
int is_valid_non_negative_integer(char *s);
int is_valid_integer(char *s);
cell *prepare_evaluator(int argc, char *argv[]);
void print_error(cell *e, const char *message, cell n);
void print_version(void);
void process_options(int argc, char *argv[]);
void repl(void);

/*{ interpreter_option_help }*/

int
main(int argc, char *argv[])
{
    number result = 0;

    process_options(argc, argv);

    if (show_help)
        print_help(NULL);

    else if (show_version)
        /* print_help also calls print_version, so only call it here
         * where show_help is false.
         */
        print_version();

    if (storage_path)
        storage_fd = open(storage_path, O_RDWR);

    if (!quiet && !show_help && !show_version)
        printf("Forthkit %s\n", INTERPRETER_NAME);

    evaluator = prepare_evaluator(argc, argv);

    if (create_image_path)
        create_image(evaluator, argc, argv);

    if (result)
        exit(result == expected_result ? 0 : 3);

    if (!command && !create_image_path && !show_help && !show_version && optind == argc || interactive)
        repl();

    exit(0);
}

cell *
prepare_evaluator(int argc, char *argv[])
{
    cell *e = NULL;
    int idx;
    number result = 0;

    if (BUNDLED)
        e = load_bundled_evaluator();

    else if (load_image_path)
        e = read_image_file(load_image_path);

    else {
        e = (cell *)malloc(evaluator_size);

        /* Clears structure, sets up basic limits. */
        /*{ interpreter_init_evaluator }*/
    }

    for (idx = optind; !result && idx < argc; idx++)
        result = evaluate_file(e, argv[idx]);

    if (result)
        exit(result == expected_result ? 0 : 3);

    if (command)
        evaluate_source(e, command, storage_fd);

    if (result)
        exit(result == expected_result ? 0 : 3);

    return e;
}

void
create_image(cell *e0, int argc, char *argv[])
{
    /* Create an indentical evaluator to compare it to. This makes it
     * easy to detect address-dependent code and create the relocation
     * table.
     */
    cell *e1 = prepare_evaluator(argc, argv);

    if (!e1) {
        fprintf(stderr, "failed to prepare comparison evaluator for create_image.\n");
        exit(2);
    }

    int image_size;
    cell *image = create_evaluator_image(e0, e1, &image_size);

    free(e1);

    if (!image) {
        fprintf(stderr, "failed to create evaluator image.\n");
        exit(2);
    }

    FILE *file;
    size_t bytes_written;

    file = fopen(create_image_path, "w");

    if (!file) {
        fprintf(stderr, "failed to open image \"%s\" for writing with errno %d\n", create_image_path, errno);
        exit(2);
    }

    bytes_written = fwrite(image, 1, image_size, file);

    if (bytes_written != image_size) {
        fprintf(stderr, "failed to write all %d bytes to \"%s\" (only %lu) with errno %d\n", image_size, create_image_path, (long unsigned int)bytes_written, errno);
        exit(2);
    }

    if (fclose(file)) {
        fprintf(stderr, "failed to close file \"%s\" with errno %d\n", create_image_path, errno);
        exit(2);
    }

    free(image);
}

cell *
load_bundled_evaluator(void)
{
    #if BUNDLED
    const char *image = &_binary_evaluator_fi_start;
    size_t image_size = &_binary_evaluator_fi_end - &_binary_evaluator_fi_start;
    return load_evaluator_image(image, image_size);
    #else
    return NULL;
    #endif
}

cell *
read_image_file(const char *path)
{
    FILE *file = fopen(path, "r");
    long image_size = -1;
    size_t bytes_read = -1;
    char *image = NULL;
    cell *evaluator = NULL;

    if (!file) {
        fprintf(stderr, "failed to open image \"%s\" for reading with errno %d\n", path, errno);
        exit(2);
    }

    fseek(file, 0, SEEK_END);

    image_size = ftell(file);

    fseek(file, 0, SEEK_SET);

    image = malloc(image_size);

    if (!image) {
        fprintf(stderr, "unable to allocate memory\n");
        exit(2);
    }

    bytes_read = fread(image, 1, image_size, file);

    if (bytes_read < image_size) {
        fprintf(stderr, "failed to read image contents from file \"%s\" with errno %d\n", path, errno);
        exit(2);
    }

    if (fclose(file)) {
        fprintf(stderr, "failed to close file \"%s\" with errno %d\n", path, errno);
        exit(2);
    }

    evaluator = load_evaluator_image(image, image_size);

    free(image);

    return evaluator;
}

void
repl(void)
{
    char *line;
    number result;

    while (1) {

        line = readline(NULL);

        if (!line) break;

        result = evaluate_source(evaluator, line, storage_fd);

        switch (result) {
        case result_ok:
            printf("ok\n");
            break;

        case err_abort_message:
            print_error(
                evaluator,
                (const char *)evaluator + evaluator[ea_error_msg_addr],
                evaluator[ea_source_idx]);
            break;

        default:

            print_error(evaluator, error_message(result), evaluator[ea_source_idx]);
            break;
        }

        free(line);
    }
}

int
evaluate_file(cell *e, char *path)
{
    int line_no;
    int result = 0;
    char *line = malloc(source_size);

    FILE *file = fopen(path, "r");

    if (!file) {
        fprintf(stderr, "failed to open file \"%s\" with errno %d\n", path, errno);
        exit(2);
    }

    for (line_no = 0; !result && fgets(line, source_size, file); line_no++)
        result = evaluate_source(e, line, storage_fd);

    if (result) {
        printf("\nWhile reading %s at line %d: \n", path, line_no);
        print_error(e, error_message(result), e[ea_source_idx]);
    }

    if (fclose(file)) {
        fprintf(stderr, "failed to close file \"%s\" with errno %d\n", path, errno);
        exit(2);
    }

    free(line);

    return result;
}

void
print_error(cell *e, const char *message, cell n)
{
    const char *text = (const char *)_to_ptr(e[ea_source_addr]);
    int i, col = 1;

    printf("\n%s:\n", message);

    for (i = 0; i < n; i++) {
        putc(text[i], stdout);
        col = text[i] == '\n' ? 1 : col+1;
    }
    putc('\n', stdout);

    for (int i = 1; i < col; i++)
        putc(' ', stdout);

    putc('^', stdout);
    putc('\n', stdout);
}

void
print_version(void)
{
    printf("Forthkit %s %s\n", INTERPRETER_NAME, VERSION_DESCRIPTION);
}

int
is_valid_non_negative_integer(char *s)
{
    while (*s == '0' && *(s+1) != 0)
        s++;

    if (strlen(s) > 9)
        return 0;

    while (*s && *s >= '0' && *s <= '9')
        s++;

    return *s == 0;
}

int
is_valid_integer(char *s)
{
    if (*s == '-')
        s++;

    return is_valid_non_negative_integer(s);
}

/*{ process_interpreter_cli_options }*/
