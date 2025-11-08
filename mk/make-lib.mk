WORKSPACE_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)

include $(WORKSPACE_DIR)/mk/common.mk

all: $(NAME)

$(REL_BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -MF $(REL_BUILD_DIR)/$*.d -c $$(realpath $<) -o $$(realpath $@)

$(NAME): $(OBJS)
	if test $$(realpath $(NAME)) != $$(realpath  $(REL_BUILD_DIR)); then \
		$(AR) -rcs $(NAME)  $(OBJS); \
	fi;

##################################

FORCE:


ifdef TEST
TESTS_EXES=tests/$(TEST).out
else
TESTS=$(wildcard tests/*.c)
TESTS_EXES=$(TESTS:.c=.out)
endif

TESTS_EXES := $(patsubst %.out,$(REL_BUILD_DIR)/%.out,$(TESTS_EXES))


$(REL_BUILD_DIR)/tests/%.o: CSTD = $(CSTD_LATEST)
$(REL_BUILD_DIR)/tests/%.o: tests/%.c

$(REL_BUILD_DIR)/tests/%.out: $(REL_BUILD_DIR)/tests/%.o $(LIBS) FORCE
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

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
	if test $$(echo $(TESTS_EXES) | wc -c) != 1; then \
		$(RM) $(TESTS_EXES) $(OBJS) $(DEPS); \
	fi; \
	if test -f $(NAME); then \
		$(RM) $(NAME); \
	fi;

re: clean all

.PHONY: all test clean re