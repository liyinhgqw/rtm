#!/usr/bin/env bash

# Run a Rtm command on all slave hosts.

usage="Usage: rtm-daemons.sh [--config confdir] [--hosts hostlistfile] [start|stop] command args..."

# if no args specified, show usage
if [ $# -le 1 ]; then
  echo $usage
  exit 1
fi

bin=`dirname "$0"`
bin=`cd "$bin"; pwd`

. "$bin/rtm-config.sh"

exec "$bin/servers.sh" --config $RTM_CONF_DIR cd "$RTM_HOME" \; "$bin/rtm-daemon.sh" --config $RTM_CONF_DIR "$@"
