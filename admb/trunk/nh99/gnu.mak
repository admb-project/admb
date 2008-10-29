.SUFFIXES: .o .cpp



.cpp.o:

	  mygccopt  $*





lib: ad_cif.o cifstrem.o clist.o mem.o str.o str_aio.o string.o string1.o string2.o string2a.o string3.o string4.o string5.o string5a.o dfadcif.o



