.PHONY: clean SS3 admb_messages init_bounded_number_matrix beta_regression hysimple simple_mcmc betareg gmrf

#all: clean beta_regression hysimple simple_mcmc betareg gmrf
#all: clean init_bounded_number_matrix admb_messages
all: clean betareg beta_regression gmrf simple_mcmc

SS3:
	OPTIONS=-s make --directory=$@

admb_messages:
	OPTIONS=-s make --directory=$@

init_bounded_number_matrix:
	OPTIONS=-s make --directory=$@

beta_regression:
	OPTIONS=-s make --directory=$@

hysimple:
	OPTIONS=-s make --directory=$@

simple_mcmc:
	OPTIONS=-s make --directory=$@

betareg:
	OPTIONS=-s make --directory=$@

gmrf:
	OPTIONS=-s make --directory=$@

clean:
	make --directory=beta_regression clean
	make --directory=hysimple clean
	make --directory=admb_messages clean
	make --directory=init_bounded_number_matrix clean
	make --directory=betareg clean
	make --directory=gmrf clean
	make --directory=simple_mcmc clean
