MK_SUBDIRS := rir-ir # rir-ast rir-backend rir-cli

include ./mk/run-in-dirs.mk

PREFIX ?= /usr/local

install:
	sudo mkdir -p $(PREFIX)/bin $(PREFIX)/share/man/man1
	sudo cp rir-cli/rir $(PREFIX)/bin/rir
	sudo cp man/rir.1 $(PREFIX)/share/man/man1/

uninstall:
	sudo rm -f $(PREFIX)/bin/rir
	sudo rm -f $(PREFIX)/share/man/man1/rir.1

.PHONY: install uninstall