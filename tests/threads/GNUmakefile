all: clean test-mforest test-msimple test-mexample

test-mforest:
	$(MAKE) --directory=mforest

test-msimple:
	$(MAKE) --directory=msimple

test-mexample:
	$(MAKE) --directory=mexample

clean:
	$(MAKE) --directory=mforest clean
	$(MAKE) --directory=msimple clean
	$(MAKE) --directory=mexample clean
