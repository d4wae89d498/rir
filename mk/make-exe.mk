WORKSPACE_DIR = $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)

all: $(NAME)

include $(WORKSPACE_DIR)/mk/common.mk

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: CSTD = $(CSTD_LATEST)
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

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
	$(RM) $(OBJS) $(NAME)

re: clean all

.PHONY: all test all clean re