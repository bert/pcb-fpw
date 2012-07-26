## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = pcb-gfpw

pcb_gfpw_SOURCES = \
	pcb-gfpw.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	libfpw.c \
	dimensions.c \
	preview.c \
	select_exceptions.c \
	register_functions.c \
	../bga.c \
	../capa.c \
	../capc.c \
	../capm.c \
	../capmp.c \
	../cappr.c \
	../con_dil.c \
	../con_dip.c \
	../con_hdr.c \
	../con_sil.c \
	../diom.c \
	../diomelf.c \
	../dip.c \
	../dips.c \
	../indc.c \
	../indm.c \
	../indp.c \
	../pga.c \
	../plcc.c \
	../res.c \
	../resc.c \
	../resm.c \
	../resmelf.c \
	../sil.c \
	../sip.c \
	../sot.c \
	../to.c \
	
pcb_gfpw_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

