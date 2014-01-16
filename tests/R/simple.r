x <- rep(0,100)
x
f <- 0
dyn.load("simple.dll")
xx <- .C("simple", as.integer(length(x)), as.double(x), as.double(f), "")
dyn.unload("simple.dll")
