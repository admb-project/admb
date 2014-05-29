ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL=cmd
  endif
endif

TARGET=beta_regression

all: clean $(TARGET) run3 run2 run

$(TARGET): $(TARGET).tpl $(TARGET).dat
ifeq ($(SHELL),cmd)
	..\\..\\admb -r $(TARGET)
else
	../../admb -r $(TARGET)
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
endif
