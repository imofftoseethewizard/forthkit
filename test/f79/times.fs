t{  0  0 * ->  0 }t
t{  0  1 * ->  0 }t
t{  1  0 * ->  0 }t
t{  1  2 * ->  2 }t
t{  2  1 * ->  2 }t
t{  3  3 * ->  9 }t
t{ -3  3 * -> -9 }t
t{  3 -3 * -> -9 }t
t{ -3 -3 * ->  9 }t

t{ mid-uint+1 1 rshift 2 *               -> mid-uint+1 }t
t{ mid-uint+1 2 rshift 4 *               -> mid-uint+1 }t
t{ mid-uint+1 1 rshift mid-uint+1 or 2 * -> mid-uint+1 }t
