TARGET=expm

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

get-outputs:
	cat expm.std
	cat expm.par
	cat expm.std
	cat expm.cor
