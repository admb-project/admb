DESTDIR=..\build\dist
OBJDESTDIR=..\build\objects\dist
LEXDESTDIR=..\build\lex

!IF DEFINED(DEBUG)
CXXFLAGS_SAF=/nologo /G7 /W4 /GF /EHsc /DSAFE_ALL /DUSE_LAPLACE /DWIN32 /D__MSVC32__=8 /I..\$(DESTDIR)\include
CXXFLAGS_OPT=/nologo /G7 /W4 /GF /EHsc /DOPT_LIB  /DUSE_LAPLACE /DWIN32 /D__MSVC32__=8 /I..\$(DESTDIR)\include
!ELSE
CXXFLAGS_SAF=/nologo /O2 /W4 /GF /EHsc /DSAFE_ALL /DUSE_LAPLACE /DWIN32 /D__MSVC32__=8 /I..\$(DESTDIR)\include
CXXFLAGS_OPT=/nologo /O2 /W4 /GF /EHsc /DOPT_LIB  /DUSE_LAPLACE /DWIN32 /D__MSVC32__=8 /I..\$(DESTDIR)\include
!ENDIF

all: dist bins contrib
	pushd $(DESTDIR) & cscript ..\..\scripts\create-admb-shortcut.vbs & popd

dist: srcs

srcs:
	IF NOT EXIST $(DESTDIR) md $(DESTDIR)
	copy ..\LICENSE.txt $(DESTDIR)
	copy ..\CHANGES.txt $(DESTDIR)
	copy ..\README.txt $(DESTDIR)
	copy ..\VERSION $(DESTDIR)
	IF NOT EXIST $(DESTDIR) md $(DESTDIR)\contrib
	IF NOT EXIST $(DESTDIR)\contrib xcopy /I /E /Y ..\contrib $(DESTDIR)\contrib
	IF NOT EXIST $(DESTDIR) md $(DESTDIR)\docs
	IF NOT EXIST $(DESTDIR)\docs xcopy /I /E /Y ..\docs $(DESTDIR)\docs
	IF NOT EXIST $(DESTDIR) md $(DESTDIR)\examples
	IF NOT EXIST $(DESTDIR)\examples xcopy /I /E /Y ..\examples $(DESTDIR)\examples
	IF NOT EXIST $(DESTDIR) md $(DESTDIR)\scripts
	IF NOT EXIST $(DESTDIR)\scripts xcopy /I /E /Y ..\scripts $(DESTDIR)\scripts
	IF NOT EXIST $(DESTDIR) md $(DESTDIR)\tests
	IF NOT EXIST $(DESTDIR)\tests xcopy /I /E /Y ..\tests $(DESTDIR)\tests
	IF NOT EXIST $(DESTDIR) md $(DESTDIR)\utilities
	IF NOT EXIST $(DESTDIR)\utilities xcopy /I /E /Y ..\utilities $(DESTDIR)\utilities
	IF NOT EXIST $(DESTDIR) md $(DESTDIR)\src
	IF NOT EXIST $(DESTDIR)\src xcopy /I /E /Y ..\src $(DESTDIR)\src

bins: lexfiles libs
	IF NOT EXIST $(DESTDIR)\bin md $(DESTDIR)\bin
	copy df1b2-separable\sed* $(DESTDIR)\bin
	copy ..\scripts\cl\*.bat $(DESTDIR)\bin
	copy ..\scripts\admb\admb.bat $(DESTDIR)\bin
	copy ..\scripts\admb\root-admb.bat ..\admb.bat
	copy ..\utilities\sed.exe $(DESTDIR)\bin
	copy ..\utilities\*.dll $(DESTDIR)\bin

lexfiles: lexdestdir $(DESTDIR)\bin\tpl2cpp.exe $(DESTDIR)\bin\tpl2rem.exe

lexdestdir:
	IF NOT EXIST $(LEXDESTDIR) md $(LEXDESTDIR)
	IF NOT EXIST $(DESTDIR)\bin md $(DESTDIR)\bin

$(DESTDIR)\bin\tpl2cpp.exe: $(LEXDESTDIR)\tpl2cpp.c
	$(CC) /nologo /TC /Fo$(LEXDESTDIR)\ /Fe$@ $(LEXDESTDIR)\tpl2cpp.c

$(LEXDESTDIR)\tpl2cpp.c: nh99\tpl2cpp.lex
	..\utilities\flex -o$(LEXDESTDIR)\lex.yy.c nh99\tpl2cpp.lex
	..\utilities\sed -f nh99\sedflex $(LEXDESTDIR)\lex.yy.c > $@

$(DESTDIR)\bin\tpl2rem.exe: $(LEXDESTDIR)\tpl2rem.c
	$(CC) /nologo /TC /Fo$(LEXDESTDIR)\ /Fe$@ $(LEXDESTDIR)\tpl2rem.c

$(LEXDESTDIR)\tpl2rem.c: df1b2-separable\tpl2rem.lex
	..\utilities\flex -w -o$(LEXDESTDIR)\lex.yy.c df1b2-separable\tpl2rem.lex 
	..\utilities\sed -f df1b2-separable\sedflex $(LEXDESTDIR)\lex.yy.c > $@

lexfiles2:
	pushd nh99& ..\..\utilities\make  --file=Makefile CC="$(CC)" DESTDIR="..\$(DESTDIR)" bins& popd
	pushd df1b2-separable& ..\..\utilities\make --file=Makefile CC="$(CC)" DESTDIR="..\$(DESTDIR)" bins& popd

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
	IF NOT EXIST $(DESTDIR)\contrib\include md $(DESTDIR)\contrib\include

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

install:
	@echo "Read INSTALL.txt for installation instructions."

clean:
	IF EXIST $(DESTDIR) rd /S /Q $(DESTDIR)
	IF EXIST $(OBJDESTDIR) rd /S /Q $(OBJDESTDIR)
	pushd ..\contrib& $(MAKE) clean& popd
	pushd ..\tests& $(MAKE) clean& popd
