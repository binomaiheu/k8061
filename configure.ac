AC_INIT([k8061],[1.1])
LIBK8061_RELEASE=1.1
LIBK8061_VERSION=1:1:0
AC_SUBST(LIBK8061_RELEASE)
AC_SUBST(LIBK8061_VERSION)

AM_INIT_AUTOMAKE([gnu])

dnl Disable unnecessary libtool tests for c++,fortran,java
define([AC_LIBTOOL_LANG_CXX_CONFIG], [:])dnl
define([AC_LIBTOOL_LANG_F77_CONFIG], [:])dnl
define([AC_LIBTOOL_LANG_GCJ_CONFIG], [:])dnl

AC_PROG_CC

AC_PROG_INSTALL

AC_PROG_LIBTOOL

AC_C_CONST
AC_FUNC_MALLOC
AC_HEADER_STDC

dnl Checking header files
AC_CHECK_HEADERS([limits.h stdlib.h string.h unistd.h])

dnl Checking libusb
PKG_CHECK_MODULES(libusb,libusb >= 0.1 )
AC_SUBST(libusb_CFLAGS)
AC_SUBST(libusb_LIBS)

dnl Checking readline and history libraries
AC_CHECK_LIB(history, add_history, [], AC_MSG_ERROR(Cannot find history library...))
AC_CHECK_LIB(readline, readline, [], AC_MSG_ERROR(Cannot find readline library...))

DX_HTML_FEATURE(ON)		 
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(OFF)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(ON)
DX_PS_FEATURE(OFF)

DX_INIT_DOXYGEN(libK8061, doxygen.cfg, doc/libK8061 )

AC_OUTPUT(Makefile src/Makefile libK8061/Makefile libK8061/libK8061.pc)



