WORKSPACE_DIR = $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)

include $(WORKSPACE_DIR)/mk/common.mk

all: $(NAME)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) -rcs $(NAME)  $(OBJS) 

##################################

FORCE:

TESTS=$(wildcard tests/*.c)
TESTS_EXES=$(TESTS:.c=.out)
tests/%.out: tests/%.o $(NAME) FORCE
	$(CC)  $(CFLAGS) $< $(NAME) -o $@  $(LDFLAGS)  && (( ./$@ && echo $(NAME) tests SUCCESS ) || (echo $(NAME) tests FAILED))

test: $(TESTS_EXES)

##################################

clean:
	$(RM) $(TESTS_EXES) $(OBJS) $(NAME)

re: clean all

.PHONY: all test clean re