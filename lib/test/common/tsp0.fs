1000 constant dict-size
dict-size reserve constant dict-start

dict-size dict-start task constant t

: task-test here ;

' task-test fiber constant f

t f ftask !

( runs with its own stack )
t{ f start t tsp0 @ t tsp @ - -> cell }t