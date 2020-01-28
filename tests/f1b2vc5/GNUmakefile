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

all: f1b2vc5
ifeq ($(CMDSHELL),cmd)
	f1b2vc5 -nohess
else
	./f1b2vc5 -nohess
endif

f1b2vc5: f1b2vc5.tpl
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb -g f1b2vc5.tpl
else
	../../admb$(EXT) -g f1b2vc5.tpl
endif

clean:
ifeq ($(CMDSHELL),cmd)
	@del admodel.hes 2>nul
	@del f1b2vc5.b01 2>nul
	@del f1b2vc5.cor 2>nul
	@del f1b2vc5.htp 2>nul
	@del f1b2vc5.p01 2>nul
	@del f1b2vc5.std 2>nul
	@del hesscheck 2>nul
	@del admodel.cov 2>nul
	@del admodel.tmp 2>nul
	@del f1b2vc5.bar 2>nul
	@del f1b2vc5.cpp 2>nul
	@del f1b2vc5.log 2>nul
	@del f1b2vc5.par 2>nul
	@del hessian.bin 2>nul
	@del admodel.dep 2>nul
	@del f1b2vc5.exe 2>nul
	@del f1b2vc5.bgs 2>nul
	@del f1b2vc5.eva 2>nul
	@del f1b2vc5.obj 2>nul
	@del f1b2vc5.rhes 2>nul
	@del fmin.log 2>nul
else
	@rm -vf admodel.hes
	@rm -vf f1b2vc5.b01
	@rm -vf f1b2vc5.cor
	@rm -vf f1b2vc5.htp
	@rm -vf f1b2vc5.p01
	@rm -vf f1b2vc5.std
	@rm -vf hesscheck
	@rm -vf admodel.cov
	@rm -vf admodel.tmp
	@rm -vf f1b2vc5.bar
	@rm -vf f1b2vc5.cpp
	@rm -vf f1b2vc5.log
	@rm -vf f1b2vc5.par
	@rm -vf hessian.bin
	@rm -vf admodel.dep
	@rm -vf f1b2vc5
	@rm -vf f1b2vc5.bgs
	@rm -vf f1b2vc5.eva
	@rm -vf f1b2vc5.obj
	@rm -vf f1b2vc5.rhes
	@rm -vf fmin.log
endif
