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

all:
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb -r main.cpp
	main.exe
else
	../../admb$(EXT) main.cpp
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
