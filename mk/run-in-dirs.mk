define run-in-dirs
	@for dir in $(MK_SUBDIRS); do \
		$(MAKE) -C $$dir $(1); \
	done
endef


all:
	$(call run-in-dirs,all)

re: clean all

test:
	$(call run-in-dirs,test)

clean:
	$(call run-in-dirs,clean)

.PHONY: all re clean
