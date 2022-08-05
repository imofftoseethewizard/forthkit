#! /bin/sh

sed -Ez 's/(\n *)+\n/\n\n/g' $1 \
    | sed -Ez 's/^( *(\n *)*)//g'
