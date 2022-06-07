#! /usr/bin/env sh

export FAMILY=$1
export VERSION_TAG=$2
. $FORTHKIT/interpreters/$FAMILY/spec/$VERSION_TAG.rc
cd $FORTHKIT/interpreters/$FAMILY/
make all
