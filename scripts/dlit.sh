#! /bin/sh

sed -E '/^ {0,3}[^ ]/d' $1 \
    | sed -E 's/^    //'
