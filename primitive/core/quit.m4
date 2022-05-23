__primitive(pr_quit)  
{
    rp = rp0;
    ip = 0;
    tp[ta_state] = 0;
}
__end
__define_primitive("QUIT", pr_quit);
