ifeq ($(TERM),cygwin)
else
ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL=cmd
  else
    EXT=.sh
  endif
endif
endif

TARGET=beta2

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
	touch $(TARGET).dat
	./$(TARGET)
endif

clean:
ifeq ($(SHELL),cmd)
	@del $(TARGET)
	@del variance
	@del fmin.log
	@del $(TARGET).exe
	@del $(TARGET).eva
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
	@del beta2.dat
else
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
	@rm -vf $(TARGET).obj
	@rm -vf $(TARGET).par
	@rm -vf $(TARGET).std
	@rm -vf eigv.rpt
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf beta2.dat
endif
