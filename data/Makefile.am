theme=hicolor
xdgdatadir=@XDGDATADIR@
themedir=$(xdgdatadir)/icons/$(theme)

app_icon = fpw

mime_icons = \
	application-x-fpw

app_icon_files = \
	$(app_icon:%=%-48.png) \
	$(app_icon:%=%.svg)
#	$(app_icon:%=%-16.png)
#	$(app_icon:%=%-22.png)
#	$(app_icon:%=%-24.png)
#	$(app_icon:%=%-32.png)

mime_icon_files = \
	$(mime_icons:%=%-16.png) \
	$(mime_icons:%=%-22.png) \
	$(mime_icons:%=%-24.png) \
	$(mime_icons:%=%-32.png) \
	$(mime_icons:%=%-48.png) \
	$(mime_icons:%=%.svg)

mime_icon_sources = \
	$(mime_icons:%=%-16.svg) \
	$(mime_icons:%=%-22.svg) \
	$(mime_icons:%=%-32.svg) \
	$(mime_icons:%=%-48.svg)

theme_icons = \
	$(mime_icon_files:%=mimetypes,%) \
	$(app_icon_files:%=apps,%)


desktopdir=$(xdgdatadir)/applications
desktop_in_files = fpw.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)

appdatadir = $(datadir)/appdata
dist_appdata_DATA = fpw.appdata.xml

@INTLTOOL_DESKTOP_RULE@


mimedir = $(xdgdatadir)/mime
xmldir = $(mimedir)/packages

xml_in_files = fpw.xml.in
xml_DATA = $(xml_in_files:.xml.in=.xml)

@INTLTOOL_XML_RULE@

kdedatadir=@KDEDATADIR@
mimelnkdir = $(kdedatadir)/mimelnk
applicationdir = $(mimelnkdir)/application

application_in_files = \
	x-fpw.desktop.in

application_DATA = $(application_in_files:.desktop.in=.desktop)

@INTLTOOL_DESKTOP_RULE@

install_icon_exec = \
	$(SETENV) GTK_UPDATE_ICON_CACHE_BIN="@GTK_UPDATE_ICON_CACHE_BIN@" \
	$(SHELL) $(top_srcdir)/icon-theme-installer \
	-t $(theme) \
	-s $(srcdir) \
	-d "x$(DESTDIR)" \
	-b $(themedir) \
	-m "$(mkinstalldirs)" \
	-x "$(INSTALL_DATA)"

install-data-local:
	$(install_icon_exec) -i $(theme_icons)

install-data-hook:
if ENABLE_UPDATE_MIME_DATABASE
	$(UPDATE_MIME_DATABASE) "$(DESTDIR)$(mimedir)"
endif
if ENABLE_UPDATE_DESKTOP_DATABASE
	$(UPDATE_DESKTOP_DATABASE) "$(DESTDIR)$(desktopdir)"
endif

uninstall-hook:
if ENABLE_UPDATE_MIME_DATABASE
	$(UPDATE_MIME_DATABASE) "$(DESTDIR)$(mimedir)"
endif
if ENABLE_UPDATE_DESKTOP_DATABASE
	$(UPDATE_DESKTOP_DATABASE) "$(DESTDIR)$(desktopdir)"
endif
	$(install_icon_exec) -u $(theme_icons)

MAINTAINERCLEANFILES = *.log core FILE *~ Makefile.in
DISTCLEANFILES = $(xml_DATA) $(application_DATA) $(desktop_DATA)
EXTRA_DIST = $(mime_icon_files) \
	$(mime_icon_sources) \
	$(xml_in_files) \
	$(xml_DATA) \
	$(application_in_files) \
	$(app_icon_files) \
	$(desktop_in_files) \
	$(desktop_DATA) \
	regen_files \
	fpw_icon.ico

