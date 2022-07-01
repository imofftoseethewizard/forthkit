divert(`-1')
define(`__header_definitions', 1)
define(`__primitive_declarations', 2)
define(`__primitive_word_definitions', 3)
define(`__primitive_implementations', 4)
define(`__primitive_registry', 5)
define(`__compiled_word_declarations', 6)
define(`__compiled_word_definitions', 7)
define(`__evaluator_variable_declarations', 8)
define(`__discard_diversion', `divert(-1)undivert($1)divert')
define(`__discard_all_diversions', `divert(-1)undivert(1)undivert(2)undivert(3)undivert(4)undivert(5)undivert(6)undivert(7)undivert(8)divert')
define(`__include_primitive', `divert(__header_definitions)include(`$1')divert`'dnl')
define(`__include_compiled_word', `divert(__compiled_word_definitions)include(`$1')divert`'dnl')

define(`__define_primitive_ext',`divert(__compiled_word_declarations)    cw_$2,
divert(__primitive_word_definitions)        _define_primitive_ext($1, $2, cw_$2, $3)')

define(`__define_parsing_primitive',`divert(__compiled_word_declarations)    cw_$2,
divert(__primitive_word_definitions)        _define_parsing_primitive($1, $2, cw_$2)')

define(`__define_primitive',`divert(__compiled_word_declarations)    cw_$2,
divert(__primitive_word_definitions)        _define_primitive($1, $2, cw_$2)')

define(`__define_immediate_primitive',`divert(__compiled_word_declarations)    cw_$2,
divert(__primitive_word_definitions)        _define_immediate_primitive($1, $2, cw_$2)')

define(`__compiled_word',`divert(__compiled_word_declarations)    $2,
divert(__compiled_word_definitions) _compiled_word($1, $2, $3);');

define(`__evaluator_variables',`divert(__evaluator_variable_declarations)')
define(`__declare_evaluator_variables',`undivert(__evaluator_variable_declarations)')
divert`'dnl
