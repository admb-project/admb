DESTDIR=..\build\dist
OBJDESTDIR=..\build\objects\dist

CXXFLAGS_SAF=/nologo /Ox /W4 /GF /EHsc /DSAFE_ALL /DUSE_LAPLACE /DWIN32 /D__MSVC32__=8 /I..\$(DESTDIR)\include
CXXFLAGS_OPT=/nologo /Ox /W4 /GF /EHsc /DOPT_LIB  /DUSE_LAPLACE /DWIN32 /D__MSVC32__=8 /I..\$(DESTDIR)\include

all: dist libs
	pushd $(DESTDIR) & cscript ..\..\scripts\create-admb-shortcut.vbs & popd

dist: srcs bins

srcs:
	IF NOT EXIST $(DESTDIR) md $(DESTDIR)
	copy ..\LICENSE.txt $(DESTDIR)
	copy ..\NEWS.txt $(DESTDIR)
	copy ..\README.txt $(DESTDIR)
	copy ..\VERSION $(DESTDIR)
	IF NOT EXIST $(DESTDIR)\examples xcopy /I /E /Y ..\examples $(DESTDIR)\examples
	IF NOT EXIST $(DESTDIR)\contrib xcopy /I /E /Y ..\contrib $(DESTDIR)\contrib

bins: libs
	IF NOT EXIST $(DESTDIR)\bin md $(DESTDIR)\bin
	copy df1b2-separable\sed* $(DESTDIR)\bin
	copy ..\scripts\cl\*.bat $(DESTDIR)\bin
	copy ..\scripts\admb\admb.bat $(DESTDIR)\bin
	copy ..\utilities\sed.exe $(DESTDIR)\bin
	copy ..\utilities\*.dll $(DESTDIR)\bin
	pushd nh99& ..\..\utilities\make  --file=Makefile CC="$(CC) /TC " DESTDIR="..\$(DESTDIR)" bins& popd
	pushd df1b2-separable& ..\..\utilities\make --file=Makefile CC="$(CC) /TC " DESTDIR="..\$(DESTDIR)" bins& popd

libs: includes admbsaf admbopt

admbsaf:
	IF NOT EXIST $(OBJDESTDIR) md $(OBJDESTDIR)
	pushd df1b2-separable & ..\..\utilities\make CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_SAF)" PREFIX_OBJ="..\$(OBJDESTDIR)\saflp-df1b2-separable-" DESTDIR="..\$(DESTDIR)" --file=Makefile & popd
	pushd linad99 & ..\..\utilities\make CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_SAF)" PREFIX_OBJ="..\$(OBJDESTDIR)\saflp-linad99-" DESTDIR="..\$(DESTDIR)" --file=Makefile & popd
	pushd nh99 & ..\..\utilities\make CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_SAF)" PREFIX_OBJ="..\$(OBJDESTDIR)\saflp-nh99-" DESTDIR="..\$(DESTDIR)" --file=Makefile & popd
	pushd tools99 & ..\..\utilities\make CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_SAF)" PREFIX_OBJ="..\$(OBJDESTDIR)\saflp-tools99-" DESTDIR="..\$(DESTDIR)" --file=Makefile & popd
	IF NOT EXIST $(DESTDIR)\lib md $(DESTDIR)\lib
	pushd $(OBJDESTDIR) & lib /OUT:..\..\dist\lib\admb.lib /NOLOGO /IGNORE:4006 saflp-df1b2-separable*.obj saflp-linad99*.obj saflp-nh99*.obj saflp-tools99*.obj

admbopt:
	IF NOT EXIST $(OBJDESTDIR) md $(OBJDESTDIR)
	pushd df1b2-separable & ..\..\utilities\make CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_OPT)" PREFIX_OBJ="..\$(OBJDESTDIR)\optlp-df1b2-separable-" DESTDIR="..\$(DESTDIR)" --file=Makefile & popd
	pushd linad99 & ..\..\utilities\make CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_OPT)" PREFIX_OBJ="..\$(OBJDESTDIR)\optlp-linad99-" DESTDIR="..\$(DESTDIR)" --file=Makefile & popd
	pushd nh99 & ..\..\utilities\make CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_OPT)" PREFIX_OBJ="..\$(OBJDESTDIR)\optlp-nh99-" DESTDIR="..\$(DESTDIR)" --file=Makefile & popd
	pushd tools99 & ..\..\utilities\make CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_OPT)" PREFIX_OBJ="..\$(OBJDESTDIR)\optlp-tools99-" DESTDIR="..\$(DESTDIR)" --file=Makefile & popd
	IF NOT EXIST $(DESTDIR)\lib md $(DESTDIR)\lib
	pushd $(OBJDESTDIR) & lib /OUT:..\..\dist\lib\admbo.lib /NOLOGO /IGNORE:4006 optlp-df1b2-separable*.obj optlp-linad99*.obj optlp-nh99*.obj optlp-tools99*.obj


includes:
	IF NOT EXIST $(DESTDIR)\include md $(DESTDIR)\include
	copy df1b2-separable\df1b2fun.h $(DESTDIR)\include
	copy df1b2-separable\adpool.h $(DESTDIR)\include
	copy df1b2-separable\adrndeff.h $(DESTDIR)\include
	copy df1b2-separable\df1b2fnl.h $(DESTDIR)\include
	copy df1b2-separable\df3fun.h $(DESTDIR)\include
	copy df1b2-separable\df32fun.h $(DESTDIR)\include
	copy df1b2-separable\df1b2loc.h $(DESTDIR)\include
	copy linad99\fvar.hpp $(DESTDIR)\include
	copy linad99\d4arr.hpp $(DESTDIR)\include
	copy linad99\dfpool.h $(DESTDIR)\include
	copy linad99\factors.h $(DESTDIR)\include
	copy nh99\admodel.h $(DESTDIR)\include
	copy nh99\adsplus.h $(DESTDIR)\include
	copy nh99\spcomm.h $(DESTDIR)\include
	copy nh99\s.h $(DESTDIR)\include
	copy nh99\newredef.h $(DESTDIR)\include
	copy nh99\param_init_bounded_number_matrix.h $(DESTDIR)\include
	copy tools99\clist.h $(DESTDIR)\include
	copy tools99\cifstrem.h $(DESTDIR)\include
	copy tools99\adstring.hpp $(DESTDIR)\include
	copy tools99\admb_messages.h $(DESTDIR)\include

contrib: contribdirs libcontribsaf libcontribopt

contribdirs:
	IF NOT EXIST $(DESTDIR)\contrib\lib md $(DESTDIR)\contrib\lib
	IF NOT EXIST $(DESTDIR)\contrib\bin md $(DESTDIR)\contrib\bin

libcontribsaf:
	pushd ..\contrib& $(MAKE) ADMB_HOME="$(MAKEDIR)\$(DESTDIR)" CXXFLAGS="$(CXXFLAGS_SAF)" PREFIX_OBJ="..\$(OBJDESTDIR)\saflp-contrib-"& popd
	lib /OUT:$(DESTDIR)\contrib\lib\contrib.lib /NOLOGO /IGNORE:4006 $(OBJDESTDIR)\saflp-contrib*.obj

libcontribopt:
	pushd ..\contrib& $(MAKE) ADMB_HOME="$(MAKEDIR)\$(DESTDIR)" CXXFLAGS="$(CXXFLAGS_OPT)" PREFIX_OBJ="..\$(OBJDESTDIR)\optlp-contrib-"& popd
	lib /OUT:$(DESTDIR)\contrib\lib\contribo.lib /NOLOGO /IGNORE:4006 $(OBJDESTDIR)\optlp-contrib*.obj

tests:
	pushd ..\tests& $(MAKE) ADMB_HOME="$(MAKEDIR)\$(DESTDIR)"& popd

verify:
	pushd $(DESTDIR)\examples& $(MAKE) ADMB_HOME="$(MAKEDIR)\$(DESTDIR)" PATH="$(MAKEDIR)\$(DESTDIR)\bin;$(PATH)" OPTION=-s all& popd
	pushd $(DESTDIR) & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-saf.txt" & popd
	pushd $(DESTDIR)\examples& $(MAKE) ADMB_HOME="$(MAKEDIR)\$(DESTDIR)" PATH="$(MAKEDIR)\$(DESTDIR)\bin;$(PATH)" all& popd
	pushd $(DESTDIR) & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-opt.txt" & popd

clean:
	IF EXIST $(DESTDIR) rd /S /Q $(DESTDIR)
	IF EXIST $(OBJDESTDIR) rd /S /Q $(OBJDESTDIR)
	pushd df1b2-separable& $(MAKE) clean& popd
	pushd nh99& $(MAKE) clean& popd
	pushd ..\contrib& $(MAKE) clean& popd
	pushd ..\tests& $(MAKE) clean& popd
	del df1b2-separable\lex.yy.c
	del df1b2-separable\tpl2rem-winflex.obj
	del nh99\lex.yy.c
	del nh99\tpl2cpp-winflex.obj
