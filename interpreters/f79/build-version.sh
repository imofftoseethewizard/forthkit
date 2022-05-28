#! /usr/bin/env sh

export VERSION_TAG=$1
. $FORTHKIT/interpreters/f79/spec/$VERSION_TAG.rc
cd $FORTHKIT/interpreters/f79/
make all
