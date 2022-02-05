#define _to_ptr(x)   (cell *)((char *)e + (x))
#define _from_ptr(x) (cell)((char *)(x) - (char *)e)

#define c_pr_addr_flag (1L << (sizeof(cell) * 8 - 1))

#define _is_primitive(x)  (((long)(x)) & c_pr_addr_flag)
#define _pr_addr(x) (void *)(_pr_ref(x) - _pr_ref(__first) | c_pr_addr_flag)
#define _pr_deref(x) (((x) & ~ c_pr_addr_flag) + _pr_ref(__first))
