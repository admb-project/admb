all:
	$(MAKE) /fcov_re.nmak all
	$(MAKE) /fcov_re_sep.nmak all

run:
	$(MAKE) /fcov_re.nmak run
	$(MAKE) /fcov_re_sep.nmak run

get-outputs: _get-outputs
	$(MAKE) /fcov_re.nmak get-outputs
	$(MAKE) /fcov_re_sep.nmak get-outputs

clean: _clean
	$(MAKE) /fcov_re.nmak clean
	$(MAKE) /fcov_re_sep.nmak clean
