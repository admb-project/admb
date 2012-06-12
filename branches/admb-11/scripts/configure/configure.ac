AC_INIT([ADMB], [11], [users@admb-project.org]): ${CXXFLAGS="${CXXFLAGS}"} ${CFLAGS="${CFLAGS}"} 

# Check for programs used in building ADMB.
AC_PROG_CC
AC_PROG_CXX
AC_LANG([C++])
AC_CHECK_HEADERS(iostream)
AC_PROG_LEX

#AC_ARG_ENABLE(enable64,
#    [AC_HELP_STRING([--enable-64bit], [Enable 64-bit compile])])

## Requires autoconf version 2.60 or newer
#AC_PROG_SED
AC_CHECK_PROG(HAS_SED,sed,[yes])
if test "${HAS_SED}" = "sed" -a "${LEX}" = "flex"
then
  LEX_TARGETS="tpl2rem.lex tpl2cpp.lex"
fi

ADMB_TARGET=unix

ADMB_VERSION=`cat VERSION`

AC_CHECK_PROG(HAS_SVNVERSION,svnversion,[yes])
if test "${HAS_SVNVERSION}" = "yes"
then
  SVNVERSION=`svnversion .`
  if test "${SVNVERSION}" != "exported"
  then
    ADMB_REVISION=".${SVNVERSION}"
    printf "creating REVISION...\n"
    echo ${SVNVERSION} > REVISION
  fi
fi

if test "${BUILD_64BIT}" = "yes"
then
CXX_32OR64BIT="64bit"
CXXFLAGS="-m64"
fi

AC_CHECK_SIZEOF([int *])
if test "$ac_cv_sizeof_int_p" = "4"
then
  CXX_32OR64BIT="32bit"
else
  CXX_32OR64BIT="64bit"
fi

if test  "`uname -s`" =  "Darwin"
then
  #CXX_32OR64BIT="64bit"
  #CXXFLAGS="-m64"
  MAKEFILE="linux.mak"
  MACOS_PRODUCT_VERSION=`sw_vers -productVersion`
  MACOS_XCODE_VERSION=`xcodebuild -version | grep Xcode | awk '{print $2}'`
  INSTALLER_PACKAGEMAKER="scripts/installers/packagemaker/GNUmakefile"
  CLANG_VERSION=`clang++ --version | head -n 1 | awk '{print $4}'`
  if test "${CXX}" = "clang++"
  then
    ADMB_TARGET="admb-${ADMB_VERSION}-macos${MACOS_PRODUCT_VERSION}-clang${CLANG_VERSION}-${CXX_32OR64BIT}"
  else
    ADMB_TARGET="admb-${ADMB_VERSION}-macos${MACOS_PRODUCT_VERSION}-xcode${MACOS_XCODE_VERSION}-${CXX_32OR64BIT}"
  fi
fi

if test  "`uname -s`" =  "Linux"
then

  #if test  "`uname -m`" =  "x86_64"
  #then
    #CXX_32OR64BIT="64bit"
    #CXXFLAGS="-m64"
  #fi
  if test "${CXX}" = "g++"
  then
    GCC_VERSION=`gcc -dumpversion`
    ADMB_TARGET="admb-${ADMB_VERSION}-linux-gcc${GCC_VERSION}-${CXX_32OR64BIT}"
  fi
  if test "${CXX}" = "icpc"
  then
    CXX_32OR64BIT="32bit"
    CXXFLAGS=""
    if [[ "`icpc -V |&  head -n 1 | awk '{ print $4 }'`" = "64" ]]
    then
    CXX_32OR64BIT="64bit"
    fi
    ICC_VERSION=`icc -dumpversion`
    ADMB_TARGET="admb-${ADMB_VERSION}-linux-icc${ICC_VERSION}-${CXX_32OR64BIT}"
  fi
  MAKEFILE="linux.mak"
fi

UNAME_S=`uname -s`
if (test  "${UNAME_S:0:10}" =  "MINGW32_NT")
then
  GCC_VERSION=`gcc -dumpversion`
  ADMB_TARGET="admb-${ADMB_VERSION}-mingw-gcc${GCC_VERSION}-${CXX_32OR64BIT}"
  MAKEFILE="linux.mak"
  INSTALLER_MINGW="scripts/installers/innosetup/mingw.iss"
fi

if (test  "${UNAME_S:0:9}" =  "CYGWIN_NT")
then
  GCC_VERSION=`gcc -dumpversion`
  ADMB_TARGET="admb-${ADMB_VERSION}-cygwin-gcc${GCC_VERSION}-${CXX_32OR64BIT}"
  MAKEFILE="linux.mak"
  INSTALLER_MINGW="scripts/installers/innosetup/mingw.iss"
fi

if test  "`uname -s`" =  "SunOS"
then
  if test "${CXX}" = "CC"
  then
    ADMB_TARGET="admb-${ADMB_VERSION}-opensolaris-sunstudio-${CXX_32OR64BIT}"
  else
    GCC_VERSION=`gcc -dumpversion`
    ADMB_TARGET="admb-${ADMB_VERSION}-opensolaris-gcc${GCC_VERSION}-${CXX_32OR64BIT}"
  fi
  MAKEFILE="linux.mak"
fi

CXXFLAGS=${CXXFLAGS}

AC_CONFIG_FILES(
  [GNUmakefile:scripts/configure/GNUmakefile.in admb_configure.h:scripts/configure/admb_configure.h.in scripts/admb/admb-bin ${INSTALLER_PACKAGEMAKER} ${INSTALLER_MINGW} ]
)

if test "${AR}" = ""
then
AC_SUBST(arvar, "")
else
AC_SUBST(arvar, AR=${AR})
fi
AC_SUBST(revision, ${ADMB_REVISION})
AC_SUBST(lextargets, ${LEX_TARGETS})
AC_SUBST(version, ${ADMB_VERSION})
AC_SUBST(target, ${ADMB_TARGET})
AC_SUBST(disk, ../build/${ADMB_TARGET})
AC_SUBST(libpath, ../build/objects/${ADMB_TARGET})
AC_SUBST(cxxflags, ${CXXFLAGS})
AC_SUBST(cflags, ${CFLAGS})
AC_SUBST(cxx, ${CXX})
AC_SUBST(cc, ${CC})
AC_SUBST(makefile, ${MAKEFILE})
AC_SUBST(gccversion, ${GCC_VERSION})
if test  "`uname -s`" =  "Darwin"
then
AC_SUBST(dmgtask, "make --file=${INSTALLER_PACKAGEMAKER}")
else
AC_SUBST(dmgtask, "")
fi

PREFIX=${prefix}
AC_SUBST(PREFIX)

AC_OUTPUT
printf "\nConfigure completed for '${ADMB_TARGET}'.\n"
printf "To build ADMB, type 'make'.\n"
