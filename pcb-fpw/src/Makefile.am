## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = pcb-fpw \
        fpw

pcb_fpw_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h
	
fpw_SOURCES = \
        fpw.c

pcb_fpw_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

fpw_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

