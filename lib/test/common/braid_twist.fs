: push-1 1 ;
: push-2 2 ;
: push-3 3 ;

t{ ' push-1 fiber lay ' push-2 fiber lay ' push-3 fiber lay 1 braid twist twist twist -> 3 2 1 }t
t{ ' push-1 fiber lay ' push-2 fiber lay ' push-3 fiber lay 2 braid twist twist twist -> 2 3 1 }t
t{ ' push-1 fiber lay ' push-2 fiber lay ' push-3 fiber lay 3 braid twist twist twist -> 1 2 3 }t
