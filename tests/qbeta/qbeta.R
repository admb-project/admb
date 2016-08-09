N<-10
options(digits=22)
x<-seq(1.0e-6,1-1.0e-6, length=N)
a<-round(exp(seq(log(0.03),log(500), length=N)),2)
b<-round(exp(seq(log(0.03),log(500), length=N)),2)
grid<-expand.grid(x,a,b)

res<-qbeta(grid[,1],grid[,2],grid[,3])

out<-cbind(grid, res)

cat("# n\n",nrow(out),"\n",file="qbeta.dat")
write.table(format(out, digits=22), file="qbeta.dat", append=TRUE, row.names=FALSE, col.names=FALSE, quote=FALSE)
 
