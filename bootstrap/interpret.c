#define do_compile xp
#define do_literal yp

#include "bootstrap/do_compile.c"
#include "bootstrap/do_literal.c"

if (1) {
     /*
       : interpret
           begin
               32 word ?dup
           while
               find ?dup
               if
                   state @
                   if
                       0> if execute else compile, then
                   else
                       drop execute
                   then
               else
                   0 swap count >number
                   state @ if literal then
               then
           repeat
       ;
      */

     /* : interpret                                     */
     begin_define_word("interpret");

     /*    begin                                        */
     exec(pr_compile_begin, __bootstrap_after_compile_begin);
  __bootstrap_after_compile_begin:

     /*        32 word ?dup                             */
     _store_data(&&op_literal);
     _store_data(32);
     _store_data(&&pr_word);
     _store_data(&&pr_q_dup);

     /*    while                                        */
     exec(pr_compile_while, __bootstrap_after_compile_while);
  __bootstrap_after_compile_while:

     /*        find ?dup                                */
     _store_data(&&pr_find);
     _store_data(&&pr_q_dup);

     /*        if                                       */
     exec(pr_compile_if, __bootstrap_after_find_compile_if);
  __bootstrap_outer_after_compile_if:

     /*            state @                              */
     _store_data(&&pr_state);
     _store_data(&&pr_fetch);

     /*            if                                   */
     exec(pr_compile_if, __bootstrap_inner_after_compile_if);
  __bootstrap_inner_after_compile_if:

     /*                0> if execute else compile, then */
     _store_data(&&pr_zero_gt);
     exec(pr_compile_if, __bootstrap_do_compile_after_compile_if);
  __bootstrap_do_compile_after_compile_if:
     _store_data(&&pr_execute);
     exec(pr_compile_else, __bootstrap_do_compile_after_compile_else);
  __bootstrap_do_compile_after_compile_else:
     _store_data(&&pr_store_compiled);
     exec(pr_compile_then, __bootstrap_do_compile_after_compile_then);
  __bootstrap_do_compile_after_compile_then:

     /*            else                                 */
     exec(pr_compile_else, __bootstrap_inner_after_compile_else);
  __bootstrap_inner_after_compile_else:

     /*                drop execute                     */
     _store_data(&&pr_drop);
     _store_data(&&pr_execute);

     /*            then                                 */
     exec(pr_compile_then, __bootstrap_inner_after_compile_then);
  __bootstrap_inner_after_compile_then:

     /*        else                                     */
     exec(pr_compile_else, __bootstrap_outer_after_compile_else);
  __bootstrap_outer_after_compile_else:

     /*            0 swap count >number                 */
     _store_data(&&op_literal);
     _store_data(0);
     _store_data(&&pr_swap);
     _store_data(&&pr_count);
     _store_data(&&pr_to_number);

     /*            state @ if literal then              */
     _store_data(&&pr_state);
     _store_data(&&pr_fetch);
     exec(pr_compile_if, __bootstrap_do_compile_after_compile_if);
  __bootstrap_do_literal_after_compile_if:
     _store_data(&&pr_literal);
     exec(pr_compile_then, __bootstrap_do_literal_after_compile_then);
  __bootstrap_do_literal_after_compile_then:

     /*        then                                     */
     exec(pr_compile_then, __bootstrap_outer_after_compile_then);
  __bootstrap_outer_after_compile_then:

     /*    repeat                                       */
     exec(pr_compile_repeat, __bootstrap_compile_repeat);
  __bootstrap_after_compile_repeat:

     /* ;                                               */
     _store_data(&&op_exit);
}

#undef do_compile
#undef do_literal
/*
   Alternate version, with modern words parse-name, find-name, etc.
    begin
        parse-name ( c-addr n ) ?dup
    while
        find-name
        ?dup-if
            state if name>compile else name>interpret then execute
        else
            parse-literal
        then
    repeat
    drop
 */
