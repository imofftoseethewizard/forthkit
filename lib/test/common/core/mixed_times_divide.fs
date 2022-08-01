: NIP SWAP DROP ;

T{       5  0      7             11 M*/ ->  3  0 }T
T{       5  0     -7             11 M*/ -> -3 -1 }T
T{      -5 -1      7             11 M*/ -> -3 -1 }T
T{      -5 -1     -7             11 M*/ ->  3  0 }T

T{ MAX-2INT       8             16 M*/ -> HI-2INT }T
T{ MAX-2INT      -8             16 M*/ -> HI-2INT DNEGATE }T
T{ MIN-2INT       8             16 M*/ -> LO-2INT }T
T{ MIN-2INT      -8             16 M*/ -> LO-2INT DNEGATE }T

T{ MAX-2INT MAX-INT        MAX-INT M*/ -> MAX-2INT }T
T{ MAX-2INT MAX-INT 2/     MAX-INT M*/ -> MAX-INT 1- HI-2INT NIP }T
T{ MIN-2INT LO-2INT NIP DUP NEGATE M*/ -> MIN-2INT }T
T{ MIN-2INT LO-2INT NIP 1- MAX-INT M*/ -> MIN-INT 3 + HI-2INT NIP 2 + }T
T{ MAX-2INT LO-2INT NIP DUP NEGATE M*/ -> MAX-2INT DNEGATE }T
T{ MIN-2INT MAX-INT            DUP M*/ -> MIN-2INT }T