ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifeq ($(findstring bash.exe,$(shell where bash.exe 2>&1 | findstr bash.exe)),bash.exe)
      EXT=.sh
    else
      CMDSHELL=cmd
    endif
  endif
endif

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb $(TARGET)
else
	../../admb$(EXT) $(TARGET)
endif

run:
ifeq ($(CMDSHELL),cmd)
	$(TARGET)
else
	./$(TARGET)
endif

clean:
ifeq ($(CMDSHELL),cmd)
	@del $(TARGET) 2>nul
	@del variance 2>nul
	@del fmin.log 2>nul
	@del $(TARGET).eva 2>nul
	@del $(TARGET).exe 2>nul
	@del $(TARGET).htp 2>nul
	@del $(TARGET).bar 2>nul
	@del $(TARGET).bgs 2>nul
	@del $(TARGET).cor 2>nul
	@del $(TARGET).cpp 2>nul
	@del $(TARGET).log 2>nul
	@del $(TARGET).o 2>nul
	@del $(TARGET).obj 2>nul
	@del $(TARGET).par 2>nul
	@del $(TARGET).std 2>nul
	@del tests_$(TARGET).o 2>nul
	@del tests_$(TARGET) 2>nul
	@del eigv.rpt 2>nul
	@del admodel.cov 2>nul
	@del admodel.dep 2>nul
	@del admodel.hes 2>nul
	@del $(TARGET).luu 2>nul
	@del $(TARGET).rhes 2>nul
	@del hesscheck 2>nul
	@del hessian.bin 2>nul
else
	@rm -vf $(TARGET)
	@rm -vf admodel.*
	@rm -vf variance
	@rm -vf hessian.bin
	@rm -vf hesscheck
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
	@rm -vf $(TARGET).luu
	@rm -vf $(TARGET).rhes
	@rm -vf eigv.rpt
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf $(TARGET).luu
	@rm -vf $(TARGET).rhes
	@rm -vf hesscheck
	@rm -vf hessian.bin
endif
endif

TARGET=priors
TPL_TARGET=rat
TPL_TARGETRE=ratre

all: clean run runre

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
