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

if [[ -z $FK_ADDRESS_MODEL ]]
then
    echo "FK_ADDRESS_MODEL is unset or empty." >&2
    exit 1
elif [[ ! $FK_ADDRESS_MODEL =~ ^(host|virtual)$ ]]
then
    echo "FK_ADDRESS_MODEL must be one of \"host\" or \"virtual\", not $FK_ADDRESS_MODEL." >&2
    exit 1
fi

if [[ -z $FK_CONCURRENCY ]]
then
    echo "FK_CONCURRENCY is unset or empty." >&2
    exit 1
elif [[ ! $FK_CONCURRENCY =~ ^(fibered|single)$ ]]
then
    echo "FK_CONCURRENCY must be one of \"fibered\" or \"single\", not $FK_CONCURRENCY." >&2
    exit 1
fi

if [[ -z $FK_EXECUTION_MODEL ]]
then
    echo "FK_EXECUTION_MODEL is unset or empty." >&2
    exit 1
elif [[ ! $FK_EXECUTION_MODEL =~ ^(computed_goto|local_subroutine|switch)$ ]]
then
    echo "FK_EXECUTION_MODEL must be one of \"computed_goto\", \"local_subroutine\"" >&2
    echo "or \"switch\", not $FK_EXECUTION_MODEL." >&2
    exit 1
fi

if [[ -z $FK_FAMILY ]]
then
    echo "FK_FAMILY is unset or empty." >&2
    exit 1
elif [[ ! $FK_FAMILY =~ ^(f79|f83|f94)$ ]]
then
    echo "FK_FAMILY must be one of \"f79\", \"f83\" or \"f94\", not $FK_FAMILY." >&2
    exit 1
fi

if [[ -z $FK_THREAD_MODEL ]]
then
    echo "FK_THREAD_MODEL is unset or empty." >&2
    exit 1
elif [[ ! $FK_THREAD_MODEL =~ ^(direct|indirect)$ ]]
then
    echo "FK_THREAD_MODEL must be one of \"direct\" or \"indirect\", not $FK_THREAD_MODEL." >&2
    exit 1
fi
