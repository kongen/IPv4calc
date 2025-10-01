m4_define([ipv4calc_major_version], [0])
m4_define([ipv4calc_minor_version], [0])
m4_define([ipv4calc_micro_version], [1])
m4_define([ipv4calc_version],[ipv4calc_major_version.ipv4calc_minor_version.ipv4calc_micro_version])

AC_INIT([ipv4calc],[ipv4calc_version],[shm@hallas.nu])
AM_INIT_AUTOMAKE([-Wall -Werror dist-xz foreign])

AC_PROG_CXX
AC_PROG_LN_S
AC_PROG_RANLIB

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_MACRO_DIR([m4])

AC_CHECK_FUNCS([inet_ntoa])
AC_CHECK_HEADERS([arpa/inet.h])

AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
AC_OUTPUT
