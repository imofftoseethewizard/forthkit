if (!_is_primitive(*ip))          \
	_enter(); \
goto *(cell *)_to_pv(*ip++);