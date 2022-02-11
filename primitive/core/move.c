_primitive(pr_move) {
    memcpy(_to_ptr(*(sp+1)), _to_ptr(*(sp+2)), *sp*sizeof(cell));
    sp += 3;
    _next();
}
_define_primitive("MOVE", pr_move);
