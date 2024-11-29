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

if [[ -z $ARCH ]]
then
    echo "ARCH is unset or empty." >&2
    exit 1
elif [[ ! $ARCH =~ ^(i386|x86_64)$ ]]
then
    echo "ARCH must be one of \"i386\" or \"x86_64\", not \"$ARCH\"." >&2
    exit 1
fi

if [[ -z $CELL_SIZE ]]
then
    echo "CELL_SIZE is unset or empty." >&2
    exit 1
elif [[ ! $CELL_SIZE =~ ^(2|4|8)$ ]]
then
    echo "CELL_SIZE must be one of 2, 4, or 8, not \"$CELL_SIZE\"." >&2
    exit 1
fi

if [[ -z $STAGE ]]
then
    echo "STAGE is unset or empty." >&2
    exit 1
elif [[ ! $STAGE =~ ^(debug|checked|unsafe)$ ]]
then
    echo "STAGE must be one of \"debug\", \"checked\" or \"unsafe\", not \"$STAGE\"." >&2
    exit 1
fi

if [[ $CC == clang ]]
then
    if [[ $EXECUTION_MODEL != switch ]]
    then
        echo "Only the switch execution model is supported with clang, not \"$EXECUTION_MODEL." >&2
        exit 1
    fi
fi

if [[ $ADDRESS_MODEL == host ]]
then
    if [[ $ARCH == i386 ]]
    then
        required_size=4
    elif [[ $ARCH == x86_64 ]]
    then
        required_size=8
    fi

    if [[ $CELL_SIZE != required_size ]]
    then
        echo "With the host address model, the cell size must match the address size." >&2
        echo "For $ARCH, this must be $required_size, not \"$CELL_SIZE\"." >&2
        exit 1
    fi
fi

if [[ $CELL_SIZE == 8 && $ARCH == i386 ]]
then
    echo "The cell size must be no larger than the architecture's address size." >&2
    echo "8 byte cells are incompatible with the i386 architecture. Use 2 or 4 instead." >&2
    exit 1
fi
