#! /usr/bin/env sh

export FAMILY=f79

mkdir -p $FORTHKIT/log
touch $FORTHKIT/log/build

log_file=$FORTHKIT/log/build

make deps >/dev/null

inotifywait -mr --fromfile $FORTHKIT/build/$FAMILY/deps.txt -e CLOSE_WRITE $FORTHKIT/address $FORTHKIT/execution-models $FORTHKIT/interpreters | \
    while read dir events file
    do
        echo $dir $events $file >>$log_file
        $FORTHKIT/interpreters/build-all-versions.sh >>$log_file
    done
