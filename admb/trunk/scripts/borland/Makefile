all: simple

verify: SS3 ham4 ham5 vonb vonbr simple catage finance n2mvol
fails: union chem-eng forest pella-t truncreg

SS3:
	cd SS3
	makadmb SS3
	SS3
	makadmbs SS3
	SS3
	cd ..

ham4:
	cd buscycle
	makadmb ham4
	ham4
	makadmbs ham4
	ham4
	cd ..

ham5:
	cd buscycle
	makadmb ham5
	ham5
	makadmbs ham5
	ham5
	cd ..

catage:
	cd catage
	makadmb catage
	catage
	makadmbs catage
	catage
	cd ..

chem-eng:
	cd chem-eng
	makadmb chem-eng
	chem-eng
	makadmbs chem-eng
	chem-eng
	cd ..

finance:
	cd finance
	makadmb finance
	finance
	makadmbs finance
	finance
	cd ..

forest:
	cd forest
	makadmb forest
	forest
	makadmbs forest
	forest
	cd ..

pella-t:
	cd pella-t
	makadmb pella-t
	pella-t
	makadmbs pella-t
	pella-t
	cd ..

vonb:
	cd robreg
	makadmb vonb
	vonb
	makadmbs vonb
	vonb
	cd ..

vonbr:
	cd robreg
	makadmb vonbr
	vonbr
	makadmbs vonbr
	vonbr
	cd ..

simple:
	cd simple
	makadmb simple
	simple
	makadmbs simple
	simple
	cd ..

truncreg:
	cd truncreg
	makadmb truncreg
	runtrunc
	fruntrunc
	makadmbs truncreg
	runtrunc
	fruntrunc
	cd ..

n2mvol:
	cd vol
	makadmb n2mvol
	n2mvol
	makadmbs n2mvol
	n2mvol
	cd ..

union:
	cd union
	makadmb-re union
	union	
	cd ..
