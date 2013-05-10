AC_INIT([ADMB], [11.1], [users@admb-project.org]): ${CXXFLAGS="${CXXFLAGS}"} ${CFLAGS="${CFLAGS}"} 

# Check for programs used in building ADMB.
AC_PROG_CC
AC_PROG_CXX
AC_LANG([C++])
AC_CHECK_HEADERS(iostream)
AC_PROG_LEX
AC_PREFIX_DEFAULT(/usr/local/admb)

AC_CHECK_PROG(HAS_SED,sed,[yes])
if test "${HAS_SED}" = "sed" -a "${LEX}" = "flex"
then
  LEX_TARGETS="tpl2rem.lex tpl2cpp.lex"
fi

AC_CONFIG_FILES(
  [GNUmakefile:scripts/configure/GNUmakefile.in ]
)

AC_SUBST(cxxflags, ${CXXFLAGS})
AC_SUBST(cflags, ${CFLAGS})
AC_SUBST(cxx, ${CXX})
AC_SUBST(cc, ${CC})

PREFIX=${prefix}
AC_SUBST(PREFIX)

AC_OUTPUT
printf "\nConfigure completed for '${CXX}'.\n"
printf "To build ADMB, type 'make'.\n"
