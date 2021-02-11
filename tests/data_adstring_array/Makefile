all: clean
	$(MAKE) /Fdata_adstring_array.nmak data_adstring_array
	$(MAKE) /Fcov_re_sep.nmak cov_re_sep
	$(MAKE) run

run:
	$(MAKE) /Fdata_adstring_array.nmak run
	$(MAKE) /F=cov_re_sep.nmak run

get-outputs:
	$(MAKE) /Fdata_adstring_array.nmak get-outputs
	$(MAKE) /Fcov_re_sep.nmak get-outputs

clean:
	$(MAKE) /Fdata_adstring_array.nmak clean
	$(MAKE) /Fcov_re_sep.nmak clean
