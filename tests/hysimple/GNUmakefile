TARGET=hysimple

default: $(TARGET)
	$(MAKE) run2

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run2:
ifeq ($(CMDSHELL),cmd)
	$(TARGET) -hybrid -mcmc 2000 -hyeps .3 -hynsteps 20
	$(TARGET) -mceval
else
	./$(TARGET) -hybrid -mcmc 2000 -hyeps .3 -hynsteps 20
	./$(TARGET) -mceval
endif
