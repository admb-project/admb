TARGET=catage
OVERRIDE=all

!include <..\test-rules.nmake>

run: catage.dat catage.tpl
	$(MAKE) $(TARGET)
	$(TARGET) -nox
	@echo "\n===\n"
	$(TARGET) -hess_step 10 -hess_step_tol 1e-18

catage.dat:
	copy ..\..\examples\admb\catage\catage.dat

catage.tpl:
	copy ..\..\examples\admb\catage\catage.tpl

get-outputs: _get-outputs
        @if exist outputs type outputs

clean: _clean
	@if exist $(TARGET).tpl del /Q $(TARGET).tpl 2>nul
        @if exist $(TARGET).b02 del /Q $(TARGET).b02 2>nul
        @if exist $(TARGET).dat del /Q $(TARGET).dat 2>nul
        @if exist $(TARGET).p02 del /Q $(TARGET).p02 2>nul
        @if exist $(TARGET).r02 del /Q $(TARGET).r02 2>nul
        @if exist $(TARGET).tpl del /Q $(TARGET).tpl 2>nul
