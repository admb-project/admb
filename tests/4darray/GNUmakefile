TARGET=4darray

default:
ifeq ($(OS),Windows_NT)
	..\..\build\admb\bin\tpl2cpp 4darray.tpl
	..\..\admb 4darray.cpp
	4darray
else
	../../build/admb/bin/tpl2cpp 4darray.tpl
	../../admb 4darray.cpp
	4darray
endif

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif
