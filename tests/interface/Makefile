all:
	$(MAKE) --directory=simple

dev:
	$(MAKE) --directory=catage
	$(MAKE) --directory=forest
	$(MAKE) --directory=sdv

clean:
	@rm -vf model_parameters/model_parameters.obj

	$(MAKE) --directory=catage clean
	$(MAKE) --directory=simple clean
	$(MAKE) --directory=forest clean
	$(MAKE) --directory=sdv clean
