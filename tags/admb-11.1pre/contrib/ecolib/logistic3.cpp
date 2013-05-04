#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 

/*---------------------------------------------------------3rd variable is a scalar*/
/*---------------------------------------------2nd variable is a scalar*/
/**  logistic function with carrying capacity c; scalar
\param x independent variable; data scalar
\param a ; differentiable scalar
\param b ; differentiable scalar
\param c carrying capacity; differentiable scalar
\return  \f$ \frac{c}{1+e^{-(a+bx)}} \f$
\ingroup ECOL
**/
dvariable logistic3(const double& x,  const prevariable& a,  const prevariable& b,  const prevariable& c)
{
    RETURN_ARRAYS_INCREMENT();	
	dvariable y;
	y=c/(1.0+exp(-(a+b*x)));

	RETURN_ARRAYS_DECREMENT();
	return (y);
}
/**  logistic function with carrying capacity c; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable scalar
\param c carrying capacity; differentiable scalar
\return  \f$ \frac{c}{1+e^{-(a+bx)}} \f$
\ingroup ECOL
**/
dvar_vector logistic3(const dvector& x,  const prevariable& a,  const prevariable& b,  const prevariable& c)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=c/(1.0+exp(-(a+b*x)));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  logistic function with carrying capacity c; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable scalar
\param c carrying capacity; differentiable scalar
\return  \f$ \frac{c}{1+e^{-(a+bx)}} \f$
\ingroup ECOL
**/
dvar_vector logistic3(const dvector& x,  const dvar_vector& a,  const prevariable& b,  const prevariable& c)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=c/(1.0+exp(-(a+b*x)));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  logistic function with carrying capacity c; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable vector
\param c carrying capacity; differentiable scalar
\return  \f$ \frac{c}{1+e^{-(a+bx)}} \f$
\ingroup ECOL
**/
dvar_vector logistic3(const dvector& x,  const prevariable& a,  const dvar_vector& b,  const prevariable& c)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=c/(1.0+exp(-(a+elem_prod(b, x))));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  logistic function with carrying capacity c; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable vector
\param c carrying capacity; differentiable scalar
\return  \f$ \frac{c}{1+e^{-(a+bx)}} \f$
\ingroup ECOL
**/
dvar_vector logistic3(const dvector& x,  const dvar_vector& a,  const dvar_vector& b,  const prevariable& c)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=c/(1.0+exp(-(a+elem_prod(b, x))));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------------------3rd variable is a vector*/
/*---------------------------------------------2nd variable is a scalar*/
/**  logistic function with carrying capacity c; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable scalar
\param c carrying capacity; differentiable vector
\return  \f$ \frac{c}{1+e^{-(a+bx)}} \f$
\ingroup ECOL
**/
dvar_vector logistic3(const dvector& x,  const prevariable& a,  const prevariable& b,  const dvar_vector& c)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_div(c, 1.0+exp(-(a+b*x)));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  logistic function with carrying capacity c; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable scalar
\param c carrying capacity; differentiable vector
\return  \f$ \frac{c}{1+e^{-(a+bx)}} \f$
\ingroup ECOL
**/
dvar_vector logistic3(const dvector& x,  const dvar_vector& a,  const prevariable& b,  const dvar_vector& c)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_div(c, 1.0+exp(-(a+b*x)));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  logistic function with carrying capacity c; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable vector
\param c carrying capacity; differentiable vector
\return  \f$ \frac{c}{1+e^{-(a+bx)}} \f$
\ingroup ECOL
**/
dvar_vector logistic3(const dvector& x,  const prevariable& a,  const dvar_vector& b,  const dvar_vector& c)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_div(c, 1.0+exp(-(a+elem_prod(b, x))));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  logistic function with carrying capacity c; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable vector
\param c carrying capacity; differentiable vector
\return  \f$ \frac{c}{1+e^{-(a+bx)}} \f$
\ingroup ECOL
**/
dvar_vector logistic3(const dvector& x,  const dvar_vector& a,  const dvar_vector& b,  const dvar_vector& c)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_div(c, 1.0+exp(-(a+elem_prod(b, x))));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------------------3rd variable is a scalar in a random effects model*/
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** logistic function with carrying capacity c; random effects scalar
\param x independent variable; data scalar
\param a ; differentiable scalar in a random effects model
\param b ; differentiable scalar in a random effects model
\param c carrying capacity; differentiable scalar in a random effects model
\return  \f$ \frac{c}{1+e^{-(a+bx)}} \f$
\ingroup ECOL
**/
df1b2variable logistic3(const double& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2variable& c)
{
	df1b2variable y;
	y=c/(1.0+exp(-(a+b*x)));

    return (y);
}
/** logistic function with carrying capacity c; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable scalar in a random effects model
\param c carrying capacity; differentiable scalar in a random effects model
\return  \f$ \frac{c}{1+e^{-(a+bx)}} \f$
\ingroup ECOL
**/
df1b2vector logistic3(const dvector& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2variable& c)
{
	df1b2vector y;
	y=c/(1.0+exp(-(a+b*x)));

    return(y);
}
/** logistic function with carrying capacity c; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable scalar in a random effects model
\param c carrying capacity; differentiable scalar in a random effects model
\return  \f$ \frac{c}{1+e^{-(a+bx)}} \f$
\ingroup ECOL
**/
df1b2vector logistic3(const dvector& x,  const df1b2vector& a,  const df1b2variable& b,  const df1b2variable& c)
{
	df1b2vector y;
	y=c/(1.0+exp(-(a+b*x)));

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** logistic function with carrying capacity c; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable vector in a random effects model
\param c carrying capacity; differentiable scalar in a random effects model
\return  \f$ \frac{c}{1+e^{-(a+bx)}} \f$
\ingroup ECOL
**/
df1b2vector logistic3(const dvector& x,  const df1b2variable& a,  const df1b2vector& b,  const df1b2variable& c)
{
	df1b2vector y;
	y=c/(1.0+exp(-(a+elem_prod(b, x))));

    return(y);
}
/** logistic function with carrying capacity c; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable vector in a random effects model
\param c carrying capacity; differentiable scalar in a random effects model
\return  \f$ \frac{c}{1+e^{-(a+bx)}} \f$
\ingroup ECOL
**/
df1b2vector logistic3(const dvector& x,  const df1b2vector& a,  const df1b2vector& b,  const df1b2variable& c)
{
	df1b2vector y;
	y=c/(1.0+exp(-(a+elem_prod(b, x))));

    return(y);
}


/*---------------------------------------------------------3rd variable is a vector in a random effects model*/
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** logistic function with carrying capacity c; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable scalar in a random effects model
\param c carrying capacity; differentiable vector in a random effects model
\return  \f$ \frac{c}{1+e^{-(a+bx)}} \f$
\ingroup ECOL
**/
df1b2vector logistic3(const dvector& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2vector& c)
{
	df1b2vector y;
	y=elem_div(c, 1.0+exp(-(a+b*x)));

    return(y);
}
/** logistic function with carrying capacity c; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable scalar in a random effects model
\param c carrying capacity; differentiable vector in a random effects model
\return  \f$ \frac{c}{1+e^{-(a+bx)}} \f$
\ingroup ECOL
**/
df1b2vector logistic3(const dvector& x,  const df1b2vector& a,  const df1b2variable& b,  const df1b2vector& c)
{
	df1b2vector y;
	y=elem_div(c, 1.0+exp(-(a+b*x)));

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** logistic function with carrying capacity c; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable vector in a random effects model
\param c carrying capacity; differentiable vector in a random effects model
\return  \f$ \frac{c}{1+e^{-(a+bx)}} \f$
\ingroup ECOL
**/
df1b2vector logistic3(const dvector& x,  const df1b2variable& a,  const df1b2vector& b,  const df1b2vector& c)
{
	df1b2vector y;
	y=elem_div(c, 1.0+exp(-(a+elem_prod(b, x))));

    return(y);
}
/** logistic function with carrying capacity c; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable vector in a random effects model
\param c carrying capacity; differentiable vector in a random effects model
\return  \f$ \frac{c}{1+e^{-(a+bx)}} \f$
\ingroup ECOL
**/
df1b2vector logistic3(const dvector& x,  const df1b2vector& a,  const df1b2vector& b,  const df1b2vector& c)
{
	df1b2vector y;
	y=elem_div(c, 1.0+exp(-(a+elem_prod(b, x))));

    return(y);
}
