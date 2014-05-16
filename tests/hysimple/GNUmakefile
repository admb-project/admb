TARGET=hysimple

ifeq ($(OS),Windows_NT)
EXT=.sh
endif

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl
	../../admb$(EXT) $(TARGET)

run:
	@printf "Started run:\n"
	./$(TARGET) -hybrid -mcmc 2000 -hyeps .3 -hynsteps 20
	./$(TARGET) -mceval
	@printf "Finished run.\n"

clean:
	@rm -f hybrid_seed
	@rm -f hysimple.obj
	@rm -f admodel.cov
	@rm -f admodel.hes
	@rm -f fmin.log
	@rm -f hysimple
	@rm -f hysimple.cor
	@rm -f hysimple.eva
	@rm -f hysimple.log
	@rm -f hysimple.par
	@rm -f hysimple.std
	@rm -f sims
	@rm -f admodel.dep
	@rm -f eigv.rpt
	@rm -f hysimple.bar
	@rm -f hysimple.cpp
	@rm -f hysimple.htp
	@rm -f hysimple.o
	@rm -f hysimple.psv
	@rm -f variance
