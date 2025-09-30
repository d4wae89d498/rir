WORKSPACE_DIR = $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)
CSTD_LATEST = c23

CC = clang #?= clang
CSTD ?= $(CSTD_LATEST)

CFLAGS ?= -std=$(CSTD) -pedantic 					\
	-Wno-newline-eof								\
	-Wno-unused										\
	-Wno-format-security							\
	-I$(WORKSPACE_DIR)/include						\
	-I$(WORKSPACE_DIR)/third-party/libsugar 		\
	-I$(WORKSPACE_DIR)/third-party/libbtp			\
	-I$(WORKSPACE_DIR)/third-party/libstc/include

# Wno-format-security: todo check why needed why fmt_printd 

#-Di_static=1										\
	-DSTC_HAS_TYPEOF=0								\
													\
	-DSTC_CSTR_UTF8=0								\
	-DSTC_CSTR_IO=0									\
	-DFMT_H_INCLUDED=1	

DEBUG ?= 0
ifeq ($(DEBUG), 1) 
	CFLAGS += -g	-fsanitize=leak
endif

LIBS ?= $(WORKSPACE_DIR)/third-party/libstc/build/Linux_clang/libstc.a 		\
	 $(WORKSPACE_DIR)/rir-backend/librir-backend.a 							\
	 $(WORKSPACE_DIR)/rir-backend/librir-backend.a 

$(WORKSPACE_DIR)/third-party/libstc/build/Linux_clang/libstc.a:
	make -C $(WORKSPACE_DIR)/third-party/libstc

$(WORKSPACE_DIR)/rir-ir/librir-ir.a:
	make -C $(WORKSPACE_DIR)/rir-ir

$(WORKSPACE_DIR)/rir-backend/librir-backend.a:
	make -C $(WORKSPACE_DIR)/rir-backend

LDFLAGS ?= $(LIBS)

AR ?= ar
RM ?= rm -f


rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))


SRCS ?= $(call rwildcard,./,*.c)
HDRS ?= $(call rwildcard,./,*.h)
OBJS ?= $(SRCS:.c=.o)

define EOL



endef