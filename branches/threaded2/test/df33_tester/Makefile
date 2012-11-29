FILENAME=test_df33_tester

all: clean run

run: $(FILENAME)
	./$^

$(FILENAME): $(FILENAME).o
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; LDFLAGS=" `gtest-config --ldflags --libs` " adlink ${OPTIONS} $(FILENAME)

$(FILENAME).o: $(FILENAME).cpp
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; adcomp ${OPTIONS} $(FILENAME)

clean:
	@rm -vf $(FILENAME)
	@rm -vf $(FILENAME).o
	@rm -vf variance
	@rm -vf fmin.log
