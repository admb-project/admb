x_s = 20.5
x_v = c(0.1, 10, 19)
a_s = 10.9
a_v = c(0.2, 10.9, 50)
b_s = 3.4
b_v = c(0.5, 3.4, 22)
c_s = 9.9
c_v = c(0.9, 9.9, 55)
theta = 0.6

x_s_nrh = 0.5
x_v_nrh = c(0.1, 0.2, 0.22)
a_s_nrh = 1.9
a_v_nrh = c(0.2, 1.1, 1.5)
b_s_nrh = 3.4
b_v_nrh = c(5, 3.4, 2)
c_s_nrh = 9.9
c_v_nrh = c(90, 99, 55)

write.table(c(length(x_v),x_s,x_v,x_s_nrh,x_v_nrh), file="tests.dat", quote=FALSE, row.names=FALSE, col.names=FALSE)
write.table(c(a_s,a_v,b_s,b_v,c_s,c_v,theta,a_s_nrh,a_v_nrh,b_s_nrh,b_v_nrh,c_s_nrh,c_v_nrh), file="tests.pin", quote=FALSE, row.names=FALSE, col.names=FALSE)

mm1=function(x,a,b){a*x/(b+x)}
mm2=function(x,a,b){a*x/(a/b+x)}
hill=function(x,a,b,n){a*x^n/(1+b*x^n)}
holling2=function(x,alpha,h){alpha*x/(1+alpha*h*x)}
holling3=function(x,a,b){a*x^2/(b^2+x^2)}
holling4=function(x,a,b,c){a*x^2/(b+c*x+x^2)}
monomolecular=function(x,a,b){a*(1-exp(-b*x))}
logistic=function(x,a,b){exp(a+b*x)/(1+exp(a+b*x))}
logisticK=function(t,K,r,n0){K/(1+(K/n0-1)*exp(-r*t))}
logistic3=function(x,a,b,c){c/(1+exp(-(a+b*x)))}
theta_logistic=function(t,K,r,n0,theta){(K^(-theta)+(n0^(-theta)-K^(-theta))*exp(-r*theta*t))^(-1/theta)}
Ricker=function(x,a,b){a*x*exp(-b*x)}
generalized_Ricker1=function(x,x0,A,alpha){A*(x/x0*exp(1-x/x0))^alpha}
generalized_Ricker2=function(x,r,a,alpha){x*exp(r*(1-(a/x)^alpha))}
nonrectangular_hyperbola=function(x, theta, alpha, pmax){1/(2*theta)*(alpha*x+pmax-sqrt((alpha*x+pmax)^2-4*theta*alpha*x*pmax))}
Gompertz=function(x,a,b){exp(-a*exp(-b*x))} 
Shepherd=function(x,a,b,c){a*x/(b+x^c)}
Hassell=function(x,a,b,c){a*x/(b+x)^c}
	
write.table(c(
#	"mm1",
	mm1(x_s,a_s,b_s),
	mm1(x_v,a_s,b_v),
	mm1(x_v,a_v,b_s),
	mm1(x_v,a_v,b_v),
#	"mm2",
	mm2(x_s,a_s,b_s),
	mm2(x_v,a_s,b_v),
	mm2(x_v,a_v,b_s),
	mm2(x_v,a_v,b_v),
#	"hill",
	hill(x_s,a_s,b_s,c_s),
	hill(x_v,a_v,b_s,c_s),
	hill(x_v,a_v,b_v,c_s),
	hill(x_v,a_v,b_s,c_v),
	hill(x_v,a_v,b_v,c_v),
	hill(x_v,a_s,b_v,c_s),
	hill(x_v,a_s,b_v,c_v),
	hill(x_v,a_s,b_s,c_v),
#	"holling2",
	holling2(x_s,a_s,b_s),
	holling2(x_v,a_s,b_v),
	holling2(x_v,a_v,b_s),
	holling2(x_v,a_v,b_v),
#	"holling3",
	holling3(x_s,a_s,b_s),
	holling3(x_v,a_s,b_v),
	holling3(x_v,a_v,b_s),
	holling3(x_v,a_v,b_v),
#	"holling4",
	holling4(x_s,a_s,b_s,c_s),
	holling4(x_v,a_v,b_s,c_s),
	holling4(x_v,a_v,b_v,c_s),
	holling4(x_v,a_v,b_s,c_v),
	holling4(x_v,a_v,b_v,c_v),
	holling4(x_v,a_s,b_v,c_s),
	holling4(x_v,a_s,b_v,c_v),
	holling4(x_v,a_s,b_s,c_v),
#	"monomolecular",
	monomolecular(x_s,a_s,b_s),
	monomolecular(x_v,a_s,b_v),
	monomolecular(x_v,a_v,b_s),
	monomolecular(x_v,a_v,b_v),
#	"logistic",
	logistic(x_s,a_s,b_s),
	logistic(x_v,a_s,b_v),
	logistic(x_v,a_v,b_s),
	logistic(x_v,a_v,b_v),
#	"logisticK",
	logisticK(x_s,a_s,b_s,c_s),
	logisticK(x_v,a_v,b_s,c_s),
	logisticK(x_v,a_v,b_v,c_s),
	logisticK(x_v,a_v,b_s,c_v),
	logisticK(x_v,a_v,b_v,c_v),
	logisticK(x_v,a_s,b_v,c_s),
	logisticK(x_v,a_s,b_v,c_v),
	logisticK(x_v,a_s,b_s,c_v),
#	"logistic3",
	logistic3(x_s,a_s,b_s,c_s),
	logistic3(x_v,a_v,b_s,c_s),
	logistic3(x_v,a_v,b_v,c_s),
	logistic3(x_v,a_v,b_s,c_v),
	logistic3(x_v,a_v,b_v,c_v),
	logistic3(x_v,a_s,b_v,c_s),
	logistic3(x_v,a_s,b_v,c_v),
	logistic3(x_v,a_s,b_s,c_v),
#	"theta_logistic",
	theta_logistic(x_s,a_s,b_s,c_s,theta),
	theta_logistic(x_v,a_v,b_s,c_s,theta),
	theta_logistic(x_v,a_v,b_v,c_s,theta),
	theta_logistic(x_v,a_v,b_s,c_v,theta),
	theta_logistic(x_v,a_v,b_v,c_v,theta),
	theta_logistic(x_v,a_s,b_v,c_s,theta),
	theta_logistic(x_v,a_s,b_v,c_v,theta),
	theta_logistic(x_v,a_s,b_s,c_v,theta),
#	"Ricker",
	Ricker(x_s,a_s,b_s),
	Ricker(x_v,a_s,b_v),
	Ricker(x_v,a_v,b_s),
	Ricker(x_v,a_v,b_v),
#	generalized_Ricker1
	generalized_Ricker1(x_s,a_s,b_s,c_s),
	generalized_Ricker1(x_v,a_v,b_s,c_s),
	generalized_Ricker1(x_v,a_v,b_v,c_s),
	generalized_Ricker1(x_v,a_v,b_s,c_v),
	generalized_Ricker1(x_v,a_v,b_v,c_v),
	generalized_Ricker1(x_v,a_s,b_v,c_s),
	generalized_Ricker1(x_v,a_s,b_v,c_v),
	generalized_Ricker1(x_v,a_s,b_s,c_v),
#	generalized_Ricker2
	generalized_Ricker2(x_s,a_s,b_s,c_s),
	generalized_Ricker2(x_v,a_v,b_s,c_s),
	generalized_Ricker2(x_v,a_v,b_v,c_s),
	generalized_Ricker2(x_v,a_v,b_s,c_v),
	generalized_Ricker2(x_v,a_v,b_v,c_v),
	generalized_Ricker2(x_v,a_s,b_v,c_s),
	generalized_Ricker2(x_v,a_s,b_v,c_v),
	generalized_Ricker2(x_v,a_s,b_s,c_v),
#	nonrectangular_hyperbola                            
	nonrectangular_hyperbola(x_s_nrh,a_s_nrh,b_s_nrh,c_s_nrh),
	nonrectangular_hyperbola(x_v_nrh,a_v_nrh,b_s_nrh,c_s_nrh),
	nonrectangular_hyperbola(x_v_nrh,a_v_nrh,b_v_nrh,c_s_nrh),
	nonrectangular_hyperbola(x_v_nrh,a_v_nrh,b_s_nrh,c_v_nrh),
	nonrectangular_hyperbola(x_v_nrh,a_v_nrh,b_v_nrh,c_v_nrh),
	nonrectangular_hyperbola(x_v_nrh,a_s_nrh,b_v_nrh,c_s_nrh),
	nonrectangular_hyperbola(x_v_nrh,a_s_nrh,b_v_nrh,c_v_nrh),
	nonrectangular_hyperbola(x_v_nrh,a_s_nrh,b_s_nrh,c_v_nrh),
#	Gompertz                            
	Gompertz(x_s,a_s,b_s),
	Gompertz(x_v,a_s,b_v),
	Gompertz(x_v,a_v,b_s),
	Gompertz(x_v,a_v,b_v),
#	Shepherd
	Shepherd(x_s,a_s,b_s,c_s),
	Shepherd(x_v,a_v,b_s,c_s),
	Shepherd(x_v,a_v,b_v,c_s),
	Shepherd(x_v,a_v,b_s,c_v),
	Shepherd(x_v,a_v,b_v,c_v),
	Shepherd(x_v,a_s,b_v,c_s),
	Shepherd(x_v,a_s,b_v,c_v),
	Shepherd(x_v,a_s,b_s,c_v),
#	Hassell
	Hassell(x_s,a_s,b_s,c_s),
	Hassell(x_v,a_v,b_s,c_s),
	Hassell(x_v,a_v,b_v,c_s),
	Hassell(x_v,a_v,b_s,c_v),
	Hassell(x_v,a_v,b_v,c_v),
	Hassell(x_v,a_s,b_v,c_s),
	Hassell(x_v,a_s,b_v,c_v),
	Hassell(x_v,a_s,b_s,c_v)
	 ), file="results_from_R.txt", row.names=FALSE, quote=FALSE, col.names=FALSE)