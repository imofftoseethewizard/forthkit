     /*
       : do-compile ( w )
               dup 2 cells + @ ( flags )
               dup <immediate flag> and
               if
                   ( word flags )
                   drop execute
               else
                   <inline flag> and
                   if
                       ?
                       begin
                           ?
                           < op_exit > =
                       while
                           @ ,
                           ?
                       repeat
                   else
                       3 cells + ,
                   then
               then
               ;
      */
