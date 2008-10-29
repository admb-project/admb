DISKDIR= /usr/local/g296-rh73-laplace
LOCALDISKDIR= /home/skaug/admodel

all:
	cd ./tools99; $(MAKE)  -f  optg296-rh73-laplace.mak   disk
	cd ./df1b2-separable; $(MAKE)  -f optg296-rh73-laplace.mak   disk
	cd ./linad99; $(MAKE)  -f  optg296-rh73-laplace.mak disk
	cd ./linad99; $(MAKE)  -f  safg296-rh73-laplace.mak disk 
	cd ./nh99;    $(MAKE)  -f  optg296-rh73-laplace.mak   disk
	cd ./df1b2-separable; $(MAKE)  -f safg296-rh73-laplace.mak   disk 

clean:
	cd ./linad99; $(MAKE)  -f  optg296-rh73-laplace.mak clean
	cd ./linad99; $(MAKE)  -f  safg296-rh73-laplace.mak clean 
	cd ./nh99;    $(MAKE)  -f  optg296-rh73-laplace.mak   clean
	cd ./tools99; $(MAKE)  -f  optg296-rh73-laplace.mak   clean
	cd ./df1b2-separable; $(MAKE)  -f optg296-rh73-laplace.mak   clean
	cd ./df1b2-separable; $(MAKE)  -f optg296-rh73-laplace.mak   clean 

hanscopy:
	cp -v -r ${DISKDIR}/* ${LOCALDISKDIR} 
