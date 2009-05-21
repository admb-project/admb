PROGRAM_NAME=depletion
run: $(PROGRAM_NAME)
	@#./$(PROGRAM_NAME)

$(PROGRAM_NAME): $(PROGRAM_NAME).cpp $(PROGRAM_NAME).htp
	mygccs $(PROGRAM_NAME)

$(PROGRAM_NAME).cpp: $(PROGRAM_NAME).tpl
	tpl2rem $(PROGRAM_NAME)

clean:
	@rm -vf $(PROGRAM_NAME)
	@rm -vf $(PROGRAM_NAME).htp
	@rm -vf $(PROGRAM_NAME).cpp
	@rm -vf *.tmp
	@rm -vf tfile*
