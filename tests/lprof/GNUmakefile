TARGET=simple

default: simple.dat
	$(MAKE) all
	$(MAKE) run2


ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

simple.dat:
ifeq ($(CMDSHELL),cmd)
	copy ..\..\examples\admb\simple\simple.dat
else
	cp ../../examples/admb/simple/simple.dat .
endif

run2:
ifeq ($(CMDSHELL),cmd)
	simple
	move simple.par simple.par.save
	simple -lprof
	move simple.par simple.par.lprof
	simple -lprof -ainp simple.par.save
	type simple.par simple.par.save simple.par.lprof
else
	./simple
	mv simple.par simple.par.save
	./simple -lprof
	mv simple.par simple.par.lprof
	./simple -lprof -ainp simple.par.save
	cat simple.par simple.par.save simple.par.lprof
endif

get-outputs:
ifeq ($(CMDSHELL),cmd)
	type dgs2
	type diags
	type est_a.plt
	type est_b.plt
	type simple.cor
	type simple.dat
	type simple.eva
	type simple.log
	type simple.par
	type simple.prf
	type simple.std
else
	cat dgs2
	cat diags
	cat est_a.plt
	cat est_b.plt
	cat simple.cor
	cat simple.dat
	cat simple.eva
	cat simple.log
	cat simple.par
	cat simple.prf
	cat simple.std
endif
