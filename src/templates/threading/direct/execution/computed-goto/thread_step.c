if (!_is_primitive(*ip))          \
    goto op_enter; \
else \
    goto *(cell *)_to_pv(*ip++); \
