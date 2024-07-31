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

docker run -it -d \
--name monitor \
-e DISPLAY=$display \
--privileged=true \
-e DOCKER_USER="${user}" \
-e USER="${user}" \
-e DOCKER_USER_ID="${uid}" \
-e DOCKER_GRP="${group}" \
-e DOCKER_GRP_ID="${gid}" \
-e XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR \
-v ${MONITOR_HOME_DIR}:/work \
-v ${XDG_RUNTIME_DIR}:${XDG_RUNTIME_DIR} \
--net host \
monitor