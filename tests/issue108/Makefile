TARGET=vonmises
OVERRIDE=all

!include <..\test-rules.nmake>

run: $(TARGET) $(TARGET).dat
	issue108

$(TARGET).dat: dat
	dat > issue108.dat

dat: dat.cpp
	$(CXX) -o dat dat.cpp

get-outputs: _get-output
	@if exist $(TARGET).dat type $(TARGET).dat

clean: _clean
	@if exist dat del /Q dat 2>nul
	@if exist $(TARGET).dat del /Q $(TARGET).dat 2>nul
