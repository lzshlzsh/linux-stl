stl_root ?= ..
inc_path := $(stl_root)/include

CC := gcc
CXX := g++
CFLAGS := -Wall -g 
LDFLAGS := #-ldl -lpthread #-static

CFLAGS += $(addprefix -I,$(inc_path))

CXXFLAGS := ${CFLAGS}

FILES := $(wildcard *.c)
TARGETS := $(patsubst %.c, %, ${FILES})
FILES := $(wildcard *.cpp)
TARGETS += $(patsubst %.cpp, %, ${FILES})

.PHONY: all clean

all: ${TARGETS}

clean:
	${RM} ${TARGETS}


% : %.cpp
	$(CXX) ${CXXFLAGS} -o $@ $^ ${LDFLAGS}
% : %.c
	$(CC) ${CFLAGS} -o $@ $^ ${LDFLAGS}
