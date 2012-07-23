# Makefile.am for autogenerating Doxygen developer documentation.

EXTRA_DIST = \
	pcb-fpw.dox \
	pcb-fpw-logo-small.png \
	pcb-fpw-main.txt \
	pcb-logo-small.png \
	what-is-pcb-fpw.html


doxygen: 
	./create_fpw_dox.sh

.DEFAULT_GOAL : all

all: doxygen

clean:
	-rm -rf *~ html latex header.html

