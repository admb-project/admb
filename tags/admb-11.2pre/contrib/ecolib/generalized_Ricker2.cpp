#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 

/*---------------------------------------------------------3rd variable is a scalar*/
/*---------------------------------------------2nd variable is a scalar*/
/**  generalized Ricker function, second parameerization; scalar
\param x independent variable; data scalar
\param r ; differentiable scalar
\param a ; differentiable scalar
\param alpha ; differentiable scalar
\return  \f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
\ingroup ECOL
**/
dvariable generalized_Ricker2(const double& x,  const prevariable& r,  const prevariable& a,  const prevariable& alpha)
{
    RETURN_ARRAYS_INCREMENT();	
	dvariable y;
	y=x*exp(r*(1.0-pow(a/x, alpha)));

	RETURN_ARRAYS_DECREMENT();
	return (y);
}
/**  generalized Ricker function, second parameerization; vectorized
\param x independent variable; data vector
\param r ; differentiable scalar
\param a ; differentiable scalar
\param alpha ; differentiable scalar
\return  \f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
\ingroup ECOL
**/
dvar_vector generalized_Ricker2(const dvector& x,  const prevariable& r,  const prevariable& a,  const prevariable& alpha)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(x, exp(r*(1.0-pow(a*pow(x, -1.0), alpha))));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  generalized Ricker function, second parameerization; vectorized
\param x independent variable; data vector
\param r ; differentiable vector
\param a ; differentiable scalar
\param alpha ; differentiable scalar
\return  \f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
\ingroup ECOL
**/
dvar_vector generalized_Ricker2(const dvector& x,  const dvar_vector& r,  const prevariable& a,  const prevariable& alpha)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(x, exp(elem_prod(r, (1.0-pow(a*pow(x, -1.0), alpha)))));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  generalized Ricker function, second parameerization; vectorized
\param x independent variable; data vector
\param r ; differentiable scalar
\param a ; differentiable vector
\param alpha ; differentiable scalar
\return  \f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
\ingroup ECOL
**/
dvar_vector generalized_Ricker2(const dvector& x,  const prevariable& r,  const dvar_vector& a,  const prevariable& alpha)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(x, exp(r*(1.0-pow(elem_div(a, x), alpha))));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  generalized Ricker function, second parameerization; vectorized
\param x independent variable; data vector
\param r ; differentiable vector
\param a ; differentiable vector
\param alpha ; differentiable scalar
\return  \f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
\ingroup ECOL
**/
dvar_vector generalized_Ricker2(const dvector& x,  const dvar_vector& r,  const dvar_vector& a,  const prevariable& alpha)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(x, exp(elem_prod(r, (1.0-pow(elem_div(a, x), alpha)))));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------------------3rd variable is a vector*/
/*---------------------------------------------2nd variable is a scalar*/
/**  generalized Ricker function, second parameerization; vectorized
\param x independent variable; data vector
\param r ; differentiable scalar
\param a ; differentiable scalar
\param alpha ; differentiable vector
\return  \f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
\ingroup ECOL
**/
dvar_vector generalized_Ricker2(const dvector& x,  const prevariable& r,  const prevariable& a,  const dvar_vector& alpha)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(x, exp(r*(1.0-pow(a*pow(x, -1.0), alpha))));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  generalized Ricker function, second parameerization; vectorized
\param x independent variable; data vector
\param r ; differentiable vector
\param a ; differentiable scalar
\param alpha ; differentiable vector
\return  \f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
\ingroup ECOL
**/
dvar_vector generalized_Ricker2(const dvector& x,  const dvar_vector& r,  const prevariable& a,  const dvar_vector& alpha)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(x, exp(elem_prod(r, (1.0-pow(a*pow(x, -1.0), alpha)))));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  generalized Ricker function, second parameerization; vectorized
\param x independent variable; data vector
\param r ; differentiable scalar
\param a ; differentiable vector
\param alpha ; differentiable vector
\return  \f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
\ingroup ECOL
**/
dvar_vector generalized_Ricker2(const dvector& x,  const prevariable& r,  const dvar_vector& a,  const dvar_vector& alpha)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(x, exp(r*(1.0-pow(elem_div(a, x), alpha))));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  generalized Ricker function, second parameerization; vectorized
\param x independent variable; data vector
\param r ; differentiable vector
\param a ; differentiable vector
\param alpha ; differentiable vector
\return  \f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
\ingroup ECOL
**/
dvar_vector generalized_Ricker2(const dvector& x,  const dvar_vector& r,  const dvar_vector& a,  const dvar_vector& alpha)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(x, exp(elem_prod(r, (1.0-pow(elem_div(a, x), alpha)))));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------------------3rd variable is a scalar in a random effects model*/
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** generalized Ricker function, second parameerization; random effects scalar
\param x independent variable; data scalar
\param r ; differentiable scalar in a random effects model
\param a ; differentiable scalar in a random effects model
\param alpha ; differentiable scalar in a random effects model
\return  \f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
\ingroup ECOL
**/
df1b2variable generalized_Ricker2(const double& x,  const df1b2variable& r,  const df1b2variable& a,  const df1b2variable& alpha)
{
	df1b2variable y;
	y=x*exp(r*(1.0-pow(a/x, alpha)));

    return (y);
}
/** generalized Ricker function, second parameerization; random effects vectorized
\param x independent variable; data vector
\param r ; differentiable scalar in a random effects model
\param a ; differentiable scalar in a random effects model
\param alpha ; differentiable scalar in a random effects model
\return  \f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
\ingroup ECOL
**/
df1b2vector generalized_Ricker2(const dvector& x,  const df1b2variable& r,  const df1b2variable& a,  const df1b2variable& alpha)
{
	df1b2vector y;
	y=elem_prod(x, exp(r*(1.0-pow(a*pow(x, -1.0), alpha))));

    return(y);
}
/** generalized Ricker function, second parameerization; random effects vectorized
\param x independent variable; data vector
\param r ; differentiable vector in a random effects model
\param a ; differentiable scalar in a random effects model
\param alpha ; differentiable scalar in a random effects model
\return  \f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
\ingroup ECOL
**/
df1b2vector generalized_Ricker2(const dvector& x,  const df1b2vector& r,  const df1b2variable& a,  const df1b2variable& alpha)
{
	df1b2vector y;
	y=elem_prod(x, exp(elem_prod(r, (1.0-pow(a*pow(x, -1.0), alpha)))));

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** generalized Ricker function, second parameerization; random effects vectorized
\param x independent variable; data vector
\param r ; differentiable scalar in a random effects model
\param a ; differentiable vector in a random effects model
\param alpha ; differentiable scalar in a random effects model
\return  \f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
\ingroup ECOL
**/
df1b2vector generalized_Ricker2(const dvector& x,  const df1b2variable& r,  const df1b2vector& a,  const df1b2variable& alpha)
{
	df1b2vector y;
	y=elem_prod(x, exp(r*(1.0-pow(elem_div(a, x), alpha))));

    return(y);
}
/** generalized Ricker function, second parameerization; random effects vectorized
\param x independent variable; data vector
\param r ; differentiable vector in a random effects model
\param a ; differentiable vector in a random effects model
\param alpha ; differentiable scalar in a random effects model
\return  \f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
\ingroup ECOL
**/
df1b2vector generalized_Ricker2(const dvector& x,  const df1b2vector& r,  const df1b2vector& a,  const df1b2variable& alpha)
{
	df1b2vector y;
	y=elem_prod(x, exp(elem_prod(r, (1.0-pow(elem_div(a, x), alpha)))));

    return(y);
}


/*---------------------------------------------------------3rd variable is a vector in a random effects model*/
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** generalized Ricker function, second parameerization; random effects vectorized
\param x independent variable; data vector
\param r ; differentiable scalar in a random effects model
\param a ; differentiable scalar in a random effects model
\param alpha ; differentiable vector in a random effects model
\return  \f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
\ingroup ECOL
**/
df1b2vector generalized_Ricker2(const dvector& x,  const df1b2variable& r,  const df1b2variable& a,  const df1b2vector& alpha)
{
	df1b2vector y;
	y=elem_prod(x, exp(r*(1.0-pow(a*pow(x, -1.0), alpha))));

    return(y);
}
/** generalized Ricker function, second parameerization; random effects vectorized
\param x independent variable; data vector
\param r ; differentiable vector in a random effects model
\param a ; differentiable scalar in a random effects model
\param alpha ; differentiable vector in a random effects model
\return  \f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
\ingroup ECOL
**/
df1b2vector generalized_Ricker2(const dvector& x,  const df1b2vector& r,  const df1b2variable& a,  const df1b2vector& alpha)
{
	df1b2vector y;
	y=elem_prod(x, exp(elem_prod(r, (1.0-pow(a*pow(x, -1.0), alpha)))));

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** generalized Ricker function, second parameerization; random effects vectorized
\param x independent variable; data vector
\param r ; differentiable scalar in a random effects model
\param a ; differentiable vector in a random effects model
\param alpha ; differentiable vector in a random effects model
\return  \f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
\ingroup ECOL
**/
df1b2vector generalized_Ricker2(const dvector& x,  const df1b2variable& r,  const df1b2vector& a,  const df1b2vector& alpha)
{
	df1b2vector y;
	y=elem_prod(x, exp(r*(1.0-pow(elem_div(a, x), alpha))));

    return(y);
}
/** generalized Ricker function, second parameerization; random effects vectorized
\param x independent variable; data vector
\param r ; differentiable vector in a random effects model
\param a ; differentiable vector in a random effects model
\param alpha ; differentiable vector in a random effects model
\return  \f$ xe^{r(1-(\frac{a}{x})^\alpha)} \f$
\ingroup ECOL
**/
df1b2vector generalized_Ricker2(const dvector& x,  const df1b2vector& r,  const df1b2vector& a,  const df1b2vector& alpha)
{
	df1b2vector y;
	y=elem_prod(x, exp(elem_prod(r, (1.0-pow(elem_div(a, x), alpha)))));

    return(y);
}
