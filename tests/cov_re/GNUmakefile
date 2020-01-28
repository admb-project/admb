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

TARGET=cov_re

all: clean cov_re cov_re_sep run

cov_re: cov_re.tpl
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb -r $@
else
	../../admb$(EXT) -r $@
endif

cov_re_sep: cov_re_sep.tpl
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb -r $@
else
	../../admb$(EXT) -r $@
endif

run:
ifeq ($(CMDSHELL),cmd)
	cov_re
	cov_re_sep
	cov_re_sep -shess
else
	./cov_re
	./cov_re_sep
	./cov_re_sep -shess
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
	@del cov_re.luu 2>nul
	@del cov_re.rhes 2>nul
	@del cov_re_sep 2>nul
	@del cov_re_sep.exe 2>nul
	@del cov_re_sep.bar 2>nul
	@del cov_re_sep.bgs 2>nul
	@del cov_re_sep.cor 2>nul
	@del cov_re_sep.cpp 2>nul
	@del cov_re_sep.eva 2>nul
	@del cov_re_sep.htp 2>nul
	@del cov_re_sep.log 2>nul
	@del cov_re_sep.obj 2>nul
	@del cov_re_sep.par 2>nul
	@del cov_re_sep.rhes 2>nul
	@del cov_re_sep.std 2>nul
	@del hesscheck 2>nul
	@del hessian.bin 2>nul
else
	@rm -vf cov_re.o
	@rm -vf cov_re.obj
	@rm -vf cov_re.cor
	@rm -vf cov_re.bar
	@rm -vf cov_re.luu
	@rm -vf admodel.hes
	@rm -vf cov_re.eva
	@rm -vf cov_re.bgs
	@rm -vf variance
	@rm -vf admodel.cov
	@rm -vf cov_re.log
	@rm -vf cov_re.par
	@rm -vf cov_re.cpp
	@rm -vf eigv.rpt
	@rm -vf hesscheck
	@rm -vf hessian.bin
	@rm -vf cov_re.std
	@rm -vf cov_re.htp
	@rm -vf fmin.log
	@rm -vf admodel.dep
	@rm -vf cov_re
	@rm -vf cov_re.exe
	@rm -vf cov_re.rhes
	@rm -vf cov_re_sep
	@rm -vf cov_re_sep.exe
	@rm -vf cov_re_sep.o
	@rm -vf cov_re_sep.obj
	@rm -vf cov_re_sep.cor
	@rm -vf cov_re_sep.rhes
	@rm -vf cov_re_sep.bar
	@rm -vf cov_re_sep.eva
	@rm -vf cov_re_sep.bgs
	@rm -vf cov_re_sep.log
	@rm -vf cov_re_sep.par
	@rm -vf cov_re_sep.cpp
	@rm -vf cov_re_sep.std
	@rm -vf cov_re_sep.htp
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf cov_re.luu
	@rm -vf cov_re.rhes
	@rm -vf cov_re_sep
	@rm -vf cov_re_sep.bar
	@rm -vf cov_re_sep.bgs
	@rm -vf cov_re_sep.cor
	@rm -vf cov_re_sep.cpp
	@rm -vf cov_re_sep.eva
	@rm -vf cov_re_sep.htp
	@rm -vf cov_re_sep.log
	@rm -vf cov_re_sep.obj
	@rm -vf cov_re_sep.par
	@rm -vf cov_re_sep.rhes
	@rm -vf cov_re_sep.std
	@rm -vf hesscheck
	@rm -vf hessian.bin
endif
