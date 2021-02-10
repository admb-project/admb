TARGET=agemat
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: _run

agemat.tpl: agemat.dat
ifeq ($(CMDSHELL),cmd)
	copy rforge-nwfscassmt\pkg\nwfscAgeingError\inst\executables\AGEMAT.TPL agemat.tpl
else
	cp rforge-nwfscassmt/pkg/nwfscAgeingError/inst/executables/AGEMAT.TPL agemat.tpl
endif

agemat.dat: rforge-nwfscassmt
ifeq ($(CMDSHELL),cmd)
	copy rforge-nwfscassmt\pkg\nwfscAgeingError\inst\doc\agemat.dat
else
	cp rforge-nwfscassmt/pkg/nwfscAgeingError/inst/doc/agemat.dat .
endif

rforge-nwfscassmt:
	git clone --depth 1 https://github.com/rforge/nwfscassmt rforge-nwfscassmt

get-outputs: _get-outputs
ifeq ($(CMDSHELL),cmd)
	@if exist Echo.Out type Echo.Out
else
	@if [ -e Echo.Out ]; then  && cat Echo.Out; fi
endif

clean: _clean
ifeq ($(CMDSHELL),cmd)
	@if exist $(TARGET).tpl del /Q $(TARGET).tpl 2>nul
	@if exist $(TARGET).dat del /Q $(TARGET).dat 2>nul
	@if exist Echo.Out del /Q Echo.Out 2>nul
else
	@rm -vf agemat.dat
	@rm -vf agemat.tpl
	@rm -vf Echo.Out
endif

total-clean:
ifeq ($(CMDSHELL),cmd)
	@if exist rforge-nwfscassmt rmdir /s /q rforge-nwfscassmt
else
	@rm -rf rforge-nwfscassmt
endif
