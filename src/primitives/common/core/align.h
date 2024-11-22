 /* Note that this assumes that a cell is an power of 2 number of bytes.
    That seems like a safe assumption.
 */

#pragma GCC diagnostic ignored "-Wint-conversion"
#define _align(x) (cell *)((long)(x) + sizeof(cell) - 1 & ~(sizeof(cell) - 1))
