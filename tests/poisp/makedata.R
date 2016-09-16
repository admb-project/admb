set.seed(12345)
lambda<-function(x) 100*(sin(x*pi)+1)
Tmax<-10
lambdamax<-200
N<-rpois(1,Tmax*lambdamax)
prop<-runif(N,0,Tmax)
A<-runif(N)<(lambda(prop)/200)
X<-prop[A]

cat("#N\n",length(X),"\n#X\n",X,"\n",file="pp.dat")









