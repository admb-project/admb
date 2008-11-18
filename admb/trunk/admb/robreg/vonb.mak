PROGRAM_NAME=vonb
run: $(PROGRAM_NAME)
	@./$(PROGRAM_NAME)

$(PROGRAM_NAME):
	@printf "Converting tpl to cpp ... ";$(ADMB_HOME)/bin/tpl2cpp $@;printf "\n"
	@printf "Compiling executable ...";$(ADMB_HOME)/bin/mygcco $@;printf "\n"

clean:
	@rm -vf $(PROGRAM_NAME){.htp,.cpp,.std,.rep,.b??,.p??,.r??,.cor,.eva,.log,}
	@rm -vf admodel{.cov,.dep,.hes} eigv.rpt fmin.log variance
