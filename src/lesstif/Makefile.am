## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = pcb-lfpw

pcb_lfpw_SOURCES = \
	pcb-lfpw.c \
	main_window.c

pcb_lfpw_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)
