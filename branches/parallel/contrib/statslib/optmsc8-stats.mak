.SUFFIXES: .obj .cpp

CC = cl

FLAGS = /nologo /W4 /GF /EHsc /DUSE_LAPLACE /DWIN32 /c /I..\..\..\..\src\df1b2-separable /I..\..\..\..\src\nh99 /I..\..\..\..\src\linad99 /I..\..\..\..\src\tools99 /I..\..\..\..\contrib\statslib /D__MSVC32__=8  /DOPT_LIB /Ox

LIBNAME = statso.lib 

include ..\..\..\..\contrib\statslib\objects.lst

all: $(DISKDIR)\lib\$(LIBNAME)
	copy ..\..\..\..\contrib\statslib\statsLib.h $(DISKDIR)\include

$(DISKDIR)\lib\$(LIBNAME): $(OBJECTS)
	lib /OUT:$@ /NOLOGO *.obj

alk.obj:
baranov.obj:
dbeta.obj:
dbinom.obj:
dgamma.obj:
dlnorm.obj:
dnbinom.obj:
dnorm.obj:
dpois.obj:
fill.obj:
logistic.obj:
dmvlogistic.obj:
rmvlogistic.obj:
dmultinom.obj:
pearsonresiduals.obj:
eplogis.obj:
multifan.obj:
dunif.obj:
dinvgamma.obj:
vcubicspline.obj:

{..\..\..\..\contrib\statslib}.cpp.obj:
	$(CC) $(FLAGS) $<

