: step-one 10 ;
: step-two -10 step-one 20 ;

' step-two fiber constant two-step-fiber

( start the fiber to set up its return stack )
1 two-step-fiber fsteps ! two-step-fiber start

( check that the fiber's return stack is not empty )
t{ two-step-fiber frp0 @ two-step-fiber frp @ = -> <false> }t

( disable step limit )
-1 two-step-fiber fsteps !

( set rp stop limit )
two-step-fiber frp @ two-step-fiber fstop !

t{ two-step-fiber start -> 10 }t

( clear rp stop limit )
two-step-fiber frp0 @ two-step-fiber fstop !

( the exit primitive checks rp stop and sets steps to 0 to halt, so disable )
( the step limit again )
-1 two-step-fiber fsteps !

t{ two-step-fiber start -> 20 }t
