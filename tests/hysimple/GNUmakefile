ifeq ($(OS),Windows_NT)
  ifeq ($(strip $(OSTYPE)),)
    SHELL=cmd
  else
    EXT=.sh
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
	@del hybrid_seed 2>nul
	@del hysimple.obj 2>nul
	@del admodel.cov 2>nul
	@del admodel.hes 2>nul
	@del fmin.log 2>nul
	@del hysimple 2>nul
	@del hysimple.exe 2>nul
	@del hysimple.cor 2>nul
	@del hysimple.eva 2>nul
	@del hysimple.log 2>nul
	@del hysimple.par 2>nul
	@del hysimple.std 2>nul
	@del sims 2>nul
	@del admodel.dep 2>nul
	@del eigv.rpt 2>nul
	@del hysimple.bar 2>nul
	@del hysimple.cpp 2>nul
	@del hysimple.htp 2>nul
	@del hysimple.o 2>nul
	@del hysimple.psv 2>nul
	@del variance 2>nul
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
