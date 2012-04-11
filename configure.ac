dnl Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([pcb-fpw],[0.0.11])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE

dnl Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_AWK
AC_PROG_CPP
AC_PROG_MKDIR_P
AC_DIAGNOSE([obsolete],[AM_PROG_CC_STDC:
	your code should no longer depend upon `am_cv_prog_cc_stdc', but upon
	`ac_cv_prog_cc_stdc'.  Remove this warning and the assignment when
	you adjust the code.  You can also remove the above call to
	AC_PROG_CC if you already called it elsewhere.])
am_cv_prog_cc_stdc=$ac_cv_prog_cc_stdc

dnl Checks for libraries.
AC_HEADER_STDC
AC_CHECK_HEADERS([libintl.h stdlib.h string.h unistd.h])
AC_SEARCH_LIBS([strerror],[cposix])

dnl Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

dnl Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset strcasecmp strdup strrchr])


pkg_modules="gtk+-2.0 >= 2.0.0"
PKG_CHECK_MODULES(PACKAGE, [$pkg_modules])
AC_SUBST(PACKAGE_CFLAGS)
AC_SUBST(PACKAGE_LIBS)

GETTEXT_PACKAGE=pcb-fpw
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [Gettext package.])

dnl Add the languages which your application supports.
ALL_LINGUAS=""
AM_GLIB_GNU_GETTEXT

dnl Create makefiles for (sub)directories.
AC_CONFIG_FILES([
Makefile
src/Makefile
po/Makefile.in
])
AC_OUTPUT

