###############################################################################
#  Copyright (c) 2014-2026 libbitcoin-explorer developers (see COPYING).
#
#         GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
#
###############################################################################

# Standard declarations.
#==============================================================================
# Requires Automake 1.14 or newer.

# Declare the required version of Autoconf.
AC_PREREQ([2.65])

# Process command-line arguments and perform initialization and verification.
AC_INIT([libbitcoin-explorer], [4.0.0], [eric@voskuil.org])

# Do compilation tests.
AC_LANG(C++)

# Specify the temporary directory for build tools.
AC_CONFIG_AUX_DIR([build-aux])

# Specify the directory of additional local Autoconf macros.
AC_CONFIG_MACRO_DIR([m4])

# Run macros for operation of generated Makefiles, enable non-recursive make.
# Unless [foreign] is specified standard GNU files will be required,
# specifically: AUTHORS, COPYING, INSTALL, NEWS, README and ChangeLog.
AM_INIT_AUTOMAKE([subdir-objects])

# Enable C and POSIX extensions that may be disabled on certain platforms.
AC_USE_SYSTEM_EXTENSIONS

# Enable the archiver.
AM_PROG_AR

# Initialize libtool.
LT_PREREQ(2.4.2)

# Enable shared libraries if available, and static if they don't conflict.
LT_INIT
AC_SUBST([LIBTOOL_DEPS])

# Determine C++ compiler to use.
AC_PROG_CXX

# Enable sed for substitution.
AC_PROG_SED

# Compute the canonical host-system type variable host, including host_os.
AC_CANONICAL_HOST

# Enable silent rules option.
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Check for pkg-config.
PKG_PROG_PKG_CONFIG
AS_IF([test -n "${PKG_CONFIG}"], [],
    [AC_MSG_ERROR([pkg-config is required but was not found.])])

AS_IF([test "x${enable_static}" != "xno"],
    [AC_SUBST([PKG_CONFIG], ["${PKG_CONFIG} --static"])])

# Declare environment variables that affect the build.
#------------------------------------------------------------------------------
AC_ARG_VAR([CC], "C compiler to use, such as gcc or clang")
AC_ARG_VAR([CXX], "C++ compiler to use, such as g++ or clang++")
AC_ARG_VAR([PKG_CONFIG_PATH], "Additional directories for package discovery.")

repository_root_dir=`cd "${srcdir}/../.." && pwd`

# Check for baseline language coverage in the compiler for the C++20 standard.
#------------------------------------------------------------------------------
AX_CXX_COMPILE_STDCXX([20], [noext], [mandatory])

# Process options.
#==============================================================================
AC_MSG_CHECKING([--enable-isystem option])
AC_ARG_ENABLE([isystem],
    AS_HELP_STRING([--enable-isystem],
        [Substitute -isystem for -I in dependencies. @<:@default=no@:>@]),
    [enable_isystem=$enableval],
    [enable_isystem=no])
AC_MSG_RESULT([$enable_isystem])
AM_CONDITIONAL([ENABLE_ISYSTEM], [test "x${enable_isystem}" != "xno"])

AC_MSG_CHECKING([--with-pkgconfigdir option])
AC_ARG_WITH([pkgconfigdir],
    AS_HELP_STRING([--with-pkgconfigdir=DIR],
        [Path to pkgconfig directory. @<:@default=${libdir}/pkgconfig@:>@]),
    [with_pkgconfigdir=$withval],
    [with_pkgconfigdir=${libdir}/pkgconfig])
AC_MSG_RESULT([$with_pkgconfigdir])
AC_SUBST([pkgconfigdir],[${with_pkgconfigdir}])

AC_MSG_CHECKING([--enable-ndebug option])
AC_ARG_ENABLE([ndebug],
    AS_HELP_STRING([--enable-ndebug],
        [Compile with NDEBUG (no debug assertions). @<:@default=yes@:>@]),
    [enable_ndebug=$enableval],
    [enable_ndebug=yes])
AC_MSG_RESULT([$enable_ndebug])
AM_CONDITIONAL([ENABLE_NDEBUG], [test "x${enable_ndebug}" != "xno"])
AS_IF([test "x${enable_ndebug}" != "xno"], [AC_DEFINE([NDEBUG])])

AS_IF([test "x${enable_shared}" != "xno"], [AC_DEFINE([BOOST_ALL_DYN_LINK])])

AC_MSG_CHECKING([--with-tests option])
AC_ARG_WITH([tests],
    AS_HELP_STRING([--with-tests],
        [Compile with unit tests. @<:@default=yes@:>@]),
    [with_tests=$withval],
    [with_tests=yes])
AC_MSG_RESULT([$with_tests])
AM_CONDITIONAL([WITH_TESTS], [test "x${with_tests}" != "xno"])

AC_MSG_CHECKING([--with-console option])
AC_ARG_WITH([console],
    AS_HELP_STRING([--with-console],
        [Compile with console application. @<:@default=yes@:>@]),
    [with_console=$withval],
    [with_console=yes])
AC_MSG_RESULT([$with_console])
AM_CONDITIONAL([WITH_CONSOLE], [test "x${with_console}" != "xno"])

# Set flags.
#==============================================================================
AX_CHECK_COMPILE_FLAG([-Wall],
  [
    CFLAGS="${CFLAGS} -Wall";
    CXXFLAGS="${CXXFLAGS} -Wall";
  ])

AX_CHECK_COMPILE_FLAG([-Wextra],
  [
    CFLAGS="${CFLAGS} -Wextra";
    CXXFLAGS="${CXXFLAGS} -Wextra";
  ])

AX_CHECK_COMPILE_FLAG([-Wno-reorder],
  [
    CXXFLAGS="${CXXFLAGS} -Wno-reorder";
  ])

AX_CHECK_COMPILE_FLAG([-Wno-missing-field-initializers],
  [
    CXXFLAGS="${CXXFLAGS} -Wno-missing-field-initializers";
  ])

AX_CHECK_COMPILE_FLAG([-Wno-missing-braces],
  [
    CXXFLAGS="${CXXFLAGS} -Wno-missing-braces";
  ])

AX_CHECK_COMPILE_FLAG([-Wno-comment],
  [
    CXXFLAGS="${CXXFLAGS} -Wno-comment";
  ])

AX_CHECK_COMPILE_FLAG([-Wno-deprecated-copy],
  [
    CXXFLAGS="${CXXFLAGS} -Wno-deprecated-copy";
  ])

AS_CASE([${CC}], [*clang*],
  [
    AX_CHECK_COMPILE_FLAG([-Wno-mismatched-tags],
      [
        CXXFLAGS="${CXXFLAGS} -Wno-mismatched-tags";
      ])
  ])

AX_CHECK_COMPILE_FLAG([-fstack-protector-all],
  [
    CXXFLAGS="${CXXFLAGS} -fstack-protector-all";
  ])

AX_CHECK_COMPILE_FLAG([-Wno-ignored-attributes],
  [
    libbitcoin_explorer_test_CXXFLAGS="${libbitcoin_explorer_test_CXXFLAGS} -Wno-ignored-attributes";
    bitcoin_explorer_CXXFLAGS="${bitcoin_explorer_CXXFLAGS} -Wno-ignored-attributes";
  ])

AX_CHECK_COMPILE_FLAG([-Wno-long-long],
  [
    libbitcoin_explorer_test_CXXFLAGS="${libbitcoin_explorer_test_CXXFLAGS} -Wno-long-long";
    bitcoin_explorer_CXXFLAGS="${bitcoin_explorer_CXXFLAGS} -Wno-long-long";
  ])

AS_CASE([${CC}], [*gnu*],
  [
    AX_CHECK_COMPILE_FLAG([-fno-var-tracking-assignments],
      [
        libbitcoin_explorer_test_CXXFLAGS="${libbitcoin_explorer_test_CXXFLAGS} -fno-var-tracking-assignments";
        bitcoin_explorer_CXXFLAGS="${bitcoin_explorer_CXXFLAGS} -fno-var-tracking-assignments";
      ])
  ])

# Check dependencies.
#==============================================================================
PKG_CHECK_MODULES(
  [libbitcoin_system],
  [libbitcoin-system >= 4.0.0],
  [],
  [
    AC_MSG_ERROR([libbitcoin-system >= 4.0.0 is required but was not found.])
  ])
AC_SUBST([libbitcoin_system_PKG], ['libbitcoin-system >= 4.0.0'])
AC_SUBST([libbitcoin_system_CPPFLAGS], [${libbitcoin_system_CFLAGS}])
AC_SUBST([libbitcoin_system_ISYS_CPPFLAGS], [`echo ${libbitcoin_system_CPPFLAGS} | ${SED} s/^-I/-isystem/g | ${SED} s/' -I'/' -isystem'/g`])
AC_MSG_NOTICE([libbitcoin_system_CPPFLAGS : ${libbitcoin_system_CPPFLAGS}])
AC_MSG_NOTICE([libbitcoin_system_ISYS_CPPFLAGS : ${libbitcoin_system_ISYS_CPPFLAGS}])
AC_MSG_NOTICE([libbitcoin_system_OTHER_CFLAGS : ${libbitcoin_system_OTHER_CFLAGS}])
AC_MSG_NOTICE([libbitcoin_system_INCLUDEDIR : ${libbitcoin_system_INCLUDEDIR}])
AC_MSG_NOTICE([libbitcoin_system_LIBS : ${libbitcoin_system_LIBS}])
AS_IF([test "x${enable_isystem}" != "xno"],
  [AC_SUBST([libbitcoin_system_BUILD_CPPFLAGS], [${libbitcoin_system_ISYS_CPPFLAGS}])],
  [AC_SUBST([libbitcoin_system_BUILD_CPPFLAGS], [${libbitcoin_system_CPPFLAGS}])])
AC_MSG_NOTICE([libbitcoin_system_BUILD_CPPFLAGS : ${libbitcoin_system_BUILD_CPPFLAGS}])

AX_BOOST_BASE([1.86.0],
  [
    AC_SUBST([boost_CPPFLAGS], [${BOOST_CPPFLAGS}])
    AC_SUBST([boost_ISYSTEM_CPPFLAGS], [`echo ${boost_CPPFLAGS} | ${SED} s/^-I/-isystem/g | ${SED} s/' -I'/' -isystem'/g`])
    AC_SUBST([boost_LDFLAGS], [${BOOST_LDFLAGS}])
    AC_MSG_NOTICE([boost_CPPFLAGS : ${boost_CPPFLAGS}])
    AC_MSG_NOTICE([boost_ISYS_CPPFLAGS : ${boost_ISYS_CPPFLAGS}])
    AC_MSG_NOTICE([boost_LDFLAGS : ${boost_LDFLAGS}])
  ],
  [
    AC_MSG_ERROR([Boost 1.86.0 or later is required but was not found.])
  ])

AS_IF([test "x${enable_isystem}" != "xno"],
  [ AC_SUBST([boost_BUILD_CPPFLAGS], [${boost_ISYSTEM_CPPFLAGS}]) ],
  [ AC_SUBST([boost_BUILD_CPPFLAGS], [${boost_CPPFLAGS}]) ])

AC_MSG_NOTICE([boost_BUILD_CPPFLAGS : ${boost_BUILD_CPPFLAGS}])

AS_IF([(test "x${with_tests}" != "xno")],
  [
    AX_BOOST_UNIT_TEST_FRAMEWORK
    AC_SUBST([boost_unit_test_framework_LIBS], [${BOOST_UNIT_TEST_FRAMEWORK_LIB}])
    AC_MSG_NOTICE([boost_unit_test_framework_LIBS : ${boost_unit_test_framework_LIBS}])
  ])

AC_CONFIG_FILES([
    Makefile
    libbitcoin-explorer.pc
  ])

AC_OUTPUT
