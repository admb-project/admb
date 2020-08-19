TARGET=cov_re_sep

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif
