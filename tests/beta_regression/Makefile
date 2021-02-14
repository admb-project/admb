TARGET=beta_regression
OVERRIDE=all

!include <..\test-rules.nmake>

run: $(TARGET)
	$(TARGET) -mno 1000
	$(TARGET) -mno 1000 -mcsave 20 -ainp $(TARGET).par -phase 10 -nohess -mcmc2 6000 -hybrid
	$(TARGET) -mno 1000  -mceval -ainp $(TARGET).par -phase 10 -nohess 

get-outputs: _get-outputs
	@if exist b1 type b1 2>nul
	@if exist b2 type b2 2>nul
	@if exist hesscheck type hesscheck 2>nul
	@if exist hybrid_seed type hybrid_seed 2>nul
	@if exist s1 type s1 2>nul
	@if exist s2 type s2 2>nul
	@if exist data type data 2>nul

clean: _clean
	@if exist b1 del /Q b1 2>nul
	@if exist b2 del /Q b2 2>nul
	@if exist hesscheck del /Q hesscheck 2>nul
	@if exist hybrid_seed del /Q hybrid_seed 2>nul
	@if exist s1 del /Q s1 2>nul
	@if exist s2 del /Q s2 2>nul
	@if exist data del /Q data 2>nul
