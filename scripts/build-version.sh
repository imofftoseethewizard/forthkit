#! /usr/bin/env sh

export FAMILY=$1
export VARIANT_TAG=$2
. $FORTHKIT/interpreters/$FAMILY/spec/$VARIANT_TAG.rc
cd $FORTHKIT/interpreters/$FAMILY/
make all
