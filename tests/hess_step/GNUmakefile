TARGET=catage

default: $(TARGET)
	$(MAKE) run2

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run2:
ifeq ($(CMDSHELL),cmd)
	$(TARGET) -nox
	$(TARGET) -hess_step 10 -hess_step_tol 1e-18
else
	./$(TARGET) -nox
	./$(TARGET) -hess_step 10 -hess_step_tol 1e-18
endif

get-outputs:
ifeq ($(CMDSHELL),cmd)
	type catage.cor
	type catage.eva
	type catage.par
	type catage.std
	type sims
else
	cat catage.cor
	cat catage.eva
	cat catage.par
	cat catage.std
	cat sims
endif
