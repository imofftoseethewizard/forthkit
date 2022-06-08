0 f@ constant f-primary

: 10-to-primary 10 f-primary ftask @ >t ;

' 10-to-primary fiber constant f

1000 dup reserve task constant t

t f ftask !
t{ f start -> 10 }t
