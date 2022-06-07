#! /usr/bin/env sh

export FAMILIES='f79 f83'

mkdir -p $FORTHKIT/log
touch $FORTHKIT/log/build

log_file=$FORTHKIT/log/build

$FORTHKIT/interpreters/update-all-deps.sh

find $FORTHKIT -name deps.txt -exec cat {} \; | \
    sort -u | \
    tee $FORTHKIT/build/build-monitor-watching.txt | \
    inotifywait -mr --fromfile - -e CLOSE_WRITE | \
    while read dir events file
    do
        echo $dir $events $file >>$log_file
        $FORTHKIT/interpreters/build-all-versions.sh >>$log_file
    done
