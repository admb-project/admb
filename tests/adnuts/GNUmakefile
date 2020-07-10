TARGET=adnuts

default: $(TARGET)
	$(MAKE) run2

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run2:
ifeq ($(CMDSHELL),cmd)
	$(TARGET) -nuts -hbf -mcmc 2000
	$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass -noest
	$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass_dense -noest -verbose_adapt_mass -refresh -1
	$(TARGET) -rwm -mcmc 2000 -mcsave 1 -noest
else
	./$(TARGET) -nuts -hbf -mcmc 2000
	./$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass -noest
	./$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass_dense -noest -verbose_adapt_mass -refresh -1
	./$(TARGET) -rwm -mcmc 2000 -mcsave 1 -noest
endif
