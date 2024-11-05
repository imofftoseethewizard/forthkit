    void *_base_probe(void) {
        return __builtin_frame_address(0);
    }

    void const * _pr_value_base  = _base_probe();
    void const * _pr_value_limit = __builtin_frame_address(0);
