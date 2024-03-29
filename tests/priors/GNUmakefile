ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifndef TERM
      export SHELL=cmd
      CMDSHELL=cmd
    endif
    ifndef CMDSHELL
      EXT=.sh
    endif
  endif
endif

TARGET=priors
TPL_TARGET=rat
TPL_TARGETRE=ratre

all: clean
	$(MAKE) run
	$(MAKE) runre

run: $(TPL_TARGET)
ifeq ($(CMDSHELL),cmd)
	$(TPL_TARGET) -nohess
else
	./$(TPL_TARGET) -nohess
endif

runre: $(TPL_TARGETRE)
ifeq ($(CMDSHELL),cmd)
	$(TPL_TARGETRE) -nohess
else
	./$(TPL_TARGETRE) -nohess
endif

$(TPL_TARGET): $(TPL_TARGET).tpl
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb $(TPL_TARGET)
else
	../../admb$(EXT) $(TPL_TARGET)
endif

$(TPL_TARGETRE): $(TPL_TARGETRE).tpl
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb -r $(TPL_TARGETRE)
else
	../../admb$(EXT) -r $(TPL_TARGETRE)
endif

get-outputs:
ifeq ($(CMDSHELL),cmd)
	@..\\..\\scripts\\get-outputs.bat $(TPL_TARGET)
	@..\\..\\scripts\\get-outputs.bat $(TPL_TARGETRE)
else
	@sh ../../scripts/get-outputs.sh $(TPL_TARGET)
	@sh ../../scripts/get-outputs.sh $(TPL_TARGETRE)
endif

clean:
ifeq ($(CMDSHELL),cmd)
	@del rat 2>nul
	@del ratre 2>nul
	@del rat.obj 2>nul
	@del ratre.obj 2>nul
	@del eigv.rpt 2>nul
	@del fmin.log 2>nul
	@del rat.exe 2>nul
	@del rat.b01 2>nul
	@del rat.b02 2>nul
	@del rat.bar 2>nul
	@del rat.cpp 2>nul
	@del rat.htp 2>nul
	@del rat.log 2>nul
	@del rat.o 2>nul
	@del rat.p01 2>nul
	@del rat.p02 2>nul
	@del rat.par 2>nul
	@del rat.r01 2>nul
	@del rat.r02 2>nul
	@del rat.rep 2>nul
	@del ratre.exe 2>nul
	@del ratre.b01 2>nul
	@del ratre.b02 2>nul
	@del ratre.bar 2>nul
	@del ratre.cpp 2>nul
	@del ratre.htp 2>nul
	@del ratre.log 2>nul
	@del ratre.o 2>nul
	@del ratre.p01 2>nul
	@del ratre.p02 2>nul
	@del ratre.par 2>nul
	@del ratre.r01 2>nul
	@del ratre.r02 2>nul
	@del ratre.rep 2>nul
	@del variance 2>nul
	@del cmpdiff.tmp 2>nul
	@del gradfil1.tmp 2>nul
	@del gradfil2.tmp 2>nul
	@del varssave.tmp 2>nul
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
