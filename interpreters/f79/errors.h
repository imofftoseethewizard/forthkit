/* https://forth-standard.org/standard/exception */

enum standard_result_code {
    next_error_code = -86,
    err_active_fiber_not_allowed,                      /* -85 */
    err_unknown_primitive,                             /* -84 */
    err_invalid_fiber_number,                          /* -83 */
    err_no_fibers_available,                           /* -82 */
    err_fiber_stack_underflow,                         /* -81 */
    err_fiber_stack_overflow,                          /* -80 */
    err_replaces,                                      /* -79 */
    err_substitute,                                    /* -78 */
    err_malformed_xchar,                               /* -77 */
    err_write_line,                                    /* -76 */
    err_write_file,                                    /* -75 */
    err_resize_file,                                   /* -74 */
    err_reposition_file,                               /* -73 */
    err_rename_file,                                   /* -72 */
    err_read_line,                                     /* -71 */
    err_read_file,                                     /* -70 */
    err_open_file,                                     /* -69 */
    err_flush_file,                                    /* -68 */
    err_file_status,                                   /* -67 */
    err_file_size,                                     /* -66 */
    err_file_position,                                 /* -65 */
    err_delete_file,                                   /* -64 */
    err_create_file,                                   /* -63 */
    err_close_file,                                    /* -62 */
    err_resize,                                        /* -61 */
    err_free,                                          /* -60 */
    err_allocate,                                      /* -59 */
    err_compile_if_else_or_then_exception,             /* -58 */
    err_exception_in_sending_or_receiving_a_character, /* -57 */
    err_quit,                                          /* -56 */
    err_floating_point_unidentified_fault,             /* -55 */
    err_floating_point_underflow,                      /* -54 */
    err_exception_stack_overflow,                      /* -53 */
    err_control_flow_stack_overflow,                   /* -52 */
    err_compilation_word_list_changed,                 /* -51 */
    err_search_order_underflow,                        /* -50 */
    err_search_order_overflow,                         /* -49 */
    err_invalid_postpone,                              /* -48 */
    err_compilation_word_list_deleted,                 /* -47 */
    err_floating_point_invalid_argument,               /* -46 */
    err_floating_point_stack_underflow,                /* -45 */
    err_floating_point_stack_overflow,                 /* -44 */
    err_floating_point_result_out_of_range,            /* -43 */
    err_floating_point_divide_by_zero,                 /* -42 */
    err_loss_of_precision,                             /* -41 */
    err_invalid_base_for_floating_point_conversion,    /* -40 */
    err_unexpected_end_of_file,                        /* -39 */
    err_non_existent_file,                             /* -38 */
    err_file_io_exception,                             /* -37 */
    err_invalid_file_position,                         /* -36 */
    err_invalid_block_number,                          /* -35 */
    err_block_write_exception,                         /* -34 */
    err_block_read_exception,                          /* -33 */
    err_invalid_name_argument,                         /* -32 */
    err_body_used_on_non_created_definition,           /* -31 */
    err_obsolescent_feature,                           /* -30 */
    err_compiler_nesting,                              /* -29 */
    err_user_interrupt,                                /* -28 */
    err_invalid_recursion,                             /* -27 */
    err_loop_parameters_unavailable,                   /* -26 */
    err_return_stack_imbalance,                        /* -25 */
    err_invalid_numeric_argument,                      /* -24 */
    err_address_alignment_exception,                   /* -23 */
    err_control_structure_mismatch,                    /* -22 */
    err_unsupported_operation,                         /* -21 */
    err_write_to_a_read_only_location,                 /* -20 */
    err_definition_name_too_long,                      /* -19 */
    err_parsed_string_overflow,                        /* -18 */
    err_pictured_numeric_output_string_overflow,       /* -17 */
    err_attempt_to_use_zero_length_string_as_a_name,   /* -16 */
    err_invalid_forget,                                /* -15 */
    err_interpreting_a_compile_only_word,              /* -14 */
    err_undefined_word,                                /* -13 */
    err_argument_type_mismatch,                        /* -12 */
    err_result_out_of_range,                           /* -11 */
    err_division_by_zero,                              /* -10 */
    err_invalid_memory_address,                        /*  -9 */
    err_dictionary_overflow,                           /*  -8 */
    err_do_loops_nested_too_deeply_during_execution,   /*  -7 */
    err_return_stack_underflow,                        /*  -6 */
    err_return_stack_overflow,                         /*  -5 */
    err_parameter_stack_underflow,                     /*  -4 */
    err_parameter_stack_overflow,                      /*  -3 */
    err_abort_message,                                 /*  -2 */
    err_abort,                                         /*  -1 */
    result_ok                                          /*   0 */
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
    "unknown primitive",                              \
    "active fiber not allowed"                        \
}
