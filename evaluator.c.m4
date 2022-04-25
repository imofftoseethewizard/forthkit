#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>

#include "evaluator.h"

char *store_counted_string(const char *s, char *here);

void
init_engine(cell *e, unsigned long size)
{
    e[ea_size]    = size;
    e[ea_forth] = 0;
}

void
reset_execution_state(cell *e)
{
    e[ea_sp] = e[ea_sp0];
    e[ea_rp] = e[ea_rp0];
    e[ea_ip] = 0;
}

int
evaluate(cell *engine, const char *source, int storage_fd)
{
    /* These are the most commonly referenced variables. */
    register cell *e = engine;
    register cell *ip;
    register cell *sp;
    register cell *rp;

    if (e[ea_interpret]) {

        ip = _to_ptr(e[ea_ip]);
        sp = _to_ptr(e[ea_sp]);
        rp = _to_ptr(e[ea_rp]);

    } else {

        rp = e + (engine_attribute_count + SOURCE_SIZE + RETURN_STACK_SIZE);
        sp = rp + PARAMETER_STACK_SIZE;

        /* registers */
        e[ea_ip]          = 0;
        e[ea_rp]          = _from_ptr(rp);
        e[ea_sp]          = _from_ptr(sp);
        e[ea_here]        = e[ea_sp] + BUFFER_COUNT * sizeof(cell);

        /* internal state */
        e[ea_base]        = 10;
        e[ea_context]     = 0;
        e[ea_current]     = _from_ptr(&e[ea_forth]);
        e[ea_data]        = e[ea_here];
        e[ea_forth]       = 0;
        e[ea_rp0]         = e[ea_rp];
        e[ea_source_idx]  = 0;
        e[ea_source_len]  = 0;
        e[ea_sp0]         = e[ea_sp];
        e[ea_state]       = 0;
        e[ea_interpret]   = 0;
        e[ea_source_addr] = _from_ptr(&e[engine_attribute_count]);
        e[ea_blk]         = 0;
        e[ea_buffers]     = e[ea_sp];
        e[ea_next_buffer] = 0;
        e[ea_scr]         = 0;

        for (register int i = 0; i < BUFFER_COUNT; i++)
            e[e[ea_buffers] + i] = -1;
    }

    /* These are generally useful to have, but probably not worth putting
       in a register.
     */
    char *here = (char *)_to_ptr(e[ea_here]);
    cell *rp0  = (cell *)_to_ptr(e[ea_rp0]);
    cell *sp0  = (cell *)_to_ptr(e[ea_sp0]);

    /* Contains the throw code for uncaught exceptions. */
    int result = 0;
    include(__execution_model)dnl
    include(__evaluator_primitives)dnl
    include(__compiled_words)dnl
    __declare_primitives()dnl
    /* The first run will have context == 0. The preamble detects that and
       defines primitives and the bootstrap interpreter.
     */
    if (!e[ea_context]) {
undivert(__primitive_word_definitions)
undivert(__compiled_word_definitions)dnl
        e[ea_context] = _from_ptr(&e[ea_forth]);
    }

    if (source) {
        _debug("interpreting source '%s'\n", source);

        memcpy(_to_ptr(e[ea_source_addr]), source, e[ea_source_len] = strlen(source));
        e[ea_source_idx] = 0;

        rp = rp0;
        *--rp = 0;
        ip = _to_ptr(e[ea_interpret]);
    }

    __implement_evaluator_core() dnl

    /* Store state back in the engine structure. */
    e[ea_ip]   = _from_ptr(ip);
    e[ea_sp]   = _from_ptr(sp);
    e[ea_rp]   = _from_ptr(rp);
    e[ea_here] = _from_ptr(here);

    _debug("done with run: result: %d\n", result);
    _print_stack();
    return result;
}

char *
store_counted_string(const char *s, char *here)
{
    cell n = strlen(s);

    here = (char *)_align(here);

    *(length_type *)here = n;

    strncpy((char *)((length_type *)here + 1), s, n);

    return here + sizeof(cell) + n + 1;
}

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

cell engine[((1 << 16)-1)/sizeof(cell)];

int
main(int argc, char *argv[])
{
    number result;
    char *line;
    int storage_fd = -1;

    _debug("engine: %lx top: %lx\n", (long)engine, (long)((char *)engine + sizeof(engine)));

    /* Clears structure. */
    init_engine(engine, sizeof(engine));

    _debug("engine initialized.\n");

    printf("Forthkit FORTH-79\n");

    if (argc > 1)
        storage_fd = open(argv[argc-1], O_RDWR);

    while (1) {

        line = readline(NULL);

        if (!line) break;

        result = evaluate(engine, line, storage_fd);
        switch (result) {
        case 0:
            printf("ok\n");
            break;

        case -1:
            show_error(engine, "aborted", engine[ea_source_idx]);
            break;

        case -10:
            show_error(engine, "division by zero", engine[ea_source_idx]);
            break;

        case -13:
            show_error(engine, "unrecognized word", engine[ea_source_idx]);
            break;

        case -24:
            show_error(engine, "invalid numeric argument", engine[ea_source_idx]);
            break;

        case -33:
            show_error(engine, "block read error", engine[ea_source_idx]);
            break;

        case -34:
            show_error(engine, "block write error", engine[ea_source_idx]);
            break;

        case -39:
            show_error(engine, "unexpected end of input", engine[ea_source_idx]);
            break;

        default:
            fprintf(stderr, "unknown throw code: %ld\n", (long)result);
            show_error(engine, "error location", engine[ea_source_idx]);
            break;
        }

        free(line);
    }
    /* exit(evaluate(engine, argv[argc-1]), -1); */
    /* exit(evaluate(engine, "15 : cc create , does> @ dup . cr ; cc"), -1); */

}
__discard_all_diversions()dnl
