#! /usr/bin/env sh

export VERSION_TAG=$1
export FAMILY=f79
. $FORTHKIT/interpreters/$FAMILY/spec/$VERSION_TAG.rc
cd $FORTHKIT/interpreters/$FAMILY/
make all
