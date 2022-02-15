variable actual-depth
create actual-results 32 4 * allot
variable start-depth
variable xcursor
: cells 4 * ;
: <> = 0= ;
: t{ depth start-depth ! 0 xcursor ! ;
: -> depth dup actual-depth ! start-depth @ > if depth start-depth @ - 0 do actual-results i cells + ! loop then ;
: }t depth actual-depth @ = if depth start-depth @ > if depth start-depth @ - 0 do actual-results i cells + @ <> if ." incorrect result: " leave then loop then else ." wrong number of results: " then ;