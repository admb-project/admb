ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifeq ($(findstring sh.exe,$(shell where sh.exe 2>&1 | findstr sh.exe)),sh.exe)
      EXT=.sh
    else
      SHELL=cmd
      CMDSHELL=cmd
    endif
  endif
endif

all: clean
	$(MAKE) run

$(TARGET): $(TARGET).tpl
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb.cmd $(TARGET) $(SRCS)
else
	../../admb$(EXT) $(TARGET) $(SRCS)
endif

run: $(TARGET)
ifeq ($(CMDSHELL),cmd)
	$(TARGET)
else
	./$(TARGET)
endif

get-outputs:
ifeq ($(CMDSHELL),cmd)
	@if exist $(TARGET).std type $(TARGET).std
	@if exist $(TARGET).par type $(TARGET).par
	@if exist $(TARGET).cor type $(TARGET).cor
	@if exist $(TARGET).eva type $(TARGET).eva
else
	@[ -f $(TARGET).std ] && cat $(TARGET).std
	@[ -f $(TARGET).par ] && cat $(TARGET).par
	@[ -f $(TARGET).cor ] && cat $(TARGET).cor
	@[ -f $(TARGET).eva ] && cat $(TARGET).eva
endif

clean:
ifeq ($(CMDSHELL),cmd)
	@if exist $(TARGET) del $(TARGET) 2>nul
	@if exist variance del variance 2>nul
	@if exist fmin.log del fmin.log 2>nul
	@if exist $(TARGET).rep del $(TARGET).rep 2>nul
	@if exist $(TARGET).eva del $(TARGET).eva 2>nul
	@if exist $(TARGET).exe del $(TARGET).exe 2>nul
	@if exist $(TARGET).htp del $(TARGET).htp 2>nul
	@if exist $(TARGET).bar del $(TARGET).bar 2>nul
	@if exist $(TARGET).bgs del $(TARGET).bgs 2>nul
	@if exist $(TARGET)cor del $(TARGET).cor 2>nul
	@if exist $(TARGET).cpp del $(TARGET).cpp 2>nul
	@if exist $(TARGET).log del $(TARGET).log 2>nul
	@if exist $(TARGET).o del $(TARGET).o 2>nul
	@if exist $(TARGET).obj del $(TARGET).obj 2>nul
	@if exist $(TARGET).par del $(TARGET).par 2>nul
	@if exist $(TARGET).std del $(TARGET).std 2>nul
	@if exist tests_$(TARGET).o del tests_$(TARGET).o 2>nul
	@if exist tests_$(TARGET) del tests_$(TARGET) 2>nul
	@if exist eigv.rpt  del eigv.rpt 2>nul
	@if exist admodel.cov del admodel.cov 2>nul
	@if exist admodel.dep del admodel.dep 2>nul
	@if exist admodel.hes del admodel.hes 2>nul
	@if exist $(TARGET).luu del $(TARGET).luu 2>nul
	@if exist $(TARGET).rhes del $(TARGET).rhes 2>nul
	@if exist hesscheck del hesscheck 2>nul
	@if exist hessian.bin del hessian.bin 2>nul
else
	@rm -vf $(TARGET)
	@rm -vf admodel.*
	@rm -vf variance
	@rm -vf hessian.bin
	@rm -vf hesscheck
	@rm -vf fmin.log
	@rm -vf $(TARGET).rep
	@rm -vf $(TARGET).eva
	@rm -vf $(TARGET).htp
	@rm -vf $(TARGET).bar
	@rm -vf $(TARGET).bgs
	@rm -vf $(TARGET).cor
	@rm -vf $(TARGET).cpp
	@rm -vf $(TARGET).log
	@rm -vf $(TARGET).o
	@rm -vf $(TARGET).obj
	@rm -vf $(TARGET).par
	@rm -vf $(TARGET).std
	@rm -vf $(TARGET).luu
	@rm -vf $(TARGET).rhes
	@rm -vf $(TARGET).[bpr]01
	@rm -vf eigv.rpt
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf $(TARGET).luu
	@rm -vf $(TARGET).rhes
	@rm -vf hesscheck
	@rm -vf hessian.bin
endif
