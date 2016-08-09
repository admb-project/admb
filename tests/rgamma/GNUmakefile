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

all: gamm1 testgamm
ifeq ($(SHELL),cmd)
	gamm1
	testgamm
else
	./gamm1
	./testgamm
endif

gamm1: gamm1.cpp
ifeq ($(SHELL),cmd)
	..\\..\\admb gamm1.cpp
else
	../../admb gamm1.cpp
endif

testgamm: testgamm.cpp
ifeq ($(SHELL),cmd)
	..\\..\\admb testgamm.cpp
else
	../../admb testgamm.cpp
endif

clean:
ifeq ($(SHELL),cmd)
	@del fmin.log gamm1 gamm1.obj testgamm testgamm.obj
else
	$(RM) fmin.log gamm1 gamm1.obj testgamm testgamm.obj
endif
