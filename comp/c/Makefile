#
# Later will add config.mk for capable install
#
include config.mk

bfc: bfc.c

install: bfc
	@cp bfc $(PREFIX)/bin/bfc
	@chmod 755 $(PREFIX)/bin/bfc
	@echo completed install

clean:
	@echo cleaning
	@$(RM) bfc out*
