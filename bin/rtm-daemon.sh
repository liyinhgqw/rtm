#!/usr/bin/env bash

# Runs a Rtm command as a daemon.
#
# Environment Variables
#
#   RTM_CONF_DIR  Alternate conf dir. Default is ${RTM_PREFIX}/conf.
#   RTM_LOG_DIR   Where log files are stored.  PWD by default.
#   RTM_PID_DIR   The pid files are stored. /tmp by default.
#   RTM_IDENT_STRING   A string representing this instance of rtm. $USER by default
##

usage="Usage: rtm-daemon.sh [--config <conf-dir>] [--hosts hostlistfile] (start|stop) <rtm-command> <args...>"

# if no args specified, show usage
if [ $# -le 1 ]; then
  echo $usage
  exit 1
fi

bin=`dirname "$0"`
bin=`cd "$bin"; pwd`

. "$bin/rtm-config.sh"

# get arguments
startStop=$1
shift
command=$1
shift

rtm_rotate_log ()
{
    log=$1;
    num=5;
    if [ -n "$2" ]; then
	num=$2
    fi
    if [ -f "$log" ]; then # rotate logs
	while [ $num -gt 1 ]; do
	    prev=`expr $num - 1`
	    [ -f "$log.$prev" ] && mv "$log.$prev" "$log.$num"
	    num=$prev
	done
	mv "$log" "$log.$num";
    fi
}

if [ -f "${RTM_CONF_DIR}/rtm-env.sh" ]; then
  . "${RTM_CONF_DIR}/rtm-env.sh"
fi

if [ "$RTM_IDENT_STRING" = "" ]; then
  export RTM_IDENT_STRING="$USER"
fi

# get log directory
if [ "$RTM_LOG_DIR" = "" ]; then
  export RTM_LOG_DIR="$RTM_HOME/logs"
fi
mkdir -p "$RTM_LOG_DIR"
touch $RTM_LOG_DIR/.rtm_test > /dev/null 2>&1
TEST_LOG_DIR=$?
if [ "${TEST_LOG_DIR}" = "0" ]; then
  rm -f $RTM_LOG_DIR/.rtm_test
else
  chown $RTM_IDENT_STRING $RTM_LOG_DIR 
fi

if [ "$RTM_PID_DIR" = "" ]; then
  RTM_PID_DIR=/tmp
fi

# some variables
export RTM_LOGFILE=rtm-$RTM_IDENT_STRING-$command-$HOSTNAME.log
export RTM_ROOT_LOGGER="INFO,DRFA"
log=$RTM_LOG_DIR/rtm-$RTM_IDENT_STRING-$command-$HOSTNAME.out
pid=$RTM_PID_DIR/rtm-$RTM_IDENT_STRING-$command.pid

case $startStop in

  (start)

    mkdir -p "$RTM_PID_DIR"

    if [ -f $pid ]; then
      if kill -0 `cat $pid` > /dev/null 2>&1; then
        echo $command running as process `cat $pid`.  Stop it first.
        exit 1
      fi
    fi

    rtm_rotate_log $log
    echo starting $command, logging to $log
    cd "$RTM_PREFIX"
    nohup "$RTM_PREFIX"/bin/rtm --config $RTM_CONF_DIR $command "$@" > "$log" 2>&1 < /dev/null &
    echo $! > $pid
    sleep 1; head -200 "$log"
    ;;
          
  (stop)

    if [ -f $pid ]; then
      if kill -0 `cat $pid` > /dev/null 2>&1; then
        echo stopping $command
        kill `cat $pid`
      else
        echo no $command to stop
      fi
      # kill the run_forever_servers
      killall $command > /dev/null 2>&1
    else
      echo no $command to stop
    fi
    ;;

  (*)
    echo $usage
    exit 1
    ;;

esac


