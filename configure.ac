AC_INIT([libitcoin_explorer], [0.1.0], [genjix@riseup.net])
AC_USE_SYSTEM_EXTENSIONS
AC_LANG(C++)
AC_CONFIG_AUX_DIR([build-aux])

# The BOOST_ROOT environment variable is *not* prioritize by the m4 tests.
# As a result there may be dependency conflicts between installed versions
# and a version specified in BOOST_ROOT.
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([-Wall -Werror])
AM_PROG_AR
LT_INIT
AC_PROG_CXX
AC_PROG_LIBTOOL
AC_GNU_SOURCE
AX_CXX_COMPILE_STDCXX_11(noext,mandatory)
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Boost doesn't publish package configs but has m4 tests.
# The current versions produce incorrect error message text.
AX_BOOST_BASE([1.50],,
    [AC_MSG_ERROR([Boost 1.50 or later is required but was not found.])])
AX_BOOST_CHRONO
AX_BOOST_DATE_TIME
AX_BOOST_FILESYSTEM
AX_BOOST_PROGRAM_OPTIONS
AX_BOOST_REGEX
AX_BOOST_SYSTEM
AX_BOOST_UNIT_TEST_FRAMEWORK

# GMP does not publish a package config, so we do a header and library test.
AC_CHECK_HEADER(gmp.h,,
    [AC_MSG_ERROR([GMP header is required but was not found.])],-)
AC_CHECK_LIB(gmp,__gmpz_init,,
    [AC_MSG_ERROR([GMP library is required but was not found.])])

# TODO: We require secp256k1 to require GMP (over OpenSSL).
PKG_CHECK_MODULES([secp256k1], [libsecp256k1 >= 0.0.1])
PKG_CHECK_MODULES([bitcoin], [libbitcoin >= 2.1.0])
PKG_CHECK_MODULES([bitcoin_client], [libbitcoin-client >= 0.0.2])
PKG_CHECK_MODULES([sodium], [libsodium >= 0.6.0])
PKG_CHECK_MODULES([zmq], [libzmq >= 4.0.0])
PKG_CHECK_MODULES([czmq], [libczmq >= 2.2.0])
PKG_CHECK_MODULES([czmqpp], [libczmq++ >= 0.4.1])

PKG_PROG_PKG_CONFIG

# Do not add contextual build parameters in configuration.
# http://stackoverflow.com/a/4680578
OPTIMIZATIONS="-fvisibility=internal"
WARNINGS="-Wall -Wextra -Wpedantic -Wno-missing-braces"
SAFEGUARDS="-fvisibility-inlines-hidden -fstack-protector-all"
EXCEPTIONS="-Wno-unused-function -Wno-unused-parameter"
AM_CXXFLAGS=$WARNINGS" "$SAFEGUARDS" "$OPTIMIZATIONS" "$EXCEPTIONS
AC_SUBST([AM_CXXFLAGS])

AC_ARG_WITH([pkgconfigdir], AS_HELP_STRING([--with-pkgconfigdir=PATH],
    [Path to the pkgconfig directory [[LIBDIR/pkgconfig]]]),
    [pkgconfigdir="$withval"], [pkgconfigdir='${libdir}/pkgconfig'])
AC_SUBST([pkgconfigdir])

AC_CONFIG_FILES([Makefile include/explorer/Makefile src/Makefile test/Makefile libbitcoin_explorer.pc])
AC_OUTPUT

