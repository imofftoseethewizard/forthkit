/* https://forth-standard.org/standard/exception */

enum standard_result_code {
    next_error_code = -84,
    err_invalid_fiber_number,
    err_no_fibers_available,
    err_fiber_stack_underflow,
    err_fiber_stack_overflow,
    err_replaces,
    err_substitute,
    err_malformed_xchar,
    err_write_line,
    err_write_file,
    err_resize_file,
    err_reposition_file,
    err_rename_file,
    err_read_line,
    err_read_file,
    err_open_file,
    err_flush_file,
    err_file_status,
    err_file_size,
    err_file_position,
    err_delete_file,
    err_create_file,
    err_close_file,
    err_resize,
    err_free,
    err_allocate,
    err_compile_if_else_or_then_exception,
    err_exception_in_sending_or_receiving_a_character,
    err_quit,
    err_floating_point_unidentified_fault,
    err_floating_point_underflow,
    err_exception_stack_overflow,
    err_control_flow_stack_overflow,
    err_compilation_word_list_changed,
    err_search_order_underflow,
    err_search_order_overflow,
    err_invalid_postpone,
    err_compilation_word_list_deleted,
    err_floating_point_invalid_argument,
    err_floating_point_stack_underflow,
    err_floating_point_stack_overflow,
    err_floating_point_result_out_of_range,
    err_floating_point_divide_by_zero,
    err_loss_of_precision,
    err_invalid_base_for_floating_point_conversion,
    err_unexpected_end_of_file,
    err_non_existent_file,
    err_file_io_exception,
    err_invalid_file_position,
    err_invalid_block_number,
    err_block_write_exception,
    err_block_read_exception,
    err_invalid_name_argument,
    err_body_used_on_non_created_definition,
    err_obsolescent_feature,
    err_compiler_nesting,
    err_user_interrupt,
    err_invalid_recursion,
    err_loop_parameters_unavailable,
    err_return_stack_imbalance,
    err_invalid_numeric_argument,
    err_address_alignment_exception,
    err_control_structure_mismatch,
    err_unsupported_operation,
    err_write_to_a_read_only_location,
    err_definition_name_too_long,
    err_parsed_string_overflow,
    err_pictured_numeric_output_string_overflow,
    err_attempt_to_use_zero_length_string_as_a_name,
    err_invalid_forget,
    err_interpreting_a_compile_only_word,
    err_undefined_word,
    err_argument_type_mismatch,
    err_result_out_of_range,
    err_division_by_zero,
    err_invalid_memory_address,
    err_dictionary_overflow,
    err_do_loops_nested_too_deeply_during_execution,
    err_return_stack_underflow,
    err_return_stack_overflow,
    err_parameter_stack_underflow,
    err_parameter_stack_overflow,
    err_abort_message,
    err_abort,
    result_ok
};

#define _define_result_messages()                     \
static char *result_messages[] = {                    \
    "ok",                                             \
    "abort",                                          \
    "abort message",                                  \
    "stack overflow",                                 \
    "stack underflow",                                \
    "return stack overflow",                          \
    "return stack underflow",                         \
    "do loops nested too deeply during execution",    \
    "dictionary overflow",                            \
    "invalid memory address",                         \
    "division by zero",                               \
    "result out of range",                            \
    "argument type mismatch",                         \
    "undefined word",                                 \
    "interpreting a compile only word",               \
    "invalid forget",                                 \
    "attempt to use zero length string as a name",    \
    "pictured numeric output string overflow",        \
    "parsed string overflow",                         \
    "definition name too long",                       \
    "write to a read only location",                  \
    "unsupported operation",                          \
    "control structure mismatch",                     \
    "address alignment exception",                    \
    "invalid numeric argument",                       \
    "return stack imbalance",                         \
    "loop parameters unavailable",                    \
    "invalid recursion",                              \
    "user interrupt",                                 \
    "compiler nesting",                               \
    "obsolescent feature",                            \
    "body used on non created definition",            \
    "invalid name argument",                          \
    "block read exception",                           \
    "block write exception",                          \
    "invalid block number",                           \
    "invalid file position",                          \
    "file io exception",                              \
    "non existent file",                              \
    "unexpected end of file",                         \
    "invalid base for floating point conversion",     \
    "loss of precision",                              \
    "floating point divide by zero",                  \
    "floating point result out of range",             \
    "floating point stack overflow",                  \
    "floating point stack underflow",                 \
    "floating point invalid argument",                \
    "compilation word list deleted",                  \
    "invalid postpone",                               \
    "search order overflow",                          \
    "search order underflow",                         \
    "compilation word list changed",                  \
    "control flow stack overflow",                    \
    "exception stack overflow",                       \
    "floating point underflow",                       \
    "floating point unidentified fault",              \
    "quit",                                           \
    "exception in sending or receiving a character",  \
    "compile if else or then exception",              \
    "allocate",                                       \
    "free",                                           \
    "resize",                                         \
    "close file",                                     \
    "create file",                                    \
    "delete file",                                    \
    "file position",                                  \
    "file size",                                      \
    "file status",                                    \
    "flush file",                                     \
    "open file",                                      \
    "read file",                                      \
    "read line",                                      \
    "rename file",                                    \
    "reposition file",                                \
    "resize file",                                    \
    "write file",                                     \
    "write line",                                     \
    "malformed xchar",                                \
    "substitute",                                     \
    "replaces",                                       \
    "fiber stack overflow",                           \
    "fiber stack underflow",                          \
    "no fibers available",                            \
    "invalid fiber number",                           \
}
