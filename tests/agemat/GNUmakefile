TARGET=agemat
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: _run

agemat.tpl: agemat.dat
	cp rforge-nwfscassmt/pkg/nwfscAgeingError/inst/executables/AGEMAT.TPL agemat.tpl

agemat.dat: rforge-nwfscassmt
	cp rforge-nwfscassmt/pkg/nwfscAgeingError/inst/doc/agemat.dat .

rforge-nwfscassmt:
	git clone --depth 1 https://github.com/rforge/nwfscassmt rforge-nwfscassmt

get-outputs: _get-outputs
ifeq ($(CMDSHELL),cmd)
	@if exist Echo.Out type Echo.Out
else
	@[ -f Echo.Out ] && cat Echo.Out
endif

clean: _clean
ifeq ($(CMDSHELL),cmd)
	@if exist rforge-nwfscassmt rmdir /s /q rforge-nwfscassmt
	@if exist $(TARGET).tpl del /Q $(TARGET).tpl 2>nul
	@if exist $(TARGET).dat del /Q $(TARGET).dat 2>nul
	@if exist Echo.Out del /Q Echo.Out 2>nul
else
	@rm -rf rforge-nwfscassmt
	@rm -vf agemat.dat
	@rm -vf agemat.tpl
	@rm -vf Echo.Out
endif
