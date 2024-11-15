# A Forth Construction Kit

Forthkit is a set of components from which it should be easy to build
a Forth-like language, a standard Forth, or some specialization
thereof.  It's currently in a rough state with little documentation,
though it can create working FORTH-79, FORTH-83 (incomplete), and
FORTH-94 (incomplete) languages.

## Goals

Forthkit will provide a toolkit for generating, building, and
understanding Forth-like languages.  It will generate all-in-one C
files with a narrative structure and comments providing comprehensive
explanations, allowing the user to read, understand, and experiment
with them.

## Roadmap

The this project evolved from an effort to understand how stack-based
interpreters are implemented.  Presently, it uses M4 for template
instantiation and builds directly on the host which contains the repo,
and it is largely undocumented.  The next obvious steps are to move
the development environment into a docker container, and to switch
from M4 to Python (in progress).  I'll add documentation as I go.  I
haven't looked at this project much in the last two years, and much of
the details have been swapped out. (See
[plguile3](https://github.com/imofftoseethewizard/plguile3) for what
had my attention most recently.)

I'll fill out the README, and this section in particular more later.
Beyond the obvious bits of adding the rest of the vocabularies for
FORTH-83 and FORTH-94, there are some hints of the future in the
[f0](https://github.com/imofftoseethewizard/forthkit/tree/f0) branch.

## Development

The local build and test set-up is in an intermediate state.  For now,
to get the local build working you will need to create a docker image
and run `monitor.sh` using the `fk-run` tool.  From the repository root
do

    test/create-test-image.sh
    bin/fk-run
    . prep.rc
    scripts/monitor.sh

The first step creates a docker image based on debian bookworm which
includes all of the prerequisites for the build.  For details, see
`test/Dockerfile`.  The next step starts a bash session in a transient
container started from that image.  By default it bind-mounts the
current directory into the container and sets the working directory to
the same.  The third and fourth steps should be run inside the
container. `. prep.rc` sets up two important environment variables.
`FORTHKIT` should contain the path to the repository root, and
`FAMILIES` lists the Forth families the build monitor should watch and
build.  The last starts the build monitor.  It watches the files that
feed into the build -- see `interpreters/Makefile` -- and rebuilds and
retests every variant specified for the Forth families watched.  Note
this does not yet shut down cleanly, so if the monitor has been
interrupted, there may be lingering subprocesses that need to be
stopped, or else there will be build races and spurious build errors.

To run one of the Forths built this way, you can find them in with
`find build -name interpreter`.  If you're on a Linux system, then you
should be able to run any of these directly.

    build/f79/clang-rel-switch-a32-c2/bin/interpreter

If you're running this from a Mac (untested), then you will need to use fk-run

    fk-run build/f79/clang-rel-switch-a32-c2/bin/interpreter

to run it inside of the build environment.

## Roadmap

Code generation via M4 needs to be replaced with a higher-level
language.  While M4 is ubiquitous, lightweight, and fast, its means of
abstraction do not lend themselves to readability.  The obvious
replacement is Python. it's currently the most popular language by
several measures, and this application does not require much in terms
of computation, so the few milliseconds one might save by implementing
this in Go or some "faster" language just don't matter.

There are three major tasks that this project will accomplish:
generating, building, and running Forth or Forth-derived interpreters.
The interface will be a CLI with subcommands

Initialize a development environment

    fk init

Generate source code (initialize with defaults if required)

    fk gen

Build source code (generate with defaults if required)

    fk build

Run interpreter (build with defaults if required)

    fk run

While this could be built with standard libraries, the `click` package
makes this very easy.  That will be the one non-standard dependency.

Options for `fk gen`
* address model: relative or absolute addressing. -a, --address-model
  r(elative), a(bsolute)

* execution model: computed goto, local subroutine, switch, -e,
  --execution-model (computed-)g(oto), l(ocal-subroutine), s(witch)

* threading model: direct or indirect, --t, --threading d(irect) i(ndirect)

* concurrency: fibered, single, -c, --concurrency, f(ibered), s(ingle)

* word size: 2, 4, or 8, -w -word-size
* arch: 32-bit or 64-bit, -a --architecture

Options or `fk build`
* compiler: gcc or clang (currently) -c, --compiler gcc, clang
* build host: local or container, -h, --host
* build target: local or container, -t, --target
* word size: 2, 4, or 8, -w -word-size
* arch: 32-bit or 64-bit, -a --architecture


## Code Generation

The output of code generation is directory with a containing all of
the files required by the selected compiler to build the interpreter.
It will include a makefile, an rc file for customizable settings, and
all required source files necessary to create three interpreter
variants.  One contains bootstrap code for producing an evaulator
image.  The second is a bare interpreter that has no bootstrap and
requires a compatible evaluator image to start.  The third is an
evaluator with the image generated by the bootstrap interpreter
bundled with it in a single file.  If the target of compilation is not
the host architecture, then an emulator will be required to generate
the evaluator image from the bootstrap evaluator.  If this is not
available, then only the first two evaluators will be built.

## Deliverable

This project will be structured as a Python package such that one could
do the following

    python3 -m pip install -y forthkit
    fk run

and have a running Forth environment.

## Specifications

### Notation

Pre-processor definitions that are intended to be specified during
compilation are in all caps, eg, `CELL_TYPE`.

Constants defined by pre-processor macros begin with `c_`.

Pre-processor macros that act as functions begin with an underscore.

### Templates

Template files should be C syntax so that formatters and syntax
highlighters work correctly.  Template parameters are delimited by
braced multiline comments: `/*{` and `}*/`.  Files should have a `.c`
or a `.h` suffix corresponding to the suffix of the destination of
their content.

Templates are structured such that the generated C files can be easily
translated into markdown files.  Block comments begin with `/*|` and
end with `|*/`, both surrounded by blank lines.  To translate a file
to markdown, opening comments are translated to ` ```C ` and the
closing comments to ` ``` `, each consuming the blank line adjacent to
the code block.  There is a little nuance in handling the beginning of
the file, but in general the opening comment delimiter will be dropped
since all generated files will start with a comment.  Original
template files also indent code blocks 4 spaces.  The `indent` utility
removes this during code generation, but a small Python utility
restores it prior to finalizing generated code.  (TODO)

### Configuration Files

Config files use the INI syntax.  I want the Python tooling to use
only standard modules that come with Python, and I didn't want to
write my own DSL for configuration.  Taking only reasonable formats,
that left INI, JSON, TOML, and XML.  JSON doesn't support comments,
and TOML wasn't expressive enough, in particular for lists.  XML is
too verbose.  I would have preferred (safe) YAML, but it's not part of
the standard CPython distribution.

The content of configuration files is in flux, and will be for some
time.

### Primitive Definition

Primitives are small pieces of C code that are parsed and contribute
information to various data structures and are interpolated into the
.c source file of the evaluator.  There is a strict form they must
follow for this to work properly, for example

    // LITERAL immediate

    pr_literal:
    {
        /* LITERAL compiling: ( n -- ) run-time ( -- n )

           If compiling, then compile the stack value n as a single cell
           literal, which when later executed, will leave n on the stack.
         */

        _compile_pr(op_literal);
        _store_data(*sp++);
        _check_dictionary_bounds();
    }

If the first non-blank line is a line-based comment, it must contain
the name of the dictionary entry the primitive will have, and it may
optionally include "immediate" after the name to indicate that the
word will be an immediate word.  If the first non-blank line is not a
line comment, then the primitive will not have a dictionary entry,
though it may still be used to compose words internally (TODO
reference for internal word composition).  The next non-blank line
must be the internal name of the primitive followed by a colon.  The
name must follow C identifier rules.  The remainder of the file forms
the body of the primitive.  It must be a brace-enclosed block of code
and it may not contain a `break`, `continue`, or `return`
statement. (TODO reference for identifiers available within
primitives)

### Compiled Word Definitions

Compiled words are created using preprocessor macros to create C code
to build definitions during bootstrap without using the outer
interpreter.  This is used to create a few defining words which enable
later words to be defined using the outer interpreter.  They have a similar
file format to primitives.  For example, the implementation of `:`

    // :
    cw_colon:
    {
        _compile_parse_word();
        _compile_pw(pr_do_colon);
    }

The first line above is a line comment which gives the name of the
word.  It may optionally include the word "immediate" to specify that
the new word is an immediate word.  The next non-comment line must be
a C label giving the internal name of the compiled word.  It is
strongly suggested that this begin with `cw_`.  This must be followed
by a single block which contains statements which will build the
definition of the word at bootstrap.  These statements are surrounded
by macros to define the word.  In the example above, this expands to

    _define_compiled_word(":", cw_colon, 0);
    {
        _compile_parse_word();
        _compile_pw(pr_do_colon);
    }
    _end_compiled_word();

The two macros that bookend the implementation provided in the
definition of `cw_colon` above are essentially the functionality of
`:` and `;`, with the additional detail that the start of the compiled
word is saved and can later be referenced for compilation by

    _compile_cw(cw_colon);



### Prelude Word Definitions

Prelude words are specified as Forth source and are interpreted during
bootstrap.  For example, the canonical Forth-79/Forth-83 definition of
`CONSTANT`

    : CONSTANT
        >R : R>
        [COMPILE] LITERAL
        [COMPILE] ;
    ;

is processed into

    const char *prelude[] = {
            ...
            ": CONSTANT",
            "    >R : R>",
            "    [COMPILE] LITERAL",
            "    [COMPILE] ;",
            ";",
            ...
        };

where the ellipses represent stringified forms of other built-in
words.

### Artifacts

Project initialization produces a directory structure containing a
copy of all templates and primitives selected in the configuration.
TODO

Code generation produces two files: `evaluator.c` and `evaluator.h`.
`evaluator.c` implements the inner and outer evaluators and built-in
primitives.  `evaluator.h` provides definitions to include and use the
evaluator in another file.  The provided `interpreter.c` does just
that and implements command line interface and REPL for the evaluator.
This is but one embodiment, and like Guile or Lua, it could be used as
an extension language for your favorite C project.

Building the default artifacts produces two objects and three
executables. The bootstrapping code, which allows the creation of
evaluator memory images, can be optionally included, so there are two
versions produced by compiling `evaluator.c`: `evaluator.o` and
`bootstrap-evaluator.o`.  From these, there three versions of the
default interpreter: `bootstrap-interpreter`, `bare-interpreter`, and
(bundled) `interpreter`.  The bootstrap interpreter contains the
bootstrap code and is used to create evaluator memory images.  The
bare interpreter has no memory image and no means to create one, and
must be started with one specified on the command line.  The ordinary
interpreter has the default bootstrap image bundled with it, but no
bootstrapping code.
