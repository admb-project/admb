all:
	$(MAKE) run
	$(MAKE) run2
	$(MAKE) run3

run:
	cp ../../examples/admb/vol/n2mvol.dat .
	cp ../../examples/admb/vol/n2mvol.tpl .
	../../admb n2mvol &> /dev/null
	time ./n2mvol&> n2mvol.out

run2:
	cp ../../examples/admb/vol/n2mvol.dat n2mvol2.dat
	../../admb n2mvol2 &> /dev/null
	time ./n2mvol2 &> n2mvol2.out

run3:
	cp ../../examples/admb/vol/n2mvol.dat n2mvol3.dat
	../../admb n2mvol3 &> /dev/null
	time ./n2mvol3 &> n2mvol3.out

clean:
