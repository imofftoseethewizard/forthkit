t{       0       1 < -> <true>  }t
t{       1       2 < -> <true>  }t
t{      -1       0 < -> <true>  }t
t{      -1       1 < -> <true>  }t
t{       0       0 < -> <false> }t
t{       1       1 < -> <false> }t
t{       1       0 < -> <false> }t
t{       2       1 < -> <false> }t
t{       0      -1 < -> <false> }t
t{       1      -1 < -> <false> }t

t{ min-int       0 < -> <true>  }t
t{ min-int max-int < -> <true>  }t
t{       0 max-int < -> <true>  }t

t{       0 min-int < -> <false> }t
t{ max-int min-int < -> <false> }t
t{ max-int       0 < -> <false> }t
