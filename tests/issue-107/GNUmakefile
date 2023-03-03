all:
	../../admb pella_t_modified
	-./pella_t_modified > out
	../../admb pella_t_modified2
	cp pella_t_modified.dat pella_t_modified2.dat
	-./pella_t_modified2 > out2

nohess:
	../../admb pella_t_modified
	-./pella_t_modified -nohess > out
	../../admb pella_t_modified2
	cp pella_t_modified.dat pella_t_modified2.dat
	-./pella_t_modified2 -nohess > out2

hess_step:
	../../admb pella_t_modified
	-./pella_t_modified -hess_step > out
	../../admb pella_t_modified2
	cp pella_t_modified.dat pella_t_modified2.dat
	-./pella_t_modified2 -hess_step > out2


diff:
	sed 's/-0\.0000/0\.0000/g' pella_t_modified.cor > pella_t_modified.cor2
	sed 's/-0\.0000/0\.0000/g' pella_t_modified2.cor > pella_t_modified2.cor2
	-diff -w --side-by-side pella_t_modified.cor2 pella_t_modified2.cor2
	-diff -w --side-by-side pella_t_modified.eva pella_t_modified2.eva
	-diff -w --side-by-side pella_t_modified.log pella_t_modified2.log
	-diff -w --side-by-side pella_t_modified.p01 pella_t_modified2.p01
	-diff -w --side-by-side pella_t_modified.p02 pella_t_modified2.p02
	-diff -w --side-by-side pella_t_modified.p03 pella_t_modified2.p03
	-diff -w --side-by-side pella_t_modified.par pella_t_modified2.par
	-diff -w --side-by-side pella_t_modified.std pella_t_modified2.std
	-diff -w --side-by-side --width=180 -w out out2
clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf cmpdiff.tmp
	@rm -vf gradfil1.tmp
	@rm -vf gradfil2.tmp
	@rm -vf varssave.tmp
	@rm -vf fmin.log out out2
	@rm -vf pella_t_modified
	@rm -vf pella_t_modified.b01
	@rm -vf pella_t_modified.b02
	@rm -vf pella_t_modified.b03
	@rm -vf pella_t_modified.bar
	@rm -vf pella_t_modified.cor
	@rm -vf pella_t_modified.cor2
	@rm -vf pella_t_modified.cpp
	@rm -vf pella_t_modified.eva
	@rm -vf pella_t_modified.htp
	@rm -vf pella_t_modified.log
	@rm -vf pella_t_modified.obj
	@rm -vf pella_t_modified.p01
	@rm -vf pella_t_modified.p02
	@rm -vf pella_t_modified.p03
	@rm -vf pella_t_modified.par
	@rm -vf pella_t_modified.std
	@rm -vf pella_t_modified2
	@rm -vf pella_t_modified2.dat
	@rm -vf pella_t_modified2.b01
	@rm -vf pella_t_modified2.b02
	@rm -vf pella_t_modified2.b03
	@rm -vf pella_t_modified2.bar
	@rm -vf pella_t_modified2.cor
	@rm -vf pella_t_modified2.cor2
	@rm -vf pella_t_modified2.cpp
	@rm -vf pella_t_modified2.eva
	@rm -vf pella_t_modified2.htp
	@rm -vf pella_t_modified2.log
	@rm -vf pella_t_modified2.obj
	@rm -vf pella_t_modified2.p01
	@rm -vf pella_t_modified2.p02
	@rm -vf pella_t_modified2.p03
	@rm -vf pella_t_modified2.par
	@rm -vf pella_t_modified2.std
	@rm -vf pella_t_modified.r01
	@rm -vf pella_t_modified.r02
	@rm -vf pella_t_modified.r03
	@rm -vf pella_t_modified.rep
	@rm -vf pella_t_modified2.r01
	@rm -vf pella_t_modified2.r02
	@rm -vf pella_t_modified2.r03
	@rm -vf pella_t_modified2.rep
