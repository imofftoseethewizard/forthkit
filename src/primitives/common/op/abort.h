#define _abort(x) result = (x), sp = sp0, rp = rp0, ip = 0, _set_state(0)
