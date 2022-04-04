ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifndef TERM
      export SHELL=cmd
      CMDSHELL=cmd
    endif
    ifndef CMDSHELL
      EXT=.sh
    endif
  endif
endif

ifeq ($(CMDSHELL),cmd)
$(CONTRIB_BIN)\ad2csv.exe: ad2csv.cpp main.cpp
	..\..\admb.cmd $(OPTION) -c -o ..\..\build\ad2csv\main.obj main.cpp
	..\..\admb.cmd $(OPTION) -c -o ..\..\build\ad2csv\ad2csv.obj ad2csv.cpp
	..\..\admb.cmd $(OPTION) -o $@ ..\..\build\ad2csv\ad2csv.obj ..\..\build\ad2csv\main.obj
else
$(CONTRIB_BIN)ad2csv: ad2csv.cpp main.cpp
	../../admb$(EXT) $(OPTION) -c -o ../../build/ad2csv/ad2csv.obj ad2csv.cpp
	../../admb$(EXT) $(OPTION) -c -o ../../build/ad2csv/main.obj main.cpp
	../../admb$(EXT) $(OPTION) -o $@ ../../build/ad2csv/ad2csv.obj ../../build/ad2csv/main.obj
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
