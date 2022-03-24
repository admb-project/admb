a: fpe_test2.dat
	admb -g fpe_test2.tpl

b: fpe_test.dat
	admb -g fpe_test.tpl fpe_check.cpp

c:
	gdb --command=fpe_test.gdb fpe_test

fpe_test2.dat:
	copy ..\..\examples\admb\simple\simple.dat fpe_test2.dat

fpe_test.dat:
	copy ..\..\examples\admb\simple\simple.dat fpe_test.dat
