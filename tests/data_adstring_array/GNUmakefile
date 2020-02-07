TARGET=data_adstring_array

default: $(TARGET)
	$(MAKE) run
	$(MAKE) clean
	$(MAKE) -f cov_re_sep.mak
	$(MAKE) -f cov_re_sep.mak clean

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif
