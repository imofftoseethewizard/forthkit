#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>

#include "evaluator.h"

void
show_error(cell *e, const char *message, cell n) {
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

_define_result_messages();

cell evaluator[((1 << 16)-1)/sizeof(cell)];

int
main(int argc, char *argv[])
{
    number result;
    char *line;
    int storage_fd = -1;

    _debug("evaluator: %lx top: %lx\n", (long)evaluator, (long)((char *)evaluator + sizeof(evaluator)));

    /* Clears structure. */
    init_evaluator(evaluator, sizeof(evaluator));

    _debug("evaluator initialized.\n");

    printf("Forthkit FORTH-79\n");

    if (argc > 1)
        storage_fd = open(argv[argc-1], O_RDWR);

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
            show_error(
                evaluator,
                (result <= next_error_code) ? "unknown_error" : result_messages[-result],
                evaluator[ea_source_idx]);
            break;
        }

        free(line);
    }
    /* exit(evaluate(evaluator, argv[argc-1]), -1); */
    /* exit(evaluate(evaluator, "15 : cc create , does> @ dup . cr ; cc"), -1); */

}
