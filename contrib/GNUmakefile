ifndef ADMB_VER
  ADMB_VER=admb
endif
ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifndef TERM
      export SHELL=cmd
      CMDSHELL=cmd
    endif
  endif
  ifeq ($(CMDSHELL),cmd)
    ifeq ($(wildcard ..\utilities\mingw\bin\g++.exe),..\utilities\mingw\bin\g++.exe)
      PATH:=$(abspath ..\utilities\mingw\bin);$(PATH)
    endif
  else
    ifeq ($(wildcard ../utilities/mingw/bin/g++.exe),../utilities/mingw/bin/g++.exe)
      PATH:=$(abspath ../utilities/mingw/bin):$(PATH)
    endif
  endif
endif
ifeq ($(CMDSHELL),cmd)
  CONTRIB_DIR=..\..\build\$(ADMB_VER)
  CONTRIB_OBJS_DIR=..\..\build\objects
  ifeq ($(CXX),g++)
    ifeq ($(findstring g++.exe,$(shell where g++.exe 2>&1 | findstr g++.exe)),g++.exe)
      ifeq ($(findstring x86_64,$(shell g++ -dumpmachine)),x86_64)
        OSNAME=-mingw64
      else
        OSNAME=-mingw32
      endif
      CXXVERSION=-g++$(basename $(basename $(shell g++ -dumpversion)))
    endif
  endif
  ifeq ($(findstring clang++,$(CXX)),clang++)
    ifneq ($(findstring clang++.exe,$(shell where clang++.exe 2>&1 | findstr clang++.exe)),clang++.exe)
      $(warning "Warning: Unable to find clang++ compiler.")
    endif
    ifeq ($(findstring x86_64,$(shell $(CXX) -dumpmachine)),x86_64)
      OSNAME=-win64
    else
      OSNAME=-win32
    endif
    CXXVERSION=-clang++$(basename $(basename $(shell $(CXX) -dumpversion)))
  endif
  ifeq ($(DEBUG),yes)
    CONTRIB_OBJS_DIR:=$(CONTRIB_OBJS_DIR)$(OSNAME)$(CXXVERSION)-debug
  else
    CONTRIB_OBJS_DIR:=$(CONTRIB_OBJS_DIR)$(OSNAME)$(CXXVERSION)
  endif
  CONTRIB_BIN=$(addsuffix \bin,$(CONTRIB_DIR))
  CONTRIB_INCLUDE=$(addsuffix \include,$(CONTRIB_DIR))
  CONTRIB_LIB=$(addsuffix \lib,$(CONTRIB_DIR))
else
  ifeq ($(OS),Windows_NT)
    UNAME_S=_NT
  else
    UNAME_S := $(shell uname -s)
  endif
  ifeq ($(UNAME_S),Linux)
    ifeq (i686,$(findstring i686,$(shell $(CXX) -dumpmachine)))
      OSNAME=-i686-linux
    else
      ifeq (x86_64,$(findstring x86_64,$(shell $(CXX) -dumpmachine)))
        OSNAME=-x86_64-linux
      else
        OSNAME=-arm64-linux
      endif
    endif
  endif
  ifeq ($(UNAME_S),Darwin)
    ifeq (i686,$(findstring i686,$(shell $(CXX) -dumpmachine)))
      OSNAME=-i686-macos
    else
      ifeq (x86_64,$(findstring x86_64,$(shell $(CXX) -dumpmachine)))
        OSNAME=-x86_64-macos
      else
        OSNAME=-arm64-macos
      endif
    endif
  endif
  ifeq ($(findstring _NT,$(UNAME_S)),_NT)
    ifeq ($(CXX),g++)
      ifeq ($(findstring g++.exe,$(shell where g++.exe 2>&1 | findstr g++.exe)),g++.exe)
        ifeq ($(findstring x86_64,$(shell g++ -dumpmachine)),x86_64)
          OSNAME=-mingw64
        else
          OSNAME=-mingw32
        endif
      endif
    endif
    ifeq ($(findstring clang++,$(CXX)),clang++)
      ifeq ($(findstring x86_64,$(shell clang++ -dumpmachine)),x86_64)
        OSNAME=-win64
      else
        OSNAME=-win32
      endif
    endif
  endif
  ifeq ($(findstring g++,$(CXX)),g++)
    ifeq ($(UNAME_S),Darwin)
      ifeq ($(findstring Homebrew,$(shell $(CXX) --version)),Homebrew)
        CXXVERSION=-g++$(basename $(basename $(shell $(CXX) -dumpversion)))
      else
        ifeq (clang-10,$(findstring clang-10,$(shell $(CXX) --version)))
          CXXVERSION=-clang10
        else ifeq (clang-11,$(findstring clang-11,$(shell $(CXX) --version)))
          CXXVERSION=-clang11
        else
          CXXVERSION=-clang
        endif
      endif
    else
      CXXVERSION=-g++$(basename $(basename $(shell $(CXX) -dumpversion)))
    endif
  endif
  ifeq ($(findstring clang++,$(CXX)),clang++)
    CXXVERSION=-clang++$(basename $(basename $(shell $(CXX) -dumpversion)))
  endif
  ifeq ($(CXX),c++)
    ifeq ($(UNAME_S),Darwin)
      ifeq (clang-10,$(findstring clang-10,$(shell $(CXX) --version)))
        CXXVERSION=-clang10
      else ifeq (clang-11,$(findstring clang-11,$(shell $(CXX) --version)))
        CXXVERSION=-clang11
      else
        CXXVERSION=-clang
      endif
    else
      CXXVERSION=-c++$(basename $(basename $(shell $(CXX) -dumpversion)))
    endif
  endif
  ifeq ($(CXX),analyze-c++)
  CXXVERSION=-analyze-c++$(basename $(basename $(shell $(CXX) -dumpversion)))
  endif
  ifeq ($(CXX),icpc)
  CXXVERSION=-icpc$(basename $(basename $(basename $(shell $(CXX) -dumpversion))))
  endif
  CONTRIB_DIR=../../build/$(ADMB_VER)/
  ifeq ($(DEBUG),yes)
  CONTRIB_OBJS_PREFIX=build/objects$(OSNAME)$(CXXVERSION)$(SHARED)-debug
  else
  CONTRIB_OBJS_PREFIX=build/objects$(OSNAME)$(CXXVERSION)$(SHARED)
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
  ifeq ($(CMDSHELL),cmd)
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\$(ADMB_VER)\lib\admb-contrib$(OSNAME)$(CXXVERSION).dll -Wl,--whole-archive ..\build\$(ADMB_VER)\lib\libadmb-contrib$(OSNAME)$(CXXVERSION)-shared-debug.a -Wl,--no-whole-archive
    ifndef SAFE_ONLY
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\$(ADMB_VER)\lib\admb-contribo$(OSNAME)$(CXXVERSION).dll -Wl,--whole-archive ..\build\$(ADMB_VER)\lib\libadmb-contribo$(OSNAME)$(CXXVERSION)-shared-debug.a -Wl,--no-whole-archive
    endif
  else
    ifeq (clang,$(findstring clang,$(shell $(CXX) --version)))
	$(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmb-contrib$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/$(ADMB_VER)/lib/libadmb-contrib$(OSNAME)$(CXXVERSION)-shared-debug.a
      ifndef SAFE_ONLY
	$(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmb-contribo$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/$(ADMB_VER)/lib/libadmb-contribo$(OSNAME)$(CXXVERSION)-shared-debug.a
      endif
    else
      ifeq ($(findstring Homebrew,$(shell $(CXX) --version)),Homebrew)
	$(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmb-contrib$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/$(ADMB_VER)/lib/libadmb-contrib$(OSNAME)$(CXXVERSION)-shared-debug.a
      else
	$(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmb-contrib$(OSNAME)$(CXXVERSION).so -Wl,--whole-archive ../build/$(ADMB_VER)/lib/libadmb-contrib$(OSNAME)$(CXXVERSION)-shared-debug.a -Wl,--no-whole-archive
      endif
      ifndef SAFE_ONLY
        ifeq ($(findstring Homebrew,$(shell $(CXX) --version)),Homebrew)
	  $(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmb-contribo$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/$(ADMB_VER)/lib/libadmb-contribo$(OSNAME)$(CXXVERSION)-shared-debug.a
        else
	  $(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmb-contribo$(OSNAME)$(CXXVERSION).so -Wl,--whole-archive ../build/$(ADMB_VER)/lib/libadmb-contribo$(OSNAME)$(CXXVERSION)-shared-debug.a -Wl,--no-whole-archive
        endif
      endif
    endif
  endif
else
  ifeq ($(CMDSHELL),cmd)
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\$(ADMB_VER)\lib\admb-contrib$(OSNAME)$(CXXVERSION).dll -Wl,--whole-archive ..\build\$(ADMB_VER)\lib\libadmb-contrib$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
    ifndef SAFE_ONLY
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\$(ADMB_VER)\lib\admb-contribo$(OSNAME)$(CXXVERSION).dll -Wl,--whole-archive ..\build\$(ADMB_VER)\lib\libadmb-contribo$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
    endif
  else
    ifeq (clang,$(findstring clang,$(shell $(CXX) --version)))
	$(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmb-contrib$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/$(ADMB_VER)/lib/libadmb-contrib$(OSNAME)$(CXXVERSION)-shared.a
      ifndef SAFE_ONLY
	$(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmb-contribo$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/$(ADMB_VER)/lib/libadmb-contribo$(OSNAME)$(CXXVERSION)-shared.a
      endif
    else
      ifeq ($(findstring Homebrew,$(shell $(CXX) --version)),Homebrew)
	$(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmb-contrib$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/$(ADMB_VER)/lib/libadmb-contrib$(OSNAME)$(CXXVERSION)-shared.a
      else
	$(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmb-contrib$(OSNAME)$(CXXVERSION).so -Wl,--whole-archive ../build/$(ADMB_VER)/lib/libadmb-contrib$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
      endif
      ifndef SAFE_ONLY
        ifeq ($(findstring Homebrew,$(shell $(CXX) --version)),Homebrew)
	  $(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmb-contribo$(OSNAME)$(CXXVERSION).so -Wl,-force_load ../build/$(ADMB_VER)/lib/libadmb-contribo$(OSNAME)$(CXXVERSION)-shared.a
        else
	  $(CXX) -shared $(LDFLAGS) -o ../build/$(ADMB_VER)/lib/libadmb-contribo$(OSNAME)$(CXXVERSION).so -Wl,--whole-archive ../build/$(ADMB_VER)/lib/libadmb-contribo$(OSNAME)$(CXXVERSION)-shared.a -Wl,--no-whole-archive
        endif
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
ifeq ($(CMDSHELL),cmd)
  ifeq ($(DEBUG),yes)
	if exist "src\$(CONTRIB_LIB)\libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a" del "src\$(CONTRIB_LIB)\libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a"
	copy "src\$(CONTRIB_LIB)\libadmb$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a" "src\$(CONTRIB_LIB)\libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a"
	$(AR) -rs ..\build\$(ADMB_VER)\lib\libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a $(addprefix ..\build\objects$(OSNAME)$(CXXVERSION)-debug\,$(shell dir /B ..\build\objects$(OSNAME)$(CXXVERSION)-debug\saflp-contrib-*.obj))
    ifndef SAFE_ONLY
	if exist  "src\$(CONTRIB_LIB)\libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a" del "src\$(CONTRIB_LIB)\libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a"
	copy "src\$(CONTRIB_LIB)\libadmbo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a" "src\$(CONTRIB_LIB)\libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a"
	$(AR) -rs ..\build\$(ADMB_VER)\lib\libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a $(addprefix ..\build\objects$(OSNAME)$(CXXVERSION)-debug\,$(shell dir /B ..\build\objects$(OSNAME)$(CXXVERSION)-debug\optlp-contrib-*.obj))
    endif
  else
	if exist "src\$(CONTRIB_LIB)\libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a" del "src\$(CONTRIB_LIB)\libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a"
	copy "src\$(CONTRIB_LIB)\libadmb$(OSNAME)$(CXXVERSION)$(SHARED).a" "src\$(CONTRIB_LIB)\libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a"
	$(AR) -rs ..\build\$(ADMB_VER)\lib\libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a $(addprefix ..\build\objects$(OSNAME)$(CXXVERSION)\,$(shell dir /B ..\build\objects$(OSNAME)$(CXXVERSION)\saflp-contrib-*.obj))
    ifndef SAFE_ONLY
	if exist  "src\$(CONTRIB_LIB)\libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a" del "src\$(CONTRIB_LIB)\libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a"
	copy "src\$(CONTRIB_LIB)\libadmbo$(OSNAME)$(CXXVERSION)$(SHARED).a" "src\$(CONTRIB_LIB)\libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a"
	$(AR) -rs ..\build\$(ADMB_VER)\lib\libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a $(addprefix ..\build\objects$(OSNAME)$(CXXVERSION)\,$(shell dir /B ..\build\objects$(OSNAME)$(CXXVERSION)\optlp-contrib-*.obj))
    endif
  endif
else
  ifeq ($(DEBUG),yes)
    ifdef SHARED
	rm -vf src/$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a
	cp -vf src/$(CONTRIB_LIB)libadmb$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a src/$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a
	$(AR) -rs src/$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a ../$(CONTRIB_OBJS_PREFIX)/saflp-contrib-*.obj
      ifndef SAFE_ONLY
	rm -vf src/$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a
	cp -vf src/$(CONTRIB_LIB)libadmbo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a src/$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a
	$(AR) -rs src/$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a ../$(CONTRIB_OBJS_PREFIX)/optlp-contrib-*.obj
      endif
    else
	rm -vf src/$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a
	cp -vf src/$(CONTRIB_LIB)libadmb$(OSNAME)$(CXXVERSION)-debug.a src/$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a
	$(AR) -rs src/$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a ../$(CONTRIB_OBJS_PREFIX)/saflp-contrib-*.obj
      ifndef SAFE_ONLY
	rm -vf src/$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a
	cp -vf src/$(CONTRIB_LIB)libadmbo$(OSNAME)$(CXXVERSION)-debug.a src/$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a
	$(AR) -rs src/$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED)-debug.a ../$(CONTRIB_OBJS_PREFIX)/optlp-contrib-*.obj
      endif
    endif
  else
    ifdef SHARED
	rm -vf src/$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a
	cp -vf src/$(CONTRIB_LIB)libadmb$(OSNAME)$(CXXVERSION)$(SHARED).a src/$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a
	$(AR) -rs src/$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a ../$(CONTRIB_OBJS_PREFIX)/saflp-contrib-*.obj
      ifndef SAFE_ONLY
	rm -vf src/$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a
	cp -vf src/$(CONTRIB_LIB)libadmbo$(OSNAME)$(CXXVERSION)$(SHARED).a src/$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a
	$(AR) -rs src/$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a ../$(CONTRIB_OBJS_PREFIX)/optlp-contrib-*.obj
      endif
    else
	rm -vf src/$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a
	cp -vf src/$(CONTRIB_LIB)libadmb$(OSNAME)$(CXXVERSION).a src/$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a
	$(AR) -rs src/$(CONTRIB_LIB)libadmb-contrib$(OSNAME)$(CXXVERSION)$(SHARED).a ../$(CONTRIB_OBJS_PREFIX)/saflp-contrib-*.obj
      ifndef SAFE_ONLY
	rm -vf src/$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a
	cp -vf src/$(CONTRIB_LIB)libadmbo$(OSNAME)$(CXXVERSION).a src/$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a
	$(AR) -rs src/$(CONTRIB_LIB)libadmb-contribo$(OSNAME)$(CXXVERSION)$(SHARED).a ../$(CONTRIB_OBJS_PREFIX)/optlp-contrib-*.obj
      endif
    endif
  endif
endif

contrib-ad2csv: contrib-dirs
ifeq ($(CMDSHELL),cmd)
	if not exist ..\build\ad2csv md ..\build\ad2csv
else
	mkdir -p ../build/ad2csv
endif
	$(MAKE) --directory=ad2csv CXXFLAGS=$(CXXFLAGS) LDFLAGS=$(LDFLAGS) OPTION=$(OPTION) CONTRIB_BIN=$(CONTRIB_BIN)

contrib-ecolib:
	$(MAKE) --directory=ecolib CXXFLAGS=$(CXXFLAGS) LDFLAGS=$(LDFLAGS) OPTION=$(OPTION) CONTRIB_OBJS_DIR=$(CONTRIB_OBJS_DIR)

contrib-gdbprintlib:
	$(MAKE) --directory=gdbprintlib CXXFLAGS=$(CXXFLAGS) LDFLAGS=$(LDFLAGS) OPTION=$(OPTION) CONTRIB_OBJS_DIR=$(CONTRIB_OBJS_DIR)

contrib-qfclib:
	$(MAKE) --directory=qfclib CXXFLAGS=$(CXXFLAGS) LDFLAGS=$(LDFLAGS) OPTION=$(OPTION) CONTRIB_OBJS_DIR=$(CONTRIB_OBJS_DIR)

contrib-statslib:
	$(MAKE) --directory=statslib CXXFLAGS=$(CXXFLAGS) LDFLAGS=$(LDFLAGS) OPTION=$(OPTION) CONTRIB_OBJS_DIR=$(CONTRIB_OBJS_DIR)

contrib-src:
	$(MAKE) --directory=src CXXFLAGS=$(CXXFLAGS) LDFLAGS=$(LDFLAGS) OPTION=$(OPTION) CONTRIB_OBJS_DIR=$(CONTRIB_OBJS_DIR)

contrib-dirs:
ifeq ($(CMDSHELL),cmd)
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
  ifeq ($(CMDSHELL),cmd)
	if not exist ..\build\$(ADMB_VER)\contrib md ..\build\$(ADMB_VER)\contrib
	xcopy ..\contrib ..\build\$(ADMB_VER)\contrib /S /Y /D
  else
	cp -Rvf ../contrib ../build/$(ADMB_VER)/
	$(MAKE) --directory=../build/$(ADMB_VER)/contrib clean
  endif
else
  ifeq ($(CMDSHELL),cmd)
	if not exist ..\build\$(ADMB_VER)\contrib md ..\build\$(ADMB_VER)\contrib
	xcopy ..\contrib ..\build\$(ADMB_VER)\contrib /S /Y /D
  else
	cp -Rvf ../contrib ../build/$(ADMB_VER)/
	$(MAKE) --directory=../build/$(ADMB_VER)/contrib clean
  endif
endif

clean:
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
