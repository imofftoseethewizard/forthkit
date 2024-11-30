#define DEFAULT_BUFFER_COUNT         32
#define DEFAULT_BUFFER_SIZE          1024
#define DEFAULT_EVALUATOR_SIZE       (sizeof(cell) == 2 ? (1<<16) - 2 : 1<<20)
#define DEFAULT_EXPECTED_RESULT      0
#define DEFAULT_FIBER_COUNT          4
#define DEFAULT_FIBER_STACK_SIZE     4
#define DEFAULT_WORD_BUFFER_SIZE     128
#define DEFAULT_PAD_BUFFER_SIZE      84 /* See PAD in doc/forth-83.txt */
#define DEFAULT_PARAMETER_STACK_SIZE 64
#define DEFAULT_RETURN_STACK_SIZE    64
#define DEFAULT_SOURCE_SIZE          1024
#define DEFAULT_TASK_COUNT           4

/* string options */
static char *command            = DEFAULT_COMMAND;
static char *create_image_path  = DEFAULT_CREATE_IMAGE_PATH;
static char *load_image_path    = DEFAULT_LOAD_IMAGE_PATH;
static char *storage_path       = DEFAULT_STORAGE_PATH;

/* integer options */
static int buffer_count         = DEFAULT_BUFFER_COUNT;
static int buffer_size          = DEFAULT_BUFFER_SIZE;
static int evaluator_size       = DEFAULT_EVALUATOR_SIZE;
static int expected_result      = DEFAULT_EXPECTED_RESULT;
static int fiber_count          = DEFAULT_FIBER_COUNT;
static int fiber_stack_size     = DEFAULT_FIBER_STACK_SIZE;
static int word_buffer_size     = DEFAULT_WORD_BUFFER_SIZE;
static int pad_buffer_size      = DEFAULT_PAD_BUFFER_SIZE;
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
    {"create-image",         required_argument, NULL,          'C'},
    {"evaluator-size",       required_argument, NULL,          'E'},
    {"expected-result",      required_argument, NULL,          'r'},
    {"fiber-count",          required_argument, NULL,          'f'},
    {"fiber-stack-size",     required_argument, NULL,          'F'},
    {"image",                required_argument, NULL,          'I'},
    {"pad-buffer-size",      required_argument, NULL,          'D'},
    {"parameter-stack-size", required_argument, NULL,          'P'},
    {"return-stack-size",    required_argument, NULL,          'R'},
    {"source-size",          required_argument, NULL,          'S'},
    {"storage",              required_argument, NULL,          's'},
    {"task-count",           required_argument, NULL,          't'},
    {"word-buffer-size",     required_argument, NULL,          'W'},
    {"help",                 no_argument,       &show_help,    1},
    {"interactive",          no_argument,       &interactive,  1},
    {"quiet",                no_argument,       &quiet,        1},
    {"version",              no_argument,       &show_version, 1},
    {0, 0, 0, 0}
};
