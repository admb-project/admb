######################
###Michaelis_Menten1###
#######################
#function;				Michaelis Menten function, 1st parametarization;
#\f$  \f$				\f$ \frac{ax}{b+x} \f$
#func(					Michaelis_Menten1(
#//calculate y(s,s,s)	y=a*x/(b+x);
#//calculate y(v,s,s)	y=a*elem_div(x, b+x);
#//calculate y(v,v,s)	y=elem_prod(a, elem_div(x, b+x));
#//calculate y(v,s,v)	y=a*elem_div(x, b+x);
#//calculate y(v,v,v)	y=elem_prod(a, elem_div(x, b+x));
sed -e 's:function;:Michaelis Menten function, 1st parametarization;:g'\
	-e 's:\\f\$  \\f\$:\\f$ \\frac{ax}{b+x} \\f$ :g'\
	-e 's:func(:Michaelis_Menten1(:g'\
	-e 's://calculate y(s,s,s):y=a*x/(b+x);:g'\
	-e 's://calculate y(v,s,s):y=a*elem_div(x, b+x);:g'\
	-e 's://calculate y(v,v,s):y=elem_prod(a, elem_div(x, b+x));:g'\
	-e 's://calculate y(v,s,v):y=a*elem_div(x, b+x);:g'\
	-e 's://calculate y(v,v,v):y=elem_prod(a, elem_div(x, b+x));:g'\
	template2var.cpp >Michaelis_Menten1.cpp
	
######################
###Michaelis_Menten2###
#######################
#function;				Michaelis Menten function, 2nd parameterization;
#\f$  \f$				\f$ \frac{ax}{a/b+x} \f$
#func(					Michaelis_Menten2(
#//calculate y(s,s,s)	y=a*x/(a/b+x);
#//calculate y(v,s,s)	y=a*elem_div(x, a/b+x);
#//calculate y(v,v,s)	y=elem_prod(a, elem_div(x, a/b+x));
#//calculate y(v,s,v)	y=a*elem_div(x, a/b+x);
#//calculate y(v,v,v)	y=elem_prod(a, elem_div(x, elem_div(a,b)+x));
sed -e 's:function;:Michaelis Menten function, 2nd parameterization;:g'\
	-e 's:\\f\$  \\f\$:\\f$ \\frac{ax}{a/b+x} \\f$ :g'\
	-e 's:func(:Michaelis_Menten2(:g'\
	-e 's://calculate y(s,s,s):y=a*x/(a/b+x);:g'\
	-e 's://calculate y(v,s,s):y=a*elem_div(x, a/b+x);:g'\
	-e 's://calculate y(v,v,s):y=elem_prod(a, elem_div(x, a/b+x));:g'\
	-e 's://calculate y(v,s,v):y=a*elem_div(x, a/b+x);:g'\
	-e 's://calculate y(v,v,v):y=elem_prod(a, elem_div(x, elem_div(a,b)+x));:g'\
	template2var.cpp >Michaelis_Menten2.cpp
##########
###Hill###
##########
#function;					Hill function;
#\f$  \f$					\f$ \frac{ax^c}{1+bx^c} \f$
#func(						Hill(
#//calculate y(s,s,s,s)		y=a*pow(x,c)/(1+b*pow(x,c));
#//calculate y(v,s,s,s)		y=a*elem_div(pow(x,c), 1+b*pow(x,c));
#//calculate y(v,v,s,s)		y=elem_prod(a, elem_div(pow(x,c), 1+b*pow(x,c)));
#//calculate y(v,s,v,s)		y=a*elem_div(pow(x,c), 1+elem_prod(b, pow(x,c)));
#//calculate y(v,v,v,s)		y=elem_prod(a, elem_div(pow(x,c), 1+elem_prod(b, pow(x,c))));
#//calculate y(v,s,s,v)		y=a*elem_div(pow(x,c), 1+b*pow(x,c));
#//calculate y(v,v,s,v)     y=elem_prod(a, elem_div(pow(x,c), 1+b*pow(x,c)));
#//calculate y(v,s,v,v)     y=a*elem_div(pow(x,c), 1+elem_prod(b, pow(x,c)));
#//calculate y(v,v,v,v)     y=elem_prod(a, elem_div(pow(x,c), 1+elem_prod(b, pow(x,c))));
sed -e 's:function;:Hill function;:g'\
	-e 's:\\f\$  \\f\$:\\f\$ \\frac{ax^c}{1+bx^c} \\f$ :g'\
	-e 's:func(:Hill(:g'\
	-e 's://calculate y(s,s,s,s):y=a*pow(x,c)/(1+b*pow(x,c));:g'\
	-e 's://calculate y(v,s,s,s):y=a*elem_div(pow(x,c), 1+b*pow(x,c));:g'\
	-e 's://calculate y(v,v,s,s):y=elem_prod(a, elem_div(pow(x,c), 1+b*pow(x,c)));:g'\
	-e 's://calculate y(v,s,v,s):y=a*elem_div(pow(x,c), 1+elem_prod(b, pow(x,c)));:g'\
	-e 's://calculate y(v,v,v,s):y=elem_prod(a, elem_div(pow(x,c), 1+elem_prod(b, pow(x,c))));:g'\
	-e 's://calculate y(v,s,s,v):y=a*elem_div(pow(x,c), 1+b*pow(x,c));:g'\
	-e 's://calculate y(v,v,s,v):y=elem_prod(a, elem_div(pow(x,c), 1+b*pow(x,c)));:g'\
	-e 's://calculate y(v,s,v,v):y=a*elem_div(pow(x,c), 1+elem_prod(b, pow(x,c)));:g'\
	-e 's://calculate y(v,v,v,v):y=elem_prod(a, elem_div(pow(x,c), 1+elem_prod(b, pow(x,c))));:g'\
	template3var.cpp>Hill.cpp

###############
###HollingII###
###############
#function;				HollingII
#\f$  \f$				\f$ \frac{\alpha x}{1+ \alpha hx} \f$
#func(					HollingII(
#//calculate y(s,s,s)	y=alpha*x/(1.0+alpha*(h*x));
#//calculate y(v,s,s)	y=elem_div(alpha*x, 1.0+alpha*(h*x));
#//calculate y(v,v,s)	y=elem_div(elem_prod(alpha,x), 1.0+elem_prod(alpha, (h*x)));
#//calculate y(v,s,v)	y=elem_div(alpha*x, 1.0+alpha*elem_prod(h,x));
#//calculate y(v,v,v)	y=elem_div(elem_prod(alpha,x), 1.0+elem_prod(alpha, elem_prod(h,x)));
#a ;					alpha ;
#a,						alpha,
#b ;					h ;
#b)						h)
sed -e 's:function;:HollingII:g'\
	-e 's:a ;:alpha ;:g'\
	-e 's:a,:alpha,:g'\
	-e 's:b ;:h ;:g'\
	-e 's:b):h):g'\
	-e 's:\\f\$  \\f\$:\\f\$ \\frac{\alpha x}{1+ \alpha hx} \\f$: g'\
	-e 's:func(:HollingII(:g'\
	-e 's://calculate y(s,s,s):y=alpha*x/(1.0+alpha*(h*x));:g'\
	-e 's://calculate y(v,s,s):y=elem_div(alpha*x, 1.0+alpha*(h*x));:g'\
	-e 's://calculate y(v,v,s):y=elem_div(elem_prod(alpha,x), 1.0+elem_prod(alpha, (h*x)));:g'\
	-e 's://calculate y(v,s,v):y=elem_div(alpha*x, 1.0+alpha*elem_prod(h,x));:g'\
	-e 's://calculate y(v,v,v):y=elem_div(elem_prod(alpha,x), 1.0+elem_prod(alpha, elem_prod(h,x)));:g'\
	template2var.cpp>HollingII.cpp
	
################
###HollingIII###
################
#function;				Holling Type III function;
#\f$  \f$				\f$ \frac{ax^2}{b^2 + x^2} \f$
#func(					HollingIII(
#//calculate y(s,s,s)	y=a*pow(x,2)/(pow(b,2)+pow(x,2));
#//calculate y(v,s,s)	y=a*elem_div(pow(x,2), pow(b,2)+pow(x,2));
#//calculate y(v,v,s)	y=elem_prod(a, elem_div(pow(x,2), pow(b,2)+pow(x,2)));
#//calculate y(v,s,v)	y=a*elem_div(pow(x,2), pow(b,2)+pow(x,2));
#//calculate y(v,v,v)	y=elem_prod(a, elem_div(pow(x,2), pow(b,2)+pow(x,2)));
sed -e 's:function;:Holling Type III function;:g'\
	-e 's:\\f\$  \\f\$:\\f\$ \\frac{ax^2}{b^2 + x^2} \\f$:g'\
	-e 's:func(:HollingIII(:g'\
	-e 's://calculate y(s,s,s):y=a*pow(x,2)/(pow(b,2)+pow(x,2));:g'\
	-e 's://calculate y(v,s,s):y=a*elem_div(pow(x,2), pow(b,2)+pow(x,2));:g'\
	-e 's://calculate y(v,v,s):y=elem_prod(a, elem_div(pow(x,2), pow(b,2)+pow(x,2)));:g'\
	-e 's://calculate y(v,s,v):y=a*elem_div(pow(x,2), pow(b,2)+pow(x,2));:g'\
	-e 's://calculate y(v,v,v):y=elem_prod(a, elem_div(pow(x,2), pow(b,2)+pow(x,2)));:g'\
	template2var.cpp>HollingIII.cpp

################
###HollingIV###
################
#function;					Holling Type IV function;
#\f$  \f$					\f$ \frac{ax^2}{b + cx + x^2} \f$
#func(						HollingIV(
#//calculate y(s,s,s,s)		y=a*pow(x,2)/(b+c*x+pow(x,2));
#//calculate y(v,s,s,s)		y=a*elem_div(pow(x,2), b+c*x+pow(x,2));
#//calculate y(v,v,s,s)		y=elem_prod(a, elem_div(pow(x,2), b+c*x+pow(x,2)));
#//calculate y(v,s,v,s)		y=a*elem_div(pow(x,2), b+c*x+pow(x,2));
#//calculate y(v,v,v,s)		y=elem_prod(a, elem_div(pow(x,2), b+c*x+pow(x,2)));
#//calculate y(v,s,s,v)		y=a*elem_div(pow(x,2), b+elem_prod(c,x)+pow(x,2));
#//calculate y(v,v,s,v)		y=elem_prod(a, elem_div(pow(x,2), b+elem_prod(c,x)+pow(x,2)));
#//calculate y(v,s,v,v)		y= a* elem_div(pow(x,2), b+elem_prod(c,x)+pow(x,2));
#//calculate y(v,v,v,v)		y=elem_prod(a, elem_div(pow(x,2), b+elem_prod(c,x)+pow(x,2)));
sed -e 's:function;:Holling Type IV function;: g' \
	-e 's:\\f\$  \\f\$:\\f\$ \\frac{ax^2}{b + cx + x^2} \\f$: g' \
	-e 's:func(:HollingIV(: g' \
	-e 's://calculate y(s,s,s,s):y=a*pow(x,2)/(b+c*x+pow(x,2));: g' \
	-e 's://calculate y(v,s,s,s):y=a*elem_div(pow(x,2), b+c*x+pow(x,2));: g' \
	-e 's://calculate y(v,v,s,s):y=elem_prod(a, elem_div(pow(x,2), b+c*x+pow(x,2)));: g' \
	-e 's://calculate y(v,s,v,s):y=a*elem_div(pow(x,2), b+c*x+pow(x,2));: g' \
	-e 's://calculate y(v,v,v,s):y=elem_prod(a, elem_div(pow(x,2), b+c*x+pow(x,2)));: g' \
	-e 's://calculate y(v,s,s,v):y=a*elem_div(pow(x,2), b+elem_prod(c,x)+pow(x,2));: g' \
	-e 's://calculate y(v,v,s,v):y=elem_prod(a, elem_div(pow(x,2), b+elem_prod(c,x)+pow(x,2)));: g' \
	-e 's://calculate y(v,s,v,v):y= a* elem_div(pow(x,2), b+elem_prod(c,x)+pow(x,2));: g' \
	-e 's://calculate y(v,v,v,v):y=elem_prod(a, elem_div(pow(x,2), b+elem_prod(c,x)+pow(x,2)));: g' \
	template3var.cpp>HollingIV.cpp

###################
###monomolecular###
###################
#function;					monomolecular function;
#\f$  \f$					\f$ a(1-e^{-bx}) \f$
#func(						monomolecular(
#//calculate y(s,s,s)		y=a*(1.0-exp(-b*x));
#//calculate y(v,s,s)		y=a*(1.0-exp(-b*x));
#//calculate y(v,v,s)		y=elem_prod(a, 1.0-exp(-b*x));
#//calculate y(v,s,v)		y=a*(1.0-exp(-1.0*elem_prod(b, x)));
#//calculate y(v,v,v)		y=elem_prod(a, 1.0-exp(-1.0*elem_prod(b, x)));
sed -e 's:function; : monomoleular function; : g' \
	-e 's:\\f\$  \\f\$:\\f$ a(1-e^{-bx}) \\f$ :g' \
	-e 's:func(:monomolecular(:g' \
	-e 's://calculate y(s,s,s):y=a*(1.0-exp(-b*x)); :g' \
	-e 's://calculate y(v,s,s):y=a*(1.0-exp(-b*x)); :g' \
	-e 's://calculate y(v,v,s):y=elem_prod(a, 1.0-exp(-b*x)); :g' \
	-e 's://calculate y(v,s,v):y=a*(1.0-exp(-1.0*elem_prod(b,x))); :g' \
	-e 's://calculate y(v,v,v):y=elem_prod(a, 1.0-exp(-1.0*elem_prod(b,x))); :g' \
	template2var.cpp >monomolecular.cpp
	
##############	
###logistic###
##############
#function;					logistic function;
#\f$  \f$					\f$ \frac{e^{a+bx}}{(1+e^{a+bx})} \f$
#func(						logistic(
#//calculate y(s,s,s)		y=exp(a+b*x)/(1+exp(a+b*x));
#//calculate y(v,s,s)		y=elem_div(exp(a+b*x), 1+exp(a+b*x));
#//calculate y(v,v,s)		y=elem_div(exp(a+b*x), 1+exp(a+b*x));
#//calculate y(v,s,v)		y=elem_div(exp(a+elem_prod(b,x)), 1+exp(a+elem_prod(b,x)));
#//calculate y(v,v,v)		y=elem_div(exp(a+elem_prod(b,x)), 1+exp(a+elem_prod(b,x)));
sed -e 's:function;:logistic function;:g' \
	-e 's:\\f\$  \\f\$:\\f$ \\frac{e^{a+bx}}{(1+e^{a+bx})} \\f$:g' \
	-e 's:func(:logistic(:g' \
	-e 's://calculate y(s,s,s):y=exp(a+b*x)/(1.0+exp(a+b*x));:g' \
	-e 's://calculate y(v,s,s):y=elem_div(exp(a+b*x), 1.0+exp(a+b*x));:g' \
	-e 's://calculate y(v,v,s):y=elem_div(exp(a+b*x), 1.0+exp(a+b*x));:g' \
	-e 's://calculate y(v,s,v):y=elem_div(exp(a+elem_prod(b,x)), 1.0+exp(a+elem_prod(b,x)));:g' \
	-e 's://calculate y(v,v,v):y=elem_div(exp(a+elem_prod(b,x)), 1.0+exp(a+elem_prod(b,x)));:g' \
	template2var.cpp >logistic.cpp
	
###############
###logisticK###
###############
#function;					ecologically parameterized logistic function with carrying capacity K;
#\f$  \f$					\f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$
#func(						logisticK(
#//calculate y(s,s,s,s)		y=K/(1.0+(K/n0-1.0)*exp(-r*t));
#//calculate y(v,s,s,s)     y=K/(1.0+(K/n0-1.0)*exp(-r*t));
#//calculate y(v,v,s,s)     y=elem_div(K, 1.0 + elem_prod(K/n0-1.0, exp(-r*t)));
#//calculate y(v,s,v,s)     y=K/(1.0+(K/n0-1.0)*exp(-1.0*elem_prod(r,t)));
#//calculate y(v,v,v,s)     y=elem_div(K, 1.0+elem_prod(K/n0-1.0, exp(-1.0*elem_prod(r,t)));
#//calculate y(v,s,s,v)     y=K/(1.0+elem_prod((K/n0-1.0), exp(-r*t)));
#//calculate y(v,v,s,v)     y=elem_div(K, 1.0 + elem_prod(elem_div(K, n0)-1.0, exp(-r*t)));
#//calculate y(v,s,v,v)     y=K/(1.0+elem_prod(K/n0-1.0, exp(-1.0*elem_prod(r,t))));
#//calculate y(v,v,v,v)     y=elem_div(K, 1.0 + elem_prod(elem_div(K, n0)-1.0, exp(-1.0*elem_prod(r,t))));
#a ;						K ;
#b ;						r ;
#c ;						n0 ;
#a,							K,
#b,							r,
#c)							n0)
#x independent				t independent
#x,							t,
sed -e 's:function;:ecologically parameterized logistic function with carrying capacity K; :g' \
    -e 's:a ;:K carrying capacity;: g'\
    -e 's:b ;:r growth rate;: g'\
    -e 's:c ;:n0 initial population size at t=0;: g'\
    -e 's:a,:K,: g'\
    -e 's:b,:r,: g'\
    -e 's:c):n0): g'\
    -e 's:x independent:t independent: g'\
    -e 's:x,:t,: g'\
	-e 's:\\f\$  \\f\$:\\f\$ \\frac{K}{1+(\\frac{K}{n0}-1)e^{-rt}} \\f$ :g' \
	-e 's:func(:logisticK( :g' \
	-e 's://calculate y(s,s,s,s):y=K/(1.0+(K/n0-1.0)*exp(-r*t)); :g'\
	-e 's://calculate y(v,s,s,s):y=K/(1.0+(K/n0-1.0)*exp(-r*t)); :g'\
	-e 's://calculate y(v,v,s,s):y=elem_div(K, 1.0 + elem_prod(K/n0-1.0, exp(-r*t))); : g'\
	-e 's://calculate y(v,s,v,s):y=K/(1.0+(K/n0-1.0)*exp(-1.0*elem_prod(r,t))); : g'\
	-e 's://calculate y(v,v,v,s):y=elem_div(K, 1.0 + elem_prod(K/n0-1.0, exp(-1.0*elem_prod(r,t)))); : g'\
	-e 's://calculate y(v,s,s,v):y=K/(1.0+elem_prod((K/n0-1.0), exp(-r*t))); : g'\
	-e 's://calculate y(v,v,s,v):y=elem_div(K, 1.0 + elem_prod(elem_div(K, n0)-1.0, exp(-r*t))); : g'\
	-e 's://calculate y(v,s,v,v):y=K/(1.0+elem_prod(K/n0-1.0, exp(-1.0*elem_prod(r,t)))); : g'\
    -e 's://calculate y(v,v,v,v):y=elem_div(K, 1.0 + elem_prod(elem_div(K, n0)-1.0, exp(-1.0*elem_prod(r,t)))); : g'\
	template3var.cpp >logisticK.cpp
	
#-e 's://calculate y(v,s,s,v):y=K/(1.0+(K/n0-1.0)*exp(-r*t)); : g'\	
#-e 's://calculate y(v,s,s,v):y=K/(1.0+elem_prod((K/n0-1.0), exp(-r*t))); : g'\
	
###############
###logistic3###
###############
#function;					logistic function with carrying capacity c;
#\f$  \f$					\f$ \frac{c}{1+e^{-(a+bx)}} \f$
#func(						logistic3(
#//calculate y(s,s,s,s)		y=c/(1.0+exp(-(a+b*x)));
#//calculate y(v,s,s,s)		y=c/(1.0+exp(-(a+b*x)));
#//calculate y(v,v,s,s)		y=c/(1.0+exp(-(a+b*x)));
#//calculate y(v,s,v,s)		y=c/(1.0+exp(-(a+elem_prod(b, x))));
#//calculate y(v,v,v,s)		y=c/(1.0+exp(-(a+elem_prod(b, x))));
#//calculate y(v,s,s,v)		y=elem_div(c, 1.0+exp(-(a+b*x)));
#//calculate y(v,v,s,v)		y=elem_div(c, 1.0+exp(-(a+b*x)));
#//calculate y(v,s,v,v)		y=elem_div(c, 1.0+exp(-(a+elem_prod(b, x))));
#//calculate y(v,v,v,v)		y=elem_div(c, 1.0+exp(-(a+elem_prod(b, x))));
#c ;						c carrying capacity;
sed -e 's:function;:logistic function with carrying capacity c;:g'\
	-e 's:\\f\$  \\f\$:\\f$ \\frac{c}{1+e^{-(a+bx)}} \\f$:	g'\
	-e 's:func(:logistic3(:g'\
	-e 's://calculate y(s,s,s,s):y=c/(1.0+exp(-(a+b*x)));:g'\
	-e 's://calculate y(v,s,s,s):y=c/(1.0+exp(-(a+b*x)));:g'\
	-e 's://calculate y(v,v,s,s):y=c/(1.0+exp(-(a+b*x)));:g'\
	-e 's://calculate y(v,s,v,s):y=c/(1.0+exp(-(a+elem_prod(b, x))));:g'\
	-e 's://calculate y(v,v,v,s):y=c/(1.0+exp(-(a+elem_prod(b, x))));:g'\
	-e 's://calculate y(v,s,s,v):y=elem_div(c, 1.0+exp(-(a+b*x)));:g'\
	-e 's://calculate y(v,v,s,v):y=elem_div(c, 1.0+exp(-(a+b*x)));:g'\
	-e 's://calculate y(v,s,v,v):y=elem_div(c, 1.0+exp(-(a+elem_prod(b, x))));:g'\
    -e 's://calculate y(v,v,v,v):y=elem_div(c, 1.0+exp(-(a+elem_prod(b, x))));:g'\
    -e 's:c ;:c carrying capacity;:g'\
	template3var.cpp >logistic3.cpp
	
####################
###theta_logistic###
####################
#function;					theta logistic function;
#\f$  \f$					\f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$			
#func(						theta_logistic(
#//calculate y(s,s,s,s)		y=pow(pow(K, -theta) + (pow(n0, -theta) - pow(K, -theta))*exp(-(r*t)*theta), -1.0/theta);
#//calculate y(v,s,s,s)     y=pow(pow(K, -theta) + (pow(n0, -theta) - pow(K, -theta))*exp(-(r*t)*theta), -1.0/theta);
#//calculate y(v,v,s,s)     y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-(r*t)*theta)), -1.0/theta);
#//calculate y(v,s,v,s)     y=pow(pow(K, -theta) + (pow(n0, -theta) - pow(K, -theta))*exp(-1.0*elem_prod(r, t)*theta), -1.0/theta);
#//calculate y(v,v,v,s)     y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-1.0*elem_prod(r, t)*theta)),-1.0/theta);
#//calculate y(v,s,s,v)     y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-(r*t)*theta)), -1.0/theta);
#//calculate y(v,v,s,v)     y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-(r*t)*theta)), -1.0/theta);
#//calculate y(v,s,v,v)     y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-1.0*elem_prod(r, t)*theta)),-1.0/theta);
#//calculate y(v,v,v,v)     y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-1.0*elem_prod(r, t)*theta)),-1.0/theta);
#a ;						K ;
#b ;				        r ;
#c ;				        n0 ;
#a,					        K,
#b,					        r,
#c)					        n0, theta)
#x independent		        t independent
#x,					        t,
sed -e 's:function;:theta logistic function;:g'\
	-e 's:a ;:K carrying capacity; :g'\
	-e 's:b ;:r growth rate;: g'\
	-e 's:c ;:n0 population size at t=0; : g'\
	-e 's:a,:K,: g'\
	-e 's:b,:r,: g'\
	-e 's:x independent:t independent: g'\
	-e 's:x,:t,: g'\
	-e 's:\\f\$  \\f\$:\\f\$ (K^{-\\theta}+(n0^{-\\theta}-K^{-\\theta})e^{-r\\theta t})^{-1/\\theta} \\f\$ :g'\
	-e 's:func(:theta_logistic(:g'\
	-e 's://calculate y(s,s,s,s):y=pow(pow(K, -theta) + (pow(n0, -theta) - pow(K, -theta))*exp(-(r*t)*theta), -1.0/theta); :g'\
	-e 's://calculate y(v,s,s,s):y=pow(pow(K, -theta) + (pow(n0, -theta) - pow(K, -theta))*exp(-(r*t)*theta), -1.0/theta); :g'\
	-e 's://calculate y(v,v,s,s):y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-(r*t)*theta)), -1.0/theta); :g'\
	-e 's://calculate y(v,s,v,s):y=pow(pow(K, -theta) + (pow(n0, -theta) - pow(K, -theta))*exp(-1.0*elem_prod(r, t)*theta), -1.0/theta); :g'\
	-e 's://calculate y(v,v,v,s):y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-1.0*elem_prod(r, t)*theta)),-1.0/theta); :g'\
	-e 's://calculate y(v,s,s,v):y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-(r*t)*theta)), -1.0/theta); :g'\
	-e 's://calculate y(v,v,s,v):y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-(r*t)*theta)), -1.0/theta); :g'\
	-e 's://calculate y(v,s,v,v):y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-1.0*elem_prod(r, t)*theta)),-1.0/theta); :g'\
	-e 's://calculate y(v,v,v,v):y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-1.0*elem_prod(r, t)*theta)),-1.0/theta); :g'\
	-e 's:df1b2vector\& c):df1b2vector\& n0, const df1b2variable\& theta): g'\
	-e 's:df1b2variable\& c):df1b2variable\& n0, const df1b2variable\& theta): g'\
	-e 's:prevariable\& c):prevariable\& n0, const prevariable\& theta): g'\
	-e 's:dvar_vector\& c):dvar_vector\& n0, const prevariable\& theta): g'\
	template3var.cpp >theta_logistic.cpp
#TODO add theta to parameter section in a new line in theta logistic


############
###Ricker###
############
#function;				Ricker function;
#\f$  \f$				\f$ axe^{-bx} \f$
#func(					Ricker(
#//calculate y(s,s,s)	y=a*x*exp(-b*x);
#//calculate y(v,s,s)	y=a*elem_prod(x, exp(-b*x));
#//calculate y(v,v,s)	y=elem_prod(a, elem_prod(x, exp(-b*x)));
#//calculate y(v,s,v)	y=a*elem_prod(x, exp(-1.0*elem_prod(b, x)));
#//calculate y(v,v,v)	y=elem_prod(a, elem_prod(x, exp(-1.0*elem_prod(b, x))));
sed -e 's:function;:Ricker function;:g'\
	-e 's:\\f\$  \\f\$:\\f$ axe^{-bx} \\f$:g'\
	-e 's:func(:Ricker(:g'\
	-e 's://calculate y(s,s,s):y=a*x*exp(-b*x);:g'\
	-e 's://calculate y(v,s,s):y=a*elem_prod(x, exp(-b*x));:g'\
	-e 's://calculate y(v,v,s):y=elem_prod(a, elem_prod(x, exp(-b*x)));:g'\
	-e 's://calculate y(v,s,v):y=a*elem_prod(x, exp(-1.0*elem_prod(b, x)));:g'\
	-e 's://calculate y(v,v,v):y=elem_prod(a, elem_prod(x, exp(-1.0*elem_prod(b, x))));:g'\
	template2var.cpp >Ricker.cpp	
	
#########################
###generalized_Ricker1###
#########################
#function;			   		generalized Ricker function, first parameerization;
#\f$  \f$					\f$ A(\frac{x}{x0}e^{(1-\frac{x}{x0})})^{\alpha} \f$
#func(						generalized_Ricker1(
#//calculate y(s,s,s,s)		y=A*pow((x/x0*exp(1-x/x0)), alpha);
#//calculate y(v,s,s,s)		y=A*pow(elem_prod(x/x0, exp(1-x/x0)), alpha);
#//calculate y(v,v,s,s)		y=A*pow(elem_prod(elem_div(x, x0), exp(1-elem_div(x, x0))), alpha);
#//calculate y(v,s,v,s)		y=elem_prod(A, pow(elem_prod(x/x0, exp(1-x/x0)), alpha));
#//calculate y(v,v,v,s)		y=elem_prod(A, pow(elem_prod(elem_div(x, x0), exp(1.0-elem_div(x, x0))), alpha));
#//calculate y(v,s,s,v)		y=A*pow(elem_prod(x/x0, exp(1-x/x0)), alpha);
#//calculate y(v,v,s,v)		y=A*pow(elem_prod(elem_div(x, x0), exp(1-elem_div(x, x0))), alpha);
#//calculate y(v,s,v,v)		y=elem_prod(A, pow(elem_prod(x/x0, exp(1-x/x0)), alpha));
#//calculate y(v,v,v,v)		y=elem_prod(A, pow(elem_prod(elem_div(x, x0), exp(1.0-elem_div(x, x0))), alpha));
#a ;						x0 ;	
#b ;				   		A ;
#c ;				   		alpha ;
#a,					   		x0,
#b,					   		A,
#c)					   		alpha)
sed -e 's:function;:generalized Ricker function, first parameerization;:g'\
	-e 's:a ;:x0 ;:g'\
	-e 's:b ;:A ;:g'\
	-e 's:c ;:alpha ;:g'\
	-e 's:a,:x0,:g'\
	-e 's:b,:A,:g'\
	-e 's:c):alpha):g'\
	-e 's:\\f\$  \\f\$:\\f\$ A(\\frac{x}{x0}e^{(1.0-\\frac{x}{x0})})^{\\alpha} \\f\$:g'\
	-e 's:func(:generalized_Ricker1(:g'\
	-e 's://calculate y(s,s,s,s):y=A*pow((x/x0*exp(1.0-x/x0)), alpha);:g'\
	-e 's://calculate y(v,s,s,s):y=A*pow(elem_prod(x/x0, exp(1.0-x/x0)), alpha);:g'\
	-e 's://calculate y(v,v,s,s):y=A*pow(elem_prod(elem_div(x, x0), exp(1.0-elem_div(x, x0))), alpha);:g'\
	-e 's://calculate y(v,s,v,s):y=elem_prod(A, pow(elem_prod(x/x0, exp(1.0-x/x0)), alpha));:g'\
	-e 's://calculate y(v,v,v,s):y=elem_prod(A, pow(elem_prod(elem_div(x, x0), exp(1.0-elem_div(x, x0))), alpha));:g'\
	-e 's://calculate y(v,s,s,v):y=A*pow(elem_prod(x/x0, exp(1.0-x/x0)), alpha);:g'\
	-e 's://calculate y(v,v,s,v):y=A*pow(elem_prod(elem_div(x, x0), exp(1.0-elem_div(x, x0))), alpha);:g'\
	-e 's://calculate y(v,s,v,v):y=elem_prod(A, pow(elem_prod(x/x0, exp(1.0-x/x0)), alpha));:g'\
	-e 's://calculate y(v,v,v,v):y=elem_prod(A, pow(elem_prod(elem_div(x, x0), exp(1.0-elem_div(x, x0))), alpha));:g'\
	template3var.cpp >generalized_Ricker1.cpp

#########################
###generalized_Ricker2###
#########################
#function;			   		generalized Ricker function, second parameerization;
#\f$  \f$					\f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
#func(						generalized_Ricker2(
#//calculate y(s,s,s,s)		y=x*exp(r*(1.0-pow(a/x, alpha)));
#//calculate y(v,s,s,s)		y=elem_prod(x, exp(r*(1.0-pow(a/x, alpha))));
#//calculate y(v,v,s,s)		y=elem_prod(x, exp(elem_prod(r, (1.0-pow(a/x, alpha)))));
#//calculate y(v,s,v,s)		y=elem_prod(x, exp(r*(1.0-pow(elem_div(a, x), alpha))));
#//calculate y(v,v,v,s)		y=elem_prod(x, exp(elem_prod(r, (1.0-pow(elem_div(a, x), alpha)))));
#//calculate y(v,s,s,v)		y=elem_prod(x, exp(r*(1.0-pow(a/x, alpha))));
#//calculate y(v,v,s,v)		y=elem_prod(x, exp(elem_prod(r, (1.0-pow(a/x, alpha)))));
#//calculate y(v,s,v,v)		y=elem_prod(x, exp(r*(1.0-pow(elem_div(a, x), alpha))));
#//calculate y(v,v,v,v)		y=elem_prod(x, exp(elem_prod(r, (1.0-pow(elem_div(a, x), alpha)))));
#a ;						r ;	
#b ;				   		a ;
#c ;				   		alpha ;
#a,					   		r,
#b,					   		a,
#c)					   		alpha)
sed -e 's:function;:generalized Ricker function, second parameerization;:g'\
	-e 's:a ;:r ;:g'\
	-e 's:b ;:a ;:g'\
	-e 's:c ;:alpha ;:g'\
	-e 's:a,:r,:g'\
	-e 's:b,:a,:g'\
	-e 's:c):alpha):g'\
	-e 's:\\f\$  \\f\$:\\f\$ xe^{r(1-(\\frac{a}{x})^\\alpha)} \\f\$:g'\
	-e 's:func(:generalized_Ricker2(:g'\
	-e 's://calculate y(s,s,s,s):y=x*exp(r*(1.0-pow(a/x, alpha)));:g'\
	-e 's://calculate y(v,s,s,s):y=elem_prod(x, exp(r*(1.0-pow(a*pow(x, -1.0), alpha))));:g'\
	-e 's://calculate y(v,v,s,s):y=elem_prod(x, exp(elem_prod(r, (1.0-pow(a*pow(x, -1.0), alpha)))));:g'\
	-e 's://calculate y(v,s,v,s):y=elem_prod(x, exp(r*(1.0-pow(elem_div(a, x), alpha))));:g'\
	-e 's://calculate y(v,v,v,s):y=elem_prod(x, exp(elem_prod(r, (1.0-pow(elem_div(a, x), alpha)))));:g'\
	-e 's://calculate y(v,s,s,v):y=elem_prod(x, exp(r*(1.0-pow(a*pow(x, -1.0), alpha))));:g'\
	-e 's://calculate y(v,v,s,v):y=elem_prod(x, exp(elem_prod(r, (1.0-pow(a*pow(x, -1.0), alpha)))));:g'\
	-e 's://calculate y(v,s,v,v):y=elem_prod(x, exp(r*(1.0-pow(elem_div(a, x), alpha))));:g'\
	-e 's://calculate y(v,v,v,v):y=elem_prod(x, exp(elem_prod(r, (1.0-pow(elem_div(a, x), alpha)))));:g'\
	template3var.cpp >generalized_Ricker2.cpp
	
##################
###power_Ricker###
##################

####################
###vonBertalanffy###
####################

##############################
###nonrectangular_hyperbola###
###############################
#a ;						theta ;
#a,							theta,
#b ;						alpha ;
#b,							alpha,
#c ;						pmax ;
#c)  						pmax) 			
#function;					nonrectangular hyperbolic function;
#\f$  \f$					\f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
#func(						nonrectangular_hyperbola(
#//calculate y(s,s,s,s)		y=pow(2.0*theta, -1.0)*(alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*theta*alpha*x*pmax, 0));
#//calculate y(v,s,s,s)		y=pow(2.0*theta, -1.0)*(alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*theta*alpha*x*pmax, 0));
#//calculate y(v,v,s,s)		y=elem_prod(pow(2.0*theta, -1.0), (alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*elem_prod(theta, x)*alpha*pmax, 0)));
#//calculate y(v,s,v,s)		y=pow(2.0*theta, -1.0)*(elem_prod(alpha, x)+pmax-pow(pow(elem_prod(alpha, x)+pmax, 2.0) - 4.0*theta*elem_prod(alpha, x)*pmax, 0));
#//calculate y(v,v,v,s)		y=elem_prod(pow(2.0*theta, -1.0), (elem_prod(alpha, x)+pmax-pow(pow(elem_prod(alpha, x)+pmax, 2.0) - 4.0*elem_prod(theta, elem_prod(alpha, x))*pmax, 0)));
#//calculate y(v,s,s,v)		y=pow(2.0*theta, -1.0)*(alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*theta*alpha*elem_prod(x, pmax), 0));
#//calculate y(v,v,s,v)		y=elem_prod(pow(2.0*theta, -1.0), (alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*elem_prod(elem_prod(theta, x), pmax)*alpha, 0)));
#//calculate y(v,s,v,v)		y=pow(2.0*theta, -1.0)*(elem_prod(alpha, x)+pmax-pow(pow(elem_prod(alpha, x)+pmax, 2.0) - 4.0*theta*elem_prod(elem_prod(alpha, x), pmax), 0));
#//calculate y(v,v,v,v)		y=elem_prod(pow(2.0*theta, -1.0), (elem_prod(alpha, x)+pmax-pow(pow(elem_prod(alpha, x)+pmax, 2.0) - 4.0*elem_prod(elem_prod(theta, elem_prod(alpha, x)), pmax), 0)));
sed -e 's:a ;:theta ;:g'\
	-e 's:a,:theta,:g'\
	-e 's:b ;:alpha ;:g'\
	-e 's:b,:alpha,:g'\
	-e 's:c ;:pmax ;:g'\
	-e 's:c):pmax):g'\
	-e 's:function;:nonrectangular hyperbolic function;:g'\
	-e 's:\\f\$  \\f\$:\\f\$ \\frac{1}{2\\theta} (\\alpha x +p_{max} - \\sqrt{(\\alpha x +p_{max})^2-4\\theta \\alpha x p_{max}}) \\f\$:g'\
	-e 's:func(:nonrectangular_hyperbola(:g'\
	-e 's://calculate y(s,s,s,s):y=pow(2.0*theta, -1.0)*(alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*theta*alpha*x*pmax, 0));:g'\
	-e 's://calculate y(v,s,s,s):y=pow(2.0*theta, -1.0)*(alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*theta*alpha*x*pmax, 0));:g'\
	-e 's://calculate y(v,v,s,s):y=elem_prod(pow(2.0*theta, -1.0), (alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*elem_prod(theta, x)*alpha*pmax, 0)));:g'\
	-e 's://calculate y(v,s,v,s):y=pow(2.0*theta, -1.0)*(elem_prod(alpha, x)+pmax-pow(pow(elem_prod(alpha, x)+pmax, 2.0) - 4.0*theta*elem_prod(alpha, x)*pmax, 0));:g'\
	-e 's://calculate y(v,v,v,s):y=elem_prod(pow(2.0*theta, -1.0), (elem_prod(alpha, x)+pmax-pow(pow(elem_prod(alpha, x)+pmax, 2.0) - 4.0*elem_prod(theta, elem_prod(alpha, x))*pmax, 0)));:g'\
	-e 's://calculate y(v,s,s,v):y=pow(2.0*theta, -1.0)*(alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*theta*alpha*elem_prod(x, pmax), 0));:g'\
	-e 's://calculate y(v,v,s,v):y=elem_prod(pow(2.0*theta, -1.0), (alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*elem_prod(elem_prod(theta, x), pmax)*alpha, 0)));:g'\
	-e 's://calculate y(v,s,v,v):y=pow(2.0*theta, -1.0)*(elem_prod(alpha, x)+pmax-pow(pow(elem_prod(alpha, x)+pmax, 2.0) - 4.0*theta*elem_prod(elem_prod(alpha, x), pmax), 0));:g'\
	-e 's://calculate y(v,v,v,v):y=elem_prod(pow(2.0*theta, -1.0), (elem_prod(alpha, x)+pmax-pow(pow(elem_prod(alpha, x)+pmax, 2.0) - 4.0*elem_prod(elem_prod(theta, elem_prod(alpha, x)), pmax), 0)));:g'\
	template3var.cpp >nonrectangular_hyperbola.cpp

##############
###Gompertz###
##############
#function;				Gompertz function;
#\f$  \f$				\f$ e^{-ae^{-bx}} \f$
#func(					Gompertz(
#//calculate y(s,s,s)	y=exp(-a*exp(-b*x));
#//calculate y(v,s,s)	y=exp(-a*exp(-b*x));
#//calculate y(v,v,s)	y=exp(-elem_prod(a, exp(-b*x)));
#//calculate y(v,s,v)	y=exp(-a*exp(-elem_prod(b, x)));
#//calculate y(v,v,v)	y=exp(-elem_prod(a, exp(-elem_prod(b, x))));
sed -e 's:function;:Gompertz function;:g'\
	-e 's:\\f\$  \\f\$:\\f\$ e^{-ae^{-bx}} \\f\$:g'\
	-e 's:func(:Gompertz(:g'\
	-e 's://calculate y(s,s,s):y=exp(-a*exp(-b*x));:g'\
	-e 's://calculate y(v,s,s):y=exp(-a*exp(-b*x));:g'\
	-e 's://calculate y(v,v,s):y=exp(-elem_prod(a, exp(-b*x)));:g'\
	-e 's://calculate y(v,s,v):y=exp(-a*exp(-elem_prod(b, x)));:g'\
	-e 's://calculate y(v,v,v):y=exp(-elem_prod(a, exp(-elem_prod(b, x))));:g'\
	template2var.cpp >Gompertz.cpp

##############
###Shepherd###
##############
#function;					Shepherd function
#\f$  \f$					\f$ \frac{ax}{b+x^c} \f$
#func(						Shepherd(
#//calculate y(s,s,s,s)		y=a*x/(b+pow(x,c));
#//calculate y(v,s,s,s)		y=a*elem_div(x, (b+pow(x,c)));
#//calculate y(v,v,s,s)		y=elem_prod(a, elem_div(x, (b+pow(x,c))));
#//calculate y(v,s,v,s)		y=a*elem_div(x, (b+pow(x,c)));
#//calculate y(v,v,v,s)		y=elem_prod(a, elem_div(x, (b+pow(x,c))));
#//calculate y(v,s,s,v)		y=a*elem_div(x, (b+pow(x,c)));
#//calculate y(v,v,s,v)		y=elem_prod(a, elem_div(x, (b+pow(x,c))));
#//calculate y(v,s,v,v)		y=a*elem_div(x, (b+pow(x,c)));
#//calculate y(v,v,v,v)		y=elem_prod(a, elem_div(x, (b+pow(x,c))));
sed -e 's:function;:Shepherd function:g'\
	-e 's:\\f\$  \\f\$:\\f\$ \\frac{ax}{b+x^c} \\f\$:g'\
	-e 's:func(:Shepherd(:g'\
	-e 's://calculate y(s,s,s,s):y=a*x/(b+pow(x,c));:g'\
	-e 's://calculate y(v,s,s,s):y=a*elem_div(x, (b+pow(x,c)));:g'\
	-e 's://calculate y(v,v,s,s):y=elem_prod(a, elem_div(x, (b+pow(x,c))));:g'\
	-e 's://calculate y(v,s,v,s):y=a*elem_div(x, (b+pow(x,c)));:g'\
	-e 's://calculate y(v,v,v,s):y=elem_prod(a, elem_div(x, (b+pow(x,c))));:g'\
	-e 's://calculate y(v,s,s,v):y=a*elem_div(x, (b+pow(x,c)));:g'\
	-e 's://calculate y(v,v,s,v):y=elem_prod(a, elem_div(x, (b+pow(x,c))));:g'\
	-e 's://calculate y(v,s,v,v):y=a*elem_div(x, (b+pow(x,c)));:g'\
	-e 's://calculate y(v,v,v,v):y=elem_prod(a, elem_div(x, (b+pow(x,c))));:g'\
	template3var.cpp >Shepherd.cpp

#############
###Hassell###
#############
#function;					Hassell function
#\f$  \f$					\f$ \frac{ax}{(b+x)^c} \f$
#func(						Hassell(
#//calculate y(s,s,s,s)		y=a*x/(pow(b+x,c));
#//calculate y(v,s,s,s)		y=a*elem_div(x, (pow(b+x,c)));
#//calculate y(v,v,s,s)		y=elem_prod(a, elem_div(x, (pow(b+x,c))));
#//calculate y(v,s,v,s)		y=a*elem_div(x, (pow(b+x,c)));
#//calculate y(v,v,v,s)		y=elem_prod(a, elem_div(x, (pow(b+x,c))));
#//calculate y(v,s,s,v)		y=a*elem_div(x, (pow(b+x,c)));
#//calculate y(v,v,s,v)		y=elem_prod(a, elem_div(x, (pow(b+x,c))));
#//calculate y(v,s,v,v)		y=a*elem_div(x, (pow(b+x,c)));
#//calculate y(v,v,v,v)		y=elem_prod(a, elem_div(x, (pow(b+x,c))));
sed -e 's:function;:Hassell function:g'\
	-e 's:\\f\$  \\f\$:\\f\$ \\frac{ax}{(b+x)^c} \\f\$:g'\
	-e 's:func(:Hassell(:g'\
	-e 's://calculate y(s,s,s,s):y=a*x/(pow(b+x,c));:g'\
	-e 's://calculate y(v,s,s,s):y=a*elem_div(x, (pow(b+x,c)));:g'\
	-e 's://calculate y(v,v,s,s):y=elem_prod(a, elem_div(x, (pow(b+x,c))));:g'\
	-e 's://calculate y(v,s,v,s):y=a*elem_div(x, (pow(b+x,c)));:g'\
	-e 's://calculate y(v,v,v,s):y=elem_prod(a, elem_div(x, (pow(b+x,c))));:g'\
	-e 's://calculate y(v,s,s,v):y=a*elem_div(x, (pow(b+x,c)));:g'\
	-e 's://calculate y(v,v,s,v):y=elem_prod(a, elem_div(x, (pow(b+x,c))));:g'\
	-e 's://calculate y(v,s,v,v):y=a*elem_div(x, (pow(b+x,c)));:g'\
	-e 's://calculate y(v,v,v,v):y=elem_prod(a, elem_div(x, (pow(b+x,c))));:g'\
	template3var.cpp >Hassell.cpp
