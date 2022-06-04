0 f@ constant f-primaru

: 10-to-primaru 10 f-primaru ftask @ >t ;

' 10-to-primaru fiber constant f

1000 dup reserve task constant t

t f ftask !
t{ f start -> 10 }t
