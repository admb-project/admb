ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL=cmd
  else
    EXT=.sh
  endif
endif

TARGET=betareg

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl $(TARGET).dat
ifeq ($(SHELL),cmd)
	..\\..\\admb -r $(TARGET)
else
	../../admb$(EXT) -r $(TARGET)
endif

run:
ifeq ($(SHELL),cmd)
	$(TARGET)
else
	./$(TARGET)
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
	@del a
	@del admodel.cov
	@del admodel.dep
	@del admodel.hes
	@del b1
	@del b2
	@del betareg.b01
	@del betareg.b02
	@del betareg.luu
	@del betareg.p01
	@del betareg.p02
	@del betareg.r01
	@del betareg.r02
	@del betareg.rep
	@del betareg.rhes
	@del data
	@del hesscheck
	@del hessian.bin
	@del s1
	@del s2
else
	@rm -vf a
	@rm -vf betareg.p02
	@rm -vf betareg.par
	@rm -vf betareg.b02
	@rm -vf betareg.r02
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
	@rm -vf a
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf b1
	@rm -vf b2
	@rm -vf betareg.b01
	@rm -vf betareg.b02
	@rm -vf betareg.luu
	@rm -vf betareg.p01
	@rm -vf betareg.p02
	@rm -vf betareg.r01
	@rm -vf betareg.r02
	@rm -vf betareg.rep
	@rm -vf betareg.rhes
	@rm -vf data
	@rm -vf hesscheck
	@rm -vf hessian.bin
	@rm -vf s1
	@rm -vf s2
endif
