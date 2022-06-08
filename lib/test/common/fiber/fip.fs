: push-10 10 ;
: push-20 20 ;

( check initial fiber ip )
t{ ' swap fiber fip @ -> ' swap }t

( check fiber ip is zero after it is finished )
t{ ' push-10 fiber dup start swap fip @ -> 10 0 }t

( check that setting ip will change behavior )j
t{ ' push-10 fiber ' push-20 over fip ! start -> 20 }t
