create fbuf 00 c, 00 c, 00 c,

: seebuf fbuf c@ fbuf char+ c@ fbuf char+ char+ c@ ;

t{ fbuf 0 20 fill seebuf -> 00 00 00 }t
t{ fbuf 1 20 fill seebuf -> 20 00 00 }t
t{ fbuf 3 20 fill seebuf -> 20 20 20 }t
