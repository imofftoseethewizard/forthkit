#! /usr/bin/env sh

mkdir -p $FORTHKIT/test/log

inotifywait -mr --exclude '.*\.[cho]$' -e CLOSE_WRITE $FORTHKIT/build | \
    while read dir events file
    do
        version_tag=$(echo $dir | sed -E 's|.*/([^/]*)/bin/|\1|')
        log_file=$FORTHKIT/test/log/$version_tag

        date -Iseconds -u >>$log_file
        VERSION_TAG=$version_tag ./runner.sh f79/core.rc >>$log_file
    done
