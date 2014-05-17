TARGET=example

ifeq ($(OS),Windows_NT)
EXT=.sh
endif

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl
	../../admb$(EXT) $(TARGET)

run:
	@printf "Started run:\n"
	./$(TARGET)
	@printf "Finished run.\n"

clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf eigv.rpt
	@rm -vf example
	@rm -vf example.b01
	@rm -vf example.bar
	@rm -vf example.cor
	@rm -vf example.cpp
	@rm -vf example.eva
	@rm -vf example.htp
	@rm -vf example.log
	@rm -vf example.obj
	@rm -vf example.p01
	@rm -vf example.par
	@rm -vf example.std
	@rm -vf fmin.log
	@rm -vf variance
