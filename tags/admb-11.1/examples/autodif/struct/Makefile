run: oldstr struct
	@./oldstr
	@./struct

oldstr: oldstr.cpp
	@printf "Compiling executable $@ ...";$(ADMB_HOME)/bin/mygcco $@; printf "\n"

struct: struct.cpp
	@printf "Compiling executable $@ ...";$(ADMB_HOME)/bin/mygcco $@; printf "\n"

clean:
	@rm -vf oldstr struct fmin.log
