( a new task defaults to the active task's base )
t{ 1000 1000 reserve task tbase @ -> base @ }t

1000 constant dict-size
dict-size reserve constant dict-start

dict-size dict-start task constant t

16 t tbase !

: test-tbase 10 . ;

( should output a )

' test-tbase fiber constant f

t f ftask ! f start
