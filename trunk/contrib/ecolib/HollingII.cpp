#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 


/*---------------------------------------------2nd variable is a scalar*/
/**  HollingII scalar
\param x independent variable; data scalar
\param alpha ; differentiable scalar
\param h ; differentiable scalar
\return  \f$ \frac{alpha x}{1+ alpha hx} \f$
\ingroup ECOL
**/
dvariable HollingII(const double& x,  const prevariable& alpha,  const prevariable& h)
{
    RETURN_ARRAYS_INCREMENT();	
	dvariable y;
	y=alpha*x/(1.0+alpha*(h*x));

	RETURN_ARRAYS_DECREMENT();
	return (y);
}
/**  HollingII vectorized
\param x independent variable; data vector
\param alpha ; differentiable scalar
\param h ; differentiable scalar
\return  \f$ \frac{alpha x}{1+ alpha hx} \f$
\ingroup ECOL
**/
dvar_vector HollingII(const dvector& x,  const prevariable& alpha,  const prevariable& h)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_div(alpha*x, 1.0+alpha*(h*x));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  HollingII vectorized
\param x independent variable; data vector
\param alpha ; differentiable vector
\param h ; differentiable scalar
\return  \f$ \frac{alpha x}{1+ alpha hx} \f$
\ingroup ECOL
**/
dvar_vector HollingII(const dvector& x,  const dvar_vector& alpha,  const prevariable& h)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_div(elem_prod(alpha,x), 1.0+elem_prod(alpha, (h*x)));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  HollingII vectorized
\param x independent variable; data vector
\param alpha ; differentiable scalar
\param h ; differentiable vector
\return  \f$ \frac{alpha x}{1+ alpha hx} \f$
\ingroup ECOL
**/
dvar_vector HollingII(const dvector& x,  const prevariable& alpha,  const dvar_vector& h)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_div(alpha*x, 1.0+alpha*elem_prod(h,x));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  HollingII vectorized
\param x independent variable; data vector
\param alpha ; differentiable vector
\param h ; differentiable vector
\return  \f$ \frac{alpha x}{1+ alpha hx} \f$
\ingroup ECOL
**/
dvar_vector HollingII(const dvector& x,  const dvar_vector& alpha,  const dvar_vector& h)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_div(elem_prod(alpha,x), 1.0+elem_prod(alpha, elem_prod(h,x)));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** HollingII random effects scalar
\param x independent variable; data scalar
\param alpha ; differentiable scalar in a random effects model
\param h ; differentiable scalar in a random effects model
\return  \f$ \frac{alpha x}{1+ alpha hx} \f$
\ingroup ECOL
**/
df1b2variable HollingII(const double& x,  const df1b2variable& alpha,  const df1b2variable& h)
{
	df1b2variable y;
	y=alpha*x/(1.0+alpha*(h*x));

    return (y);
}
/** HollingII random effects vectorized
\param x independent variable; data vector
\param alpha ; differentiable scalar in a random effects model
\param h ; differentiable scalar in a random effects model
\return  \f$ \frac{alpha x}{1+ alpha hx} \f$
\ingroup ECOL
**/
df1b2vector HollingII(const dvector& x,  const df1b2variable& alpha,  const df1b2variable& h)
{
	df1b2vector y;
	y=elem_div(alpha*x, 1.0+alpha*(h*x));

    return(y);
}
/** HollingII random effects vectorized
\param x independent variable; data vector
\param alpha ; differentiable vector in a random effects model
\param h ; differentiable scalar in a random effects model
\return  \f$ \frac{alpha x}{1+ alpha hx} \f$
\ingroup ECOL
**/
df1b2vector HollingII(const dvector& x,  const df1b2vector& alpha,  const df1b2variable& h)
{
	df1b2vector y;
	y=elem_div(elem_prod(alpha,x), 1.0+elem_prod(alpha, (h*x)));

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** HollingII random effects vectorized
\param x independent variable; data vector
\param alpha ; differentiable scalar in a random effects model
\param h ; differentiable vector in a random effects model
\return  \f$ \frac{alpha x}{1+ alpha hx} \f$
\ingroup ECOL
**/
df1b2vector HollingII(const dvector& x,  const df1b2variable& alpha,  const df1b2vector& h)
{
	df1b2vector y;
	y=elem_div(alpha*x, 1.0+alpha*elem_prod(h,x));

    return(y);
}
/** HollingII random effects vectorized
\param x independent variable; data vector
\param alpha ; differentiable vector in a random effects model
\param h ; differentiable vector in a random effects model
\return  \f$ \frac{alpha x}{1+ alpha hx} \f$
\ingroup ECOL
**/
df1b2vector HollingII(const dvector& x,  const df1b2vector& alpha,  const df1b2vector& h)
{
	df1b2vector y;
	y=elem_div(elem_prod(alpha,x), 1.0+elem_prod(alpha, elem_prod(h,x)));

    return(y);
}

