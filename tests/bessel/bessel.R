N<-10
options(digits=22)
x <- seq(1.0e-4,10, length=N)
nu <- 1:10
grid<-expand.grid(x,nu)

fun<-function(xnu){x<-xnu[1]; nu<-xnu[2]; c(besselI(x,nu), besselK(x,nu), besselJ(x,nu), besselY(x,nu))}

res<-t(apply(grid,1,fun))

out<-cbind(grid, res)

cat("# n\n",nrow(out),"\n",file="bessel.dat")
write.table(format(out, digits=22), file="bessel.dat", append=TRUE, row.names=FALSE, col.names=FALSE, quote=FALSE)

