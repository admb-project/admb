.PHONY: all ham4 ham5 catage finance vonb vonbr n2mvol simple union

all: simple
	@echo
	@echo Completed ADMB example and runs
	@echo Successful
	@echo

verify: ham4 ham5 catage finance vonb vonbr n2mvol simple union
noverify: chem-eng forest pella-t truncreg

ham4:
	cd buscycle && makeadm.bat ham4 && ham4.exe
	cd buscycle && makeadms.bat ham4 && ham4.exe

ham5:
	cd buscycle && makeadm.bat ham5 && ham5.exe
	cd buscycle && makeadms.bat ham5 && ham5.exe

catage:
	cd catage && makeadm.bat catage && catage.exe
	cd catage && makeadms.bat catage && catage.exe

chem-eng:
	cd chem-eng && makeadm.bat chem-eng && chem-eng.exe
	cd chem-eng && makeadms.bat chem-eng && chem-eng.exe

finance:
	cd finance && makeadm.bat finance && finance.exe
	cd finance && makeadms.bat finance && finance.exe

forest:
	cd forest && makeadm.bat forest && forest.exe
	cd forest && makeadms.bat forest && forest.exe

pella-t:
	cd pella-t && makeadm.bat pella-t && pella-t.exe
	cd pella-t && makeadms.bat pella-t && pella-t.exe

vonb:
	cd robreg && makeadm.bat vonb && vonb.exe
	cd robreg && makeadms.bat vonb && vonb.exe

vonbr:
	cd robreg && makeadm.bat vonbr && vonbr.exe
	cd robreg && makeadms.bat vonbr && vonbr.exe

simple:
	cd simple && makeadm.bat simple && simple.exe
	cd simple && makeadms.bat simple && simple.exe

truncreg:
	cd truncreg && makeadm.bat truncreg && runtrunc.bat && fruntrunc
	cd truncreg && makeadms.bat truncreg && runtrunc.bat && fruntrunc

n2mvol:
	cd vol && makeadm.bat n2mvol && n2mvol.exe
	cd vol && makeadms.bat n2mvol && n2mvol.exe

union:
	cd union && makeadmre.bat union && union.exe
	cd union && makeadmres.bat union && union.exe
