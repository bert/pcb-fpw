# Makefile.am for autogenerating Doxygen developer documentation.

EXTRA_DIST = \
	pcb-fpw.dox \
	pcb-fpw-logo-small.png \
	pcb-fpw-main.txt \
	pcb-logo-small.png \
	what-is-pcb-fpw.html


doxygen:
if DOXYGEN
	./create_fpw_dox.sh
else
	@echo "Skipping Doxygen developer documentation generation ..."
endif


.DEFAULT_GOAL : all

all: doxygen

clean:
	-rm -rf *~ html latex header.html

distclean:
	-rm -rf *~ html latex header.html Makefile.in Makefile

