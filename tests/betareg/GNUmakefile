TARGET=betareg
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: $(TARGET)
ifeq ($(CMDSHELL),cmd)
# get the mcmc info  note -mcmc2 and not -mcmc  thois means that RE's are part of the mcmc
	$(TARGET) -mcmc2 300 -hybrid -mno 1000  -shess 
	$(TARGET) -nohess -phase 10 -binp betareg.bar -mcmc2 2000 -hybrid -mno 1000 -shess 
# test the restart
	$(TARGET) -nohess -phase 10 -binp betareg.bar -mcmc2 2000 -hybrid -mno 1000 -mcr -shess 
# do the mceval part
	$(TARGET) -nohess -phase 10 -binp betareg.bar -mcmc2 25 -hybrid -mno 1000 -mceval -shess 
else
# get the mcmc info  note -mcmc2 and not -mcmc  thois means that RE's are part of the mcmc
	./$(TARGET) -mcmc2 300 -hybrid -mno 1000  -shess 
	./$(TARGET) -nohess -phase 10 -binp betareg.bar -mcmc2 2000 -hybrid -mno 1000 -shess 
# test the restart
	./$(TARGET) -nohess -phase 10 -binp betareg.bar -mcmc2 2000 -hybrid -mno 1000 -mcr -shess 
# do the mceval part
	./$(TARGET) -nohess -phase 10 -binp betareg.bar -mcmc2 25 -hybrid -mno 1000 -mceval -shess 
endif

get-outputs: _get-outputs
ifeq ($(CMDSHELL),cmd)
	@if exist a type a
	@if exist b1 type b1
	@if exist b2 type b2
	@if exist data type data 
	@if exist hesscheck type hesscheck
	@if exist s1 type s1
	@if exist s2 type s2
	@if exist $(TARGET).b02 type $(TARGET).b02
	@if exist $(TARGET).p02 type $(TARGET).p02
else
	@if [ -e a ]; then cat a; fi
	@if [ -e b1 ]; then cat b1; fi
	@if [ -e b2 ]; then cat b2; fi
	@if [ -e data ]; then cat data; fi
	@if [ -e hesscheck ]; then cat hesscheck; fi
	@if [ -e s1 ]; then cat s1; fi
	@if [ -e s2 ]; then cat s2; fi
	@if [ -e $(TARGET).b02 ]; then cat $(TARGET).b02; fi
	@if [ -e $(TARGET).p02 ]; then cat $(TARGET).p02; fi
endif

clean: _clean
ifeq ($(CMDSHELL),cmd)
	@if exist a del /Q a 2>nul
	@if exist b1 del /Q b1 2>nul
	@if exist b2 del /Q b2 2>nul
	@if exist data  del /Q data 2>nul
	@if exist hesscheck del /Q hesscheck 2>nul
	@if exist s1 del /Q s1 2>nul
	@if exist s2 del /Q s2 2>nul
	@if exist $(TARGET).b02 del /Q $(TARGET).b02 2>nul
	@if exist $(TARGET).p02 del /Q $(TARGET).p02 2>nul
	@if exist $(TARGET).r02 del /Q $(TARGET).r02 2>nul
	@if exist $(TARGET).shess del /Q $(TARGET).shess 2>nul
	@if exist hybrid_seed del /Q hybrid_seed  2>nul
else
	@rm -vf a
	@rm -vf b1
	@rm -vf b2
	@rm -vf data
	@rm -vf hesscheck
	@rm -vf s1
	@rm -vf s2
	@rm -vf $(TARGET).b02
	@rm -vf $(TARGET).p02
	@rm -vf $(TARGET).r02
	@rm -vf $(TARGET).shess
	@rm -vf hybrid_seed
endif
