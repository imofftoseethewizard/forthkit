#define CELL_TYPE                int
#define DOUBLE_TYPE              long long
#define LENGTH_TYPE              unsigned char

#define BUFFER_SIZE              1024 /* move to runtime */
#define FIBER_STACK_SIZE         4    /* move to runtime */
#define FIBER_COUNT              4    /* move to runtime */
#define MAX_WORD_LENGTH          64   /* move to runtime */
#define PARAMETER_STACK_SIZE     128  /* move to runtime */
#define RETURN_STACK_SIZE        256  /* move to runtime */
#define SOURCE_SIZE              1024 /* move to runtime */
#define TASK_COUNT               2    /* move to runtime */

/* Diagnostic output control */
#define LOG                      0
#define TRACE                    0
#define VERBOSE                  0

#define DEBUG                    0
#define BOUNDS_CHECKING          1
