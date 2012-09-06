#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 

/*---------------------------------------------------------3rd variable is a scalar*/
/*---------------------------------------------2nd variable is a scalar*/
/**  ecologically parameterized logistic function with carrying capacity K;  scalar
\param t independent variable; data scalar
\param K carrying capacity; differentiable scalar
\param r growth rate; differentiable scalar
\param n0 initial population size at t=0; differentiable scalar
\return  \f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$ 
\ingroup ECOL
**/
dvariable logisticK( const double& t,  const prevariable& K,  const prevariable& r,  const prevariable& n0)
{
    RETURN_ARRAYS_INCREMENT();	
	dvariable y;
	y=K/(1.0+(K/n0-1.0)*exp(-r*t)); 

	RETURN_ARRAYS_DECREMENT();
	return (y);
}
/**  ecologically parameterized logistic function with carrying capacity K;  vectorized
\param t independent variable; data vector
\param K carrying capacity; differentiable scalar
\param r growth rate; differentiable scalar
\param n0 initial population size at t=0; differentiable scalar
\return  \f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$ 
\ingroup ECOL
**/
dvar_vector logisticK( const dvector& t,  const prevariable& K,  const prevariable& r,  const prevariable& n0)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=K/(1.0+(K/n0-1.0)*exp(-r*t)); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  ecologically parameterized logistic function with carrying capacity K;  vectorized
\param t independent variable; data vector
\param K carrying capacity; differentiable vector
\param r growth rate; differentiable scalar
\param n0 initial population size at t=0; differentiable scalar
\return  \f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$ 
\ingroup ECOL
**/
dvar_vector logisticK( const dvector& t,  const dvar_vector& K,  const prevariable& r,  const prevariable& n0)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_div(K, 1.0 + elem_prod(K/n0-1.0, exp(-r*t))); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  ecologically parameterized logistic function with carrying capacity K;  vectorized
\param t independent variable; data vector
\param K carrying capacity; differentiable scalar
\param r growth rate; differentiable vector
\param n0 initial population size at t=0; differentiable scalar
\return  \f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$ 
\ingroup ECOL
**/
dvar_vector logisticK( const dvector& t,  const prevariable& K,  const dvar_vector& r,  const prevariable& n0)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=K/(1.0+(K/n0-1.0)*exp(-1.0*elem_prod(r,t))); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  ecologically parameterized logistic function with carrying capacity K;  vectorized
\param t independent variable; data vector
\param K carrying capacity; differentiable vector
\param r growth rate; differentiable vector
\param n0 initial population size at t=0; differentiable scalar
\return  \f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$ 
\ingroup ECOL
**/
dvar_vector logisticK( const dvector& t,  const dvar_vector& K,  const dvar_vector& r,  const prevariable& n0)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_div(K, 1.0 + elem_prod(K/n0-1.0, exp(-1.0*elem_prod(r,t)))); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------------------3rd variable is a vector*/
/*---------------------------------------------2nd variable is a scalar*/
/**  ecologically parameterized logistic function with carrying capacity K;  vectorized
\param t independent variable; data vector
\param K carrying capacity; differentiable scalar
\param r growth rate; differentiable scalar
\param n0 initial population size at t=0; differentiable vector
\return  \f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$ 
\ingroup ECOL
**/
dvar_vector logisticK( const dvector& t,  const prevariable& K,  const prevariable& r,  const dvar_vector& n0)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=K/(1.0+elem_prod((K/n0-1.0), exp(-r*t))); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  ecologically parameterized logistic function with carrying capacity K;  vectorized
\param t independent variable; data vector
\param K carrying capacity; differentiable vector
\param r growth rate; differentiable scalar
\param n0 initial population size at t=0; differentiable vector
\return  \f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$ 
\ingroup ECOL
**/
dvar_vector logisticK( const dvector& t,  const dvar_vector& K,  const prevariable& r,  const dvar_vector& n0)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_div(K, 1.0 + elem_prod(elem_div(K, n0)-1.0, exp(-r*t))); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  ecologically parameterized logistic function with carrying capacity K;  vectorized
\param t independent variable; data vector
\param K carrying capacity; differentiable scalar
\param r growth rate; differentiable vector
\param n0 initial population size at t=0; differentiable vector
\return  \f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$ 
\ingroup ECOL
**/
dvar_vector logisticK( const dvector& t,  const prevariable& K,  const dvar_vector& r,  const dvar_vector& n0)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=K/(1.0+elem_prod(K/n0-1.0, exp(-1.0*elem_prod(r,t)))); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  ecologically parameterized logistic function with carrying capacity K;  vectorized
\param t independent variable; data vector
\param K carrying capacity; differentiable vector
\param r growth rate; differentiable vector
\param n0 initial population size at t=0; differentiable vector
\return  \f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$ 
\ingroup ECOL
**/
dvar_vector logisticK( const dvector& t,  const dvar_vector& K,  const dvar_vector& r,  const dvar_vector& n0)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_div(K, 1.0 + elem_prod(elem_div(K, n0)-1.0, exp(-1.0*elem_prod(r,t)))); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------------------3rd variable is a scalar in a random effects model*/
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** ecologically parameterized logistic function with carrying capacity K;  random effects scalar
\param t independent variable; data scalar
\param K carrying capacity; differentiable scalar in a random effects model
\param r growth rate; differentiable scalar in a random effects model
\param n0 initial population size at t=0; differentiable scalar in a random effects model
\return  \f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$ 
\ingroup ECOL
**/
df1b2variable logisticK( const double& t,  const df1b2variable& K,  const df1b2variable& r,  const df1b2variable& n0)
{
	df1b2variable y;
	y=K/(1.0+(K/n0-1.0)*exp(-r*t)); 

    return (y);
}
/** ecologically parameterized logistic function with carrying capacity K;  random effects vectorized
\param t independent variable; data vector
\param K carrying capacity; differentiable scalar in a random effects model
\param r growth rate; differentiable scalar in a random effects model
\param n0 initial population size at t=0; differentiable scalar in a random effects model
\return  \f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$ 
\ingroup ECOL
**/
df1b2vector logisticK( const dvector& t,  const df1b2variable& K,  const df1b2variable& r,  const df1b2variable& n0)
{
	df1b2vector y;
	y=K/(1.0+(K/n0-1.0)*exp(-r*t)); 

    return(y);
}
/** ecologically parameterized logistic function with carrying capacity K;  random effects vectorized
\param t independent variable; data vector
\param K carrying capacity; differentiable vector in a random effects model
\param r growth rate; differentiable scalar in a random effects model
\param n0 initial population size at t=0; differentiable scalar in a random effects model
\return  \f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$ 
\ingroup ECOL
**/
df1b2vector logisticK( const dvector& t,  const df1b2vector& K,  const df1b2variable& r,  const df1b2variable& n0)
{
	df1b2vector y;
	y=elem_div(K, 1.0 + elem_prod(K/n0-1.0, exp(-r*t))); 

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** ecologically parameterized logistic function with carrying capacity K;  random effects vectorized
\param t independent variable; data vector
\param K carrying capacity; differentiable scalar in a random effects model
\param r growth rate; differentiable vector in a random effects model
\param n0 initial population size at t=0; differentiable scalar in a random effects model
\return  \f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$ 
\ingroup ECOL
**/
df1b2vector logisticK( const dvector& t,  const df1b2variable& K,  const df1b2vector& r,  const df1b2variable& n0)
{
	df1b2vector y;
	y=K/(1.0+(K/n0-1.0)*exp(-1.0*elem_prod(r,t))); 

    return(y);
}
/** ecologically parameterized logistic function with carrying capacity K;  random effects vectorized
\param t independent variable; data vector
\param K carrying capacity; differentiable vector in a random effects model
\param r growth rate; differentiable vector in a random effects model
\param n0 initial population size at t=0; differentiable scalar in a random effects model
\return  \f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$ 
\ingroup ECOL
**/
df1b2vector logisticK( const dvector& t,  const df1b2vector& K,  const df1b2vector& r,  const df1b2variable& n0)
{
	df1b2vector y;
	y=elem_div(K, 1.0 + elem_prod(K/n0-1.0, exp(-1.0*elem_prod(r,t)))); 

    return(y);
}


/*---------------------------------------------------------3rd variable is a vector in a random effects model*/
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** ecologically parameterized logistic function with carrying capacity K;  random effects vectorized
\param t independent variable; data vector
\param K carrying capacity; differentiable scalar in a random effects model
\param r growth rate; differentiable scalar in a random effects model
\param n0 initial population size at t=0; differentiable vector in a random effects model
\return  \f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$ 
\ingroup ECOL
**/
df1b2vector logisticK( const dvector& t,  const df1b2variable& K,  const df1b2variable& r,  const df1b2vector& n0)
{
	df1b2vector y;
	y=K/(1.0+elem_prod((K/n0-1.0), exp(-r*t))); 

    return(y);
}
/** ecologically parameterized logistic function with carrying capacity K;  random effects vectorized
\param t independent variable; data vector
\param K carrying capacity; differentiable vector in a random effects model
\param r growth rate; differentiable scalar in a random effects model
\param n0 initial population size at t=0; differentiable vector in a random effects model
\return  \f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$ 
\ingroup ECOL
**/
df1b2vector logisticK( const dvector& t,  const df1b2vector& K,  const df1b2variable& r,  const df1b2vector& n0)
{
	df1b2vector y;
	y=elem_div(K, 1.0 + elem_prod(elem_div(K, n0)-1.0, exp(-r*t))); 

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** ecologically parameterized logistic function with carrying capacity K;  random effects vectorized
\param t independent variable; data vector
\param K carrying capacity; differentiable scalar in a random effects model
\param r growth rate; differentiable vector in a random effects model
\param n0 initial population size at t=0; differentiable vector in a random effects model
\return  \f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$ 
\ingroup ECOL
**/
df1b2vector logisticK( const dvector& t,  const df1b2variable& K,  const df1b2vector& r,  const df1b2vector& n0)
{
	df1b2vector y;
	y=K/(1.0+elem_prod(K/n0-1.0, exp(-1.0*elem_prod(r,t)))); 

    return(y);
}
/** ecologically parameterized logistic function with carrying capacity K;  random effects vectorized
\param t independent variable; data vector
\param K carrying capacity; differentiable vector in a random effects model
\param r growth rate; differentiable vector in a random effects model
\param n0 initial population size at t=0; differentiable vector in a random effects model
\return  \f$ \frac{K}{1+(\frac{K}{n0}-1)e^{-rt}} \f$ 
\ingroup ECOL
**/
df1b2vector logisticK( const dvector& t,  const df1b2vector& K,  const df1b2vector& r,  const df1b2vector& n0)
{
	df1b2vector y;
	y=elem_div(K, 1.0 + elem_prod(elem_div(K, n0)-1.0, exp(-1.0*elem_prod(r,t)))); 

    return(y);
}
