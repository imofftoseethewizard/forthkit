1000 dup reserve task constant t

: finish-t t done ;

' finish-t fiber constant f

t f ftask !

f start
