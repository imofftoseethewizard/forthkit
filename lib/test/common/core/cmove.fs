create fbuf 20 c, 20 c, 20 c,
create sbuf 12 c, 34 c, 56 c,

: seebuf fbuf c@ fbuf char+ c@ fbuf char+ char+ c@ ;

t{ fbuf fbuf 3 chars cmove seebuf -> 20 20 20 }t
t{ sbuf fbuf 0 chars cmove seebuf -> 20 20 20 }t
t{ sbuf fbuf 1 chars cmove seebuf -> 12 20 20 }t
t{ sbuf fbuf 3 chars cmove seebuf -> 12 34 56 }t
t{ fbuf char+ fbuf 2 chars cmove seebuf -> 34 56 56 }t
t{ fbuf fbuf char+ 2 chars cmove seebuf -> 34 34 34 }t
