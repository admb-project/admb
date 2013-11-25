../../build/dist/contrib/bin/ad2csv: ad2csv.cpp main.cpp
	../../admb $(OPTION) $^
ifeq ($(SHELL),sh.exe)
	copy ad2csv $@
else
	cp ad2csv $@
endif

clean:
	rm -f ad2csv.exe main.obj ad2csv.obj
	rm -f main.o ad2csv.o
