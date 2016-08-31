all:
	$(MAKE) clean
	../../../admb oldstr.cpp
	../../../admb struct.cpp
	$(MAKE) run

run:
	./oldstr
	./struct

clean:
	rm -vf fmin.log
	rm -vf oldstr
	rm -vf oldstr.obj
	rm -vf struct
	rm -vf struct.obj
