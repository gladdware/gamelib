# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([gladdware-gamelib], [0.0.1], [gladdware@alexgladd.com])
AC_CONFIG_SRCDIR([src/App.h])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE

# KBuild-style compilation
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# configure for posix threads
AX_PTHREAD

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# init libtool
AC_ENABLE_SHARED
AC_DISABLE_STATIC
LT_INIT

# Checks for libraries.
AC_CHECK_LIB([m], [roundl])
AC_CHECK_LIB([rt], [clock_gettime])
PKG_CHECK_MODULES([LIBGL], [gl])
PKG_CHECK_MODULES([LIBGLU], [glu])
PKG_CHECK_MODULES([LIBSDL], [sdl])
PKG_CHECK_MODULES([LIBSDL_IMAGE], [SDL_image])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

# Makefile output
AC_CONFIG_FILES([\
    Makefile \
    src/Makefile \
    tst/Makefile
])

AC_OUTPUT
