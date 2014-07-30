ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL = cmd
    ifeq ($(SHELL),cmd)
      MYPWD=$(shell cd)
    else
      MYPWD=$(shell cmd /C cd)
    endif
    PATH:=$(MYPWD)\..\utilities\mingw\bin;$(PATH);$(MYPWD)\..\utilities
  else
    ifneq ($(TERM),xterm)
      MYPWD=$(shell pwd)
      PATH:=$(MYPWD)/../utilities/mingw/bin:$(PATH)
    endif
    PATH:=$(PATH):$(MYPWD)/../utilities
  endif
endif
ifeq ($(SHELL),cmd)
  ifeq ($(DEBUG),yes)
  CONTRIB_DIR=..\..\build\debug\contrib
  CONTRIB_OBJS_DIR=..\..\build\objects\debug\contrib
  else
  CONTRIB_DIR=..\..\build\dist\contrib
  CONTRIB_OBJS_DIR=..\..\build\objects\dist\contrib
  endif
  CONTRIB_BIN=$(addsuffix \bin,$(CONTRIB_DIR))
  CONTRIB_INCLUDE=$(addsuffix \include,$(CONTRIB_DIR))
  CONTRIB_LIB=$(addsuffix \lib,$(CONTRIB_DIR))
else
  ifeq ($(DEBUG),yes)
  CONTRIB_DIR=../../build/debug/contrib
  CONTRIB_OBJS_DIR=../../build/objects/debug/contrib$(SHARED)
  else
  CONTRIB_DIR=../../build/dist/contrib
  CONTRIB_OBJS_DIR=../../build/objects/dist/contrib$(SHARED)
  endif
  CONTRIB_BIN=$(addsuffix /bin,$(CONTRIB_DIR))
  CONTRIB_INCLUDE=$(addsuffix /include,$(CONTRIB_DIR))
  CONTRIB_LIB=$(addsuffix /lib,$(CONTRIB_DIR))
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

shared:
ifeq ($(DEBUG),yes)
  ifeq ($(SHELL),cmd)
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\debug\lib\admb-contrib.dll -Wl,--whole-archive ..\build\debug\lib\libadmb-contrib-shared.a -Wl,--no-whole-archive
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\debug\lib\admb-contribo.dll -Wl,--whole-archive ..\build\debug\lib\libadmb-contribo-shared.a -Wl,--no-whole-archive
  else
    ifeq (LLVM,$(findstring LLVM,$(shell $(CXX) --version)))
	$(CXX) -shared $(LDFLAGS) -o ../build/debug/lib/libadmb-contrib.so -Wl,-force_load ../build/debug/lib/libadmb-contrib-shared.a
	$(CXX) -shared $(LDFLAGS) -o ../build/debug/lib/libadmb-contribo.so -Wl,-force_load ../build/debug/lib/libadmb-contribo-shared.a
    else
	$(CXX) -shared $(LDFLAGS) -o ../build/debug/lib/libadmb-contrib.so -Wl,--whole-archive ../build/debug/lib/libadmb-contrib-shared.a -Wl,--no-whole-archive
	$(CXX) -shared $(LDFLAGS) -o ../build/debug/lib/libadmb-contribo.so -Wl,--whole-archive ../build/debug/lib/libadmb-contribo-shared.a -Wl,--no-whole-archive
    endif
  endif
else
  ifeq ($(SHELL),cmd)
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\dist\lib\admb-contrib.dll -Wl,--whole-archive ..\build\dist\lib\libadmb-contrib-shared.a -Wl,--no-whole-archive
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\dist\lib\admb-contribo.dll -Wl,--whole-archive ..\build\dist\lib\libadmb-contribo-shared.a -Wl,--no-whole-archive
  else
    ifeq (LLVM,$(findstring LLVM,$(shell $(CXX) --version)))
	$(CXX) -shared $(LDFLAGS) -o ../build/dist/lib/libadmb-contrib.so -Wl,-force_load ../build/dist/lib/libadmb-contrib-shared.a
	$(CXX) -shared $(LDFLAGS) -o ../build/dist/lib/libadmb-contribo.so -Wl,-force_load ../build/dist/lib/libadmb-contribo-shared.a
    else
	$(CXX) -shared $(LDFLAGS) -o ../build/dist/lib/libadmb-contrib.so -Wl,--whole-archive ../build/dist/lib/libadmb-contrib-shared.a -Wl,--no-whole-archive
	$(CXX) -shared $(LDFLAGS) -o ../build/dist/lib/libadmb-contribo.so -Wl,--whole-archive ../build/dist/lib/libadmb-contribo-shared.a -Wl,--no-whole-archive
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
	if exist  src\$(CONTRIB_LIB)\..\..\lib\libadmb-contrib$(SHARED).a del src\$(CONTRIB_LIB)\..\..\lib\libadmb-contrib$(SHARED).a
	copy src\$(CONTRIB_LIB)\..\..\lib\libadmb$(SHARED).a src\$(CONTRIB_LIB)\..\..\lib\libadmb-contrib$(SHARED).a
	$(AR) -rs src\$(CONTRIB_LIB)\..\..\lib\libadmb-contrib$(SHARED).a ..\build\objects\debug\contrib-saflp-*.obj
	if exist  src\$(CONTRIB_LIB)\..\..\lib\libadmb-contribo$(SHARED).a del src\$(CONTRIB_LIB)\..\..\lib\libadmb-contribo$(SHARED).a
	copy src\$(CONTRIB_LIB)\..\..\lib\libadmbo$(SHARED).a src\$(CONTRIB_LIB)\..\..\lib\libadmb-contribo$(SHARED).a
	$(AR) -rs src\$(CONTRIB_LIB)\..\..\lib\libadmb-contribo$(SHARED).a ..\build\objects\debug\contrib-optlp-*.obj
  else
	if exist  src\$(CONTRIB_LIB)\..\..\lib\libadmb-contrib$(SHARED).a del src\$(CONTRIB_LIB)\..\..\lib\libadmb-contrib$(SHARED).a
	copy src\$(CONTRIB_LIB)\..\..\lib\libadmb$(SHARED).a src\$(CONTRIB_LIB)\..\..\lib\libadmb-contrib$(SHARED).a
	$(AR) -rs src\$(CONTRIB_LIB)\..\..\lib\libadmb-contrib$(SHARED).a ..\build\objects\dist\contrib-saflp-*.obj
	if exist  src\$(CONTRIB_LIB)\..\..\lib\libadmb-contribo$(SHARED).a del src\$(CONTRIB_LIB)\..\..\lib\libadmb-contribo$(SHARED).a
	copy src\$(CONTRIB_LIB)\..\..\lib\libadmbo$(SHARED).a src\$(CONTRIB_LIB)\..\..\lib\libadmb-contribo$(SHARED).a
	$(AR) -rs src\$(CONTRIB_LIB)\..\..\lib\libadmb-contribo$(SHARED).a ..\build\objects\dist\contrib-optlp-*.obj
  endif
else
  ifdef SHARED
    ifeq ($(DEBUG),yes)
	rm -vf src/$(CONTRIB_DIR)/../lib/libadmb-contrib-shared.a
	cp -vf src/$(CONTRIB_DIR)/../lib/libadmb-shared.a src/$(CONTRIB_DIR)/../lib/libadmb-contrib-shared.a
	$(AR) -rs src/$(CONTRIB_DIR)/../lib/libadmb-contrib-shared.a ../build/objects/debug/contrib-shared-saflp-*.obj
	rm -vf src/$(CONTRIB_DIR)/../lib/libadmb-contribo-shared.a
	cp -vf src/$(CONTRIB_DIR)/../lib/libadmbo-shared.a src/$(CONTRIB_DIR)/../lib/libadmb-contribo-shared.a
	$(AR) -rs src/$(CONTRIB_DIR)/../lib/libadmb-contribo-shared.a ../build/objects/debug/contrib-shared-optlp-*.obj
    else
	rm -vf src/$(CONTRIB_DIR)/../lib/libadmb-contrib-shared.a
	cp -vf src/$(CONTRIB_DIR)/../lib/libadmb-shared.a src/$(CONTRIB_DIR)/../lib/libadmb-contrib-shared.a
	$(AR) -rs src/$(CONTRIB_DIR)/../lib/libadmb-contrib-shared.a ../build/objects/dist/contrib-shared-saflp-*.obj
	rm -vf src/$(CONTRIB_DIR)/../lib/libadmb-contribo-shared.a
	cp -vf src/$(CONTRIB_DIR)/../lib/libadmbo-shared.a src/$(CONTRIB_DIR)/../lib/libadmb-contribo-shared.a
	$(AR) -rs src/$(CONTRIB_DIR)/../lib/libadmb-contribo-shared.a ../build/objects/dist/contrib-shared-optlp-*.obj
    endif
  else
    ifeq ($(DEBUG),yes)
	rm -vf src/$(CONTRIB_DIR)/../lib/libadmb-contrib.a
	cp -vf src/$(CONTRIB_DIR)/../lib/libadmb.a src/$(CONTRIB_DIR)/../lib/libadmb-contrib.a
	$(AR) -rs src/$(CONTRIB_DIR)/../lib/libadmb-contrib.a ../build/objects/debug/contrib-saflp-*.obj
	rm -vf src/$(CONTRIB_DIR)/../lib/libadmb-contribo.a
	cp -vf src/$(CONTRIB_DIR)/../lib/libadmbo.a src/$(CONTRIB_DIR)/../lib/libadmb-contribo.a
	$(AR) -rs src/$(CONTRIB_DIR)/../lib/libadmb-contribo.a ../build/objects/debug/contrib-optlp-*.obj
    else
	rm -vf src/$(CONTRIB_DIR)/../lib/libadmb-contrib.a
	cp -vf src/$(CONTRIB_DIR)/../lib/libadmb.a src/$(CONTRIB_DIR)/../lib/libadmb-contrib.a
	$(AR) -rs src/$(CONTRIB_DIR)/../lib/libadmb-contrib.a ../build/objects/dist/saflp-*.obj ../build/objects/dist/contrib-saflp-*.obj
	rm -vf src/$(CONTRIB_DIR)/../lib/libadmb-contribo.a
	cp -vf src/$(CONTRIB_DIR)/../lib/libadmbo.a src/$(CONTRIB_DIR)/../lib/libadmb-contribo.a
	$(AR) -rs src/$(CONTRIB_DIR)/../lib/libadmb-contribo.a ../build/objects/dist/contrib-optlp-*.obj
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
	if not exist src\$(CONTRIB_DIR) md src\$(CONTRIB_DIR)
	if not exist src\$(CONTRIB_BIN) md src\$(CONTRIB_BIN)
	if not exist src\$(CONTRIB_INCLUDE) md src\$(CONTRIB_INCLUDE)
	if not exist src\$(CONTRIB_LIB) md src\$(CONTRIB_LIB)
else
	mkdir -p src/$(CONTRIB_DIR)
	mkdir -p src/$(CONTRIB_BIN)
	mkdir -p src/$(CONTRIB_INCLUDE)
	mkdir -p src/$(CONTRIB_LIB)
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
