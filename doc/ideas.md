Presume that all operators are included in a file "operators.c",
all primitives are included in a file "primitives.c", and all compiled
words in "compiled.c", where each operator is defined by something like

    operator(op_branch) {
        _debug("branch: ");
        _print_stack();
        ip += *sp++ ? 2 : 0;
        _next();
    }

each primitive is defined by something like

    primitive("DEPTH", pr_depth, 0) {
        *--sp = sp0 - sp;
        _next();
    }

and each compiled word is defined by something like

    compiled_word("SPACE", cw_space, 0) {
        _compile_pr(op_literal);
        _store_data(32);
        _compile_pr(pr_emit);
        _compile_pr(op_exit);
    }

Then different definitions of those macros can produce the appropriate
translations.

## Local functions

Declarations of local functions:

    #define primitive(name, label, flags) auto void label(void)

but to define the corresponding function

    #define primitive(name, label, flags) void label(void)

and to add it to the dictionary

    #define primitive(name, label, flags) define_primitive(name, label, flags)

where `define_primitive` encapsulates the storage of the ...

## Threaded
