run: compile
	@./ham4
	@./ham5

compile:
	@dos2unix ham4.tpl
	@dos2unix ham5.tpl
	@printf "Converting tpl to cpp ... ";$(ADMB_HOME)/bin/tpl2cpp ham4;printf "\n"
	@printf "Converting tpl to cpp ... ";$(ADMB_HOME)/bin/tpl2cpp ham5;printf "\n"
	@printf "Compiling executable ... ";$(ADMB_HOME)/bin/mygcco ham4;printf "\n"
	@printf "Compiling executable ...";$(ADMB_HOME)/bin/mygcco ham5;printf "\n"

clean:
	@rm -vf ham?{.htp,.cpp,.std,.rep,.b??,.p??,.r??,.cor,.eva,.log,}
	@rm -vf qafter?.tex
	@rm -vf qbefore?.tex
	@rm -vf admodel{.cov,.dep,.hes} eigv.rpt fmin.log variance
