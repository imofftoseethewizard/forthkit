#define _abort(x) result = (x), sp = sp0, rp = rp0, ip = 0, e[ea_state] = 0

__primitive(op_abort)
{
    _abort(*sp);
}
__end

__define_operator("abort", op_abort);
