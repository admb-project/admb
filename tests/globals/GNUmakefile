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

all:
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb -r main.cpp
	main.exe
else
	../../admb main.cpp
	./main
endif

clean:
ifeq ($(CMDSHELL),cmd)
	@if exist main.obj del main.obj
	@if exist main.exe del main.exe
else
	@rm -vf main.obj
	@rm -vf main
endif
