1000 constant dict-size
dict-size reserve constant dict-start

dict-size dict-start task constant t

: task-test here here ;

' task-test fiber constant f

t{ f ftask @ -> 0 }t

1 f fsteps !

t{ f start -> here }t

-1 f fsteps !
t f ftask !

( runs with its own stack )
t{ f start -> }t