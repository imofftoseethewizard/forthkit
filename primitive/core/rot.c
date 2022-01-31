
#define _rot() tmp0 = *sp, *sp = *(sp+2), *(sp+2) = *(sp+1), *(sp+1) = tmp0

_primitive(pr_rot) {
    _rot();
    _next();
}
define_primitive("ROT", pr_rot);
