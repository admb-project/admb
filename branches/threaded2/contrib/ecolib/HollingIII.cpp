#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 


/*---------------------------------------------2nd variable is a scalar*/
/**  Holling Type III function; scalar
\param x independent variable; data scalar
\param a ; differentiable scalar
\param b ; differentiable scalar
\return  \f$  \f$
**/
dvariable HollingIII(const double& x,  const prevariable& a,  const prevariable& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvariable y;
	y=a*pow(x,2)/(pow(b,2)+pow(x,2));

	RETURN_ARRAYS_DECREMENT();
	return (y);
}
/**  Holling Type III function; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable scalar
\return  \f$  \f$
**/
dvar_vector HollingIII(const dvector& x,  const prevariable& a,  const prevariable& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=a*elem_div(pow(x,2), pow(b,2)+pow(x,2));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  Holling Type III function; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable scalar
\return  \f$  \f$
**/
dvar_vector HollingIII(const dvector& x,  const dvar_vector& a,  const prevariable& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(a, elem_div(pow(x,2), pow(b,2)+pow(x,2)));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  Holling Type III function; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable vector
\return  \f$  \f$
**/
dvar_vector HollingIII(const dvector& x,  const prevariable& a,  const dvar_vector& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=a*elem_div(pow(x,2), pow(b,2)+pow(x,2));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  Holling Type III function; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable vector
\return  \f$  \f$
**/
dvar_vector HollingIII(const dvector& x,  const dvar_vector& a,  const dvar_vector& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(a, elem_div(pow(x,2), pow(b,2)+pow(x,2)));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** Holling Type III function; random effects scalar
\param x independent variable; data scalar
\param a ; differentiable scalar in a random effects model
\param b ; differentiable scalar in a random effects model
\return  \f$  \f$
**/
df1b2variable HollingIII(const double& x,  const df1b2variable& a,  const df1b2variable& b)
{
	df1b2variable y;
	y=a*pow(x,2)/(pow(b,2)+pow(x,2));

    return (y);
}
/** Holling Type III function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable scalar in a random effects model
\return  \f$  \f$
**/
df1b2vector HollingIII(const dvector& x,  const df1b2variable& a,  const df1b2variable& b)
{
	df1b2vector y;
	y=a*elem_div(pow(x,2), pow(b,2)+pow(x,2));

    return(y);
}
/** Holling Type III function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable scalar in a random effects model
\return  \f$  \f$
**/
df1b2vector HollingIII(const dvector& x,  const df1b2vector& a,  const df1b2variable& b)
{
	df1b2vector y;
	y=elem_prod(a, elem_div(pow(x,2), pow(b,2)+pow(x,2)));

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** Holling Type III function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable vector in a random effects model
\return  \f$  \f$
**/
df1b2vector HollingIII(const dvector& x,  const df1b2variable& a,  const df1b2vector& b)
{
	df1b2vector y;
	y=a*elem_div(pow(x,2), pow(b,2)+pow(x,2));

    return(y);
}
/** Holling Type III function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable vector in a random effects model
\return  \f$  \f$
**/
df1b2vector HollingIII(const dvector& x,  const df1b2vector& a,  const df1b2vector& b)
{
	df1b2vector y;
	y=elem_prod(a, elem_div(pow(x,2), pow(b,2)+pow(x,2)));

    return(y);
}

