#update.cpp:void main()

run: ch_rob robsim robust runsims update
	@./ch_rob
	#@./robsim
	#@./robust
	#@./runsims
	#@./update

ch_rob: ch_rob.cpp
	@printf "Compiling executable $@ ...";g++ $^ -I. -fpermissive -Wno-deprecated -I$(ADMB_HOME)/include -L$(ADMB_HOME)/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -o$@; printf "\n"

robsim: robsim.cpp
	@printf "Compiling executable $@ ...";g++ $^ -I. -fpermissive -Wno-deprecated -I$(ADMB_HOME)/include -L$(ADMB_HOME)/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -o$@; printf "\n"

robust: fcomp_r.cpp robust.cpp
	@printf "Compiling executable $@ ...";g++ $^ -I. -fpermissive -Wno-deprecated -I$(ADMB_HOME)/include -L$(ADMB_HOME)/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -o$@; printf "\n"

runsims: runsims.cpp
	@printf "Compiling executable $@ ...";g++ -o$@ $^ ; printf "\n"

update: update.cpp
	@printf "Compiling executable $@ ...";g++ $^ -I. -fpermissive -Wno-deprecated -I$(ADMB_HOME)/include -L$(ADMB_HOME)/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -o$@; printf "\n"

clean:
	@rm -vf ch_rob robsim robust runsims update fmin.log
