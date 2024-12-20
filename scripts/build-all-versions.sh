#! /usr/bin/env sh

cd $FORTHKIT/interpreters

for family in $FAMILIES
do
    for f in `ls $FORTHKIT/interpreters/$family/spec/*.rc`
    do
        export VARIANT_TAG=$(echo $f | sed -E 's|.*/([^.]*)\.rc$|\1|')
        . $f
        FAMILY=$family make deps all 2>&1 | egrep ': error: '

        if [ $? = '0' ]
        then
            echo `date "+%Y-%m-%dT%H:%M:%SZ" -u` Build of $family version $VARIANT_TAG failed.
        else
            echo `date "+%Y-%m-%dT%H:%M:%SZ" -u` Built $family version $VARIANT_TAG successfully.
        fi
    done
done
