ifeq ($(OS),Windows_NT)
  ifneq (,$(findstring sh.exe,$(SHELL)))
    ifeq ($(SHELL),sh.exe)
      PWD=$(shell cd)
      ifdef MINGW_HOME
        PATH:=$(MINGW_HOME)\bin;$(PATH)
      else
        PATH:=$(PWD)\..\utilities\mingw\bin;$(PATH)
      endif
      PATH:=$(PATH);$(PWD)\..\utilities
    else
      PWD=$(shell cmd /C cd)
      ifdef MINGW_HOME
        PATH:=$(MINGW_HOME)\bin;$(PATH)
      else
        PATH:=$(PWD)\..\utilities\mingw\bin;$(PATH)
      endif
      PATH:=$(PATH);$(PWD)\..\utilities
    endif
  else
    PWD=$(shell pwd)
    ifdef MINGW_HOME
      MINGW_DIR=$(shell cd $(MINGW_HOME) && pwd)
      PATH:=$(MINGW_DIR)/bin:$(PATH)
    else
      PATH:=$(PWD)/../utilities/mingw/bin:$(PATH)
    endif
    PATH:=$(PATH):$(PWD)/../utilities
  endif
endif

ifeq ($(SHELL),sh.exe)
  DIST=..\build\dist
  LIBSDIR=$(DIST)\lib
  LIBSDIR:=$(addsuffix \,$(LIBSDIR))
  OBJSDIR=..\build\objects\dist
  OBJSDIR:=$(addsuffix \,$(OBJSDIR))
else
  INSTALL_DIR=/usr/local/
  DIST=../build/dist
  LIBSDIR=$(DIST)/lib/
  OBJSDIR=../build/objects/dist/
endif

ifdef CXX
  USER_CXX:= $(CXX)
endif

ifdef CXXFLAGS
  USER_CXXFLAGS:= $(CXXFLAGS)
  CXXFLAGS:= $(CXXFLAGS)
endif

ifdef LDFLAGS
  USER_LDFLAGS:= $(LDFLAGS)
endif

ifdef DEBUG
  CXXFLAGS:= -g $(CXXFLAGS)
else
  ifeq ($(CXX),openCC)
    CXXFLAGS:= -O2 $(CXXFLAGS)
  else
    CXXFLAGS:= -O3 $(CXXFLAGS)
  endif
endif

ifdef BUILD_SHARED_LIBRARY
  CXXFLAGS:= -fPIC $(CXXFLAGS)
endif

ifneq ($(CXX),CC)
CXXFLAGS:= -Wall $(CXXFLAGS)
endif

CXXFLAGS:= $(CXXFLAGS) -DSAFE_ALL -D__GNUDOS__ -Dlinux -D__SPDLL__ -DUSE_LAPLACE

ifeq ($(SHELL),sh.exe)
CXXFLAGS:= $(CXXFLAGS) -I..\build\dist\include
else
CXXFLAGS:= $(CXXFLAGS) -I../build/dist/include
endif

CXXFLAGS_OPT_LIB:=$(subst -DSAFE_ALL,-DOPT_LIB,$(CXXFLAGS))

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
OBJECTS:=$(OBJECTS) $(addprefix optlp-tools99-,$(OBJ7)) $(addprefix saflp-tools99-,$(OBJ7))

OBJECTS:=$(sort $(addprefix $(OBJSDIR),$(OBJECTS)))

all: revision dist contrib
	@echo ADMB build completed.
	@echo Check README.txt for usage and installation information.

shared: includes objects
	$(CXX) -shared -o${DIST}/lib/libadmb.so ../build/objects/dist/saflp-*.obj
	$(CXX) -shared -o${DIST}/lib/libadmbo.so ../build/objects/dist/optlp-*.obj
	@echo ADMB shared build completed.
	@echo Check README.txt for usage and installation information.

revision:
ifeq ($(SHELL),sh.exe)
	-svnversion .. > ..\REVISION
else
	-svnversion .. > ../REVISION
endif

contrib:
ifeq ($(SHELL),sh.exe)
	if not exist ${DIST}\contrib md ${DIST}\contrib
	if not exist ${DIST}\contrib\lib md ${DIST}\contrib\lib
	if not exist ${DIST}\contrib\bin md ${DIST}\contrib\bin
	if not exist ${DIST}\contrib\include md ${DIST}\contrib\include
	$(MAKE) DIST=${DIST} --directory=..\contrib
else
	mkdir -p ${DIST}/contrib/lib
	mkdir -p ${DIST}/contrib/bin
	mkdir -p ${DIST}/contrib/include
	$(MAKE) DIST=${DIST} --directory=../contrib
endif

dist: libs bins docs
ifeq ($(SHELL),sh.exe)
	if not exist ${DIST}\contrib md ${DIST}\contrib
	xcopy ..\contrib $(DIST)\contrib /S /Y /D
	if not exist ${DIST}\docs md ${DIST}\docs
	xcopy ..\docs $(DIST)\docs /S /Y /D
	if not exist ${DIST}\examples md ${DIST}\examples
	xcopy ..\examples $(DIST)\examples /S /Y /D
	if not exist ${DIST}\src md ${DIST}\src
	xcopy ..\src $(DIST)\src /S /Y /D
	if not exist ${DIST}\scripts md ${DIST}\scripts
	xcopy ..\scripts $(DIST)\scripts /S /Y /D
	if not exist ${DIST}\tests md ${DIST}\tests
	xcopy ..\tests $(DIST)\tests /S /Y /D
	if not exist ${DIST}\utilities md ${DIST}\utilities
	xcopy ..\utilities $(DIST)\utilities /S /Y /D
	copy /Y ..\LICENSE.txt ${DIST}
	copy /Y ..\README.txt ${DIST}
	copy /Y ..\CHANGES.txt ${DIST}
	copy /Y ..\VERSION ${DIST}
	copy /Y ..\Makefile ${DIST}
else
	cp -R ../contrib ${DIST}
	cp -R ../docs ${DIST} 
	cp -R ../examples ${DIST}
	cp -R ../src ${DIST}
	cp -R ../scripts ${DIST}
	cp -R ../tests ${DIST}
	cp -vR ../utilities ${DIST}
	cp -f ../LICENSE.txt ${DIST}
	cp -f ../README.txt ${DIST}
	cp -f ../CHANGES.txt ${DIST}
	cp -f ../VERSION ${DIST}
	cp -f ../Makefile ${DIST}
endif

libs: includes objects_dir objects
ifeq ($(SHELL),sh.exe)
	if not exist ${DIST}\lib md ${DIST}\lib
	if exist ${DIST}\lib\libadmb.a del ${DIST}\lib\libadmb.a
	if exist ${DIST}\lib\libadmbo.a del ${DIST}\lib\libadmbo.a
else
	mkdir -p ${DIST}/lib
	rm -vf ${DIST}/lib/libadmb.a
	rm -vf ${DIST}/lib/libadmbo.a
endif
	$(AR) -rs $(LIBSDIR)libadmb.a $(OBJSDIR)saflp-linad99-*.obj
	$(AR) -rs $(LIBSDIR)libadmb.a $(OBJSDIR)saflp-df1b2-separable-*.obj
	$(AR) -rs $(LIBSDIR)libadmb.a $(OBJSDIR)saflp-nh99-*.obj
	$(AR) -rs $(LIBSDIR)libadmb.a $(OBJSDIR)saflp-tools99-*.obj
	$(AR) -rs $(LIBSDIR)libadmb.a $(OBJSDIR)saflp-sparse-*.obj
	$(AR) -rs $(LIBSDIR)libadmbo.a $(OBJSDIR)optlp-linad99-*.obj
	$(AR) -rs $(LIBSDIR)libadmbo.a $(OBJSDIR)optlp-df1b2-separable-*.obj
	$(AR) -rs $(LIBSDIR)libadmbo.a $(OBJSDIR)optlp-nh99-*.obj
	$(AR) -rs $(LIBSDIR)libadmbo.a $(OBJSDIR)optlp-tools99-*.obj
	$(AR) -rs $(LIBSDIR)libadmbo.a $(OBJSDIR)optlp-sparse-*.obj

bins:
ifeq ($(SHELL),sh.exe)
	if not exist ${DIST}\bin md ${DIST}\bin
	copy df1b2-separable\seddf1b* ${DIST}\bin
	copy df1b2-separable\sedf1b2* ${DIST}\bin
	echo set ADMB_CFG_CXX=$(USER_CXX)>${DIST}\bin\admb-cfg.bat
	echo set ADMB_CFG_CXXFLAGS=$(USER_CXXFLAGS)>>${DIST}\bin\admb-cfg.bat
	echo set ADMB_CFG_LDFLAGS=$(USER_LDFLAGS)>>${DIST}\bin\admb-cfg.bat
	echo set MINGW_HOME=$(MINGW_HOME)>>${DIST}\bin\admb-cfg.bat
	copy ..\utilities\sed.exe ${DIST}\bin
	copy ..\utilities\libiconv2.dll ${DIST}\bin
	copy ..\utilities\libintl3.dll ${DIST}\bin
	copy ..\utilities\regex2.dll ${DIST}\bin
	copy ..\scripts\admb\admb.bat ${DIST}\bin\admb.cmd
	copy ..\scripts\admb\root-admb.bat ..\admb.cmd
	copy ..\scripts\admb\root-admb.bat ${DIST}\admb.cmd
	copy ..\scripts\admb\adlink.bat ${DIST}\bin\adlink.cmd
	copy ..\scripts\admb\adcomp.bat ${DIST}\bin\adcomp.cmd
	$(MAKE) --directory=df1b2-separable CC=$(CC) DIST=..\${DIST} bins
	$(MAKE) --directory=nh99 CC=$(CC) DIST=..\${DIST} bins
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
	echo "MINGW_HOME=\"$(MINGW_HOME)\"">>${DIST}/bin/admb-cfg.sh
	cp ../utilities/sed.exe ${DIST}/bin
	cp ../utilities/libiconv2.dll ${DIST}/bin
	cp ../utilities/libintl3.dll ${DIST}/bin
	cp ../utilities/regex2.dll ${DIST}/bin
	cp ../scripts/admb/admb ${DIST}/bin/admb.sh
	cp ../scripts/admb/root-admb ../admb.sh
	cp ../scripts/admb/root-admb ${DIST}/admb.sh
	cp ../scripts/admb/adcomp ${DIST}/bin/adcomp.sh
	cp ../scripts/admb/adlink ${DIST}/bin/adlink.sh
	cp ../scripts/admb/admb.bat ${DIST}/bin/admb.cmd
	cp ../scripts/admb/root-admb.bat ../admb.cmd
	cp ../scripts/admb/root-admb.bat ${DIST}/admb.cmd
	cp ../scripts/admb/adcomp.bat ${DIST}/bin/adcomp.cmd
	cp ../scripts/admb/adlink.bat ${DIST}/bin/adlink.cmd
  else
	echo "ADMB_CFG_LDFLAGS=\"$(USER_LDFLAGS)\"">>${DIST}/bin/admb-cfg.sh
	echo "MINGW_HOME=\"$(MINGW_HOME)\"">>${DIST}/bin/admb-cfg.sh
	cp ../scripts/admb/admb ${DIST}/bin
	cp ../scripts/admb/adlink ${DIST}/bin
	cp ../scripts/admb/adcomp ${DIST}/bin
	ln -sf bin/admb ${DIST}
	ln -sf build/dist/bin/admb ..
  endif
	$(MAKE) --directory=df1b2-separable CC=$(CC) DIST=../${DIST} bins
	$(MAKE) --directory=nh99 CC=$(CC) DIST=../${DIST} bins
endif

docs:

docs2:
	$(MAKE) --directory=docs

includes:
ifeq ($(SHELL),sh.exe)
	if not exist ${DIST}\include md ${DIST}\include
	copy linad99\fvar.hpp ${DIST}\include
	copy linad99\dfpool.h ${DIST}\include
	copy linad99\trunc.hpp ${DIST}\include
	copy linad99\factors.h ${DIST}\include
	copy tools99\adoption.hpp ${DIST}\include
	copy tools99\adstring.hpp ${DIST}\include
	copy tools99\cifstrem.h ${DIST}\include
	copy tools99\clist.h ${DIST}\include
	copy tools99\admb_messages.h ${DIST}\include
	copy df1b2-separable\adpool.h ${DIST}\include
	copy df1b2-separable\adrndeff.h ${DIST}\include
	copy df1b2-separable\df1b2fun.h ${DIST}\include
	copy df1b2-separable\df32fun.h ${DIST}\include
	copy df1b2-separable\df3fun.h ${DIST}\include
	copy df1b2-separable\df1b2fnl.h ${DIST}\include
	copy df1b2-separable\df1b2loc.h ${DIST}\include
	copy df1b2-separable\smartbuf.h ${DIST}\include
	copy nh99\admodel.h ${DIST}\include
	copy nh99\adsplus.h ${DIST}\include
	copy nh99\spcomm.h ${DIST}\include
	copy nh99\param_init_bounded_number_matrix.h ${DIST}\include
	copy nh99\gccmanip.h ${DIST}\include
else
	mkdir -p ${DIST}/include
	cp linad99/fvar.hpp ${DIST}/include
	cp linad99/dfpool.h ${DIST}/include
	cp linad99/trunc.hpp ${DIST}/include
	cp linad99/factors.h ${DIST}/include
	cp tools99/adoption.hpp ${DIST}/include
	cp tools99/adstring.hpp ${DIST}/include
	cp tools99/cifstrem.h ${DIST}/include
	cp tools99/clist.h ${DIST}/include
	cp tools99/admb_messages.h ${DIST}/include
	cp df1b2-separable/adpool.h ${DIST}/include
	cp df1b2-separable/adrndeff.h ${DIST}/include
	cp df1b2-separable/df1b2fun.h ${DIST}/include
	cp df1b2-separable/df32fun.h ${DIST}/include
	cp df1b2-separable/df3fun.h ${DIST}/include
	cp df1b2-separable/df1b2fnl.h ${DIST}/include
	cp df1b2-separable/df1b2loc.h ${DIST}/include
	cp df1b2-separable/smartbuf.h ${DIST}/include
	cp nh99/admodel.h ${DIST}/include
	cp nh99/adsplus.h ${DIST}/include
	cp nh99/spcomm.h ${DIST}/include
	cp nh99/param_init_bounded_number_matrix.h ${DIST}/include
	cp nh99/gccmanip.h ${DIST}/include
endif

objects_dir:
ifeq ($(SHELL),sh.exe)
	if not exist $(OBJSDIR) md $(OBJSDIR)
else
	mkdir -p $(OBJSDIR)
endif

objects: $(OBJECTS)

ifeq ($(SHELL),sh.exe)
$(OBJSDIR)optlp-nh99-banner.obj: nh99\banner.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -DADMB_VERSION=$(shell if exist ..\VERSION type ..\VERSION) -o$@ $<

$(OBJSDIR)saflp-nh99-banner.obj: nh99\banner.cpp
	$(CXX) -c $(CXXFLAGS) -DADMB_VERSION=$(shell if exist ..\VERSION type ..\VERSION) -o$@ $<

$(OBJSDIR)optlp-sparse-hs_sparse.obj: sparse\hs_sparse.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o$@ $<

$(OBJSDIR)saflp-sparse-hs_sparse.obj: sparse\hs_sparse.cpp
	$(CXX) -c $(CXXFLAGS) -o$@ $<

$(OBJSDIR)optlp-df1b2-separable-%.obj: df1b2-separable\%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o$@ $<

$(OBJSDIR)saflp-df1b2-separable-%.obj: df1b2-separable\%.cpp
	$(CXX) -c $(CXXFLAGS) -o$@ $<

$(OBJSDIR)optlp-linad99-%.obj:linad99\%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o$@ $<

$(OBJSDIR)saflp-linad99-%.obj:linad99\%.cpp
	$(CXX) -c $(CXXFLAGS) -o$@ $<

$(OBJSDIR)optlp-nh99-%.obj:nh99\%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o$@ $<

$(OBJSDIR)saflp-nh99-%.obj:nh99\%.cpp
	$(CXX) -c $(CXXFLAGS) -o$@ $<

$(OBJSDIR)optlp-tools99-%.obj:tools99\%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o$@ $<

$(OBJSDIR)saflp-tools99-%.obj:tools99\%.cpp
	$(CXX) -c $(CXXFLAGS) -o$@ $<
else
$(OBJSDIR)optlp-nh99-banner.obj: nh99/banner.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -DADMB_VERSION=$(shell cat ../VERSION) -DADMB_REVISION=$(shell test -f ../REVISION && cat ../REVISION) -o$@ $<

$(OBJSDIR)saflp-nh99-banner.obj: nh99/banner.cpp
	$(CXX) -c $(CXXFLAGS) -DADMB_VERSION=$(shell cat ../VERSION) -DADMB_REVISION=$(shell test -f ../REVISION && cat ../REVISION) -o$@ $<

$(OBJSDIR)optlp-sparse-hs_sparse.obj: sparse/hs_sparse.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o$@ $<

$(OBJSDIR)saflp-sparse-hs_sparse.obj: sparse/hs_sparse.cpp
	$(CXX) -c $(CXXFLAGS) -o$@ $<

$(OBJSDIR)optlp-df1b2-separable-%.obj:df1b2-separable/%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o$@ $<

$(OBJSDIR)saflp-df1b2-separable-%.obj:df1b2-separable/%.cpp
	$(CXX) -c $(CXXFLAGS) -o$@ $<

$(OBJSDIR)optlp-linad99-%.obj:linad99/%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o$@ $<

$(OBJSDIR)saflp-linad99-%.obj:linad99/%.cpp
	$(CXX) -c $(CXXFLAGS) -o$@ $<

$(OBJSDIR)optlp-nh99-%.obj:nh99/%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o$@ $<

$(OBJSDIR)saflp-nh99-%.obj:nh99/%.cpp
	$(CXX) -c $(CXXFLAGS) -o$@ $<

$(OBJSDIR)optlp-tools99-%.obj:tools99/%.cpp
	$(CXX) -c $(CXXFLAGS_OPT_LIB) -o$@ $<

$(OBJSDIR)saflp-tools99-%.obj:tools99/%.cpp
	$(CXX) -c $(CXXFLAGS) -o$@ $<
endif

verify:
ifeq ($(SHELL),sh.exe)
	$(MAKE) FAST_OPTION=-f -C $(DIST)\examples --file=Makefile all
	pushd ..\build\dist & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-opt.txt" & popd
	$(MAKE) -C $(DIST)\examples --file=Makefile all
	pushd ..\build\dist & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-saf.txt" & popd
else
	$(MAKE) FAST_OPTION=-f -C $(DIST)/examples all
	-../scripts/get-outputs.sh ${DIST}/examples/ > "../benchmarks-opt.txt"
	$(MAKE) -C $(DIST)/examples all
	-../scripts/get-outputs.sh ${DIST}/examples/ > "../benchmarks-saf.txt"
endif

tests:
ifeq ($(SHELL),sh.exe)
	$(MAKE) --directory=..\contrib test
	$(MAKE) --directory=..\tests
else
	$(MAKE) --directory=../contrib test
	$(MAKE) --directory=../tests
endif

install:
	@#echo "Read INSTALL.txt for installation instructions."
	rm -rvf /usr/local/admb
	cp -Rf ../build/dist $(INSTALL_DIR)admb
	ln -sf $(INSTALL_DIR)admb/bin/admb $(INSTALL_DIR)bin/admb

clean:
ifeq ($(SHELL),sh.exe)
	if exist ..\build rd /S /Q ..\build
	if exist ..\admb del ..\admb
	if exist ..\admb.bat del ..\admb.bat
	if exist ..\admb.cmd del ..\admb.cmd
	if exist ..\admb.zip del ..\admb.zip
	if exist ..\REVISION del ..\REVISION
	if exist nh99\lex.yy.c del nh99\lex.yy.c
	if exist nh99\tpl2cpp.c del nh99\tpl2cpp.c
	if exist df1b2-separable\lex.yy.c del df1b2-separable\lex.yy.c
	if exist df1b2-separable\tpl2rem.c del df1b2-separable\tpl2rem.c
	$(MAKE) --directory=..\contrib clean
	$(MAKE) --directory=..\tests clean
else
	@rm -vf ../admb
	@rm -vf ../admb.bat
	@rm -vf ../admb.cmd
	@rm -vf ../admb.zip
	@rm -vf ../REVISION
	@rm -vf nh99/lex.yy.c
	@rm -vf nh99/tpl2cpp.c
	@rm -vf nh99/tpl2cpp
	@rm -vf df1b2-separable/lex.yy.c
	@rm -vf df1b2-separable/tpl2rem.c
	@rm -vf df1b2-separable/tpl2rem
	@rm -vrf ../build
	$(MAKE) --directory=../contrib clean
	$(MAKE) --directory=../tests clean
endif

check:
	echo "SHELL: $(SHELL)"
	echo "PATH: $(PATH)"
	echo "PWD: $(PWD)"
	echo "MINGW_HOME: $(MINGW_HOME)"
	echo "MINGW_DIR: $(MINGW_DIR)"
