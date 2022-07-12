#! /usr/bin/env sh

cd $FORTHKIT/interpreters

export FAMILIES='f79 f83 f94'

mkdir -p $FORTHKIT/log
touch $FORTHKIT/log/build

log_file=$FORTHKIT/log/build

$FORTHKIT/scripts/update-all-deps.sh

find $FORTHKIT/build -name deps.txt -exec cat {} \; | \
    sort -u | \
    tee $FORTHKIT/build/build-monitor-watching.txt | \
    inotifywait -mr --fromfile - -e CLOSE_WRITE | \
    while read dir events file
    do
        echo $dir $events $file >>$log_file
        $FORTHKIT/scripts/build-all-versions.sh >>$log_file
    done
