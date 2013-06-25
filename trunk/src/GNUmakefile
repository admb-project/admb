.NOTPARALLEL: all libs contrib

INSTALL_DIR=/usr/local/

ifeq ($(SHELL),sh.exe)
  DISK=..\build\dist
  LIBPATH=..\build\objects\dist
  CXXFLAGS_INCLUDES:=-I..\${DISK}\include
  PWD=$(shell cd)
  ifndef MINGW_HOME
    PATH:=..\..\utilities\mingw\bin:$(PATH)
    AR=..\utilities\mingw\bin\ar
    MAKE=..\utilities\make
  endif
else
  DISK=../build/dist
  LIBPATH=../build/objects/dist
  CXXFLAGS_INCLUDES:=-I../${DISK}/include
  PWD=$(shell pwd)
endif

ifeq ($(SHELL),sh.exe)
CXXFLAGS:=-D__GNUDOS__ -Dlinux -D__SPDLL__ -DUSE_LAPLACE -I..\build\dist\include $(CXXFLAGS)
else
CXXFLAGS:=-D__GNUDOS__ -Dlinux -D__SPDLL__ -DUSE_LAPLACE -I../build/dist/include $(CXXFLAGS)
endif

ifneq ($(CXX),CC)
CXXFLAGS:=-Wall $(CXXFLAGS)
endif

ifdef BUILD_SHARED_LIBRARY
CXXFLAGS:=-fPIC $(CXXFLAGS)
endif

ifdef DEBUG
CXXFLAGS:=-g $(CXXFLAGS)
else
CXXFLAGS:=-O3 $(CXXFLAGS)
endif

include df1b2-separable/objects.lst
OPTLP_DF1B2_SEPARABLE_OBJS=$(sort $(addprefix ../build/objects/dist/optlp-df1b2-separable-,$(OBJ0)))
SAFLP_DF1B2_SEPARABLE_OBJS=$(sort $(addprefix ../build/objects/dist/saflp-df1b2-separable-,$(OBJ0)))

include linad99/objects.lst
OPTLP_LINAD99_OBJS=$(sort $(addprefix ../build/objects/dist/optlp-linad99-,$(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)))
SAFLP_LINAD99_OBJS=$(sort $(addprefix ../build/objects/dist/saflp-linad99-,$(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)))

include nh99/objects.lst
OPTLP_NH99_OBJS=$(sort $(addprefix ../build/objects/dist/optlp-nh99-,$(filter-out dfqromb.obj,$(OBJ6))))
SAFLP_NH99_OBJS=$(sort $(addprefix ../build/objects/dist/saflp-nh99-,$(filter-out dfqromb.obj,$(OBJ6))))

include tools99/objects.lst
OPTLP_TOOLS99_OBJS=$(sort $(addprefix ../build/objects/dist/optlp-tools99-,$(OBJ7)))
SAFLP_TOOLS99_OBJS=$(sort $(addprefix ../build/objects/dist/saflp-tools99-,$(OBJ7)))

all: revision dist contrib
ifeq ($(SHELL),sh.exe)
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
ifneq ($(SHELL),sh.exe)
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
else
	if exist ${DISK} rd /S /Q ${DISK}
	md ${DISK}
	md ${DISK}\contrib
	xcopy ..\contrib $(DISK)\contrib /S
	md ${DISK}\docs
	xcopy ..\docs $(DISK)\docs /S
	md ${DISK}\examples
	xcopy ..\examples $(DISK)\examples /S
	md ${DISK}\src
	xcopy ..\src $(DISK)\src /S
	md ${DISK}\scripts
	xcopy ..\scripts $(DISK)\scripts /S
	md ${DISK}\tests
	xcopy ..\tests $(DISK)\tests /S
	md ${DISK}\utilities
	copy /Y ..\LICENSE.txt ${DISK}
	copy /Y ..\README.txt ${DISK}
	copy /Y ..\CHANGES.txt ${DISK}
	copy /Y ..\VERSION ${DISK}
	copy /Y ..\Makefile ${DISK}
endif

contrib: includes bins libs
ifneq ($(SHELL),sh.exe)
	mkdir -p ${DISK}/contrib/lib
	mkdir -p ${DISK}/contrib/bin
	mkdir -p ${DISK}/contrib/include
	$(MAKE) CXXFLAGS="$(CXXFLAGS)" ADMB_HOME="${PWD}/${DISK}" --directory=../contrib
else
	if not exist ${DISK}\contrib md ${DISK}\contrib
	if not exist ${DISK}\contrib\lib md ${DISK}\contrib\lib
	if not exist ${DISK}\contrib\bin md ${DISK}\contrib\bin
	if not exist ${DISK}\contrib\include md ${DISK}\contrib\include
	$(MAKE) CXXFLAGS="$(CXXFLAGS)" ADMB_HOME="$(PWD)\${DISK}" --directory=..\contrib
endif

libs: $(OPTLP_DF1B2_SEPARABLE_OBJS) $(SAFLP_DF1B2_SEPARABLE_OBJS) $(OPTLP_LINAD99_OBJS) $(SAFLP_LINAD99_OBJS) $(OPTLP_NH99_OBJS) $(SAFLP_NH99_OBJS) $(OPTLP_TOOLS99_OBJS) $(SAFLP_TOOLS99_OBJS) ../build/objects/dist/saflp-sparse-hs_sparse.obj ../build/objects/dist/optlp-sparse-hs_sparse.obj
ifeq ($(SHELL),sh.exe)
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

../build/objects/dist/optlp-nh99-banner.obj: nh99/banner.cpp
	$(CXX) -c -DOPT_LIB $(CXXFLAGS) -DADMB_VERSION=$(shell cat ../../VERSION) -DADMB_REVISION=$(shell test -e ../../REVISION && cat ../../REVISION) -o$@ $<

../build/objects/dist/saflp-nh99-banner.obj: nh99/banner.cpp
	$(CXX) -c -DSAFE_ALL $(CXXFLAGS) -DADMB_VERSION=$(shell cat ../../VERSION) -DADMB_REVISION=$(shell test -e ../../REVISION && cat ../../REVISION) -o$@ $<

../build/objects/dist/optlp-sparse-hs_sparse.obj: sparse/hs_sparse.cpp
	$(CXX) -c -DOPT_LIB $(CXXFLAGS) -o$@ $<

../build/objects/dist/saflp-sparse-hs_sparse.obj: sparse/hs_sparse.cpp
	$(CXX) -c -DSAFE_ALL $(CXXFLAGS) -o$@ $<

../build/objects/dist/optlp-df1b2-separable-%.obj:df1b2-separable/%.cpp
	$(CXX) -c -DOPT_LIB $(CXXFLAGS) -o$@ $<

../build/objects/dist/saflp-df1b2-separable-%.obj:df1b2-separable/%.cpp
	$(CXX) -c -DSAFE_ALL $(CXXFLAGS) -o$@ $<

../build/objects/dist/optlp-linad99-%.obj:linad99/%.cpp
	$(CXX) -c -DOPT_LIB $(CXXFLAGS) -o$@ $<

../build/objects/dist/saflp-linad99-%.obj:linad99/%.cpp
	$(CXX) -c -DSAFE_ALL $(CXXFLAGS) -o$@ $<

../build/objects/dist/saflp-nh99-%.obj:nh99/%.cpp
	$(CXX) -c -DSAFE_ALL $(CXXFLAGS) -o$@ $<

../build/objects/dist/optlp-nh99-%.obj:nh99/%.cpp
	$(CXX) -c -DOPT_LIB $(CXXFLAGS) -o$@ $<

../build/objects/dist/saflp-tools99-%.obj:tools99/%.cpp
	$(CXX) -c -DSAFE_ALL $(CXXFLAGS) -o$@ $<

../build/objects/dist/optlp-tools99-%.obj:tools99/%.cpp
	$(CXX) -c -DOPT_LIB $(CXXFLAGS) -o$@ $<

includes:
ifneq ($(SHELL),sh.exe)
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
else
	md ${DISK}\include
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
endif

bins:
ifneq ($(SHELL),sh.exe)
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
	$(MAKE) --directory=df1b2-separable CC=$(CC) DISKDIR=../${DISK} bins
	$(MAKE) --directory=nh99 CC=$(CC) DISKDIR=../${DISK} bins
	ln -sf bin/admb ${DISK}
	ln -sf build/dist/bin/admb ..
  ifdef COMSPEC
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
else
	md ${DISK}\bin
	copy df1b2-separable\seddf1b* ${DISK}\bin
	copy df1b2-separable\sedf1b2* ${DISK}\bin
	if exist ${DISK}\bin\admb-cfg.sh del ${DISK}\bin\admb-cfg.sh
	echo "CXX=$(CXX)" > ${DISK}\bin\admb-cfg.sh
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
endif

verify:
ifndef USE_ADMB_HOME
  ifneq ($(SHELL),sh.exe)
	PATH="${PWD}/${DISK}/bin:$(PATH)" CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" SAFE_OPTION=1 $(MAKE) -C $(DISK)/examples all
	-../scripts/get-outputs.sh ${DISK}/examples/ > "../benchmarks-saf.txt"
	PATH="${PWD}/${DISK}/bin:$(PATH)" CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" $(MAKE) -C $(DISK)/examples all
	-../scripts/get-outputs.sh ${DISK}/examples/ > "../benchmarks-opt.txt"
  else
	$(MAKE) ADMB_HOME="$(CURDIR)\${DISK}" PATH="$(CURDIR)\${DISK}\bin:$(PATH)" CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" SAFE_OPTION=1 -C $(DISK)\examples --file=Makefile all
	pushd ..\build\dist & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-saf.txt" & popd
	$(MAKE) ADMB_HOME="$(CURDIR)\${DISK}" PATH="$(CURDIR)\${DISK}\bin:$(PATH)" CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" -C $(DISK)\examples --file=Makefile all
	pushd ..\build\dist & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-saf.txt" & popd
  endif
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
	cp -Rf ../build/dist $(INSTALL_DIR)admb
	ln -sf $(INSTALL_DIR)admb/bin/admb $(INSTALL_DIR)bin/admb

install2:
	@echo "Read INSTALL.txt for installation instructions."

clean:
ifneq ($(SHELL),sh.exe)
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
else
	if exist build rd /S /Q ..\build
	if exist ..\admb.bat del ..\admb.bat
endif
