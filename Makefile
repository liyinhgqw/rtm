.SECONDEXPANSION:
.PHONY: all clean
.DELETE_ON_ERROR:
.PROCIOUS: %/.dir_timestamp

SRCDIR := src
O := build

CXX := g++

# TODO: add my own build libs
LIBS := $O/libutil.a $O/librpc.a $O/libexamples.a $O/libtime.a

LDFLAGS := \
  -L$O\
  -Wl,--start-group\
  ${LIBS} \
  -Wl,--end-group\
  -lrt -lprotobuf -lpthread -lboost_thread
  # TODO: add extenal libs
  
  
CPPFLAGS := -Isrc -I$O

CXXFLAGS := -Wall -Wextra -Wno-unused-parameter -O0 -g2 -std=c++0x -fPIC -fno-omit-frame-pointer
 
VPATH = ${SRCDIR}

# TODO: mod target
all: $O/examples/kvserver $O/examples/kvclient	## generate example using tools

%/.dir_timestamp:
	mkdir -p $(dir $@)
	touch $@

$O/%.o : %.cc $$(@D)/.dir_timestamp
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -o $@ $<

clean:
	rm -rf $O

# TODO: mod path/to/libname in $SRCS
SRCS := $(wildcard src/util/*.cc)
OBJS_RAW := $(patsubst %.cc,%.o,${SRCS})
OBJS := $(subst src,build,${OBJS_RAW})
$O/libutil.a : ${OBJS}
	ar rcs -o $@ $^
	
SRCS := $(wildcard src/rpc/*.cc)
OBJS_RAW := $(patsubst %.cc,%.o,${SRCS})
OBJS := $(subst src,build,${OBJS_RAW})
$O/librpc.a : ${OBJS}
	ar rcs -o $@ $^
	
SRCS := $(wildcard src/time/*.cc)
OBJS_RAW := $(patsubst %.cc,%.o,${SRCS})
OBJS := $(subst src,build,${OBJS_RAW})
$O/libtime.a : ${OBJS}
	ar rcs -o $@ $^
	
SRCS := $(wildcard src/examples/*.cc)
OBJS_RAW := $(patsubst %.cc,%.o,${SRCS})
OBJS := $(subst src,build,${OBJS_RAW})
$O/libexamples.a : ${OBJS}
	ar rcs -o $@ $^

# TODO: mod target
$O/examples/kvserver : $O/examples/kvserver.o ${LIBS}
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o $@ $(filter %.o,$^) ${LDFLAGS}
$O/examples/kvclient : $O/examples/kvclient.o ${LIBS}
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o $@ $(filter %.o,$^) ${LDFLAGS}
	