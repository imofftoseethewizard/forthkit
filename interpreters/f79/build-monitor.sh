#! /usr/bin/env sh

log_file=$FORTHKIT/build/log

make deps >/dev/null

inotifywait -mr --fromfile deps.txt -e CLOSE_WRITE $FORTHKIT/address $FORTHKIT/execution-models $FORTHKIT/interpreters/f79 | \
    while read dir events file
    do
        echo $dir $events $file >>$log_file
        $FORTHKIT/interpreters/f79/build-all-versions.sh >>$log_file
    done
