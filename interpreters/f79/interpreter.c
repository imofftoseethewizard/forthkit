#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>

#include "evaluator.h"

#define INTERPRETER_NAME    "forth-79"
#define VERSION_DESCRIPTION "<version TODO>"

#define DEFAULT_COMMAND NULL

#define DEFAULT_BUFFER_COUNT         32
#define DEFAULT_BUFFER_SIZE          1024
#define DEFAULT_EVALUATOR_SIZE       1<<20
#define DEFAULT_FIBER_COUNT          4
#define DEFAULT_FIBER_STACK_SIZE     4
#define DEFAULT_MAX_WORD_LENGTH      64
#define DEFAULT_PARAMETER_STACK_SIZE 256
#define DEFAULT_RETURN_STACK_SIZE    256
#define DEFAULT_SOURCE_SIZE          1024
#define DEFAULT_TASK_COUNT           4

static cell *evaluator = NULL;

/* string options */
static char *command            = DEFAULT_COMMAND;

/* integer options */
static int buffer_count         = DEFAULT_BUFFER_COUNT;
static int buffer_size          = DEFAULT_BUFFER_SIZE;
static int evaluator_size       = DEFAULT_EVALUATOR_SIZE;
static int fiber_count          = DEFAULT_FIBER_COUNT;
static int fiber_stack_size     = DEFAULT_FIBER_STACK_SIZE;
static int max_word_length      = DEFAULT_MAX_WORD_LENGTH;
static int parameter_stack_size = DEFAULT_PARAMETER_STACK_SIZE;
static int return_stack_size    = DEFAULT_RETURN_STACK_SIZE;
static int source_size          = DEFAULT_SOURCE_SIZE;
static int task_count           = DEFAULT_TASK_COUNT;

/* flags */
static int interactive  = 0;
static int quiet        = 0;
static int show_help    = 0;
static int show_version = 0;

static struct option long_options[] = {
    {"buffer-count",         required_argument, NULL,          'b'},
    {"buffer-size",          required_argument, NULL,          'B'},
    {"command",              required_argument, NULL,          'c'},
    {"evaluator-size",       required_argument, NULL,          'E'},
    {"fiber-count",          required_argument, NULL,          'f'},
    {"fiber-stack-size",     required_argument, NULL,          'F'},
    {"max-word-length",      required_argument, NULL,          'w'},
    {"parameter-stack-size", required_argument, NULL,          'P'},
    {"return-stack-size",    required_argument, NULL,          'R'},
    {"source-size",          required_argument, NULL,          'S'},
    {"task-count",           required_argument, NULL,          't'},
    {"help",                 no_argument,       &show_help,    1},
    {"interactive",          no_argument,       &interative,   1},
    {"quiet",                no_argument,       &quiet,        1},
    {"version",              no_argument,       &show_version, 1},
    {0, 0, 0, 0}
};

int evaluate_file(char *path);
int is_valid_non_negative_integer(char *s);
void print_version(void);
void process_options(int argc, char *argv[]);
void repl(void);

void
print_help(char *message)
{
    print_version();

    printf("usage: %s [options] [file ...]\n", INTERPRETER_NAME);
    printf("\n");

    if (message) {
        printf("\n");
        printf("%s %s\n", optstring, message);
    }

    printf("\n");
}

int
main(int argc, char *argv[])
{
    int idx;
    number result = 0;
    /* int storage_fd = -1; */

    process_options(argc, argv);

    evaluator = (cell *)malloc(evaluator_size);

    /* Clears structure, sets up basic limits. */
    init_evaluator(
        evaluator,
        buffer_count,
        buffer_size,
        evaluator_size,
        fiber_count,
        fiber_stack_size,
        max_word_length,
        parameter_stack_size,
        return_stack_size,
        source_size,
        task_count);

    if (!quiet)
        printf("Forthkit %s\n", INTERPRETER_NAME);

    if (show_help)
        print_help(NULL);

    else if (show_version)
        /* print_help also calls print_version, so only call it here if show_help is false */
        print_version();

    /* TODO
    if (argc > 1)
        storage_fd = open(argv[argc-1], O_RDWR);
    */

    for (idx = optind; !result && idx < argc; idx++)
        result = evaluate_file(argv[idx]);

    if (result)
        exit(result);

    if (!command && !show_help && !show_version && optind == argc || interactive)
        repl();
}

void
repl(void)
{
    char *line;
    int result;

    while (1) {

        line = readline(NULL);

        if (!line) break;

        result = evaluate(evaluator, line, storage_fd);

        switch (result) {
        case result_ok:
            printf("%s\n", result_messages[result]);
            break;

        case err_abort_message:
        default:
            print_error(
                evaluator,
                (result <= next_error_code) ? "unknown_error" : result_messages[-result],
                evaluator[ea_source_idx]);
            break;
        }

        free(line);
    }
}

int
evaluate_file(char *path)
{
    int result = 0;
    char *line = malloc(source_size);

    FILE *file = fopen(path, "r");

    if (!file) {
        fprintf(stderr, "failed to open file \"%s\" with errno %d\n", path, errno);
        exit(2);
    }

    while (!result && fgets(line, source_size, file))
        result = evaluate(evaluator, line, 0);

    if (fclose(file)) {
        fprintf(stderr, "failed to close file \"%s\" with errno %d\n", path, errno);
        exit(3);
    }

    free(line);

    return result;
}

/* defined in evaluator.h */
_define_result_messages();

void
print_error(cell *e, const char *message, cell n) {
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
    printf("%s %s\n", INTERPRETER_NAME, VERSION_DESCRIPTION);
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

void
process_options(int argc, char *argv[])
{
    int c;

    while (1) {

        c = getopt_long(argc, argv, "b:B:c:E:F:f:hiP:qR:S:t:vw:", long_options, NULL);

        if (c == -1) break;

        switch (c) {
        case 0:
            /* indicates a flag option. getopt_long has already set the flag value; nothing
               needs to be done.
            */
            break;

        case 'b':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("must have a non-negative integer argument.");
                exit(1);
            }

            buffer_count = atoi(optarg);
            break;

        case 'B':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("must have a non-negative integer argument.");
                exit(1);
            }

            buffer_size = atoi(optarg);
            break;

        case 'c':
            command = optarg;
            break;

        case 'E':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("must have a non-negative integer argument.");
                exit(1);
            }

            evaluator_size = atoi(optarg);
            break;

        case 'F':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("must have a non-negative integer argument.");
                exit(1);
            }

            fiber_stack_size = atoi(optarg);
            break;

        case 'f':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("must have a non-negative integer argument.");
                exit(1);
            }

            fiber_count = atoi(optarg);
            break;

        case 'h':
            show_help = 1;
            break;

        case 'i':
            interactive = 1;
            break;

        case 'P':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("must have a non-negative integer argument.");
                exit(1);
            }

            parameter_stack_size = atoi(optarg);
            break;

        case 'q':
            quiet = 1;
            break;

        case 'R':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("must have a non-negative integer argument.");
                exit(1);
            }

            return_stack_size = atoi(optarg);
            break;

        case 'S':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("must have a non-negative integer argument.");
                exit(1);
            }

            source_size = atoi(optarg);
            break;

        case 't':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("must have a non-negative integer argument.");
                exit(1);
            }

            task_count = atoi(optarg);
            break;

        case 'v':
            show_version = 1;
            break;

        case ':':
            /* missing value */
            print_help("requires an argument.");
            exit(1);

        case '?':
            /* unknown option */
            print_help("is not a recognized option.");
            exit(1);
        }
    }
}
