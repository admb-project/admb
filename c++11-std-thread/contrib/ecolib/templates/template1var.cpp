#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 

/**  function; scalar
\param x independent variable; data scalar
\param a ; differentiable scalar
\return  \f$  \f$
\ingroup ECOL
**/
dvariable func(const double& x,  const prevariable& a)
{
    RETURN_ARRAYS_INCREMENT();	
	dvariable y;
	//calculate y(s,s)

	RETURN_ARRAYS_DECREMENT();
	return (y);
}
/**  function; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\return  \f$  \f$
\ingroup ECOL
**/
dvar_vector func(const dvector& x,  const prevariable& a)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	//calculate y(v,s)

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  function; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\return  \f$  \f$
\ingroup ECOL
**/
dvar_vector func(const dvector& x,  const dvar_vector& a)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	//calculate y(v,v)

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*-------------------------------1st varible contains random effects*/
/** function; random effects scalar
\param x independent variable; data scalar
\param a ; differentiable scalar in a random effects model
\return  \f$  \f$
\ingroup ECOL
**/
df1b2variable func(const double& x,  const df1b2variable& a)
{
	df1b2variable y;
	//calculate y(s,s)

    return (y);
}
/** function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\return  \f$  \f$
\ingroup ECOL
**/
df1b2vector func(const dvector& x,  const df1b2variable& a)
{
	df1b2vector y;
	//calculate y(v,s)

    return(y);
}
/** function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\return  \f$  \f$
\ingroup ECOL
**/
df1b2vector func(const dvector& x,  const df1b2vector& a)
{
	df1b2vector y;
	//calculate y(v,v)

    return(y);
}