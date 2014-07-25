all:
	..\..\admb.cmd ad2csv.cpp main.cpp
!IF DEFINED(DEBUG)
	copy ad2csv.exe ..\..\build\debug\contrib\bin
!ELSE
	copy ad2csv.exe ..\..\build\dist\contrib\bin
!ENDIf

clean:
	del ad2csv.obj
	del main.obj
	del ad2csv.exe
