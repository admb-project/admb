all:
	$(MAKE) --file=cov_re.mak all
	$(MAKE) --file=cov_re_sep.mak all

run:
	$(MAKE) --file=cov_re.mak run
	$(MAKE) --file=cov_re_sep.mak run

get-outputs:
	@echo "# tests cov_re cov_re_sep"
	@$(MAKE) --no-print-directory --file=cov_re.mak get-outputs
	@$(MAKE) --no-print-directory --file=cov_re_sep.mak get-outputs

clean:
	$(MAKE) --file=cov_re.mak clean
	$(MAKE) --file=cov_re_sep.mak clean
