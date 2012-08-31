#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 


/*---------------------------------------------2nd variable is a scalar*/
/**  Michaelis Menten function, 1st parametarization; scalar
\param x independent variable; data scalar
\param a ; differentiable scalar
\param b ; differentiable scalar
\return  \f$ \frac{ax}{b+x} \f$ 
\ingroup ECOL
**/
dvariable Michaelis_Menten1(const double& x,  const prevariable& a,  const prevariable& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvariable y;
	y=a*x/(b+x);

	RETURN_ARRAYS_DECREMENT();
	return (y);
}
/**  Michaelis Menten function, 1st parametarization; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable scalar
\return  \f$ \frac{ax}{b+x} \f$ 
\ingroup ECOL
**/
dvar_vector Michaelis_Menten1(const dvector& x,  const prevariable& a,  const prevariable& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=a*elem_div(x, b+x);

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  Michaelis Menten function, 1st parametarization; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable scalar
\return  \f$ \frac{ax}{b+x} \f$ 
\ingroup ECOL
**/
dvar_vector Michaelis_Menten1(const dvector& x,  const dvar_vector& a,  const prevariable& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(a, elem_div(x, b+x));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  Michaelis Menten function, 1st parametarization; vectorized
\param x independent variable; data vector
\param a ; differentiable scalar
\param b ; differentiable vector
\return  \f$ \frac{ax}{b+x} \f$ 
\ingroup ECOL
**/
dvar_vector Michaelis_Menten1(const dvector& x,  const prevariable& a,  const dvar_vector& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=a*elem_div(x, b+x);

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  Michaelis Menten function, 1st parametarization; vectorized
\param x independent variable; data vector
\param a ; differentiable vector
\param b ; differentiable vector
\return  \f$ \frac{ax}{b+x} \f$ 
\ingroup ECOL
**/
dvar_vector Michaelis_Menten1(const dvector& x,  const dvar_vector& a,  const dvar_vector& b)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(a, elem_div(x, b+x));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** Michaelis Menten function, 1st parametarization; random effects scalar
\param x independent variable; data scalar
\param a ; differentiable scalar in a random effects model
\param b ; differentiable scalar in a random effects model
\return  \f$ \frac{ax}{b+x} \f$ 
\ingroup ECOL
**/
df1b2variable Michaelis_Menten1(const double& x,  const df1b2variable& a,  const df1b2variable& b)
{
	df1b2variable y;
	y=a*x/(b+x);

    return (y);
}
/** Michaelis Menten function, 1st parametarization; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable scalar in a random effects model
\return  \f$ \frac{ax}{b+x} \f$ 
\ingroup ECOL
**/
df1b2vector Michaelis_Menten1(const dvector& x,  const df1b2variable& a,  const df1b2variable& b)
{
	df1b2vector y;
	y=a*elem_div(x, b+x);

    return(y);
}
/** Michaelis Menten function, 1st parametarization; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable scalar in a random effects model
\return  \f$ \frac{ax}{b+x} \f$ 
\ingroup ECOL
**/
df1b2vector Michaelis_Menten1(const dvector& x,  const df1b2vector& a,  const df1b2variable& b)
{
	df1b2vector y;
	y=elem_prod(a, elem_div(x, b+x));

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** Michaelis Menten function, 1st parametarization; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable scalar in a random effects model
\param b ; differentiable vector in a random effects model
\return  \f$ \frac{ax}{b+x} \f$ 
\ingroup ECOL
**/
df1b2vector Michaelis_Menten1(const dvector& x,  const df1b2variable& a,  const df1b2vector& b)
{
	df1b2vector y;
	y=a*elem_div(x, b+x);

    return(y);
}
/** Michaelis Menten function, 1st parametarization; random effects vectorized
\param x independent variable; data vector
\param a ; differentiable vector in a random effects model
\param b ; differentiable vector in a random effects model
\return  \f$ \frac{ax}{b+x} \f$ 
\ingroup ECOL
**/
df1b2vector Michaelis_Menten1(const dvector& x,  const df1b2vector& a,  const df1b2vector& b)
{
	df1b2vector y;
	y=elem_prod(a, elem_div(x, b+x));

    return(y);
}

