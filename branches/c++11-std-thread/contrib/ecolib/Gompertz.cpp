#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 


/*---------------------------------------------2nd variable is a scalar*/
/**  Gompertz function; scalar
\param x independent variable; data scalar
\param a ; differentiable scalar
\param b ; differentiable scalar
\return  \f$ e^{-ae^{-bx}} \f$
\ingroup ECOL
**/
dvariable Gompertz(const double& x,  const prevariable& a,  const prevariable& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvariable y;
	y=exp(-a*exp(-b*x));

	RETURN_ARRAYS_DECREMENT();
	return (y);
}
/**  Gompertz function; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable scalar
\return  \f$ e^{-ae^{-bx}} \f$
\ingroup ECOL
**/
dvar_vector Gompertz(const dvector& x,  const prevariable& a,  const prevariable& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=exp(-a*exp(-b*x));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  Gompertz function; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable scalar
\return  \f$ e^{-ae^{-bx}} \f$
\ingroup ECOL
**/
dvar_vector Gompertz(const dvector& x,  const dvar_vector& a,  const prevariable& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=exp(-elem_prod(a, exp(-b*x)));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  Gompertz function; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable vector
\return  \f$ e^{-ae^{-bx}} \f$
\ingroup ECOL
**/
dvar_vector Gompertz(const dvector& x,  const prevariable& a,  const dvar_vector& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=exp(-a*exp(-elem_prod(b, x)));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  Gompertz function; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable vector
\return  \f$ e^{-ae^{-bx}} \f$
\ingroup ECOL
**/
dvar_vector Gompertz(const dvector& x,  const dvar_vector& a,  const dvar_vector& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=exp(-elem_prod(a, exp(-elem_prod(b, x))));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** Gompertz function; random effects scalar
\param x independent variable; data scalar
\param a ; differentiable scalar in a random effects model
\param b ; differentiable scalar in a random effects model
\return  \f$ e^{-ae^{-bx}} \f$
\ingroup ECOL
**/
df1b2variable Gompertz(const double& x,  const df1b2variable& a,  const df1b2variable& b)
{
	df1b2variable y;
	y=exp(-a*exp(-b*x));

    return (y);
}
/** Gompertz function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable scalar in a random effects model
\return  \f$ e^{-ae^{-bx}} \f$
\ingroup ECOL
**/
df1b2vector Gompertz(const dvector& x,  const df1b2variable& a,  const df1b2variable& b)
{
	df1b2vector y;
	y=exp(-a*exp(-b*x));

    return(y);
}
/** Gompertz function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable scalar in a random effects model
\return  \f$ e^{-ae^{-bx}} \f$
\ingroup ECOL
**/
df1b2vector Gompertz(const dvector& x,  const df1b2vector& a,  const df1b2variable& b)
{
	df1b2vector y;
	y=exp(-elem_prod(a, exp(-b*x)));

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** Gompertz function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable vector in a random effects model
\return  \f$ e^{-ae^{-bx}} \f$
\ingroup ECOL
**/
df1b2vector Gompertz(const dvector& x,  const df1b2variable& a,  const df1b2vector& b)
{
	df1b2vector y;
	y=exp(-a*exp(-elem_prod(b, x)));

    return(y);
}
/** Gompertz function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable vector in a random effects model
\return  \f$ e^{-ae^{-bx}} \f$
\ingroup ECOL
**/
df1b2vector Gompertz(const dvector& x,  const df1b2vector& a,  const df1b2vector& b)
{
	df1b2vector y;
	y=exp(-elem_prod(a, exp(-elem_prod(b, x))));

    return(y);
}

