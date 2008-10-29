
all:
	cd ./linad99; $(MAKE) -f optg32-rh8-demo.mak disk
	cd ./nh99;    $(MAKE) -f optg32-rh8-demo.mak  disk
	cd ./tools99; $(MAKE) -f optg32-rh8-demo.mak  disk
	cd ./linad99; $(MAKE) -f safg32-rh8-demo.mak  disk

clean:
	cd ./linad99; $(MAKE) -f optg32-rh8-demo.mak clean
	cd ./nh99;    $(MAKE) -f optg32-rh8-demo.mak  clean
	cd ./tools99; $(MAKE) -f optg32-rh8-demo.mak  clean
	cd ./linad99; $(MAKE) -f safg32-rh8-demo.mak  clean
