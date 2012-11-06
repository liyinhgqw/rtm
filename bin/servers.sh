#!/usr/bin/env bash

# Run a shell command on all server hosts.
#
# Environment Variables
#
#   RTM_SERVERS    File naming remote hosts.
#     Default is ${RTM_CONF_DIR}/servers.
#   RTM_CONF_DIR  Alternate conf dir. Default is ${RTM_HOME}/conf.
#   RTM_SLAVE_SLEEP Seconds to sleep between spawning remote commands.
#   RTM_SSH_OPTS Options passed to ssh when running remote commands.
##

usage="Usage: servers.sh [--config confdir] command..."

# if no args specified, show usage
if [ $# -le 0 ]; then
  echo $usage
  exit 1
fi

bin=`dirname "$0"`
bin=`cd "$bin"; pwd`

. "$bin/rtm-config.sh"

# If the servers file is specified in the command line,
# then it takes precedence over the definition in 
# rtm-env.sh. Save it here.
HOSTLIST=$RTM_SERVERS

if [ -f "${RTM_CONF_DIR}/rtm-env.sh" ]; then
  . "${RTM_CONF_DIR}/rtm-env.sh"
fi

if [ "$HOSTLIST" = "" ]; then
  if [ "$RTM_SERVERS" = "" ]; then
    export HOSTLIST="${RTM_CONF_DIR}/servers"
  else
    export HOSTLIST="${RTM_SERVERS}"
  fi
fi

for server in `cat "$HOSTLIST"|sed  "s/#.*$//;/^$/d"`; do
 ssh $RTM_SSH_OPTS $server $"${@// /\\ }" \
   2>&1 | sed "s/^/$server: /" &
 if [ "$RTM_SLAVE_SLEEP" != "" ]; then
   sleep $RTM_SLAVE_SLEEP
 fi
done

wait
