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
  CONTRIB_OBJS_DIR=..\..\build\objects\contrib
  CONTRIB_DIR=..\..\build\dist\contrib
  CONTRIB_BIN=$(addsuffix \bin,$(CONTRIB_DIR))
  CONTRIB_INCLUDE=$(addsuffix \include,$(CONTRIB_DIR))
  CONTRIB_LIB=$(addsuffix \lib,$(CONTRIB_DIR))
else
  CONTRIB_OBJS_DIR=../../build/objects/contrib
  CONTRIB_DIR=../../build/dist/contrib
  CONTRIB_BIN=$(addsuffix /bin,$(CONTRIB_DIR))
  CONTRIB_INCLUDE=$(addsuffix /include,$(CONTRIB_DIR))
  CONTRIB_LIB=$(addsuffix /lib,$(CONTRIB_DIR))
endif
ifdef DEBUG
OPTION=-g
endif

all: 
	$(MAKE) contrib-includes
	$(MAKE) contrib-libs
	$(MAKE) contrib-ad2csv
	@echo ADMB contrib build completed.

shared: all
ifeq ($(SHELL),cmd)
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\dist\contrib\lib\contrib.dll -Wl,--whole-archive ..\build\dist\contrib\lib\libcontrib.a -Wl,--no-whole-archive -Wl,-Bdynamic ..\build\dist\lib\admb.dll
	$(CXX) -static -shared $(LDFLAGS) -o ..\build\dist\contrib\lib\contribo.dll -Wl,--whole-archive ..\build\dist\contrib\lib\libcontribo.a -Wl,--no-whole-archive -Wl,-Bdynamic ..\build\dist\lib\admbo.dll
else
  ifeq (LLVM,$(findstring LLVM,$(shell $(CXX) --version)))
	$(CXX) -shared $(LDFLAGS) -o../build/dist/contrib/lib/libcontrib.so -Wl,-force_load ../build/dist/contrib/lib/libcontrib.a ../build/dist/lib/libadmb.so
	$(CXX) -shared $(LDFLAGS) -o../build/dist/contrib/lib/libcontribo.so -Wl,-force_load ../build/dist/contrib/lib/libcontribo.a ../build/dist/lib/libadmbo.so
  else
	$(CXX) -shared $(LDFLAGS) -o../build/dist/contrib/lib/libcontrib.so -Wl,--whole-archive ../build/dist/contrib/lib/libcontrib.a -Wl,--no-whole-archive ../build/dist/lib/libadmb.so
	$(CXX) -shared $(LDFLAGS) -o../build/dist/contrib/lib/libcontribo.so -Wl,--whole-archive ../build/dist/contrib/lib/libcontribo.a -Wl,--no-whole-archive ../build/dist/lib/libadmbo.so
  endif
endif
	@echo ADMB contrib shared build completed.

contrib-includes: contrib-dirs
	@$(MAKE) --directory=ecolib CONTRIB_INCLUDE=$(CONTRIB_INCLUDE) includes
	@$(MAKE) --directory=gdbprintlib CONTRIB_INCLUDE=$(CONTRIB_INCLUDE) includes
	@$(MAKE) --directory=qfclib CONTRIB_INCLUDE=$(CONTRIB_INCLUDE) includes
	@$(MAKE) --directory=statslib CONTRIB_INCLUDE=$(CONTRIB_INCLUDE) includes
	@$(MAKE) --directory=src CONTRIB_INCLUDE=$(CONTRIB_INCLUDE) includes

contrib-libs: contrib-ecolib contrib-gdbprintlib contrib-qfclib contrib-statslib contrib-src
ifeq ($(SHELL),cmd)
	if exist  src\$(CONTRIB_LIB)\libcontrib.a del src\$(CONTRIB_LIB)\libcontrib.a
	$(AR) -rs src\$(CONTRIB_LIB)\libcontrib.a src\$(CONTRIB_OBJS_DIR)\saflp-contrib-*.obj
	if exist  src\$(CONTRIB_LIB)\libcontribo.a del src\$(CONTRIB_LIB)\libcontribo.a
	$(AR) -rs src\$(CONTRIB_LIB)\libcontribo.a src\$(CONTRIB_OBJS_DIR)\optlp-contrib-*.obj
else
	rm -vf src/$(CONTRIB_LIB)/libcontrib.a
	$(AR) -rs src/$(CONTRIB_LIB)/libcontrib.a src/$(CONTRIB_OBJS_DIR)/saflp-contrib-*.obj
	rm -vf src/$(CONTRIB_LIB)/libcontribo.a
	$(AR) -rs src/$(CONTRIB_LIB)/libcontribo.a src/$(CONTRIB_OBJS_DIR)/optlp-contrib-*.obj
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
	if not exist src\$(CONTRIB_OBJS_DIR) md src\$(CONTRIB_OBJS_DIR)
	if not exist src\$(CONTRIB_DIR) md src\$(CONTRIB_DIR)
	if not exist src\$(CONTRIB_BIN) md src\$(CONTRIB_BIN)
	if not exist src\$(CONTRIB_INCLUDE) md src\$(CONTRIB_INCLUDE)
	if not exist src\$(CONTRIB_LIB) md src\$(CONTRIB_LIB)
else
	mkdir -p src/$(CONTRIB_OBJS_DIR)
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
ifeq ($(SHELL),cmd)
	if not exist ..\build\dist\contrib md ..\build\dist\contrib
	xcopy ..\contrib ..\build\dist\contrib /S /Y /D
else
	cp -R ../contrib ../build/dist/
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
