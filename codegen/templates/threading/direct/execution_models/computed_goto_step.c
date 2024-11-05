if (!_is_primitive(*ip))          \
	goto op_enter;                \
goto *(cell *)_to_pv(*ip++);
