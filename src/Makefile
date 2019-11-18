SHELL=cmd

LEXDESTDIR=..\build\lex

#SAFE_ALL= /DSAFE_ALL

!IF ([cl /? 2>&1 | findstr /C:"Compiler Version 19." > nul] == 0)
CXXVERSION=-vc19
!ELSE
CXXVERSION=-vc
!ENDIF
!IF ([cl /? 2>&1 | findstr /C:" x64" > nul] == 0)
OSNAME=-winx64
!ELSEIF ([cl /? 2>&1 | findstr /C:" x86" > nul] == 0)
OSNAME=-winx86
!ELSE
OSNAME=-win
!ENDIF

!IF DEFINED(DEBUG)
DESTDIR=..\build\debug
OBJDESTDIR=..\build\objects$(OSNAME)$(CXXVERSION)\debug
CXXFLAGS_SAF=/nologo /W4 /wd6001 /wd4100 /wd4239 /GF /EHsc$(SAFE_ALL) /analyze:stacksize 50024 /D_USE_MATH_DEFINES /D_CRT_SECURE_NO_WARNINGS /D_CRT_NONSTDC_NO_DEPRECATE /I$(DESTDIR)\include
CXXFLAGS_OPT=/nologo /W4 /wd6001 /wd4100 /wd4239 /GF /EHsc /analyze:stacksize 50024 /D_USE_MATH_DEFINES /DOPT_LIB /D_CRT_SECURE_NO_WARNINGS /D_CRT_NONSTDC_NO_DEPRECATE /I$(DESTDIR)\include
!ELSE
DESTDIR=..\build\dist
OBJDESTDIR=..\build\objects$(OSNAME)$(CXXVERSION)\dist
CXXFLAGS_SAF=/nologo /O2 /W4 /wd6001 /wd4100 /wd4239 /GF /EHsc$(SAFE_ALL) /D_USE_MATH_DEFINES /D_CRT_SECURE_NO_WARNINGS /D_CRT_NONSTDC_NO_DEPRECATE /I$(DESTDIR)\include
CXXFLAGS_OPT=/nologo /O2 /W4 /wd6001 /wd4100 /wd4239 /GF /EHsc /DOPT_LIB /D_USE_MATH_DEFINES /D_CRT_SECURE_NO_WARNINGS /D_CRT_NONSTDC_NO_DEPRECATE /I$(DESTDIR)\include
!ENDIF

!INCLUDE df1b2-separable\objects.lst
!IF DEFINED(DEBUG)
!IF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx64"
OPTLP_DF1B2_SEPARABLE_OBJS=$(OBJ0: = ..\build\objects-winx64-vc19\debug\optlp-df1b2-separable-)
SAFLP_DF1B2_SEPARABLE_OBJS=$(OBJ0: = ..\build\objects-winx64-vc19\debug\saflp-df1b2-separable-)
!ELSEIF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx86"
OPTLP_DF1B2_SEPARABLE_OBJS=$(OBJ0: = ..\build\objects-winx86-vc19\debug\optlp-df1b2-separable-)
SAFLP_DF1B2_SEPARABLE_OBJS=$(OBJ0: = ..\build\objects-winx86-vc19\debug\saflp-df1b2-separable-)
!ELSE
OPTLP_DF1B2_SEPARABLE_OBJS=$(OBJ0: = ..\build\objects-win-vc\debug\optlp-df1b2-separable-)
SAFLP_DF1B2_SEPARABLE_OBJS=$(OBJ0: = ..\build\objects-win-vc\debug\saflp-df1b2-separable-)
!ENDIF
!ELSE
!IF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx64"
OPTLP_DF1B2_SEPARABLE_OBJS=$(OBJ0: = ..\build\objects-winx64-vc19\dist\optlp-df1b2-separable-)
SAFLP_DF1B2_SEPARABLE_OBJS=$(OBJ0: = ..\build\objects-winx64-vc19\dist\saflp-df1b2-separable-)
!ELSEIF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx86"
OPTLP_DF1B2_SEPARABLE_OBJS=$(OBJ0: = ..\build\objects-winx86-vc19\dist\optlp-df1b2-separable-)
SAFLP_DF1B2_SEPARABLE_OBJS=$(OBJ0: = ..\build\objects-winx86-vc19\dist\saflp-df1b2-separable-)
!ELSE
OPTLP_DF1B2_SEPARABLE_OBJS=$(OBJ0: = ..\build\objects-win-vc\dist\optlp-df1b2-separable-)
SAFLP_DF1B2_SEPARABLE_OBJS=$(OBJ0: = ..\build\objects-win-vc\dist\saflp-df1b2-separable-)
!ENDIF
!ENDIF

!INCLUDE linad99\objects.lst
!IF DEFINED(DEBUG)
!IF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx64"
OPTLP_LINAD99_OBJS=$(OBJ1: = ..\build\objects-winx64-vc19\debug\optlp-linad99-) $(OBJ2: = ..\build\objects-winx64-vc19\debug\optlp-linad99-) $(OBJ3: = ..\build\objects-winx64-vc19\debug\optlp-linad99-) $(OBJ4: = ..\build\objects-winx64-vc19\debug\optlp-linad99-)
SAFLP_LINAD99_OBJS=$(OBJ1: = ..\build\objects-winx64-vc19\debug\saflp-linad99-) $(OBJ2: = ..\build\objects-winx64-vc19\debug\saflp-linad99-) $(OBJ3: = ..\build\objects-winx64-vc19\debug\saflp-linad99-) $(OBJ4: = ..\build\objects-winx64-vc19\debug\saflp-linad99-) $(OBJ16: = ..\build\objects-winx64-vc19\debug\saflp-linad99-)
!ELSEIF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx86"
OPTLP_LINAD99_OBJS=$(OBJ1: = ..\build\objects-winx86-vc19\debug\optlp-linad99-) $(OBJ2: = ..\build\objects-winx86-vc19\debug\optlp-linad99-) $(OBJ3: = ..\build\objects-winx86-vc19\debug\optlp-linad99-) $(OBJ4: = ..\build\objects-winx86-vc19\debug\optlp-linad99-)
SAFLP_LINAD99_OBJS=$(OBJ1: = ..\build\objects-winx86-vc19\debug\saflp-linad99-) $(OBJ2: = ..\build\objects-winx86-vc19\debug\saflp-linad99-) $(OBJ3: = ..\build\objects-winx86-vc19\debug\saflp-linad99-) $(OBJ4: = ..\build\objects-winx86-vc19\debug\saflp-linad99-) $(OBJ16: = ..\build\objects-winx86-vc19\debug\saflp-linad99-)
!ELSE
OPTLP_LINAD99_OBJS=$(OBJ1: = ..\build\objects-win-vc\debug\optlp-linad99-) $(OBJ2: = ..\build\objects-win-vc\debug\optlp-linad99-) $(OBJ3: = ..\build\objects-win-vc\debug\optlp-linad99-) $(OBJ4: = ..\build\objects-win-vc\debug\optlp-linad99-)
SAFLP_LINAD99_OBJS=$(OBJ1: = ..\build\objects-win-vc\debug\saflp-linad99-) $(OBJ2: = ..\build\objects-win-vc\debug\saflp-linad99-) $(OBJ3: = ..\build\objects-win-vc\debug\saflp-linad99-) $(OBJ4: = ..\build\objects-win-vc\debug\saflp-linad99-) $(OBJ16: = ..\build\objects-win-vc\debug\saflp-linad99-)
!ENDIF
!IF DEFINED(TRAVIS)
!IF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx64"
SAFLP_LINAD99_OBJS1=$(OBJ1: = ..\build\objects-winx64-vc19\debug\saflp-linad99-)
SAFLP_LINAD99_OBJS3=$(OBJ3: = ..\build\objects-winx64-vc19\debug\saflp-linad99-)
SAFLP_LINAD99_OBJS2=$(OBJ2: = ..\build\objects-winx64-vc19\debug\saflp-linad99-) $(OBJ4: = ..\build\objects-winx64-vc19\debug\saflp-linad99-) $(OBJ16: = ..\build\objects-winx64-vc19\debug\saflp-linad99-)
!ELSEIF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx86"
SAFLP_LINAD99_OBJS1=$(OBJ1: = ..\build\objects-winx86-vc19\debug\saflp-linad99-)
SAFLP_LINAD99_OBJS3=$(OBJ3: = ..\build\objects-winx86-vc19\debug\saflp-linad99-)
SAFLP_LINAD99_OBJS2=$(OBJ2: = ..\build\objects-winx86-vc19\debug\saflp-linad99-) $(OBJ4: = ..\build\objects-winx86-vc19\debug\saflp-linad99-) $(OBJ16: = ..\build\objects-winx86-vc19\debug\saflp-linad99-)
!ELSE
SAFLP_LINAD99_OBJS1=$(OBJ1: = ..\build\objects-win-vc\debug\saflp-linad99-)
SAFLP_LINAD99_OBJS3=$(OBJ3: = ..\build\objects-win-vc\debug\saflp-linad99-)
SAFLP_LINAD99_OBJS2=$(OBJ2: = ..\build\objects-win-vc\debug\saflp-linad99-) $(OBJ4: = ..\build\objects-win-vc\debug\saflp-linad99-) $(OBJ16: = ..\build\objects-win-vc\debug\saflp-linad99-)
!ELSE
!ENDIF
!ENDIF
!ELSE
!IF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx64"
OPTLP_LINAD99_OBJS=$(OBJ1: = ..\build\objects-winx64-vc19\dist\optlp-linad99-) $(OBJ2: = ..\build\objects-winx64-vc19\dist\optlp-linad99-) $(OBJ3: = ..\build\objects-winx64-vc19\dist\optlp-linad99-) $(OBJ4: = ..\build\objects-winx64-vc19\dist\optlp-linad99-)
SAFLP_LINAD99_OBJS=$(OBJ1: = ..\build\objects-winx64-vc19\dist\saflp-linad99-) $(OBJ2: = ..\build\objects-winx64-vc19\dist\saflp-linad99-) $(OBJ3: = ..\build\objects-winx64-vc19\dist\saflp-linad99-) $(OBJ4: = ..\build\objects-winx64-vc19\dist\saflp-linad99-) $(OBJ16: = ..\build\objects-winx64-vc19\dist\saflp-linad99-)
!ELSEIF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx86"
OPTLP_LINAD99_OBJS=$(OBJ1: = ..\build\objects-winx86-vc19\dist\optlp-linad99-) $(OBJ2: = ..\build\objects-winx86-vc19\dist\optlp-linad99-) $(OBJ3: = ..\build\objects-winx86-vc19\dist\optlp-linad99-) $(OBJ4: = ..\build\objects-winx86-vc19\dist\optlp-linad99-)
SAFLP_LINAD99_OBJS=$(OBJ1: = ..\build\objects-winx86-vc19\dist\saflp-linad99-) $(OBJ2: = ..\build\objects-winx86-vc19\dist\saflp-linad99-) $(OBJ3: = ..\build\objects-winx86-vc19\dist\saflp-linad99-) $(OBJ4: = ..\build\objects-winx86-vc19\dist\saflp-linad99-) $(OBJ16: = ..\build\objects-winx86-vc19\dist\saflp-linad99-)
!ELSE
OPTLP_LINAD99_OBJS=$(OBJ1: = ..\build\objects-win-vc\dist\optlp-linad99-) $(OBJ2: = ..\build\objects-win-vc\dist\optlp-linad99-) $(OBJ3: = ..\build\objects-win-vc\dist\optlp-linad99-) $(OBJ4: = ..\build\objects-win-vc\dist\optlp-linad99-)
SAFLP_LINAD99_OBJS=$(OBJ1: = ..\build\objects-win-vc\dist\saflp-linad99-) $(OBJ2: = ..\build\objects-win-vc\dist\saflp-linad99-) $(OBJ3: = ..\build\objects-win-vc\dist\saflp-linad99-) $(OBJ4: = ..\build\objects-win-vc\dist\saflp-linad99-) $(OBJ16: = ..\build\objects-win-vc\dist\saflp-linad99-)
!ENDIF
!ENDIF

!INCLUDE nh99\objects.lst
!IF DEFINED(DEBUG)
!IF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx64"
OPTLP_NH99_OBJS=$(OBJ6: = ..\build\objects-winx64-vc19\debug\optlp-nh99-)
SAFLP_NH99_OBJS=$(OBJ6: = ..\build\objects-winx64-vc19\debug\saflp-nh99-)
!ELSEIF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx86"
OPTLP_NH99_OBJS=$(OBJ6: = ..\build\objects-winx86-vc19\debug\optlp-nh99-)
SAFLP_NH99_OBJS=$(OBJ6: = ..\build\objects-winx86-vc19\debug\saflp-nh99-)
!ELSE
OPTLP_NH99_OBJS=$(OBJ6: = ..\build\objects-win-vc\debug\optlp-nh99-)
SAFLP_NH99_OBJS=$(OBJ6: = ..\build\objects-win-vc\debug\saflp-nh99-)
!ENDIF
!ELSE
!IF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx64"
OPTLP_NH99_OBJS=$(OBJ6: = ..\build\objects-winx64-vc19\dist\optlp-nh99-)
SAFLP_NH99_OBJS=$(OBJ6: = ..\build\objects-winx64-vc19\dist\saflp-nh99-)
!ELSEIF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx86"
OPTLP_NH99_OBJS=$(OBJ6: = ..\build\objects-winx86-vc19\dist\optlp-nh99-)
SAFLP_NH99_OBJS=$(OBJ6: = ..\build\objects-winx86-vc19\dist\saflp-nh99-)
!ELSE
OPTLP_NH99_OBJS=$(OBJ6: = ..\build\objects-win-vc\dist\optlp-nh99-)
SAFLP_NH99_OBJS=$(OBJ6: = ..\build\objects-win-vc\dist\saflp-nh99-)
!ENDIF
!ENDIF

!INCLUDE tools99\objects.lst
!IF DEFINED(DEBUG)
!IF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx64"
OPTLP_TOOLS99_OBJS=$(OBJ7: = ..\build\objects-winx64-vc19\debug\optlp-tools99-)
SAFLP_TOOLS99_OBJS=$(OBJ7: = ..\build\objects-winx64-vc19\debug\saflp-tools99-)
!ELSEIF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx86"
OPTLP_TOOLS99_OBJS=$(OBJ7: = ..\build\objects-winx86-vc19\debug\optlp-tools99-)
SAFLP_TOOLS99_OBJS=$(OBJ7: = ..\build\objects-winx86-vc19\debug\saflp-tools99-)
!ELSE
OPTLP_TOOLS99_OBJS=$(OBJ7: = ..\build\objects-win-vc\debug\optlp-tools99-)
SAFLP_TOOLS99_OBJS=$(OBJ7: = ..\build\objects-win-vc\debug\saflp-tools99-)
!ENDIF
!ELSE
!IF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx64"
OPTLP_TOOLS99_OBJS=$(OBJ7: = ..\build\objects-winx64-vc19\dist\optlp-tools99-)
SAFLP_TOOLS99_OBJS=$(OBJ7: = ..\build\objects-winx64-vc19\dist\saflp-tools99-)
!ELSEIF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx86"
OPTLP_TOOLS99_OBJS=$(OBJ7: = ..\build\objects-winx86-vc19\dist\optlp-tools99-)
SAFLP_TOOLS99_OBJS=$(OBJ7: = ..\build\objects-winx86-vc19\dist\saflp-tools99-)
!ELSE
OPTLP_TOOLS99_OBJS=$(OBJ7: = ..\build\objects-win-vc\dist\optlp-tools99-)
SAFLP_TOOLS99_OBJS=$(OBJ7: = ..\build\objects-win-vc\dist\saflp-tools99-)
!ENDIF
!ENDIF

all: dist
	@rem pushd $(DESTDIR) & cscript ..\..\scripts\create-admb-shortcut.vbs & popd

shared: all
	IF EXIST $(DESTDIR)\lib\admb.dll del $(DESTDIR)\lib\admb.dll
	pushd $(OBJDESTDIR) & link /DLL /OUT:..\..\$(DESTDIR)\lib\admb.dll /NOLOGO /IGNORE:4006 saflp-df1b2-separable*.obj saflp-linad99*.obj saflp-nh99*.obj saflp-tools99*.obj saflp-sparse*.obj
	IF EXIST $(DESTDIR)\lib\admbo.dll del $(DESTDIR)\lib\admbo.dll
	pushd $(OBJDESTDIR) & link /DLL /OUT:..\..\$(DESTDIR)\lib\admbo.dll /NOLOGO /IGNORE:4006 optlp-df1b2-separable*.obj optlp-linad99*.obj optlp-nh99*.obj optlp-tools99*.obj optlp-sparse*.obj
	@echo ADMB shared build completed.

dist: bins
	IF NOT EXIST $(DESTDIR) md $(DESTDIR)
	copy ..\LICENSE.txt $(DESTDIR)
	copy ..\CHANGES.txt $(DESTDIR)
	copy ..\README.txt $(DESTDIR)
	copy ..\VERSION $(DESTDIR)
	$(MAKE) lexfiles

bins: libs
	IF NOT EXIST $(DESTDIR)\bin md $(DESTDIR)\bin
	echo set ADMB_CFG_CXX=$(CXX)>$(DESTDIR)\bin\admb-cfg.bat
	echo set ADMB_CFG_CXXFLAGS=$(CXXFLAGS)>>$(DESTDIR)\bin\admb-cfg.bat
	echo set ADMB_CFG_LDFLAGS=$(LDFLAGS)>>$(DESTDIR)\bin\admb-cfg.bat
	copy df1b2-separable\sed* $(DESTDIR)\bin
	if exist ..\admb del ..\admb
	copy ..\scripts\admb\admb.bat $(DESTDIR)\bin\admb.cmd
!IF DEFINED(DEBUG)
	copy ..\scripts\admb\root-admb-debug.bat ..\admb.cmd
	copy ..\scripts\admb\root-admb-debug.bat $(DESTDIR)\admb.cmd
!ELSE
	copy ..\scripts\admb\root-admb.bat ..\admb.cmd
	copy ..\scripts\admb\root-admb.bat $(DESTDIR)\admb.cmd
!ENDIF
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
	..\utilities\flex -o$(LEXDESTDIR)\lex.yy.c df1b2-separable\tpl2rem.lex
	..\utilities\sed -f df1b2-separable\sedflex $(LEXDESTDIR)\lex.yy.c > $@

libs: objects
	IF NOT EXIST $(DESTDIR)\lib md $(DESTDIR)\lib
	IF EXIST $(DESTDIR)\lib\admb$(OSNAME)$(CXXVERSION).lib del $(DESTDIR)\lib\admb$(OSNAME)$(CXXVERSION).lib
	pushd $(OBJDESTDIR) & lib /OUT:..\..\$(DESTDIR)\lib\admb$(OSNAME)$(CXXVERSION).lib /NOLOGO /IGNORE:4006 saflp-df1b2-separable*.obj saflp-linad99*.obj saflp-nh99*.obj saflp-tools99*.obj saflp-sparse*.obj
	IF EXIST $(DESTDIR)\lib\admbo$(OSNAME)$(CXXVERSION).lib del $(DESTDIR)\lib\admbo$(OSNAME)$(CXXVERSION).lib
	pushd $(OBJDESTDIR) & lib /OUT:..\..\$(DESTDIR)\lib\admbo$(OSNAME)$(CXXVERSION).lib /NOLOGO /IGNORE:4006 optlp-df1b2-separable*.obj optlp-linad99*.obj optlp-nh99*.obj optlp-tools99*.obj optlp-sparse*.obj

!IF DEFINED(SAFE_ONLY)
objects: includes $(SAFLP_DF1B2_SEPARABLE_OBJS) $(SAFLP_LINAD99_OBJS) $(SAFLP_NH99_OBJS) $(SAFLP_TOOLS99_OBJS) $(OBJDESTDIR)\saflp-sparse-hs_sparse.obj
!ELSE
objects: includes $(OPTLP_DF1B2_SEPARABLE_OBJS) $(SAFLP_DF1B2_SEPARABLE_OBJS) $(OPTLP_LINAD99_OBJS) $(SAFLP_LINAD99_OBJS) $(OPTLP_NH99_OBJS) $(SAFLP_NH99_OBJS) $(OPTLP_TOOLS99_OBJS) $(SAFLP_TOOLS99_OBJS) $(OBJDESTDIR)\optlp-sparse-hs_sparse.obj $(OBJDESTDIR)\saflp-sparse-hs_sparse.obj
!ENDIF
!IF DEFINED(DEBUG)
!IF DEFINED(TRAVIS)
objects1: includes $(SAFLP_LINAD99_OBJS1)
objects3: includes $(SAFLP_LINAD99_OBJS3)
objects2: includes $(SAFLP_DF1B2_SEPARABLE_OBJS) $(SAFLP_LINAD99_OBJS2) $(SAFLP_NH99_OBJS) $(SAFLP_TOOLS99_OBJS) $(OBJDESTDIR)\saflp-sparse-hs_sparse.obj

$(SAFLP_LINAD99_OBJS1):: $(@B:saflp-linad99-=linad99\).cpp
	$(CXX) /c $(CXXFLAGS_SAF) /Fo$@ $?
$(SAFLP_LINAD99_OBJS2):: $(@B:saflp-linad99-=linad99\).cpp
	$(CXX) /c $(CXXFLAGS_SAF) /Fo$@ $?
$(SAFLP_LINAD99_OBJS3):: $(@B:saflp-linad99-=linad99\).cpp
	$(CXX) /c $(CXXFLAGS_SAF) /Fo$@ $?
!ENDIF
!ENDIF

$(SAFLP_DF1B2_SEPARABLE_OBJS):: $(@B:saflp-df1b2-separable-=df1b2-separable\).cpp
	$(CXX) /c $(CXXFLAGS_SAF) /Fo$@ $?

$(OPTLP_DF1B2_SEPARABLE_OBJS):: $(@B:optlp-df1b2-separable-=df1b2-separable\).cpp
	$(CXX) /c $(CXXFLAGS_OPT) /Fo$@ $?

$(SAFLP_LINAD99_OBJS):: $(@B:saflp-linad99-=linad99\).cpp
	$(CXX) /c $(CXXFLAGS_SAF) /Fo$@ $?

$(OPTLP_LINAD99_OBJS):: $(@B:optlp-linad99-=linad99\).cpp
	$(CXX) /c $(CXXFLAGS_OPT) /Fo$@ $?

$(SAFLP_NH99_OBJS):: $(@B:saflp-nh99-=nh99\).cpp
	$(CXX) /c $(CXXFLAGS_SAF) /Fo$@ $?

$(OPTLP_NH99_OBJS):: $(@B:optlp-nh99-=nh99\).cpp
	$(CXX) /c $(CXXFLAGS_OPT) /Fo$@ $?

$(SAFLP_TOOLS99_OBJS):: $(@B:saflp-tools99-=tools99\).cpp
	$(CXX) /c $(CXXFLAGS_SAF) /Fo$@ $?

$(OPTLP_TOOLS99_OBJS):: $(@B:optlp-tools99-=tools99\).cpp
	$(CXX) /c $(CXXFLAGS_OPT) /Fo$@ $?

$(OBJDESTDIR)\optlp-sparse-hs_sparse.obj: sparse\hs_sparse.cpp
	$(CXX) /c $(CXXFLAGS_OPT) /Fo$@ $?

$(OBJDESTDIR)\saflp-sparse-hs_sparse.obj: sparse\hs_sparse.cpp
	$(CXX) /c $(CXXFLAGS_SAF) /Fo$@ $?

includes: objdestdir
	IF NOT EXIST $(DESTDIR)\include md $(DESTDIR)\include
	copy df1b2-separable\df1b2fun.h $(DESTDIR)\include
	copy df1b2-separable\adpool.h $(DESTDIR)\include
	copy df1b2-separable\adrndeff.h $(DESTDIR)\include
	copy df1b2-separable\df1b2fnl.h $(DESTDIR)\include
	copy df1b2-separable\df3fun.h $(DESTDIR)\include
	copy df1b2-separable\df32fun.h $(DESTDIR)\include
	copy df1b2-separable\df33fun.h $(DESTDIR)\include
	copy df1b2-separable\df1b2loc.h $(DESTDIR)\include
	copy linad99\df11fun.h $(DESTDIR)\include
	copy linad99\df12fun.h $(DESTDIR)\include
	copy linad99\df13fun.h $(DESTDIR)\include
	copy linad99\fvar.hpp $(DESTDIR)\include
	copy linad99\gradient_structure.h $(DESTDIR)\include
	copy linad99\dvector.h $(DESTDIR)\include
	copy linad99\ivector.h $(DESTDIR)\include
	copy linad99\imatrix.h $(DESTDIR)\include
	copy linad99\vector_shapex.h $(DESTDIR)\include
	copy linad99\dfpool.h $(DESTDIR)\include
	copy linad99\factors.h $(DESTDIR)\include
	copy nh99\admodel.h $(DESTDIR)\include
	copy nh99\param_init_bounded_number_matrix.h $(DESTDIR)\include
	copy tools99\clist.h $(DESTDIR)\include
	copy tools99\cifstrem.h $(DESTDIR)\include
	copy tools99\adstring.hpp $(DESTDIR)\include
	copy tools99\admb_messages.h $(DESTDIR)\include
	copy tools99\Vectorize.hpp $(DESTDIR)\include
	copy tools99\tiny_ad.hpp $(DESTDIR)\include
	copy tools99\tiny_vec.hpp $(DESTDIR)\include
	copy tools99\tiny_wrap.hpp $(DESTDIR)\include
	copy tools99\integrate.cpp $(DESTDIR)\include
	copy tools99\integrate.hpp $(DESTDIR)\include
	copy tools99\integrate_wrap.hpp $(DESTDIR)\include
	copy tools99\adjson.h $(DESTDIR)\include
	if not exist $(DESTDIR)\include\contrib md $(DESTDIR)\include\contrib

objdestdir:
	IF NOT EXIST $(OBJDESTDIR) md $(OBJDESTDIR)

install:
	@echo "Read INSTALL.txt for installation instructions."
copy:
	IF NOT EXIST $(DESTDIR) md $(DESTDIR)\docs
	IF NOT EXIST $(DESTDIR)\docs xcopy /I /E /Y ..\docs $(DESTDIR)\docs
	IF NOT EXIST $(DESTDIR) md $(DESTDIR)\examples
	IF NOT EXIST $(DESTDIR)\examples xcopy /I /E /Y ..\examples $(DESTDIR)\examples
	IF NOT EXIST $(DESTDIR) md $(DESTDIR)\scripts
	IF NOT EXIST $(DESTDIR)\scripts xcopy /I /E /Y ..\scripts $(DESTDIR)\scripts
	pushd ..\scripts & $(MAKE) clean
	IF NOT EXIST $(DESTDIR) md $(DESTDIR)\tests
	IF NOT EXIST $(DESTDIR)\tests xcopy /I /E /Y ..\tests $(DESTDIR)\tests
	IF NOT EXIST $(DESTDIR) md $(DESTDIR)\src
	IF NOT EXIST $(DESTDIR)\src xcopy /I /E /Y ..\src $(DESTDIR)\src
	IF NOT EXIST $(DESTDIR) md $(DESTDIR)\utilities
	IF NOT EXIST $(DESTDIR)\utilities xcopy /I /E /Y ..\src $(DESTDIR)\utilities
	pushd ..\contrib & $(MAKE) copy
	pushd ..\tests & $(MAKE) copy
	copy ..\Makefile $(DESTDIR)

clean:
	if exist ..\benchmarks-opt.txt del ..\benchmarks-opt.txt
	if exist ..\benchmarks-saf.txt del ..\benchmarks-saf.txt
	if exist ..\build rd /S /Q ..\build
	if exist ..\admb del ..\admb
	if exist ..\admb.cmd del ..\admb.cmd
	if exist ..\admb.bat del ..\admb.bat
	if exist ..\admb.sh del ..\admb.sh
	if exist ..\admb.zip del ..\admb.zip

check:
	@echo "SHELL: $(SHELL)"
	@echo "PATH: $(PATH)"
	@echo "TERM: $(TERM)"
	@echo "MAKE: $(MAKE)"
	@echo "CXX: $(CXX)"
	@echo "OS: $(OS)"
	@echo "OSTYPE: $(OSTYPE)"
