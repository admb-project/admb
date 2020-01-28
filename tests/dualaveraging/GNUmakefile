TARGET=dualaveraging
SRCS=hybmcmc.cpp

default: $(TARGET)
	$(MAKE) run3
	$(MAKE) run2
	$(MAKE) run1

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run1:
ifeq ($(SHELL),cmd)
	$(TARGET) -mno 1000  -mceval -ainp $(TARGET).par -phase 10 -nohess 
else
	./$(TARGET) -mno 1000  -mceval -ainp $(TARGET).par -phase 10 -nohess 
endif

run2:
ifeq ($(SHELL),cmd)
	$(TARGET) -mno 1000 -mcsave 20 -ainp $(TARGET).par -phase 10 -nohess -mcmc2 6000 -hybrid
else
	./$(TARGET) -mno 1000 -mcsave 20 -ainp $(TARGET).par -phase 10 -nohess -mcmc2 6000 -hybrid
endif

run3:
ifeq ($(SHELL),cmd)
	$(TARGET) -mno 1000
else
	./$(TARGET) -mno 1000
endif

get-outputs:
ifeq ($(CMDSHELL),cmd)
	type b1
	type b2
	type beta_regression.cor
	type beta_regression.eva
	type beta_regression.p01
	type beta_regression.par
	type beta_regression.rhes
	type beta_regression.std
	type hesscheck
	type hybrid_seed
	type s1
	type s2
else
	cat b1
	cat b2
	cat beta_regression.cor
	cat beta_regression.eva
	cat beta_regression.p01
	cat beta_regression.par
	cat beta_regression.rhes
	cat beta_regression.std
	cat hesscheck
	cat hybrid_seed
	cat s1
	cat s2
endif
