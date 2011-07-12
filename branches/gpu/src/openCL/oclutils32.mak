.SUFFIXES: .obj .cpp

CC = cl

FLAGS = /DWIN32 /D_WINDOWS /D_LIB /D_MBCS /D__MSVC32__=8 /DSAFE_ALL /DOPT_LIB /c /I"%GPU%/OpenCL/common/inc" /I"%GPU%/shared/inc" /I"%MSSDK%/Include" /Ox /EHsc /nologo

LIBNAME = oclutils32.lib 

include ..\..\..\..\src\openCL\objects.lst

all: $(DISKDIR)\lib\$(LIBNAME)
	copy $(GPU)\OpenCL\common\inc\oclUtils.h $(DISKDIR)\include\oclutils.h
	IF NOT EXIST $(DISKDIR)\include\CL mkdir $(DISKDIR)\include\CL
	copy $(GPU)\OpenCL\common\inc\CL\*.h $(DISKDIR)\include\CL\*.h
	copy $(GPU)\OpenCL\common\lib\Win32\OpenCL.lib $(DISKDIR)\lib\OpenCL.lib

$(DISKDIR)\lib\$(LIBNAME): $(OCLUTILS)
	lib /OUT:$@ /NOLOGO $(OCLUTILS)

../openCL/$(OCLUTILS):

$(OCLUTILS): $(GPU)\OpenCL\common\src\oclUtils.cpp
	$(CC) $(FLAGS) /Fo$@ $(GPU)\OpenCL\common\src\oclUtils.cpp

{..\..\..\..\src\openCL}.cpp.obj:
	$(CC) $(FLAGS) $<
