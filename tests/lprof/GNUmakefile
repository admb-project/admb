TARGET=simple
OVERRIDE=all

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

run: $(TARGET) simple.dat
ifeq ($(CMDSHELL),cmd)
	simple
	move simple.par simple.par.save
	simple -lprof
	move simple.par simple.par.lprof
	simple -lprof -ainp simple.par.save
else
	./simple
	mv simple.par simple.par.save
	./simple -lprof
	mv simple.par simple.par.lprof
	./simple -lprof -ainp simple.par.save
endif

get-outputs: _get-outputs
ifeq ($(CMDSHELL),cmd)
	@if exist dgs2 type dgs2
	@if exist diags type diags
	@if exist est_a.plt type est_a.plt
	@if exist est_b.plt type est_b.plt
	@if exist $(TARGET).par.save type simple.par.save
	@if exist $(TARGET).par.lprof type simple.par.lprof
else
	@if [ -e dgs2 ]; then cat dgs2; fi
	@if [ -e diags ]; then cat diags; fi
	@if [ -e est_a.plt ]; then cat est_a.plt; fi
	@if [ -e est_b.plt ]; then cat est_b.plt; fi
	@if [ -e $(TARGET).par.save ]; then cat $(TARGET).par.save; fi
	@if [ -e $(TARGET).par.lprof ]; then cat $(TARGET).par.lprof; fi
endif

clean: _clean
ifeq ($(CMDSHELL),cmd)
	if exist dgs2 del /Q dgs2
	if exist diags del /Q diags
	if exist est_a.plt del /Q est_a.plt
	if exist est_b.plt del /Q est_b.plt
	if exist $(TARGET).par.save del /Q simple.par.save
	if exist $(TARGET).par.lprof del /Q simple.par.lprof
	if exist $(TARGET).dat del /Q simple.dat
else
	rm -vf dgs2
	rm -vf diags
	rm -vf est_a.plt
	rm -vf est_b.plt
	rm -vf simple.par.save
	rm -vf simple.par.lprof
	rm -vf simple.dat
endif
