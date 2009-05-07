#PROGRAM_NAME=union
PROGRAM_NAME=depletion
run: $(PROGRAM_NAME)
	@#./$(PROGRAM_NAME)

$(PROGRAM_NAME): $(PROGRAM_NAME).cpp $(PROGRAM_NAME).htp
	@printf "Compiling executable ...";$(ADMB_HOME)/bin/mygccs $(PROGRAM_NAME); printf "\n"

$(PROGRAM_NAME).cpp: $(PROGRAM_NAME).tpl
	@printf "Converting tpl to cpp ... ";touch xxalloc5.tmp; $(ADMB_HOME)/bin/tpl2rem $(PROGRAM_NAME); printf "\n"

clean:
	@rm -vf $(PROGRAM_NAME){.htp,.cpp,.std,.rep,.b??,.p??,.r??,.cor,.eva,.log,.rhes,.luu,}
	@rm -vf admodel{.cov,.dep,.hes} eigv.rpt fmin.log variance hess*
