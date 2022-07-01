#! /usr/bin/env sh

inotifywait -mr --exclude 'log|.*\.[cho]$' -e CLOSE_WRITE $FORTHKIT/build | \
    while read dir events file
    do
        if [ $file = 'bootstrap-interpreter' ]
        then
            version_tag=$(echo $dir | sed -E 's|.*/([^/]+)/bin/|\1|')

            export FAMILY=$(echo $dir | sed -E "s|.*/([^/]*)/$version_tag/bin/|\1|")

            log_file=$FORTHKIT/log/test/$FAMILY/$version_tag

            mkdir -p $FORTHKIT/log/test/$FAMILY

            VERSION_TAG=$version_tag $FORTHKIT/scripts/runner.sh $FORTHKIT/test/common/*.rc $FORTHKIT/test/$FAMILY/*.rc >>$log_file
        fi
    done
