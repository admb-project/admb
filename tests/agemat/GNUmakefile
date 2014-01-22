all: agemat.tpl
	../../admb agemat.tpl

agemat.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/nwfscassmt/pkg/nwfscAgeingError/inst/executables/AGEMAT.TPL > agemat.tpl

clean:
	@rm -vf agemat agemat.cpp agemat.htp agemat.obj agemat.tpl
