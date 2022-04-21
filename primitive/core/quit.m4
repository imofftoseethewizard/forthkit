__primitive(pr_quit)  
{
    rp = rp0;
    ip = 0;
    e[ea_state] = 0;
}
__end
__define_primitive("QUIT", pr_quit);
