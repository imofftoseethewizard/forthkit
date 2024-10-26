#! /usr/bin/env bash

docker rmi -f fk-test || true

docker build \
    --build-arg USERNAME=$(whoami) \
    --build-arg USER_UID=$(id -u) \
    --build-arg USER_GID=$(id -g) \
    --build-arg USER_HOME=$HOME \
    -t fk-test \
    $(dirname $0)
