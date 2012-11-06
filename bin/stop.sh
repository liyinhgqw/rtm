#!/usr/bin/env bash

# Stop rtm map reduce daemons.  Run this on master node.

bin=`dirname "$0"`
bin=`cd "$bin"; pwd`

. "$bin/rtm-config.sh"

"$bin"/rtm-daemon.sh --config $RTM_CONF_DIR stop timeserver 
"$bin"/rtm-daemons.sh --config $RTM_CONF_DIR stop rtmserver 

