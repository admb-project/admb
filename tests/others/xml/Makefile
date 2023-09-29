# extensivly hacked version of
# A Generic Makefile for ADMB programs that also includes additonal libraries.
# Developed for Mac OSx using the clang++ compiler
# Author: Steve Martell & John Sibert
# —————————————————————— INSTRUCTIONS ———————————————————————— #
# 1. Set the EXEC variable to the name of the program.         #
# 2. List additional .cpp files required by EXEC in SRCS macro #
# 3. Set the ADMB_HOME path to your distribution of ADMB.      #
# 4. To make executables with ADMB "safe" library type: make   #
# 5. Optimized executables type: make OPT=TRUE                 #
# ———————————————————————————————————————————————————————————— #
#TARGETS = xpella pella-xml
#SRCS = $(TARGETS).cpp ADMB_XMLDoc.cpp 
#OBJS = $(SRCS:.cpp=.o)
#TPLS = $(TARGETS).tpl
#DEPS = $(SRCS:.cpp=.depends)

# Export the path to your ADMB dist directory
# export ADMB_HOME=/home/jsibert/admb/trunk/build/dist

# establish the C++ compiler (on Mac OSX use clang++)
# CC=gcc
# CXX=g++
CC=clang
CXX=clang++
# and linker
LL = $(CC)
LD = $(CXX)
# Remove macro
RM=rm -fv

# identify some extra file name suffixes
.SUFFIXES: .tpl .cpp .o .obj

# tell make not to delete these intermediate targets
.PRECIOUS: %.c %.cpp %.o %.obj

# make some special PHONY targets
.PHONY: all help rules clean dox

# set up ADMB flags and appropriate libraries
# make the "safe" version by default
# to make "the optimized" version, type  `make OPT=TRUE
ifeq ($(OPT),TRUE)
  CC_OPT = -O3 -DOPT_LIB
  LDFLAGS = -O3 
  LDLIBS  = $(ADMB_HOME)/lib/libadmbo.a $(ADMB_HOME)/contrib/lib/libcontribo.a -lxml2
else
  CC_OPT = -O0 -DSAFE_ALL -ggdb
  LDFLAGS = -O0 -ggdb
  LDLIBS  = $(ADMB_HOME)/lib/libadmb.a $(ADMB_HOME)/contrib/lib/libcontrib.a -lxml2
endif

# set general compiler flags
CXXFLAGS = $(CC_OPT) -D__GNUDOS__ -Dlinux -DUSE_LAPLACE  -I. -I$(ADMB_HOME)/include -I$(ADMB_HOME)/contrib/include -I/usr/include/libxml2 


# this is the default target
all: tpl2cpp pella-xml xpella simple

# link the object file into the executable 
pella-xml: pella-xml.o ADMB_XMLDoc.o
	$(LD) $(LDFLAGS) -o  $@ $^ $(LDLIBS)

xpella: xpella.o ADMB_XMLDoc.o model_xml.o
	$(LD) $(LDFLAGS) -o  $@ $^ $(LDLIBS)

simple: simple.o ADMB_XMLDoc.o model_xml.o
	$(LD) $(LDFLAGS) -o  $@ $^ $(LDLIBS)

# Advanced Auto Dependency Generation
# Check compiler options for generating phony targets (-MP -MD for clang compiler on OSX)
%.o : %.cpp
	$(CXX) -MP -MD -c -o $@ $< $(CXXFLAGS)

-include $(OBJS:%.o=%.d)

# Build the cpp file from the tpl
%.cpp : %.tpl tpl2cpp
	./tpl2cpp $*

#From ~/admb/trunk/src$ vi Makefile 
#
#lexfiles: lexdestdir $(DESTDIR)\bin\tpl2cpp.exe $(DESTDIR)\bin\tpl2rem.exe
#
#$(DESTDIR)\bin\tpl2cpp.exe: $(LEXDESTDIR)\tpl2cpp.c
#	$(CC) /nologo /TC /Fo$(LEXDESTDIR)\ /Fe$@ $(LEXDESTDIR)\tpl2cpp.c
#
#$(LEXDESTDIR)\tpl2cpp.c: nh99\tpl2cpp.lex
#	..\utilities\flex -o$(LEXDESTDIR)\lex.yy.c nh99\tpl2cpp.lex
#	..\utilities\sed -f nh99\sedflex $(LEXDESTDIR)\lex.yy.c > $@
#
#$(DESTDIR)\bin\tpl2rem.exe: $(LEXDESTDIR)\tpl2rem.c
#	$(CC) /nologo /TC /Fo$(LEXDESTDIR)\ /Fe$@ $(LEXDESTDIR)\tpl2rem.c
#
#$(LEXDESTDIR)\tpl2rem.c: df1b2-separable\tpl2rem.lex
#	..\utilities\flex -o$(LEXDESTDIR)\lex.yy.c df1b2-separable\tpl2rem.lex
#	..\utilities\sed -f df1b2-separable\sedflex $(LEXDESTDIR)\lex.yy.c > $@

tpl2cpp: tpl2cpp.c
	$(CC) tpl2cpp.c -ggdb -o tpl2cpp

tpl2cpp.c: tpl2cpp.lex
	flex -o lex.yy.c tpl2cpp.lex
	sed -f sedflex lex.yy.c > $@



clean: 
	$(RM) tpl2cpp tpl2cpp.c lex.yy.c
	$(RM) pella-xml pella-xml.htp pella-xml.cpp
	$(RM) xpella xpella.htp xpella.cpp
	$(RM) simple simple.htp simple.cpp
	$(RM) *.o
	$(RM) *.bar *.cor *.eva *.log *.par *.rep *.std *.hes *.cov *.dep
	rm -rf dox

dox:
	doxygen

# generate some information about what your are doing
rules:
	@echo OPT = $(OPT)
	@echo CC_OPT = $(CC_OPT)
	@echo PWD = $(PWD)
	@echo ADMB_HOME = $(ADMB_HOME)
	@echo CC = $(CC)
	$(CC) --version
	@echo LD = $(LD)
	@echo CXXFLAGS = $(CXXFLAGS)
	@echo LDFLAGS = $(LDFLAGS)


# Some help for the naive
help:
	@echo Set:   EXEC target to the BaseName of your tpl script.
	@echo Usage: make <OPT=TRUE>
	@echo        specify OPT=TRUE to build optimized version



