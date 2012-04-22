EXTRA_DIST = \
	pcb-fpw.dox \
	pcb-fpw-logo-small.png \
	pcb-fpw-main.txt \
	pcb-logo-small.png \
	what-is-pcb-fpw.html


.DEFAULT_GOAL := all

all:

doxygen: pcb-fpw.dox
	@echo 'Creating doxygen documentation for pcb-fpw...'
	@echo '<title>PCB-FPW: PCB FPW - Printed Circuit Board FootPrintWizard.</title>' > header.html
	@echo '<link href="doxygen.css" rel="stylesheet" type="text/css">' >> header.html
	@echo '<link href="tabs.css" rel="stylesheet" type="text/css">' >> header.html
	@echo '</head><body>' >> header.html
	@echo '<h3>PCB-FPW developer documentation based on version: ' $(git describe) ' </h3>' >> header.html
	$(DOXYGEN) pcb-fpw.dox

clean:
	-rm -rf *~ html latex

distclean-local:
	-rm -rf html latex

maintainer-clean-local:
	-rm -rf html latex

