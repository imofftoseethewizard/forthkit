( this word should always fail, right? )
: this-shouldn't-work 10 >r 20 ;

' this-shouldn't-work fiber constant f

( check if it works with a different fiber )
t{ 1 f fsteps ! f start f fr> -1 f fsteps ! f start -> 10 20 }t