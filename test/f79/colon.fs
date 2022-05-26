t{ : nop : [ ' ; compile, ] ; -> }t
t{ nop nop1 nop nop2 -> }t
t{ nop1 -> }t
t{ nop2 -> }t

t{ : gdx   123 ;    : gdx   gdx 234 ; -> }t
t{ gdx -> 123 234 }t
