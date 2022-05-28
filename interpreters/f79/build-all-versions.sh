#! /usr/bin/env sh

for f in `ls $FORTHKIT/interpreters/f79/spec/*.rc`
do
    export VERSION_TAG=$(echo $f | sed -E 's|.*/([^.]*)\.rc$|\1|')
    . $f
    make all >/dev/null 2>&1

    if [ $? = '0' ]
    then
        echo `date "+%Y-%m-%dT%H:%M:%SZ" -u` Built version $VERSION_TAG successfully.
    else
        echo `date "+%Y-%m-%dT%H:%M:%SZ" -u` Build of version $VERSION_TAG failed.
    fi
done