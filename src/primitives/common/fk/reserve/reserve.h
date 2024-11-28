// top is cell-aligned and is the address of the last available
// word in memory.  Reserve (x) bytes and align the result to get
// the new top.  Return the address of the cell above top, as this
// is the beginning of the reserved area.

#define _reserve(x) \
    (top -= (x), \
     top -= (int)top % sizeof(cell), \
     _from_ptr(top + sizeof(cell)))
