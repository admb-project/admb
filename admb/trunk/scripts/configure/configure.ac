AC_INIT([ADMB], [9.1], [users@admb-project.org])

AC_CONFIG_FILES(
  [admb.cfg:scripts/configure/admb.cfg.in src/Makefile scripts/bash/admb-bin]
)

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
if test  "`uname -s`" =  "Darwin"
then
  MACOS_PRODUCT_VERSION=`sw_vers -productVersion`
  MACOS_XCODE_VERSION=`xcodebuild -version | grep Xcode | awk '{print $2}'`
  ADMB_TARGET="admb-macos${MACOS_PRODUCT_VERSION}-xcode${MACOS_XCODE_VERSION}-${CXX_32OR64BIT}"
  MAKEFILE="linux.mak"
fi

if test  "`uname -s`" =  "Linux"
then
  GCC_VERSION=`gcc -dumpversion`
  ADMB_TARGET="admb-linux-gcc${GCC_VERSION}-${CXX_32OR64BIT}"
  MAKEFILE="linux.mak"
fi

AC_SUBST(target, ${ADMB_TARGET})
AC_SUBST(disk, ../build/${ADMB_TARGET}/dist)
AC_SUBST(libpath, ../build/${ADMB_TARGET}/objects)
AC_SUBST(arch_cxxflag, ${ARCH_CXXFLAG})
AC_SUBST(cxx, ${CXX})
AC_SUBST(makefile, ${MAKEFILE})

PREFIX=${prefix}
AC_SUBST(PREFIX)

AC_OUTPUT
