ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL=cmd
  else
    EXT=.sh
  endif
endif

TARGET=priors
TPL_TARGET=rat
TPL_TARGETRE=ratre

all: clean run runre

run: $(TPL_TARGET)
ifeq ($(SHELL),cmd)
	$(TPL_TARGET) -nohess
else
	./$(TPL_TARGET) -nohess
endif

runre: $(TPL_TARGETRE)
ifeq ($(SHELL),cmd)
	$(TPL_TARGETRE) -nohess
else
	./$(TPL_TARGETRE) -nohess
endif

$(TPL_TARGET): $(TPL_TARGET).tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb $(TPL_TARGET)
else
	../../admb$(EXT) $(TPL_TARGET)
endif

$(TPL_TARGETRE): $(TPL_TARGETRE).tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb -r $(TPL_TARGETRE)
else
	../../admb$(EXT) -r $(TPL_TARGETRE)
endif

clean:
ifeq ($(SHELL),cmd)
	@del rat
	@del ratre
	@del rat.obj
	@del ratre.obj
	@del eigv.rpt
	@del fmin.log
	@del rat.exe
	@del rat.b01
	@del rat.b02
	@del rat.bar
	@del rat.cpp
	@del rat.htp
	@del rat.log
	@del rat.o
	@del rat.p01
	@del rat.p02
	@del rat.par
	@del rat.r01
	@del rat.r02
	@del rat.rep
	@del ratre.exe
	@del ratre.b01
	@del ratre.b02
	@del ratre.bar
	@del ratre.cpp
	@del ratre.htp
	@del ratre.log
	@del ratre.o
	@del ratre.p01
	@del ratre.p02
	@del ratre.par
	@del ratre.r01
	@del ratre.r02
	@del ratre.rep
	@del variance
	@del cmpdiff.tmp
	@del gradfil1.tmp
	@del gradfil2.tmp
	@del varssave.tmp
else
	@rm -f rat.obj
	@rm -f ratre.obj
	@rm -f eigv.rpt
	@rm -f fmin.log
	@rm -f rat
	@rm -f rat.b01
	@rm -f rat.b02
	@rm -f rat.bar
	@rm -f rat.cpp
	@rm -f rat.htp
	@rm -f rat.log
	@rm -f rat.o
	@rm -f rat.p01
	@rm -f rat.p02
	@rm -f rat.par
	@rm -f rat.r01
	@rm -f rat.r02
	@rm -f rat.rep
	@rm -f ratre
	@rm -f ratre.b01
	@rm -f ratre.b02
	@rm -f ratre.bar
	@rm -f ratre.cpp
	@rm -f ratre.htp
	@rm -f ratre.log
	@rm -f ratre.o
	@rm -f ratre.p01
	@rm -f ratre.p02
	@rm -f ratre.par
	@rm -f ratre.r01
	@rm -f ratre.r02
	@rm -f ratre.rep
	@rm -f variance
	@rm -f cmpdiff.tmp
	@rm -f gradfil1.tmp
	@rm -f gradfil2.tmp
	@rm -f varssave.tmp
endif
