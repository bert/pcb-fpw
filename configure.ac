# Process this file with autoconf to produce a configure script.

AC_INIT([pcb-fpw],[0.0.11])
AC_CONFIG_SRCDIR([config.h.in])
AC_PREREQ([2.65])
AM_INIT_AUTOMAKE([1.11])
AC_GNU_SOURCE
AC_CONFIG_HEADERS([config.h])

# Try to figure out if we are building from git sources.
# If we are then unless building of the documentation has
# been disabled then just require the user have all the right
# tools.  Users building from a tarball won't need latex, makeinfo,
# etc. but if you're already downloading development sources, then
# it is not unreasonable to require development tools.  What motivated
# this is that using maintainer mode proved to cause regular confusion.

pcb_fpw_sources="tarball"
AC_MSG_CHECKING([if you are building from a git checkout])
pcb_fpw_git_version=no
if test -f $srcdir/.gitignore ; then
	pcb_fpw_git_version=yes
	AC_MSG_RESULT([yes])
	pcb_fpw_sources="GIT"
else
	AC_MSG_RESULT([no])
fi
AM_CONDITIONAL(GIT_VERSION, test x$pcb_fpw_git_version = xyes)

# See if we are supposed to build the docs.

docs_yesno=yes
AC_MSG_CHECKING([if the documentation should be built])
AC_ARG_ENABLE([doc],
[  --enable-doc            Build and install the documentation [[default=yes]]],
[
if test "X$enable_doc" = "Xno" ; then
        DOC=""
        AC_MSG_RESULT([no])
        docs_yesno=no
else
        DOC=doc
        AC_MSG_RESULT([yes])
        docs_yesno=yes
fi
],
[
DOC=doc
AC_MSG_RESULT([yes])
docs_yesno=yes
])
AC_SUBST(DOC)


AC_MSG_CHECKING([if maintainer mode is required])
if test "$docs_yesno" = "yes" -a "$pcb_git_version" = "yes" ; then
	AC_MSG_RESULT([yes -- the documentation build is enabled and your sources are from git])
	enable_maintainer_mode=yes
else
	AC_MSG_RESULT([no])
fi

AM_MAINTAINER_MODE

# Determine host type
AC_CANONICAL_HOST
AC_MSG_CHECKING(for windows)
PCB_FPW_PATH_DELIMETER=":"
PCB_FPW_DIR_SEPARATOR_S="/"
PCB_FPW_DIR_SEPARATOR_C='/'
case $host in
	*-*-cygwin* )
		CFLAGS="$CFLAGS ${CYGWIN_CFLAGS}"
		CPPFLAGS="$CPPFLAGS ${CYGWIN_CPPFLAGS}"
		;;

	*-*-mingw* )
		WIN32=yes
		CFLAGS="$CFLAGS ${MINGW_CFLAGS:--mms-bitfields -mwindows}"
		CPPFLAGS="$CPPFLAGS ${MINGW_CPPFLAGS:--mms-bitfields -mwindows}"
		;;

	* )
		WIN32=no
		;;
esac

AC_MSG_RESULT($WIN32)
AC_SUBST(WIN32)
AM_CONDITIONAL(WIN32, test x$WIN32 = xyes)
if test "x$WIN32" = "xyes" ; then
	PCB_FPW_PATH_DELIMETER=";"
	PCB_FPW_DIR_SEPARATOR_S="\\\\"
	PCB_FPW_DIR_SEPARATOR_C='\\'
fi

AC_DEFINE_UNQUOTED(PCB_FPW_DIR_SEPARATOR_C,'$PCB_FPW_DIR_SEPARATOR_C',[Directory separator char])
AC_DEFINE_UNQUOTED(PCB_FPW_DIR_SEPARATOR_S,"$PCB_FPW_DIR_SEPARATOR_S",[Directory separator string])
AC_DEFINE_UNQUOTED(PCB_FPW_PATH_DELIMETER,"$PCB_FPW_PATH_DELIMETER",[Search path separator string])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
if test "x$WIN32" = "xyes" ; then
	AC_CHECK_TOOL(WINDRES, windres, [no])
	if test "$WINDRES" = "no" ; then
		AC_MSG_ERROR([*** Could not find an implementation of windres in your PATH.])
	fi
fi
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_AWK
AC_PROG_CPP

# AC_PROG_MKDIR_P
# is a backport of autoconf-2.60's AC_PROG_MKDIR_P.
# Remove this macro when we can assume autoconf >= 2.60.
m4_ifdef([AC_PROG_MKDIR_P], [], [
  AC_DEFUN([AC_PROG_MKDIR_P],
    [AC_REQUIRE([AM_PROG_MKDIR_P])dnl defined by automake
     MKDIR_P='$(mkdir_p)'
     AC_SUBST([MKDIR_P])])])
AC_PROG_MKDIR_P

AC_DIAGNOSE([obsolete],[AM_PROG_CC_STDC:
	your code should no longer depend upon `am_cv_prog_cc_stdc', but upon
	`ac_cv_prog_cc_stdc'.  Remove this warning and the assignment when
	you adjust the code.  You can also remove the above call to
	AC_PROG_CC if you already called it elsewhere.])
am_cv_prog_cc_stdc=$ac_cv_prog_cc_stdc

# Checks for libraries.
AC_HEADER_STDC
AC_CHECK_HEADERS([libintl.h stdlib.h string.h unistd.h])
AC_SEARCH_LIBS([strerror],[cposix])
AC_CHECK_LIB(X11, XOpenDisplay, , , $X_LIBS)
AC_CHECK_LIB(Xext, main, , , $X_LIBS)
AC_CHECK_LIB(Xt, XtOpenDisplay, , , $X_LIBS)
AC_CHECK_LIB(Xmu, main, , , $X_LIBS)
AC_CHECK_LIB(Xpm, main, , , $X_LIBS)
AC_CHECK_LIB(Xm, XmCreateMainWindow, , , $X_LIBS)
AC_CHECK_LIB(fl, yywrap)
AC_CHECK_LIB([m], [sqrt])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset strcasecmp strdup strrchr])

# Search for glib.
PKG_CHECK_MODULES(GLIB, glib-2.0, ,
		[AC_MSG_RESULT([Note: cannot find glib-2.0.
You may want to review the following errors:
$GLIB_PKG_ERRORS])]
)

pkg_modules="gtk+-2.0 >= 2.0.0"
PKG_CHECK_MODULES(PACKAGE, [$pkg_modules])
AC_SUBST(PACKAGE_CFLAGS)
AC_SUBST(PACKAGE_LIBS)

# i18n
GETTEXT_PACKAGE=$PACKAGE
AH_TEMPLATE([GETTEXT_PACKAGE], [Name of this program's gettext domain])
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [Gettext package.])
AC_SUBST(GETTEXT_PACKAGE)
# Add the languages which your application supports.
ALL_LINGUAS=""
AM_GLIB_GNU_GETTEXT

# Used for building the icons.
AC_PATH_PROG(XPMTOPPM, xpmtoppm, notfound)
AC_PATH_PROG(PPMTOWINICON, ppmtowinicon, notfound)
AC_PATH_PROG(CONVERT, convert, notfound)

# desktop integration

AC_PATH_PROG(SETENV, env, [])
AC_PATH_PROG(GTK_UPDATE_ICON_CACHE_BIN, gtk-update-icon-path, [true])

# Change default location for XDG files (MIME and Icons)
AC_ARG_WITH(xdgdatadir, [  --with-xdgdatadir=path  Change where the theme icons 
and mime registrations are installed [[DATADIR]]], [opt_xdgdatadir=$withval])

# Change default location for KDE data files (KDE MIME registrations)
AC_ARG_WITH(kdedatadir, [  --with-kdedatadir=path  Change where the KDE mime reg
istrations are installed [[DATADIR]]], [opt_kdedatadir=$withval])

if test x$opt_xdgdatadir = x; then
	# path was not specified with --with-xdgdatadir
	XDGDATADIR='${datadir}'
else
	# path WAS specified with --with-xdgdatadir
	XDGDATADIR="$opt_xdgdatadir"
fi
AC_SUBST(XDGDATADIR)

if test x$opt_kdedatadir = x; then
	# path was not specified with --with-kdedatadir
	KDEDATADIR='${datadir}'
else
	# path WAS specified with --with-kdedatadir
	KDEDATADIR="$opt_kdedatadir"
fi
AC_SUBST(KDEDATADIR)

AC_ARG_ENABLE(update-desktop-database,
	AC_HELP_STRING([--disable-update-desktop-database],
	[do not update desktop database after installation]),,
	enable_update_desktop_database=yes)

AM_CONDITIONAL(ENABLE_UPDATE_DESKTOP_DATABASE, test x$enable_update_desktop_database = xyes)

if test x$enable_update_desktop_database = xyes ; then
	AC_PATH_PROG(UPDATE_DESKTOP_DATABASE, [update-desktop-database], no)
	if test $UPDATE_DESKTOP_DATABASE = no; then
	AC_MSG_ERROR([Cannot find update-desktop-database, make sure it is installed and in your PATH, or configure with --disable-update-desktop-database])
	fi
fi

AC_ARG_ENABLE(update-mime-database,
	AC_HELP_STRING([--disable-update-mime-database],
	[do not update mime database after installation]),,
	enable_update_mime_database=yes)

AM_CONDITIONAL(ENABLE_UPDATE_MIME_DATABASE, test x$enable_update_mime_database = xyes)

if test x$enable_update_mime_database = xyes ; then
	AC_PATH_PROG(UPDATE_MIME_DATABASE, [update-mime-database], no)
	if test $UPDATE_MIME_DATABASE = no; then
	AC_MSG_ERROR([Cannot find update-mime-database, make sure it is installed and in your PATH, or configure with --disable-update-mime-database])
	fi
fi

# Create makefiles for (sub)directories.
AC_CONFIG_FILES([
Makefile
po/Makefile.in
doc/Makefile
doc/doxygen/Makefile
doc/manual/Makefile
src/Makefile
])
AC_OUTPUT

# Print some results.
expandedXDGDATADIR=`eval "echo $XDGDATADIR"`
expandedKDEDATADIR=`eval "echo $KDEDATADIR"`
AC_MSG_RESULT([
-----------------------------------------------
Configuration summary for $PACKAGE $VERSION:
Source tree distribution: $pcb_fpw_sources
Build documentation:      $docs_yesno
xdg data directory:       $expandedXDGDATADIR
KDE data directory:       $expandedKDEDATADIR
CC:                       $CC
CXX:                      $CXX
CPPFLAGS:                 $CPPFLAGS
CFLAGS:                   $CFLAGS
CXXFLAGS:                 $CXXFLAGS
LIBS:                     $LIBS
-----------------------------------------------
])

# EOF

# FIXME: add Makefile.in files to get the following
#data/Makefile
#doc/Makefile
#src/dbms/Makefile
#src/gtk2/Makefile
#src/gtk3/Makefile
#src/lesstif/Makefile

