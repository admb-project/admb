all: new_sim_thread3 new_sim_thread4 compare

new_sim_thread3:
	./mygcco2 $@
	@echo "=== Run $@"
	time ./$@

new_sim_thread4:
	./mygcco2 $@
	@echo "=== Run $@"
	time ./$@

compare:
	diff yyy zzz

example: thread-ex.c
	g++ -pthread -fpermissive -othread-ex thread-ex.c
	./thread-ex

clean:
	@rm -vf new_sim_thread3 new_sim_thread4
	@rm -vf yyy zzz
	@rm -vf variance eigv.rpt fmin.log
	@rm -vf thread-ex
