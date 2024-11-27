#! /usr/bin/env bash

#<md
#
# This script checks that the environment variables are set, have
# valid values, and do not violate any of the following constraints:
#
# * `Clang` only supports the `switch` execution type.
# * With `host` addressing the cell size must equal the target architecture's pointer size.
# * The cell size must not exceed the target architecture's pointer size.
#
#/>

if [[ -z $CC ]]
then
    echo "CC is unset or empty." >&2
    exit 1
elif [[ ! $CC =~ ^(clang|gcc)$ ]]
then
    echo "CC must be one of \"clang\" or \"gcc\", not \"$CC\"." >&2
    exit 1
fi

if [[ -z $FK_ARCH ]]
then
    echo "FK_ARCH is unset or empty." >&2
    exit 1
elif [[ ! $FK_ARCH =~ ^(i386|x86_64)$ ]]
then
    echo "FK_ARCH must be one of \"i386\" or \"x86_64\", not \"$FK_ARCH\"." >&2
    exit 1
fi

if [[ -z $FK_CELL_SIZE ]]
then
    echo "FK_CELL_SIZE is unset or empty." >&2
    exit 1
elif [[ ! $FK_CELL_SIZE =~ ^(2|4|8)$ ]]
then
    echo "FK_CELL_SIZE must be one of 2, 4, or 8, not \"$FK_CELL_SIZE\"." >&2
    exit 1
fi

if [[ -z $FK_STAGE ]]
then
    echo "FK_STAGE is unset or empty." >&2
    exit 1
elif [[ ! $FK_STAGE =~ ^(debug|checked|unsafe)$ ]]
then
    echo "FK_STAGE must be one of \"debug\", \"checked\" or \"unsafe\", not \"$FK_STAGE\"." >&2
    exit 1
fi

if [[ $CC == clang ]]
then
    if [[ $FK_EXECUTION_MODEL != switch ]]
    then
        echo "Only the switch execution model is supported with clang, not \"$FK_EXECUTION_MODEL." >&2
        exit 1
    fi
fi

if [[ $FK_ADDRESS_MODEL == host ]]
then
    if [[ $FK_ARCH == i386 ]]
    then
        required_size=4
    elif [[ $FK_ARCH == x86_64 ]]
    then
        required_size=8
    fi

    if [[ $FK_CELL_SIZE != required_size ]]
    then
        echo "With the host address model, the cell size must match the address size." >&2
        echo "For $FK_ARCH, this must be $required_size, not \"$FK_CELL_SIZE\"." >&2
        exit 1
    fi
fi

if [[ $FK_CELL_SIZE == 8 && $FK_ARCH == i386 ]]
then
    echo "The cell size must be no larger than the architecture's address size." >&2
    echo "8 byte cells are incompatible with the i386 architecture. Use 2 or 4 instead." >&2
    exit 1
fi
