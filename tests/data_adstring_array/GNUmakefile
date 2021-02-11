all: clean
	$(MAKE) --file=data_adstring_array.mak data_adstring_array
	$(MAKE) --file=cov_re_sep.mak cov_re_sep
	$(MAKE) run

run:
	$(MAKE) --file=data_adstring_array.mak run
	$(MAKE) --file=cov_re_sep.mak run

get-outputs:
	$(MAKE) --file=data_adstring_array.mak get-outputs
	$(MAKE) --file=cov_re_sep.mak get-outputs

clean:
	$(MAKE) --file=data_adstring_array.mak clean
	$(MAKE) --file=cov_re_sep.mak clean
