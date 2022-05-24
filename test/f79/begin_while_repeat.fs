t{ : gi3 begin dup 5 < while dup 1+ repeat ; -> }t
t{ 0 gi3 -> 0 1 2 3 4 5 }t
t{ 4 gi3 -> 4 5 }t
t{ 5 gi3 -> 5 }t
t{ 6 gi3 -> 6 }t

t{ : gi5 begin dup 2 > while
            dup 5 < while dup 1+ repeat
        123 else 345 then ; -> }t

t{ 1 gi5 -> 1 345 }t
t{ 2 gi5 -> 2 345 }t
t{ 3 gi5 -> 3 4 5 123 }t
t{ 4 gi5 -> 4 5 123 }t
t{ 5 gi5 -> 5 123 }t
