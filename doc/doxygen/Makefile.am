# Makefile.am for autogenerating Doxygen developer documentation.

EXTRA_DIST = \
	pcb-fpw.dox \
	pcb-fpw-logo-small.png \
	pcb-fpw-main.txt \
	pcb-logo-small.png \
	what-is-pcb-fpw.html


doxygen: 
	$(shell echo '<title>PCB-FPW: PCB FPW - Printed Circuit Board FootPrintWizard.</title>' > header.html)
	$(shell echo '<link href="doxygen.css" rel="stylesheet" type="text/css">' >> header.html)
	$(shell echo '<link href="tabs.css" rel="stylesheet" type="text/css">' >> header.html)
	$(shell echo '</head><body>' >> header.html)
	$(shell echo '<h3>PCB-FPW developer documentation based on version: ' $(shell git describe) ' </h3>' >> header.html)
	$(shell ./create_fpw-dox.sh)
	$(shell echo 'Created doxygen documentation for pcb-fpw ...')

.DEFAULT_GOAL : all

all: doxygen

clean:
	-rm -rf *~ html latex header.html

