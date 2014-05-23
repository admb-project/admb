TARGET=gmrf

ifeq ($(OS),Windows_NT)
EXT=.sh
endif

all: clean $(TARGET) run run2

$(TARGET): $(TARGET).tpl
	../../admb$(EXT) -r $(TARGET)

run:
	@printf "Started run:\n"
	./run
	@printf "Finished run.\n"

run2:
	@printf "Started runw:\n"
	./run2
	@printf "Finished run2.\n"

clean:
	@rm -vf gmrf.par
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
