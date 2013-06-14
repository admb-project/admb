# Prepares the dat-file for the socatt data.

# Reads data
data <- read.table("data/Socatt.txt")
names(data) <- c("district","iddist","year","y","party","soc_class","gender","age","religion")
data$id <- 10000*data$district + data$iddist 			# Unique key for each individual

data$y[data$y==0] <- 1 		# Combines 0's and 1's

n <- nrow(data)
M <- length(unique(data$id))

# Setter opp modellen
X <- 1*cbind(data$rel==2,data$rel==3,data$rel==4)
p <- ncol(X)


# Skriver til ADMB
cat("# n\n",n,"\n",file="socatt.dat")
cat("# y\n",data$y,"\n",file="socatt.dat",append=T)
cat("# S\n",7,"\n",file="socatt.dat",append=T)
cat("# p\n",p,"\n# X\n",file="socatt.dat",append=T)
write.table(X,col=F,row=F,quote=F,file="socatt.dat",append=T)
cat("# M\n",M,"\n",file="socatt.dat",append=T)
cat("# ngroup\n",table(data$id),"\n",file="socatt.dat",append=T)

cat("987654321\n",file="socatt.dat",append=T)

cat("# b\n",rep(0,p),"\n",file="socatt.pin")
cat("# log_sigma\n",-.69,"\n",file="socatt.pin",append=T)
cat("# tmpk\n",c(-2,rep(0,7-2)),"\n",file="socatt.pin",append=T)
cat("# u\n",rep(0,M),"\n",file="socatt.pin",append=T)


# Calculates kappa
kappa <- function(logsigma,tmpk)
{
  kappa <- tmpk[1];
  for(i in 2:6)
    kappa[i] <- kappa[i-1] + exp(tmpk[i])
  kappa <- kappa*exp(logsigma)
  kappa
}





