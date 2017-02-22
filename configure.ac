#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.69])
AC_INIT([libsecxx], [0.0.0], [BUG-REPORT-ADDRESS])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_SRCDIR([src/main.cpp])
 
# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AM_PROG_AR

# Checks for libraries.
LT_INIT

AX_CHECK_OPENSSL
AX_BOOST_BASE([])
AX_BOOST_SYSTEM
AX_BOOST_DATE_TIME
AX_BOOST_ASIO
AX_PTHREAD

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AX_CXX_COMPILE_STDCXX_11([ext],[mandatory])

# Checks for library functions.

AC_CONFIG_FILES([Makefile
	sec.pc])

AC_OUTPUT