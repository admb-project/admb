all:
	$(MAKE) clean
	../../../admb hemholtz.cpp hem_func.cpp
	$(MAKE) run

run:
	./hemholtz

clean:
	rm -vf hemholtz
	rm -vf fmin.log
	rm -vf hem_func.obj
	rm -vf hemholtz.obj
