if (!_is_primitive(*ip))
    _enter();
else
    ((native_word *)(_to_pv(*ip++)))();
