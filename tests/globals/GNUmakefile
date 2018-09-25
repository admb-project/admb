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

all:
ifeq ($(SHELL),cmd)
	..\\..\\admb -r main.cpp
	main.exe
else
	../../admb main.cpp
	./main
endif

clean:
ifeq ($(OS),Windows_NT)
	@del main.ob
	@del main.exe
else
	@rm -vf main.obj
	@rm -vf main
endif
