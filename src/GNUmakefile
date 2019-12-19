ifeq ($(OS),Windows_NT)
  ifeq ($(strip $(TERM)),)
    SHELL=cmd
    ifeq ($(wildcard ..\utilities\mingw\bin\g++.exe),..\utilities\mingw\bin\g++.exe)
      PATH:=$(shell cd)\..\utilities\mingw\bin;$(PATH)
    endif
  else
    ifeq ($(wildcard ../utilities/mingw/bin/g++.exe),../utilities/mingw/bin/g++.exe)
      PATH:=$(shell pwd)/../utilities/mingw/bin:$(PATH)
    endif
  endif
endif

ifeq ($(SHELL),cmd)
  DIST=..\build\admb
  LIBSDIR=$(DIST)\lib
  LIBSDIR:=$(addsuffix \,$(LIBSDIR))
  OBJSDIR=..\build\objects
  ifeq ($(CXX),g++)
    ifeq (,$(shell where g++.exe))
      $(error "Error: Missing g++ compiler.")
    endif
    ifeq ($(findstring x86_64,$(shell g++ -dumpmachine)),x86_64)
      ifeq ($(findstring MSYS2,$(shell g++ --version)),MSYS2)
        OSNAME=x86_64-msys2
      else
        OSNAME=mingw64
      endif
    else
      ifeq ($(findstring MSYS2,$(shell g++ --version)),MSYS2)
        OSNAME=i686-msys2
      else
        OSNAME=mingw32
      endif
    endif
    CXXVERSION=-g++$(basename $(basename $(shell g++ -dumpversion)))
  endif
  ifdef SHARED
  OBJSDIR:=$(addsuffix \$(OSNAME)$(CXXVERSION)-shared\,$(OBJSDIR))
  else
  OBJSDIR:=$(addsuffix \$(OSNAME)$(CXXVERSION)\,$(OBJSDIR))
  endif
  ADMB_VERSION:=$(shell if exist ..\VERSION type ..\VERSION)
else
  INSTALL_DIR=/usr/local/
  ifeq ($(DEBUG),yes)
  DIST=$(shell pwd)/../build/admb
  else
  DIST=../build/admb
  endif
  LIBSDIR=$(DIST)/lib/
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
    ifeq (i686,$(findstring i686,$(shell $(CXX) -dumpmachine)))
      OSNAME=i686-linux
    else
      OSNAME=x86_64-linux
    endif
  endif
  ifeq ($(UNAME_S),Darwin)
    ifeq (i686,$(findstring i686,$(shell $(CXX) -dumpmachine)))
      OSNAME=i686-macos
    else
      OSNAME=x86_64-macos
    endif
  endif
  ifeq ($(findstring _NT,$(UNAME_S)),_NT)
    ifeq ($(findstring x86_64,$(shell g++ -dumpmachine)),x86_64)
      ifeq ($(findstring MSYS2,$(shell g++ --version)),MSYS2)
        OSNAME=x86_64-msys2
      else
        OSNAME=mingw64
      endif
    else
      ifeq ($(findstring MSYS2,$(shell g++ --version)),MSYS2)
        OSNAME=i686-msys2
      else
        OSNAME=mingw32
      endif
    endif
  endif
  ifndef OSNAME
    $(warning Unknown UNAME_S = "$(UNAME_S)" results in empty OSNAME.)
  endif
  ifeq ($(CXX),g++)
  CXXVERSION=-g++$(basename $(basename $(shell $(CXX) -dumpversion)))
  endif
  ifeq ($(CXX),clang++)
  CXXVERSION=-clang++$(basename $(basename $(shell $(CXX) -dumpversion)))
  endif
  ifeq ($(CXX),c++)
  CXXVERSION=-c++$(basename $(basename $(shell $(CXX) -dumpversion)))
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
  ifeq ($(DEBUG),yes)
  OBJSDIR=$(shell pwd)/../build/objects/$(OSNAME)$(CXXVERSION)
  else
  OBJSDIR=../build/objects/$(OSNAME)$(CXXVERSION)
  endif
  ifdef SHARED
  OBJSDIR:=$(sort $(addsuffix -shared/, $(OBJSDIR)))
  else
  OBJSDIR:=$(sort $(addsuffix /, $(OBJSDIR)))
  endif
  ADMB_VERSION:=$(shell cat ../VERSION)
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

ifeq ($(DEBUG),yes)
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
ADCXXFLAGS:= $(ADCXXFLAGS) -Wall -Wextra -Wconversion -Wno-unused-parameter
endif

ifeq ($(SHELL),cmd)
  ifeq ($(CXX),g++)
    GCCMAJVER:="GCCVER$(shell gcc -dumpversion)"
    ifeq (GCCVER7,$(findstring GCCVER7,$(GCCMAJVER)))
      ADCXXFLAGS:= -std=c++14 $(ADCXXFLAGS)
    else
      ifeq (GCCVER6,$(findstring GCCVER6,$(GCCMAJVER)))
        ADCXXFLAGS:= -std=c++14 $(ADCXXFLAGS)
      else
        ADCXXFLAGS:= -std=c++11 $(ADCXXFLAGS)
      endif
    endif
  endif
else
  ifeq ("$(shell uname)","Darwin")
    ADCXXFLAGS:= -std=c++14 $(ADCXXFLAGS)
  else
    ifeq ($(CXX),clang++)
      ADCXXFLAGS:= -std=c++11 $(ADCXXFLAGS)
    else
      ifeq ($(CXX),icpc)
        ICPCMAJVER:=$(shell icpc -dumpversion | cut -f1 -d. )
        ifeq ("$(ICPCMAJVER)","17")
          ADCXXFLAGS:= -std=c++14 $(ADCXXFLAGS)
        else
          ADCXXFLAGS:= -std=c++11 $(ADCXXFLAGS)
        endif
      else
        ifeq ($(CXX),CC)
          ADCXXFLAGS:= -std=c++11 $(ADCXXFLAGS)
        else
          ifeq ($(CXX),g++)
            GCCMAJVER:=$(shell gcc -dumpversion | cut -f1 -d. )
            ifeq ("$(GCCMAJVER)","4")
              GCCMINVER:=$(shell gcc -dumpversion | cut -f2 -d. )
              ifeq ("$(GCCMINVER)","9")
                ADCXXFLAGS:= -std=c++11 $(ADCXXFLAGS)
              else
                ADCXXFLAGS:= -std=c++0x $(ADCXXFLAGS)
              endif
            else
              ADCXXFLAGS:= -std=c++14 $(ADCXXFLAGS)
            endif
          endif
        endif
      endif
    endif
  endif
endif

#ADCXXFLAGS:=$(strip $(ADCXXFLAGS)) -DSAFE_ALL
ADCXXFLAGS:= $(ADCXXFLAGS) -D_USE_MATH_DEFINES

ifeq ($(DEBUG),yes)
  ifeq ($(SHELL),cmd)
ADCXXFLAGS:=$(strip $(ADCXXFLAGS)) -I..\build\admb\include
  else
ADCXXFLAGS:=$(strip $(ADCXXFLAGS)) -I$(shell pwd)/../build/admb/include
  endif
else
  ifeq ($(SHELL),cmd)
ADCXXFLAGS:=$(strip $(ADCXXFLAGS)) -I..\build\admb\include
  else
ADCXXFLAGS:=$(strip $(ADCXXFLAGS)) -I../build/admb/include
  endif
endif

ifeq ($(TERM),cygwin)
  ifeq ($(CXX),g++)
    ifeq (x86_64,$(findstring x86_64,$(shell $(CXX) -dumpmachine)))
      ADCXXFLAGS:=$(subst -I,-D_FILE_OFFSET_BITS=64 -I,$(ADCXXFLAGS))
    endif
  endif
else
ifeq ($(SHELL),cmd)
  ifeq ($(CXX),g++)
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
ifneq ($(CXX),CC)
  ifneq ($(CXX),openCC)
    ifneq ($(CXX),icpc)
CXXFLAGS_OPT_LIB:=$(subst -Wno-,-Wno-unused-result -Wno-,$(CXXFLAGS_OPT_LIB))
    endif
  endif
endif

include df1b2-separable/objects.lst
OBJECTS=$(addprefix optlp-df1b2-separable-,$(OBJ0)) $(addprefix saflp-df1b2-separable-,$(OBJ0))

include linad99/objects.lst
OBJECTS:=$(OBJECTS) $(addprefix optlp-linad99-,$(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4))
OBJECTS:=$(OBJECTS) $(addprefix saflp-linad99-,$(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ16))
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
  ifeq ($(SHELL),cmd)
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\admb\lib\admb$(OSNAME)$(CXXVERSION).dll -Wl,--whole-archive ..\build\admb\lib\libadmb-$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\admb\lib\admbo$(OSNAME)$(CXXVERSION).dll -Wl,--whole-archive ..\build\admb\lib\libadmbo-$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
  else
    ifeq (clang,$(findstring clang,$(shell $(CXX) --version)))
	$(CXX) -shared $(LDFLAGS) -o ../build/admb/lib/libadmb-$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/admb/lib/libadmb-$(OSNAME)$(CXXVERSION)-shared.a
      ifndef SAFE_ONLY
	$(CXX) -shared $(LDFLAGS) -o ../build/admb/lib/libadmbo-$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/admb/lib/libadmbo-$(OSNAME)$(CXXVERSION)-shared.a
      endif
    else
	$(CXX) -shared $(LDFLAGS) -o ../build/admb/lib/libadmb-$(OSNAME)$(CXXVERSION).so -Wl,--whole-archive ../build/admb/lib/libadmb-$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
      ifndef SAFE_ONLY
	$(CXX) -shared $(LDFLAGS) -o ../build/admb/lib/libadmbo-$(OSNAME)$(CXXVERSION).so -Wl,--whole-archive ../build/admb/lib/libadmbo-$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
      endif
    endif
  endif
else
  ifeq ($(SHELL),cmd)
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\admb\lib\admb$(OSNAME)$(CXXVERSION).dll -Wl,--whole-archive ..\build\admb\lib\libadmb-$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\admb\lib\admbo$(OSNAME)$(CXXVERSION).dll -Wl,--whole-archive ..\build\admb\lib\libadmbo-$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
  else
    ifeq (clang,$(findstring clang,$(shell $(CXX) --version)))
	$(CXX) -shared $(LDFLAGS) -o ../build/admb/lib/libadmb-$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/admb/lib/libadmb-$(OSNAME)$(CXXVERSION)-shared.a
      ifndef SAFE_ONLY
	$(CXX) -shared $(LDFLAGS) -o ../build/admb/lib/libadmbo-$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/admb/lib/libadmbo-$(OSNAME)$(CXXVERSION)-shared.a
      endif
    else
	$(CXX) -shared $(LDFLAGS) -o ../build/admb/lib/libadmb-$(OSNAME)$(CXXVERSION).so -Wl,--whole-archive ../build/admb/lib/libadmb-$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
      ifndef SAFE_ONLY
	$(CXX) -shared $(LDFLAGS) -o ../build/admb/lib/libadmbo-$(OSNAME)$(CXXVERSION).so -Wl,--whole-archive ../build/admb/lib/libadmbo-$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
      endif
    endif
  endif
endif

dist: libs
	$(MAKE) bins
ifeq ($(SHELL),cmd)
	copy /Y ..\LICENSE.txt ${DIST}
	copy /Y ..\README.txt ${DIST}
	copy /Y ..\CHANGES.txt ${DIST}
	copy /Y ..\VERSION ${DIST}
else
	cp -f ../LICENSE.txt ${DIST}
	cp -f ../README.txt ${DIST}
	cp -f ../CHANGES.txt ${DIST}
	cp -f ../VERSION ${DIST}
endif

bins:
ifeq ($(SHELL),cmd)
	if not exist ${DIST}\bin md ${DIST}\bin
	copy df1b2-separable\seddf1b* ${DIST}\bin
	copy df1b2-separable\sedf1b2* ${DIST}\bin
	echo set ADMB_CFG_CXX=$(USER_CXX)>${DIST}\bin\admb-cfg.bat
	echo set ADMB_CFG_CXXFLAGS=$(USER_CXXFLAGS)>>${DIST}\bin\admb-cfg.bat
	echo set ADMB_CFG_LDFLAGS=$(USER_LDFLAGS)>>${DIST}\bin\admb-cfg.bat
	copy ..\utilities\sed.exe ${DIST}\bin
	copy ..\utilities\libiconv2.dll ${DIST}\bin
	copy ..\utilities\libintl3.dll ${DIST}\bin
	copy ..\utilities\regex2.dll ${DIST}\bin
	copy ..\scripts\admb\admb.bat ${DIST}\bin\admb.cmd
  ifeq ($(DEBUG),yes)
	copy ..\scripts\admb\root-admb-debug.bat ..\admb.cmd
	copy ..\scripts\admb\root-admb-debug.bat ${DIST}\admb.cmd
  else
	copy ..\scripts\admb\root-admb.bat ..\admb.cmd
	copy ..\scripts\admb\root-admb.bat ${DIST}\admb.cmd
  endif
	copy ..\scripts\admb\adlink.bat ${DIST}\bin\adlink.cmd
	copy ..\scripts\admb\adcomp.bat ${DIST}\bin\adcomp.cmd
	$(MAKE) --directory=df1b2-separable CC=gcc DIST=..\${DIST} bins
	$(MAKE) --directory=nh99 CC=gcc DIST=..\${DIST} bins
else
	mkdir -p ${DIST}/bin
	cp df1b2-separable/seddf1b* df1b2-separable/sedf1b2* ${DIST}/bin
  ifdef BUILD_SHARED_LIBRARY
	cp ../scripts/admb/adlink-shared ${DIST}/bin/adlink
  endif
  ifeq ($(OS),Windows_NT)
	echo "ADMB_CFG_CXXFLAGS=\"$(USER_CXXFLAGS)\"">${DIST}/bin/admb-cfg.sh
	echo "ADMB_CFG_LDFLAGS=\"-static $(USER_LDFLAGS)\"">>${DIST}/bin/admb-cfg.sh
	cp ../scripts/admb/admb ${DIST}/bin/admb.sh
    ifeq ($(DEBUG),yes)
	cp ../scripts/admb/root-admb-debug.sh ../admb.sh
	cp ../scripts/admb/root-admb-debug.sh ${DIST}/admb.sh
    else
	cp ../scripts/admb/root-admb.sh ../admb.sh
	cp ../scripts/admb/admb ${DIST}/admb.sh
    endif
	cp ../scripts/admb/adcomp ${DIST}/bin/adcomp.sh
	cp ../scripts/admb/adlink ${DIST}/bin/adlink.sh
	cp ../scripts/admb/admb.bat ${DIST}/bin/admb.cmd
    ifeq ($(DEBUG),yes)
	cp ../scripts/admb/root-admb-debug.bat ../admb.cmd
	cp ../scripts/admb/root-admb-debug.bat ${DIST}/admb.cmd
    else
	cp ../scripts/admb/root-admb.bat ../admb.cmd
	cp ../scripts/admb/root-admb.bat ${DIST}/admb.cmd
    endif
	cp ../scripts/admb/adcomp.bat ${DIST}/bin/adcomp.cmd
	cp ../scripts/admb/adlink.bat ${DIST}/bin/adlink.cmd
  else
	echo "ADMB_CFG_CXXFLAGS=\"$(USER_CXXFLAGS)\"">${DIST}/bin/admb-cfg$(OSNAME)$(CXXVERSION).sh
	echo "ADMB_CFG_LDFLAGS=\"$(USER_LDFLAGS)\"">>${DIST}/bin/admb-cfg$(OSNAME)$(CXXVERSION).sh
	cp ../scripts/admb/admb ${DIST}/bin
	cp ../scripts/admb/adlink ${DIST}/bin
	cp ../scripts/admb/adcomp ${DIST}/bin
	ln -sf bin/admb ${DIST}
	#cp ../scripts/admb/root-admb ${DIST}/admb
	ln -sf build/admb/bin/admb ..
	#cp ../scripts/admb/root-admb ../admb
  endif
    ifeq ($(DEBUG),yes)
	$(MAKE) --directory=df1b2-separable CC=$(CC) DIST=${DIST} bins
	$(MAKE) --directory=nh99 CC=$(CC) DIST=${DIST} bins
    else
	$(MAKE) --directory=df1b2-separable CC=$(CC) DIST=../${DIST} bins
	$(MAKE) --directory=nh99 CC=$(CC) DIST=../${DIST} bins
    endif
endif

ifeq ($(SHELL),cmd)
libs: $(DIST)\include
else
libs: $(DIST)/include
endif
	$(MAKE) objects
ifeq ($(SHELL),cmd)
	if not exist ${DIST}\lib md ${DIST}\lib
	if exist ${DIST}\lib\libadmb-$(OSNAME)$(CXXVERSION)(SHARED).a del ${DIST}\lib\libadmb-$(OSNAME)$(CXXVERSION)$(SHARED).a
	if exist ${DIST}\lib\libadmbo-$(OSNAME)$(CXXVERSION)$(SHARED).a del ${DIST}\lib\libadmbo-$(OSNAME)$(CXXVERSION)$(SHARED).a
else
	mkdir -p ${DIST}/lib
	rm -vf ${DIST}/lib/libadmb-$(OSNAME)$(CXXVERSION)$(SHARED).a
	rm -vf ${DIST}/lib/libadmbo-$(OSNAME)$(CXXVERSION)$(SHARED).a
endif
ifeq ($(SHELL),cmd)
	$(AR) -rs $(LIBSDIR)libadmb-$(OSNAME)$(CXXVERSION)$(SHARED).a $(OBJSDIR)saflp-linad99-*.obj
else
	$(AR) -rs $(LIBSDIR)libadmb-$(OSNAME)$(CXXVERSION)$(SHARED).a $(OBJSDIR)saflp-linad99-[f]*.obj
	$(AR) -rs $(LIBSDIR)libadmb-$(OSNAME)$(CXXVERSION)$(SHARED).a $(OBJSDIR)saflp-linad99-[^f]*.obj
endif
	$(AR) -rs $(LIBSDIR)libadmb-$(OSNAME)$(CXXVERSION)$(SHARED).a $(OBJSDIR)saflp-df1b2-separable-*.obj
	$(AR) -rs $(LIBSDIR)libadmb-$(OSNAME)$(CXXVERSION)$(SHARED).a $(OBJSDIR)saflp-nh99-*.obj
	$(AR) -rs $(LIBSDIR)libadmb-$(OSNAME)$(CXXVERSION)$(SHARED).a $(OBJSDIR)saflp-tools99-*.obj
	$(AR) -rs $(LIBSDIR)libadmb-$(OSNAME)$(CXXVERSION)$(SHARED).a $(OBJSDIR)saflp-sparse-*.obj
ifndef SAFE_ONLY
  ifeq ($(SHELL),cmd)
	$(AR) -rs $(LIBSDIR)libadmbo-$(OSNAME)$(CXXVERSION)$(SHARED).a $(OBJSDIR)optlp-linad99-*.obj
  else
	$(AR) -rs $(LIBSDIR)libadmbo-$(OSNAME)$(CXXVERSION)$(SHARED).a $(OBJSDIR)optlp-linad99-[f]*.obj
	$(AR) -rs $(LIBSDIR)libadmbo-$(OSNAME)$(CXXVERSION)$(SHARED).a $(OBJSDIR)optlp-linad99-[^f]*.obj
  endif
	$(AR) -rs $(LIBSDIR)libadmbo-$(OSNAME)$(CXXVERSION)$(SHARED).a $(OBJSDIR)optlp-df1b2-separable-*.obj
	$(AR) -rs $(LIBSDIR)libadmbo-$(OSNAME)$(CXXVERSION)$(SHARED).a $(OBJSDIR)optlp-nh99-*.obj
	$(AR) -rs $(LIBSDIR)libadmbo-$(OSNAME)$(CXXVERSION)$(SHARED).a $(OBJSDIR)optlp-tools99-*.obj
	$(AR) -rs $(LIBSDIR)libadmbo-$(OSNAME)$(CXXVERSION)$(SHARED).a $(OBJSDIR)optlp-sparse-*.obj
endif

objects: $(OBJSDIR)
	$(MAKE) _objects
_objects: $(OBJECTS)

ifeq ($(SHELL),cmd)
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

ifeq ($(DEBUG),yes)
$(OBJSDIR)optlp-sparse-hs_sparse.obj: $(shell pwd)/sparse/hs_sparse.cpp
else
$(OBJSDIR)optlp-sparse-hs_sparse.obj: sparse/hs_sparse.cpp
endif
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

ifeq ($(DEBUG),yes)
$(OBJSDIR)saflp-sparse-hs_sparse.obj: $(shell pwd)/sparse/hs_sparse.cpp
else
$(OBJSDIR)saflp-sparse-hs_sparse.obj:sparse/hs_sparse.cpp
endif
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -o $@ $<

ifeq ($(DEBUG),yes)
$(OBJSDIR)optlp-df1b2-separable-%.obj:$(shell pwd)/df1b2-separable/%.cpp
else
$(OBJSDIR)optlp-df1b2-separable-%.obj:df1b2-separable/%.cpp
endif
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

ifeq ($(DEBUG),yes)
$(OBJSDIR)saflp-df1b2-separable-%.obj:$(shell pwd)/df1b2-separable/%.cpp
else
$(OBJSDIR)saflp-df1b2-separable-%.obj:df1b2-separable/%.cpp
endif
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -o $@ $<

ifeq ($(DEBUG),yes)
$(OBJSDIR)optlp-linad99-%.obj:$(shell pwd)/linad99/%.cpp
else
$(OBJSDIR)optlp-linad99-%.obj:linad99/%.cpp
endif
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

ifeq ($(DEBUG),yes)
$(OBJSDIR)saflp-linad99-%.obj:$(shell pwd)/linad99/%.cpp
else
$(OBJSDIR)saflp-linad99-%.obj:linad99/%.cpp
endif
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -o $@ $<

ifeq ($(DEBUG),yes)
$(OBJSDIR)optlp-nh99-%.obj:$(shell pwd)/nh99/%.cpp
else
$(OBJSDIR)optlp-nh99-%.obj:nh99/%.cpp
endif
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

ifeq ($(DEBUG),yes)
$(OBJSDIR)saflp-nh99-%.obj:$(shell pwd)/nh99/%.cpp
else
$(OBJSDIR)saflp-nh99-%.obj:nh99/%.cpp
endif
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -o $@ $<

ifeq ($(DEBUG),yes)
$(OBJSDIR)optlp-tools99-%.obj:$(shell pwd)/tools99/%.cpp
else
$(OBJSDIR)optlp-tools99-%.obj:tools99/%.cpp
endif
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

ifeq ($(DEBUG),yes)
$(OBJSDIR)saflp-tools99-%.obj:$(shell pwd)/tools99/%.cpp
else
$(OBJSDIR)saflp-tools99-%.obj:tools99/%.cpp
endif
	$(CXX) -c $(CXXFLAGS_SAF_LIB) -o $@ $<
endif

ifeq ($(SHELL),cmd)
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
endif

ifeq ($(SHELL),cmd)
$(OBJSDIR): ${DIST}\include:
	if not exist $(OBJSDIR) md $(OBJSDIR)
else
$(OBJSDIR): ${DIST}/include
	mkdir -p $(OBJSDIR)
endif

dist-clean:
ifeq ($(SHELL),cmd)
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
ifeq ($(SHELL),cmd)
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
ifeq ($(DEBUG),yes)
  ifeq ($(INSTALL_DIR),/usr/local/)
	find ../build/admb -type d -exec chmod 755 {} \;
	find ../build/admb -type f -exec chmod 644 {} \;
	chmod a+rx ../build/admb/bin/admb
	chmod a+rx ../build/admb/bin/adlink
	chmod a+rx ../build/admb/bin/adcomp
	chmod a+rx ../build/admb/bin/tpl2cpp
	chmod a+rx ../build/admb/bin/tpl2rem
	chmod a+rx ../build/admb/contrib
	chmod a+r ../build/admb/bin/sed*
	chmod a+r ../build/admb/include/*.*
	chmod a+r ../build/admb/contrib/include/*.*
  endif
	cp -Rvf ../build/admb $(INSTALL_DIR)admb
else
  ifeq ($(INSTALL_DIR),/usr/local/)
	find ../build/admb -type d -exec chmod 755 {} \;
	find ../build/admb -type f -exec chmod 644 {} \;
	chmod a+rx ../build/admb/bin/admb
	chmod a+rx ../build/admb/bin/adlink
	chmod a+rx ../build/admb/bin/adcomp
	chmod a+rx ../build/admb/bin/tpl2cpp
	chmod a+rx ../build/admb/bin/tpl2rem
	chmod a+rx ../build/admb/contrib
	chmod a+r ../build/admb/bin/sed*
	chmod a+r ../build/admb/include/*.*
	chmod a+r ../build/admb/contrib/include/*.*
  endif
	cp -Rvf ../build/admb $(INSTALL_DIR)admb
endif
	ln -svf $(INSTALL_DIR)admb/bin/admb $(INSTALL_DIR)bin/admb

copy:
ifeq ($(SHELL),cmd)
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
	$(MAKE) --directory=../build/admb/src dist-clean
	cp -f ../Makefile ${DIST}
endif

coding-standard: cpplint.py
	python cpplint.py --linelength=80 --extension=c,cpp,h,hpp --filter=-,+whitespace/tab,+whitespace/blank_line,+whitespace/line_length,+whitespace/end_of_line df1b2-separable/*.h* linad99/*.h* nh99/*.h* sparse/*.h* tools99/*.h* df1b2-separable/*.cpp linad99/*.cpp nh99/*.cpp sparse/*.cpp tools99/*.cpp

cpplint.py:
	svn cat https://github.com/google/styleguide/trunk/cpplint/cpplint.py > cpplint.py

zip:
ifeq ($(OS),Windows_NT)
	pushd ..\\build && powershell -ExecutionPolicy ByPass -F ..\\scripts\zipadmb.ps1 && popd
else
	cd ../build/ && zip -r admb.zip admb
endif

check:
	@echo "SHELL: $(SHELL)"
	@echo "PATH: $(PATH)"
	@echo "TERM: $(TERM)"
	@echo "MAKE: $(MAKE)"
	@echo "CXX: $(CXX)"
	@echo "OS: $(OS)"
	@echo "OSTYPE: $(OSTYPE)"
