: two-step 10 20 ;
' two-step fiber constant two-step-fiber

( default steps should be -1, indicating unlimited stepping )
t{ two-step-fiber fsteps @ -> -1 }t

( execute the first step, putting 10 on the stack )
t{ 1 two-step-fiber fsteps ! two-step-fiber start -> 10 }t

( check that the fiber's step count is zero )
t{ two-step-fiber fsteps @ -> 0 }t

( execute the second step )
t{ 1 two-step-fiber fsteps ! two-step-fiber start -> 20 }t
