TARGET=priors
TPL_TARGET=rat
TPL_TARGETRE=ratre

all: clean run runre

run: $(TPL_TARGET)
	./$(TPL_TARGET) -nohess

runre: $(TPL_TARGETRE)
	./$(TPL_TARGETRE) -nohess

$(TPL_TARGET): $(TPL_TARGET).tpl
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; CXXFLAGS=${CXXFLAGS} admb -s $(TPL_TARGET)

$(TPL_TARGETRE): $(TPL_TARGETRE).tpl
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; CXXFLAGS=${CXXFLAGS} admb -s -r $(TPL_TARGETRE)

clean:
	@rm -f eigv.rpt
	@rm -f fmin.log
	@rm -f rat
	@rm -f rat.b01
	@rm -f rat.b02
	@rm -f rat.bar
	@rm -f rat.cpp
	@rm -f rat.htp
	@rm -f rat.log
	@rm -f rat.o
	@rm -f rat.p01
	@rm -f rat.p02
	@rm -f rat.par
	@rm -f rat.r01
	@rm -f rat.r02
	@rm -f rat.rep
	@rm -f ratre
	@rm -f ratre.b01
	@rm -f ratre.b02
	@rm -f ratre.bar
	@rm -f ratre.cpp
	@rm -f ratre.htp
	@rm -f ratre.log
	@rm -f ratre.o
	@rm -f ratre.p01
	@rm -f ratre.p02
	@rm -f ratre.par
	@rm -f ratre.r01
	@rm -f ratre.r02
	@rm -f ratre.rep
	@rm -f variance
