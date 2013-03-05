.PHONY: clean testminmax SS3 admb_messages init_bounded_number_matrix beta_regression hysimple simple_mcmc betareg gmrf RC04_solve RC04_det RC04_inv RC10_spline1 RC10_spline2 RC13_dsort RC15_eigen RC26_dflndet RC27_dfsolve1 RC27_dfsolve2 RC05_quad RC01_svd atan2 priors betai beta2 beta3 adstring_array df33_tester beta_deviate

ADMB_HOME=$(CURDIR)/../build/dist

all: test-cov_re

main: test-geolocation test-cov_re

test-geolocation:
	-$(MAKE) --directory=geolocation

test-expm:
	$(MAKE) --directory=expm

test-cov_re:
	ADMB_HOME=$(ADMB_HOME) $(MAKE) --directory=cov_re

adstring_array:
	OPTIONS=-s $(MAKE) --directory=$@

priors:
	CXXFLAGS=$(CXXFLAGS) OPTIONS=-s $(MAKE) --directory=$@

atan2:
	OPTIONS=-s $(MAKE) --directory=$@

testminmax:
	OPTIONS=-s $(MAKE) --directory=$@

SS3:
	$(MAKE) --directory=$@

admb_messages:
	OPTIONS=-s $(MAKE) --directory=$@

init_bounded_number_matrix:
	OPTIONS=-s $(MAKE) --directory=$@

df33_tester:
	OPTIONS=-s $(MAKE) --directory=$@

beta_regression:
	OPTIONS=-s $(MAKE) --directory=$@

hysimple:
	OPTIONS=-s $(MAKE) --directory=$@

simple_mcmc:
	OPTIONS=-s $(MAKE) --directory=$@

betareg:
	OPTIONS=-s $(MAKE) --directory=$@

gmrf:
	OPTIONS=-s $(MAKE) --directory=$@

RC04_solve:
	OPTIONS=-s $(MAKE) --directory=$@

RC04_det:
	OPTIONS=-s $(MAKE) --directory=$@

RC04_inv:
	OPTIONS=-s $(MAKE) --directory=$@

RC10_spline1:
	OPTIONS=-s $(MAKE) --directory=$@

RC10_spline2:
	OPTIONS=-s $(MAKE) --directory=$@

RC13_dsort:
	OPTIONS=-s $(MAKE) --directory=$@

RC15_eigen:
	OPTIONS=-s $(MAKE) --directory=$@

RC26_dflndet:
	OPTIONS=-s $(MAKE) --directory=$@

RC27_dfsolve1:
	OPTIONS=-s $(MAKE) --directory=$@

RC27_dfsolve2:
	OPTIONS=-s $(MAKE) --directory=$@

RC05_quad:
	OPTIONS=-s $(MAKE) --directory=$@

RC01_svd:
	OPTIONS=-s $(MAKE) --directory=$@

betai:
	OPTIONS=-s $(MAKE) --directory=$@

beta_deviate:
	OPTIONS=-s $(MAKE) --directory=$@

beta2:
	OPTIONS=-s $(MAKE) --directory=$@

beta3:
	OPTIONS=-s $(MAKE) --directory=$@

clean:
	$(MAKE) --directory=geolocation clean
	$(MAKE) --directory=expm clean
	$(MAKE) --directory=adstring_array clean
	$(MAKE) --directory=priors clean
	$(MAKE) --directory=beta_regression clean
	$(MAKE) --directory=hysimple clean
	$(MAKE) --directory=admb_messages clean
	$(MAKE) --directory=init_bounded_number_matrix clean
	$(MAKE) --directory=betareg clean
	$(MAKE) --directory=gmrf clean
	$(MAKE) --directory=simple_mcmc clean
	$(MAKE) --directory=testminmax clean
	$(MAKE) --directory=RC04_solve clean
	$(MAKE) --directory=RC04_det clean
	$(MAKE) --directory=RC04_inv clean
	$(MAKE) --directory=RC10_spline1 clean
	$(MAKE) --directory=RC10_spline2 clean
	$(MAKE) --directory=RC13_dsort clean
	$(MAKE) --directory=RC15_eigen clean
	$(MAKE) --directory=RC26_dflndet clean
	$(MAKE) --directory=RC27_dfsolve1 clean
	$(MAKE) --directory=RC27_dfsolve2 clean
	$(MAKE) --directory=RC05_quad clean
	$(MAKE) --directory=RC01_svd clean
	$(MAKE) --directory=betai clean
	$(MAKE) --directory=beta2 clean
	$(MAKE) --directory=beta3 clean
	$(MAKE) --directory=beta_deviate clean
	$(MAKE) --directory=SS3 clean
	$(MAKE) --directory=cov_re clean
