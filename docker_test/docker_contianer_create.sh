#!/usr/bin/env bash

MONITOR_HOME_DIR="$( cd "$( dirname "$0" )/.." && pwd )"
echo MONITOR_HOME_DIR: $MONITOR_HOME_DIR

display=""
if [ -z ${DISPLAY} ];then
    display=":1"
else
    display="${DISPLAY}"
fi

user="${USER}"
uid="$(id -u)"
group="$(id -g -n)"
gid="$(id -g)"

echo "create docker"
echo display: $display

docker run -it -d \
--name monitor_test \
--env=unix$DISPLAY \
--privileged=true \
--net host \
-v ${MONITOR_HOME_DIR}:/work \
-v /tmp/.X11-unix:/tmp/.X11-unix \
monitor

# docker run -it -d \
# --name monitor_test \
# -e DISPLAY=$display \
# -e XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR \
# -v ${MONITOR_HOME_DIR}:/work \
# -v ${XDG_RUNTIME_DIR}:${XDG_RUNTIME_DIR} \
# -v /tmp/.X11-unix:/tmp/.X11-unix \
# --net host \
# monitor
