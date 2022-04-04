TARGET=dualaveraging
#SRCS=hybmcmc.cpp
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: $(TARGET)
ifeq ($(CMDSHELL),cmd)
	$(TARGET) -mno 1000
	$(TARGET) -mno 1000 -mcsave 20 -ainp $(TARGET).par -phase 10 -nohess -mcmc2 6000 -hybrid
	$(TARGET) -mno 1000  -mceval -ainp $(TARGET).par -phase 10 -nohess 
else
	./$(TARGET) -mno 1000
	./$(TARGET) -mno 1000 -mcsave 20 -ainp $(TARGET).par -phase 10 -nohess -mcmc2 6000 -hybrid
	./$(TARGET) -mno 1000  -mceval -ainp $(TARGET).par -phase 10 -nohess 
endif

get-outputs: _get-outputs
ifeq ($(CMDSHELL),cmd)
	@if exist b1 type b1
	@if exist b2 type b2
	@if exist hesscheck type hesscheck
	@if exist hybrid_seed type hybrid_seed
	@if exist s1 type s1
	@if exist s2 type s2
else
	@if [ -e b1 ]; then cat b1; fi
	@if [ -e b2 ]; then cat b2; fi
	@if [ -e hesscheck ]; then cat hesscheck; fi
	@if [ -e hybrid_seed ]; then cat hybrid_seed; fi
	@if [ -e s1 ]; then cat s1; fi
	@if [ -e s2 ]; then cat s2; fi
endif

clean: _clean
ifeq ($(CMDSHELL),cmd)
	@if exist b1 del /Q b1 
	@if exist b2 del /Q b2
	@if exist data del /Q data
	@if exist hybmcmc.obj del /Q hybmcmc.obj
	@if exist hybrid_seed del /Q hybrid_seed
	@if exist s1 del /Q s1 
	@if exist s2 del /Q s2
	@del /Q dualaveraging.b01
	@del /Q dualaveraging.r01
else
	@rm -vf b1
	@rm -vf b2
	@rm -vf data
	@rm -vf hybmcmc.obj
	@rm -vf hybrid_seed
	@rm -vf s1
	@rm -vf s2
	@rm -vf dualaveraging.b01
	@rm -vf dualaveraging.r01
endif
