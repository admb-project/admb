all:
	..\..\admb.cmd ad2csv.cpp main.cpp
!IF DEFINED(DEBUG)
	copy ad2csv.exe ..\..\build\debug\contrib\bin
!ELSE
	copy ad2csv.exe ..\..\build\dist\contrib\bin
!ENDIf

clean:
	if exist ad2csv.obj del /Q ad2csv.obj
	if exist main.obj del /Q main.obj
	if exist ad2csv.exe del /Q ad2csv.exe
