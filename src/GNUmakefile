ifndef DISK
DISK=../build/dist
endif

PWD=$(shell pwd)

ifndef LIBPATH
LIBPATH=../build/objects/dist
endif

ifndef ADMB_HOME
ADMB_HOME=${PWD}/${DISK}
endif

CXXFLAGS:=-DADMB_VERSION=$(shell cat ../VERSION) $(CXXFLAGS)

ifndef ADMB_REVISION
ADMB_REVISION=$(shell test -e ../REVISION && cat ../REVISION)
endif

ifneq ($(ADMB_REVISION),)
CXXFLAGS:=-DADMB_REVISION=$(ADMB_REVISION) $(CXXFLAGS)
ADMB_REVISION:=-r$(ADMB_REVISION)
endif

#CXXFLAGS_INCLUDES:=-I../df1b2-separable -I../nh99 -I../linad99 -I../tools99
CXXFLAGS_INCLUDES:=-I../${DISK}/include
ifeq ($(CXX),CC)
CXXFLAGS:=-D__GNUDOS__ -Dlinux -D__SPDLL__ -DUSE_LAPLACE $(CXXFLAGS)
else
CXXFLAGS:=-Wall -D__GNUDOS__ -Dlinux -D__SPDLL__ -DUSE_LAPLACE $(CXXFLAGS)
endif

ifdef DEBUG
CXXFLAGS:=-c -g $(CXXFLAGS)
else
CXXFLAGS:=-c -O3 $(CXXFLAGS)
endif

all: dist contrib
	@printf "\nADMB build completed.\n"
	@printf "For installation, check README.txt.\n"

dist: includes examples bins
	mkdir -p ${LIBPATH}
	$(MAKE) --directory=linad99 CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=../${LIBPATH}/optlp-linad99- DISKDIR=../${DISK}
	$(MAKE) --directory=linad99 CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DSAFE_ALL $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=../${LIBPATH}/saflp-linad99- DISKDIR=../${DISK}
	$(MAKE) --directory=df1b2-separable CC=$(CC) CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=../${LIBPATH}/optlp-df1b2-separable- DISKDIR=../${DISK}
	$(MAKE) --directory=df1b2-separable CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DSAFE_ALL $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=../${LIBPATH}/saflp-df1b2-separable- DISKDIR=../${DISK}
	$(MAKE) --directory=nh99 CC=$(CC) CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=../${LIBPATH}/optlp-nh99- ADMB_CONFIGURE=${ADMB_CONFIGURE} DISKDIR=../${DISK}
	$(MAKE) --directory=tools99 CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" PREFIX_OBJ=../${LIBPATH}/optlp-tools99- DISKDIR=../${DISK}

	mkdir -p ${DISK}/lib
	rm -vf ${DISK}/lib/libadmb.a
	$(AR) -rs ${DISK}/lib/libadmb.a ../build/objects/dist/saflp-linad99-*.obj
	$(AR) -rs ${DISK}/lib/libadmb.a ../build/objects/dist/saflp-df1b2-separable-*.obj
	$(AR) -rs ${DISK}/lib/libadmb.a ../build/objects/dist/optlp-nh99-*.obj
	$(AR) -rs ${DISK}/lib/libadmb.a ../build/objects/dist/optlp-tools99-*.obj

	rm -vf ${DISK}/lib/libadmbo.a
	$(AR) -rs ${DISK}/lib/libadmbo.a ../build/objects/dist/optlp-linad99-*.obj
	$(AR) -rs ${DISK}/lib/libadmbo.a ../build/objects/dist/optlp-df1b2-separable-*.obj
	$(AR) -rs ${DISK}/lib/libadmbo.a ../build/objects/dist/optlp-nh99-*.obj
	$(AR) -rs ${DISK}/lib/libadmbo.a ../build/objects/dist/optlp-tools99-*.obj

	mkdir -p ${DISK}/docs/manuals
	cp -vf ../LICENSE.txt ${DISK}
	cp -vf ../README.txt ${DISK}
	cp -vf ../NEWS.txt ${DISK}
	cp -vf ../VERSION ${DISK}
	rm -rf `find ${DISK} -type d -name .svn`
	mkdir -p ${DISK}/contrib

includes:
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

bins:
	mkdir -p ${DISK}/bin
	cp df1b2-separable/seddf1b* df1b2-separable/sedf1b2* ${DISK}/bin
	cp ../scripts/admb/admb ${DISK}/bin
	cp ../scripts/admb/admb.bat ${DISK}/bin
ifeq ($(CXX),CC)
	  cp ../scripts/CC/adcomp ${DISK}/bin
	  cp ../scripts/CC/adlink ${DISK}/bin
endif
ifeq ($(CXX),c++)
	  cp ../scripts/admb/adcomp ${DISK}/bin
	  cp ../scripts/admb/adlink ${DISK}/bin
endif
ifeq ($(CXX),g++)
	  cp ../scripts/g++/adcomp ${DISK}/bin
	  cp ../scripts/g++/adlink ${DISK}/bin
	  cp ../scripts/g++/adcomp.bat ${DISK}/bin
	  cp ../scripts/g++/adlink.bat ${DISK}/bin
endif
ifeq ($(CXX),x86_64-w64-mingw32-g++.exe)
	  cp ../scripts/g++/adcomp-x86_64-w64-mingw32 ${DISK}/bin/adcomp
	  cp ../scripts/g++/adlink-x86_64-w64-mingw32 ${DISK}/bin/adlink
endif
ifeq ($(CXX),clang++)
	  cp ../scripts/clang++/adcomp ${DISK}/bin
	  cp ../scripts/clang++/adlink ${DISK}/bin
endif
ifeq ($(CXX),icpc)
	  cp ../scripts/icpc/adcomp ${DISK}/bin
	  cp ../scripts/icpc/adlink ${DISK}/bin
endif
ifeq ($(CXX),g++.exe)
	  cp ../scripts/admb/admb.bat ${DISK}/bin
	  cp ../scripts/$(CXX)/adcomp.bat ${DISK}/bin
	  cp ../scripts/$(CXX)/adlink.bat ${DISK}/bin
	  cp ../scripts/mingw/set-admb-mingw.bat ${DISK}/bin
	  cp ../utilities/sed.exe ${DISK}/bin
endif

examples:
	rm -rf ${DISK}/examples
	cp -R ../examples ${DISK}

verify:
	ADMB_HOME="${ADMB_HOME}" PATH="${ADMB_HOME}/bin:$(PATH)" CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" SAFE_OPTION=1 $(MAKE) -C ${DISK}/examples all
	-../scripts/get-outputs.sh ${DISK}/examples/ > "../benchmarks$(ADMB_REVISION)-saf.txt"
	ADMB_HOME="${ADMB_HOME}" PATH="${ADMB_HOME}/bin:$(PATH)" CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" $(MAKE) -C ${DISK}/examples all
	-../scripts/get-outputs.sh ${DISK}/examples/ > "../benchmarks$(ADMB_REVISION)-opt.txt"

contrib:
	$(MAKE) ADMB_HOME="${ADMB_HOME}" --directory=../contrib

tests:
	$(MAKE) ADMB_HOME="${ADMB_HOME}" CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" --directory=../contrib test
	$(MAKE) ADMB_HOME="${ADMB_HOME}" CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" --directory=../tests

check-admb2r:
	export ADMB_HOME=${PWD}/${DISK}; export PATH=${PWD}/${DISK}/bin:$(PATH); $(MAKE) -C ../test/admb2r gcc

clean:
	@rm -f nh99/lex.yy.c
	@rm -f df1b2-separable/lex.yy.c
	@rm -f nh99/tpl2cpp
	@rm -f df1b2-separable/tpl2rem
	@rm -rvf $(DISK)
	@rm -rvf $(LIBPATH)
	@rm -vf nh99/tpl2cpp.c
	@rm -vf df1b2-separable/tpl2rem.c
	@make --directory=../contrib clean
	@make --directory=../tests clean
