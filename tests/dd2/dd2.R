# example of what to compare against 
library(numDeriv)
f<-function(x)pbeta(x[1],x[2],x[3])
x<-c(.1,.2,.3)
H<-hessian(f,x)
H
