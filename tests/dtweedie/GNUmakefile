TARGET=tweedie

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

R:
	Rscript Tweedie_demo.R
