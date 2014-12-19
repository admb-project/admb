#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 


/*---------------------------------------------2nd variable is a scalar*/
/**  logistic function; scalar
\param x independent variable; data scalar
\param a ; differentiable scalar
\param b ; differentiable scalar
\return  \f$ \frac{e^{a+bx}}{(1+e^{a+bx})} \f$
\ingroup ECOL
**/
dvariable logistic(const double& x,  const prevariable& a,  const prevariable& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvariable y;
	y=exp(a+b*x)/(1.0+exp(a+b*x));

	RETURN_ARRAYS_DECREMENT();
	return (y);
}
/**  logistic function; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable scalar
\return  \f$ \frac{e^{a+bx}}{(1+e^{a+bx})} \f$
\ingroup ECOL
**/
dvar_vector logistic(const dvector& x,  const prevariable& a,  const prevariable& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_div(exp(a+b*x), 1.0+exp(a+b*x));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  logistic function; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable scalar
\return  \f$ \frac{e^{a+bx}}{(1+e^{a+bx})} \f$
\ingroup ECOL
**/
dvar_vector logistic(const dvector& x,  const dvar_vector& a,  const prevariable& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_div(exp(a+b*x), 1.0+exp(a+b*x));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  logistic function; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable vector
\return  \f$ \frac{e^{a+bx}}{(1+e^{a+bx})} \f$
\ingroup ECOL
**/
dvar_vector logistic(const dvector& x,  const prevariable& a,  const dvar_vector& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_div(exp(a+elem_prod(b,x)), 1.0+exp(a+elem_prod(b,x)));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  logistic function; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable vector
\return  \f$ \frac{e^{a+bx}}{(1+e^{a+bx})} \f$
\ingroup ECOL
**/
dvar_vector logistic(const dvector& x,  const dvar_vector& a,  const dvar_vector& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_div(exp(a+elem_prod(b,x)), 1.0+exp(a+elem_prod(b,x)));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** logistic function; random effects scalar
\param x independent variable; data scalar
\param a ; differentiable scalar in a random effects model
\param b ; differentiable scalar in a random effects model
\return  \f$ \frac{e^{a+bx}}{(1+e^{a+bx})} \f$
\ingroup ECOL
**/
df1b2variable logistic(const double& x,  const df1b2variable& a,  const df1b2variable& b)
{
	df1b2variable y;
	y=exp(a+b*x)/(1.0+exp(a+b*x));

    return (y);
}
/** logistic function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable scalar in a random effects model
\return  \f$ \frac{e^{a+bx}}{(1+e^{a+bx})} \f$
\ingroup ECOL
**/
df1b2vector logistic(const dvector& x,  const df1b2variable& a,  const df1b2variable& b)
{
	df1b2vector y;
	y=elem_div(exp(a+b*x), 1.0+exp(a+b*x));

    return(y);
}
/** logistic function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable scalar in a random effects model
\return  \f$ \frac{e^{a+bx}}{(1+e^{a+bx})} \f$
\ingroup ECOL
**/
df1b2vector logistic(const dvector& x,  const df1b2vector& a,  const df1b2variable& b)
{
	df1b2vector y;
	y=elem_div(exp(a+b*x), 1.0+exp(a+b*x));

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** logistic function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable vector in a random effects model
\return  \f$ \frac{e^{a+bx}}{(1+e^{a+bx})} \f$
\ingroup ECOL
**/
df1b2vector logistic(const dvector& x,  const df1b2variable& a,  const df1b2vector& b)
{
	df1b2vector y;
	y=elem_div(exp(a+elem_prod(b,x)), 1.0+exp(a+elem_prod(b,x)));

    return(y);
}
/** logistic function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable vector in a random effects model
\return  \f$ \frac{e^{a+bx}}{(1+e^{a+bx})} \f$
\ingroup ECOL
**/
df1b2vector logistic(const dvector& x,  const df1b2vector& a,  const df1b2vector& b)
{
	df1b2vector y;
	y=elem_div(exp(a+elem_prod(b,x)), 1.0+exp(a+elem_prod(b,x)));

    return(y);
}

