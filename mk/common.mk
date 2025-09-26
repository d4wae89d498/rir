WORKSPACE_DIR = $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)

CSTD ?=c99
CFLAGS ?= -std=$(CSTD) -pedantic 				\
	-Wno-newline-eof							\
	-Wno-unused									\
	-I$(WORKSPACE_DIR)/third-party/STC/include	\
	-I$(WORKSPACE_DIR)/third-party/libsugar 	\
	-I$(WORKSPACE_DIR)/third-party/libbtp		\
	-I$(WORKSPACE_DIR)/include					\

#-Di_static=1								\
	-DSTC_HAS_TYPEOF=0				\
\
	-DSTC_CSTR_UTF8=0							\
	-DSTC_CSTR_IO=0								\
	-DFMT_H_INCLUDED=1	

DEBUG ?= 0

ifeq ($(DEBUG), 1) 
	CFLAGS = $(CFLAGS) -g	-fsanitize=leak
endif


LDFLAGS ?=
CC ?= clang


AR ?= ar
RM ?= rm -f


rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))


SRCS ?= $(call rwildcard,./,*.c)
HDRS ?= $(call rwildcard,./,*.h)
OBJS ?= $(SRCS:.c=.o)

define EOL



endef