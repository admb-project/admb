all: run-new_sim_thread4 run-new_sim_thread3 tests

gtest-all.o:
	g++ -c -std=c++11 -pthread -I../googletest-read-only -I../googletest-read-only/include  ../googletest-read-only/src/gtest-all.cc

tests: gtest-all.o
	CXXFLAGS="-std=c++11 -I../googletest-read-only/include" admb tests_threaded.cpp gtest-all.o new_sim_thread3.o adpthread_manager.o df_file.o model7.o
	./tests_threaded

run-new_sim_thread3:
	CXXFLAGS="-std=c++11" admb new_sim_thread3.cpp main3.cpp adpthread_manager.cpp df_file.cpp model7.cpp 
	@echo "=== Run new_sim_thread3"
	time ./new_sim_thread3

run-new_sim_thread4:
	CXXFLAGS="-std=c++11" admb new_sim_thread4.cpp main4.cpp df_file.cpp model7.cpp 
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
	@rm -vf adpthread_manager.o main3.o main4.o  df_file.o model7.o new_sim_thread3.o new_sim_thread4.o
	@rm -vf tests_threaded gtest-all.o  tests_threaded.o
