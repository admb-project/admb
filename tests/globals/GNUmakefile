ifeq ($(OS),Windows_NT)
  ifeq ($(strip $(OSTYPE)),)
    SHELL=cmd
  else
    EXT=.sh
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
ifeq ($(SHELL),cmd)
	@del main.obj
	@del main.exe
else
	@rm -vf main.obj
	@rm -vf main
endif
