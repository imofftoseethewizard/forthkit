#define _emit() putc(*sp++, stdout)

__primitive(pr_emit)  
{
    _emit();
}
__end
__define_primitive("EMIT", pr_emit);
