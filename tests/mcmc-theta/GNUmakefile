TARGET=theta

default: $(TARGET) 
	$(MAKE) run2

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run2:
ifeq ($(SHELL),cmd)
	$(TARGET) -nonit -mcmc 1000 -mcsave 10
else
	./$(TARGET) -nonit -mcmc 1000 -mcsave 10
endif
