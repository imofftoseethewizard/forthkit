# Errors

The listing below contains the numeric value in the first column,
the C language symbol in the second, the remainder of the line
forming the description of the error.

## Forth Standard Errors

These are defined in the [Forth standard](https://forth-standard.org/standard/exception).

      0 result_ok                                         ok
     -1 err_abort                                         abort
     -2 err_abort_message                                 abort message
     -3 err_parameter_stack_overflow                      stack overflow
     -4 err_parameter_stack_underflow                     stack underflow
     -5 err_return_stack_overflow                         return stack overflow
     -6 err_return_stack_underflow                        return stack underflow
     -7 err_do_loops_nested_too_deeply_during_execution   do loops nested too deeply during execution
     -8 err_dictionary_overflow                           dictionary overflow
     -9 err_invalid_memory_address                        invalid memory address
    -10 err_division_by_zero                              division by zero
    -11 err_result_out_of_range                           result out of range
    -12 err_argument_type_mismatch                        argument type mismatch
    -13 err_undefined_word                                undefined word
    -14 err_interpreting_a_compile_only_word              interpreting a compile only word
    -15 err_invalid_forget                                invalid forget
    -16 err_attempt_to_use_zero_length_string_as_a_name   attempt to use zero length string as a name
    -17 err_pictured_numeric_output_string_overflow       pictured numeric output string overflow
    -18 err_parsed_string_overflow                        parsed string overflow
    -19 err_definition_name_too_long                      definition name too long
    -20 err_write_to_a_read_only_location                 write to a read only location
    -21 err_unsupported_operation                         unsupported operation
    -22 err_control_structure_mismatch                    control structure mismatch
    -23 err_address_alignment_exception                   address alignment exception
    -24 err_invalid_numeric_argument                      invalid numeric argument
    -25 err_return_stack_imbalance                        return stack imbalance
    -26 err_loop_parameters_unavailable                   loop parameters unavailable
    -27 err_invalid_recursion                             invalid recursion
    -28 err_user_interrupt                                user interrupt
    -29 err_compiler_nesting                              compiler nesting
    -30 err_obsolescent_feature                           obsolescent feature
    -31 err_body_used_on_non_created_definition           body used on non created definition
    -32 err_invalid_name_argument                         invalid name argument
    -33 err_block_read_exception                          block read exception
    -34 err_block_write_exception                         block write exception
    -35 err_invalid_block_number                          invalid block number
    -36 err_invalid_file_position                         invalid file position
    -37 err_file_io_exception                             file io exception
    -38 err_non_existent_file                             non existent file
    -39 err_unexpected_end_of_file                        unexpected end of file
    -40 err_invalid_base_for_floating_point_conversion    invalid base for floating point conversion
    -41 err_loss_of_precision                             loss of precision
    -42 err_floating_point_divide_by_zero                 floating point divide by zero
    -43 err_floating_point_result_out_of_range            floating point result out of range
    -44 err_floating_point_stack_overflow                 floating point stack overflow
    -45 err_floating_point_stack_underflow                floating point stack underflow
    -46 err_floating_point_invalid_argument               floating point invalid argument
    -47 err_compilation_word_list_deleted                 compilation word list deleted
    -48 err_invalid_postpone                              invalid postpone
    -49 err_search_order_overflow                         search order overflow
    -50 err_search_order_underflow                        search order underflow
    -51 err_compilation_word_list_changed                 compilation word list changed
    -52 err_control_flow_stack_overflow                   control flow stack overflow
    -53 err_exception_stack_overflow                      exception stack overflow
    -54 err_floating_point_underflow                      floating point underflow
    -55 err_floating_point_unidentified_fault             floating point unidentified fault
    -56 err_quit                                          quit
    -57 err_exception_in_sending_or_receiving_a_character exception in sending or receiving a character
    -58 err_compile_if_else_or_then_exception             compile if else or then exception
    -59 err_allocate                                      allocate
    -60 err_free                                          free
    -61 err_resize                                        resize
    -62 err_close_file                                    close file
    -63 err_create_file                                   create file
    -64 err_delete_file                                   delete file
    -65 err_file_position                                 file position
    -66 err_file_size                                     file size
    -67 err_file_status                                   file status
    -68 err_flush_file                                    flush file
    -69 err_open_file                                     open file
    -70 err_read_file                                     read file
    -71 err_read_line                                     read line
    -72 err_rename_file                                   rename file
    -73 err_reposition_file                               reposition file
    -74 err_resize_file                                   resize file
    -75 err_write_file                                    write file
    -76 err_write_line                                    write line
    -77 err_malformed_xchar                               malformed xchar
    -78 err_substitute                                    substitute
    -79 err_replaces                                      replaces

# Forthkit Errors

    -8192 err_active_fiber_not_allowed                    active fiber not allowed
    -8193 err_active_task_not_allowed                     active task not allowed
    -8194 err_fiber_stack_overflow                        fiber stack overflow
    -8195 err_fiber_stack_underflow                       fiber stack underflow
    -8196 err_invalid_fiber_number                        invalid fiber number
    -8197 err_invalid_task_number                         invalid task number
    -8198 err_no_fibers_available                         no fibers available
    -8199 err_no_tasks_available                          no tasks available
    -8200 err_primary_task_not_allowed                    primary task not allowed
    -8201 err_unable_to_allocate_memory                   unable to allocate memory
    -8202 err_unknown_primitive                           unknown primitive
