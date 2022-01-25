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
                       execute
                   then
               else
                   do_literal
               then
           repeat
       ;
      */

     /* : interpret               */
     begin_define_primitive("interpret");

     /*    begin                  */
     exec(p1_compile_begin, __bootstrap_after_compile_begin);
  __bootstrap_after_compile_begin:

     /*        32 word ?dup       */
     _store_data(&&op_literal);
     _store_data(32);
     _store_data(&&p1_word);
     _store_data(&&p1_q_dup);

     /*    while                  */
     exec(p1_compile_while, __bootstrap_after_compile_while);
  __bootstrap_after_compile_while:

     /*        find ?dup          */
     _store_data(&&p1_find);
     _store_data(&&p1_q_dup);

     /*        if                 */
     exec(p1_compile_if, __bootstrap_after_find_compile_if);
  __bootstrap_outer_after_compile_if:

     /*            state          */
     _store_data(&&p1_state);
     exec(p1_compile_if, __bootstrap_inner_after_compile_if);

     /*            if             */
  __bootstrap_inner_after_compile_if:

     /*                do_compile */
     _store_data(do_compile);

     /*            else           */
     exec(p1_compile_else, __bootstrap_inner_after_compile_else);
  __bootstrap_inner_after_compile_else:

     /*                execute    */
     _store_data(&&p1_execute);

     /*            then           */
     exec(p1_compile_then, __bootstrap_inner_after_compile_then);
  __bootstrap_inner_after_compile_then:

     /*        else               */
     exec(p1_compile_else, __bootstrap_outer_after_compile_else);
  __bootstrap_outer_after_compile_else:

     /*            do_literal     */
     _store_data(do_literal);

     /*        then               */
     exec(p1_compile_then, __bootstrap_outer_after_compile_then);
  __bootstrap_outer_after_compile_then:

     /*    repeat                 */
     exec(p1_compile_repeat, __bootstrap_compile_repeat);
  __bootstrap_after_compile_repeat:

     /* ; */
     _store_data(&&op_exit);

  /*    _store_data(&&p1_dup); */
  /*    _store_data(&&op_literal); */
  /*    _store_data(sizeof(cell) * 2); */
  /*    _store_data(&&p1_plus); */
  /*    _store_data(&&p1_fetch); */
  /*    _store_data(&&op_literal); */
  /*    _store_data(c_immediate); */
  /*    _store_data(&&p1_and); */
  /*    exec(p1_compile_if, __bootstrap_after_immediate_compile_if); */
  /* __bootstrap_after_immediate_compile_if: */
  /*    _store_data(&&p1_execute); */
  /*    exec(p1_compile_else, __bootstrap_after_immediate_compile_else); */
  /* __bootstrap_after_immediate_compile_else: */

}

#undef do_compile
#undef do_literal
