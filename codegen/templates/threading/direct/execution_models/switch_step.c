if (!_is_primitive(*ip))
	_enter();

else {
	switch (_to_pv(*ip++)) {
	/*{ primitive_implementations }*/
	default:
		result = err_unknown_primitive;
		ip = 0;
		break;
	}
}
