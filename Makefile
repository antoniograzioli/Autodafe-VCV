RACK_DIR ?= ../..


SOURCES = $(wildcard src/*.cpp)   $(wildcard src/*.c)

LDFLAGS += -Lsrc/stk/src -lstk

LDFLAGS += -Lsrc/Gamma/build/lib -lGamma


DISTRIBUTABLES += $(wildcard LICENSE*) res
# Must include the VCV plugin Makefile framework
include $(RACK_DIR)/plugin.mk

