# Makefile.am for generating a User Manual.

UM_SOURCES := $(wildcard *.xml)

UM_TARGETS := $(patsubst %.xml,%.html,$(UM_SOURCES))

%.html: %.xml
	xmlto html-nochunks $<

.DEFAULT_GOAL := all

all:

user_manual: $(UM_TARGETS)
	@echo 'Creating an User Manual for pcb-fpw...'

clean:
	-rm -rf *.html *~

distclean-local:
	-rm -rf *.html *~

maintainer-clean-local:
	-rm -rf *.html *~

