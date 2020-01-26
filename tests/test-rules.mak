ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifeq ($(findstring bash.exe,$(shell where bash.exe 2>&1 | findstr bash.exe)),bash.exe)
      EXT=.sh
    else
      CMDSHELL=cmd
    endif
  endif
endif

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb $(TARGET)
else
	../../admb$(EXT) $(TARGET)
endif

run:
ifeq ($(CMDSHELL),cmd)
	$(TARGET)
else
	./$(TARGET)
endif

clean:
ifeq ($(CMDSHELL),cmd)
	@del $(TARGET) 2>nul
	@del variance 2>nul
	@del fmin.log 2>nul
	@del $(TARGET).eva 2>nul
	@del $(TARGET).exe 2>nul
	@del $(TARGET).htp 2>nul
	@del $(TARGET).bar 2>nul
	@del $(TARGET).bgs 2>nul
	@del $(TARGET).cor 2>nul
	@del $(TARGET).cpp 2>nul
	@del $(TARGET).log 2>nul
	@del $(TARGET).o 2>nul
	@del $(TARGET).obj 2>nul
	@del $(TARGET).par 2>nul
	@del $(TARGET).std 2>nul
	@del tests_$(TARGET).o 2>nul
	@del tests_$(TARGET) 2>nul
	@del eigv.rpt 2>nul
	@del admodel.cov 2>nul
	@del admodel.dep 2>nul
	@del admodel.hes 2>nul
	@del $(TARGET).luu 2>nul
	@del $(TARGET).rhes 2>nul
	@del hesscheck 2>nul
	@del hessian.bin 2>nul
else
	@rm -vf $(TARGET)
	@rm -vf admodel.*
	@rm -vf variance
	@rm -vf hessian.bin
	@rm -vf hesscheck
	@rm -vf fmin.log
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
	@rm -vf eigv.rpt
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf $(TARGET).luu
	@rm -vf $(TARGET).rhes
	@rm -vf hesscheck
	@rm -vf hessian.bin
endif
