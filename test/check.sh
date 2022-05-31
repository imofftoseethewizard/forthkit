#! /usr/bin/env sh

# The first argument is the expected output of the command given by the
# remainder of the arguments. If the output does not match then this will emit
# the command's output and exit 1.

# If the command has a non-zero exit status, then this will emit the command's
# output and exit with the same status.

expected_output=$1

shift

actual_output=$("$@")
result_code=$?

if [ $result_code != '0' ]
then
    echo $actual_output
    exit $result_code
fi

if [ $actual_output != $expected_output ]
then
    echo $actual_output
    exit 1
fi
