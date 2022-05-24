create wbuf 20 , 20 , 20 ,
create rbuf 12 , 34 , 56 ,

: seebuf wbuf @ wbuf cell+ @ wbuf cell+ cell+ @ ;

t{ wbuf wbuf 3 move seebuf -> 20 20 20 }t
t{ rbuf wbuf 0 move seebuf -> 20 20 20 }t
t{ rbuf wbuf 1 move seebuf -> 12 20 20 }t
t{ rbuf wbuf 3 move seebuf -> 12 34 56 }t
t{ wbuf cell+ wbuf 2 move seebuf -> 34 56 56 }t
t{ wbuf wbuf cell+ 2 move seebuf -> 34 34 34 }t
