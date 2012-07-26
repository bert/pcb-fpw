## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = pcb-gfpw

pcb_gfpw_SOURCES = \
	pcb_gfpw.c \
	pcb_gfpw.h \
	about_dialog.c \
	about_dialog.h \
	callbacks.c \
	callbacks.h \
	dimensions_dialog.c \
	dimensions_dialog.h \
	filechooser_dialog.c \
	filechooser_dialog.h \
	main_window.c \
	main_window.h \
	preview_dialog.c \
	preview_dialog.h \
	select_exceptions_dialog.c \
	select_exceptions_dialog.h \
	support.c \
	support.h \
	../bga.c \
	../bga.h \
	../capa.c \
	../capa.h \
	../capad.c \
	../capad.h \
	../capc.c \
	../capc.h \
	../capm.c \
	../capm.h \
	../capmp.c \
	../capmp.h \
	../cappr.c \
	../cappr.h \
	../con_dil.c \
	../con_dil.h \
	../con_dip.c \
	../con_dip.h \
	../con_hdr.c \
	../con_hdr.h \
	../con_sil.c \
	../con_sil.h \
	../dioad.c \
	../dioad.h \
	../diom.c \
	../diom.h \
	../diomelf.c \
	../diomelf.h \
	../dip.c \
	../dip.h \
	../dips.c \
	../dips.h \
	../globals.h \
	../hdrv.c \
	../hdrv.h \
	../indad.c \
	../indad.h \
	../indc.c \
	../indc.h \
	../indm.c \
	../indm.h \
	../indp.c \
	../indp.h \
	../jump.c \
	../jump.h \
	../libfpw.c \
	../libfpw.h \
	../mtgnp.c \
	../mtgnp.h \
	../mtgp.c \
	../mtgp.h \
	../packages.h \
	../pcb_globals.h \
	../pga.c \
	../pga.h \
	../plcc.c \
	../plcc.h \
	../resad.c \
	../resad.h \
	../resar.c \
	../resar.h \
	../res.c \
	../res.h \
	../resc.c \
	../resc.h \
	../resm.c \
	../resm.h \
	../resmelf.c \
	../resmelf.h \
	../sil.c \
	../sil.h \
	../sip.c \
	../sip.h \
	../sot.c \
	../sot.h \
	../to.c \
	../to.h
	
pcb_gfpw_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

# EOF #

