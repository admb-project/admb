AC_INIT([ADMB], [9.1], [users@admb-project.org])

# Check for programs used in building ADMB.
AC_PROG_CC
AC_PROG_CXX
AC_LANG([C++])
AC_CHECK_HEADERS(iostream)
AC_PROG_LEX

## Requires autoconf version 2.60 or newer
#AC_PROG_SED

# Check for programs used in building ADMB.
CXX_32OR64BIT="32bit"
CXXFLAGS="-m64"
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([])],
  [CXX_32OR64BIT="64bit"]
  [AC_MSG_RESULT([checking whether C++ compiler is 64-bit enabled... yes])],
  [CXXFLAGS="-m32"]
  [AC_MSG_RESULT([checking whether C++ compiler is 64-bit enabled... no])]
)
ARCH_CXXFLAG=${CXXFLAGS}

ADMB_TARGET=unix

ADMB_VERSION=`cat VERSION`
if test -e `which svnversion`
then
  SVNVERSION=`svnversion .` 
  if test "${SVNVERSION}" != "exported"
  then
    ADMB_REVISION=".${SVNVERSION}"
  fi
fi

if test  "`uname -s`" =  "Darwin"
then
  MACOS_PRODUCT_VERSION=`sw_vers -productVersion`
  MACOS_XCODE_VERSION=`xcodebuild -version | grep Xcode | awk '{print $2}'`
  ADMB_TARGET="admb-macos${MACOS_PRODUCT_VERSION}-xcode${MACOS_XCODE_VERSION}-${CXX_32OR64BIT}"
  MAKEFILE="linux.mak"
  INSTALLER_PACKAGEMAKER="scripts/installers/packagemaker/GNUmakefile"
fi

if test  "`uname -s`" =  "Linux"
then
  GCC_VERSION=`gcc -dumpversion`
  ADMB_TARGET="admb-linux-gcc${GCC_VERSION}-${CXX_32OR64BIT}"
  MAKEFILE="linux.mak"
fi

AC_CONFIG_FILES(
  [GNUmakefile:scripts/configure/GNUmakefile.in admb_configure.h:scripts/configure/admb_configure.h.in scripts/bash/admb-bin ${INSTALLER_PACKAGEMAKER} ]
)

AC_SUBST(revision, ${ADMB_REVISION})
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
