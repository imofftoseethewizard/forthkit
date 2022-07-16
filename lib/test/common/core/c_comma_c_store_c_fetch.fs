HERE 1 C,
HERE 2 C,

CONSTANT 2ndc
CONSTANT 1stc

t{    1stc 2ndc <  -> <true> }t
t{ 1stc 1+         ->  2ndc  }t
t{ 1stc C@ 2ndc C@ ->   1 2  }t
t{       3 1stc C! ->        }t
t{ 1stc C@ 2ndc C@ ->   3 2  }t
t{       4 2ndc C! ->        }t
t{ 1stc C@ 2ndc C@ ->   3 4  }t
