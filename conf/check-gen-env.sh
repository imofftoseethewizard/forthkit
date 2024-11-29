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

if [[ -z $ADDRESS_MODEL ]]
then
    echo "ADDRESS_MODEL is unset or empty." >&2
    exit 1
elif [[ ! $ADDRESS_MODEL =~ ^(host|virtual)$ ]]
then
    echo "ADDRESS_MODEL must be one of \"host\" or \"virtual\", not \"$ADDRESS_MODEL\"." >&2
    exit 1
fi

if [[ -z $CONCURRENCY_MODEL ]]
then
    echo "CONCURRENCY_MODEL is unset or empty." >&2
    exit 1
elif [[ ! $CONCURRENCY_MODEL =~ ^(fibered|single)$ ]]
then
    echo "CONCURRENCY_MODEL must be one of \"fibered\" or \"single\", not \"$CONCURRENCY_MODEL\"." >&2
    exit 1
fi

if [[ -z $EXECUTION_MODEL ]]
then
    echo "EXECUTION_MODEL is unset or empty." >&2
    exit 1
elif [[ ! $EXECUTION_MODEL =~ ^(computed-goto|local-subroutine|switch)$ ]]
then
    echo "EXECUTION_MODEL must be one of \"computed-goto\", \"local-subroutine\"" >&2
    echo "or \"switch\", not \"$EXECUTION_MODEL\"." >&2
    exit 1
fi

if [[ -z $FAMILY ]]
then
    echo "FAMILY is unset or empty." >&2
    exit 1
elif [[ ! $FAMILY =~ ^(f79|f83|f94)$ ]]
then
    echo "FAMILY must be one of \"f79\", \"f83\" or \"f94\", not \"$FAMILY\"." >&2
    exit 1
fi

if [[ -z $THREAD_MODEL ]]
then
    echo "THREAD_MODEL is unset or empty." >&2
    exit 1
elif [[ ! $THREAD_MODEL =~ ^(direct|indirect)$ ]]
then
    echo "THREAD_MODEL must be one of \"direct\" or \"indirect\", not \"$THREAD_MODEL\"." >&2
    exit 1
fi
