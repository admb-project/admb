all:
	cd RC04_solve && $(MAKE) /NOLOGO
	cd RC04_det && $(MAKE) /NOLOGO
	cd RC04_inv && $(MAKE) /NOLOGO
	cd RC10_spline1 && $(MAKE) /NOLOGO
	cd RC10_spline2 && $(MAKE) /NOLOGO
	cd RC13_dsort && $(MAKE) /NOLOGO
	cd RC15_eigen && $(MAKE) /NOLOGO
	cd RC26_dflndet && $(MAKE) /NOLOGO
	cd RC27_dfsolve1 && $(MAKE) /NOLOGO
	cd RC27_dfsolve2 && $(MAKE) /NOLOGO
	cd RC05_quad && $(MAKE) /NOLOGO
	cd RC01_svd && $(MAKE) /NOLOGO

clean:
	cd RC04_solve && $(MAKE) /NOLOGO clean
	cd RC04_det && $(MAKE) /NOLOGO clean
	cd RC04_inv && $(MAKE) /NOLOGO clean
	cd RC10_spline1 && $(MAKE) /NOLOGO clean
	cd RC10_spline2 && $(MAKE) /NOLOGO clean
	cd RC13_dsort && $(MAKE) /NOLOGO clean
	cd RC15_eigen && $(MAKE) /NOLOGO clean
	cd RC26_dflndet && $(MAKE) /NOLOGO clean
	cd RC27_dfsolve1 && $(MAKE) /NOLOGO clean
	cd RC27_dfsolve2 && $(MAKE) /NOLOGO clean
	cd RC05_quad && $(MAKE) /NOLOGO clean
	cd RC01_svd && $(MAKE) /NOLOGO clean

get-outputs:
	@echo # tests alternatives
	@cd RC04_solve && $(MAKE) /NOLOGO get-outputs
	@cd RC04_det && $(MAKE) /NOLOGO get-outputs
	@cd RC04_inv && $(MAKE) /NOLOGO get-outputs
	@cd RC10_spline1 && $(MAKE) /NOLOGO get-outputs
	@cd RC10_spline2 && $(MAKE) /NOLOGO get-outputs
	@cd RC13_dsort && $(MAKE) /NOLOGO get-outputs
	@cd RC15_eigen && $(MAKE) /NOLOGO get-outputs
	@cd RC26_dflndet && $(MAKE) /NOLOGO get-outputs
	@cd RC27_dfsolve1 && $(MAKE) /NOLOGO get-outputs
	@cd RC27_dfsolve2 && $(MAKE) /NOLOGO get-outputs
	@cd RC05_quad && $(MAKE) /NOLOGO get-outputs
	@cd RC01_svd && $(MAKE) /NOLOGO get-outputs
