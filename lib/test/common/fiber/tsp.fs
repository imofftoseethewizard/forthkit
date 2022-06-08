1000 constant dict-size
dict-size reserve constant dict-start

dict-size dict-start task constant t

: task-test here ;

' task-test fiber constant f

t f ftask !

( runs with its own stack )
t{ t tsp @ f start t tsp @ - -> cell }t