#define _pr_value(x)       ((cell)-x ## _token)
#define _pr_value_base     (-(number)pr_token_count + 1)
#define _pr_value_limit    -1
#define _primitive(name) case _pr_value(name):

#define _next()          break

    do {
        _trace("start dispatch:     ");

        while (ip && !_is_primitive(*ip)) {
            _trace("dispatch execute:   ");
            *--rp = _from_ptr(ip+1);
            ip = _to_ptr(*ip);
        }

        _trace("dispatch primitive: ");
        if (ip) switch (*ip++) {
#define _dispatch()                                     \
        default:                                    \
          ip = 0; \
        break;
          /* illegal operator */                        \
        }                                               \
    }                                                   \
    while (ip);                                         \
                                                        \
    _trace("dispatch exited:   ");

#define _declare_primitive(x)
