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

	rm -rf ${DISK}/src
	cp -R ../src ${DISK}

	rm -rf ${DISK}/docs
	cp -R ../docs ${DISK} 

	rm -rf ${DISK}/tests
	cp -R ../tests ${DISK}

	rm -rf ${DISK}/utilities
	cp -R ../utilities ${DISK}

	cp -vf ../LICENSE.txt ${DISK}
	cp -vf ../README.txt ${DISK}
	cp -vf ../NEWS.txt ${DISK}
	cp -vf ../VERSION ${DISK}
	cp -vf ../Makefile ${DISK}

	rm -rf `find ${DISK} -type d -name .svn`

	rm -rf ${DISK}/contrib
	cp -R ../contrib ${DISK}
	mkdir -p ${DISK}/contrib/include
	mkdir -p ${DISK}/contrib/lib
	mkdir -p ${DISK}/contrib/bin

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
	cp ../scripts/admb/adcomp ${DISK}/bin
	cp ../scripts/admb/adlink ${DISK}/bin
	rm -f ${DISK}/bin/admb-cfg.sh
	echo "CXX=$(CXX)" > ${DISK}/bin/admb-cfg.sh
ifeq ($(CXX),g++)
	  cp ../scripts/admb/adcomp.bat ${DISK}/bin
	  cp ../scripts/admb/adlink.bat ${DISK}/bin
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
	-../scripts/get-outputs.sh ${DISK}/examples/ > "../benchmarks-saf.txt"
	ADMB_HOME="${ADMB_HOME}" PATH="${ADMB_HOME}/bin:$(PATH)" CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" $(MAKE) -C ${DISK}/examples all
	-../scripts/get-outputs.sh ${DISK}/examples/ > "../benchmarks-opt.txt"

contrib:
	$(MAKE) ADMB_HOME="${ADMB_HOME}" --directory=../contrib

tests:
	$(MAKE) ADMB_HOME="${ADMB_HOME}" CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" --directory=../contrib test
	$(MAKE) ADMB_HOME="${ADMB_HOME}" CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" --directory=../tests

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
