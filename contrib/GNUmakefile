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
  ifeq ($(DEBUG),yes)
  CONTRIB_DIR=..\..\build\debug
  CONTRIB_OBJS_DIR=..\..\build\objects\debug
  else
  CONTRIB_DIR=..\..\build\dist
  CONTRIB_OBJS_DIR=..\..\build\objects\dist
  endif
  ifeq ($(CXX),g++)
    ifeq ($(findstring x86_64,$(shell g++ -dumpmachine)),x86_64)
      ifeq ($(findstring MSYS2,$(shell g++ --version)),MSYS2)
        OSNAME=-x86_64-msys
      else
        OSNAME=-mingw64
      endif
    else
      ifeq ($(findstring MSYS2,$(shell g++ --version)),MSYS2)
        OSNAME=-i686-msys
      else
        OSNAME=-mingw32
      endif
    endif
    CXXVERSION=-g++$(basename $(basename $(shell g++ -dumpversion)))
  endif
  CONTRIB_OBJS_DIR:="\"$(CONTRIB_OBJS_DIR)$(OSNAME)$(CXXVERSION)\""
  CONTRIB_OBJS_DIR:=$(addsuffix \contrib,$(CONTRIB_OBJS_DIR))
  CONTRIB_BIN=$(addsuffix \bin\\,$(CONTRIB_DIR))
  CONTRIB_INCLUDE=$(addsuffix \include,$(CONTRIB_DIR))
  CONTRIB_LIB=$(addsuffix \lib\,$(CONTRIB_DIR))
else
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
    ifeq (i686,$(findstring i686,$(shell $(CXX) -dumpmachine)))
      OSNAME=-i686-linux
    else
      OSNAME=-x86_64-linux
    endif
  endif
  ifeq ($(UNAME_S),Darwin)
    ifeq (i686,$(findstring i686,$(shell $(CXX) -dumpmachine)))
      OSNAME=-i686-macosx
    else
      OSNAME=-x86_64-macosx
    endif
  endif
  ifeq ($(findstring _NT,$(UNAME_S)),_NT)
    ifeq ($(findstring x86_64,$(shell g++ -dumpmachine)),x86_64)
      ifeq ($(findstring MSYS2,$(shell g++ --version)),MSYS2)
        OSNAME=-x86_64-msys
      else
        OSNAME=-mingw64
      endif
    else
      ifeq ($(findstring MSYS2,$(shell g++ --version)),MSYS2)
        OSNAME=-i686-msys
      else
        OSNAME=-mingw32
      endif
    endif
  endif
  ifeq ($(CXX),g++)
  CXXVERSION=-g++$(basename $(basename $(shell g++ -dumpversion)))
  endif
  ifeq ($(CXX),clang++)
  CXXVERSION=-clang++$(basename $(basename $(shell g++ -dumpversion)))
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
  ifeq ($(DEBUG),yes)
  CONTRIB_DIR=../../build/debug/
  CONTRIB_OBJS_PREFIX=build/objects/debug$(OSNAME)$(CXXVERSION)$(SHARED)/contrib
  else
  CONTRIB_DIR=../../build/dist/
  CONTRIB_OBJS_PREFIX=build/objects/dist$(OSNAME)$(CXXVERSION)$(SHARED)/contrib
  endif
  CONTRIB_OBJS_DIR=../../$(CONTRIB_OBJS_PREFIX)
  CONTRIB_BIN=$(addsuffix bin/,$(CONTRIB_DIR))
  CONTRIB_INCLUDE=$(addsuffix include/contrib/,$(CONTRIB_DIR))
  CONTRIB_LIB=$(addsuffix lib/,$(CONTRIB_DIR))
endif
ifeq ($(DEBUG),yes)
  OPTION=-g
endif
ifdef SHARED
  OPTION:="-d $(OPTION)"
endif

all: 
	$(MAKE) contrib-includes
	$(MAKE) contrib-libs
	$(MAKE) contrib-ad2csv

shared: libs
ifeq ($(DEBUG),yes)
  ifeq ($(SHELL),cmd)
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\debug\lib\admb-contrib$(OSNAME)$(CXXVERSION).dll -Wl,--whole-archive ..\build\debug\lib\libadmb-contrib$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
    ifndef SAFE_ONLY
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\debug\lib\admb-contribo$(OSNAME)$(CXXVERSION).dll -Wl,--whole-archive ..\build\debug\lib\libadmb-contribo$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
    endif
  else
    ifeq (clang,$(findstring clang,$(shell $(CXX) --version)))
	$(CXX) -shared $(LDFLAGS) -o ../build/debug/lib/libadmb-contrib$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/debug/lib/libadmb-contrib$(OSNAME)$(CXXVERSION)-shared.a
      ifndef SAFE_ONLY
	$(CXX) -shared $(LDFLAGS) -o ../build/debug/lib/libadmb-contribo$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/debug/lib/libadmb-contribo$(OSNAME)$(CXXVERSION)-shared.a
      endif
    else
	$(CXX) -shared $(LDFLAGS) -o ../build/debug/lib/libadmb-contrib$(OSNAME)$(CXXVERSION).so -Wl,--whole-archive ../build/debug/lib/libadmb-contrib$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
      ifndef SAFE_ONLY
	$(CXX) -shared $(LDFLAGS) -o ../build/debug/lib/libadmb-contribo$(OSNAME)$(CXXVERSION).so -Wl,--whole-archive ../build/debug/lib/libadmb-contribo$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
      endif
    endif
  endif
else
  ifeq ($(SHELL),cmd)
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\dist\lib\admb-contrib$(OSNAME)$(CXXVERSION).dll -Wl,--whole-archive ..\build\dist\lib\libadmb-contrib$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
    ifndef SAFE_ONLY
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\dist\lib\admb-contribo$(OSNAME)$(CXXVERSION).dll -Wl,--whole-archive ..\build\dist\lib\libadmb-contribo$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
    endif
  else
    ifeq (clang,$(findstring clang,$(shell $(CXX) --version)))
	$(CXX) -shared $(LDFLAGS) -o ../build/dist/lib/libadmb-contrib$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/dist/lib/libadmb-contrib$(OSNAME)$(CXXVERSION)-shared.a
      ifndef SAFE_ONLY
	$(CXX) -shared $(LDFLAGS) -o ../build/dist/lib/libadmb-contribo$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/dist/lib/libadmb-contribo$(OSNAME)$(CXXVERSION)-shared.a
      endif
    else
	$(CXX) -shared $(LDFLAGS) -o ../build/dist/lib/libadmb-contrib$(OSNAME)$(CXXVERSION).so -Wl,--whole-archive ../build/dist/lib/libadmb-contrib$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
      ifndef SAFE_ONLY
	$(CXX) -shared $(LDFLAGS) -o ../build/dist/lib/libadmb-contribo$(OSNAME)$(CXXVERSION).so -Wl,--whole-archive ../build/dist/lib/libadmb-contribo$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
      endif
    endif
  endif
endif

contrib-includes: contrib-dirs
	@$(MAKE) --directory=ecolib CONTRIB_INCLUDE=$(CONTRIB_INCLUDE) includes
	@$(MAKE) --directory=gdbprintlib CONTRIB_INCLUDE=$(CONTRIB_INCLUDE) includes
	@$(MAKE) --directory=qfclib CONTRIB_INCLUDE=$(CONTRIB_INCLUDE) includes
	@$(MAKE) --directory=statslib CONTRIB_INCLUDE=$(CONTRIB_INCLUDE) includes
	@$(MAKE) --directory=src CONTRIB_INCLUDE=$(CONTRIB_INCLUDE) includes

libs: 
	$(MAKE) contrib-dirs
	$(MAKE) contrib-libs

contrib-libs: contrib-ecolib contrib-gdbprintlib contrib-qfclib contrib-statslib contrib-src
ifeq ($(SHELL),cmd)
  ifeq ($(DEBUG),yes)
	if exist  src\$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a del src\$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a
	copy src\$(CONTRIB_LIB)libadmb$(OSNAME)$(CXXVERSION)$(SHARED).a src\$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a
	$(AR) -rs src\$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a ..\build\objects\debug$(OSNAME)$(CXXVERSION)\contrib-saflp-*.obj
    ifndef SAFE_ONLY
	if exist  src\$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a del src\$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a
	copy src\$(CONTRIB_LIB)libadmbo$(OSNAME)$(CXXVERSION)$(SHARED).a src\$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a
	$(AR) -rs src\$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a ..\build\objects\debug$(OSNAME)$(CXXVERSION)\contrib-optlp-*.obj
    endif
  else
	if exist "src\$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a" del "src\$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a"
	copy "src\$(CONTRIB_LIB)libadmb$(OSNAME)$(CXXVERSION)$(SHARED).a" "src\$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a"
	$(AR) -rs "src\$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a" "..\build\objects\dist$(OSNAME)$(CXXVERSION)\contrib-saflp-*.obj"
    ifndef SAFE_ONLY
	if exist  "src\$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a" del "src\$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a"
	copy "src\$(CONTRIB_LIB)libadmbo$(OSNAME)$(CXXVERSION)$(SHARED).a" "src\$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a"
	$(AR) -rs "src\$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a" "..\build\objects\dist$(OSNAME)$(CXXVERSION)\contrib-optlp-*.obj"
    endif
  endif
else
  ifdef SHARED
	rm -vf src/$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a
	cp -vf src/$(CONTRIB_LIB)libadmb$(OSNAME)$(CXXVERSION)$(SHARED).a src/$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a
	$(AR) -rs src/$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a ../$(CONTRIB_OBJS_PREFIX)-saflp-*.obj
    ifndef SAFE_ONLY
	rm -vf src/$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a
	cp -vf src/$(CONTRIB_LIB)libadmbo$(OSNAME)$(CXXVERSION)$(SHARED).a src/$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a
	$(AR) -rs src/$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a ../$(CONTRIB_OBJS_PREFIX)-optlp-*.obj
    endif
  else
	rm -vf src/$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a
	cp -vf src/$(CONTRIB_LIB)libadmb$(OSNAME)$(CXXVERSION).a src/$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a
	$(AR) -rs src/$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a ../$(CONTRIB_OBJS_PREFIX)-saflp-*.obj
    ifndef SAFE_ONLY
	rm -vf src/$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a
	cp -vf src/$(CONTRIB_LIB)libadmbo$(OSNAME)$(CXXVERSION).a src/$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a
	$(AR) -rs src/$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a ../$(CONTRIB_OBJS_PREFIX)-optlp-*.obj
    endif
  endif
endif

contrib-ad2csv: contrib-dirs
	$(MAKE) --directory=ad2csv CXXFLAGS= LDFLAGS= OPTION=$(OPTION) CONTRIB_BIN=$(CONTRIB_BIN)

contrib-ecolib:
	$(MAKE) --directory=ecolib CXXFLAGS= LDFLAGS= OPTION=$(OPTION) CONTRIB_OBJS_DIR=$(CONTRIB_OBJS_DIR)

contrib-gdbprintlib:
	$(MAKE) --directory=gdbprintlib CXXFLAGS= LDFLAGS= OPTION=$(OPTION) CONTRIB_OBJS_DIR=$(CONTRIB_OBJS_DIR)

contrib-qfclib:
	$(MAKE) --directory=qfclib CXXFLAGS= LDFLAGS= OPTION=$(OPTION) CONTRIB_OBJS_DIR=$(CONTRIB_OBJS_DIR)

contrib-statslib:
	$(MAKE) --directory=statslib CXXFLAGS= LDFLAGS= OPTION=$(OPTION) CONTRIB_OBJS_DIR=$(CONTRIB_OBJS_DIR)

contrib-src:
	$(MAKE) --directory=src CXXFLAGS= LDFLAGS= OPTION=$(OPTION) CONTRIB_OBJS_DIR=$(CONTRIB_OBJS_DIR)

contrib-dirs:
ifeq ($(SHELL),cmd)
	if not exist src\$(CONTRIB_INCLUDE) md src\$(CONTRIB_INCLUDE)
else
	mkdir -p src/$(CONTRIB_INCLUDE)
endif

test:
	$(MAKE) --directory=src test 

contrib-admb2r:
	$(MAKE) --directory=admb2r ADMB_HOME="$(ADMB_HOME)" gcc

contrib-test-R:
	$(MAKE) --directory=ecolib test
	$(MAKE) --directory=qfclib test

copy:
ifeq ($(DEBUG),yes)
  ifeq ($(SHELL),cmd)
	if not exist ..\build\debug\contrib md ..\build\debug\contrib
	xcopy ..\contrib ..\build\debug\contrib /S /Y /D
  else
	cp -Rvf ../contrib ../build/debug/
	$(MAKE) --directory=../build/debug/contrib clean
  endif
else
  ifeq ($(SHELL),cmd)
	if not exist ..\build\dist\contrib md ..\build\dist\contrib
	xcopy ..\contrib ..\build\dist\contrib /S /Y /D
  else
	cp -Rvf ../contrib ../build/dist/
	$(MAKE) --directory=../build/dist/contrib clean
  endif
endif

clean:
	$(MAKE) --directory=ide clean
	$(MAKE) --directory=ecolib clean
	$(MAKE) --directory=gdbprintlib clean
	$(MAKE) --directory=qfclib clean
	$(MAKE) --directory=statslib clean
	$(MAKE) --directory=src clean
	$(MAKE) --directory=ad2csv clean

check:
	@echo "SHELL: $(SHELL)"
	@echo "PATH: $(PATH)"
	@echo "TERM: $(TERM)"
	@echo "MAKE: $(MAKE)"
	@echo "CXX: $(CXX)"
	@echo "OS: $(OS)"
	@echo "OSTYPE: $(OSTYPE)"
