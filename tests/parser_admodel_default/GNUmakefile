default:
ifeq ($(OS),Windows_NT)
	copy ..\..\examples\admb\simple\simple.tpl admodel.tpl
	copy ..\..\examples\admb\simple\simple.dat admodel.dat
	..\..\build\admb\bin\tpl2cpp -debug
else
	cp ../../examples/admb/simple/simple.tpl admodel.tpl
	cp ../../examples/admb/simple/simple.dat admodel.dat
	../../build/admb/bin/tpl2cpp -debug
endif
