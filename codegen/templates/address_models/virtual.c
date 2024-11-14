#define _to_ptr(x)   (cell *)((char *)e + (x))
#define _from_ptr(x) (cell)((char *)(x) - (char *)e)

#define c_primitive_flag ((cell)1 << (sizeof(cell) * 8 - 1))

#define _is_primitive(x)  (((long)(x)) & c_primitive_flag)

#define _from_pv(x) (void *)((x) - _pr_value_base | c_primitive_flag)
#define _to_pv(x) (((x) & ~ c_primitive_flag) + _pr_value_base)
