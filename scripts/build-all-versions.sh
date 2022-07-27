#! /usr/bin/env sh

cd $FORTHKIT/interpreters

for family in f94 # $FAMILIES
do
    for f in `ls $FORTHKIT/interpreters/$family/spec/gcc-rel-switch-a32-c4.rc`
    do
        export VERSION_TAG=$(echo $f | sed -E 's|.*/([^.]*)\.rc$|\1|')
        . $f
        FAMILY=$family make deps all 2>&1 | egrep ': error: '

        if [ $? = '0' ]
        then
            echo `date "+%Y-%m-%dT%H:%M:%SZ" -u` Build of $family  version $VERSION_TAG failed.
        else
            echo `date "+%Y-%m-%dT%H:%M:%SZ" -u` Built $family version $VERSION_TAG successfully.
        fi
    done
done
