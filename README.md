# A Forth Construction Kit

Forthkit is a set of components from which it should be easy to build
a Forth-like language, a standard Forth, or some specialization
thereof.  It's currently in a rough state with little documentation,
though it can create working FORTH-79, FORTH-83 (incomplete), and
FORTH-94 (incomplete) languages.

## Roadmap

The this project evolved from an effort to understand how stack-based
interpreters are implemented.  Presently, it uses M4 for template
instantiation and builds directly on the host which contains the repo,
and it is largely undocumented.  The next obvious steps are to move
the development environment into a docker container, and to switch
from M4 to Python.  I'll add documentation as I go.  I haven't looked
at this project much in the last two years, and much of the details
have been swapped out. (See
[plguile3](https://github.com/imofftoseethewizard/plguile3) for what
had my attention most recently.)

I'll fill out the README, and this section in particular more later.
Beyond the obvious bits of adding the rest of the vocabularies for
FORTH-83 and FORTH-94, there are some hints of the future in the
[f0](https://github.com/imofftoseethewizard/plguile3) branch.

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
