.PHONY: clean admb_messages init_bounded_number_matrix beta_regression hysimple

all: admb_messages init_bounded_number_matrix beta_regression hysimple

admb_messages:
	OPTIONS=-s make --directory=$@

init_bounded_number_matrix:
	OPTIONS=-s make --directory=$@

beta_regression:
	OPTIONS=-s make --directory=$@

hysimple:
	OPTIONS=-s make --directory=$@

clean:
	make --directory=beta_regression clean
	make --directory=hysimple clean
