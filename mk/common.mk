WORKSPACE_DIR = $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)

CVER ?=99
CFLAGS ?= -std=c$(CVER) -pedantic 					\
	-Wno-newline-eof							\
	-I$(WORKSPACE_DIR)/third-party/libstc		\
	-I$(WORKSPACE_DIR)/third-party/libsugar 	\
	-I$(WORKSPACE_DIR)/third-party/libbtp		\
	-I$(WORKSPACE_DIR)/include

DEBUG ?= 0

ifeq ($(DEBUG), 1) 
	CFLAGS = $(CFLAGS) -g	-fsanitize=leak
endif


LDFLAGS ?=
CC ?= clang


AR ?= ar -rcs
RM ?= rm -f


rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))


SRCS ?= $(call rwildcard,./,*.c)
HDRS ?= $(call rwildcard,./,*.h)
OBJS ?= $(SRCS:.c=.o)

define EOL



endef