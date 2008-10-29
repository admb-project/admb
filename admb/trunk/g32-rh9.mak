
all:
	cd ./tools99; $(MAKE) -f optg32-rh9.mak  disk
	cd ./linad99; $(MAKE) -f optg32-rh9.mak disk
	cd ./nh99;    $(MAKE) -f optg32-rh9.mak  disk
	cd ./linad99; $(MAKE) -f safg32-rh9.mak  disk

clean:
	cd ./linad99; $(MAKE) -f optg32-rh9.mak clean
	cd ./nh99;    $(MAKE) -f optg32-rh9.mak  clean
	cd ./tools99; $(MAKE) -f optg32-rh9.mak  clean
	cd ./linad99; $(MAKE) -f safg32-rh9.mak  clean
