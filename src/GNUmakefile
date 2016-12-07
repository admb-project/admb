ifeq ($(OS),Windows_NT)
  ifeq ($(TERM),cygwin)
  else
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL = cmd
    ifeq ($(SHELL),cmd)
      MYPWD=$(shell cd)
    else
      MYPWD=$(shell cmd /C cd)
    endif
    PATH:=$(MYPWD)\..\utilities\mingw\bin;$(PATH)
  else
    ifneq ($(TERM),xterm)
      MYPWD=$(shell pwd)
      PATH:=$(MYPWD)/../utilities/mingw/bin:$(PATH)
    endif
  endif
  endif
endif

ifeq ($(SHELL),cmd)
  ifeq ($(DEBUG),yes)
  DIST=..\build\debug
  else
  DIST=..\build\dist
  endif
  LIBSDIR=$(DIST)\lib
  LIBSDIR:=$(addsuffix \,$(LIBSDIR))
  ifeq ($(DEBUG),yes)
  OBJSDIR=..\build\objects\debug
  else
  OBJSDIR=..\build\objects\dist
  endif
  OBJSDIR:=$(addsuffix \,$(OBJSDIR))
  ADMB_VERSION:=$(shell if exist ..\VERSION type ..\VERSION)
else
  INSTALL_DIR=/usr/local/
  ifeq ($(DEBUG),yes)
  DIST=$(shell pwd)/../build/debug
  else
  DIST=../build/dist
  endif
  LIBSDIR=$(DIST)/lib/
  ifeq ($(DEBUG),yes)
  OBJSDIR=$(shell pwd)/../build/objects/debug/
  else
  OBJSDIR=../build/objects/dist/
  endif
  ADMB_VERSION:=$(shell cat ../VERSION)
endif
ifdef SHARED
  ifneq ($(SHELL),cmd)
    OBJSDIR:=$(addsuffix shared-,$(OBJSDIR))
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

ifeq ($(DEBUG),yes)
  ADCXXFLAGS:= -g $(ADCXXFLAGS)
else
  ifeq ($(CXX),openCC)
    ADCXXFLAGS:= -O2 $(ADCXXFLAGS)
  else
    ADCXXFLAGS:= -O3 $(ADCXXFLAGS)
  endif
endif

ifneq ($(CXX),CC)
ADCXXFLAGS:= -Wall -Wextra -Wconversion -Wno-unused-parameter $(ADCXXFLAGS)
endif

ifeq ("$(shell uname)","Darwin")
  ADCXXFLAGS:= -std=c++14 $(ADCXXFLAGS)
else ifeq ($(CXX),clang++)
  ADCXXFLAGS:= -std=c++11 $(ADCXXFLAGS)
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
      ADCXXFLAGS:= -std=c++0x $(ADCXXFLAGS)
    endif
  else
    ADCXXFLAGS:= -std=c++14 $(ADCXXFLAGS)
  endif
endif

#ADCXXFLAGS:=$(strip $(ADCXXFLAGS)) -DSAFE_ALL

ifeq ($(DEBUG),yes)
  ifeq ($(SHELL),cmd)
ADCXXFLAGS:=$(strip $(ADCXXFLAGS)) -I..\build\debug\include
  else
ADCXXFLAGS:=$(strip $(ADCXXFLAGS)) -I$(shell pwd)/../build/debug/include
  endif
else
  ifeq ($(SHELL),cmd)
ADCXXFLAGS:=$(strip $(ADCXXFLAGS)) -I..\build\dist\include
  else
ADCXXFLAGS:=$(strip $(ADCXXFLAGS)) -I../build/dist/include
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

$(info INFO: $(USER_CXXFLAGS) )
$(info INFO: $(CXXFLAGS) )
$(info INFO: $(ADCXXFLAGS) )
override CXXFLAGS=$(strip $(USER_CXXFLAGS) $(ADCXXFLAGS))
$(info INFO: $CXXFLAGS)

CXXFLAGS_OPT_LIB:=$(subst -I,-DOPT_LIB -I,$(CXXFLAGS))

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

ifeq ($(COVERAGE),yes)
OBJECTS:=$(filter-out optlp-%,$(OBJECTS))
endif

OBJECTS:=$(sort $(addprefix $(OBJSDIR),$(OBJECTS)))

all: dist
ifeq ($(SHELL),cmd)
	if not exist $(DIST)\utilities md $(DIST)\utilities
	xcopy ..\utilities $(DIST)\utilities /S /Y /D
	$(MAKE) copy
  ifeq ($(DEBUG),yes)
	$(MAKE) --directory=..\build\debug\src dist-clean
  else
	$(MAKE) --directory=..\build\dist\src dist-clean
  endif
else
	cp -vRf ../utilities ${DIST}
	$(MAKE) copy
  ifeq ($(DEBUG),yes)
	$(MAKE) --directory=../build/debug/src dist-clean
  else
	$(MAKE) --directory=../build/dist/src dist-clean
  endif
endif
	@echo ADMB build completed.
	@echo Check README.txt for usage and installation information.

shared: dirs
	$(MAKE) objects
ifeq ($(DEBUG),yes)
  ifeq ($(SHELL),cmd)
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\debug\lib\admb.dll -Wl,--whole-archive ..\build\debug\lib\libadmb-shared.a -Wl,--no-whole-archive
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\debug\lib\admbo.dll -Wl,--whole-archive ..\build\debug\lib\libadmbo-shared.a -Wl,--no-whole-archive
  else
    ifeq (clang,$(findstring clang,$(shell $(CXX) --version)))
	$(CXX) -shared $(LDFLAGS) -o ../build/debug/lib/libadmb.so -Wl,-force_load ../build/debug/lib/libadmb-shared.a
	$(CXX) -shared $(LDFLAGS) -o ../build/debug/lib/libadmbo.so -Wl,-force_load ../build/debug/lib/libadmbo-shared.a
    else
	$(CXX) -shared $(LDFLAGS) -o ../build/debug/lib/libadmb.so -Wl,--whole-archive ../build/debug/lib/libadmb-shared.a -Wl,--no-whole-archive
	$(CXX) -shared $(LDFLAGS) -o ../build/debug/lib/libadmbo.so -Wl,--whole-archive ../build/debug/lib/libadmbo-shared.a -Wl,--no-whole-archive
    endif
  endif
else
  ifeq ($(SHELL),cmd)
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\dist\lib\admb.dll -Wl,--whole-archive ..\build\dist\lib\libadmb-shared.a -Wl,--no-whole-archive
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\dist\lib\admbo.dll -Wl,--whole-archive ..\build\dist\lib\libadmbo-shared.a -Wl,--no-whole-archive
  else
    ifeq (clang,$(findstring clang,$(shell $(CXX) --version)))
	$(CXX) -shared $(LDFLAGS) -o ../build/dist/lib/libadmb.so -Wl,-force_load ../build/dist/lib/libadmb-shared.a
	$(CXX) -shared $(LDFLAGS) -o ../build/dist/lib/libadmbo.so -Wl,-force_load ../build/dist/lib/libadmbo-shared.a
    else
	$(CXX) -shared $(LDFLAGS) -o ../build/dist/lib/libadmb.so -Wl,--whole-archive ../build/dist/lib/libadmb-shared.a -Wl,--no-whole-archive
	$(CXX) -shared $(LDFLAGS) -o ../build/dist/lib/libadmbo.so -Wl,--whole-archive ../build/dist/lib/libadmbo-shared.a -Wl,--no-whole-archive
    endif
  endif
endif

dist: bins
	$(MAKE) libs
ifeq ($(SHELL),cmd)
	copy /Y ..\LICENSE.txt ${DIST}
	copy /Y ..\README.txt ${DIST}
	copy /Y ..\CHANGES.txt ${DIST}
	copy /Y ..\VERSION ${DIST}
	copy /Y ..\Makefile ${DIST}
else
	cp -f ../LICENSE.txt ${DIST}
	cp -f ../README.txt ${DIST}
	cp -f ../CHANGES.txt ${DIST}
	cp -f ../VERSION ${DIST}
	cp -f ../Makefile ${DIST}
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
	if not exist $(DIST)\include\contrib md $(DIST)\include\contrib
	copy nh99\nocontrib.h $(DIST)\include\contrib\contrib.h
	$(MAKE) --directory=df1b2-separable CC=gcc DIST=..\${DIST} bins
	$(MAKE) --directory=nh99 CC=gcc DIST=..\${DIST} bins
else
	mkdir -p ${DIST}/bin
	cp df1b2-separable/seddf1b* df1b2-separable/sedf1b2* ${DIST}/bin
  ifdef BUILD_SHARED_LIBRARY
	cp ../scripts/admb/adlink-shared ${DIST}/bin/adlink
  endif
	echo "ADMB_CFG_CXX=\"$(USER_CXX)\"">${DIST}/bin/admb-cfg.sh
	echo "ADMB_CFG_CXXFLAGS=\"$(USER_CXXFLAGS)\"">>${DIST}/bin/admb-cfg.sh
  ifeq ($(OS),Windows_NT)
	echo "ADMB_CFG_LDFLAGS=\"-static $(USER_LDFLAGS)\"">>${DIST}/bin/admb-cfg.sh
	cp ../scripts/admb/admb ${DIST}/bin/admb.sh
    ifeq ($(DEBUG),yes)
	cp ../scripts/admb/root-admb-debug.sh ../admb.sh
	cp ../scripts/admb/root-admb-debug.sh ${DIST}/admb.sh
    else
	cp ../scripts/admb/root-admb.sh ../admb.sh
	cp ../scripts/admb/root-admb.sh ${DIST}/admb.sh
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
	echo "ADMB_CFG_LDFLAGS=\"$(USER_LDFLAGS)\"">>${DIST}/bin/admb-cfg.sh
	cp ../scripts/admb/admb ${DIST}/bin
	cp ../scripts/admb/adlink ${DIST}/bin
	cp ../scripts/admb/adcomp ${DIST}/bin
	ln -sf bin/admb ${DIST}
	#cp ../scripts/admb/root-admb ${DIST}/admb
    ifeq ($(DEBUG),yes)
	ln -sf build/debug/bin/admb ..
    else
	ln -sf build/dist/bin/admb ..
    endif
	#cp ../scripts/admb/root-admb ../admb
  endif
	mkdir -p $(DIST)/include/contrib
	touch $(DIST)/include/contrib/contrib.h
    ifeq ($(DEBUG),yes)
	$(MAKE) --directory=df1b2-separable CC=$(CC) DIST=${DIST} bins
	$(MAKE) --directory=nh99 CC=$(CC) DIST=${DIST} bins
    else
	$(MAKE) --directory=df1b2-separable CC=$(CC) DIST=../${DIST} bins
	$(MAKE) --directory=nh99 CC=$(CC) DIST=../${DIST} bins
    endif
endif

ifndef SHARED
libs:  includes
else
libs: dirs
endif
	$(MAKE) objects
ifeq ($(SHELL),cmd)
	if not exist ${DIST}\lib md ${DIST}\lib
	if exist ${DIST}\lib\libadmb$(SHARED).a del ${DIST}\lib\libadmb$(SHARED).a
	if exist ${DIST}\lib\libadmbo$(SHARED).a del ${DIST}\lib\libadmbo$(SHARED).a
else
	mkdir -p ${DIST}/lib
	rm -vf ${DIST}/lib/libadmb$(SHARED).a
	rm -vf ${DIST}/lib/libadmbo$(SHARED).a
endif
	$(AR) -rs $(LIBSDIR)libadmb$(SHARED).a $(OBJSDIR)saflp-linad99-*.obj
	$(AR) -rs $(LIBSDIR)libadmb$(SHARED).a $(OBJSDIR)saflp-df1b2-separable-*.obj
	$(AR) -rs $(LIBSDIR)libadmb$(SHARED).a $(OBJSDIR)saflp-nh99-*.obj
	$(AR) -rs $(LIBSDIR)libadmb$(SHARED).a $(OBJSDIR)saflp-tools99-*.obj
	$(AR) -rs $(LIBSDIR)libadmb$(SHARED).a $(OBJSDIR)saflp-sparse-*.obj
ifndef COVERAGE
	$(AR) -rs $(LIBSDIR)libadmbo$(SHARED).a $(OBJSDIR)optlp-linad99-*.obj
	$(AR) -rs $(LIBSDIR)libadmbo$(SHARED).a $(OBJSDIR)optlp-df1b2-separable-*.obj
	$(AR) -rs $(LIBSDIR)libadmbo$(SHARED).a $(OBJSDIR)optlp-nh99-*.obj
	$(AR) -rs $(LIBSDIR)libadmbo$(SHARED).a $(OBJSDIR)optlp-tools99-*.obj
	$(AR) -rs $(LIBSDIR)libadmbo$(SHARED).a $(OBJSDIR)optlp-sparse-*.obj
endif

objects: $(OBJECTS)

ifeq ($(SHELL),cmd)
$(OBJSDIR)optlp-nh99-banner.obj: nh99\banner.cpp
ifeq ($(ADMB_VERSION),)
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<
else
	$(CXX) -c $(subst -I,-DADMB_VERSION=$(ADMB_VERSION) -I,$(CXXFLAGS_OPT_LIB)) -o $@ $<
endif
$(OBJSDIR)saflp-nh99-banner.obj: nh99\banner.cpp
ifeq ($(ADMB_VERSION),)
	$(CXX) -c $(CXXFLAGS) -o $@ $<
else
	$(CXX) -c $(subst -I,-DADMB_VERSION=$(ADMB_VERSION) -I,$(CXXFLAGS)) -o $@ $<
endif

$(OBJSDIR)optlp-sparse-hs_sparse.obj: sparse\hs_sparse.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

$(OBJSDIR)saflp-sparse-hs_sparse.obj: sparse\hs_sparse.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(OBJSDIR)optlp-df1b2-separable-%.obj: df1b2-separable\%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

$(OBJSDIR)saflp-df1b2-separable-%.obj: df1b2-separable\%.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(OBJSDIR)optlp-linad99-%.obj:linad99\%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

$(OBJSDIR)saflp-linad99-%.obj:linad99\%.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(OBJSDIR)optlp-nh99-%.obj:nh99\%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

$(OBJSDIR)saflp-nh99-%.obj:nh99\%.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(OBJSDIR)optlp-tools99-%.obj:tools99\%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<

$(OBJSDIR)saflp-tools99-%.obj:tools99\%.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<
else
$(OBJSDIR)optlp-nh99-banner.obj: nh99/banner.cpp
ifeq ($(ADMB_VERSION),)
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o $@ $<
else
	$(CXX) -c $(subst -I,-DADMB_VERSION=$(ADMB_VERSION) -I,$(CXXFLAGS_OPT_LIB)) -o $@ $<
endif
$(OBJSDIR)saflp-nh99-banner.obj: nh99/banner.cpp
ifeq ($(ADMB_VERSION),)
	$(CXX) -c $(CXXFLAGS) -o $@ $<
else
	$(CXX) -c $(subst -I,-DADMB_VERSION=$(ADMB_VERSION) -I,$(CXXFLAGS)) -o $@ $<
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
	$(CXX) -c $(CXXFLAGS) -o $@ $<

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
	$(CXX) -c $(CXXFLAGS) -o $@ $<

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
	$(CXX) -c $(CXXFLAGS) -o $@ $<

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
	$(CXX) -c $(CXXFLAGS) -o $@ $<

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
	$(CXX) -c $(CXXFLAGS) -o $@ $<
endif

includes: dirs
ifeq ($(SHELL),cmd)
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

dirs:
ifeq ($(SHELL),cmd)
	if not exist $(OBJSDIR) md $(OBJSDIR)
else
  ifeq ($(DEBUG),yes)
	mkdir -p ../build/objects/debug/
  else
	mkdir -p ../build/objects/dist/
  endif
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
	chmod a+rx ../build/debug/bin/admb
	chmod a+rx ../build/debug/bin/adlink
	chmod a+rx ../build/debug/bin/adcomp
	chmod a+rx ../build/debug/contrib
	chmod a+r ../build/debug/bin/sed*
	chmod a+r ../build/debug/include/*.*
	chmod a+r ../build/debug/contrib/include/*.*
  endif
	cp -Rvf ../build/debug $(INSTALL_DIR)admb
else
  ifeq ($(INSTALL_DIR),/usr/local/)
	chmod a+rx ../build/dist/bin/admb
	chmod a+rx ../build/dist/bin/adlink
	chmod a+rx ../build/dist/bin/adcomp
	chmod a+rx ../build/dist/contrib
	chmod a+r ../build/dist/bin/sed*
	chmod a+r ../build/dist/include/*.*
	chmod a+r ../build/dist/contrib/include/*.*
  endif
	cp -Rvf ../build/dist $(INSTALL_DIR)admb
endif
	ln -svf $(INSTALL_DIR)admb/bin/admb $(INSTALL_DIR)bin/admb

copy:
ifeq ($(SHELL),cmd)
	if not exist $(DIST)\src md $(DIST)\src
	xcopy ..\src $(DIST)\src /S /Y /D
	if not exist $(DIST)\scripts md $(DIST)\scripts 
	xcopy ..\scripts $(DIST)\scripts /S /Y /D
	$(MAKE) --directory=$(DIST)/scripts clean
	if not exist $(DIST)\examples md $(DIST)\examples
	xcopy ..\examples $(DIST)\examples /S /Y /D
	$(MAKE) --directory=..\contrib copy
	$(MAKE) --directory=..\tests copy
else
	cp -R ../src $(DIST)
	cp -R ../scripts $(DIST)
	$(MAKE) --directory=$(DIST)/scripts clean
	cp -R ../examples $(DIST)
	$(MAKE) --directory=../contrib copy
	$(MAKE) --directory=../tests copy
endif

coding-standard: cpplint.py
	python cpplint.py --linelength=80 --extension=c,cpp,h,hpp --filter=-,+whitespace/tab,+whitespace/blank_line,+whitespace/line_length,+whitespace/end_of_line df1b2-separable/*.h* linad99/*.h* nh99/*.h* sparse/*.h* tools99/*.h* df1b2-separable/*.cpp linad99/*.cpp nh99/*.cpp sparse/*.cpp tools99/*.cpp

cpplint.py:
	svn cat https://github.com/google/styleguide/trunk/cpplint/cpplint.py > cpplint.py

check:
	@echo "SHELL: $(SHELL)"
	@echo "PATH: $(PATH)"
	@echo "TERM: $(TERM)"
	@echo "MAKE: $(MAKE)"
	@echo "CXX: $(CXX)"
	@echo "OS: $(OS)"
	@echo "OSTYPE: $(OSTYPE)"
