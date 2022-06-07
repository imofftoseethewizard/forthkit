t{ 0 factive? -> <true> }t
t{ 1 factive? -> <false> }t
t{ -1 factive? -> <false> }t

1000 dup reserve task constant t

: is-primary-active? 0 factive? ;

t{ ' is-primary-active? fiber start -> <false> }t
