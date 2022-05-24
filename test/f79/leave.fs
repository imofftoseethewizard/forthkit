t{ : gd5 123 swap 0 do
        i 4 > if drop 234 leave then
    loop ; -> }t

t{ 1 gd5 -> 123 }t
t{ 5 gd5 -> 123 }t
t{ 6 gd5 -> 234 }t
