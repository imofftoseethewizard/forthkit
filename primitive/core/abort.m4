__primitive(pr_abort)
{
     /* -1 is the throw code for abort.
        see https://forth-standard.org/standard/exception
     */
    _abort(-1);
}
__end
__define_primitive("ABORT", pr_abort);
