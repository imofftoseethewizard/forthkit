#! /usr/bin/env sh

cd $FORTHKIT/interpreters

for family in $FAMILIES
do
    for f in `ls $FORTHKIT/interpreters/$family/spec/*.rc`
    do
        export VARIANT_TAG=$(echo $f | sed -E 's|.*/([^.]*)\.rc$|\1|')
        . $f
        FAMILY=$family make deps >/dev/null 2>&1
    done
done
