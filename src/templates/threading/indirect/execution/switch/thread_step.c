switch (_to_pv(*wp++)) {

/*{ primitive_implementations }*/

default:
    _debug("unknown_primitive: %x\n", *(wp-1));
    result = err_unknown_primitive;
    ip = 0;
    break;
}

wp = ip ? _to_ptr(*ip++) : NULL;
