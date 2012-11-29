# Prepare Union-wages data for ADMB-RE.
# Developed under R-1.8.

library(splines)

# Read data from file
data <- read.table("union_and_wages.txt",skip=12)
names(data) <- c("education","south","sex","experience","union","wage","age","race","occupation","sector","marr")
n <- nrow(data)

# Start writing to dat-file
cat("# n\n",n,"\n",file="union.dat")
cat("# y\n",data$union,"\n",file="union.dat",append=T)
cat("# race\n",data$race,"\n",file="union.dat",append=T)
cat("# sex\n",data$sex,"\n",file="union.dat",append=T)
cat("# south\n",data$south,"\n",file="union.dat",append=T)

# Support function: return index of first and last non-zero element of x
minmaxindex <- function(x) 
{
  x <- c(0,x,0)
  tmp <- x!=0
  c((1:length(x))[tmp & (c(0,diff(tmp))!=0)],(1:length(x))[tmp & (c(diff(tmp),0)!=0)])-1
}

# Function for writing design matrix for spline to file
catSpline <- function(x,ord,file)
{
  x1 <- min(x)
  x2 <- max(x)
  B <- splineDesign(knots=c(rep(x1,ord-1),seq(x1,x2,l=20),rep(x2,ord-1)),x=x,ord=ord)
  cat("# m1\n",ncol(B),"\n# X_B\n",file=file,append=T)
  write.table(B,file=file,append=T,col=F,row=F,quote=F)
  cat("# min,max index in X_B m\n",file=file,append=T)	# Writes start and stop indexes in B
  write.table(t(apply(B,1,minmaxindex)),file=file,append=T,col=F,row=F,quote=F)
  B
}

# Continue writing to the dat file: desingn matrices for splines
cat("# Design-matrix for wages\n",file="union.dat",append=T)
XB1 <- catSpline(x=data$wage,ord=4,"union.dat")
cat("# Design-matrix for age\n",file="union.dat",append=T)
XB2 <- catSpline(x=data$age,ord=3,"union.dat")
cat("# Design-matrix for education\n",file="union.dat",append=T)
XB3 <- catSpline(x=data$ed,ord=3,"union.dat")

