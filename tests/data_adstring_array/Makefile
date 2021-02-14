all: clean
	$(MAKE) /NOLOGO /Fdata_adstring_array.nmak data_adstring_array
	$(MAKE) /NOLOGO /Fcov_re_sep.nmak cov_re_sep
	$(MAKE) /NOLOGO run

run:
	$(MAKE) /NOLOGO /Fdata_adstring_array.nmak run
	$(MAKE) /NOLOGO /F=cov_re_sep.nmak run

get-outputs:
	$(MAKE) /NOLOGO /Fdata_adstring_array.nmak get-outputs
	$(MAKE) /NOLOGO /Fcov_re_sep.nmak get-outputs

clean:
	$(MAKE) /NOLOGO /Fdata_adstring_array.nmak clean
	$(MAKE) /NOLOGO /Fcov_re_sep.nmak clean
