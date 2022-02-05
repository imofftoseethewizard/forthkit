#define _to_ptr(x)   ((cell *)(x))
#define _from_ptr(x) ((cell)(x))

#define _is_primitive(x)  ((void *)(x) >= &&__first && (void *)(x) <= &&__last)
#define _pr_addr(x) (&&x)
#define _pr_deref(x) x
