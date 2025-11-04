WORKSPACE_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)

BUILD_DIR = $(WORKSPACE_DIR)/build

REL_DIR := $(patsubst $(WORKSPACE_DIR)/%,%,$(CURDIR))
REL_BUILD_DIR = $(WORKSPACE_DIR)/build/$(REL_DIR)

CSTD_LATEST = c23

CC = clang #?= clang
CSTD ?= $(CSTD_LATEST)
TRACE ?= 0
DEBUG ?= 0

CFLAGS ?= -std=$(CSTD) -pedantic 					\
	-Wno-newline-eof								\
	-Wno-unused										\
	-Wno-format-security							\
	-Wno-empty-translation-unit						\
	-I$(WORKSPACE_DIR)/include						\
	-I$(WORKSPACE_DIR)/third-party/libstc/include	\
	-I$(WORKSPACE_DIR)/third-party/libsugar 		\
	-I$(WORKSPACE_DIR)/third-party/libdiag 			\
	-I$(WORKSPACE_DIR)/third-party/libbpc			\
	-I$(WORKSPACE_DIR)/third-party/libstcutils		\
	-DTRACE=$(TRACE)								\
	-DDEBUG=1										\
	-DWS_DIR=$(WORKSPACE_DIR)						\
	-DNAME=$<
# Wno-format-security: todo check why needed why fmt_printd 
ifeq ($(DEBUG), 1) 
	CFLAGS += -g	-fsanitize=address
endif

LIBS ?= $(WORKSPACE_DIR)/third-party/libstc/build/Linux_clang/libstc.a 	\
	 $(BUILD_DIR)/third-party/libdiag/libdiag.a 						\
																		\
	 $(BUILD_DIR)/rir-backend/librir-backend.a 							\
	 $(BUILD_DIR)/rir-ir/librir-ir.a 									\
	 $(BUILD_DIR)/rir-parser/librir-parser.a 							\

$(WORKSPACE_DIR)/third-party/libstc/build/Linux_clang/libstc.a:
	make -C $(WORKSPACE_DIR)/third-party/libstc

ifneq ($(NAME),libdiag.a)
$(BUILD_DIR)/third-party/libdiag/libdiag.a:
	make -C $(WORKSPACE_DIR)/third-party/libdiag
endif

ifneq ($(NAME),librir-backend.a)
$(BUILD_DIR)/rir-backend/librir-backend.a:
	make -C $(WORKSPACE_DIR)/rir-backend
endif

ifneq ($(NAME),librir-ir.a)
$(BUILD_DIR)/rir-ir/librir-ir.a:
	make -C $(WORKSPACE_DIR)/rir-ir
endif

ifneq ($(NAME),librir-parser.a)
$(BUILD_DIR)/rir-parser/librir-parser.a:
	make -C $(WORKSPACE_DIR)/rir-parser
endif
LDFLAGS ?= $(LIBS)

AR ?= ar
RM ?= rm -f


rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))


SRCS ?= $(call rwildcard,./,*.c)

OBJS ?= $(patsubst ./%.c,$(REL_BUILD_DIR)/%.o,$(SRCS))
DEPS ?= $(patsubst ./%.c,$(REL_BUILD_DIR)/%.d,$(SRCS))


NAME := $(REL_BUILD_DIR)/$(NAME)

.DEFAULT_GOAL := all

-include $(DEPS)

define EOL



endef