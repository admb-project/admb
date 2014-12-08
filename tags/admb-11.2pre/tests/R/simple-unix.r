x <- rep(0,100)
f <- 0
dyn.load("simple.so")
xx <- .C("simple", as.integer(length(x)), as.double(x), as.double(f), "")
dyn.unload("simple.so")
