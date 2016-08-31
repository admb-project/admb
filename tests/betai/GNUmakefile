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

TARGET=betai

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl $(TARGET).dat
ifeq ($(SHELL),cmd)
	..\\..\\admb -g $(TARGET)
else
	../../admb$(EXT) -g $(TARGET)
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
else
	@rm -vf $(TARGET)
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
	@rm -vf tests_$(TARGET).o
	@rm -vf tests_$(TARGET)
	@rm -vf eigv.rpt
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
endif
