#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>

#include "evaluator.h"

#define INTERPRETER_NAME    "forth-79"
#define VERSION_DESCRIPTION "<version TODO>"

#define DEFAULT_COMMAND      NULL
#define DEFAULT_STORAGE_PATH NULL

#define DEFAULT_BUFFER_COUNT         32
#define DEFAULT_BUFFER_SIZE          1024
#define DEFAULT_EVALUATOR_SIZE       1<<20
#define DEFAULT_EXPECTED_RESULT      0
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
static char *storage_path       = DEFAULT_STORAGE_PATH;

/* integer options */
static int buffer_count         = DEFAULT_BUFFER_COUNT;
static int buffer_size          = DEFAULT_BUFFER_SIZE;
static int evaluator_size       = DEFAULT_EVALUATOR_SIZE;
static int expected_result      = DEFAULT_EXPECTED_RESULT;
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

/* file descriptor of unstructured binary storage */
static int storage_fd = -1;

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
    {"expected-result",      required_argument, NULL,          'r'},
    {"source-size",          required_argument, NULL,          'S'},
    {"storage",              required_argument, NULL,          's'},
    {"task-count",           required_argument, NULL,          't'},
    {"help",                 no_argument,       &show_help,    1},
    {"interactive",          no_argument,       &interactive,  1},
    {"quiet",                no_argument,       &quiet,        1},
    {"version",              no_argument,       &show_version, 1},
    {0, 0, 0, 0}
};

/* defined in evaluator.h */
_define_result_messages();

/* used for composing error in response to getopt_long errors; see process_options() */
static char message_buffer[100];

int evaluate_file(char *path);
int is_valid_non_negative_integer(char *s);
int is_valid_integer(char *s);
void print_error(cell *e, const char *message, cell n);
void print_version(void);
void process_options(int argc, char *argv[]);
void repl(void);

void
print_help(char *message)
{
    print_version();

    printf("usage: %s [options] [file ...]\n", INTERPRETER_NAME);

    printf("  -B, --buffer-size           size of block buffers in bytes, default %d\n", DEFAULT_BUFFER_SIZE);
    printf("  -b, --buffer-count          number of block buffers, default %d\n", DEFAULT_BUFFER_COUNT);
    printf("  -c, --command               command to execute, suppresses repl\n");
    printf("  -E, --evaluator-size        size of memory area for evaluator in bytes, default %d\n", DEFAULT_EVALUATOR_SIZE);
    printf("  -F, --fiber-stack-size      maximum depth of fiber stack, default %d\n", DEFAULT_FIBER_STACK_SIZE);
    printf("  -f, --fiber-count           number of fibers to reserve space for, default %d\n", DEFAULT_FIBER_COUNT);
    printf("  -h, --help                  show this message\n");
    printf("  -i, --interactive           start repl regardless of other options\n");
    printf("  -P, --parameter-stack-size  maximum depth of parameter stack, default %d\n", DEFAULT_PARAMETER_STACK_SIZE);
    printf("  -q, --quiet                 suppress greeting\n");
    printf("  -R, --return-stack-size     maximum depth of return stack, default %d\n", DEFAULT_RETURN_STACK_SIZE);
    printf("  -r, --expected-result       expected result from evaluation, default %d\n", DEFAULT_EXPECTED_RESULT);
    printf("  -S, --source-size           size of parsing buffer in bytes, default %d\n", DEFAULT_SOURCE_SIZE);
    printf("  -s, --storage               path to block storage\n");
    printf("  -t, --task-count            number of tasks to reserve space for, default %d\n", DEFAULT_TASK_COUNT);
    printf("  -v, --version               print version\n");
    printf("  -w, --max-word-length       maximum length of parsed word, default %d\n", DEFAULT_MAX_WORD_LENGTH);
    printf("\n");

    if (message) {
        printf("\n");
        printf("%s\n", message);
    }

    printf("\n");
}

int
main(int argc, char *argv[])
{
    int idx;
    number result = 0;

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

    if (!quiet && !show_help && !show_version)
        printf("Forthkit %s\n", INTERPRETER_NAME);

    if (show_help)
        print_help(NULL);

    else if (show_version)
        /* print_help also calls print_version, so only call it here if show_help is false */
        print_version();

    if (storage_path)
        storage_fd = open(storage_path, O_RDWR);

    for (idx = optind; !result && idx < argc; idx++)
        result = evaluate_file(argv[idx]);

    if (result)
        exit(result == expected_result ? 0 : 3);

    if (command)
        result = evaluate(evaluator, command, storage_fd);

    if (result)
        exit(result == expected_result ? 0 : 3);

    if (!command && !show_help && !show_version && optind == argc || interactive)
        repl();

    exit(0);
}

void
repl(void)
{
    char *line;
    number result;

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
        result = evaluate(evaluator, line, storage_fd);

    if (fclose(file)) {
        fprintf(stderr, "failed to close file \"%s\" with errno %d\n", path, errno);
        exit(3);
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

void
process_options(int argc, char *argv[])
{
    int c;

    while (1) {

        c = getopt_long(argc, argv, ":b:B:c:E:F:f:hiP:qR:r:S:s:t:vw:", long_options, NULL);

        if (c == -1) break;

        switch (c) {
        case 0:
            /* indicates a flag option. getopt_long has already set the flag value; nothing
               needs to be done.
            */
            break;

        case 'b':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("-b, --buffer-count must have a non-negative integer argument.");
                exit(1);
            }

            buffer_count = atoi(optarg);
            break;

        case 'B':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("-B, --buffer-size must have a non-negative integer argument.");
                exit(1);
            }

            buffer_size = atoi(optarg);
            break;

        case 'c':
            command = optarg;
            break;

        case 'E':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("-E, --evaluator-size must have a non-negative integer argument.");
                exit(1);
            }

            evaluator_size = atoi(optarg);
            break;

        case 'F':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("-F, --fiber-stack-size must have a non-negative integer argument.");
                exit(1);
            }

            fiber_stack_size = atoi(optarg);
            break;

        case 'f':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("-f, --fiber-count must have a non-negative integer argument.");
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
                print_help("-P, --parameter-stack-size must have a non-negative integer argument.");
                exit(1);
            }

            parameter_stack_size = atoi(optarg);
            break;

        case 'q':
            quiet = 1;
            break;

        case 'R':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("-R, --return-stack-size must have a non-negative integer argument.");
                exit(1);
            }

            return_stack_size = atoi(optarg);
            break;

        case 'r':

            if (!is_valid_integer(optarg)) {
                print_help("-r, --expected-result must have an integer argument.");
                exit(1);
            }

            expected_result = atoi(optarg);
            break;

        case 'S':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("-S, --source-size must have a non-negative integer argument.");
                exit(1);
            }

            source_size = atoi(optarg);
            break;

        case 's':
            storage_path = optarg;
            break;

        case 't':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("-t, --task-count must have a non-negative integer argument.");
                exit(1);
            }

            task_count = atoi(optarg);
            break;

        case 'v':
            show_version = 1;
            break;

        case ':':
            sprintf(message_buffer, "-%c requires an argument.", optopt);
            print_help(message_buffer);
            exit(1);

        case '?':
            sprintf(message_buffer, "-%c is not a recognized option.", optopt);
            print_help(message_buffer);
            exit(1);
        }
    }
}
