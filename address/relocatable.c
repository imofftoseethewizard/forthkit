#define _to_ptr(x)   (cell *)((char *)e + (x))
#define _from_ptr(x) (cell)((char *)(x) - (char *)e)

#define c_pr_addr_flag (1L << (sizeof(cell) * 8 - 1))
#define c_pr_addr_base ((size_t)&&__first - c_pr_addr_flag)

#define _is_primitive(x)  (((size_t) x) & c_pr_addr_flag)
#define _pr_addr(x) ((&&x) - c_pr_addr_base)
#define _pr_deref(x) ((x) + c_pr_addr_base)
