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
	$(MAKE) gamm1
	$(MAKE) testgamm
	$(MAKE) run

run:
ifeq ($(CMDSHELL),cmd)
	gamm1
	testgamm
else
	./gamm1
	./testgamm
endif

gamm1: gamm1.cpp
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb gamm1.cpp
else
	../../admb$(EXT) gamm1.cpp
endif

testgamm: testgamm.cpp
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb testgamm.cpp
else
	../../admb$(EXT) testgamm.cpp
endif

clean:
ifeq ($(CMDSHELL),cmd)
	@del fmin.log gamm1 gamm1.obj testgamm testgamm.obj
else
	$(RM) fmin.log gamm1 gamm1.obj testgamm testgamm.obj
endif
