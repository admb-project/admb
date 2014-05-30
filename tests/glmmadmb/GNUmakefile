ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL=cmd
  endif
endif

TARGET=glmmadmb

all: clean $(TARGET) nbmm bvprobit

$(TARGET): $(TARGET).tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb$(EXT) -r $(TARGET)
else
	../../admb$(EXT) -r $(TARGET)
endif

$(TARGET).tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/glmmadmb/pkg/inst/tpl/$@ > $@

nbmm: nbmm.tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb$(EXT) -r $@
else
	../../admb$(EXT) -r $@
endif

nbmm.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/glmmadmb/pkg/inst/tpl/$@ > $@

bvprobit: bvprobit.tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb$(EXT) -r $@
else
	../../admb$(EXT) -r $@
endif

bvprobit.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/glmmadmb/pkg/inst/tpl/$@ > $@

run:
ifeq ($(SHELL),cmd)
	$(TARGET)
else
	touch $(TARGET).dat
	./$(TARGET)
endif

clean:
ifeq ($(SHELL),cmd)
	@del $(TARGET)
	@del variance
	@del fmin.log
	@del $(TARGET).eva
	@del $(TARGET).htp
	@del $(TARGET).bar
	@del $(TARGET).bgs
	@del $(TARGET).cor
	@del $(TARGET).cpp
	@del $(TARGET).log
	@del $(TARGET).o
	@del $(TARGET).obj
	@del $(TARGET).par
	@del $(TARGET).std
	@del tests_$(TARGET).o
	@del tests_$(TARGET)
	@del eigv.rpt
else
	@rm -vf $(TARGET)
	@rm -vf $(TARGET).dat
	@rm -vf admodel.*
	@rm -vf variance
	@rm -vf fmin.log
	@rm -vf $(TARGET).eva
	@rm -vf $(TARGET).htp
	@rm -vf $(TARGET).bar
	@rm -vf $(TARGET).bgs
	@rm -vf $(TARGET).cor
	@rm -vf $(TARGET).cpp
	@rm -vf $(TARGET).log
	@rm -vf $(TARGET).o
	@rm -vf $(TARGET).obj
	@rm -vf $(TARGET).par
	@rm -vf $(TARGET).std
	@rm -vf eigv.rpt
endif
