.PHONY: all ham4 ham5 catage finance vonb vonbr n2mvol simple

verify: ham4 ham5 catage finance vonb vonbr n2mvol simple
	@echo -------------------------------
	@echo Completed ADMB example and runs
	@echo Successful
	@echo -------------------------------

all: simple
noverify: chem-eng forest pella-t truncreg union

ham4:
	@echo Build and run $@: && cd buscycle && admb.bat ham4 && ham4.exe
	@echo Build and run $@: && cd buscycle && admb.bat -s ham4 && ham4.exe

ham5:
	@echo Build and run $@: && cd buscycle && admb.bat ham5 && ham5.exe
	@echo Build and run $@: && cd buscycle && admb.bat -s ham5 && ham5.exe

catage:
	@echo Build and run $@: && cd catage && admb.bat catage && catage.exe
	@echo Build and run $@: && cd catage && admb.bat -s catage && catage.exe

chem-eng:
	@echo Build and run $@: && cd chem-eng && admb.bat chem-eng && chem-eng.exe
	@echo Build and run $@: && cd chem-eng && admb.bat -s chem-eng && chem-eng.exe

finance:
	@echo Build and run $@: && cd finance && admb.bat finance && finance.exe
	@echo Build and run $@: && cd finance && admb.bat -s finance && finance.exe

forest:
	@echo Build and run $@: && cd forest && admb.bat forest && forest.exe
	@echo Build and run $@: && cd forest && admb.bat -s forest && forest.exe

pella-t:
	@echo Build and run $@: && cd pella-t && admb.bat pella-t && pella-t.exe
	@echo Build and run $@: && cd pella-t && admb.bat -s pella-t && pella-t.exe

vonb:
	@echo Build and run $@: && cd robreg && admb.bat vonb && vonb.exe
	@echo Build and run $@: && cd robreg && admb.bat -s vonb && vonb.exe

vonbr:
	@echo Build and run $@: && cd robreg && admb.bat vonbr && vonbr.exe
	@echo Build and run $@: && cd robreg && admb.bat -s vonbr && vonbr.exe

simple:
	@echo Build and run $@: && cd simple && admb.bat simple && simple.exe
	@echo Build and run $@: && cd simple && admb.bat -s simple && simple.exe

truncreg:
	@echo Build and run $@: && cd truncreg && admb.bat truncreg && runtrunc.bat && fruntrunc
	@echo Build and run $@: && cd truncreg && admb.bat -s truncreg && runtrunc.bat && fruntrunc

n2mvol:
	@echo Build and run $@: && cd vol && admb.bat n2mvol && n2mvol.exe
	@echo Build and run $@: && cd vol && admb.bat -s n2mvol && n2mvol.exe

union:
	@echo Build and run $@: && cd union && admbre.bat union && union.exe
	@echo Build and run $@: && cd union && admbres.bat union && union.exe
