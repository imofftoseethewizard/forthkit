t{       0       1 > -> <false> }t
t{       1       2 > -> <false> }t
t{      -1       0 > -> <false> }t
t{      -1       1 > -> <false> }t
t{       0       0 > -> <false> }t
t{       1       1 > -> <false> }t
t{       1       0 > -> <true>  }t
t{       2       1 > -> <true>  }t
t{       0      -1 > -> <true>  }t
t{       1      -1 > -> <true>  }t

t{ min-int       0 > -> <false> }t
t{ min-int max-int > -> <false> }t
t{       0 max-int > -> <false> }t

t{       0 min-int > -> <true>  }t
t{ max-int min-int > -> <true>  }t
t{ max-int       0 > -> <true>  }t
