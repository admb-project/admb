all:
	$(MAKE) --directory=RC04_solve
	$(MAKE) --directory=RC04_det
	$(MAKE) --directory=RC04_inv
	$(MAKE) --directory=RC10_spline1
	$(MAKE) --directory=RC10_spline2
	$(MAKE) --directory=RC13_dsort
	$(MAKE) --directory=RC15_eigen
	$(MAKE) --directory=RC26_dflndet
	$(MAKE) --directory=RC27_dfsolve1
	$(MAKE) --directory=RC27_dfsolve2
	$(MAKE) --directory=RC05_quad
	$(MAKE) --directory=RC01_svd
clean:
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
get-outputs:
	@echo "# tests alternatives"
	@$(MAKE) --no-print-directory --directory=RC04_solve get-outputs
	@$(MAKE) --no-print-directory --directory=RC04_det get-outputs
	@$(MAKE) --no-print-directory --directory=RC04_inv get-outputs
	@$(MAKE) --no-print-directory --directory=RC10_spline1 get-outputs
	@$(MAKE) --no-print-directory --directory=RC10_spline2 get-outputs
	@$(MAKE) --no-print-directory --directory=RC13_dsort get-outputs
	@$(MAKE) --no-print-directory --directory=RC15_eigen get-outputs
	@$(MAKE) --no-print-directory --directory=RC26_dflndet get-outputs
	@$(MAKE) --no-print-directory --directory=RC27_dfsolve1 get-outputs
	@$(MAKE) --no-print-directory --directory=RC27_dfsolve2 get-outputs
	@$(MAKE) --no-print-directory --directory=RC05_quad get-outputs
	@$(MAKE) --no-print-directory --directory=RC01_svd get-outputs
