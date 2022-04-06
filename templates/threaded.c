{{{extra_headers}}}

#define BUFFER_COUNT             {{{buffer_count}}}
#define BUFFER_SIZE              {{{buffer_size}}}
#define CELL_TYPE                {{{cell_type}}}
#define DOUBLE_TYPE              {{{double_type}}}
#define LENGTH_TYPE              {{{length_type}}}
#define MAX_WORD_LENGTH          {{{max_word_length}}}
#define PARAMETER_STACK_SIZE     {{{parameter_stack_size}}}
#define RETURN_STACK_SIZE        {{{return_stack_size}}}
#define SOURCE_SIZE              {{{source_size}}}

/* Diagnostic output control */
#define LOG                      {{{diagnostic.log}}}
#define TRACE                    {{{diagnostic.trace}}}
#define VERBOSE                  {{{diagnostic.verbose}}}

typedef unsigned CELL_TYPE cell;
typedef CELL_TYPE number;
typedef CELL_TYPE cell_offset;

#define c_msb ((cell)1 << (sizeof(cell) * 8 - 1))

typedef LENGTH_TYPE length_type;

typedef DOUBLE_TYPE double_number;
typedef unsigned DOUBLE_TYPE double_cell;

#define _from_high_word(x) ((x) >> (sizeof(number)*8))
#define _from_low_word(x)  ((number)(x))
#define _to_high_word(x)   (((double_number)(x)) << (sizeof(number)*8))
#define _to_low_word(x)    ((double_number)(x))

/* The memory model defines _to_ptr, _from_ptr, _is_primitive, _from_pr,
   and _to_pv
 */
{{{memory_model}}}

#define _primitive(name) if (0) name:
#define _pr_value(x)       ((void *)&&x)
#define _pr_value_base     (void *)&&__first
#define _pr_value_limit    (void *)&&__last

#define _next()                                 \
    do {                                        \
        _trace("start next: ");                 \
                                                \
        while (ip && !_is_primitive(*ip)) {     \
            _trace("execute next: ");           \
            *--rp = _from_ptr(ip+1);            \
            ip = _to_ptr(*ip);                  \
        }                                       \
                                                \
        _trace("primitive next: ");             \
        if (ip) goto *_to_pv(*ip++);         \
                                                \
        _trace("exiting next: ");               \
        goto __last;                            \
    }                                           \
    while (0)

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

__first:
    {{{operators}}}
    {{{primitives}}}
    {{{compiled_words}}}

    /* The first run will have context == 0. The preamble detects that and
       defines primitives and the bootstrap interpreter.
     */
    if (!e[ea_context])
        e[ea_context] = _from_ptr(&e[ea_forth]);

    if (source) {
        _debug("interpreting source '%s'\n", source);

        memcpy(_to_ptr(e[ea_source_addr]), source, e[ea_source_len] = strlen(source));
        e[ea_source_idx] = 0;

        rp = rp0;
        *--rp = 0;
        ip = _to_ptr(e[ea_interpret]);
    }

    _next();
__last:

    /* Store state back in the engine structure. */
    e[ea_ip]   = _from_ptr(ip);
    e[ea_sp]   = _from_ptr(sp);
    e[ea_rp]   = _from_ptr(rp);
    e[ea_here] = _from_ptr(here);

    _debug("done with run: result: %d\n", result);
    _print_stack();
    return result;
}
