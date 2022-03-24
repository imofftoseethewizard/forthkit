#define _c_half_cell_bits (8 * sizeof(cell) / 2))

#define _high_half(x) ((x) >> _c_half_cell_bits)
#define _low_half(x)  ((x) & (1 << _c_half_cell_bits - 1)
