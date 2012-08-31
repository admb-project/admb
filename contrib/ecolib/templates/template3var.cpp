#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 

/*---------------------------------------------------------3rd variable is a scalar*/
/*---------------------------------------------2nd variable is a scalar*/
/**  function; scalar
\param x independent variable; data scalar
\param a ; differentiable scalar
\param b ; differentiable scalar
\param c ; differentiable scalar
\return  \f$  \f$
\ingroup ECOL
**/
dvariable func(const double& x,  const prevariable& a,  const prevariable& b,  const prevariable& c)
{
    RETURN_ARRAYS_INCREMENT();	
	dvariable y;
	//calculate y(s,s,s,s)

	RETURN_ARRAYS_DECREMENT();
	return (y);
}
/**  function; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable scalar
\param c ; differentiable scalar
\return  \f$  \f$
\ingroup ECOL
**/
dvar_vector func(const dvector& x,  const prevariable& a,  const prevariable& b,  const prevariable& c)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	//calculate y(v,s,s,s)

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  function; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable scalar
\param c ; differentiable scalar
\return  \f$  \f$
\ingroup ECOL
**/
dvar_vector func(const dvector& x,  const dvar_vector& a,  const prevariable& b,  const prevariable& c)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	//calculate y(v,v,s,s)

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  function; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable vector
\param c ; differentiable scalar
\return  \f$  \f$
\ingroup ECOL
**/
dvar_vector func(const dvector& x,  const prevariable& a,  const dvar_vector& b,  const prevariable& c)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	//calculate y(v,s,v,s)

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  function; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable vector
\param c ; differentiable scalar
\return  \f$  \f$
\ingroup ECOL
**/
dvar_vector func(const dvector& x,  const dvar_vector& a,  const dvar_vector& b,  const prevariable& c)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	//calculate y(v,v,v,s)

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------------------3rd variable is a vector*/
/*---------------------------------------------2nd variable is a scalar*/
/**  function; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable scalar
\param c ; differentiable vector
\return  \f$  \f$
\ingroup ECOL
**/
dvar_vector func(const dvector& x,  const prevariable& a,  const prevariable& b,  const dvar_vector& c)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	//calculate y(v,s,s,v)

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  function; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable scalar
\param c ; differentiable vector
\return  \f$  \f$
\ingroup ECOL
**/
dvar_vector func(const dvector& x,  const dvar_vector& a,  const prevariable& b,  const dvar_vector& c)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	//calculate y(v,v,s,v)

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  function; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable vector
\param c ; differentiable vector
\return  \f$  \f$
\ingroup ECOL
**/
dvar_vector func(const dvector& x,  const prevariable& a,  const dvar_vector& b,  const dvar_vector& c)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	//calculate y(v,s,v,v)

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  function; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable vector
\param c ; differentiable vector
\return  \f$  \f$
\ingroup ECOL
**/
dvar_vector func(const dvector& x,  const dvar_vector& a,  const dvar_vector& b,  const dvar_vector& c)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	//calculate y(v,v,v,v)

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------------------3rd variable is a scalar in a random effects model*/
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** function; random effects scalar
\param x independent variable; data scalar
\param a ; differentiable scalar in a random effects model
\param b ; differentiable scalar in a random effects model
\param c ; differentiable scalar in a random effects model
\return  \f$  \f$
\ingroup ECOL
**/
df1b2variable func(const double& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2variable& c)
{
	df1b2variable y;
	//calculate y(s,s,s,s)

    return (y);
}
/** function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable scalar in a random effects model
\param c ; differentiable scalar in a random effects model
\return  \f$  \f$
\ingroup ECOL
**/
df1b2vector func(const dvector& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2variable& c)
{
	df1b2vector y;
	//calculate y(v,s,s,s)

    return(y);
}
/** function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable scalar in a random effects model
\param c ; differentiable scalar in a random effects model
\return  \f$  \f$
\ingroup ECOL
**/
df1b2vector func(const dvector& x,  const df1b2vector& a,  const df1b2variable& b,  const df1b2variable& c)
{
	df1b2vector y;
	//calculate y(v,v,s,s)

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable vector in a random effects model
\param c ; differentiable scalar in a random effects model
\return  \f$  \f$
\ingroup ECOL
**/
df1b2vector func(const dvector& x,  const df1b2variable& a,  const df1b2vector& b,  const df1b2variable& c)
{
	df1b2vector y;
	//calculate y(v,s,v,s)

    return(y);
}
/** function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable vector in a random effects model
\param c ; differentiable scalar in a random effects model
\return  \f$  \f$
\ingroup ECOL
**/
df1b2vector func(const dvector& x,  const df1b2vector& a,  const df1b2vector& b,  const df1b2variable& c)
{
	df1b2vector y;
	//calculate y(v,v,v,s)

    return(y);
}


/*---------------------------------------------------------3rd variable is a vector in a random effects model*/
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable scalar in a random effects model
\param c ; differentiable vector in a random effects model
\return  \f$  \f$
\ingroup ECOL
**/
df1b2vector func(const dvector& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2vector& c)
{
	df1b2vector y;
	//calculate y(v,s,s,v)

    return(y);
}
/** function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable scalar in a random effects model
\param c ; differentiable vector in a random effects model
\return  \f$  \f$
\ingroup ECOL
**/
df1b2vector func(const dvector& x,  const df1b2vector& a,  const df1b2variable& b,  const df1b2vector& c)
{
	df1b2vector y;
	//calculate y(v,v,s,v)

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable vector in a random effects model
\param c ; differentiable vector in a random effects model
\return  \f$  \f$
\ingroup ECOL
**/
df1b2vector func(const dvector& x,  const df1b2variable& a,  const df1b2vector& b,  const df1b2vector& c)
{
	df1b2vector y;
	//calculate y(v,s,v,v)

    return(y);
}
/** function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable vector in a random effects model
\param c ; differentiable vector in a random effects model
\return  \f$  \f$
\ingroup ECOL
**/
df1b2vector func(const dvector& x,  const df1b2vector& a,  const df1b2vector& b,  const df1b2vector& c)
{
	df1b2vector y;
	//calculate y(v,v,v,v)

    return(y);
}
