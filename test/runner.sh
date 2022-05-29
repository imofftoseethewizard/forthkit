#! /usr/bin/env sh

# The first and only parameter should identify a file which contains the tests,
# one per line, each of which should be a command that is executable in the same
# environment that this script is running in.

# future improvements:
#   3. markdown mode ($1 ~ *.md)
#       a. run lines in code blocks
#       b. everything else is a comment
#   4. ensure failure messages are easy to read
#   5. control over output
#       a. -q/--quiet -> no output only exit code
#       b. -n/--normal (as below)
#       c. -v/--verbose, echo command and stderr from the command
#       d. -d/--debug echo command and stdout, stderr from command
#   7. error message for nothing to do
#   8. error message for file not found/inaccessible
#   9. detect and compensate for missing newline at end of $tests file


n=0                 # number of failures
total=0             # total tests

while [ $# != '0' ]
do
    tests=$1

    while read line
    do

        # skip comments and blank lines
        if echo $line | grep -q -E '^[ ]*(#|$)'
        then
            continue
        fi

        sh -c "$line" >/dev/null 2>&1

        if [ $? != '0' ]
        then
            eval echo FAILED: $line
            n=$((n+1))
        fi

        total=$((total+1))

    done < $tests

    shift
done

if [ $n = 0 ]
then
    echo All $total tests passed.
else
    echo $n out of $total tests failed.
    exit 1
fi
