#! /usr/bin/env sh

inotifywait -mr --exclude 'log|.*\.[cho]$' -e CLOSE_WRITE $FORTHKIT/build | \
    while read dir events file
    do
        if echo $dir | grep /bin/ >/dev/null
        then
            version_tag=$(echo $dir | sed -E 's|.*/([^/]+)/bin/|\1|')

            family=$(echo $dir | sed -E "s|.*/([^/]*)/$version_tag/bin/|\1|")

            log_file=$FORTHKIT/log/test/$family/$version_tag

            mkdir -p $FORTHKIT/log/test/$family

            VERSION_TAG=$version_tag ./runner.sh $FORTHKIT/test/$family/core.rc $FORTHKIT/test/$family/fiber.rc >>$log_file
        fi
    done
