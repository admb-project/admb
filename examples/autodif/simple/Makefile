# #fcomp_s.cpp  Makefile  s1.cpp  simp1.cpp  simple.cpp  ss.cpp
# SRCS=fcomp_s.cpp
# run: s1 simp1 simple ss
# 	@./s1
# 	@./simp1
# 	@./simple
# 	@./ss
# 
# s1: s1.cpp
# 	@printf "Compiling executable $@ ...";g++ $^ -I. -fpermissive -Wno-deprecated -I$(ADMB_HOME)/include -L$(ADMB_HOME)/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -o$@; printf "\n"
# 
# simp1: $(SRCS) simp1.cpp
# 	@printf "Compiling executable $@ ...";g++ $^ -I. -fpermissive -Wno-deprecated -I$(ADMB_HOME)/include -L$(ADMB_HOME)/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -o$@; printf "\n"
# 
# simple: $(SRCS) simple.cpp
# 	@printf "Compiling executable $@ ...";g++ $^ -I. -fpermissive -Wno-deprecated -I$(ADMB_HOME)/include -L$(ADMB_HOME)/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -o$@; printf "\n"
# 
# ss: ss.cpp
# 	@printf "Compiling executable $@ ...";g++ $^ -I. -fpermissive -Wno-deprecated -I$(ADMB_HOME)/include -L$(ADMB_HOME)/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -o$@; printf "\n"
# 
# clean:
# 	@rm -vf s1 simp1 simple ss fmin.log

SRCS=fcomp_s.cpp

run: simple simple2
	@./simple
	@./simple2

simple: $(SRCS) simple.cpp
	@printf "Compiling executable $@ ...";g++ $^ -I. -fpermissive -Wno-deprecated -I$(ADMB_HOME)/include -L$(ADMB_HOME)/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -o$@; printf "\n"

simple2: $(SRCS) simple2.cpp
	@printf "Compiling executable $@ ...";g++ $^ -I. -fpermissive -Wno-deprecated -I$(ADMB_HOME)/include -L$(ADMB_HOME)/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -o$@; printf "\n"


# note path to the debug libraries relative to ADMB_HOME is a kludge
# and may be specific to Sibert's laptop
debug: $(SRCS) simple2.cpp
	printf "Compiling executable simple2 in debug mode\n:"
	g++ $^ -I. -ggdb -fpermissive -Wno-deprecated -I$(ADMB_HOME)/../../debug/admb-linux-gcc4.4.3-64bit/include -L$(ADMB_HOME)/../../debug/admb-linux-gcc4.4.3-64bit/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -ldf1b2s -ladmod -ladt -lads -ldf1b2s -ladmod -ladt -lads -osimple2

clean:
	@rm -vf simple
	@rm -vf simple2
