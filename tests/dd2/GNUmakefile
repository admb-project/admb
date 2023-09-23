TARGET=dd2
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: $(TARGET)
ifeq ($(CMDSHELL),cmd)
	$(TARGET) -imaxfn 0 -noinit > outputs
else
	./$(TARGET) -imaxfn 0 -noinit &> outputs
endif

get-outputs: _get-outputs
ifeq ($(CMDSHELL),cmd)
	@if exist outputs type outputs
else
	@if [ -e outputs ]; then cat outputs; fi
endif

clean: _clean
ifeq ($(CMDSHELL),cmd)
	@if exist f1b2list13 del /Q f1b2list13 2>nul
	@if exist outputs del /Q outputs 2>nul
	@if exist f1b2list1 del /Q f1b2list1 2>nul
	@if exist f1b2list12 del /Q f1b2list12 2>nul
	@if exist nf1b2list1 del /Q nf1b2list1 2>nul
	@if exist nf1b2list12 del /Q nf1b2list12 2>nul
	@if exist nf1b2list13 del /Q nf1b2list13 2>nul
	@if exist cmpdiff.tmp del /Q cmpdiff.tmp 2>nul
	@if exist cmpdiff1.tmp del /Q cmpdiff.tmp 2>nul
	@if exist gradfil1.tmp del /Q gradfil1.tmp 2>nul
	@if exist gradfil2.tmp del /Q gradfil2.tmp 2>nul
	@if exist gradfil12.tmp del /Q gradfil1.tmp 2>nul
	@if exist gradfil22.tmp del /Q gradfil2.tmp 2>nul
	@if exist varssave.tmp del /Q varssave.tmp 2>nul
	@if exist varssave2.tmp del /Q varssave.tmp 2>nul
else
	@rm -vf f1b2list13
	@rm -vf outputs
	@rm -vf f1b2list1
	@rm -vf f1b2list12
	@rm -vf f1b2list13
	@rm -vf nf1b2list1
	@rm -vf nf1b2list12
	@rm -vf nf1b2list13
	@rm -vf cmpdiff.tmp
	@rm -vf gradfil1.tmp
	@rm -vf gradfil2.tmp
	@rm -vf varssave.tmp
	@rm -vf cmpdiff1.tmp
	@rm -vf gradfil12.tmp
	@rm -vf gradfil22.tmp
	@rm -vf varssave2.tmp
endif
