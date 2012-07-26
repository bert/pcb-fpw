## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = pcb-gfpw

pcb_gfpw_SOURCES = \
	pcb-gfpw.c \
	about_dialog.c about_dialog.h \
	support.c support.h
	
pcb_gfpw_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)
	
# EOF #

