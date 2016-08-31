ifeq ($(TERM),cygwin)
else
ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL=cmd
  else
    EXT=.sh
  endif
endif
endif

all: f1b2vc5
ifeq ($(SHELL),cmd)
	f1b2vc5 -nohess
else
	./f1b2vc5 -nohess
endif

f1b2vc5: f1b2vc5.tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb -g f1b2vc5.tpl
else
	../../admb$(EXT) -g f1b2vc5.tpl
endif

clean:
ifeq ($(SHELL),cmd)
	@del admodel.hes
	@del f1b2vc5.b01
	@del f1b2vc5.cor
	@del f1b2vc5.htp
	@del f1b2vc5.p01
	@del f1b2vc5.std
	@del hesscheck
	@del admodel.cov
	@del admodel.tmp
	@del f1b2vc5.bar
	@del f1b2vc5.cpp
	@del f1b2vc5.log
	@del f1b2vc5.par
	@del hessian.bin
	@del admodel.dep
	@del f1b2vc5.exe
	@del f1b2vc5.bgs
	@del f1b2vc5.eva
	@del f1b2vc5.obj
	@del f1b2vc5.rhes
	@del fmin.log
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
