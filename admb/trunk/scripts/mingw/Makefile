.PHONY: all ham4 ham5 catage finance vonb vonbr n2mvol simple

verify: ham4 ham5 catage finance vonb vonbr n2mvol simple
	@echo -------------------------------
	@echo Completed ADMB example and runs
	@echo Successful
	@echo -------------------------------

all: simple
noverify: chem-eng forest pella-t truncreg union

ham4:
	@echo Build and run $@: && cd buscycle && makeadm.bat ham4 && ham4.exe
	@echo Build and run $@: && cd buscycle && makeadms.bat ham4 && ham4.exe

ham5:
	@echo Build and run $@: && cd buscycle && makeadm.bat ham5 && ham5.exe
	@echo Build and run $@: && cd buscycle && makeadms.bat ham5 && ham5.exe

catage:
	@echo Build and run $@: && cd catage && makeadm.bat catage && catage.exe
	@echo Build and run $@: && cd catage && makeadms.bat catage && catage.exe

chem-eng:
	@echo Build and run $@: && cd chem-eng && makeadm.bat chem-eng && chem-eng.exe
	@echo Build and run $@: && cd chem-eng && makeadms.bat chem-eng && chem-eng.exe

finance:
	@echo Build and run $@: && cd finance && makeadm.bat finance && finance.exe
	@echo Build and run $@: && cd finance && makeadms.bat finance && finance.exe

forest:
	@echo Build and run $@: && cd forest && makeadm.bat forest && forest.exe
	@echo Build and run $@: && cd forest && makeadms.bat forest && forest.exe

pella-t:
	@echo Build and run $@: && cd pella-t && makeadm.bat pella-t && pella-t.exe
	@echo Build and run $@: && cd pella-t && makeadms.bat pella-t && pella-t.exe

vonb:
	@echo Build and run $@: && cd robreg && makeadm.bat vonb && vonb.exe
	@echo Build and run $@: && cd robreg && makeadms.bat vonb && vonb.exe

vonbr:
	@echo Build and run $@: && cd robreg && makeadm.bat vonbr && vonbr.exe
	@echo Build and run $@: && cd robreg && makeadms.bat vonbr && vonbr.exe

simple:
	@echo Build and run $@: && cd simple && makeadm.bat simple && simple.exe
	@echo Build and run $@: && cd simple && makeadms.bat simple && simple.exe

truncreg:
	@echo Build and run $@: && cd truncreg && makeadm.bat truncreg && runtrunc.bat && fruntrunc
	@echo Build and run $@: && cd truncreg && makeadms.bat truncreg && runtrunc.bat && fruntrunc

n2mvol:
	@echo Build and run $@: && cd vol && makeadm.bat n2mvol && n2mvol.exe
	@echo Build and run $@: && cd vol && makeadms.bat n2mvol && n2mvol.exe

union:
	@echo Build and run $@: && cd union && makeadmre.bat union && union.exe
	@echo Build and run $@: && cd union && makeadmres.bat union && union.exe
