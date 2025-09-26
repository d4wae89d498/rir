WORKSPACE_DIR = $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)

include $(WORKSPACE_DIR)/mk/common.mk

all: $(NAME)

$(WORKSPACE_DIR)/third-party/libstc/build/Linux_gcc/libstc.a:
	make -C $(WORKSPACE_DIR)/third-party/libstc

$(WORKSPACE_DIR)/rir-backend/librir-backend.a:
	make -C $(WORKSPACE_DIR)/rir-backend

$(NAME): $(OBJS)\
$(WORKSPACE_DIR)/third-party/libstc/build/Linux_gcc/libstc.a\
$(WORKSPACE_DIR)/rir-backend/librir-backend.a
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

##################################

TESTS := $(wildcard tests/*.sh)

test: all $(TESTS)
	@FAIL=0; \
	for t in $(TESTS); do \
		if bash $$t; then \
			echo "$(NAME) test $$t SUCCESS"; \
		else \
			echo "$(NAME) test $$t FAILED"; \
			FAIL=1; \
		fi; \
	done; \
	exit $$FAIL

##################################

clean:
	$(RM) $(OBJS) $(NAME)

re: clean all

.PHONY: all test all clean re