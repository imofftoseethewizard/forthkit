#! /usr/bin/env sh

$FORTHKIT/scripts/build-monitor.sh >/dev/null 2>&1 &
$FORTHKIT/scripts/test-monitor.sh  >/dev/null 2>&1 &

tail -f -n 0 `find $FORTHKIT/log -type f`
