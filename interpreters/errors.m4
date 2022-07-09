include(`stack.m4')dnl
divert(`-1')

define(__define_error_symbol,`
  pushdef(`__error_symbol_definitions', `$1 = $2,')
  pushdef(`__error_descriptor_initializers', `{ $1,
  "$1",
  $3
  },
  ')
  __define_constant("$1", $1)
')


define(__show, ``$1'
')
define(__define_error_symbols,`enum error_codes {
stack_foreach(`__error_symbol_definitions', `__show')}')
define(__initialize_error_descriptors,`stack_foreach(`__error_descriptor_initializers', `__show')dnl')

__define_error_symbol(result_ok,                                           0, "ok")
__define_error_symbol(err_abort,                                          -1, "abort")
__define_error_symbol(err_abort_message,                                  -2, "abort message")
__define_error_symbol(err_parameter_stack_overflow,                       -3, "stack overflow")
__define_error_symbol(err_parameter_stack_underflow,                      -4, "stack underflow")
__define_error_symbol(err_return_stack_overflow,                          -5, "return stack overflow")
__define_error_symbol(err_return_stack_underflow,                         -6, "return stack underflow")
__define_error_symbol(err_do_loops_nested_too_deeply_during_execution,    -7, "do loops nested too deeply during execution")
__define_error_symbol(err_dictionary_overflow,                            -8, "dictionary overflow")
__define_error_symbol(err_invalid_memory_address,                         -9, "invalid memory address")
__define_error_symbol(err_division_by_zero,                              -10, "division by zero")
__define_error_symbol(err_result_out_of_range,                           -11, "result out of range")
__define_error_symbol(err_argument_type_mismatch,                        -12, "argument type mismatch")
__define_error_symbol(err_undefined_word,                                -13, "undefined word")
__define_error_symbol(err_interpreting_a_compile_only_word,              -14, "interpreting a compile only word")
__define_error_symbol(err_invalid_forget,                                -15, "invalid forget")
__define_error_symbol(err_attempt_to_use_zero_length_string_as_a_name,   -16, "attempt to use zero length string as a name")
__define_error_symbol(err_pictured_numeric_output_string_overflow,       -17, "pictured numeric output string overflow")
__define_error_symbol(err_parsed_string_overflow,                        -18, "parsed string overflow")
__define_error_symbol(err_definition_name_too_long,                      -19, "definition name too long")
__define_error_symbol(err_write_to_a_read_only_location,                 -20, "write to a read only location")
__define_error_symbol(err_unsupported_operation,                         -21, "unsupported operation")
__define_error_symbol(err_control_structure_mismatch,                    -22, "control structure mismatch")
__define_error_symbol(err_address_alignment_exception,                   -23, "address alignment exception")
__define_error_symbol(err_invalid_numeric_argument,                      -24, "invalid numeric argument")
__define_error_symbol(err_return_stack_imbalance,                        -25, "return stack imbalance")
__define_error_symbol(err_loop_parameters_unavailable,                   -26, "loop parameters unavailable")
__define_error_symbol(err_invalid_recursion,                             -27, "invalid recursion")
__define_error_symbol(err_user_interrupt,                                -28, "user interrupt")
__define_error_symbol(err_compiler_nesting,                              -29, "compiler nesting")
__define_error_symbol(err_obsolescent_feature,                           -30, "obsolescent feature")
__define_error_symbol(err_body_used_on_non_created_definition,           -31, "body used on non created definition")
__define_error_symbol(err_invalid_name_argument,                         -32, "invalid name argument")
__define_error_symbol(err_block_read_exception,                          -33, "block read exception")
__define_error_symbol(err_block_write_exception,                         -34, "block write exception")
__define_error_symbol(err_invalid_block_number,                          -35, "invalid block number")
__define_error_symbol(err_invalid_file_position,                         -36, "invalid file position")
__define_error_symbol(err_file_io_exception,                             -37, "file io exception")
__define_error_symbol(err_non_existent_file,                             -38, "non existent file")
__define_error_symbol(err_unexpected_end_of_file,                        -39, "unexpected end of file")
__define_error_symbol(err_invalid_base_for_floating_point_conversion,    -40, "invalid base for floating point conversion")
__define_error_symbol(err_loss_of_precision,                             -41, "loss of precision")
__define_error_symbol(err_floating_point_divide_by_zero,                 -42, "floating point divide by zero")
__define_error_symbol(err_floating_point_result_out_of_range,            -43, "floating point result out of range")
__define_error_symbol(err_floating_point_stack_overflow,                 -44, "floating point stack overflow")
__define_error_symbol(err_floating_point_stack_underflow,                -45, "floating point stack underflow")
__define_error_symbol(err_floating_point_invalid_argument,               -46, "floating point invalid argument")
__define_error_symbol(err_compilation_word_list_deleted,                 -47, "compilation word list deleted")
__define_error_symbol(err_invalid_postpone,                              -48, "invalid postpone")
__define_error_symbol(err_search_order_overflow,                         -49, "search order overflow")
__define_error_symbol(err_search_order_underflow,                        -50, "search order underflow")
__define_error_symbol(err_compilation_word_list_changed,                 -51, "compilation word list changed")
__define_error_symbol(err_control_flow_stack_overflow,                   -52, "control flow stack overflow")
__define_error_symbol(err_exception_stack_overflow,                      -53, "exception stack overflow")
__define_error_symbol(err_floating_point_underflow,                      -54, "floating point underflow")
__define_error_symbol(err_floating_point_unidentified_fault,             -55, "floating point unidentified fault")
__define_error_symbol(err_quit,                                          -56, "quit")
__define_error_symbol(err_exception_in_sending_or_receiving_a_character, -57, "exception in sending or receiving a character")
__define_error_symbol(err_compile_if_else_or_then_exception,             -58, "compile if else or then exception")
__define_error_symbol(err_allocate,                                      -59, "allocate")
__define_error_symbol(err_free,                                          -60, "free")
__define_error_symbol(err_resize,                                        -61, "resize")
__define_error_symbol(err_close_file,                                    -62, "close file")
__define_error_symbol(err_create_file,                                   -63, "create file")
__define_error_symbol(err_delete_file,                                   -64, "delete file")
__define_error_symbol(err_file_position,                                 -65, "file position")
__define_error_symbol(err_file_size,                                     -66, "file size")
__define_error_symbol(err_file_status,                                   -67, "file status")
__define_error_symbol(err_flush_file,                                    -68, "flush file")
__define_error_symbol(err_open_file,                                     -69, "open file")
__define_error_symbol(err_read_file,                                     -70, "read file")
__define_error_symbol(err_read_line,                                     -71, "read line")
__define_error_symbol(err_rename_file,                                   -72, "rename file")
__define_error_symbol(err_reposition_file,                               -73, "reposition file")
__define_error_symbol(err_resize_file,                                   -74, "resize file")
__define_error_symbol(err_write_file,                                    -75, "write file")
__define_error_symbol(err_write_line,                                    -76, "write line")
__define_error_symbol(err_malformed_xchar,                               -77, "malformed xchar")
__define_error_symbol(err_substitute,                                    -78, "substitute")
__define_error_symbol(err_replaces,                                      -79, "replaces")

__define_error_symbol(err_active_fiber_not_allowed,                      -8192, "active fiber not allowed")
__define_error_symbol(err_active_task_not_allowed,                       -8193, "active task not allowed")
__define_error_symbol(err_fiber_stack_overflow,                          -8194, "fiber stack overflow")
__define_error_symbol(err_fiber_stack_underflow,                         -8195, "fiber stack underflow")
__define_error_symbol(err_invalid_fiber_number,                          -8196, "invalid fiber number")
__define_error_symbol(err_invalid_task_number,                           -8197, "invalid task number")
__define_error_symbol(err_no_fibers_available,                           -8198, "no fibers available")
__define_error_symbol(err_no_tasks_available,                            -8199, "no tasks available")
__define_error_symbol(err_primary_task_not_allowed,                      -8200, "primary task not allowed")
__define_error_symbol(err_unable_to_allocate_memory,                     -8201, "unable to allocate memory")
__define_error_symbol(err_unknown_primitive,                             -8202, "unknown primitive")

divert`'dnl