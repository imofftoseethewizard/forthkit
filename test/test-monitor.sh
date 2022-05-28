#! /usr/bin/env sh

mkdir -p $FORTHKIT/test/log

inotifywait -mr --exclude 'log|.*\.[cho]$' -e CLOSE_WRITE $FORTHKIT/build | \
    while read dir events file
    do
        version_tag=$(echo $dir | sed -E 's|.*/([^/]*)/bin/|\1|')
        log_file=$FORTHKIT/test/log/$version_tag

        echo -n `date "+%Y-%m-%dT%H:%M:%SZ" -u` "" >>$log_file
        VERSION_TAG=$version_tag ./runner.sh $FORTHKIT/test/f79/core.rc >>$log_file
    done
