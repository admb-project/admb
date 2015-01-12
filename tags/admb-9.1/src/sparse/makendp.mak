LIBRARY = libor.a

LL = ar860n

CC = mx860n

CFLAGS = -c -I. -DDOS386 -DOPT_LIB



HEADERS = cifstrem.h clist.h safe_mem.h string.hpp

OBJECTS = cifstrem.o clist.o mem.o string.o string1.o \

	 string2.o string3.o string4.o str.o



# otter research large model library

$(LIBRARY).lib : $(OBJECTS)

	$(LL) $(LIBRARY) @$(LL).rsp,$(LL)

#del $(LL).rsp



.cpp.o : 

	$(CC)  $(CFLAGS) {$< }

	echo -+$* & >> $(LL).rsp



$(LL).rsp :

#	del $(LL).rsp

##########

