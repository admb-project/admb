run: chem-eng
	@./chem-eng

chem-eng:
	@dos2unix $@.tpl
	@printf "Converting tpl to cpp ... ";$(ADMB_HOME)/bin/tpl2cpp $@;printf "\n"
	@printf "Compiling executable ...";$(ADMB_HOME)/bin/mygcco $@;printf "\n"

clean:
	@rm -vf chem-eng{.htp,.cpp,.std,.rep,.b??,.p??,.r??,.cor,.eva,.log,}
	@rm -vf qafter?.tex
	@rm -vf qbefore?.tex
	@rm -vf admodel{.cov,.dep,.hes} eigv.rpt fmin.log variance
