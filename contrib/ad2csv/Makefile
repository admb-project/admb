!IFNDEF ADMB_VER
ADMB_VER=admb
!ENDIF

all:
!IF DEFINED(DEBUG)
	..\..\admb.cmd -g -c -o ..\..\build\ad2csv\ad2csv.obj ad2csv.cpp
	..\..\admb.cmd -g -c -o ..\..\build\ad2csv\main.obj main.cpp
	..\..\admb.cmd -g -o ..\..\build\$(ADMB_VER)\bin\ad2csv.exe ..\..\build\ad2csv\ad2csv.obj ..\..\build\ad2csv\main.obj
!ELSE
	..\..\admb.cmd -c -o ..\..\build\ad2csv\ad2csv.obj ad2csv.cpp
	..\..\admb.cmd -c -o ..\..\build\ad2csv\main.obj main.cpp
	..\..\admb.cmd -o ..\..\build\$(ADMB_VER)\bin\ad2csv.exe ..\..\build\ad2csv\ad2csv.obj ..\..\build\ad2csv\main.obj
!ENDIF

clean:
	if exist ad2csv.obj del /Q ad2csv.obj
	if exist main.obj del /Q main.obj
	if exist ad2csv.exe del /Q ad2csv.exe
