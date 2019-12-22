all:
!IF DEFINED(DEBUG)
	..\..\admb.cmd -g ad2csv.cpp main.cpp
!ELSE
	..\..\admb.cmd ad2csv.cpp main.cpp
!ENDIF
	copy ad2csv.exe ..\..\build\admb\bin

clean:
	if exist ad2csv.obj del /Q ad2csv.obj
	if exist main.obj del /Q main.obj
	if exist ad2csv.exe del /Q ad2csv.exe
