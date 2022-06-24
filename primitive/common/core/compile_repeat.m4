#define _compile_repeat()                               \
do {                                                    \
    _compile_pr(op_jump);                               \
    _store_data(*sp++ - _from_ptr(dp));                 \
    _compile_jump_target();                             \
} while (0);

__primitive(pr_compile_repeat)
{
    /* REPEAT compiling: ( sys -- )

       Used in the form:

       |   BEGIN ... flag WHILE ... REPEAT

       At execution time, REPEAT continues execution to just after
       the corresponding BEGIN . sys is balanced with its
       corresponding WHILE .
     */

    _compile_repeat();
    _check_dictionary_bounds();
}
__end
__define_immediate_primitive("REPEAT", pr_compile_repeat);
