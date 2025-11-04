WORKSPACE_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)

include $(WORKSPACE_DIR)/mk/common.mk

all: $(NAME)

$(REL_BUILD_DIR)/%.o: CSTD = $(CSTD_LATEST)
$(REL_BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $(REL_BUILD_DIR)/$@)
	$(CC) $(CFLAGS) -MMD -MP -MF $(REL_BUILD_DIR)/$*.d -c $< -o $@

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

##################################

TESTS := $(wildcard tests/*.sh)

test: all $(LIBS) $(TESTS)
	@bash -c '\
		FAIL=0; \
		for t in $(TESTS); do \
			if bash $$t; then \
				echo "$(NAME) test $$t SUCCESS"; \
			else \
				echo "$(NAME) test $$t FAILED"; \
				FAIL=1; \
			fi; \
		done; \
		exit $$FAIL \
	'
##################################

clean:
	$(RM) $(OBJS) $(NAME) $(DEPS)

re: clean all

.PHONY: all test all clean re