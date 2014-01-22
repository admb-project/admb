ifeq ($(OS),Windows_NT)
EXT=.sh
endif

all: agemat.tpl
	../../admb$(EXT) agemat.tpl

agemat.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/nwfscassmt/pkg/nwfscAgeingError/inst/executables/AGEMAT.TPL > agemat.tpl

clean:
	@rm -vf agemat agemat.cpp agemat.htp agemat.obj
