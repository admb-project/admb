# get som von mises RV (small rejection sampler)
set.seed(123)
N<-10000
proposal <- runif(N,0,2*pi)
U<-runif(N)
densUN <- function(x,mu=1,kappa=2)exp(kappa*cos(x-mu))/exp(kappa)
X<-proposal[U<densUN(proposal)]

cat("# X\n1000\n",X[1:1000], file="vonmises.dat")
