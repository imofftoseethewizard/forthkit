#! /usr/bin/env sh

mkdir -p $FORTHKIT/log
touch $FORTHKIT/log/build

log_file=$FORTHKIT/log/build

make deps >/dev/null

inotifywait -mr --fromfile deps.txt -e CLOSE_WRITE $FORTHKIT/address $FORTHKIT/execution-models $FORTHKIT/interpreters/f79 | \
    while read dir events file
    do
        echo $dir $events $file >>$log_file
        $FORTHKIT/interpreters/f79/build-all-versions.sh >>$log_file
    done
