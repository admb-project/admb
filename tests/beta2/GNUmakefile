TARGET=beta2

ifeq ($(OS),Windows_NT)
EXT=.sh
endif

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl
	../../admb$(EXT) $(TARGET)

run:
	@printf "Started run:\n"
	touch $(TARGET).dat
	./$(TARGET)
	@printf "Finished run.\n"

clean:
	@rm -vf $(TARGET)
	@rm -vf $(TARGET).dat
	@rm -vf admodel.*
	@rm -vf variance
	@rm -vf fmin.log
	@rm -vf $(TARGET).eva
	@rm -vf $(TARGET).htp
	@rm -vf $(TARGET).bar
	@rm -vf $(TARGET).bgs
	@rm -vf $(TARGET).cor
	@rm -vf $(TARGET).cpp
	@rm -vf $(TARGET).log
	@rm -vf $(TARGET).o
	@rm -vf $(TARGET).par
	@rm -vf $(TARGET).std
	@rm -vf eigv.rpt
