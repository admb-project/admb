default:
ifeq ($(OS),Windows_NT)
	copy ..\..\examples\admb\simple\simple.tpl admodel.tpl
	copy ..\..\examples\admb\simple\simple.dat admodel.dat
	..\..\build\admb\bin\tpl2cpp -debug
else
	cp ../../examples/admb/simple/simple.tpl admodel.tpl
	cp ../../examples/admb/simple/simple.dat admodel.dat
	../../build/admb/bin/tpl2cpp -debug
	../../admb admodel.cpp
	./admodel
	$(MAKE) clean

	cp ../../examples/admb/simple/simple.tpl admodel.tpl
	cp ../../examples/admb/simple/simple.dat admodel.dat
	../../build/admb/bin/tpl2cpp
	../../admb admodel.cpp
	./admodel
	$(MAKE) clean
endif

clean:
ifeq ($(OS),Windows_NT)
	del admodel.htp admodel.cpp
else
	rm -vf admodel admodel.cpp admodel.htp admodel.bar admodel.cor admodel.cov admodel.dat admodel.dep admodel.eva admodel.hes admodel.log admodel.obj admodel.par admodel.std admodel.tpl fmin.log
endif
