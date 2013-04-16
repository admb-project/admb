MAKEFLAG_J=-j 1

ifeq ($(SHELL),sh.exe)
  DISK=..\build\dist
  LIBPATH=..\build\objects\dist
  CXXFLAGS_INCLUDES:=-I..\${DISK}\include
else
  DISK=../build/dist
  LIBPATH=../build/objects/dist
  CXXFLAGS_INCLUDES:=-I../${DISK}/include
endif

ifndef INSTALL_DIR
INSTALL_DIR=/usr/local/admb
endif

ifneq ($(SHELL),sh.exe)
PWD=$(shell pwd)
else
PWD=$(shell cd)
endif


ifeq ($(CXX),CC)
CXXFLAGS:=-D__GNUDOS__ -Dlinux -D__SPDLL__ -DUSE_LAPLACE $(CXXFLAGS)
else
CXXFLAGS:=-Wall -D__GNUDOS__ -Dlinux -D__SPDLL__ -DUSE_LAPLACE $(CXXFLAGS)
endif

ifdef DEBUG
CXXFLAGS:=-g $(CXXFLAGS)
else
CXXFLAGS:=-O3 $(CXXFLAGS)
endif

all: dist contrib
ifneq ($(SHELL),sh.exe)
	pushd $(DESTDIR) & cscript ..\..\scripts\create-admb-shortcut.vbs & popd
endif
	@echo ADMB build completed.
	@echo For installation, check README.txt.

dist:
ifneq ($(SHELL),sh.exe)
	rm -rf ${DISK}
	mkdir -p ${DISK}
	cp -R ../contrib ${DISK}
	cp -R ../docs ${DISK} 
	cp -R ../examples ${DISK}
	cp -R ../src ${DISK}
	cp -R ../tests ${DISK}
	cp -R ../utilities ${DISK}
	cp -f ../LICENSE.txt ${DISK}
	cp -f ../README.txt ${DISK}
	cp -f ../CHANGES.txt ${DISK}
	cp -f ../VERSION ${DISK}
	cp -f ../Makefile ${DISK}
	rm -rf `find ${DISK} -type d -name .svn`
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
	$(MAKE) ADMB_HOME="${PWD}/${DISK}" --directory=../contrib
else
	if not exist ${DISK}\contrib md ${DISK}\contrib
	if not exist ${DISK}\contrib\lib md ${DISK}\contrib\lib
	if not exist ${DISK}\contrib\bin md ${DISK}\contrib\bin
	$(MAKE) ADMB_HOME="$(CURDIR)\${DISK}" --directory=..\contrib
endif

libs: admbsaf admbopt

admbsaf:
ifneq ($(SHELL),sh.exe)
	mkdir -p ${DISK}/lib
	mkdir -p ${LIBPATH}
	$(MAKE) $(MAKEFLAG_J) --directory=df1b2-separable CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DSAFE_ALL $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=../${LIBPATH}/saflp-df1b2-separable- DISKDIR=../${DISK}
	$(MAKE) $(MAKEFLAG_J) --directory=linad99 CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DSAFE_ALL $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=../${LIBPATH}/saflp-linad99- DISKDIR=../${DISK}
	$(MAKE) $(MAKEFLAG_J) --directory=nh99 CC=$(CC) CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=../${LIBPATH}/optlp-nh99- ADMB_CONFIGURE=${ADMB_CONFIGURE} DISKDIR=../${DISK}
	$(MAKE) $(MAKEFLAG_J) --directory=tools99 CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=../${LIBPATH}/optlp-tools99- DISKDIR=../${DISK}
	rm -vf ${DISK}/lib/libadmb.a
	$(AR) -rs ${DISK}/lib/libadmb.a ../build/objects/dist/saflp-linad99-*.obj
	$(AR) -rs ${DISK}/lib/libadmb.a ../build/objects/dist/saflp-df1b2-separable-*.obj
	$(AR) -rs ${DISK}/lib/libadmb.a ../build/objects/dist/optlp-nh99-*.obj
	$(AR) -rs ${DISK}/lib/libadmb.a ../build/objects/dist/optlp-tools99-*.obj
else
	if not exist ${DISK}\lib md ${DISK}\lib
	if not exist ..\build\objects md ..\build\objects
	if not exist ..\build\objects\dist md ..\build\objects\dist
	$(MAKE) $(MAKEFLAG_J) --directory=df1b2-separable CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DSAFE_ALL $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=..\${LIBPATH}\saflp-df1b2-separable- DISKDIR=../${DISK}
	$(MAKE) $(MAKEFLAG_J) --directory=linad99 CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DSAFE_ALL $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=..\${LIBPATH}\saflp-linad99- DISKDIR=../${DISK}
	$(MAKE) $(MAKEFLAG_J) --directory=nh99 CC=$(CC) CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=..\${LIBPATH}\optlp-nh99- ADMB_CONFIGURE=${ADMB_CONFIGURE} DISKDIR=../${DISK}
	$(MAKE) $(MAKEFLAG_J) --directory=tools99 CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=..\${LIBPATH}\optlp-tools99- DISKDIR=../${DISK}
	if exist ${DISK}\lib\libadmb.a del ${DISK}\lib\libadmb.a
	$(AR) -rs ${DISK}\lib\libadmb.a ..\build\objects\dist\saflp-linad99-*.obj
	$(AR) -rs ${DISK}\lib\libadmb.a ..\build\objects\dist\saflp-df1b2-separable-*.obj
	$(AR) -rs ${DISK}\lib\libadmb.a ..\build\objects\dist\optlp-nh99-*.obj
	$(AR) -rs ${DISK}\lib\libadmb.a ..\build\objects\dist\optlp-tools99-*.obj
endif

admbopt:
ifneq ($(SHELL),sh.exe)
	mkdir -p ${DISK}/lib
	mkdir -p ${LIBPATH}
	$(MAKE) $(MAKEFLAG_J) --directory=df1b2-separable CC=$(CC) CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=../${LIBPATH}/optlp-df1b2-separable- DISKDIR=../${DISK}
	$(MAKE) $(MAKEFLAG_J) --directory=linad99 CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=../${LIBPATH}/optlp-linad99- DISKDIR=../${DISK}
	$(MAKE) $(MAKEFLAG_J) --directory=nh99 CC=$(CC) CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=../${LIBPATH}/optlp-nh99- ADMB_CONFIGURE=${ADMB_CONFIGURE} DISKDIR=../${DISK}
	$(MAKE) $(MAKEFLAG_J) --directory=tools99 CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=../${LIBPATH}/optlp-tools99- DISKDIR=../${DISK}
	rm -vf ${DISK}/lib/libadmbo.a
	$(AR) -rs ${DISK}/lib/libadmbo.a ../build/objects/dist/optlp-linad99-*.obj
	$(AR) -rs ${DISK}/lib/libadmbo.a ../build/objects/dist/optlp-df1b2-separable-*.obj
	$(AR) -rs ${DISK}/lib/libadmbo.a ../build/objects/dist/optlp-nh99-*.obj
	$(AR) -rs ${DISK}/lib/libadmbo.a ../build/objects/dist/optlp-tools99-*.obj
else
	if not exist ${DISK}\lib md ${DISK}\lib
	if not exist ..\build\objects md ..\build\objects
	if not exist ..\build\objects\dist md ..\build\objects\dist
	$(MAKE) $(MAKEFLAG_J) --directory=df1b2-separable CC=$(CC) CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=..\${LIBPATH}\optlp-df1b2-separable- DISKDIR=..\${DISK}
	$(MAKE) $(MAKEFLAG_J) --directory=linad99 CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=..\${LIBPATH}\optlp-linad99- DISKDIR=..\${DISK}
	$(MAKE) $(MAKEFLAG_J) --directory=nh99 CC=$(CC) CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=..\${LIBPATH}\optlp-nh99- ADMB_CONFIGURE=${ADMB_CONFIGURE} DISKDIR=..\${DISK}
	$(MAKE) $(MAKEFLAG_J) --directory=tools99 CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=..\${LIBPATH}\optlp-tools99- DISKDIR=..\${DISK}
	if exist ${DISK}\lib\libadmbo.a del ${DISK}\lib\libadmbo.a
	$(AR) -rs ${DISK}\lib\libadmbo.a ..\build\objects\dist\optlp-linad99-*.obj
	$(AR) -rs ${DISK}\lib\libadmbo.a ..\build\objects\dist\optlp-df1b2-separable-*.obj
	$(AR) -rs ${DISK}\lib\libadmbo.a ..\build\objects\dist\optlp-nh99-*.obj
	$(AR) -rs ${DISK}\lib\libadmbo.a ..\build\objects\dist\optlp-tools99-*.obj
endif

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
	cp ../scripts/admb/adlink ${DISK}/bin
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
	cp ../scripts/admb/root-admb.bat ..
  endif
else
	md ${DISK}\bin
	copy df1b2-separable\seddf1b* ${DISK}\bin
	copy df1b2-separable\sedf1b2* ${DISK}\bin
	del ${DISK}\bin\admb-cfg.sh
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
	copy ..\scripts\admb\root-admb.bat ..
endif


verify:
ifndef USE_ADMB_HOME
  ifneq ($(SHELL),sh.exe)
	ADMB_HOME="${PWD}/${DISK}" PATH="${PWD}/${DISK}/bin:$(PATH)" CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" SAFE_OPTION=1 $(MAKE) -C $(DISK)/examples all
	-../scripts/get-outputs.sh ${DISK}/examples/ > "../benchmarks-saf.txt"
	ADMB_HOME="${PWD}/${DISK}" PATH="${PWD}/${DISK}/bin:$(PATH)" CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" $(MAKE) -C $(DISK)/examples all
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
	@echo "Read INSTALL.txt for installation instructions."

clean:
ifneq ($(SHELL),sh.exe)
	@rm -f nh99/lex.yy.c
	@rm -f df1b2-separable/lex.yy.c
	@rm -f nh99/tpl2cpp
	@rm -f df1b2-separable/tpl2rem
	@rm -rvf $(DISK)
	@rm -rvf $(LIBPATH)
	@rm -vf nh99/tpl2cpp.c
	@rm -vf df1b2-separable/tpl2rem.c
	@$(MAKE) --directory=../contrib clean
	@$(MAKE) --directory=../tests clean
else
	if exist build rd /S /Q ..\build
endif
