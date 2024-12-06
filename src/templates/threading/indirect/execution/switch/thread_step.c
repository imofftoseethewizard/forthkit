switch (_to_pv(*wp++)) {

/*{ primitive_implementations }*/

default:
    _debug("unknown_primitive: %x %x %x %x\n", *_to_ptr(0x274c), *_to_ptr(0x2750), *_to_ptr(0x2754), *_to_ptr(0x2758));
    _debug("unknown_primitive: %x %x %x\n", *(wp-2), *(wp-1), *wp);
    result = err_unknown_primitive;
    ip = 0;
    break;
}

wp = ip ? _to_ptr(*ip++) : NULL;
