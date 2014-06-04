all: 
	$(MAKE) glmmadmb.exe nbmm.exe bvprobit.exe
	$(MAKE) run

glmmadmb.exe: glmmadmb.tpl
	..\\..\\admb -r $@

glmmadmb.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/glmmadmb/pkg/inst/tpl/$@ > $@

nbmm.exe: nbmm.tpl
	..\\..\\admb -r $@

nbmm.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/glmmadmb/pkg/inst/tpl/$@ > $@

bvprobit.exe: bvprobit.tpl
	..\\..\\admb -r $@

bvprobit.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/glmmadmb/pkg/inst/tpl/$@ > $@

run:
	glmmadmb.exe

clean:
	@del admodel.cov
	@del admodel.dep
	@del admodel.hes
	@del b1
	@del b2
	@del eigv.rpt
	@del fmin.log
	@del glmmadmb.exe
	@del glmmadmb.b01
	@del glmmadmb.bar
	@del glmmadmb.bgs
	@del glmmadmb.cor
	@del glmmadmb.cpp
	@del glmmadmb.eva
	@del glmmadmb.htp
	@del glmmadmb.log
	@del glmmadmb.luu
	@del glmmadmb.obj
	@del glmmadmb.p01
	@del glmmadmb.par
	@del glmmadmb.r01
	@del glmmadmb.rep
	@del glmmadmb.rhes
	@del glmmadmb.std
	@del hesscheck
	@del hessian.bin
	@del phi.rep
	@del s1
	@del s2
	@del variance
	@del bvprobit.cpp bvprobit.obj bvprobit bvprobit.htp
	@del nbmm.cpp nbmm.obj nbmm nbmm.htp
