#!/usr/bin/env bash

# Start timeserver and rtmservers daemons. 

bin=`dirname "$0"`
bin=`cd "$bin"; pwd`

. "$bin/rtm-config.sh"

# start rtm daemons
# start timeserver first to accept time sync from rtmservers
"$bin"/rtm-daemon.sh --config $RTM_CONF_DIR start client 
