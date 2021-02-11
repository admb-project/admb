all: clean
	$(MAKE) /Fdata_adstring_array.mak data_adstring_array
	$(MAKE) /Fcov_re_sep.mak cov_re_sep
	$(MAKE) run

run:
	$(MAKE) /Fdata_adstring_array.mak run
	$(MAKE) /F=cov_re_sep.mak run

get-outputs:
	$(MAKE) /Fdata_adstring_array.mak get-outputs
	$(MAKE) /Fcov_re_sep.mak get-outputs

clean:
	$(MAKE) /Fdata_adstring_array.mak clean
	$(MAKE) /Fcov_re_sep.mak clean
