TARGET=catage

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

all: copy
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb.cmd catage.tpl
	$(TARGET) -nox
	@echo "\n===\n"
	$(TARGET) -hess_step 10 -hess_step_tol 1e-18
else
	../../admb$(EXT) catage.tpl
	./$(TARGET) -nox
	@echo "\n===\n"
	./$(TARGET) -hess_step 10 -hess_step_tol 1e-18
endif

copy: catage.dat catage.tpl

catage.dat:
ifeq ($(CMDSHELL),cmd)
	copy ..\..\examples\admb\catage\catage.dat
else
	cp ../../examples/admb/catage/catage.dat .
endif

catage.tpl:
ifeq ($(CMDSHELL),cmd)
	copy ..\..\examples\admb\catage\catage.tpl
else
	cp ../../examples/admb/catage/catage.tpl .
endif

clean:
ifeq ($(CMDSHELL),cmd)
	@del admodel.cov
	@del admodel.dep
	@del admodel.hes
	@del catage.exe
	@del catage.b01
	@del catage.b02
	@del catage.bar
	@del catage.cor
	@del catage.cpp
	@del catage.dat
	@del catage.eva
	@del catage.htp
	@del catage.log
	@del catage.obj
	@del catage.p01
	@del catage.p02
	@del catage.par
	@del catage.r01
	@del catage.r02
	@del catage.rep
	@del catage.std
	@del catage.tpl
else
	@rm -vf fmin.log
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf catage
	@rm -vf catage.b01
	@rm -vf catage.b02
	@rm -vf catage.bar
	@rm -vf catage.cor
	@rm -vf catage.cpp
	@rm -vf catage.dat
	@rm -vf catage.eva
	@rm -vf catage.htp
	@rm -vf catage.log
	@rm -vf catage.obj
	@rm -vf catage.p01
	@rm -vf catage.p02
	@rm -vf catage.par
	@rm -vf catage.r01
	@rm -vf catage.r02
	@rm -vf catage.rep
	@rm -vf catage.std
	@rm -vf catage.tpl
	@rm -vf fmin.log
endif

get-outputs:
ifeq ($(CMDSHELL),cmd)
	type catage.cor
	type catage.eva
	type catage.par
	type catage.std
	type sims
else
	cat catage.cor
	cat catage.eva
	cat catage.par
	cat catage.std
	cat sims
endif
