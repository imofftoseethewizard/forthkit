t{ : gd2 do i -1 +loop ; -> }t
t{  1 4 gd2 -> 4 3 2  1 }t
t{ -1 2 gd2 -> 2 1 0 -1 }t

( There is a subtle difference in the definition of +loop     )
( between FORTH-79 and FORTH-83. The earlier version defines  )
( loop exit as the index being >= the limit -- if inc > 0 --  )
( and < the limit if inc < 0. All later versions define the   )
( exit condition in terms of the index crossing the limit.    )
( 8 of the test cases below were changed for FORTH-79.        )

variable gditerations
variable gdincrement

: gd7 ( limit start increment -- )
    gdincrement !
    0 gditerations !
    do
        1 gditerations +!
        i
        gditerations @ 6 = if leave then
        gdincrement @
    +loop gditerations @
;

t{    4  4  -1 gd7 ->  4                  1  }t
t{    1  4  -1 gd7 ->  4  3  2  1         4  }t
t{    4  1  -1 gd7 ->  1                  1  }t
t{    4  1   0 gd7 ->  1  1  1  1   1   1 6  }t
t{    0  0   0 gd7 ->  0                  1  }t
t{    1  4   0 gd7 ->  4                  1  }t
t{    1  4   1 gd7 ->  4                  1  }t
t{    4  1   1 gd7 ->  1  2  3            3  }t
t{    4  4   1 gd7 ->  4                  1  }t
t{    2 -1  -1 gd7 -> -1                  1  }t
t{   -1  2  -1 gd7 ->  2  1  0 -1         4  }t
t{    2 -1   0 gd7 -> -1 -1 -1 -1  -1  -1 6  }t
t{   -1  2   0 gd7 ->  2                  1  }t
t{   -1  2   1 gd7 ->  2                  1  }t
t{    2 -1   1 gd7 -> -1 0 1              3  }t
t{  -20 30 -10 gd7 -> 30 20 10  0 -10 -20 6  }t
t{  -20 31 -10 gd7 -> 31 21 11  1  -9 -19 6  }t
t{  -20 29 -10 gd7 -> 29 19  9 -1 -11     5  }t
