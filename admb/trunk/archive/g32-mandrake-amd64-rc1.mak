
all:
	cd ./linad99; $(MAKE) -f optg32-mandrake-amd64-rc1.mak disk
	cd ./nh99;    $(MAKE) -f optg32-mandrake-amd64-rc1.mak  disk
	cd ./tools99; $(MAKE) -f optg32-mandrake-amd64-rc1.mak  disk
	cd ./linad99; $(MAKE) -f safg32-mandrake-amd64-rc1.mak  disk

pvmall:
	cd ./linad99; $(MAKE) OPTIONS=-DUSE_ADPVM -f optg32-mandrake-amd64-rc1.mak disk
	cd ./nh99;    $(MAKE) OPTIONS=-DUSE_ADPVM -f optg32-mandrake-amd64-rc1.mak all
	cd ./tools99; $(MAKE) OPTIONS=-DUSE_ADPVM -f optg32-mandrake-amd64-rc1.mak  disk
	cd ./linad99; $(MAKE) OPTIONS=-DUSE_ADPVM -f safg32-mandrake-amd64-rc1.mak  disk

clean:
	cd ./linad99; $(MAKE) -f optg32-mandrake-amd64-rc1.mak clean
	cd ./nh99;    $(MAKE) -f optg32-mandrake-amd64-rc1.mak  clean
	cd ./tools99; $(MAKE) -f optg32-mandrake-amd64-rc1.mak  clean
	cd ./linad99; $(MAKE) -f safg32-mandrake-amd64-rc1.mak  clean
