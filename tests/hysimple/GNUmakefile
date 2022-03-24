TARGET=hysimple
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: $(TARGET)
ifeq ($(CMDSHELL),cmd)
	$(TARGET) -hybrid -mcmc 2000 -hyeps .3 -hynsteps 20
	$(TARGET) -mceval
else
	./$(TARGET) -hybrid -mcmc 2000 -hyeps .3 -hynsteps 20
	./$(TARGET) -mceval
endif

get-outputs: _get-outputs

clean: _clean
ifeq ($(CMDSHELL),cmd)
	if exist hybrid_seed del /Q hybrid_seed
else
	@rm -vf hybrid_seed
endif
