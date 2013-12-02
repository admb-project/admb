ifeq ($(SHELL),sh.exe)
  OBJS_DIR=..\..\build\objects\dist
  OBJS_DIR:=$(addsuffix \,$(OBJS_DIR))
  OBJS_DIR2=..\build\objects\dist
  OBJS_DIR2:=$(addsuffix \,$(OBJS_DIR2))
  ifndef DIST
    DIST=..\build\dist
  endif
  CONTRIB_DIR=..\$(addsuffix \contrib,$(DIST))
  CONTRIB_LIB=$(addsuffix \contrib\lib\,$(DIST))
else
  OBJS_DIR=../../build/objects/dist/
  OBJS_DIR2=../build/objects/dist/
  ifndef DIST
    DIST=../build/dist
  endif
  CONTRIB_DIR=../$(addsuffix /contrib,$(DIST))
  CONTRIB_LIB=$(addsuffix /contrib/lib/,$(DIST))
endif

all: contrib-libs contrib-ad2csv

contrib-libs: contrib-ecolib contrib-gdbprintlib contrib-qfclib contrib-statslib contrib-src
	$(AR) -rs $(CONTRIB_LIB)libcontrib.a $(OBJS_DIR2)saflp-contrib-*.obj
	$(AR) -rs $(CONTRIB_LIB)libcontribo.a $(OBJS_DIR2)optlp-contrib-*.obj

contrib-ecolib:
	$(MAKE) --directory=ecolib PREFIX=$(OBJS_DIR)saflp-$@- CONTRIB_DIR=$(CONTRIB_DIR)
	$(MAKE) --directory=ecolib OPTION=-f PREFIX=$(OBJS_DIR)optlp-$@- CONTRIB_DIR=$(CONTRIB_DIR)

contrib-gdbprintlib:
	$(MAKE) --directory=gdbprintlib PREFIX=$(OBJS_DIR)saflp-$@- CONTRIB_DIR=$(CONTRIB_DIR)
	$(MAKE) --directory=gdbprintlib OPTION=-f PREFIX=$(OBJS_DIR)optlp-$@- CONTRIB_DIR=$(CONTRIB_DIR)

contrib-qfclib:
	$(MAKE) --directory=qfclib PREFIX=$(OBJS_DIR)saflp-$@- CONTRIB_DIR=$(CONTRIB_DIR)
	$(MAKE) --directory=qfclib OPTION=-f PREFIX=$(OBJS_DIR)optlp-$@- CONTRIB_DIR=$(CONTRIB_DIR)

contrib-statslib:
	$(MAKE) --directory=statslib PREFIX=$(OBJS_DIR)saflp-$@- CONTRIB_DIR=$(CONTRIB_DIR)
	$(MAKE) --directory=statslib OPTION=-f PREFIX=$(OBJS_DIR)optlp-$@- CONTRIB_DIR=$(CONTRIB_DIR)

contrib-src:
	$(MAKE) --directory=src PREFIX=$(OBJS_DIR)saflp-$@- CONTRIB_DIR=$(CONTRIB_DIR)
	$(MAKE) --directory=src OPTION=-f PREFIX=$(OBJS_DIR)optlp-$@- CONTRIB_DIR=$(CONTRIB_DIR)

contrib-ad2csv:
	$(MAKE) --directory=ad2csv OPTION=-f

test:
	$(MAKE) --directory=src test 

contrib-admb2r:
	$(MAKE) --directory=admb2r ADMB_HOME="$(ADMB_HOME)" gcc

contrib-test-R:
	$(MAKE) --directory=ecolib test
	$(MAKE) --directory=qfclib test

clean:
	@$(MAKE) --directory=ecolib clean
	@$(MAKE) --directory=gdbprintlib clean
	@$(MAKE) --directory=qfclib clean
	@$(MAKE) --directory=statslib clean
	@$(MAKE) --directory=src clean
	@$(MAKE) --directory=ad2csv clean
