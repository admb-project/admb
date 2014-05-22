TARGET=beta_regression

ifeq ($(OS),Windows_NT)
EXT=.sh
endif

all: clean $(TARGET) run3 run2 run

$(TARGET): $(TARGET).tpl $(TARGET).dat
	../../admb$(EXT) -r $(TARGET)

run:
	@printf "Started run:\n"
	./$(TARGET) -mno 1000  -mceval -ainp $(TARGET).par -phase 10 -nohess 
	@printf "Finished run.\n"
run2:
	@printf "Started run2:\n"
	./$(TARGET) -mno 1000 -mcsave 20 -ainp $(TARGET).par -phase 10 -nohess -mcmc2 6000 -hybrid
	@printf "Finished run2.\n"

run3:
	@printf "Started run3:\n"
	./$(TARGET) -mno 1000
	@printf "Finished run3.\n"

clean:
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
