# included in all the rtm scripts with source command
# should not be executable directly
# also should not be passed any arguments, since we need original $*

# resolve links - $0 may be a softlink

this="${BASH_SOURCE-$0}"
common_bin=$(cd -P -- "$(dirname -- "$this")" && pwd -P)
script="$(basename -- "$this")"
this="$common_bin/$script"

# convert relative path to absolute path
config_bin=`dirname "$this"`
script=`basename "$this"`
config_bin=`cd "$config_bin"; pwd`
this="$config_bin/$script"

# the root of the rtm installation
export RTM_PREFIX=`dirname "$this"`/..
#check to see if the conf dir is given as an optional argument
if [ $# -gt 1 ]
then
    if [ "--config" = "$1" ]
	  then
	      shift
	      confdir=$1
	      shift
	      RTM_CONF_DIR=$confdir
    fi
fi
 
DEFAULT_CONF_DIR="conf"
RTM_CONF_DIR="${RTM_CONF_DIR:-$RTM_PREFIX/$DEFAULT_CONF_DIR}"

#check to see it is specified whether to use the servers or the
# timeserver file
if [ $# -gt 1 ]
then
    if [ "--hosts" = "$1" ]
    then
        shift
        serversfile=$1
        shift
        export RTM_SERVERS="${RTM_CONF_DIR}/$serversfile"
    fi
fi

if [ -f "${RTM_CONF_DIR}/rtm-env.sh" ]; then
  . "${RTM_CONF_DIR}/rtm-env.sh"
fi

if [ "$RTM_HOME_WARN_SUPPRESS" = "" ] && [ "$RTM_HOME" != "" ]; then
  echo "Warning: \$RTM_HOME is deprecated." 1>&2
  echo 1>&2
fi

export RTM_HOME=${RTM_PREFIX}
export RTM_HOME_WARN_SUPPRESS=1

