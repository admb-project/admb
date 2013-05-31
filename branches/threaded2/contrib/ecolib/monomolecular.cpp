#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 


/*---------------------------------------------2nd variable is a scalar*/
/**   monomoleular function; scalar
\param x independent variable; data scalar
\param a ; differentiable scalar
\param b ; differentiable scalar
\return  \f$ a(1-e^{-bx}) \f$ 
**/
dvariable monomolecular(const double& x,  const prevariable& a,  const prevariable& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvariable y;
	y=a*(1.0-exp(-b*x)); 

	RETURN_ARRAYS_DECREMENT();
	return (y);
}
/**   monomoleular function; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable scalar
\return  \f$ a(1-e^{-bx}) \f$ 
**/
dvar_vector monomolecular(const dvector& x,  const prevariable& a,  const prevariable& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=a*(1.0-exp(-b*x)); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**   monomoleular function; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable scalar
\return  \f$ a(1-e^{-bx}) \f$ 
**/
dvar_vector monomolecular(const dvector& x,  const dvar_vector& a,  const prevariable& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(a, 1.0-exp(-b*x)); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**   monomoleular function; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable vector
\return  \f$ a(1-e^{-bx}) \f$ 
**/
dvar_vector monomolecular(const dvector& x,  const prevariable& a,  const dvar_vector& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=a*(1.0-exp(-1.0*elem_prod(b,x))); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**   monomoleular function; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable vector
\return  \f$ a(1-e^{-bx}) \f$ 
**/
dvar_vector monomolecular(const dvector& x,  const dvar_vector& a,  const dvar_vector& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(a, 1.0-exp(-1.0*elem_prod(b,x))); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/**  monomoleular function; random effects scalar
\param x independent variable; data scalar
\param a ; differentiable scalar in a random effects model
\param b ; differentiable scalar in a random effects model
\return  \f$ a(1-e^{-bx}) \f$ 
**/
df1b2variable monomolecular(const double& x,  const df1b2variable& a,  const df1b2variable& b)
{
	df1b2variable y;
	y=a*(1.0-exp(-b*x)); 

    return (y);
}
/**  monomoleular function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable scalar in a random effects model
\return  \f$ a(1-e^{-bx}) \f$ 
**/
df1b2vector monomolecular(const dvector& x,  const df1b2variable& a,  const df1b2variable& b)
{
	df1b2vector y;
	y=a*(1.0-exp(-b*x)); 

    return(y);
}
/**  monomoleular function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable scalar in a random effects model
\return  \f$ a(1-e^{-bx}) \f$ 
**/
df1b2vector monomolecular(const dvector& x,  const df1b2vector& a,  const df1b2variable& b)
{
	df1b2vector y;
	y=elem_prod(a, 1.0-exp(-b*x)); 

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/**  monomoleular function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable vector in a random effects model
\return  \f$ a(1-e^{-bx}) \f$ 
**/
df1b2vector monomolecular(const dvector& x,  const df1b2variable& a,  const df1b2vector& b)
{
	df1b2vector y;
	y=a*(1.0-exp(-1.0*elem_prod(b,x))); 

    return(y);
}
/**  monomoleular function; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable vector in a random effects model
\return  \f$ a(1-e^{-bx}) \f$ 
**/
df1b2vector monomolecular(const dvector& x,  const df1b2vector& a,  const df1b2vector& b)
{
	df1b2vector y;
	y=elem_prod(a, 1.0-exp(-1.0*elem_prod(b,x))); 

    return(y);
}

