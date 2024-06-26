DEFAULT_CPPSTD_VER=17
ifndef ADMB_VER
  ADMB_VER=admb
endif
ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifndef TERM
      export SHELL=cmd
      CMDSHELL=cmd
    endif
  endif
  ifeq ($(CMDSHELL),cmd)
    ifeq ($(wildcard ..\utilities\mingw\bin\g++.exe),..\utilities\mingw\bin\g++.exe)
      PATH:=$(abspath ..\utilities\mingw\bin);$(PATH)
    endif
  else
    ifeq ($(wildcard ../utilities/mingw/bin/g++.exe),../utilities/mingw/bin/g++.exe)
      PATH:=$(abspath ../utilities/mingw/bin);$(PATH)
    endif
  endif
endif
ifeq ($(CMDSHELL),cmd)
  DIST=..\build\$(ADMB_VER)
  LIBSDIR=$(DIST)\lib
  LIBSDIR:=$(addsuffix \,$(LIBSDIR))
  OBJSDIR=..\build\objects
  ifeq ($(CXX),g++)
    ifeq ($(findstring g++.exe,$(shell where g++.exe 2>&1 | findstr g++.exe)),g++.exe)
      ifeq ($(findstring x86_64,$(shell g++ -dumpmachine)),x86_64)
        OSNAME=-mingw64
      else
        OSNAME=-mingw32
      endif
      CXXVERSION=-g++$(basename $(basename $(shell g++ -dumpversion)))
    endif
  endif
  ifeq ($(findstring clang++,$(CXX)),clang++)
    ifneq ($(findstring clang++.exe,$(shell where clang++.exe 2>&1 | findstr clang++.exe)),clang++.exe)
      $(warning "Warning: Unable to find clang++ compiler.")
    endif
    ifeq ($(findstring x86_64,$(shell $(CXX) -dumpmachine)),x86_64)
      OSNAME=-win64
    else
      OSNAME=-win32
    endif
    CXXVERSION=-clang++$(basename $(basename $(shell $(CXX) -dumpversion)))
  endif
  ifdef SHARED
  OBJSDIR:=$(addsuffix $(OSNAME)$(CXXVERSION)-shared,$(OBJSDIR))
  else
  OBJSDIR:=$(addsuffix $(OSNAME)$(CXXVERSION),$(OBJSDIR))
  endif
  ifdef DEBUG
  OBJSDIR:=$(addsuffix -debug,$(OBJSDIR))
  endif
  OBJSDIR_:=$(OBJSDIR)
  OBJSDIR:=$(addsuffix \,$(OBJSDIR))
  ADMB_VERSION:=$(shell if exist ..\VERSION.txt type ..\VERSION.txt)
else
  ifndef INSTALL_DIR
    INSTALL_DIR=/usr/local/
  endif
  DIST=../build/$(ADMB_VER)
  LIBSDIR=$(DIST)/lib/
  ifeq ($(OS),Windows_NT)
    UNAME_S=_NT
  else
    UNAME_S := $(shell uname -s)
  endif
  ifeq ($(UNAME_S),Linux)
    ifeq (i686,$(findstring i686,$(shell $(CXX) -dumpmachine)))
      OSNAME=-i686-linux
    else
      ifeq (x86_64,$(findstring x86_64,$(shell $(CXX) -dumpmachine)))
        OSNAME=-x86_64-linux
      else
        OSNAME=-arm64-linux
      endif
    endif
  endif
  ifeq ($(UNAME_S),Darwin)
    ifeq (i686,$(findstring i686,$(shell $(CXX) -dumpmachine)))
      OSNAME=-i686-macos
    else
      ifeq (x86_64,$(findstring x86_64,$(shell $(CXX) -dumpmachine)))
        OSNAME=-x86_64-macos
      else
        OSNAME=-arm64-macos
      endif
    endif
  endif
  ifeq ($(findstring _NT,$(UNAME_S)),_NT)
    ifeq ($(CXX),g++)
      ifeq ($(findstring g++.exe,$(shell where g++.exe 2>&1 | findstr g++.exe)),g++.exe)
        ifeq ($(findstring x86_64,$(shell g++ -dumpmachine)),x86_64)
          OSNAME=-mingw64
        else
          OSNAME=-mingw32
        endif
      endif
    endif
    ifeq ($(findstring clang++,$(CXX)),clang++)
      ifeq ($(findstring x86_64,$(shell clang++ -dumpmachine)),x86_64)
        OSNAME=-win64
      else
        OSNAME=-win32
      endif
    endif
  endif
  ifndef OSNAME
    $(warning Unknown UNAME_S = "$(UNAME_S)" results in empty OSNAME.)
  else
    ifeq ($(findstring g++,$(CXX)),g++)
      ifeq ($(UNAME_S),Darwin)
        ifeq ($(findstring Homebrew,$(shell $(CXX) --version)),Homebrew)
          CXXVERSION=-g++$(basename $(basename $(shell $(CXX) -dumpversion)))
        else
          ifeq (clang-10,$(findstring clang-10,$(shell $(CXX) --version)))
            CXXVERSION=-clang10
          else ifeq (clang-11,$(findstring clang-11,$(shell $(CXX) --version)))
            CXXVERSION=-clang11
          else
            CXXVERSION=-clang
          endif
        endif
      else
        CXXVERSION=-g++$(basename $(basename $(shell $(CXX) -dumpversion)))
      endif
    endif
    ifeq ($(findstring clang++,$(CXX)),clang++)
      CXXVERSION=-clang++$(basename $(basename $(shell $(CXX) -dumpversion)))
    endif
    ifeq ($(findstring c++,$(CXX)),c++)
      ifeq ($(UNAME_S),Darwin)
        ifeq (clang-10,$(findstring clang-10,$(shell $(CXX) --version)))
          CXXVERSION=-clang10
        else ifeq (clang-11,$(findstring clang-11,$(shell $(CXX) --version)))
          CXXVERSION=-clang11
        else
          CXXVERSION=-clang
        endif
      else
        CXXVERSION=-c++$(basename $(basename $(shell $(CXX) -dumpversion)))
      endif
    endif
    ifeq ($(CXX),analyze-c++)
      CXXVERSION=-analyze-c++$(basename $(basename $(shell $(CXX) -dumpversion)))
    endif
    ifeq ($(CXX),icpc)
      CXXVERSION=-icpc$(basename $(basename $(basename $(shell $(CXX) -dumpversion))))
    endif
    ifndef CXXVERSION
      $(warning Unknown CXX = "$(CXX)" results in empty CXXVERSION.)
    endif
    ifdef SHARED
      OBJSDIR=../build/objects$(OSNAME)$(CXXVERSION)-shared
    else
      OBJSDIR=../build/objects$(OSNAME)$(CXXVERSION)
    endif
    ifeq ($(DEBUG),yes)
      OBJSDIR:=$(sort $(addsuffix -debug, $(OBJSDIR)))
    endif
    OBJSDIR_:=$(OBJSDIR)
    OBJSDIR:=$(sort $(addsuffix /, $(OBJSDIR)))
    ADMB_VERSION:=$(shell cat ../VERSION.txt)
  endif
endif

ifdef CXX
  USER_CXX:= $(CXX)
endif

ifdef CXXFLAGS
  USER_CXXFLAGS:= $(CXXFLAGS)
endif

ifdef LDFLAGS
  USER_LDFLAGS:= $(LDFLAGS)
endif

ADCXXFLAGS=
ifdef SHARED
  ifneq ($(OS),Windows_NT)
    ADCXXFLAGS:= -fPIC $(ADCXXFLAGS)
  endif
endif

ifdef DEBUG
  ADCXXFLAGS:= -g $(ADCXXFLAGS)
else
  ifeq ($(CXX),openCC)
    ADCXXFLAGS:= -O2 $(ADCXXFLAGS)
  else
    ifneq ($(CXX),icpc)
      ADCXXFLAGS:= -O3 $(ADCXXFLAGS)
    endif
  endif
endif

ifneq ($(CXX),CC)
ADCXXFLAGS:= $(ADCXXFLAGS) -Wall -Wextra -Wconversion
endif

ifeq ($(CMDSHELL),cmd)
  ifeq ($(CXX),g++)
    ifeq ($(findstring g++.exe,$(shell where g++.exe 2>&1 | findstr g++.exe)),g++.exe)
      GCCMAJVER:="GCCVER$(shell gcc -dumpversion)"
      ifeq (GCCVER4,$(findstring GCCVER4,$(GCCMAJVER)))
        ADCXXFLAGS:= -std=c++11 $(ADCXXFLAGS)
      else ifeq (GCCVER5,$(findstring GCCVER5,$(GCCMAJVER)))
        ADCXXFLAGS:= -std=c++11 $(ADCXXFLAGS)
      else ifeq (GCCVER6,$(findstring GCCVER6,$(GCCMAJVER)))
        ADCXXFLAGS:= -std=c++11 $(ADCXXFLAGS)
      else ifeq (GCCVER7,$(findstring GCCVER7,$(GCCMAJVER)))
        ADCXXFLAGS:= -std=c++11 $(ADCXXFLAGS)
      else ifeq (GCCVER8,$(findstring GCCVER8,$(GCCMAJVER)))
        ADCXXFLAGS:= -std=c++14 $(ADCXXFLAGS)
      else ifeq (GCCVER9,$(findstring GCCVER9,$(GCCMAJVER)))
        ADCXXFLAGS:= -std=c++17 $(ADCXXFLAGS)
      else ifeq (GCCVER10,$(findstring GCCVER10,$(GCCMAJVER)))
        ADCXXFLAGS:= -std=c++17 $(ADCXXFLAGS)
      else
        ADCXXFLAGS:= -std=c++$(DEFAULT_CPPSTD_VER) $(ADCXXFLAGS)
      endif
    endif
  endif
else
  ifeq ("$(UNAME_S)","Darwin")
    ADCXXFLAGS:= -std=c++$(DEFAULT_CPPSTD_VER) $(ADCXXFLAGS)
  else
    ifeq ($(findstring clang++,$(CXX)),clang++)
      ADCXXFLAGS:= -std=c++17 $(ADCXXFLAGS)
    else ifeq ($(CXX),icpc)
      ICPCMAJVER:=$(shell icpc -dumpversion | cut -f1 -d. )
      ifeq ("$(ICPCMAJVER)","17")
        ADCXXFLAGS:= -std=c++14 $(ADCXXFLAGS)
      else
        ADCXXFLAGS:= -std=c++11 $(ADCXXFLAGS)
      endif
    else ifeq ($(CXX),CC)
      ADCXXFLAGS:= -std=c++11 $(ADCXXFLAGS)
    else ifeq ($(CXX),g++)
      GCCMAJVER:=$(shell gcc -dumpversion | cut -f1 -d. )
      ifeq ("$(GCCMAJVER)","4")
        GCCMINVER:=$(shell gcc -dumpversion | cut -f2 -d. )
        ifeq ("$(GCCMINVER)","9")
          ADCXXFLAGS:= -std=c++11 $(ADCXXFLAGS)
        else
          ifeq ("$(GCCMINVER)","8")
            ADCXXFLAGS:= -std=c++11 $(ADCXXFLAGS)
          else
            ADCXXFLAGS:= -std=c++0x $(ADCXXFLAGS)
          endif
        endif
      else ifeq ("$(GCCMAJVER)","5")
        ADCXXFLAGS:= -std=c++11 $(ADCXXFLAGS)
      else ifeq ("$(GCCMAJVER)","6")
        ADCXXFLAGS:= -std=c++11 $(ADCXXFLAGS)
      else ifeq ("$(GCCMAJVER)","7")
        ADCXXFLAGS:= -std=c++11 $(ADCXXFLAGS)
      else ifeq ("$(GCCMAJVER)","8")
        ADCXXFLAGS:= -std=c++14 $(ADCXXFLAGS)
      else ifeq ("$(GCCMAJVER)","9")
        ADCXXFLAGS:= -std=c++17 $(ADCXXFLAGS)
      else ifeq ("$(GCCMAJVER)","10")
        ADCXXFLAGS:= -std=c++17 $(ADCXXFLAGS)
      else
        ADCXXFLAGS:= -std=c++$(DEFAULT_CPPSTD_VER) $(ADCXXFLAGS)
      endif
    endif
  endif
endif

ifeq ($(DEBUG),yes)
ADCXXFLAGS:= $(ADCXXFLAGS) -DDEBUG
else ifeq ($(DEBUG),diag)
ADCXXFLAGS:= $(ADCXXFLAGS) -DDEBUG=0
endif

#ADCXXFLAGS:=$(strip $(ADCXXFLAGS)) -DSAFE_ALL
ADCXXFLAGS:= $(ADCXXFLAGS) -D_USE_MATH_DEFINES

ifeq ($(DEBUG),yes)
  ifeq ($(CMDSHELL),cmd)
ADCXXFLAGS:=$(strip $(ADCXXFLAGS)) -I..\build\$(ADMB_VER)\include
  else
ADCXXFLAGS:=$(strip $(ADCXXFLAGS)) -I../build/$(ADMB_VER)/include
  endif
else
  ifeq ($(CMDSHELL),cmd)
ADCXXFLAGS:=$(strip $(ADCXXFLAGS)) -I..\build\$(ADMB_VER)\include
  else
ADCXXFLAGS:=$(strip $(ADCXXFLAGS)) -I../build/$(ADMB_VER)/include
  endif
endif

ifeq ($(CMDSHELL),cmd)
  ifeq ($(CXX),g++)
    ifeq ($(findstring g++.exe,$(shell where g++.exe 2>&1 | findstr g++.exe)),g++.exe)
      ifeq (x86_64,$(findstring x86_64,$(shell $(CXX) -dumpmachine)))
        ADCXXFLAGS:=$(subst -I,-D_FILE_OFFSET_BITS=64 -I,$(ADCXXFLAGS))
      endif
    endif
  endif
endif

CXXFLAGS_SAF_LIB=$(strip $(USER_CXXFLAGS) $(ADCXXFLAGS))
CXXFLAGS_OPT_LIB:=$(subst -D_USE_MATH_DEFINES,-DOPT_LIB -D_USE_MATH_DEFINES,$(CXXFLAGS_SAF_LIB))

ifeq ($(CXX),c++)
CXXFLAGS_OPT_LIB:=$(subst -Wextra,-Wextra,$(CXXFLAGS_OPT_LIB))
endif
ifeq ($(CXX),g++)
CXXFLAGS_OPT_LIB:=$(subst -Wextra,-Wextra,$(CXXFLAGS_OPT_LIB))
endif

include df1b2-separable/objects.lst
OBJECTS=$(addprefix optlp-df1b2-separable-,$(OBJ0)) $(addprefix saflp-df1b2-separable-,$(OBJ0))

include linad99/objects.lst
OBJECTS:=$(OBJECTS) $(addprefix optlp-linad99-,$(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4))
OBJECTS:=$(OBJECTS) $(addprefix saflp-linad99-,$(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ16))
ifeq ($(DEBUG),diag)
OBJECTS:=$(OBJECTS) $(addprefix optlp-linad99-,$(DIAG))
OBJECTS:=$(OBJECTS) $(addprefix saflp-linad99-,$(DIAG))
endif
ifeq ($(CXX),icpc)
OBJECTS:=$(OBJECTS) $(addprefix optlp-linad99-,$(OBJ16))
endif

include nh99/objects.lst
ifeq ($(CXX),CC)
OBJ6:=$(filter-out dfqromb.obj,$(OBJ6))
endif
OBJECTS:=$(OBJECTS) $(addprefix optlp-nh99-,$(OBJ6)) optlp-sparse-hs_sparse.obj
OBJECTS:=$(OBJECTS) $(addprefix saflp-nh99-,$(OBJ6)) saflp-sparse-hs_sparse.obj

include tools99/objects.lst
ifeq ($(CXX),openCC)
OBJ7:=$(filter-out adjson.obj,$(OBJ7))
endif
OBJECTS:=$(OBJECTS) $(addprefix optlp-tools99-,$(OBJ7)) $(addprefix saflp-tools99-,$(OBJ7))

ifdef SAFE_ONLY
OBJECTS:=$(filter-out optlp-%,$(OBJECTS))
endif

OBJECTS:=$(sort $(addprefix $(OBJSDIR),$(OBJECTS)))

all: dist

shared: libs
	$(MAKE) bins
ifeq ($(DEBUG),yes)
  ifeq ($(CMDSHELL),cmd)
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\$(ADMB_VER)\lib\admb$(OSNAME)$(CXXVERSION).dll -Wl,--whole-archive ..\build\$(ADMB_VER)\lib\libadmb$(OSNAME)$(CXXVERSION)-shared-debug.a -Wl,--no-whole-archive
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\$(ADMB_VER)\lib\admbo$(OSNAME)$(CXXVERSION).dll -Wl,--whole-archive ..\build\$(ADMB_VER)\lib\libadmbo$(OSNAME)$(CXXVERSION)-shared-debug.a -Wl,--no-whole-archive
  else
    ifeq (clang,$(findstring clang,$(shell $(CXX) --version)))
	$(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmb$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/$(ADMB_VER)/lib/libadmb$(OSNAME)$(CXXVERSION)-shared-debug.a
      ifndef SAFE_ONLY
	$(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmbo$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/$(ADMB_VER)/lib/libadmbo$(OSNAME)$(CXXVERSION)-shared-debug.a
      endif
    else
      ifeq ($(findstring Homebrew,$(shell $(CXX) --version)),Homebrew)
	$(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmb$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/$(ADMB_VER)/lib/libadmb$(OSNAME)$(CXXVERSION)-shared-debug.a
      else
	$(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmb$(OSNAME)$(CXXVERSION).so -Wl,--whole-archive ../build/$(ADMB_VER)/lib/libadmb$(OSNAME)$(CXXVERSION)-shared-debug.a -Wl,--no-whole-archive
      endif
      ifndef SAFE_ONLY
        ifeq ($(findstring Homebrew,$(shell $(CXX) --version)),Homebrew)
	  $(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmbo$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/$(ADMB_VER)/lib/libadmbo$(OSNAME)$(CXXVERSION)-shared-debug.a
        else
	  $(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmbo$(OSNAME)$(CXXVERSION).so -Wl,--whole-archive ../build/$(ADMB_VER)/lib/libadmbo$(OSNAME)$(CXXVERSION)-shared-debug.a -Wl,--no-whole-archive
        endif
      endif
    endif
  endif
else
  ifeq ($(CMDSHELL),cmd)
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\$(ADMB_VER)\lib\admb$(OSNAME)$(CXXVERSION).dll -Wl,--whole-archive ..\build\$(ADMB_VER)\lib\libadmb$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\$(ADMB_VER)\lib\admbo$(OSNAME)$(CXXVERSION).dll -Wl,--whole-archive ..\build\$(ADMB_VER)\lib\libadmbo$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
  else
    ifeq (clang,$(findstring clang,$(shell $(CXX) --version)))
	$(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmb$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/$(ADMB_VER)/lib/libadmb$(OSNAME)$(CXXVERSION)-shared.a
      ifndef SAFE_ONLY
	$(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmbo$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/$(ADMB_VER)/lib/libadmbo$(OSNAME)$(CXXVERSION)-shared.a
      endif
    else
      ifeq ($(findstring Homebrew,$(shell $(CXX) --version)),Homebrew)
	$(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmb$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/$(ADMB_VER)/lib/libadmb$(OSNAME)$(CXXVERSION)-shared.a
      else
	$(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmb$(OSNAME)$(CXXVERSION).so -Wl,--whole-archive ../build/$(ADMB_VER)/lib/libadmb$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
      endif
      ifndef SAFE_ONLY
        ifeq ($(findstring Homebrew,$(shell $(CXX) --version)),Homebrew)
	  $(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmbo$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/$(ADMB_VER)/lib/libadmbo$(OSNAME)$(CXXVERSION)-shared.a
        else
	  $(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmbo$(OSNAME)$(CXXVERSION).so -Wl,--whole-archive ../build/$(ADMB_VER)/lib/libadmbo$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
        endif
      endif
    endif
  endif
endif

dist: libs
	$(MAKE) bins
ifeq ($(CMDSHELL),cmd)
	copy /Y ..\LICENSE.txt ${DIST}
	$(DIST)\bin\sed.exe "s/\.md/\.txt/g" ..\README.md > ${DIST}\README.txt
	copy /Y ..\CHANGES.md ${DIST}\CHANGES.txt
	copy /Y ..\VERSION.txt ${DIST}
	pushd $(DIST) & ..\..\scripts\create-admb-command-prompt.bat & popd
	pushd $(DIST)\bin & copy ..\..\..\scripts\set-admb-command-prompt.bat & popd
	pushd $(DIST)\bin & copy ..\..\..\scripts\admb-command-prompt.cmd & popd
	pushd .. & scripts\create-admb-command-prompt.bat & popd
else
	cp -f ../LICENSE.txt ${DIST}
	cat ../README.md | sed 's/\.md/\.txt/g' > ${DIST}/README.txt
	cp -f ../CHANGES.md ${DIST}/CHANGES.txt
	cp -f ../VERSION.txt ${DIST}
endif

bins:
ifeq ($(CMDSHELL),cmd)
	if not exist ${DIST}\bin md ${DIST}\bin
	copy df1b2-separable\seddf1b* ${DIST}\bin
	copy df1b2-separable\sedf1b2* ${DIST}\bin
	echo set ADMB_CFG_CXXFLAGS=$(USER_CXXFLAGS)>${DIST}\bin\admb-cfg$(OSNAME)$(CXXVERSION).bat
	echo set ADMB_CFG_LDFLAGS=$(USER_LDFLAGS)>>${DIST}\bin\admb-cfg$(OSNAME)$(CXXVERSION).bat
	copy ..\utilities\sed.exe ${DIST}\bin
	copy ..\utilities\shared\msys-iconv-2.dll ${DIST}\bin
	copy ..\utilities\shared\msys-intl-8.dll ${DIST}\bin
	copy ..\utilities\shared\msys-2.0.dll ${DIST}\bin
	copy ..\scripts\admb\admb.bat ${DIST}\bin\admb.cmd
	copy ..\scripts\admb\root-admb.bat ..\admb.cmd
	copy ..\scripts\admb\root-admb.bat ${DIST}\admb.cmd
	copy ..\scripts\admb\adlink.bat ${DIST}\bin\adlink.cmd
	copy ..\scripts\admb\adcomp.bat ${DIST}\bin\adcomp.cmd
	if not exist ..\build\tpl2rem md ..\build\tpl2rem
	$(MAKE) --directory=df1b2-separable CC=gcc DIST=..\${DIST} CMDSHELL=${CMDSHELL} bins
	if not exist ..\build\tpl2cpp md ..\build\tpl2cpp
	$(MAKE) --directory=nh99 CC=gcc DIST=..\${DIST} CMDSHELL=${CMDSHELL} bins
else
	mkdir -p ${DIST}/bin
	cp df1b2-separable/seddf1b* df1b2-separable/sedf1b2* ${DIST}/bin
  ifdef BUILD_SHARED_LIBRARY
	cp ../scripts/admb/adlink-shared ${DIST}/bin/adlink
  endif
  ifeq ($(OS),Windows_NT)
	echo set ADMB_CFG_CXXFLAGS=$(USER_CXXFLAGS)>${DIST}/bin/admb-cfg$(OSNAME)$(CXXVERSION).bat
	echo set ADMB_CFG_LDFLAGS=-static $(USER_LDFLAGS)>>${DIST}/bin/admb-cfg$(OSNAME)$(CXXVERSION).bat
	echo "ADMB_CFG_CXXFLAGS=$(USER_CXXFLAGS)">${DIST}/bin/admb-cfg$(OSNAME)$(CXXVERSION).sh
	echo "ADMB_CFG_LDFLAGS=-static $(USER_LDFLAGS)">>${DIST}/bin/admb-cfg$(OSNAME)$(CXXVERSION).sh
	cp ../scripts/admb/admb.sh ${DIST}/bin/admb.sh
	cp ../scripts/admb/root-admb.sh ../admb.sh
	cp ../scripts/admb/admb.sh ${DIST}/admb.sh
	cp ../scripts/admb/adcomp ${DIST}/bin/adcomp.sh
	cp ../scripts/admb/adlink ${DIST}/bin/adlink.sh
	cp ../scripts/admb/admb.bat ${DIST}/bin/admb.cmd
	cp ../scripts/admb/root-admb.bat ../admb.cmd
	cp ../scripts/admb/root-admb.bat ${DIST}/admb.cmd
	cp ../scripts/admb/adcomp.bat ${DIST}/bin/adcomp.cmd
	cp ../scripts/admb/adlink.bat ${DIST}/bin/adlink.cmd
  else
	echo "ADMB_CFG_CXXFLAGS=$(USER_CXXFLAGS)">${DIST}/bin/admb-cfg$(OSNAME)$(CXXVERSION).sh
	echo "ADMB_CFG_LDFLAGS=$(USER_LDFLAGS)">>${DIST}/bin/admb-cfg$(OSNAME)$(CXXVERSION).sh
	cp ../scripts/admb/admb ${DIST}/bin
	cp ../scripts/admb/adlink ${DIST}/bin
	cp ../scripts/admb/adcomp ${DIST}/bin
	ln -sf bin/admb ${DIST}
	#cp ../scripts/admb/root-admb ${DIST}/admb
	ln -sf build/$(ADMB_VER)/bin/admb ..
	#cp ../scripts/admb/root-admb ../admb
  endif
	mkdir -p ../build/tpl2rem
  ifeq ($(CXX),g++)
	$(MAKE) --directory=df1b2-separable CC=gcc DIST=../${DIST} CMDSHELL= bins
  else
	$(MAKE) --directory=df1b2-separable CC=$(CC) DIST=../${DIST} CMDSHELL= bins
  endif
	mkdir -p ../build/tpl2cpp
  ifeq ($(CXX),g++)
	$(MAKE) --directory=nh99 CC=gcc DIST=../${DIST} CMDSHELL= bins
  else
	$(MAKE) --directory=nh99 CC=$(CC) DIST=../${DIST} CMDSHELL= bins
  endif
endif

libs: objects
ifeq ($(DEBUG),yes)
  ifeq ($(CMDSHELL),cmd)
	if not exist ${DIST}\lib md ${DIST}\lib
	if exist ${DIST}\lib\libadmb$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a del ${DIST}\lib\libadmb$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a
	if exist ${DIST}\lib\libadmbo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a del ${DIST}\lib\libadmbo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a
  else
	mkdir -p ${DIST}/lib
	rm -vf ${DIST}/lib/libadmb$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a
	rm -vf ${DIST}/lib/libadmbo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a
  endif
	$(AR) -rs $(LIBSDIR)libadmb$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a $(filter $(OBJSDIR)saflp-linad99-f%.obj,$(OBJECTS))
	$(AR) -rs $(LIBSDIR)libadmb$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a $(filter-out $(OBJSDIR)saflp-linad99-f%.obj, $(filter $(OBJSDIR)saflp-linad99%,$(OBJECTS)))
	$(AR) -rs $(LIBSDIR)libadmb$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a $(filter $(OBJSDIR)saflp-df1b2-separable-%.obj,$(OBJECTS))
	$(AR) -rs $(LIBSDIR)libadmb$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a $(filter $(OBJSDIR)saflp-nh99-%.obj,$(OBJECTS))
	$(AR) -rs $(LIBSDIR)libadmb$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a $(filter $(OBJSDIR)saflp-tools99-%.obj,$(OBJECTS))
	$(AR) -rs $(LIBSDIR)libadmb$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a $(filter $(OBJSDIR)saflp-sparse-%.obj,$(OBJECTS))
  ifndef SAFE_ONLY
	$(AR) -rs $(LIBSDIR)libadmbo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a $(filter $(OBJSDIR)optlp-linad99-f%.obj,$(OBJECTS))
	$(AR) -rs $(LIBSDIR)libadmbo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a $(filter-out $(OBJSDIR)optlp-linad99-f%.obj, $(filter $(OBJSDIR)optlp-linad99%,$(OBJECTS)))
	$(AR) -rs $(LIBSDIR)libadmbo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a $(filter $(OBJSDIR)optlp-df1b2-separable-%.obj,$(OBJECTS))
	$(AR) -rs $(LIBSDIR)libadmbo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a $(filter $(OBJSDIR)optlp-nh99-%.obj,$(OBJECTS))
	$(AR) -rs $(LIBSDIR)libadmbo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a $(filter $(OBJSDIR)optlp-tools99-%.obj,$(OBJECTS))
	$(AR) -rs $(LIBSDIR)libadmbo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a $(filter $(OBJSDIR)optlp-sparse-%.obj,$(OBJECTS))
  endif
else
  ifeq ($(CMDSHELL),cmd)
	if not exist ${DIST}\lib md ${DIST}\lib
	if exist ${DIST}\lib\libadmb$(OSNAME)$(CXXVERSION)$(SHARED).a del ${DIST}\lib\libadmb$(OSNAME)$(CXXVERSION)$(SHARED).a
	if exist ${DIST}\lib\libadmbo$(OSNAME)$(CXXVERSION)$(SHARED).a del ${DIST}\lib\libadmbo$(OSNAME)$(CXXVERSION)$(SHARED).a
  else
	mkdir -p ${DIST}/lib
	rm -vf ${DIST}/lib/libadmb$(OSNAME)$(CXXVERSION)$(SHARED).a
	rm -vf ${DIST}/lib/libadmbo$(OSNAME)$(CXXVERSION)$(SHARED).a
  endif
	$(AR) -rs $(LIBSDIR)libadmb$(OSNAME)$(CXXVERSION)$(SHARED).a $(filter $(OBJSDIR)saflp-linad99-f%.obj,$(OBJECTS))
	$(AR) -rs $(LIBSDIR)libadmb$(OSNAME)$(CXXVERSION)$(SHARED).a $(filter-out $(OBJSDIR)saflp-linad99-f%.obj, $(filter $(OBJSDIR)saflp-linad99%,$(OBJECTS)))
	$(AR) -rs $(LIBSDIR)libadmb$(OSNAME)$(CXXVERSION)$(SHARED).a $(filter $(OBJSDIR)saflp-df1b2-separable-%.obj,$(OBJECTS))
	$(AR) -rs $(LIBSDIR)libadmb$(OSNAME)$(CXXVERSION)$(SHARED).a $(filter $(OBJSDIR)saflp-nh99-%.obj,$(OBJECTS))
	$(AR) -rs $(LIBSDIR)libadmb$(OSNAME)$(CXXVERSION)$(SHARED).a $(filter $(OBJSDIR)saflp-tools99-%.obj,$(OBJECTS))
	$(AR) -rs $(LIBSDIR)libadmb$(OSNAME)$(CXXVERSION)$(SHARED).a $(filter $(OBJSDIR)saflp-sparse-%.obj,$(OBJECTS))
  ifndef SAFE_ONLY
	$(AR) -rs $(LIBSDIR)libadmbo$(OSNAME)$(CXXVERSION)$(SHARED).a $(filter $(OBJSDIR)optlp-linad99-f%.obj,$(OBJECTS))
	$(AR) -rs $(LIBSDIR)libadmbo$(OSNAME)$(CXXVERSION)$(SHARED).a $(filter-out $(OBJSDIR)optlp-linad99-f%.obj, $(filter $(OBJSDIR)optlp-linad99%,$(OBJECTS)))
	$(AR) -rs $(LIBSDIR)libadmbo$(OSNAME)$(CXXVERSION)$(SHARED).a $(filter $(OBJSDIR)optlp-df1b2-separable-%.obj,$(OBJECTS))
	$(AR) -rs $(LIBSDIR)libadmbo$(OSNAME)$(CXXVERSION)$(SHARED).a $(filter $(OBJSDIR)optlp-nh99-%.obj,$(OBJECTS))
	$(AR) -rs $(LIBSDIR)libadmbo$(OSNAME)$(CXXVERSION)$(SHARED).a $(filter $(OBJSDIR)optlp-tools99-%.obj,$(OBJECTS))
	$(AR) -rs $(LIBSDIR)libadmbo$(OSNAME)$(CXXVERSION)$(SHARED).a $(filter $(OBJSDIR)optlp-sparse-%.obj,$(OBJECTS))
  endif
endif

ifeq ($(CMDSHELL),cmd)
objects: $(OBJSDIR_) ${DIST}\include
else
objects: $(OBJSDIR_) ${DIST}/include
endif
	$(MAKE) _objects
_objects: $(OBJECTS)

ifeq ($(CMDSHELL),cmd)
$(OBJSDIR)optlp-nh99-banner.obj: nh99\banner.cpp
ifeq ($(ADMB_VERSION),)
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<
else
	$(CXX) -c $(subst -I,-DADMB_VERSION=$(ADMB_VERSION) -I,$(CXXFLAGS_OPT_LIB)) -o $@ $<
endif
$(OBJSDIR)saflp-nh99-banner.obj: nh99\banner.cpp
ifeq ($(ADMB_VERSION),)
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -o $@ $<
else
	$(CXX) -c $(subst -I,-DADMB_VERSION=$(ADMB_VERSION) -I,$(CXXFLAGS_SAF_LIB)) -o $@ $<
endif

$(OBJSDIR)optlp-linad99-dfsdmat.obj:linad99\dfsdmat.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -Wno-free-nonheap-object -o $@ $<

$(OBJSDIR)saflp-linad99-dfsdmat.obj:linad99\dfsdmat.cpp
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -Wno-free-nonheap-object -o $@ $<

$(OBJSDIR)optlp-tools99-string.obj:tools99\string.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -Wno-free-nonheap-object -o $@ $<

$(OBJSDIR)saflp-tools99-string.obj:tools99\string.cpp
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -Wno-free-nonheap-object -o $@ $<

$(OBJSDIR)optlp-tools99-string1.obj:tools99\string1.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -Wno-free-nonheap-object -o $@ $<

$(OBJSDIR)saflp-tools99-string1.obj:tools99\string1.cpp
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -Wno-free-nonheap-object -o $@ $<

$(OBJSDIR)optlp-sparse-hs_sparse.obj: sparse\hs_sparse.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

$(OBJSDIR)saflp-sparse-hs_sparse.obj: sparse\hs_sparse.cpp
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -o $@ $<

$(OBJSDIR)optlp-df1b2-separable-%.obj: df1b2-separable\%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

$(OBJSDIR)saflp-df1b2-separable-%.obj: df1b2-separable\%.cpp
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -o $@ $<

$(OBJSDIR)optlp-linad99-%.obj:linad99\%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

$(OBJSDIR)saflp-linad99-%.obj:linad99\%.cpp
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -o $@ $<

$(OBJSDIR)optlp-nh99-%.obj:nh99\%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

$(OBJSDIR)saflp-nh99-%.obj:nh99\%.cpp
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -o $@ $<

$(OBJSDIR)optlp-tools99-%.obj:tools99\%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

$(OBJSDIR)saflp-tools99-%.obj:tools99\%.cpp
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -o $@ $<
else
$(OBJSDIR)optlp-nh99-banner.obj: nh99/banner.cpp
ifeq ($(ADMB_VERSION),)
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<
else
	$(CXX) -c $(subst -I,-DADMB_VERSION=$(ADMB_VERSION) -I,$(CXXFLAGS_OPT_LIB)) -o $@ $<
endif
$(OBJSDIR)saflp-nh99-banner.obj: nh99/banner.cpp
ifeq ($(ADMB_VERSION),)
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -o $@ $<
else
	$(CXX) -c $(subst -I,-DADMB_VERSION=$(ADMB_VERSION) -I,$(CXXFLAGS_SAF_LIB)) -o $@ $<
endif

$(OBJSDIR)optlp-linad99-dfsdmat.obj:linad99/dfsdmat.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -Wno-free-nonheap-object -o $@ $<

$(OBJSDIR)saflp-linad99-dfsdmat.obj:linad99/dfsdmat.cpp
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -Wno-free-nonheap-object -o $@ $<

$(OBJSDIR)optlp-tools99-string.obj:tools99/string.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -Wno-free-nonheap-object -o $@ $<

$(OBJSDIR)saflp-tools99-string.obj:tools99/string.cpp
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -Wno-free-nonheap-object -o $@ $<

$(OBJSDIR)optlp-tools99-string1.obj:tools99/string1.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -Wno-free-nonheap-object -o $@ $<

$(OBJSDIR)saflp-tools99-string1.obj:tools99/string1.cpp
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -Wno-free-nonheap-object -o $@ $<

$(OBJSDIR)optlp-sparse-hs_sparse.obj: sparse/hs_sparse.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

$(OBJSDIR)saflp-sparse-hs_sparse.obj:sparse/hs_sparse.cpp
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -o $@ $<

$(OBJSDIR)optlp-df1b2-separable-%.obj:df1b2-separable/%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

$(OBJSDIR)saflp-df1b2-separable-%.obj:df1b2-separable/%.cpp
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -o $@ $<

$(OBJSDIR)optlp-linad99-%.obj:linad99/%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

$(OBJSDIR)saflp-linad99-%.obj:linad99/%.cpp
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -o $@ $<

$(OBJSDIR)optlp-nh99-%.obj:nh99/%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

$(OBJSDIR)saflp-nh99-%.obj:nh99/%.cpp
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -o $@ $<

$(OBJSDIR)optlp-tools99-%.obj:tools99/%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

$(OBJSDIR)saflp-tools99-%.obj:tools99/%.cpp
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -o $@ $<
endif

ifeq ($(CMDSHELL),cmd)
${DIST}\include:
	if not exist ${DIST}\include md ${DIST}\include
	copy linad99\df11fun.h ${DIST}\include
	copy linad99\df12fun.h ${DIST}\include
	copy linad99\df13fun.h ${DIST}\include
	copy linad99\fvar.hpp ${DIST}\include
	copy linad99\gradient_structure.h ${DIST}\include
	copy linad99\dvector.h ${DIST}\include
	copy linad99\ivector.h ${DIST}\include
	copy linad99\imatrix.h ${DIST}\include
	copy linad99\vector_shapex.h ${DIST}\include
	copy linad99\dfpool.h ${DIST}\include
	copy linad99\factors.h ${DIST}\include
	copy tools99\adoption.hpp ${DIST}\include
	copy tools99\adstring.hpp ${DIST}\include
	copy tools99\cifstrem.h ${DIST}\include
	copy tools99\clist.h ${DIST}\include
	copy tools99\admb_messages.h ${DIST}\include
	copy tools99\Vectorize.hpp ${DIST}\include
	copy tools99\tiny_ad.hpp ${DIST}\include
	copy tools99\tiny_vec.hpp ${DIST}\include
	copy tools99\tiny_wrap.hpp ${DIST}\include
	copy tools99\integrate.cpp ${DIST}\include
	copy tools99\integrate.hpp ${DIST}\include
	copy tools99\integrate_wrap.hpp ${DIST}\include
	copy tools99\adjson.h ${DIST}\include
	copy df1b2-separable\adpool.h ${DIST}\include
	copy df1b2-separable\adrndeff.h ${DIST}\include
	copy df1b2-separable\df1b2fun.h ${DIST}\include
	copy df1b2-separable\df32fun.h ${DIST}\include
	copy df1b2-separable\df33fun.h ${DIST}\include
	copy df1b2-separable\df3fun.h ${DIST}\include
	copy df1b2-separable\df1b2fnl.h ${DIST}\include
	copy df1b2-separable\df1b2loc.h ${DIST}\include
	copy nh99\admodel.h ${DIST}\include
	copy nh99\param_init_bounded_number_matrix.h ${DIST}\include
	copy sparse\hs.h ${DIST}\include
	copy sparse\cs.h ${DIST}\include
else
${DIST}/include:
	mkdir -p ${DIST}/include
	cp linad99/df11fun.h ${DIST}/include
	cp linad99/df12fun.h ${DIST}/include
	cp linad99/df13fun.h ${DIST}/include
	cp linad99/fvar.hpp ${DIST}/include
	cp linad99/gradient_structure.h ${DIST}/include
	cp linad99/dvector.h ${DIST}/include
	cp linad99/ivector.h ${DIST}/include
	cp linad99/imatrix.h ${DIST}/include
	cp linad99/vector_shapex.h ${DIST}/include
	cp linad99/dfpool.h ${DIST}/include
	cp linad99/factors.h ${DIST}/include
	cp tools99/adoption.hpp ${DIST}/include
	cp tools99/adstring.hpp ${DIST}/include
	cp tools99/cifstrem.h ${DIST}/include
	cp tools99/clist.h ${DIST}/include
	cp tools99/admb_messages.h ${DIST}/include
	cp tools99/Vectorize.hpp ${DIST}/include
	cp tools99/tiny_ad.hpp ${DIST}/include
	cp tools99/tiny_vec.hpp ${DIST}/include
	cp tools99/tiny_wrap.hpp ${DIST}/include
	cp tools99/integrate.cpp ${DIST}/include
	cp tools99/integrate.hpp ${DIST}/include
	cp tools99/integrate_wrap.hpp ${DIST}/include
	cp tools99/adjson.h ${DIST}/include
	cp df1b2-separable/adpool.h ${DIST}/include
	cp df1b2-separable/adrndeff.h ${DIST}/include
	cp df1b2-separable/df1b2fun.h ${DIST}/include
	cp df1b2-separable/df32fun.h ${DIST}/include
	cp df1b2-separable/df33fun.h ${DIST}/include
	cp df1b2-separable/df3fun.h ${DIST}/include
	cp df1b2-separable/df1b2fnl.h ${DIST}/include
	cp df1b2-separable/df1b2loc.h ${DIST}/include
	cp nh99/admodel.h ${DIST}/include
	cp nh99/param_init_bounded_number_matrix.h ${DIST}/include
	cp sparse/hs.h ${DIST}/include
	cp sparse/cs.h ${DIST}/include
endif

$(OBJSDIR_):
ifeq ($(CMDSHELL),cmd)
	if not exist $(OBJSDIR_) md $(OBJSDIR_)
else
	mkdir -p $(OBJSDIR_)
endif

dist-clean:
ifeq ($(CMDSHELL),cmd)
	if exist ..\benchmarks-opt.txt del ..\benchmarks-opt.txt
	if exist ..\benchmarks-saf.txt del ..\benchmarks-saf.txt
	if exist nh99\lex.yy.c del nh99\lex.yy.c
	if exist nh99\tpl2cpp.c del nh99\tpl2cpp.c
	if exist df1b2-separable\lex.yy.c del df1b2-separable\lex.yy.c
	if exist df1b2-separable\tpl2rem.c del df1b2-separable\tpl2rem.c
else
	@rm -vf ../benchmarks-opt.txt
	@rm -vf ../benchmarks-saf.txt
	@rm -vf nh99/lex.yy.c
	@rm -vf nh99/tpl2cpp.c
	@rm -vf nh99/tpl2cpp
	@rm -vf df1b2-separable/lex.yy.c
	@rm -vf df1b2-separable/tpl2rem.c
	@rm -vf df1b2-separable/tpl2rem
endif

clean: dist-clean
ifeq ($(CMDSHELL),cmd)
	if exist ..\admb del ..\admb
	if exist ..\admb.bat del ..\admb.bat
	if exist ..\admb.cmd del ..\admb.cmd
	if exist ..\admb.zip del ..\admb.zip
	if exist ..\REVISION del ..\REVISION
	if exist ..\build rd /S /Q ..\build
else
	@rm -vf ../admb
	@rm -vf ../admb.bat
	@rm -vf ../admb.cmd
	@rm -vf ../admb.sh
	@rm -vf ../admb.zip
	@rm -vf ../REVISION
	@rm -vrf ../build
endif

install:
	@#echo "Read INSTALL.txt for installation instructions."
ifeq ($(INSTALL_DIR),/usr/local/)
	find ../build/$(ADMB_VER) -type d -exec chmod 755 {} \;
	find ../build/$(ADMB_VER) -type f -exec chmod 644 {} \;
  ifeq ($(OS),Windows_NT)
	chmod a+rx ../build/$(ADMB_VER)/bin/admb.cmd
	chmod a+rx ../build/$(ADMB_VER)/bin/admb.sh
	chmod a+rx ../build/$(ADMB_VER)/bin/adlink.cmd
	chmod a+rx ../build/$(ADMB_VER)/bin/adcomp.cmd
	chmod a+rx ../build/$(ADMB_VER)/bin/tpl2cpp.exe
	chmod a+rx ../build/$(ADMB_VER)/bin/tpl2rem.exe
  else
	chmod a+rx ../build/$(ADMB_VER)/bin/admb
	chmod a+rx ../build/$(ADMB_VER)/bin/adlink
	chmod a+rx ../build/$(ADMB_VER)/bin/adcomp
	chmod a+rx ../build/$(ADMB_VER)/bin/tpl2cpp
	chmod a+rx ../build/$(ADMB_VER)/bin/tpl2rem
  endif
	chmod a+r ../build/$(ADMB_VER)/bin/sed*
	chmod a+r ../build/$(ADMB_VER)/include/*.*
	chmod a+r ../build/$(ADMB_VER)/include/contrib/*.*
endif
	cp -Rvf ../build/$(ADMB_VER) $(INSTALL_DIR)
ifeq ($(INSTALL_DIR),/usr/local/)
  ifneq ($(OS),Windows_NT)
	ln -svf $(INSTALL_DIR)admb/bin/admb $(INSTALL_DIR)bin/admb
  endif
endif

copy:
ifeq ($(CMDSHELL),cmd)
	if not exist $(DIST)\utilities md $(DIST)\utilities
	xcopy ..\utilities $(DIST)\utilities /S /Y /D
	if not exist $(DIST)\src md $(DIST)\src
	xcopy ..\src $(DIST)\src /S /Y /D
	if not exist $(DIST)\scripts md $(DIST)\scripts
	xcopy ..\scripts $(DIST)\scripts /S /Y /D
	$(MAKE) --directory=$(DIST)/scripts clean
	if not exist $(DIST)\examples md $(DIST)\examples
	xcopy ..\examples $(DIST)\examples /S /Y /D
	$(MAKE) --directory=..\contrib copy
	$(MAKE) --directory=..\tests copy
	$(MAKE) --directory=..\build\admb\src dist-clean
	copy /Y ..\Makefile ${DIST}
else
	cp -vRf ../utilities ${DIST}
	cp -R ../src $(DIST)
	cp -R ../scripts $(DIST)
	$(MAKE) --directory=$(DIST)/scripts clean
	cp -R ../examples $(DIST)
	$(MAKE) --directory=../contrib copy
	$(MAKE) --directory=../tests copy
	$(MAKE) --directory=../build/$(ADMB_VER)/src dist-clean
	cp -f ../Makefile ${DIST}
endif

coding-standard: cpplint.py
	python cpplint.py --linelength=80 --extension=c,cpp,h,hpp --filter=-,+whitespace/tab,+whitespace/blank_line,+whitespace/line_length,+whitespace/end_of_line df1b2-separable/*.h* linad99/*.h* nh99/*.h* sparse/*.h* tools99/*.h* df1b2-separable/*.cpp linad99/*.cpp nh99/*.cpp sparse/*.cpp tools99/*.cpp

cpplint.py:
	svn cat https://github.com/google/styleguide/trunk/cpplint/cpplint.py > cpplint.py

zip:
ifeq ($(OS),Windows_NT)
  ifeq ($(CMDSHELL),cmd)
	copy /Y ..\docs\install\QuickStartWindows.md ..\build\admb\INSTALL.txt
	if not exist $(DIST)\examples md $(DIST)\examples
	xcopy ..\examples $(DIST)\examples /S /Y /D
  else
	cp ../docs/install/QuickStartWindows.md ../build/$(ADMB_VER)/INSTALL.txt
	cp -R ../examples $(DIST)
  endif
	pushd ..\\build && powershell -ExecutionPolicy ByPass -F ..\\scripts\zipadmb.ps1 && popd
else
  ifeq ($(UNAME_S),Linux)
	cp ../docs/install/QuickStartUnix.md ../build/$(ADMB_VER)/INSTALL.txt
  endif
  ifeq ($(UNAME_S),Darwin)
	cp ../docs/install/QuickStartUnix.md ../build/$(ADMB_VER)/INSTALL.txt
  endif
	cp -R ../examples $(DIST)
	cd ../build/ && zip -r $(ADMB_VER).zip $(ADMB_VER)
endif

check:
	@echo "SHELL: $(SHELL)"
	@echo "PATH: $(PATH)"
	@echo "TERM: $(TERM)"
	@echo "MAKE: $(MAKE)"
	@echo "CXX: $(CXX)"
	@echo "OS: $(OS)"
	@echo "OSTYPE: $(OSTYPE)"
	@echo "COMSPEC: $(COMSPEC)"
