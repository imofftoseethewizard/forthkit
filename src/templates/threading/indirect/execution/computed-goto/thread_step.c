wp = _to_ptr(*ip++); \
_trace("early main loop: ");              \
goto *(cell *)_to_pv(*wp++);