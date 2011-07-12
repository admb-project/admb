.SUFFIXES: .obj .cpp

CC = cl

FLAGS = /DWIN32 /D_WINDOWS /D_LIB /D_MBCS /D__MSVC32__=8 /DSAFE_ALL /DOPT_LIB /c /I"%GPU%/OpenCL/common/inc" /I"%GPU%/shared/inc" /I"%MSSDK%/Include" /Ox /EHsc /nologo

LIBNAME = shrutils32.lib 

include ..\..\..\..\src\openCL\objects.lst

all: $(DISKDIR)\lib\$(LIBNAME)
	copy $(GPU)\shared\inc\shrUtils.h $(DISKDIR)\include
	copy $(GPU)\shared\inc\cmd_arg_reader.h $(DISKDIR)\include

$(DISKDIR)\lib\$(LIBNAME): $(SHRUTILS) $(CMDARGREADER)
	lib /OUT:$@ /NOLOGO $(SHRUTILS) $(CMDARGREADER)

../openCL/$(SHRUTILS):

$(SHRUTILS): $(GPU)\shared\src\shrUtils.cpp
	$(CC) $(FLAGS) /Fo$@ $(GPU)\shared\src\shrUtils.cpp

../openCL/$(CMDARGREADER):

$(CMDARGREADER): $(GPU)\shared\src\cmd_arg_reader.cpp
	$(CC) $(FLAGS) /Fo$@ $(GPU)\shared\src\cmd_arg_reader.cpp

{..\..\..\..\src\openCL}.cpp.obj:
	$(CC) $(FLAGS) $<

