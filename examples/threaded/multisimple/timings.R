#plot.speedup<-function()
#{
#   ref <- 1
#
#   file="timings.csv"
#   t<-read.csv(file=file,header=TRUE)
#   a <- t$real[ref]/t$real
#   file="timings-prime.csv"
#   tp<-read.csv(file=file,header=TRUE)
#   ap <- tp$real[ref]/tp$real
#   plot(t$n,a,type='b',xlab="# of threads",ylab="Speedup over single thread (laptop)",
#            xlim=c(0,t$n[nrow(t)]), ylim=c(0,t$n[nrow(t)]))
#   points(tp$n,ap,type='b',col="blue")
#   lines(c(0,t$n[nrow(t)]),c(0,t$n[nrow(t)]),lty="dotted")
#
#
#   x11()
#   file="katsuo-msimple-timings.csv"
#   t<-read.table(file=file,header=TRUE)
#   a <- t$real[ref]/t$real
#   plot(t$n,a,type='b',xlab="# of threads",ylab="Speedup over single thread (katsuo)",
#            xlim=c(0,t$n[nrow(t)]), ylim=c(0,t$n[nrow(t)]))
#   lines(c(0,t$n[nrow(t)]),c(0,t$n[nrow(t)]),lty="dotted")
#   
#}

plot.speedup<-function(file)
{
   ref <- 1

   t<-read.table(file=file,header=TRUE)
   a <- t$real[ref]/t$real
   plot(t$n,a,type='b',xlab="# of threads",ylab="Speedup over single thread",
            xlim=c(0,t$n[nrow(t)]), ylim=c(0,t$n[nrow(t)]),main=file)
   lines(c(0,t$n[nrow(t)]),c(0,t$n[nrow(t)]),lty="dotted",lwd=2)
}
