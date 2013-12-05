.ONESHELL:
ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
SHELL = cmd
endif
ifeq ($(OS),Windows_NT)
EXT=.sh
endif
OPTION=-f

ifeq ($(SHELL),cmd)
$(CONTRIB_BIN)\ad2csv.exe: ad2csv.cpp main.cpp
	..\..\admb $(OPTION) $^
	copy ad2csv.exe $@
else
$(CONTRIB_BIN)/ad2csv: ad2csv.cpp main.cpp
	../../admb$(EXT) $(OPTION) $^
	cp ad2csv $@
endif

clean:
ifeq ($(SHELL),cmd)
	del ad2csv ad2csv.exe main.obj ad2csv.obj
	del main.o ad2csv.o
else
	rm -f ad2csv ad2csv.exe main.obj ad2csv.obj
	rm -f main.o ad2csv.o
endif
