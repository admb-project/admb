#macros for making optimized library for BORLAND 4.0
CC = bcc32
LL = tlib
FLAGS = -q -w -I\\Borland\\BCC55\\Include -I..\\nh99 -I..\\linad99 -I..\\tools99 ${OPTIONS} -DUSE_LAPLACE -O2 -DOPT_LIB -DDOS386 -I. -6 -c -f
#FLAGS = -H -Hc -O2 -DOPT_LIB -DDOS386 -I. -5 -c -f
LIBPATH = b32polp
LIBNAME = df1b2o.lib 
BINDIR=bin
LIBRARIAN = tlib
#DISKDIR= f:/borland-50-laplace
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp .dir

vpath %.obj $(LIBPATH)$

include objects.lst

all: $(LIBPATH)/$(LIBNAME) disk


$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJSPLUS)
	echo $(LIBNAME)  > $(LIBPATH)/t.rsp
	cd $(LIBPATH) ; \
	del *.lib ; \
	ls *.obj >> t.rsp
	cd ..
	sed -e ' 1,$$s/$$/ \&/' -e '2,$$s/^/+/' -e ' $$s/ \&//' -e ' s/b32o\///' $(LIBPATH)/t.rsp > tmpfile
	cp tmpfile $(LIBPATH)/t.rsp 
	cd $(LIBPATH) ; \
	tlib /P1024 @t.rsp
	cd ..

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -w-8057 -w-8004 -w-8001 -w-8066 -w-8084 -w-8060 -w-8071 -w-8008 -w-8041 -w-8012 -o$(LIBPATH)/$* $<

$(OBJSPLUS): %.obj: %.cpp
	$(CC) $(FLAGS) -w-8057 -w-8004 -w-8001 -w-8066 -w-8084 -w-8060 -w-8071 -w-8008 -w-8041 -w-8012 -o$(LIBPATH)/$* $<

disk: 
	cp adpool.h adrndeff.h df1b2fun.h smartbuf.h $(DISKDIR)/$(INCLUDEDIR)
	cp df1b2fnl.h $(DISKDIR)/$(INCLUDEDIR)
	cp df1b2loc.h $(DISKDIR)/$(INCLUDEDIR)
	cp df32fun.h $(DISKDIR)/$(INCLUDEDIR)
	cp df3fun.h $(DISKDIR)/$(INCLUDEDIR)
	cp f1b2locl.h $(DISKDIR)/$(INCLUDEDIR)
	flex < tpl2rem.lex
	sed -f sedflex lex.yy.c > tpl2rem.c
	bcc32 -w -w-8008 -w-8008 -w-8004 -w-8012 -w-8071 -w-8013 -DWIN32 -I\\Borland\\BCC55\\Include -L\\Borland\\BCC55\\Lib tpl2rem.c
	cp tpl2rem.exe $(DISKDIR)/$(BINDIR)/tpl2rem.exe
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 
	cp sedcmd $(DISKDIR)/$(BINDIR)
	cp sedcmd2 $(DISKDIR)/$(BINDIR)
	cp sedcmd3 $(DISKDIR)/$(BINDIR)
	cp seddf1b2 $(DISKDIR)/$(BINDIR)
	cp seddf1b3 $(DISKDIR)/$(BINDIR)
	cp seddf1b4 $(DISKDIR)/$(BINDIR)
	cp sedf1b2a $(DISKDIR)/$(BINDIR)
	cp sedf1b2c $(DISKDIR)/$(BINDIR)
	cp sedf1b2d $(DISKDIR)/$(BINDIR)

clean:
	-rm -f bor502-win32olp/*.obj
	-rm -f bor502-win32slp/*.obj
	-rm -f bor502-win32olp/t.rsp
	-rm -f bor502-win32slp/t.rsp
	-rm -f tmpfile
	-rm -f tpl2rem.obj
	-rm -f tpl2rem.exe
	-rm -f lex.yy.c
	-rm -f tpl2rem.tds
	-rm -f bor502-win32olp/df1b2o.lib
	-rm -f bor502-win32slp/df1b2s.lib
	-rm -f bor502-win32olp/df1b2o.BAK
	-rm -f bor502-win32slp/df1b2s.BAK
