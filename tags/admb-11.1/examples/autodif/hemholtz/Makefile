SRCS=hem_func.cpp
run: hemholtz
	@./hemholtz

hemholtz: $(SRCS) hemholtz.cpp
	@printf "Compiling executable $@ ...";g++ $^ -I. -fpermissive -Wno-deprecated -I$(ADMB_HOME)/include -L$(ADMB_HOME)/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -o$@; printf "\n"

clean:
	@rm -vf hemholtz
