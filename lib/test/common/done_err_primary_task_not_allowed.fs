0 f@ constant f-primary

: finish-primary f-primary ftask @ done ;

' finish-primary fiber constant f

1000 dup reserve task constant t

t f ftask !
t f start
