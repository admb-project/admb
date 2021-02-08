
TARGET=agemat
OVERRIDE=all

!include <..\test-rules.nmake>

run: _run

agemat.tpl:
	copy rforge-nwfscassmt\\pkg\\nwfscAgeingError\\inst\\executables\\AGEMAT.TPL agemat.tpl

agemat.dat: rforge-nwfscassmt
	copy rforge-nwfscassmt\\pkg\\nwfscAgeingError\\inst\\doc\\agemat.dat

rforge-nwfscassmt:
	git clone --depth 1 https://github.com/rforge/nwfscassmt rforge-nwfscassmt

get-outputs: _get-outputs
	@if exist Echo.Out type Echo.Out

clean: _clean
	@if exist rforge-nwfscassmt rmdir /s /q rforge-nwfscassmt
	@if exist $(TARGET).tpl del /Q $(TARGET).tpl 2>nul
	@if exist $(TARGET).dat del /Q $(TARGET).dat 2>nul
	@if exist Echo.Out del /Q Echo.Out 2>nul
