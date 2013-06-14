TARGET=test_adstring
ADMB_HOME=${PWD}/../../build/admb-macos10.6.4-xcode3.2.2-64bit/dist

all: clean run

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(TARGET).o
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; CXXFLAGS=-I/usr/local/gtest-1.5.0/include LDFLAGS="-L/usr/local/gtest-1.5.0/lib -lgtest" adlink ${OPTIONS} $(TARGET)

$(TARGET).o: $(TARGET).cpp
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; CXXFLAGS=-I/usr/local/gtest-1.5.0/include LDFLAGS="-L/usr/local/gtest-1.5.0/lib -lgtest" adcomp ${OPTIONS} $(TARGET) 

clean:
	@rm -vf  $(TARGET).o
	@rm -vf  $(TARGET)
