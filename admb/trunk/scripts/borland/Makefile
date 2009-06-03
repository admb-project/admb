all: simple

admb-re: biglog

verify: SS3 ham4 ham5 vonb vonbr simple catage finance n2mvol
fails: union chem-eng forest pella-t truncreg

SS3:
	cd SS3
	admb SS3
	SS3
	admb -s SS3
	SS3
	cd ..

ham4:
	cd buscycle
	admb ham4
	ham4
	admb -s ham4
	ham4
	cd ..

ham5:
	cd buscycle
	admb ham5
	ham5
	admb -s ham5
	ham5
	cd ..

catage:
	cd catage
	admb catage
	catage
	admb -s catage
	catage
	cd ..

chem-eng:
	cd chem-eng
	admb chem-eng
	chem-eng
	admb -s chem-eng
	chem-eng
	cd ..

finance:
	cd finance
	admb finance
	finance
	admb -s finance
	finance
	cd ..

forest:
	cd forest
	admb forest
	forest
	admb -s forest
	forest
	cd ..

pella-t:
	cd pella-t
	admb pella-t
	pella-t
	admb -s pella-t
	pella-t
	cd ..

vonb:
	cd robreg
	admb vonb
	vonb
	admb -s vonb
	vonb
	cd ..

vonbr:
	cd robreg
	admb vonbr
	vonbr
	admb -s vonbr
	vonbr
	cd ..

simple:
	cd simple
	admb simple
	simple
	admb -s simple
	simple
	cd ..

truncreg:
	cd truncreg
	admb truncreg
	runtrunc
	fruntrunc
	admb -s truncreg
	runtrunc
	fruntrunc
	cd ..

n2mvol:
	cd vol
	admb n2mvol
	n2mvol
	admb -s n2mvol
	n2mvol
	cd ..

union:
	cd union
	admb-re union
	union	
	cd ..

biglog:
	cd ..\admb-re\biglog
	admb -r biglog
	biglog
	cd ..\..\admb
