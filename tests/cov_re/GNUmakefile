.PHONY: run

all: clean cov_re cov_re_sep run

cov_re: cov_re.tpl
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; admb -r -s $@

cov_re_sep: cov_re_sep.tpl
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; admb -r -s $@

run:
	@printf "Started run:\n"
	./cov_re
	@printf "Finished run.\n"

	@printf "Started run:\n"
	./cov_re_sep
	@printf "Finished run.\n"

	@printf "Started run:\n"
	./cov_re_sep -shess
	@printf "Finished run.\n"

clean:
	@rm -vf cov_re.o
	@rm -vf cov_re.cor
	@rm -vf cov_re.bar
	@rm -vf cov_re.luu
	@rm -vf admodel.hes
	@rm -vf cov_re.eva
	@rm -vf cov_re.bgs
	@rm -vf variance
	@rm -vf admodel.cov
	@rm -vf cov_re.log
	@rm -vf cov_re.par
	@rm -vf cov_re.cpp
	@rm -vf eigv.rpt
	@rm -vf hesscheck
	@rm -vf hessian.bin
	@rm -vf cov_re.std
	@rm -vf cov_re.htp
	@rm -vf fmin.log
	@rm -vf admodel.dep
	@rm -vf cov_re
	@rm -vf cov_re.rhes
	@rm -vf cov_re_sep
	@rm -vf cov_re_sep.o
	@rm -vf cov_re_sep.cor
	@rm -vf cov_re_sep.rhes
	@rm -vf cov_re_sep.bar
	@rm -vf cov_re_sep.eva
	@rm -vf cov_re_sep.bgs
	@rm -vf cov_re_sep.log
	@rm -vf cov_re_sep.par
	@rm -vf cov_re_sep.cpp
	@rm -vf cov_re_sep.std
	@rm -vf cov_re_sep.htp
