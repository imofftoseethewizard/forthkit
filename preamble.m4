define(`__header_definitions', 1)dnl
define(`__primitive_declarations', 2)dnl
define(`__primitive_implementations', 3)dnl
define(`__compiled_word_declarations', 4)dnl
define(`__compiled_word_definitions', 5)dnl
define(`__discard_diversion', `divert(-1)undivert($1)divert')dnl
define(`__discard_all_diversions', `divert(-1)undivert(1)undivert(2)undivert(3)undivert(4)undivert(5)divert')dnl
define(`__include_primitive', `divert(__header_definitions)include(`$1')divert')dnl

define(`__define_primitive_ext',`divert(__compiled_word_declarations)    cw_$2,
divert(__compiled_word_definitions)        _define_primitive_ext($1, $2, cw_$2, $3)')dnl

define(`__define_parsing_primitive',`divert(__compiled_word_declarations)    cw_$2,
divert(__compiled_word_definitions)        _define_parsing_primitive($1, $2, cw_$2)')dnl

define(`__define_primitive',`divert(__compiled_word_declarations)    cw_$2,
divert(__compiled_word_definitions)        _define_primitive($1, $2, cw_$2)')dnl

define(`__define_immediate_primitive',`divert(__compiled_word_declarations)    cw_$2,
divert(__compiled_word_definitions)        _define_immediate_primitive($1, $2, cw_$2)')dnl

define(`__compiled_word',`divert(__compiled_word_declarations)    $2,
divert(__compiled_word_definitions)
        _begin_define_word($1, $3);
        _register_compiled_word($2);')dnl
