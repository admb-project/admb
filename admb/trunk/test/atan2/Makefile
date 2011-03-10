.PHONY: tpl
TARGET=test_atan2

all: clean run

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(TARGET).o
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; CXXFLAGS=-I/usr/local/gtest-1.5.0/include LDFLAGS="-static -L/usr/local/gtest-1.5.0/lib -lgtest -lpthread " adlink -s ${OPTIONS} $(TARGET)

$(TARGET).o: $(TARGET).cpp
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; CXXFLAGS=-I/usr/local/gtest-1.5.0/include LDFLAGS="-static -L/usr/local/gtest-1.5.0/lib -lgtest -lpthread " adcomp -s ${OPTIONS} $(TARGET) 

clean:
	@rm -vf  $(TARGET).o
	@rm -vf  $(TARGET)
