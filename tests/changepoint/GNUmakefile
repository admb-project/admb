TARGET=changepoint

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

default: $(TARGET).tpl $(TARGET).dat
	$(MAKE) $(TARGET)
	$(MAKE) run

changepoint.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/nwfscassmt/pkg/nwfscAgeingError/inst/executables/AGEMAT.TPL > changepoint.tpl

changepoint.dat:
	svn cat svn://scm.r-forge.r-project.org/svnroot/nwfscassmt/pkg/nwfscAgeingError/inst/doc/changepoint.dat > changepoint.dat
