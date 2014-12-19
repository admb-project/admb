ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL=cmd
  else
    EXT=.sh
  endif
endif
TARGET=cov_re

all: clean cov_re cov_re_sep run

cov_re: cov_re.tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb -r $@
else
	../../admb$(EXT) -r $@
endif

cov_re_sep: cov_re_sep.tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb -r $@
else
	../../admb$(EXT) -r $@
endif

run:
ifeq ($(SHELL),cmd)
	cov_re
	cov_re_sep
	cov_re_sep -shess
else
	./cov_re
	./cov_re_sep
	./cov_re_sep -shess
endif

clean:
ifeq ($(SHELL),cmd)
	@del $(TARGET)
	@del variance
	@del fmin.log
	@del $(TARGET).eva
	@del $(TARGET).exe
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
	@del admodel.cov
	@del admodel.dep
	@del admodel.hes
	@del cov_re.luu
	@del cov_re.rhes
	@del cov_re_sep
	@del cov_re_sep.exe
	@del cov_re_sep.bar
	@del cov_re_sep.bgs
	@del cov_re_sep.cor
	@del cov_re_sep.cpp
	@del cov_re_sep.eva
	@del cov_re_sep.htp
	@del cov_re_sep.log
	@del cov_re_sep.obj
	@del cov_re_sep.par
	@del cov_re_sep.rhes
	@del cov_re_sep.std
	@del hesscheck
	@del hessian.bin
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
