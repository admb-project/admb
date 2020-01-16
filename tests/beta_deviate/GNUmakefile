ifeq ($(OS),Windows_NT)
  ifeq ($(strip $(OSTYPE)),)
    SHELL=cmd
  else
    EXT=.sh
  endif
endif

TARGET=minto

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl $(TARGET).dat
ifeq ($(SHELL),cmd)
	..\\..\\admb -r -g $(TARGET)
else
	../../admb$(EXT) -r -g $(TARGET)
endif

run:
ifeq ($(SHELL),cmd)
	$(TARGET)
else
	./$(TARGET)
endif

clean:
ifeq ($(SHELL),cmd)
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
	@del hesscheck 2>nul
	@del hessian.bin 2>nul
	@del minto.rhes 2>nul
else
	@rm -vf $(TARGET)
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
	@rm -vf tests_$(TARGET).o
	@rm -vf tests_$(TARGET)
	@rm -vf eigv.rpt
	@rm -vf hesscheck
	@rm -vf hessian.bin
	@rm -vf nf1b2list12
	@rm -vf f1b2list1
	@rm -vf nf1b2list13
	@rm -vf nf1b2list1
	@rm -vf minto.rhes
	@rm -vf f1b2list12
	@rm -vf f1b2list13
	@rm -vf beta_deviate.log
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf hesscheck
	@rm -vf hessian.bin
	@rm -vf minto.rhes
endif

get-outputs:
ifeq ($(SHELL),cmd)
	type hesscheck
	type minto.cor
	type minto.dat
	type minto.eva
	type minto.par
	type minto.rhes
	type minto.std
else
	cat hesscheck
	cat minto.cor
	cat minto.dat
	cat minto.eva
	cat minto.par
	cat minto.rhes
	cat minto.std
endif
