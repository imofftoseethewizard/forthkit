#! /usr/bin/env sh

inotifywait -mr --exclude 'log|.*\.[cho]$' -e CLOSE_WRITE $FORTHKIT/build/f83/gcc-abs-thr-a32-c4-l1 | \
    while read dir events file
    do
        if [ $file = 'interpreter' ] || [ $file = 'bootstrap-interpreter' ]
        then
            version_tag=$(echo $dir | sed -E 's|.*/([^/]+)/bin/|\1|')

            export FAMILY=$(echo $dir | sed -E "s|.*/([^/]*)/$version_tag/bin/|\1|")
            export INTERPRETER=$file
            export VERSION_TAG=$version_tag

            log_file=$FORTHKIT/log/test/$FAMILY/$version_tag

            mkdir -p $FORTHKIT/log/test/$FAMILY

            $FORTHKIT/scripts/runner.sh >>$log_file  \
                $FORTHKIT/test/common/*.rc           \
                $FORTHKIT/test/$FAMILY/*.rc          \
                $FORTHKIT/test/common/$file/*.rc     \
                $FORTHKIT/test/$FAMILY/$file/*.rc

        fi
    done
