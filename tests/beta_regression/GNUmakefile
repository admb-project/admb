ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL=cmd
  else
    EXT=.sh
  endif
endif

TARGET=beta_regression

all: clean $(TARGET) run3 run2 run

$(TARGET): $(TARGET).tpl $(TARGET).dat
ifeq ($(SHELL),cmd)
	..\\..\\admb -r $(TARGET)
else
	../../admb$(EXT) -r $(TARGET)
endif

run:
ifeq ($(SHELL),cmd)
	$(TARGET) -mno 1000  -mceval -ainp $(TARGET).par -phase 10 -nohess 
else
	./$(TARGET) -mno 1000  -mceval -ainp $(TARGET).par -phase 10 -nohess 
endif

run2:
ifeq ($(SHELL),cmd)
	$(TARGET) -mno 1000 -mcsave 20 -ainp $(TARGET).par -phase 10 -nohess -mcmc2 6000 -hybrid
else
	./$(TARGET) -mno 1000 -mcsave 20 -ainp $(TARGET).par -phase 10 -nohess -mcmc2 6000 -hybrid
endif

run3:
ifeq ($(SHELL),cmd)
	$(TARGET) -mno 1000
else
	./$(TARGET) -mno 1000
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
	@del beta_regression.par
	@del admodel.cov
	@del admodel.dep
	@del admodel.hes
	@del b1
	@del b2
	@del beta_regression.b01
	@del beta_regression.luu
	@del beta_regression.p01
	@del beta_regression.psv
	@del beta_regression.r01
	@del beta_regression.rep
	@del beta_regression.rhes
	@del data
	@del hesscheck
	@del hessian.bin
	@del hybrid_seed
	@del s1
	@del s2
	@del sims
else
	@rm -vf b1 b2 s1 s2
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
	@rm -vf hybrid_seed
	@rm -vf beta_regression.par
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf b1
	@rm -vf b2
	@rm -vf beta_regression.b01
	@rm -vf beta_regression.luu
	@rm -vf beta_regression.p01
	@rm -vf beta_regression.psv
	@rm -vf beta_regression.r01
	@rm -vf beta_regression.rep
	@rm -vf beta_regression.rhes
	@rm -vf data
	@rm -vf hesscheck
	@rm -vf hessian.bin
	@rm -vf hybrid_seed
	@rm -vf s1
	@rm -vf s2
	@rm -vf sims
endif

get-outputs:
ifeq ($(SHELL),cmd)
	type b1
	type b2
	type beta_regression.cor
	type beta_regression.eva
	type beta_regression.p01
	type beta_regression.par
	type beta_regression.rhes
	type beta_regression.std
	type hesscheck
	type hybrid_seed
	type s1
	type s2
else
	cat b1
	cat b2
	cat beta_regression.cor
	cat beta_regression.eva
	cat beta_regression.p01
	cat beta_regression.par
	cat beta_regression.rhes
	cat beta_regression.std
	cat hesscheck
	cat hybrid_seed
	cat s1
	cat s2
endif
