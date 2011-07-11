# Generates data from the logistic model and prepare input files for ADMB and BUGS


# Model parameters
n <- 200	# Sample size
p <- 5		# Number of fixed effects
q <- 30		# Number of random effects
sigma <- 0.1
mu <- 0
b <- rep(0,p)
X <- matrix(runif(n*p,-2,2),nrow=n)
X[abs(X)<.0001] <- 1			# Because BUGS does not handle e-formated numbers
Z <- matrix(runif(n*q,-2,2),nrow=n)
Z[abs(Z)<.0001] <- 1			# Because BUGS does not handle e-formated numbers
	
u <- rnorm(q,0,sigma)			# Random effects

eta <-  mu + X%*%b + Z%*%u
P <- exp(eta)/(1+exp(eta))
y  <- rbinom(n,1,P)			# Observations


# Write data files for Winbugs
cat("list(n=",n,	
		",p=",p,
		",x=structure(.Data=c(",paste(t(X),collapse=","),"),.Dim=c(",n,",",p,")),\n",
		",q=",q,
		",z=structure(.Data=c(",paste(t(Z),collapse=","),"),.Dim=c(",n,",",q,")),\n",
		",y=c(",paste(y,collapse=","),"))\n",sep="",file="data.txt")

# Skriver startverdier til fil for Winbugs
#cat("list(tau=",1/(3*sigma)^2,
#		",u=c(",paste(rep(0,q),collapse=","),")",
#		",b=c(",paste(rep(-1,p),collapse=","),
#		"))\n",sep="",file="inits.txt")


# Write data files for ADMB
cat("# n\n",n,"\n",file="logistic.dat")
cat("# y\n",y,"\n",file="logistic.dat",append=T)
cat("# p\n",p,"\n# X\n",file="logistic.dat",append=T)
write.table(X,col=F,row=F,quote=F,file="logistic.dat",append=T)
cat("# q\n",q,"\n# Z\n",file="logistic.dat",append=T)
write.table(Z,col=F,row=F,quote=F,file="logistic.dat",append=T)

cat("# b\n",rep(-1,p),"\n",file="logistic.pin")
cat("# log_sigma\n",log(3*sigma),"\n",file="logistic.pin",append=T)
cat("# u\n",rep(0,q),"\n",file="logistic.pin",append=T)
cat("# Bb\n",c(-10,10),"\n",file="logistic.pin",append=T)
cat("# Bls\n",c(-6,5),"\n",file="logistic.pin",append=T)


