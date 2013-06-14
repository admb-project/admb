PROG_NAME=io_examp

run: $(PROG_NAME)
	@./$(PROG_NAME)

$(PROG_NAME):
	@printf "Compiling executable ...";$(ADMB_HOME)/bin/mygcco $@

clean:
	@rm -vf $(PROG_NAME) file1.tmp  file2.tmp
