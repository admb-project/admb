#!/usr/bin/Rscript --vanilla --default-packages=utils

args <- commandArgs(TRUE)
if (length(args) > 0)
{
  filename <- substring(args[1], 3)
  filename_so <- paste(filename, ".so", sep = "") 
  dyn.load(filename_so)
  ret <- .C(filename, "")
  dyn.unload(filename_so)
}
