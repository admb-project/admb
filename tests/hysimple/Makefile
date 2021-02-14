TARGET=hysimple
OVERRIDE=all

!include <..\test-rules.nmake>

run: $(TARGET)
	$(TARGET) -hybrid -mcmc 2000 -hyeps .3 -hynsteps 20
	$(TARGET) -mceval

get-outputs: _get-outputs

clean: _clean
	@if exist hybrid_seed del /Q hybrid_seed
