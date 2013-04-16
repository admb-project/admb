ifndef ADMB_HOME
ADMB_HOME=../../build/dist
endif

all: $(addprefix $(PREFIX_OBJ), contrib.obj)
	cp contrib.h $(ADMB_HOME)/contrib/include

test:
	ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" admb simple.tpl
	./simple

clean:
	@rm -f sample.obj
	@rm -f simple.std
	@rm -f simple.htp
	@rm -f admodel.hes
	@rm -f variance
	@rm -f simple
	@rm -f admodel.cov
	@rm -f simple.bar
	@rm -f eigv.rpt
	@rm -f simple.eva
	@rm -f fmin.log
	@rm -f simple.log
	@rm -f simple.cpp
	@rm -f simple.par
	@rm -f simple.cor
	@rm -f admodel.dep

$(PREFIX_OBJ)%.obj: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<
