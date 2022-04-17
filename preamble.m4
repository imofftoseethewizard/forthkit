define(`header_definitions', 1)dnl
define(`primitive_declarations', 2)dnl
define(`primitive_implementations', 3)dnl
define(`compiled_word_declarations', 4)dnl
define(`compiled_word_definitions', 5)dnl
define(`discard_diversion', `divert(-1)undivert($1)divert')dnl
define(`discard_all_diversions', `divert(-1)undivert(1)undivert(2)undivert(4)undivert(4)undivert(5)divert')dnl
define(`include_primitive', `divert(header_definitions)include(`$1')divert')dnl
