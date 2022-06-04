1000 dup reserve task constant t

: push-10 10 ;

' push-10 fiber constant f

t{ t f ftask ! f start t t> -> 10 }t