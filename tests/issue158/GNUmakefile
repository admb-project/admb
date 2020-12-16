.PHONY: clean run

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

TARGET=simple

all: clean
	$(MAKE) run

$(TARGET):
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb$(EXT) -g $(TARGET)
else
	../../admb -g $(TARGET)
endif

run: $(TARGET)
	@printf "Started run:\n"
ifeq ($(CMDSHELL),cmd)
	copy ..\\..\\examples\\admb\\simple\\simple.dat .
	$(TARGET).exe
else
	cp ../../examples/admb/simple/simple.dat .
	./$(TARGET)
endif
	@printf "Finished run.\n"

clean:
ifeq ($(CMDSHELL),cmd)
	@del header.tmp 2>NUL
	@del xxalloc.tmp 2>NUL
	@del xxglobal.tmp 2>NUL
	@del xxhtop.tmp 2>NUL
	@del admodel.cov 2>NUL
	@del admodel.dep 2>NUL
	@del admodel.hes 2>NUL
	@del fmin.log 2>NUL
	@del hesscheck 2>NUL
	@del hessian.bin 2>NUL
	@del $(TARGET).exe 2>NUL
	@del $(TARGET).bar 2>NUL
	@del $(TARGET).bgs 2>NUL
	@del $(TARGET).cor 2>NUL
	@del $(TARGET).cpp 2>NUL
	@del $(TARGET).ecm 2>NUL
	@del $(TARGET).eva 2>NUL
	@del $(TARGET).hst 2>NUL
	@del $(TARGET).htp 2>NUL
	@del $(TARGET).log 2>NUL
	@del $(TARGET).luu 2>NUL
	@del $(TARGET).mc2 2>NUL
	@del $(TARGET).mcm 2>NUL
	@del $(TARGET).obj 2>NUL
	@del $(TARGET).par 2>NUL
	@del $(TARGET).psv 2>NUL
	@del $(TARGET).rhes 2>NUL
	@del $(TARGET).std 2>NUL
	@del $(TARGET).dat 2>NUL
	@del sims 2>NUL
else
	@rm -vf header.tmp
	@rm -vf xxalloc.tmp
	@rm -vf xxglobal.tmp
	@rm -vf xxhtop.tmp
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf fmin.log
	@rm -vf hesscheck
	@rm -vf hessian.bin
	@rm -vf $(TARGET)
	@rm -vf $(TARGET).bar
	@rm -vf $(TARGET).bgs
	@rm -vf $(TARGET).cor
	@rm -vf $(TARGET).cpp
	@rm -vf $(TARGET).ecm
	@rm -vf $(TARGET).eva
	@rm -vf $(TARGET).hst
	@rm -vf $(TARGET).htp
	@rm -vf $(TARGET).log
	@rm -vf $(TARGET).luu
	@rm -vf $(TARGET).mc2
	@rm -vf $(TARGET).mcm
	@rm -vf $(TARGET).obj
	@rm -vf $(TARGET).par
	@rm -vf $(TARGET).psv
	@rm -vf $(TARGET).rhes
	@rm -vf $(TARGET).std
	@rm -vf $(TARGET).dat
	@rm -vf sims
endif
