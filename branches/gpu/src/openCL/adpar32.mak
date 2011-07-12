.SUFFIXES: .obj .cpp

CC = cl

FLAGS = /DWIN32 /D_WINDOWS /D_LIB /D_MBCS /D__MSVC32__=8  /DSAFE_ALL /c /I..\..\..\..\src\openCL /I"%GPU%/shared/inc/" /I"%GPU%/OpenCL/common/inc" /I"C:\admb-branches-gpu\src\linad99" /I"C:\admb-branches-gpu\src\tools99" /I"C:\admb-branches-gpu\src\nh99" /I"C:\admb-branches-gpu\src\df1b2-separable" /I"%MSSDK%/Include" /Ox /EHsc /nologo

LIBNAME = adpar32.lib 

include ..\..\..\..\src\openCL\objects.lst

all: $(DISKDIR)\lib\$(LIBNAME)
	copy ..\..\..\..\src\openCL\adpar32.h $(DISKDIR)\include

$(DISKDIR)\lib\$(LIBNAME): $(ADPAR)
	lib /OUT:$@ /NOLOGO $(ADPAR)

../openCL/$(ADPAR):

$(ADPAR): ..\..\..\..\src\openCL\adpar32.cpp
	$(CC) $(FLAGS) /Fo$@ ..\..\..\..\src\openCL\adpar32.cpp

{..\..\..\..\src\openCL}.cpp.obj:
	$(CC) $(FLAGS) $<

