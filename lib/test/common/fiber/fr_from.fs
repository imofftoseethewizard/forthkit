( this word should always fail, right? )
: this-shouldn't-work 10 >r 20 ;

' this-shouldn't-work fiber constant f

( set single step for f, start f to push 10 onto its return stack, take 10 )
( from its return stack, set unlimited steps for f to let it complete. )
t{ 1 f fsteps ! f start f fr> -1 f fsteps ! f start -> 10 20 }t