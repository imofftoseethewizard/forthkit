t{ : does1 does> @ 1 + ; -> }t
t{ : does2 does> @ 2 + ; -> }t
t{ create cr1 -> }t
t{ cr1   -> here }t
t{ 1 ,   ->   }t
t{ cr1 @ -> 1 }t
t{ does1 ->   }t
t{ cr1   -> 2 }t
t{ does2 ->   }t
t{ cr1   -> 3 }t

t{ : weird: create does> 1 + does> 2 + ; -> }t
t{ weird: w1 -> }t
t{ w1 -> here 1 + }t
t{ w1 -> here 2 + }t
