t{ #f ' #f fiber start #f -> 1 2 1 }t

: push-10 10 ;
: push-20 20 ;

t{ ' push-10 fiber start push-20 -> 10 20 }t
