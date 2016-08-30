ifeq ($(TERM),cygwin)
else
ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL=cmd
  else
    EXT=.sh
  endif
endif
endif

TARGET=hysimple

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb $(TARGET)
else
	../../admb$(EXT) $(TARGET)
endif

run:
ifeq ($(SHELL),cmd)
	$(TARGET) -hybrid -mcmc 2000 -hyeps .3 -hynsteps 20
	$(TARGET) -mceval
else
	./$(TARGET) -hybrid -mcmc 2000 -hyeps .3 -hynsteps 20
	./$(TARGET) -mceval
endif

clean:
ifeq ($(SHELL),cmd)
	@del hybrid_seed
	@del hysimple.obj
	@del admodel.cov
	@del admodel.hes
	@del fmin.log
	@del hysimple
	@del hysimple.exe
	@del hysimple.cor
	@del hysimple.eva
	@del hysimple.log
	@del hysimple.par
	@del hysimple.std
	@del sims
	@del admodel.dep
	@del eigv.rpt
	@del hysimple.bar
	@del hysimple.cpp
	@del hysimple.htp
	@del hysimple.o
	@del hysimple.psv
	@del variance
else
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
endif
