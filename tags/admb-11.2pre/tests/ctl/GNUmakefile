ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL=cmd
  else
    EXT=.sh
  endif
endif

TARGET=example

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb $(TARGET)
else
	../../admb$(EXT) $(TARGET)
endif

run:
ifeq ($(SHELL),cmd)
	$(TARGET)
else
	./$(TARGET)
endif

clean:
ifeq ($(SHELL),cmd)
	@del $(TARGET)
	@del variance
	@del fmin.log
	@del $(TARGET).eva
	@del $(TARGET).exe
	@del $(TARGET).htp
	@del $(TARGET).bar
	@del $(TARGET).bgs
	@del $(TARGET).cor
	@del $(TARGET).cpp
	@del $(TARGET).log
	@del $(TARGET).o
	@del $(TARGET).obj
	@del $(TARGET).par
	@del $(TARGET).std
	@del tests_$(TARGET).o
	@del tests_$(TARGET)
	@del eigv.rpt
	@del admodel.cov
	@del admodel.dep
	@del admodel.hes
	@del example.b01
	@del example.p01
else
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
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf example.b01
	@rm -vf example.p01
endif
