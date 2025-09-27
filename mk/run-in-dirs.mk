define run-in-dirs
	@( \
		status=0; \
		for dir in $(MK_SUBDIRS); do \
			$(MAKE) -C $$dir $(1) || status=1; \
		done; \
		echo "status:: $$status"; \
		exit $$status \
	)
endef


all:
	$(call run-in-dirs,all)

re: clean all

test:
	$(call run-in-dirs,test)

clean:
	$(call run-in-dirs,clean)

.PHONY: all re clean
