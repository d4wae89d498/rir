WORKSPACE_DIR = $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)

include $(WORKSPACE_DIR)/mk/common.mk

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

##################################

TESTS := $(wildcard tests/*.sh)

test: $(TESTS)
	@for t in $(TESTS); do \
		if bash $$t; then \
			echo "$(NAME) test $$t SUCCESS"; \
		else \
			echo "$(NAME) test $$t FAILED"; \
		fi \
	done

##################################

clean:
	$(RM) $(OBJS) $(NAME)

re: clean all

.PHONY: all test all clean re