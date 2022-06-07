#! /usr/bin/env sh

cd $FORTHKIT/interpreters

for family in $FAMILIES
do
    for f in `ls $FORTHKIT/interpreters/$family/spec/*.rc`
    do
        export VERSION_TAG=$(echo $f | sed -E 's|.*/([^.]*)\.rc$|\1|')
        . $f
        FAMILY=$family make deps all >/dev/null 2>&1

        if [ $? = '0' ]
        then
            echo `date "+%Y-%m-%dT%H:%M:%SZ" -u` Built $family version $VERSION_TAG successfully.
        else
            echo `date "+%Y-%m-%dT%H:%M:%SZ" -u` Build of $family  version $VERSION_TAG failed.
        fi
    done
done
