__primitive(pr_abort)  
{
     /* -1 is the throw code for abort.
        see https://forth-standard.org/standard/exception
     */
    *--sp = -1;
    _abort();
}
__end
__define_primitive("ABORT", pr_abort);