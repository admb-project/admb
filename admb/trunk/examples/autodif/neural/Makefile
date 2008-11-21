#neur1.cpp:void main()
#neur2.cpp:main()
#neur3.cpp:main()
#neural.cpp:main()
#neural.cpp:main()
#nplot2.cpp:void main(int argc, char * argv[])
#winit.cpp:void main()
run:

neur1: neur1.cpp
	@printf "Compiling executable $@ ...";g++ $^ -I. -fpermissive -Wno-deprecated -I$(ADMB_HOME)/include -L$(ADMB_HOME)/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -o$@; printf "\n"

neur2: neur2.cpp
	@printf "Compiling executable $@ ...";g++ $^ -I. -fpermissive -Wno-deprecated -I$(ADMB_HOME)/include -L$(ADMB_HOME)/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -o$@; printf "\n"

neur3: neur3.cpp
	@printf "Compiling executable $@ ...";g++ $^ -I. -fpermissive -Wno-deprecated -I$(ADMB_HOME)/include -L$(ADMB_HOME)/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -o$@; printf "\n"

neural: neural.cpp
	@printf "Compiling executable $@ ...";g++ $^ -I. -fpermissive -Wno-deprecated -I$(ADMB_HOME)/include -L$(ADMB_HOME)/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -o$@; printf "\n"

nplot2: nplot2.cpp
	@printf "Compiling executable $@ ...";g++ $^ -I. -fpermissive -Wno-deprecated -I$(ADMB_HOME)/include -L$(ADMB_HOME)/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -o$@; printf "\n"

winit: winit.cpp
	@printf "Compiling executable $@ ...";g++ $^ -I. -fpermissive -Wno-deprecated -I$(ADMB_HOME)/include -L$(ADMB_HOME)/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -o$@; printf "\n"

clean:
	@rm -vf neur1 fmin.log
