/*|

`DOES> ( -- addr )` compiling: `( -- )`

Defines the execution-time action of a word created by a
high-level defining word.  Used in the form:

    : <namex> ... <create> ... DOES> ... ;

and then

    <namex> <name>

where `<create>` is `CREATE` or any user defined word which executes
`CREATE`.

Marks the termination of the defining part of the defining word
`<namex>` and then begins the definition of the execution-time action
for words that will later be defined by `<namex>`.  When `<name>` is
later executed, the address of `<name>`'s parameter field is placed on
the stack and then the sequence of words between `DOES>` and `;` are
executed.

The compile-time context of `DOES>` is the compilation of a new
defining word `<namex>`. `DOES>` captures the location of the code
that will be compiled after `DOES>`, compiles a literal to put that
address on the stack, and then compiles `pr_do_does` and `op_exit`.
`op_exit` is required to ensure that the code which provides the
interpretation semantics of words defined with `<namex>` is isolated
from `<namex>`'s interpretation semantics.

When `<namex>` is executed, `pr_do_does` replaces the interpretation
semantics of the most recently defined word with `op_do_does` and the
code address from the stack.  If the previously defined word was not
defined with `CREATE`, then an ambiguous condition exists.  In the
case of a direct-threaded interpreter, `CREATE` produces the following
code

    op_literal
    <addr of cell below op_exit>
    op_exit

to implement `DOES>`, this is replaced with

    op_do_does
    <address of does> code>
    op_exit

In indirect threading, this begins with

    op_do_const
    <addr of next cell>

and is replaced by

    op_do_does
    <address of does> code>

where `op_do_does` puts the address after `op_exit` (direct threaded)
or after the code offset (indirect threaded) on the stack when
executing words defined with `<namex>`.  In both cases, `op_do_does`
then jumps to the code address immediately following.

  |*/

// DOES immediate

pr_does:
{
    _compile_pw(op_literal);
    _store_data(_from_ptr((cell *)dp + 3));
    _compile_pw(pr_do_does);
    _compile_pw(op_exit);

    _check_dictionary_bounds();
}
