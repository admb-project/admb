TARGET=4darray

default:
ifeq ($(OS),Windows_NT)
	..\..\build\admb\bin\tpl2cpp 4darray.tpl
	..\..\admb.cmd 4darray.cpp
else
	../../build/admb/bin/tpl2cpp 4darray.tpl
	../../admb 4darray.cpp
endif
	$(MAKE) _run

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

_run:
	$(MAKE) run
