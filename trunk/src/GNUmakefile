MAKEFLAG_J=-j 1
ifndef DISK
DISK=../build/dist
endif

ifndef INSTALL_DIR
INSTALL_DIR=/usr/local/admb
endif

PWD=$(shell pwd)

ifndef LIBPATH
LIBPATH=../build/objects/dist
endif

CXXFLAGS_INCLUDES:=-I../${DISK}/include
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
	@printf "\nADMB build completed.\n"
	@printf "For installation, check README.txt.\n"

dist:
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
	cp -f ../NEWS.txt ${DISK}
	cp -f ../VERSION ${DISK}
	cp -f ../Makefile ${DISK}
	rm -rf `find ${DISK} -type d -name .svn`

contrib: includes bins libs
	mkdir -p ${DISK}/contrib/lib
	mkdir -p ${DISK}/contrib/bin
	$(MAKE) ADMB_HOME="${PWD}/${DISK}" --directory=../contrib

libs: admbsaf admbopt

admbsaf:
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

admbopt:
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

includes:
	mkdir -p ${DISK}/include
	cp linad99/fvar.hpp ${DISK}/include
	cp linad99/dfpool.h ${DISK}/include
	cp linad99/trunc.hpp ${DISK}/include
	cp linad99/factors.h ${DISK}/include
	#cp linad99/vector_shape.h ${DISK}/include
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
	cp ../scripts/admb/adcomp ${DISK}/bin
	cp ../scripts/admb/adlink ${DISK}/bin
	rm -f ${DISK}/bin/admb-cfg.sh
	echo "CXX=$(CXX)" > ${DISK}/bin/admb-cfg.sh
	$(MAKE) --directory=df1b2-separable CC=$(CC) DISKDIR=../${DISK} bins
	$(MAKE) --directory=nh99 CC=$(CC) DISKDIR=../${DISK} bins
	ln -sf bin/admb ${DISK}
	ln -sf build/dist/bin/admb ..
ifdef COMSPEC
	cp ../scripts/admb/admb.bat ${DISK}/bin
	cp ../scripts/mingw/set-admb-mingw.bat ${DISK}/bin
	cp ../utilities/sed.exe ${DISK}/bin
	cp ../scripts/admb/adcomp.bat ${DISK}/bin
	cp ../scripts/admb/adlink.bat ${DISK}/bin
endif

verify:
	ADMB_HOME="${PWD}/${DISK}" PATH="${PWD}/${DISK}/bin:$(PATH)" CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" SAFE_OPTION=1 $(MAKE) -C $(DISK)/examples all
	-../scripts/get-outputs.sh ${DISK}/examples/ > "../benchmarks-saf.txt"
	ADMB_HOME="${PWD}/${DISK}" PATH="${PWD}/${DISK}/bin:$(PATH)" CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" $(MAKE) -C $(DISK)/examples all
	-../scripts/get-outputs.sh ${DISK}/examples/ > "../benchmarks-opt.txt"

verify_admb_home:
ifdef ADMB_HOME
	ADMB_HOME="${ADMB_HOME}" PATH="${ADMB_HOME}/bin:$(PATH)" CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" SAFE_OPTION=1 $(MAKE) -C $(DISK)/examples all
	-../scripts/get-outputs.sh ${DISK}/examples/ > "../benchmarks-saf.txt"
	ADMB_HOME="${ADMB_HOME}" PATH="${ADMB_HOME}/bin:$(PATH)" CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" $(MAKE) -C $(DISK)/examples all
	-../scripts/get-outputs.sh ${DISK}/examples/ > "../benchmarks-opt.txt"
endif

tests:
	$(MAKE) ADMB_HOME="${PWD}/${DISK}" --directory=../contrib test
	$(MAKE) ADMB_HOME="${PWD}/${DISK}" --directory=../tests

tests_admb_home:
ifdef ADMB_HOME
	$(MAKE) ADMB_HOME="${ADMB_HOME}" --directory=../contrib test
	$(MAKE) ADMB_HOME="${ADMB_HOME}" --directory=../tests
endif

install:
ifneq ($(SHELL),sh.exe)
	cp -Rvf $(DISK) $(INSTALL_DIR)
endif

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
