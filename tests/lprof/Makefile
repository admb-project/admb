TARGET=simple
OVERRIDE=all

!include <..\test-rules.nmake>

simple.dat:
	copy ..\..\examples\admb\simple\simple.dat

run: $(TARGET) simple.dat
	simple
	move simple.par simple.par.save
	simple -lprof
	move simple.par simple.par.lprof
	simple -lprof -ainp simple.par.save

get-outputs: _get-outputs
	if exist dgs2 type dgs2
	if exist diags type diags
	if exist est_a.plt type est_a.plt
	if exist est_b.plt type est_b.plt
	if exist $(TARGET).par.save type simple.par.save
	if exist $(TARGET).par.lprof type simple.par.lprof
	if exist $(TARGET).dat type simple.dat

clean:
	if exist dgs2 del /Q dgs2
	if exist diags del /Q diags
	if exist est_a.plt del /Q est_a.plt
	if exist est_b.plt del /Q est_b.plt
	if exist $(TARGET).par.save del /Q simple.par.save
	if exist $(TARGET).par.lprof del /Q simple.par.lprof
	if exist $(TARGET).dat del /Q simple.dat
