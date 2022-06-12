__primitive(pr_drop)
{
    /* DROP ( n -- )

       Drop the top value from the stack.
     */
    ++sp;
}
__end
__define_primitive("DROP", pr_drop);
