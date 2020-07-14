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
	$(TARGET) -nuts -hbf -mcmc 2000 -mcseed 12 -hyeps 1 -refresh -1 
	$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass -noest -mcseed 141 -refresh -1
	$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass_dense -noest -verbose_adapt_mass -refresh -1 -mcseed 532
	$(TARGET) -rwm -mcmc 2000 -mcsave 1 -noest -mcseed 123 -refresh -1
	$(TARGET) -hmc -mcmc 2000 -hynstep 1 -noest -mcseed 123 -refresh -1
	$(TARGET) -hmc -mcmc 2000 -hynstep 1 -hyeps 1-noest -mcseed 123 -refresh -1

else
	./$(TARGET) -nuts -hbf -mcmc 2000 -mcseed 12 -hyeps 1 -refresh -1 
	./$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass -noest -mcseed 141 -refresh -1
	./$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass_dense -noest -verbose_adapt_mass -refresh -1 -mcseed 532
	./$(TARGET) -rwm -mcmc 2000 -mcsave 1 -noest -mcseed 123 -refresh -1
	./$(TARGET) -hmc -mcmc 2000 -hynstep 1 -noest -mcseed 123 -refresh -1
	./$(TARGET) -hmc -mcmc 2000 -hynstep 1 -hyeps 1 -noest -mcseed 123 -refresh -1
endif
