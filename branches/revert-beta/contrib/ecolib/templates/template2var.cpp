#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 


/*---------------------------------------------2nd variable is a scalar*/
/**  function; scalar
\param x independent variable; data scalar
\param a ; differentiable scalar
\param b ; differentiable scalar
\return  \f$  \f$
**/
dvariable func(const double& x,  const prevariable& a,  const prevariable& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvariable y;
	//calculate y(s,s,s)

	RETURN_ARRAYS_DECREMENT();
	return (y);
}
/**  function; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable scalar
\return  \f$  \f$
**/
dvar_vector func(const dvector& x,  const prevariable& a,  const prevariable& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	//calculate y(v,s,s)

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  function; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable scalar
\return  \f$  \f$
**/
dvar_vector func(const dvector& x,  const dvar_vector& a,  const prevariable& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	//calculate y(v,v,s)

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  function; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable vector
\return  \f$  \f$
**/
dvar_vector func(const dvector& x,  const prevariable& a,  const dvar_vector& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	//calculate y(v,s,v)

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  function; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable vector
\return  \f$  \f$
**/
dvar_vector func(const dvector& x,  const dvar_vector& a,  const dvar_vector& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	//calculate y(v,v,v)

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** function; random effects scalar
\param x independent variable; data scalar
\param a ; differentiable scalar in a random effects model
\param b ; differentiable scalar in a random effects model
\return  \f$  \f$
**/
df1b2variable func(const double& x,  const df1b2variable& a,  const df1b2variable& b)
{
	df1b2variable y;
	//calculate y(s,s,s)

    return (y);
}
/** function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable scalar in a random effects model
\return  \f$  \f$
**/
df1b2vector func(const dvector& x,  const df1b2variable& a,  const df1b2variable& b)
{
	df1b2vector y;
	//calculate y(v,s,s)

    return(y);
}
/** function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable scalar in a random effects model
\return  \f$  \f$
**/
df1b2vector func(const dvector& x,  const df1b2vector& a,  const df1b2variable& b)
{
	df1b2vector y;
	//calculate y(v,v,s)

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable vector in a random effects model
\return  \f$  \f$
**/
df1b2vector func(const dvector& x,  const df1b2variable& a,  const df1b2vector& b)
{
	df1b2vector y;
	//calculate y(v,s,v)

    return(y);
}
/** function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable vector in a random effects model
\return  \f$  \f$
**/
df1b2vector func(const dvector& x,  const df1b2vector& a,  const df1b2vector& b)
{
	df1b2vector y;
	//calculate y(v,v,v)

    return(y);
}

