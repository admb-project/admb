ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL=cmd
  else
    EXT=.sh
  endif
endif

TARGET=testminmax

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb $(TARGET)
else
	../../admb$(EXT) $(TARGET)
endif

run:
ifeq ($(SHELL),cmd)
	$(TARGET) -nohess
else
	touch testminmax.dat
	./$(TARGET) -nohess
endif

clean:
ifeq ($(SHELL),cmd)
	@del b1 b2 s1 s2
	@del $(TARGET).exe
	@del variance
	@del testminmax.dat
	@del fmin.log
	@del $(TARGET).dat
	@del $(TARGET).par
	@del $(TARGET).eva
	@del $(TARGET).htp
	@del $(TARGET).bar
	@del $(TARGET).bgs
	@del $(TARGET).cor
	@del $(TARGET).cpp
	@del $(TARGET).log
	@del $(TARGET).luu
	@del $(TARGET).b01
	@del $(TARGET).psv
	@del $(TARGET).r01
	@del $(TARGET).o
	@del $(TARGET).obj
	@del $(TARGET).p01
	@del $(TARGET).std
	@del $(TARGET).rep
	@del $(TARGET).rhes
	@del $(TARGET)
	@del f1b2list13
	@del hesscheck
	@del data
	@del sims
	@del eigv.rpt
	@del hessian.bin
	@del f1b2list1 gradfil1.tmp nf1b2list12
	@del f1b2list12 gradfil2.tmp nf1b2list13
	@del cmpdiff.tmp f1b2list1 nf1b2list1 varssave.tmp
	@del eigv.rpt
	@del fmin.log
	@del testminmax.bar
	@del testminmax.cpp
	@del testminmax.exe
	@del testminmax.htp
	@del testminmax.log
	@del testminmax.obj
	@del testminmax.par
	@del variance
else
	@rm -vf b1 b2 s1 s2
	@rm -vf $(TARGET)
	@rm -vf admodel.*
	@rm -vf variance
	@rm -vf testminmax.dat
	@rm -vf fmin.log
	@rm -vf $(TARGET).dat
	@rm -vf $(TARGET).par
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
	@rm -vf $(TARGET)
	@rm -vf f1b2list13
	@rm -vf hesscheck
	@rm -vf data
	@rm -vf sims
	@rm -vf eigv.rpt
	@rm -vf hessian.bin
	@rm -vf f1b2list1 gradfil1.tmp nf1b2list12
	@rm -vf f1b2list12 gradfil2.tmp nf1b2list13
	@rm -vf cmpdiff.tmp f1b2list1 nf1b2list1 varssave.tmp
endif
