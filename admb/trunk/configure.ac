AC_INIT([ADMB], [9.1], [users@admb-project.org])

# Check for programs used in building ADMB.
AC_PROG_CC
AC_PROG_CXX
AC_LANG([C++])
AC_CHECK_HEADERS(iostream)
AC_PROG_LEX
AC_PROG_SED

# Check for programs used in building ADMB.
CXX_32OR64BIT="32bit"
SAVED_CXXFLAGS="$CXXFLAGS"
CXXFLAGS="$CXXFLAGS -m64"
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([])],
  [CXX_32OR64BIT="64bit"]
  [AC_MSG_RESULT([checking whether C++ compiler is 64-bit enabled... yes])],
  [CXXFLAGS=$SAVED_CXXFLAGS]
  [AC_MSG_RESULT([checking whether C++ compiler is 64-bit enabled... no])]
)

admb_target=linux
if test  "`uname -s`" =  "Darwin"
then
  MACOS_PRODUCT_VERSION=`sw_vers -productVersion`
  MACOS_XCODE_VERSION=`xcodebuild -version | grep Xcode | awk '{print $2}'`
  ADMB_TARGET="admb-macos${MACOS_PRODUCT_VERSION}-xcode${MACOS_XCODE_VERSION}"
  admb_target="admb-macos${MACOS_PRODUCT_VERSION}-xcode${MACOS_XCODE_VERSION}-${CXX_32OR64BIT}"
fi

AC_SUBST(target, $admb_target)
AC_OUTPUT(admb.cfg)
