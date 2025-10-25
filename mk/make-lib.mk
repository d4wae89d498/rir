WORKSPACE_DIR = $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)

all: $(NAME)

include $(WORKSPACE_DIR)/mk/common.mk

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) -rcs $(NAME)  $(OBJS) 

##################################

FORCE:


ifdef TEST
TESTS_EXES=tests/$(TEST).out
else
TESTS=$(wildcard tests/*.c)
TESTS_EXES=$(TESTS:.c=.out)
endif

tests/%.o: CSTD = $(CSTD_LATEST)
tests/%.o: tests/%.c
tests/%.out: tests/%.o $(LIBS) $(NAME) FORCE
	$(CC) $(CFLAGS) $< $(NAME) -o $@ $(LDFLAGS)

test: $(TESTS_EXES)
	@echo "Running tests..."
	@failed=0; \
	for t in $(TESTS_EXES); do \
	   	fullpath=$$(realpath $$t); \
	    echo "Running $$fullpath..."; \
	    if ! $$fullpath; then \
	        echo "FAILED for $$fullpath"; \
	        failed=1; \
	    else \
	        echo "SUCCESS for $$fullpath"; \
	    fi; \
	done; \
	exit $$failed


##################################

clean:
	$(RM) $(TESTS_EXES) $(OBJS) $(NAME)

re: clean all

.PHONY: all test clean re