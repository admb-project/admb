.PHONY: tpl
TARGET=test_param_init_bounded_number_matrix

all: clean run tpl

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(TARGET).o
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; CXXFLAGS=-I/usr/local/gtest-1.5.0/include LDFLAGS="-static -L/usr/local/gtest-1.5.0/lib -lgtest -lpthread " adlink -s ${OPTIONS} $(TARGET)

$(TARGET).o: $(TARGET).cpp
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; CXXFLAGS=-I/usr/local/gtest-1.5.0/include LDFLAGS="-static -L/usr/local/gtest-1.5.0/lib -lgtest -lpthread " adcomp -s ${OPTIONS} $(TARGET) 

tpl:
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; CXXFLAGS=-I/usr/local/gtest-1.5.0/include LDFLAGS="-static -L/usr/local/gtest-1.5.0/lib -lgtest -lpthread " admb -s test
	touch test.dat
	./test

clean:
	@rm -vf  $(TARGET).o
	@rm -vf  $(TARGET)
	@rm -vf test
	@rm -vf test.bar
	@rm -vf test.dat
	@rm -vf variance
	@rm -vf test.eva
	@rm -vf test.log
	@rm -vf test.par
	@rm -vf test.cpp
	@rm -vf test.cor
	@rm -vf test.std
	@rm -vf test.dat
	@rm -vf admodel.hes
	@rm -vf fmin.log
	@rm -vf test.htp
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf eigv.rpt
