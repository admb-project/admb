TARGET=gmrf
OVERRIDE=all

!include <..\test-rules.nmake>

run: $(TARGET)
 	$(TARGET) -est -ilmn 5 -ind gmrf100.dat -shess -ndi 10000000 -gbs 500000000 -noinit
	$(TARGET) -est -ilmn 5 -ind gmrf200.dat -shess -ndi 10000000 -gbs 1500000000 -noinit -nl1 1000000

get-outputs: _get-outputs
	@if exist outputs type outputs

clean: _clean
	@if exist f1b2list1 del /Q f1b2list1 2>nul
	@if exist f1b2list12 del /Q f1b2list12 2>nul
	@if exist nf1b2list1 del /Q nf1b2list1 2>nul
	@if exist nf1b2list12 del /Q nf1b2list12 2>nul
	@if exist nf1b2list13 del /Q nf1b2list13 2>nul
