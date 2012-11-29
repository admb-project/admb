.PHONY: tpl
TARGET=test_atan2
TPL_TARGET=atan2

all: clean run

run: $(TPL_TARGET) $(TARGET)
	./$(TPL_TARGET) -nohess
	./$(TARGET)

$(TPL_TARGET): $(TPL_TARGET).tpl
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; admb -s $(TPL_TARGET)

$(TARGET): $(TARGET).o
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; CXXFLAGS=-I/usr/local/gtest-1.5.0/include LDFLAGS="-static -L/usr/local/gtest-1.5.0/lib -lgtest -lpthread " adlink -s ${OPTIONS} $(TARGET)

$(TARGET).o: $(TARGET).cpp
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; CXXFLAGS=-I/usr/local/gtest-1.5.0/include LDFLAGS="-static -L/usr/local/gtest-1.5.0/lib -lgtest -lpthread " adcomp -s ${OPTIONS} $(TARGET) 

clean:
	@rm -vf  $(TARGET).o
	@rm -vf  $(TARGET)
	@rm -vf  $(TPL_TARGET)
	@rm -vf atan2.eva
	@rm -vf admodel.hes
	@rm -vf atan2.log
	@rm -vf atan2.par
	@rm -vf atan2.cpp
	@rm -vf variance
	@rm -vf atan2.rep
	@rm -vf eigv.rpt
	@rm -vf atan2.htp
	@rm -vf atan2.bar
	@rm -vf fmin.log
	@rm -vf admodel.dep
