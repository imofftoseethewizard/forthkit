#include "config.h"

typedef unsigned CELL_TYPE cell;
typedef CELL_TYPE number;

#define c_msb ((cell)1 << (sizeof(cell) * 8 - 1))

typedef LENGTH_TYPE length_type;

typedef DOUBLE_TYPE double_number;
typedef unsigned DOUBLE_TYPE double_cell;

#define _from_high_word(x) ((x) >> (sizeof(number)*8))
#define _from_low_word(x)  ((number)(x))
#define _to_high_word(x)   (((double_number)(x)) << (sizeof(number)*8))
#define _to_low_word(x)    ((double_number)(x))

enum engine_attribute {
    ea_size,
    ea_ip,
    ea_rp,
    ea_sp,
    ea_here,
    ea_base,
    ea_context,
    ea_current,
    ea_data,
    ea_forth,
    ea_rp0,
    ea_source_idx,
    ea_source_len,
    ea_sp0,
    ea_state,
    ea_interpret,
    ea_source_addr,
    ea_blk,
    ea_buffers,
    ea_next_buffer,
    ea_scr,

    /* must be last */
    engine_attribute_count
};

enum compiled_words {
    enumerate_compiled_words()
};

extern void init_engine(cell *e, unsigned long size);
extern int evaluate(cell *e, const char *source, int storage_fd);
extern void reset_execution_state(cell *e);
