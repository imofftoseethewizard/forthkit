#define _to_ptr(x)   ((cell *)(x))
#define _from_ptr(x) ((cell)(x))

#define _is_primitive(x)  ((void *)(x) >= _pr_value_base && (void *)(x) <= _pr_value_limit)
#define _from_pv(x) x
#define _to_pv(x) x
