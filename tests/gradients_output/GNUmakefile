ifeq ($(OS),Windows_NT)
  ifeq ($(strip $(OSTYPE)),)
    SHELL=cmd
  else
    EXT=.sh
  endif
endif

TARGET=de

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl $(TARGET).dat
ifeq ($(SHELL),cmd)
	..\\..\\admb $(TARGET)
else
	../../admb$(EXT) $(TARGET)
endif

run:
ifeq ($(SHELL),cmd)
	$(TARGET)
	type $(TARGET).rep
else
	./$(TARGET)
	cat $(TARGET).rep
endif

clean:
ifeq ($(SHELL),cmd)
	@del a 2>nul
	@del $(TARGET).p02 2>nul
	@del $(TARGET).par 2>nul
	@del $(TARGET).b02 2>nul
	@del $(TARGET).r02 2>nul
	@del b1 b2 s1 s2 2>nul
	@del $(TARGET) 2>nul
	@del admodel.tmp 2>nul
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
	@del $(TARGET).luu 2>nul
	@del $(TARGET).b01 2>nul
	@del $(TARGET).psv 2>nul
	@del $(TARGET).r01 2>nul
	@del $(TARGET).o 2>nul
	@del $(TARGET).obj 2>nul
	@del $(TARGET).p01 2>nul
	@del $(TARGET).std 2>nul
	@del $(TARGET).rep 2>nul
	@del $(TARGET).rhes 2>nul
	@del f1b2list13 2>nul
	@del hesscheck 2>nul
	@del data 2>nul
	@del sims 2>nul
	@del eigv.rpt 2>nul
	@del hessian.bin 2>nul
	@del f1b2list1 gradfil1.tmp nf1b2list12 2>nul
	@del f1b2list12 gradfil2.tmp nf1b2list13 2>nul
	@del cmpdiff.tmp f1b2list1 nf1b2list1 varssave.tmp 2>nul
	@del admodel.cov 2>nul
	@del admodel.dep 2>nul
	@del admodel.hes 2>nul
else
	@rm -vf a
	@rm -vf $(TARGET).p02
	@rm -vf $(TARGET).par
	@rm -vf $(TARGET).b02
	@rm -vf $(TARGET).r02
	@rm -vf b1 b2 s1 s2
	@rm -vf $(TARGET)
	@rm -vf admodel.*
	@rm -vf variance
	@rm -vf fmin.log
	@rm -vf $(TARGET).eva
	@rm -vf $(TARGET).exe
	@rm -vf $(TARGET).htp
	@rm -vf $(TARGET).bar
	@rm -vf $(TARGET).bgs
	@rm -vf $(TARGET).cor
	@rm -vf $(TARGET).cpp
	@rm -vf $(TARGET).log
	@rm -vf $(TARGET).luu
	@rm -vf $(TARGET).b01
	@rm -vf $(TARGET).psv
	@rm -vf $(TARGET).r01
	@rm -vf $(TARGET).o
	@rm -vf $(TARGET).obj
	@rm -vf $(TARGET).p01
	@rm -vf $(TARGET).std
	@rm -vf $(TARGET).rep
	@rm -vf $(TARGET).rhes
	@rm -vf f1b2list13
	@rm -vf hesscheck
	@rm -vf data
	@rm -vf sims
	@rm -vf eigv.rpt
	@rm -vf hessian.bin
	@rm -vf f1b2list1 gradfil1.tmp nf1b2list12
	@rm -vf f1b2list12 gradfil2.tmp nf1b2list13
	@rm -vf cmpdiff.tmp f1b2list1 nf1b2list1 varssave.tmp
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
endif
