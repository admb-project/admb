TARGET=catage
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: catage.dat catage.tpl
	$(MAKE) $(TARGET)
ifeq ($(CMDSHELL),cmd)
	$(TARGET) -nox
	@echo "\n===\n"
	$(TARGET) -hess_step 10 -hess_step_tol 1e-18
else
	./$(TARGET) -nox
	@echo "\n===\n"
	./$(TARGET) -hess_step 10 -hess_step_tol 1e-18
endif

catage.dat:
ifeq ($(CMDSHELL),cmd)
	copy ..\..\examples\admb\catage\catage.dat
else
	cp ../../examples/admb/catage/catage.dat .
endif

catage.tpl:
ifeq ($(CMDSHELL),cmd)
	copy ..\..\examples\admb\catage\catage.tpl
else
	cp ../../examples/admb/catage/catage.tpl .
endif

get-outputs: _get-outputs
ifeq ($(CMDSHELL),cmd)
	@if exist outputs type outputs
else
	@if [ -e outputs ]; then cat outputs; fi
endif

clean: _clean
ifeq ($(CMDSHELL),cmd)
	@if exist $(TARGET).b02 del /Q $(TARGET).b02 2>nul
	@if exist $(TARGET).dat del /Q $(TARGET).dat 2>nul
	@if exist $(TARGET).p02 del /Q $(TARGET).p02 2>nul
	@if exist $(TARGET).r02 del /Q $(TARGET).r02 2>nul
	@if exist $(TARGET).tpl del /Q $(TARGET).tpl 2>nul
else
	@rm -vf $(TARGET).b02
	@rm -vf $(TARGET).dat
	@rm -vf $(TARGET).p02
	@rm -vf $(TARGET).r02
	@rm -vf $(TARGET).tpl
endif
