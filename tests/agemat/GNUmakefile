TARGET=agemat

default: $(TARGET).tpl
	$(MAKE) $(TARGET)
	$(MAKE) run2

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run2:
ifeq ($(CMDSHELL),cmd)
	agemat
else
	./agemat
endif

agemat.tpl: agemat.dat
	cp rforge-nwfscassmt/pkg/nwfscAgeingError/inst/executables/AGEMAT.TPL agemat.tpl

agemat.dat: rforge-nwfscassmt
	cp rforge-nwfscassmt/pkg/nwfscAgeingError/inst/doc/agemat.dat .

rforge-nwfscassmt:
	git clone --depth 1 https://github.com/rforge/nwfscassmt rforge-nwfscassmt

get-outputs:
ifeq ($(CMDSHELL),cmd)
	type agemat.bar
	type agemat.cor
	type agemat.eva
	type agemat.p01
	type agemat.par
	type agemat.r01
	type agemat.rep
	type agemat.std
	type Echo.Out
else
	cat agemat.bar
	cat agemat.cor
	cat agemat.eva
	cat agemat.p01
	cat agemat.par
	cat agemat.r01
	cat agemat.rep
	cat agemat.std
	cat Echo.Out
endif

total-clean: clean
ifeq ($(CMDSHELL),cmd)
	@if exist rforge-nwfscassmt rmdir /s /q rforge-nwfscassmt
	del agemat.dat
	del agemat.tpl
else
	rm -rf rforge-nwfscassmt
	rm -vf agemat.dat
	rm -vf agemat.tpl
endif
