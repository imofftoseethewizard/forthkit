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
