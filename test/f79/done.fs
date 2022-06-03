1000 constant dict-size
dict-size reserve constant dict-start

dict-size dict-start task constant t

: star 42 emit ;

' star fiber constant f1
' star fiber constant f2

t f1 ftask !
t f2 ftask !

( check that completing a task will cancel any laid fibers )
f1 lay f2 lay twist t done twist

t{ t tdp @ t ttop @ -> 0 0 }t
