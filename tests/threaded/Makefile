all: run-new_sim_thread3 run-new_sim_thread4

run-new_sim_thread3:
	admb new_sim_thread3.cpp main.cpp adpthread_manager.cpp df_file.cpp model7.cpp 
	@echo "=== Run new_sim_thread3"
	time ./new_sim_thread3

run-new_sim_thread4:
	admb new_sim_thread4.cpp df_file.cpp model7.cpp 
	@echo "=== Run new_sim_thread4"
	time ./new_sim_thread4

verify:
	diff yyy zzz

example: thread-ex.c
	g++ -pthread -fpermissive -othread-ex thread-ex.c
	./thread-ex

clean:
	@rm -vf new_sim_thread3 new_sim_thread4
	@rm -vf yyy zzz
	@rm -vf variance eigv.rpt fmin.log
	@rm -vf thread-ex
	@rm -vf adpthread_manager.o main.o df_file.o model7.o new_sim_thread3.o new_sim_thread4.o
