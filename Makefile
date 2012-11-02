.SECONDEXPANSION:
.PHONY: all clean
.DELETE_ON_ERROR:
.PROCIOUS: %/.dir_timestamp

SRCDIR := src
O := build

CXX := g++

# TODO: add my own build libs
LIBS := $O/libutil.a $O/librpc.a

LDFLAGS := \
  -L$O\
  -Wl,--start-group\
  ${LIBS} \
  -Wl,--end-group\
  -lrt -lprotobuf -lpthread
  # TODO: add extenal libs
  
  
CPPFLAGS := -Isrc -I$O

CXXFLAGS := -Wall -Wextra -Wno-unused-parameter -O0 -g2 -std=c++0x -fPIC -fno-omit-frame-pointer
 
VPATH = ${SRCDIR}

# TODO: mod target
all: $O/examples/example	## generate example using tools

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

# TODO: mod target
$O/examples/example : $O/examples/example.o ${LIBS}
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o $@ $(filter %.o,$^) ${LDFLAGS}
	