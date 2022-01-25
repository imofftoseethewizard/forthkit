#define do_compile xp
#define do_literal yp

#include "bootstrap/do_compile.c"
#include "bootstrap/do_literal.c"

if (1) {
     /*
       : interpret
           begin
               bl word ?dup
           while
               find ?dup
               if
                   state
                   if
                       do_compile
                   else
                       drop execute
                   then
               else
                   do_literal
               then
           repeat
       ;
      */

     /* : interpret                 */
     begin_define_word("interpret");

     /*    begin                    */
     exec(pr_compile_begin, __bootstrap_after_compile_begin);
  __bootstrap_after_compile_begin:

     /*        32 word ?dup         */
     _store_data(&&op_literal);
     _store_data(32);
     _store_data(&&pr_word);
     _store_data(&&pr_q_dup);

     /*    while                    */
     exec(pr_compile_while, __bootstrap_after_compile_while);
  __bootstrap_after_compile_while:

     /*        find ?dup            */
     _store_data(&&pr_find);
     _store_data(&&pr_q_dup);

     /*        if                   */
     exec(pr_compile_if, __bootstrap_after_find_compile_if);
  __bootstrap_outer_after_compile_if:

     /*            state            */
     _store_data(&&pr_state);

     /*            if               */
     exec(pr_compile_if, __bootstrap_inner_after_compile_if);
  __bootstrap_inner_after_compile_if:

     /*                do_compile   */
     _store_data(do_compile);

     /*            else             */
     exec(pr_compile_else, __bootstrap_inner_after_compile_else);
  __bootstrap_inner_after_compile_else:

     /*                drop execute */
     _store_data(&&pr_drop);
     _store_data(&&pr_execute);

     /*            then             */
     exec(pr_compile_then, __bootstrap_inner_after_compile_then);
  __bootstrap_inner_after_compile_then:

     /*        else                 */
     exec(pr_compile_else, __bootstrap_outer_after_compile_else);
  __bootstrap_outer_after_compile_else:

     /*            do_literal       */
     _store_data(do_literal);

     /*        then                 */
     exec(pr_compile_then, __bootstrap_outer_after_compile_then);
  __bootstrap_outer_after_compile_then:

     /*    repeat                   */
     exec(pr_compile_repeat, __bootstrap_compile_repeat);
  __bootstrap_after_compile_repeat:

     /* ;                           */
     _store_data(&&op_exit);

  /*    _store_data(&&pr_dup); */
  /*    _store_data(&&op_literal); */
  /*    _store_data(sizeof(cell) * 2); */
  /*    _store_data(&&pr_plus); */
  /*    _store_data(&&pr_fetch); */
  /*    _store_data(&&op_literal); */
  /*    _store_data(c_immediate); */
  /*    _store_data(&&pr_and); */
  /*    exec(pr_compile_if, __bootstrap_after_immediate_compile_if); */
  /* __bootstrap_after_immediate_compile_if: */
  /*    _store_data(&&pr_execute); */
  /*    exec(pr_compile_else, __bootstrap_after_immediate_compile_else); */
  /* __bootstrap_after_immediate_compile_else: */

}

#undef do_compile
#undef do_literal
