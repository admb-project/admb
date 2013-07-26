.NOTPARALLEL: all libs contrib

INSTALL_DIR=/usr/local/

ifeq ($(OS),Windows_NT)
  ifdef TERM
    ifeq ("$(TERM)","xterm")
      TERMINAL=cygwin
    endif
    ifeq ("$(TERM)","cygwin")
      TERMINAL=cygwin
    endif
  else
    TERMINAL=dos
    SHELL=cmd
  endif
endif

ifeq ($(TERMINAL),dos)
  DISK=..\build\dist
  LIBPATH=..\build\objects\dist
  PWD=$(shell cd)
  PATH:=$(PATH);..\utilities\mingw\bin;..\utilities
else
  DISK=../build/dist
  LIBPATH=../build/objects/dist
  PWD=$(shell pwd)
endif

ifdef DEBUG
CXXFLAGS_PRE:=-g
else
  ifeq ($(CXX),openCC)
    CXXFLAGS_PRE:=-O2
  else
    CXXFLAGS_PRE:=-O3
  endif
endif

ifdef BUILD_SHARED_LIBRARY
CXXFLAGS_PRE:=$(CXXFLAGS_PRE) -fPIC
endif

ifneq ($(CXX),CC)
CXXFLAGS_PRE:=$(CXXFLAGS_PRE) -Wall
endif

CXXFLAGS_DEFINES:=-D__GNUDOS__ -Dlinux -D__SPDLL__ -DUSE_LAPLACE

ifeq ($(TERMINAL),dos)
CXXFLAGS_INCLUDES:=-I..\build\dist\include
CXXFLAGS_INCLUDES_CONTRIB:=-I..\..\build\dist\include
else
CXXFLAGS_INCLUDES:=-I../build/dist/include
CXXFLAGS_INCLUDES_CONTRIB:=-I../../build/dist/include
endif

ifdef CXXFLAGS
CXXFLAGS_OPT:=$(CXXFLAGS_PRE) $(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_DEFINES) $(CXXFLAGS_INCLUDES)
CXXFLAGS_SAFE:=$(CXXFLAGS_PRE) $(CXXFLAGS) -DSAFE_ALL $(CXXFLAGS_DEFINES) $(CXXFLAGS_INCLUDES)
CXXFLAGS_OPT_CONTRIB:=$(CXXFLAGS_PRE) $(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_DEFINES) $(CXXFLAGS_INCLUDES_CONTRIB)
CXXFLAGS_SAFE_CONTRIB:=$(CXXFLAGS_PRE) $(CXXFLAGS) -DSAFE_ALL $(CXXFLAGS_DEFINES) $(CXXFLAGS_INCLUDES_CONTRIB)
else
CXXFLAGS_OPT:=$(CXXFLAGS_PRE) -DOPT_LIB $(CXXFLAGS_DEFINES) $(CXXFLAGS_INCLUDES)
CXXFLAGS_SAFE:=$(CXXFLAGS_PRE) -DSAFE_ALL $(CXXFLAGS_DEFINES) $(CXXFLAGS_INCLUDES)
CXXFLAGS_OPT_CONTRIB:=$(CXXFLAGS_PRE) -DOPT_LIB $(CXXFLAGS_DEFINES) $(CXXFLAGS_INCLUDES_CONTRIB)
CXXFLAGS_SAFE_CONTRIB:=$(CXXFLAGS_PRE) -DSAFE_ALL $(CXXFLAGS_DEFINES) $(CXXFLAGS_INCLUDES_CONTRIB)
endif

include df1b2-separable/objects.lst
ifeq ($(TERMINAL),dos)
OPTLP_DF1B2_SEPARABLE_OBJS=$(sort $(addprefix ..\build\objects\dist\optlp-df1b2-separable-,$(OBJ0)))
SAFLP_DF1B2_SEPARABLE_OBJS=$(sort $(addprefix ..\build\objects\dist\saflp-df1b2-separable-,$(OBJ0)))
else
OPTLP_DF1B2_SEPARABLE_OBJS=$(sort $(addprefix ../build/objects/dist/optlp-df1b2-separable-,$(OBJ0)))
SAFLP_DF1B2_SEPARABLE_OBJS=$(sort $(addprefix ../build/objects/dist/saflp-df1b2-separable-,$(OBJ0)))
endif

include linad99/objects.lst
ifeq ($(TERMINAL),dos)
OPTLP_LINAD99_OBJS=$(sort $(addprefix ..\build\objects\dist\optlp-linad99-,$(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)))
SAFLP_LINAD99_OBJS=$(sort $(addprefix ..\build\objects\dist\saflp-linad99-,$(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)))
else
OPTLP_LINAD99_OBJS=$(sort $(addprefix ../build/objects/dist/optlp-linad99-,$(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)))
SAFLP_LINAD99_OBJS=$(sort $(addprefix ../build/objects/dist/saflp-linad99-,$(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)))
endif

include nh99/objects.lst
ifeq ($(CXX),CC)
 ifeq ($(TERMINAL),dos)
 OPTLP_NH99_OBJS=$(sort $(addprefix ..\build\objects\dist\optlp-nh99-,$(filter-out dfqromb.obj,$(OBJ6)))) ..\build\objects\dist\optlp-sparse-hs_sparse.obj
 SAFLP_NH99_OBJS=$(sort $(addprefix ..\build\objects\dist\saflp-nh99-,$(filter-out dfqromb.obj,$(OBJ6)))) ..\build\objects\dist\saflp-sparse-hs_sparse.obj
 else
 OPTLP_NH99_OBJS=$(sort $(addprefix ../build/objects/dist/optlp-nh99-,$(filter-out dfqromb.obj,$(OBJ6)))) ../build/objects/dist/optlp-sparse-hs_sparse.obj
 SAFLP_NH99_OBJS=$(sort $(addprefix ../build/objects/dist/saflp-nh99-,$(filter-out dfqromb.obj,$(OBJ6)))) ../build/objects/dist/saflp-sparse-hs_sparse.obj
 endif
else
 ifeq ($(TERMINAL),dos)
 OPTLP_NH99_OBJS=$(sort $(addprefix ..\build\objects\dist\optlp-nh99-,$(OBJ6))) ..\build\objects\dist\optlp-sparse-hs_sparse.obj
 SAFLP_NH99_OBJS=$(sort $(addprefix ..\build\objects\dist\saflp-nh99-,$(OBJ6))) ..\build\objects\dist\saflp-sparse-hs_sparse.obj
 else
 OPTLP_NH99_OBJS=$(sort $(addprefix ../build/objects/dist/optlp-nh99-,$(OBJ6))) ../build/objects/dist/optlp-sparse-hs_sparse.obj
 SAFLP_NH99_OBJS=$(sort $(addprefix ../build/objects/dist/saflp-nh99-,$(OBJ6))) ../build/objects/dist/saflp-sparse-hs_sparse.obj
 endif
endif

include tools99/objects.lst
ifeq ($(TERMINAL),dos)
OPTLP_TOOLS99_OBJS=$(sort $(addprefix ..\build\objects\dist\optlp-tools99-,$(OBJ7)))
SAFLP_TOOLS99_OBJS=$(sort $(addprefix ..\build\objects\dist\saflp-tools99-,$(OBJ7)))
else
OPTLP_TOOLS99_OBJS=$(sort $(addprefix ../build/objects/dist/optlp-tools99-,$(OBJ7)))
SAFLP_TOOLS99_OBJS=$(sort $(addprefix ../build/objects/dist/saflp-tools99-,$(OBJ7)))
endif

all: revision dist contrib
ifdef USE_DOS
	pushd $(DISK) & cscript ..\..\scripts\create-admb-shortcut.vbs & popd
endif
ifndef BUILD_SHARED_LIBRARY
	$(MAKE) CXXFLAGS="$(CXXFLAGS)" ADMB_HOME="$(PWD)/${DISK}" --directory=../contrib build-ad2csv
endif
	@echo ADMB build completed.
	@echo For installation, check README.txt.

shared: objects
	g++ -shared -o${DISK}/lib/libadmb.so ../build/objects/dist/saflp-linad99-*.obj ../build/objects/dist/saflp-df1b2-separable-*.obj ../build/objects/dist/optlp-nh99-*.obj ../build/objects/dist/optlp-tools99-*.obj ../build/objects/dist/saflp-contrib-*.obj
	g++ -shared -o${DISK}/lib/libadmbo.so ../build/objects/dist/optlp-*.obj
	$(MAKE) CXXFLAGS="$(CXXFLAGS)" ADMB_HOME="$(PWD)/${DISK}" --directory=../contrib build-ad2csv
	@echo ADMB shared build completed.
	@echo For installation, check README.txt.

revision:
	-svnversion .. > ../REVISION
dist:
ifeq ($(TERMINAL),dos)
	if not exist ${DISK} md ${DISK}
	if not exist ${LIBPATH} md ${LIBPATH}
	if not exist ${DISK}\contrib md ${DISK}\contrib
	xcopy ..\contrib $(DISK)\contrib /S /Y /D
	if not exist ${DISK}\docs md ${DISK}\docs
	xcopy ..\docs $(DISK)\docs /S /Y /D
	if not exist ${DISK}\examples md ${DISK}\examples
	xcopy ..\examples $(DISK)\examples /S /Y /D
	if not exist ${DISK}\src md ${DISK}\src
	xcopy ..\src $(DISK)\src /S /Y /D
	if not exist ${DISK}\scripts md ${DISK}\scripts
	xcopy ..\scripts $(DISK)\scripts /S /Y /D
	if not exist ${DISK}\tests md ${DISK}\tests
	xcopy ..\tests $(DISK)\tests /S /Y /D
	if not exist ${DISK}\utilities md ${DISK}\utilities
	copy /Y ..\LICENSE.txt ${DISK}
	copy /Y ..\README.txt ${DISK}
	copy /Y ..\CHANGES.txt ${DISK}
	copy /Y ..\VERSION ${DISK}
	copy /Y ..\Makefile ${DISK}
else
	rm -rf ${DISK}
	mkdir -p ${DISK}
	cp -R ../contrib ${DISK}
	cp -R ../docs ${DISK} 
	cp -R ../examples ${DISK}
	cp -R ../src ${DISK}
	cp -R ../scripts ${DISK}
	cp -R ../tests ${DISK}
	cp -R ../utilities ${DISK}
	cp -f ../LICENSE.txt ${DISK}
	cp -f ../README.txt ${DISK}
	cp -f ../CHANGES.txt ${DISK}
	cp -f ../VERSION ${DISK}
	cp -f ../Makefile ${DISK}
	rm -rf `find ${DISK} -type d -name .svn`
	mkdir -p ../build/objects/dist/
endif

contrib: includes bins libs
ifeq ($(TERMINAL),dos)
	if not exist ${DISK}\contrib md ${DISK}\contrib
	if not exist ${DISK}\contrib\lib md ${DISK}\contrib\lib
	if not exist ${DISK}\contrib\bin md ${DISK}\contrib\bin
	if not exist ${DISK}\contrib\include md ${DISK}\contrib\include
	$(MAKE) CXXFLAGS_OPT_CONTRIB="$(CXXFLAGS_OPT_CONTRIB)" CXXFLAGS_SAFE_CONTRIB="$(CXXFLAGS_SAFE_CONTRIB)" ADMB_HOME="$(PWD)\${DISK}" --directory=..\contrib
else
	mkdir -p ${DISK}/contrib/lib
	mkdir -p ${DISK}/contrib/bin
	mkdir -p ${DISK}/contrib/include
	$(MAKE) CXXFLAGS_OPT_CONTRIB="$(CXXFLAGS_OPT_CONTRIB)" CXXFLAGS_SAFE_CONTRIB="$(CXXFLAGS_SAFE_CONTRIB)" ADMB_HOME="$(PWD)/${DISK}" --directory=../contrib
endif

libs: objects
ifeq ($(TERMINAL),dos)
	if not exist ${DISK}\lib md ${DISK}\lib
	if exist ${DISK}\lib\libadmb.a del ${DISK}\lib\libadmb.a
	$(AR) -rs ${DISK}\lib\libadmb.a ..\build\objects\dist\saflp-linad99-*.obj
	$(AR) -rs ${DISK}\lib\libadmb.a ..\build\objects\dist\saflp-df1b2-separable-*.obj
	$(AR) -rs ${DISK}\lib\libadmb.a ..\build\objects\dist\optlp-nh99-*.obj
	$(AR) -rs ${DISK}\lib\libadmb.a ..\build\objects\dist\optlp-tools99-*.obj
	$(AR) -rs ${DISK}\lib\libadmb.a ..\build\objects\dist\optlp-sparse-*.obj
	if exist ${DISK}\lib\libadmbo.a del ${DISK}\lib\libadmbo.a
	$(AR) -rs ${DISK}\lib\libadmbo.a ..\build\objects\dist\optlp-linad99-*.obj
	$(AR) -rs ${DISK}\lib\libadmbo.a ..\build\objects\dist\optlp-df1b2-separable-*.obj
	$(AR) -rs ${DISK}\lib\libadmbo.a ..\build\objects\dist\optlp-nh99-*.obj
	$(AR) -rs ${DISK}\lib\libadmbo.a ..\build\objects\dist\optlp-tools99-*.obj
	$(AR) -rs ${DISK}\lib\libadmbo.a ..\build\objects\dist\optlp-sparse-*.obj
else
	mkdir -p ${DISK}/lib
	rm -vf ${DISK}/lib/libadmb.a
	$(AR) -rs ${DISK}/lib/libadmb.a ../build/objects/dist/saflp-linad99-*.obj
	$(AR) -rs ${DISK}/lib/libadmb.a ../build/objects/dist/saflp-df1b2-separable-*.obj
	$(AR) -rs ${DISK}/lib/libadmb.a ../build/objects/dist/saflp-nh99-*.obj
	$(AR) -rs ${DISK}/lib/libadmb.a ../build/objects/dist/saflp-tools99-*.obj
	$(AR) -rs ${DISK}/lib/libadmb.a ../build/objects/dist/saflp-sparse-*.obj
	rm -vf ${DISK}/lib/libadmbo.a
	$(AR) -rs ${DISK}/lib/libadmbo.a ../build/objects/dist/optlp-linad99-*.obj
	$(AR) -rs ${DISK}/lib/libadmbo.a ../build/objects/dist/optlp-df1b2-separable-*.obj
	$(AR) -rs ${DISK}/lib/libadmbo.a ../build/objects/dist/optlp-nh99-*.obj
	$(AR) -rs ${DISK}/lib/libadmbo.a ../build/objects/dist/optlp-tools99-*.obj
	$(AR) -rs ${DISK}/lib/libadmbo.a ../build/objects/dist/optlp-sparse-*.obj
endif

objects: $(OPTLP_DF1B2_SEPARABLE_OBJS) $(SAFLP_DF1B2_SEPARABLE_OBJS) $(OPTLP_LINAD99_OBJS) $(SAFLP_LINAD99_OBJS) $(OPTLP_NH99_OBJS) $(SAFLP_NH99_OBJS) $(OPTLP_TOOLS99_OBJS) $(SAFLP_TOOLS99_OBJS)

ifeq ($(TERMINAL),dos)
..\build\objects\dist\optlp-nh99-banner.obj: nh99\banner.cpp
	$(CXX) -c $(CXXFLAGS_OPT) -DADMB_VERSION=$(shell cat ../../VERSION) -DADMB_REVISION=$(shell test -e ../../REVISION && cat ../../REVISION) -o$@ $<

..\build\objects\dist\saflp-nh99-banner.obj: nh99\banner.cpp
	$(CXX) -c $(CXXFLAGS_SAFE) -DADMB_VERSION=$(shell cat ../../VERSION) -DADMB_REVISION=$(shell test -e ../../REVISION && cat ../../REVISION) -o$@ $<

..\build\objects\dist\optlp-sparse-hs_sparse.obj: sparse\hs_sparse.cpp
	$(CXX) -c $(CXXFLAGS_OPT) -o$@ $<

..\build\objects\dist\saflp-sparse-hs_sparse.obj: sparse\hs_sparse.cpp
	$(CXX) -c $(CXXFLAGS_SAFE) -o$@ $<

..\build\objects\dist\optlp-df1b2-separable-%.obj: df1b2-separable\%.cpp
	$(CXX) -c $(CXXFLAGS_OPT) -o$@ $<

..\build\objects\dist\saflp-df1b2-separable-%.obj: df1b2-separable\%.cpp
	$(CXX) -c $(CXXFLAGS_SAFE) -o$@ $<

..\build\objects\dist\optlp-linad99-%.obj:linad99\%.cpp
	$(CXX) -c $(CXXFLAGS_OPT) -o$@ $<

..\build\objects\dist\saflp-linad99-%.obj:linad99\%.cpp
	$(CXX) -c $(CXXFLAGS_SAFE) -o$@ $<

..\build\objects\dist\optlp-nh99-%.obj:nh99\%.cpp
	$(CXX) -c $(CXXFLAGS_OPT) -o$@ $<

..\build\objects\dist\saflp-nh99-%.obj:nh99\%.cpp
	$(CXX) -c $(CXXFLAGS_SAFE) -o$@ $<

..\build\objects\dist\optlp-tools99-%.obj:tools99\%.cpp
	$(CXX) -c $(CXXFLAGS_OPT) -o$@ $<

..\build\objects\dist\saflp-tools99-%.obj:tools99\%.cpp
	$(CXX) -c $(CXXFLAGS_SAFE) -o$@ $<
else
../build/objects/dist/optlp-nh99-banner.obj: nh99/banner.cpp
	$(CXX) -c $(CXXFLAGS_OPT) -DADMB_VERSION=$(shell cat ../../VERSION) -DADMB_REVISION=$(shell test -e ../../REVISION && cat ../../REVISION) -o$@ $<

../build/objects/dist/saflp-nh99-banner.obj: nh99/banner.cpp
	$(CXX) -c $(CXXFLAGS_SAFE) -DADMB_VERSION=$(shell cat ../../VERSION) -DADMB_REVISION=$(shell test -e ../../REVISION && cat ../../REVISION) -o$@ $<

../build/objects/dist/optlp-sparse-hs_sparse.obj: sparse/hs_sparse.cpp
	$(CXX) -c $(CXXFLAGS_OPT) -o$@ $<

../build/objects/dist/saflp-sparse-hs_sparse.obj: sparse/hs_sparse.cpp
	$(CXX) -c $(CXXFLAGS_SAFE) -o$@ $<

../build/objects/dist/optlp-df1b2-separable-%.obj:df1b2-separable/%.cpp
	$(CXX) -c $(CXXFLAGS_OPT) -o$@ $<

../build/objects/dist/saflp-df1b2-separable-%.obj:df1b2-separable/%.cpp
	$(CXX) -c $(CXXFLAGS_SAFE) -o$@ $<

../build/objects/dist/optlp-linad99-%.obj:linad99/%.cpp
	$(CXX) -c $(CXXFLAGS_OPT) -o$@ $<

../build/objects/dist/saflp-linad99-%.obj:linad99/%.cpp
	$(CXX) -c $(CXXFLAGS_SAFE) -o$@ $<

../build/objects/dist/optlp-nh99-%.obj:nh99/%.cpp
	$(CXX) -c $(CXXFLAGS_OPT) -o$@ $<

../build/objects/dist/saflp-nh99-%.obj:nh99/%.cpp
	$(CXX) -c $(CXXFLAGS_SAFE) -o$@ $<

../build/objects/dist/optlp-tools99-%.obj:tools99/%.cpp
	$(CXX) -c $(CXXFLAGS_OPT) -o$@ $<

../build/objects/dist/saflp-tools99-%.obj:tools99/%.cpp
	$(CXX) -c $(CXXFLAGS_SAFE) -o$@ $<
endif

includes:
ifeq ($(TERMINAL),dos)
	if not exist ${DISK}\include md ${DISK}\include
	copy linad99\fvar.hpp ${DISK}\include
	copy linad99\dfpool.h ${DISK}\include
	copy linad99\trunc.hpp ${DISK}\include
	copy linad99\factors.h ${DISK}\include
	copy tools99\adoption.hpp ${DISK}\include
	copy tools99\adstring.hpp ${DISK}\include
	copy tools99\cifstrem.h ${DISK}\include
	copy tools99\clist.h ${DISK}\include
	copy tools99\admb_messages.h ${DISK}\include
	copy df1b2-separable\adpool.h ${DISK}\include
	copy df1b2-separable\adrndeff.h ${DISK}\include
	copy df1b2-separable\df1b2fun.h ${DISK}\include
	copy df1b2-separable\df32fun.h ${DISK}\include
	copy df1b2-separable\df3fun.h ${DISK}\include
	copy df1b2-separable\df1b2fnl.h ${DISK}\include
	copy df1b2-separable\df1b2loc.h ${DISK}\include
	copy df1b2-separable\smartbuf.h ${DISK}\include
	copy nh99\admodel.h ${DISK}\include
	copy nh99\adsplus.h ${DISK}\include
	copy nh99\spcomm.h ${DISK}\include
	copy nh99\s.h ${DISK}\include
	copy nh99\newredef.h ${DISK}\include
	copy nh99\param_init_bounded_number_matrix.h ${DISK}\include
	copy nh99\gccmanip.h ${DISK}\include
else
	mkdir -p ${DISK}/include
	cp linad99/fvar.hpp ${DISK}/include
	cp linad99/dfpool.h ${DISK}/include
	cp linad99/trunc.hpp ${DISK}/include
	cp linad99/factors.h ${DISK}/include
	cp tools99/adoption.hpp ${DISK}/include
	cp tools99/adstring.hpp ${DISK}/include
	cp tools99/cifstrem.h ${DISK}/include
	cp tools99/clist.h ${DISK}/include
	cp tools99/admb_messages.h ${DISK}/include
	cp df1b2-separable/adpool.h ${DISK}/include
	cp df1b2-separable/adrndeff.h ${DISK}/include
	cp df1b2-separable/df1b2fun.h ${DISK}/include
	cp df1b2-separable/df32fun.h ${DISK}/include
	cp df1b2-separable/df3fun.h ${DISK}/include
	cp df1b2-separable/df1b2fnl.h ${DISK}/include
	cp df1b2-separable/df1b2loc.h ${DISK}/include
	cp df1b2-separable/smartbuf.h ${DISK}/include
	cp nh99/admodel.h ${DISK}/include
	cp nh99/adsplus.h ${DISK}/include
	cp nh99/spcomm.h ${DISK}/include
	cp nh99/s.h ${DISK}/include
	cp nh99/newredef.h ${DISK}/include
	cp nh99/param_init_bounded_number_matrix.h ${DISK}/include
	cp nh99/gccmanip.h ${DISK}/include
endif

bins:
ifeq ($(TERMINAL),dos)
	if not exist ${DISK}\bin md ${DISK}\bin
	copy df1b2-separable\seddf1b* ${DISK}\bin
	copy df1b2-separable\sedf1b2* ${DISK}\bin
	if exist ${DISK}\bin\admb-cfg.sh del ${DISK}\bin\admb-cfg.sh
	echo "CXX=$(CXX)" > ${DISK}\bin\admb-cfg.sh
	echo "CXXFLAGS=$(CXXFLAGS)" >> ${DISK}\bin\admb-cfg.sh
  ifeq ($(OS),Windows_NT)
	echo "LDFLAGS=-static $(LDFLAGS)" >> ${DISK}\bin\admb-cfg.sh
  else
	echo "LDFLAGS=$(LDFLAGS)" >> ${DISK}\bin\admb-cfg.sh
  endif
	$(MAKE) --directory=df1b2-separable CC=$(CC) DISKDIR=..\${DISK} bins
	$(MAKE) --directory=nh99 CC=$(CC) DISKDIR=..\${DISK} bins
	copy ..\scripts\mingw\set-admb-mingw.bat ${DISK}\bin
	copy ..\utilities\sed.exe ${DISK}\bin
	copy ..\utilities\libiconv2.dll ${DISK}\bin
	copy ..\utilities\libintl3.dll ${DISK}\bin
	copy ..\utilities\regex2.dll ${DISK}\bin
	copy ..\scripts\admb\adcomp.bat ${DISK}\bin
	copy ..\scripts\admb\adlink.bat ${DISK}\bin
	copy ..\scripts\admb\admb.bat ${DISK}\bin
	copy ..\scripts\admb\root-admb.bat ..\admb.bat
else
	mkdir -p ${DISK}/bin
	cp df1b2-separable/seddf1b* df1b2-separable/sedf1b2* ${DISK}/bin
	cp ../scripts/admb/admb ${DISK}/bin
	cp ../scripts/admb/adcomp ${DISK}/bin
  ifdef BUILD_SHARED_LIBRARY
	cp ../scripts/admb/adlink-shared ${DISK}/bin/adlink
  else
	cp ../scripts/admb/adlink ${DISK}/bin
  endif
	rm -f ${DISK}/bin/admb-cfg.sh
	echo "CXX=$(CXX)" > ${DISK}/bin/admb-cfg.sh
	echo "CXXFLAGS=$(CXXFLAGS)" >> ${DISK}/bin/admb-cfg.sh
  ifeq ($(OS),Windows_NT)
	echo "LDFLAGS=-static $(LDFLAGS)" >> ${DISK}/bin/admb-cfg.sh
  else
	echo "LDFLAGS=$(LDFLAGS)" >> ${DISK}/bin/admb-cfg.sh
  endif
	$(MAKE) --directory=df1b2-separable CC=$(CC) DISKDIR=../${DISK} bins
	$(MAKE) --directory=nh99 CC=$(CC) DISKDIR=../${DISK} bins
	ln -sf bin/admb ${DISK}
	ln -sf build/dist/bin/admb ..
  ifeq ($(OS),Windows_NT)
    ifneq ("$(TERM)","xterm")
	cp ../scripts/mingw/set-admb-mingw.bat ${DISK}/bin
	cp ../utilities/sed.exe ${DISK}/bin
	cp ../utilities/libiconv2.dll ${DISK}/bin
	cp ../utilities/libintl3.dll ${DISK}/bin
	cp ../utilities/regex2.dll ${DISK}/bin
	cp ../scripts/admb/adcomp.bat ${DISK}/bin
	cp ../scripts/admb/adlink.bat ${DISK}/bin
	cp ../scripts/admb/admb.bat ${DISK}/bin
	cp ../scripts/admb/root-admb.bat ../admb.bat
    endif
  endif
endif

verify:
ifeq ($(TERMINAL),dos)
	$(MAKE) ADMB_HOME="$(CURDIR)\${DISK}" PATH="$(CURDIR)\${DISK}\bin:$(PATH):$(CURDIR)\..\utilities:$(CURDIR)\..\utilities\mingw\bin" SAFE_OPTION=1 -C $(DISK)\examples --file=Makefile all
	pushd ..\build\dist & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-saf.txt" & popd
	$(MAKE) ADMB_HOME="$(CURDIR)\${DISK}" PATH="$(CURDIR)\${DISK}\bin:$(PATH):$(CURDIR)\..\utilities:$(CURDIR)\..\utilities\mingw\bin" -C $(DISK)\examples --file=Makefile all
	pushd ..\build\dist & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-saf.txt" & popd
else
	PATH="${PWD}/${DISK}/bin:$(PATH)" SAFE_OPTION=1 $(MAKE) -C $(DISK)/examples all
	-../scripts/get-outputs.sh ${DISK}/examples/ > "../benchmarks-saf.txt"
	PATH="${PWD}/${DISK}/bin:$(PATH)" $(MAKE) -C $(DISK)/examples all
	-../scripts/get-outputs.sh ${DISK}/examples/ > "../benchmarks-opt.txt"
endif

tests:
ifndef USE_ADMB_HOME
	$(MAKE) ADMB_HOME="${PWD}/${DISK}" --directory=../contrib test
	$(MAKE) ADMB_HOME="${PWD}/${DISK}" --directory=../tests
else
	$(MAKE) ADMB_HOME="${ADMB_HOME}" --directory=../contrib test
	$(MAKE) ADMB_HOME="${ADMB_HOME}" --directory=../tests
endif

install:
	@#echo "Read INSTALL.txt for installation instructions."
	cp -Rf ../build/dist $(INSTALL_DIR)admb
	ln -sf $(INSTALL_DIR)admb/bin/admb $(INSTALL_DIR)bin/admb

clean:
ifeq ($(TERMINAL),dos)
	if exist build rd /S /Q ..\build
	if exist ..\admb.bat del ..\admb.bat
else
	@rm -f nh99/lex.yy.c
	@rm -f df1b2-separable/lex.yy.c
	@rm -f nh99/tpl2cpp
	@rm -f df1b2-separable/tpl2rem
	@rm -f nh99/tpl2cpp.c
	@rm -f df1b2-separable/tpl2rem.c
	@rm -rf ../build
	@$(MAKE) --directory=../contrib clean
	@$(MAKE) --directory=../tests clean
	@rm -f ../admb
endif
