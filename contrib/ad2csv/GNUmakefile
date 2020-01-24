.ONESHELL:

ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifeq ($(findstring bash.exe,$(shell where bash.exe 2>&1 | head)),bash.exe)
      EXT=.sh
    else
      CMDSHELL=cmd
    endif
  endif
endif

OPTION=-f

ifeq ($(CMDSHELL),cmd)
$(CONTRIB_BIN)\ad2csv.exe: ad2csv.cpp main.cpp
	..\..\admb.cmd $(OPTION) $^
	copy ad2csv.exe $@
else
$(CONTRIB_BIN)ad2csv: ad2csv.cpp main.cpp
	../../admb$(EXT) $(OPTION) $^
	cp ad2csv $@
endif

clean:
ifeq ($(CMDSHELL),cmd)
	if exist ad2csv del /Q ad2csv
	if exist ad2csv.exe del /Q ad2csv.exe
	if exist main.o del /Q main.o
	if exist main.obj del /Q main.obj
	if exist ad2csv.o del /Q ad2csv.o
	if exist ad2csv.obj del /Q ad2csv.obj
else
	rm -f ad2csv ad2csv.exe main.obj ad2csv.obj
	rm -f main.o ad2csv.o
endif
