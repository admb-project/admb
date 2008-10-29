
all:
	cd ./linad99; $(MAKE)  -f  optg296-rh73.mak disk
	cd ./linad99; $(MAKE)  -f  safg296-rh73.mak disk 
	cd ./nh99;    $(MAKE)  -f  optg296-rh73.mak   disk
	cd ./tools99; $(MAKE)  -f  optg296-rh73.mak   disk

alldbg:
	cd ./linad99; $(MAKE) "OPTIONS = -g "  -f  optg296-rh73.mak disk
	cd ./linad99; $(MAKE) "OPTIONS = -g "  -f  safg296-rh73.mak disk 
	cd ./nh99;    $(MAKE) "OPTIONS = -g "  -f  optg296-rh73.mak   disk
	cd ./tools99; $(MAKE) "OPTIONS = -g "  -f  optg296-rh73.mak   disk


clean:
	cd ./linad99; $(MAKE)  -f  optg296-rh73.mak clean
	cd ./linad99; $(MAKE)  -f  safg296-rh73.mak clean 
	cd ./nh99;    $(MAKE)  -f  optg296-rh73.mak   clean
	cd ./tools99; $(MAKE)  -f  optg296-rh73.mak   clean
