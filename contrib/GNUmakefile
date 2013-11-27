ifeq ($(SHELL),sh.exe)
  OBJSDIR=..\..\build\objects\dist
  OBJSDIR:=$(addsuffix \,$(OBJSDIR))
  ifndef DIST
    DIST=..\build\dist
  endif
  CONTRIBDIR=$(addsuffix \contrib\,$(DIST))
else
  OBJSDIR=../../build/objects/dist
  OBJSDIR:=$(addsuffix /,$(OBJSDIR))
  ifndef DIST
    DIST=../build/dist
  endif
  CONTRIBDIR=$(addsuffix /contrib/,$(DIST))
endif

all: libs build-ad2csv

libs: build-gdbprintlib build-statslib build-ecolib build-qfclib build-src
ifeq ($(SHELL),sh.exe)
	$(AR) -rs $(CONTRIBDIR)lib\libcontrib.a ..\build\objects\dist\saflp-contrib-*.obj
	$(AR) -rs $(CONTRIBDIR)lib\libcontribo.a ..\build\objects\dist\optlp-contrib-*.obj
else
	$(AR) -rs $(CONTRIBDIR)lib/libcontrib.a ../build/objects/dist/saflp-contrib-*.obj
	$(AR) -rs $(CONTRIBDIR)lib/libcontribo.a ../build/objects/dist/optlp-contrib-*.obj
endif

build-gdbprintlib:
	$(MAKE) --directory=gdbprintlib PREFIX_OBJ=$(OBJSDIR)saflp-contrib-gdbprintlib-
	$(MAKE) --directory=gdbprintlib PREFIX_OBJ=$(OBJSDIR)optlp-contrib-gdbprintlib-
ifeq ($(SHELL),sh.exe)
	copy gdbprintlib\gdbprintlib.h $(CONTRIBDIR)include
else
	cp gdbprintlib/gdbprintlib.h $(CONTRIBDIR)include
endif

build-statslib:
	$(MAKE) --directory=statslib PREFIX_OBJ=$(OBJSDIR)saflp-contrib-statslib-
	$(MAKE) --directory=statslib OPTION=-f PREFIX_OBJ=$(OBJSDIR)optlp-contrib-statslib-
ifeq ($(SHELL),sh.exe)
	copy statslib\statsLib.h $(CONTRIBDIR)include
else
	cp statslib/statsLib.h $(CONTRIBDIR)include
endif

build-ecolib:
	$(MAKE) --directory=ecolib PREFIX_OBJ=$(OBJSDIR)saflp-contrib-ecolib-
	$(MAKE) --directory=ecolib OPTION=-f PREFIX_OBJ=$(OBJSDIR)optlp-contrib-ecolib-
ifeq ($(SHELL),sh.exe)
	copy ecolib\ecolib.h $(CONTRIBDIR)include
else
	cp ecolib/ecolib.h $(CONTRIBDIR)include
endif

build-qfclib:
	$(MAKE) --directory=qfclib PREFIX_OBJ=$(OBJSDIR)saflp-contrib-qfclib-
	$(MAKE) --directory=qfclib OPTION=-f PREFIX_OBJ=$(OBJSDIR)optlp-contrib-qfclib-
ifeq ($(SHELL),sh.exe)
	copy qfclib\qfclib.h $(CONTRIBDIR)include
else
	cp qfclib/qfclib.h $(CONTRIBDIR)include
endif

build-ad2csv:
	$(MAKE) --directory=ad2csv

build-admb2r:
	$(MAKE) --directory=admb2r ADMB_HOME="$(ADMB_HOME)" gcc

build-src:
	$(MAKE) --directory=src OPTION=-f PREFIX_OBJ=$(OBJSDIR)optlp-contrib-
	$(MAKE) --directory=src PREFIX_OBJ=$(OBJSDIR)saflp-contrib-
ifeq ($(SHELL),sh.exe)
	copy src\contrib.h $(CONTRIBDIR)include
else
	cp src/contrib.h $(CONTRIBDIR)include
endif

test:
	$(MAKE) --directory=src test 

test-needR:
	$(MAKE) --directory=ecolib test
	$(MAKE) --directory=qfclib test

clean:
	@$(MAKE) --directory=gdbprintlib clean
	@$(MAKE) --directory=ecolib clean
	@$(MAKE) --directory=qfclib clean
	@$(MAKE) --directory=statslib clean
	@$(MAKE) --directory=ad2csv clean
	@$(MAKE) --directory=ad2csv clean
	@$(MAKE) --directory=src clean
