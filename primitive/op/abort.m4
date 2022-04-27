#define _abort() result = *sp, sp = sp0, rp = rp0, ip = 0, e[ea_state] = 0

__primitive(op_abort)
{
    _abort();
    _next();
}
__end
