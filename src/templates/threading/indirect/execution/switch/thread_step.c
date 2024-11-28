wp = _to_ptr(*ip++);

switch (_to_pv(*wp++)) {

/*{ primitive_implementations }*/

default:
    result = err_unknown_primitive;
    ip = 0;
    break;
}
