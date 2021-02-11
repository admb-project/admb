TARGET=dualaveraging

!include <..\test-rules.nmake>

run: $(TARGET)
	$(TARGET) -mno 1000
	$(TARGET) -mno 1000 -mcsave 20 -ainp $(TARGET).par -phase 10 -nohess -mcmc2 6000 -hybrid
	$(TARGET) -mno 1000  -mceval -ainp $(TARGET).par -phase 10 -nohess 

get-outputs: _get-outputs
	@if exist b1 type b1
	@if exist b2 type b2
	@if exist hesscheck type hesscheck
	@if exist hybrid_seed type hybrid_seed
	@if exist s1 type s1
	@if exist s2 type s2

clean: _clean
	@if exist b1 del /Q b1 
	@if exist b2 del /Q b2
	@if exist data del /Q data
	@if exist hybmcmc.obj del /Q hybmcmc.obj
	@if exist hybrid_seed del /Q hybrid_seed
	@if exist s1 del /Q s1 
	@if exist s2 del /Q s2
