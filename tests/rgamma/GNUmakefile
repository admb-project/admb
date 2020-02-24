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

all: gamm1 testgamm
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
