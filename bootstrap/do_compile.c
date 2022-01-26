     /*
       : do-compile ( w )
               dup 2 cells + @ ( flags )
               dup <immediate flag> and
               if
                   ( word flags )
                   drop execute
               else
                 compile,
               then
               ;
      */
