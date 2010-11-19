AC_INIT([ADMB], [9.1], [users@admb-project.org])

# Check for programs used in building ADMB.
AC_PROG_CC
AC_PROG_CXX
AC_LANG([C++])
AC_CHECK_HEADERS(iostream)
AC_PROG_LEX

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
  fi
fi

#AC_COMPILE_IFELSE([AC_LANG_PROGRAM([])],
#  [CXX_32OR64BIT="64bit"]
#  [AC_MSG_RESULT([checking whether C++ compiler is 64-bit enabled... yes])],
#  [CXXFLAGS="-m32"]
#  [AC_MSG_RESULT([checking whether C++ compiler is 64-bit enabled... no])]
#)
CXX_32OR64BIT="32bit"
CXXFLAGS="-m32"

if test  "`uname -s`" =  "Darwin"
then
  CXX_32OR64BIT="64bit"
  CXXFLAGS="-m64"
  MACOS_PRODUCT_VERSION=`sw_vers -productVersion`
  MACOS_XCODE_VERSION=`xcodebuild -version | grep Xcode | awk '{print $2}'`
  ADMB_TARGET="admb${ADMB_VERSION}${ADMB_REVISION}-macos${MACOS_PRODUCT_VERSION}-xcode${MACOS_XCODE_VERSION}-${CXX_32OR64BIT}"
  MAKEFILE="linux.mak"
  INSTALLER_PACKAGEMAKER="scripts/installers/packagemaker/GNUmakefile"
fi

if test  "`uname -s`" =  "Linux"
then

  if test  "`uname -m`" =  "x86_64"
  then
    CXX_32OR64BIT="64bit"
    CXXFLAGS="-m64"
  fi
  GCC_VERSION=`gcc -dumpversion`
  ADMB_TARGET="admb${ADMB_VERSION}${ADMB_REVISION}-linux-gcc${GCC_VERSION}-${CXX_32OR64BIT}"
  MAKEFILE="linux.mak"
fi

if test  "`uname -s`" =  "MINGW32_NT-6.1"
then
  GCC_VERSION=`gcc -dumpversion`
  ADMB_TARGET="admb${ADMB_VERSION}${ADMB_REVISION}-mingw-gcc${GCC_VERSION}-${CXX_32OR64BIT}"
  MAKEFILE="linux.mak"
fi

ARCH_CXXFLAG=${CXXFLAGS}

AC_CONFIG_FILES(
  [GNUmakefile:scripts/configure/GNUmakefile.in admb_configure.h:scripts/configure/admb_configure.h.in scripts/bash/admb-bin ${INSTALLER_PACKAGEMAKER} ]
)

AC_SUBST(revision, ${ADMB_REVISION})
AC_SUBST(lextargets, ${LEX_TARGETS})
AC_SUBST(version, ${ADMB_VERSION})
AC_SUBST(target, ${ADMB_TARGET})
AC_SUBST(disk, ../build/${ADMB_TARGET}/dist)
AC_SUBST(libpath, ../build/${ADMB_TARGET}/objects)
AC_SUBST(arch_cxxflag, ${ARCH_CXXFLAG})
AC_SUBST(cxx, ${CXX})
AC_SUBST(makefile, ${MAKEFILE})

PREFIX=${prefix}
AC_SUBST(PREFIX)

AC_OUTPUT
printf "\nConfigure completed for ${ADMB_TARGET}\n"
printf "To build ADMB, type 'make'\n"
