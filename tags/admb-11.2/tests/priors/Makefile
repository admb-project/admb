TARGET=priors
TPL_TARGET=rat
TPL_TARGETRE=ratre

all: clean run runre

run: $(TPL_TARGET)
	$(TPL_TARGET) -nohess

runre: $(TPL_TARGETRE)
	$(TPL_TARGETRE) -nohess

$(TPL_TARGET): $(TPL_TARGET).tpl
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; CXXFLAGS=${CXXFLAGS} admb -s $(TPL_TARGET)

$(TPL_TARGETRE): $(TPL_TARGETRE).tpl
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; CXXFLAGS=${CXXFLAGS} admb -s -r $(TPL_TARGETRE)

clean:
	@if exist eigv.rpt del /Q eigv.rpt
	@if exist fmin.log del /Q fmin.log
	@if exist rat del /Q rat
	@if exist rat.exe del /Q rat.exe
	@if exist rat.b01 del /Q rat.b01
	@if exist rat.b02 del /Q rat.b02
	@if exist rat.bar del /Q rat.bar
	@if exist rat.cpp del /Q rat.cpp
	@if exist rat.htp del /Q rat.htp
	@if exist rat.log del /Q rat.log
	@if exist rat.obj del /Q rat.obj
	@if exist rat.obj del /Q rat.obj
	@if exist rat.p01 del /Q rat.p01
	@if exist rat.p02 del /Q rat.p02
	@if exist rat.par del /Q rat.par
	@if exist rat.r01 del /Q rat.r01
	@if exist rat.r02 del /Q rat.r02
	@if exist rat.rep del /Q rat.rep
	@if exist ratre del /Q ratre
	@if exist ratre.exe del /Q ratre.exe
	@if exist ratre.b01 del /Q ratre.b01
	@if exist ratre.b02 del /Q ratre.b02
	@if exist ratre.bar del /Q ratre.bar
	@if exist ratre.cpp del /Q ratre.cpp
	@if exist ratre.htp del /Q ratre.htp
	@if exist ratre.log del /Q ratre.log
	@if exist ratre.o del /Q ratre.o
	@if exist ratre.p01 del /Q ratre.p01
	@if exist ratre.p02 del /Q ratre.p02
	@if exist ratre.par del /Q ratre.par
	@if exist ratre.r01 del /Q ratre.r01
	@if exist ratre.r02 del /Q ratre.r02
	@if exist ratre.rep del /Q ratre.rep
	@if exist variance del /Q variance
