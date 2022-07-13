#! /usr/bin/env sh

(ps -o pid,comm| egrep '(notifywait|monitor|sh|tail)$' | awk '{print $1}' | grep -v $$ | xargs kill)  >/dev/null 2>&1
(find $FORTHKIT/build -name "deps.txt" | xargs rm) >/dev/null 2>&1
($FORTHKIT/scripts/update-all-deps.sh) >/dev/null 2>&1
