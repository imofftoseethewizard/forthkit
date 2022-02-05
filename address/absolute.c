#define _to_ptr(x)   ((cell *)(x))
#define _from_ptr(x) ((cell)(x))

#define _is_primitive(x)  ((void *)(x) >= _pr_ref(__first) && (void *)(x) <= _pr_ref(__last))
#define _pr_addr(x) _pr_ref(x)
#define _pr_deref(x) x
