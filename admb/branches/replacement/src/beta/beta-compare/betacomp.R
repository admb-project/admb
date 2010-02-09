compare.beta <- function(file)
{
  dat <- scan(file,com='#')
  nx <- as.integer(dat[1])
  b <- dat[2]
  x <- dat[3]
  print(paste(nx,b,x))
  beta <- matrix(dat[4:(length(dat)-3)],ncol=3,byrow=T)
  colnames(beta)<-c("a", "AD","cephes")
  print(head(beta))
  R <- pbeta(x, beta[,"a"], b)

  plot(beta[,"a"],beta[,"AD"],type = 'l',xlab="A",ylab="inc beta",lwd=7)
  lines(beta[,"a"],beta[,"cephes"],col="lightblue",lwd=3)
# points(beta[,"a"],jitter(R),col="red")
  lines(beta[,"a"],R,col="red")
  dev.copy2pdf(file="beta-comp.pdf")

  x11()
  devR <- (R - beta[,"AD"])/beta[,"AD"]
  plot(beta[,"a"],devR,type ='l',col="red",xlab="A",ylab="Error relative to AD",lwd=3)
  devC <- (beta[,"cephes"] - beta[,"AD"])/beta[,"AD"]
  lines(beta[,"a"],devC,col="blue")
  dev.copy2pdf(file="beta-dev.pdf")
  print(summary(cbind(devC,devR)))
  return(beta)

}
