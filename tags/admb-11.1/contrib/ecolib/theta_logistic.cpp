#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 

/*---------------------------------------------------------3rd variable is a scalar*/
/*---------------------------------------------2nd variable is a scalar*/
/**  theta logistic function; scalar
\param t independent variable; data scalar
\param K carrying capacity;  differentiable scalar
\param r growth rate; differentiable scalar
\param n0 population size at t=0;  differentiable scalar
\return  \f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$ 
\ingroup ECOL
**/
dvariable theta_logistic(const double& t,  const prevariable& K,  const prevariable& r,  const prevariable& n0, const prevariable& theta)
{
    RETURN_ARRAYS_INCREMENT();	
	dvariable y;
	y=pow(pow(K, -theta) + (pow(n0, -theta) - pow(K, -theta))*exp(-(r*t)*theta), -1.0/theta); 

	RETURN_ARRAYS_DECREMENT();
	return (y);
}
/**  theta logistic function; vectorized
\param t independent variable; data vector
\param K carrying capacity;  differentiable scalar
\param r growth rate; differentiable scalar
\param n0 population size at t=0;  differentiable scalar
\return  \f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$ 
\ingroup ECOL
**/
dvar_vector theta_logistic(const dvector& t,  const prevariable& K,  const prevariable& r,  const prevariable& n0, const prevariable& theta)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=pow(pow(K, -theta) + (pow(n0, -theta) - pow(K, -theta))*exp(-(r*t)*theta), -1.0/theta); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  theta logistic function; vectorized
\param t independent variable; data vector
\param K carrying capacity;  differentiable vector
\param r growth rate; differentiable scalar
\param n0 population size at t=0;  differentiable scalar
\return  \f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$ 
\ingroup ECOL
**/
dvar_vector theta_logistic(const dvector& t,  const dvar_vector& K,  const prevariable& r,  const prevariable& n0, const prevariable& theta)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-(r*t)*theta)), -1.0/theta); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  theta logistic function; vectorized
\param t independent variable; data vector
\param K carrying capacity;  differentiable scalar
\param r growth rate; differentiable vector
\param n0 population size at t=0;  differentiable scalar
\return  \f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$ 
\ingroup ECOL
**/
dvar_vector theta_logistic(const dvector& t,  const prevariable& K,  const dvar_vector& r,  const prevariable& n0, const prevariable& theta)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=pow(pow(K, -theta) + (pow(n0, -theta) - pow(K, -theta))*exp(-1.0*elem_prod(r, t)*theta), -1.0/theta); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  theta logistic function; vectorized
\param t independent variable; data vector
\param K carrying capacity;  differentiable vector
\param r growth rate; differentiable vector
\param n0 population size at t=0;  differentiable scalar
\return  \f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$ 
\ingroup ECOL
**/
dvar_vector theta_logistic(const dvector& t,  const dvar_vector& K,  const dvar_vector& r,  const prevariable& n0, const prevariable& theta)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-1.0*elem_prod(r, t)*theta)),-1.0/theta); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------------------3rd variable is a vector*/
/*---------------------------------------------2nd variable is a scalar*/
/**  theta logistic function; vectorized
\param t independent variable; data vector
\param K carrying capacity;  differentiable scalar
\param r growth rate; differentiable scalar
\param n0 population size at t=0;  differentiable vector
\return  \f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$ 
\ingroup ECOL
**/
dvar_vector theta_logistic(const dvector& t,  const prevariable& K,  const prevariable& r,  const dvar_vector& n0, const prevariable& theta)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-(r*t)*theta)), -1.0/theta); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  theta logistic function; vectorized
\param t independent variable; data vector
\param K carrying capacity;  differentiable vector
\param r growth rate; differentiable scalar
\param n0 population size at t=0;  differentiable vector
\return  \f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$ 
\ingroup ECOL
**/
dvar_vector theta_logistic(const dvector& t,  const dvar_vector& K,  const prevariable& r,  const dvar_vector& n0, const prevariable& theta)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-(r*t)*theta)), -1.0/theta); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  theta logistic function; vectorized
\param t independent variable; data vector
\param K carrying capacity;  differentiable scalar
\param r growth rate; differentiable vector
\param n0 population size at t=0;  differentiable vector
\return  \f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$ 
\ingroup ECOL
**/
dvar_vector theta_logistic(const dvector& t,  const prevariable& K,  const dvar_vector& r,  const dvar_vector& n0, const prevariable& theta)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-1.0*elem_prod(r, t)*theta)),-1.0/theta); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  theta logistic function; vectorized
\param t independent variable; data vector
\param K carrying capacity;  differentiable vector
\param r growth rate; differentiable vector
\param n0 population size at t=0;  differentiable vector
\return  \f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$ 
\ingroup ECOL
**/
dvar_vector theta_logistic(const dvector& t,  const dvar_vector& K,  const dvar_vector& r,  const dvar_vector& n0, const prevariable& theta)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-1.0*elem_prod(r, t)*theta)),-1.0/theta); 

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------------------3rd variable is a scalar in a random effects model*/
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** theta logistic function; random effects scalar
\param t independent variable; data scalar
\param K carrying capacity;  differentiable scalar in a random effects model
\param r growth rate; differentiable scalar in a random effects model
\param n0 population size at t=0;  differentiable scalar in a random effects model
\return  \f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$ 
\ingroup ECOL
**/
df1b2variable theta_logistic(const double& t,  const df1b2variable& K,  const df1b2variable& r,  const df1b2variable& n0, const df1b2variable& theta)
{
	df1b2variable y;
	y=pow(pow(K, -theta) + (pow(n0, -theta) - pow(K, -theta))*exp(-(r*t)*theta), -1.0/theta); 

    return (y);
}
/** theta logistic function; random effects vectorized
\param t independent variable; data vector
\param K carrying capacity;  differentiable scalar in a random effects model
\param r growth rate; differentiable scalar in a random effects model
\param n0 population size at t=0;  differentiable scalar in a random effects model
\return  \f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$ 
\ingroup ECOL
**/
df1b2vector theta_logistic(const dvector& t,  const df1b2variable& K,  const df1b2variable& r,  const df1b2variable& n0, const df1b2variable& theta)
{
	df1b2vector y;
	y=pow(pow(K, -theta) + (pow(n0, -theta) - pow(K, -theta))*exp(-(r*t)*theta), -1.0/theta); 

    return(y);
}
/** theta logistic function; random effects vectorized
\param t independent variable; data vector
\param K carrying capacity;  differentiable vector in a random effects model
\param r growth rate; differentiable scalar in a random effects model
\param n0 population size at t=0;  differentiable scalar in a random effects model
\return  \f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$ 
\ingroup ECOL
**/
df1b2vector theta_logistic(const dvector& t,  const df1b2vector& K,  const df1b2variable& r,  const df1b2variable& n0, const df1b2variable& theta)
{
	df1b2vector y;
	y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-(r*t)*theta)), -1.0/theta); 

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** theta logistic function; random effects vectorized
\param t independent variable; data vector
\param K carrying capacity;  differentiable scalar in a random effects model
\param r growth rate; differentiable vector in a random effects model
\param n0 population size at t=0;  differentiable scalar in a random effects model
\return  \f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$ 
\ingroup ECOL
**/
df1b2vector theta_logistic(const dvector& t,  const df1b2variable& K,  const df1b2vector& r,  const df1b2variable& n0, const df1b2variable& theta)
{
	df1b2vector y;
	y=pow(pow(K, -theta) + (pow(n0, -theta) - pow(K, -theta))*exp(-1.0*elem_prod(r, t)*theta), -1.0/theta); 

    return(y);
}
/** theta logistic function; random effects vectorized
\param t independent variable; data vector
\param K carrying capacity;  differentiable vector in a random effects model
\param r growth rate; differentiable vector in a random effects model
\param n0 population size at t=0;  differentiable scalar in a random effects model
\return  \f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$ 
\ingroup ECOL
**/
df1b2vector theta_logistic(const dvector& t,  const df1b2vector& K,  const df1b2vector& r,  const df1b2variable& n0, const df1b2variable& theta)
{
	df1b2vector y;
	y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-1.0*elem_prod(r, t)*theta)),-1.0/theta); 

    return(y);
}


/*---------------------------------------------------------3rd variable is a vector in a random effects model*/
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** theta logistic function; random effects vectorized
\param t independent variable; data vector
\param K carrying capacity;  differentiable scalar in a random effects model
\param r growth rate; differentiable scalar in a random effects model
\param n0 population size at t=0;  differentiable vector in a random effects model
\return  \f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$ 
\ingroup ECOL
**/
df1b2vector theta_logistic(const dvector& t,  const df1b2variable& K,  const df1b2variable& r,  const df1b2vector& n0, const df1b2variable& theta)
{
	df1b2vector y;
	y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-(r*t)*theta)), -1.0/theta); 

    return(y);
}
/** theta logistic function; random effects vectorized
\param t independent variable; data vector
\param K carrying capacity;  differentiable vector in a random effects model
\param r growth rate; differentiable scalar in a random effects model
\param n0 population size at t=0;  differentiable vector in a random effects model
\return  \f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$ 
\ingroup ECOL
**/
df1b2vector theta_logistic(const dvector& t,  const df1b2vector& K,  const df1b2variable& r,  const df1b2vector& n0, const df1b2variable& theta)
{
	df1b2vector y;
	y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-(r*t)*theta)), -1.0/theta); 

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** theta logistic function; random effects vectorized
\param t independent variable; data vector
\param K carrying capacity;  differentiable scalar in a random effects model
\param r growth rate; differentiable vector in a random effects model
\param n0 population size at t=0;  differentiable vector in a random effects model
\return  \f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$ 
\ingroup ECOL
**/
df1b2vector theta_logistic(const dvector& t,  const df1b2variable& K,  const df1b2vector& r,  const df1b2vector& n0, const df1b2variable& theta)
{
	df1b2vector y;
	y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-1.0*elem_prod(r, t)*theta)),-1.0/theta); 

    return(y);
}
/** theta logistic function; random effects vectorized
\param t independent variable; data vector
\param K carrying capacity;  differentiable vector in a random effects model
\param r growth rate; differentiable vector in a random effects model
\param n0 population size at t=0;  differentiable vector in a random effects model
\return  \f$ (K^{-\theta}+(n0^{-\theta}-K^{-\theta})e^{-r\theta t})^{-1/\theta} \f$ 
\ingroup ECOL
**/
df1b2vector theta_logistic(const dvector& t,  const df1b2vector& K,  const df1b2vector& r,  const df1b2vector& n0, const df1b2variable& theta)
{
	df1b2vector y;
	y=pow(pow(K, -theta) + elem_prod(pow(n0, -theta) - pow(K, -theta), exp(-1.0*elem_prod(r, t)*theta)),-1.0/theta); 

    return(y);
}
