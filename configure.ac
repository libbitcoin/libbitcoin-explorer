AC_INIT([sx], [0.1], [genjix@riseup.net])
AC_USE_SYSTEM_EXTENSIONS
AC_LANG(C++)
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AM_PROG_AR
LT_INIT
AC_PROG_CXX
AC_PROG_LIBTOOL
AC_GNU_SOURCE
AX_CXX_COMPILE_STDCXX_11(noext,mandatory)
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([libbitcoin], [libbitcoin])
PKG_CHECK_MODULES([libwallet], [libwallet])
PKG_CHECK_MODULES([libobelisk], [libobelisk],
    [enable_obelisk="yes"], [enable_obelisk="no"])
AM_CONDITIONAL([HAVE_OBELISK], [test $enable_obelisk = "yes"])
AC_CONFIG_FILES([Makefile src/Makefile test/Makefile])
AC_OUTPUT

