TARGET=simple_mcmc

default: $(TARGET)
	$(MAKE) run2

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run2:
ifeq ($(CMDSHELL),cmd)
	$(TARGET) -mcmc 1000 -mcsave 10
	$(TARGET) -mceval
else
	./$(TARGET) -mcmc 1000 -mcsave 10
	./$(TARGET) -mceval
endif

get-outputs:
ifeq ($(CMDSHELL),cmd)
	type simple_mcmc.cor
	type simple_mcmc.eva
	type simple_mcmc.par
	type simple_mcmc.std
	type sims
else
	cat simple_mcmc.cor
	cat simple_mcmc.eva
	cat simple_mcmc.par
	cat simple_mcmc.std
	cat sims
endif
