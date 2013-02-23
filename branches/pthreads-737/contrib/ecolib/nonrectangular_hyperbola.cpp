#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 

/*---------------------------------------------------------3rd variable is a scalar*/
/*---------------------------------------------2nd variable is a scalar*/
/**  nonrectangular hyperbolic function; scalar
\param x independent variable; data scalar
\param theta ; differentiable scalar
\param alpha ; differentiable scalar
\param pmax ; differentiable scalar
\return  \f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
\ingroup ECOL
**/
dvariable nonrectangular_hyperbola(const double& x,  const prevariable& theta,  const prevariable& alpha,  const prevariable& pmax)
{
    RETURN_ARRAYS_INCREMENT();	
	dvariable y;
	y=pow(2.0*theta, -1.0)*(alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*theta*alpha*x*pmax, 0));

	RETURN_ARRAYS_DECREMENT();
	return (y);
}
/**  nonrectangular hyperbolic function; vectorized
\param x independent variable; data vector
\param theta ; differentiable scalar
\param alpha ; differentiable scalar
\param pmax ; differentiable scalar
\return  \f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
\ingroup ECOL
**/
dvar_vector nonrectangular_hyperbola(const dvector& x,  const prevariable& theta,  const prevariable& alpha,  const prevariable& pmax)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=pow(2.0*theta, -1.0)*(alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*theta*alpha*x*pmax, 0));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  nonrectangular hyperbolic function; vectorized
\param x independent variable; data vector
\param theta ; differentiable vector
\param alpha ; differentiable scalar
\param pmax ; differentiable scalar
\return  \f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
\ingroup ECOL
**/
dvar_vector nonrectangular_hyperbola(const dvector& x,  const dvar_vector& theta,  const prevariable& alpha,  const prevariable& pmax)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(pow(2.0*theta, -1.0), (alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*elem_prod(theta, x)*alpha*pmax, 0)));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  nonrectangular hyperbolic function; vectorized
\param x independent variable; data vector
\param theta ; differentiable scalar
\param alpha ; differentiable vector
\param pmax ; differentiable scalar
\return  \f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
\ingroup ECOL
**/
dvar_vector nonrectangular_hyperbola(const dvector& x,  const prevariable& theta,  const dvar_vector& alpha,  const prevariable& pmax)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=pow(2.0*theta, -1.0)*(elem_prod(alpha, x)+pmax-pow(pow(elem_prod(alpha, x)+pmax, 2.0) - 4.0*theta*elem_prod(alpha, x)*pmax, 0));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  nonrectangular hyperbolic function; vectorized
\param x independent variable; data vector
\param theta ; differentiable vector
\param alpha ; differentiable vector
\param pmax ; differentiable scalar
\return  \f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
\ingroup ECOL
**/
dvar_vector nonrectangular_hyperbola(const dvector& x,  const dvar_vector& theta,  const dvar_vector& alpha,  const prevariable& pmax)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(pow(2.0*theta, -1.0), (elem_prod(alpha, x)+pmax-pow(pow(elem_prod(alpha, x)+pmax, 2.0) - 4.0*elem_prod(theta, elem_prod(alpha, x))*pmax, 0)));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------------------3rd variable is a vector*/
/*---------------------------------------------2nd variable is a scalar*/
/**  nonrectangular hyperbolic function; vectorized
\param x independent variable; data vector
\param theta ; differentiable scalar
\param alpha ; differentiable scalar
\param pmax ; differentiable vector
\return  \f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
\ingroup ECOL
**/
dvar_vector nonrectangular_hyperbola(const dvector& x,  const prevariable& theta,  const prevariable& alpha,  const dvar_vector& pmax)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=pow(2.0*theta, -1.0)*(alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*theta*alpha*elem_prod(x, pmax), 0));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  nonrectangular hyperbolic function; vectorized
\param x independent variable; data vector
\param theta ; differentiable vector
\param alpha ; differentiable scalar
\param pmax ; differentiable vector
\return  \f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
\ingroup ECOL
**/
dvar_vector nonrectangular_hyperbola(const dvector& x,  const dvar_vector& theta,  const prevariable& alpha,  const dvar_vector& pmax)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(pow(2.0*theta, -1.0), (alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*elem_prod(elem_prod(theta, x), pmax)*alpha, 0)));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  nonrectangular hyperbolic function; vectorized
\param x independent variable; data vector
\param theta ; differentiable scalar
\param alpha ; differentiable vector
\param pmax ; differentiable vector
\return  \f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
\ingroup ECOL
**/
dvar_vector nonrectangular_hyperbola(const dvector& x,  const prevariable& theta,  const dvar_vector& alpha,  const dvar_vector& pmax)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=pow(2.0*theta, -1.0)*(elem_prod(alpha, x)+pmax-pow(pow(elem_prod(alpha, x)+pmax, 2.0) - 4.0*theta*elem_prod(elem_prod(alpha, x), pmax), 0));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  nonrectangular hyperbolic function; vectorized
\param x independent variable; data vector
\param theta ; differentiable vector
\param alpha ; differentiable vector
\param pmax ; differentiable vector
\return  \f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
\ingroup ECOL
**/
dvar_vector nonrectangular_hyperbola(const dvector& x,  const dvar_vector& theta,  const dvar_vector& alpha,  const dvar_vector& pmax)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(pow(2.0*theta, -1.0), (elem_prod(alpha, x)+pmax-pow(pow(elem_prod(alpha, x)+pmax, 2.0) - 4.0*elem_prod(elem_prod(theta, elem_prod(alpha, x)), pmax), 0)));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------------------3rd variable is a scalar in a random effects model*/
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** nonrectangular hyperbolic function; random effects scalar
\param x independent variable; data scalar
\param theta ; differentiable scalar in a random effects model
\param alpha ; differentiable scalar in a random effects model
\param pmax ; differentiable scalar in a random effects model
\return  \f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
\ingroup ECOL
**/
df1b2variable nonrectangular_hyperbola(const double& x,  const df1b2variable& theta,  const df1b2variable& alpha,  const df1b2variable& pmax)
{
	df1b2variable y;
	y=pow(2.0*theta, -1.0)*(alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*theta*alpha*x*pmax, 0));

    return (y);
}
/** nonrectangular hyperbolic function; random effects vectorized
\param x independent variable; data vector
\param theta ; differentiable scalar in a random effects model
\param alpha ; differentiable scalar in a random effects model
\param pmax ; differentiable scalar in a random effects model
\return  \f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
\ingroup ECOL
**/
df1b2vector nonrectangular_hyperbola(const dvector& x,  const df1b2variable& theta,  const df1b2variable& alpha,  const df1b2variable& pmax)
{
	df1b2vector y;
	y=pow(2.0*theta, -1.0)*(alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*theta*alpha*x*pmax, 0));

    return(y);
}
/** nonrectangular hyperbolic function; random effects vectorized
\param x independent variable; data vector
\param theta ; differentiable vector in a random effects model
\param alpha ; differentiable scalar in a random effects model
\param pmax ; differentiable scalar in a random effects model
\return  \f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
\ingroup ECOL
**/
df1b2vector nonrectangular_hyperbola(const dvector& x,  const df1b2vector& theta,  const df1b2variable& alpha,  const df1b2variable& pmax)
{
	df1b2vector y;
	y=elem_prod(pow(2.0*theta, -1.0), (alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*elem_prod(theta, x)*alpha*pmax, 0)));

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** nonrectangular hyperbolic function; random effects vectorized
\param x independent variable; data vector
\param theta ; differentiable scalar in a random effects model
\param alpha ; differentiable vector in a random effects model
\param pmax ; differentiable scalar in a random effects model
\return  \f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
\ingroup ECOL
**/
df1b2vector nonrectangular_hyperbola(const dvector& x,  const df1b2variable& theta,  const df1b2vector& alpha,  const df1b2variable& pmax)
{
	df1b2vector y;
	y=pow(2.0*theta, -1.0)*(elem_prod(alpha, x)+pmax-pow(pow(elem_prod(alpha, x)+pmax, 2.0) - 4.0*theta*elem_prod(alpha, x)*pmax, 0));

    return(y);
}
/** nonrectangular hyperbolic function; random effects vectorized
\param x independent variable; data vector
\param theta ; differentiable vector in a random effects model
\param alpha ; differentiable vector in a random effects model
\param pmax ; differentiable scalar in a random effects model
\return  \f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
\ingroup ECOL
**/
df1b2vector nonrectangular_hyperbola(const dvector& x,  const df1b2vector& theta,  const df1b2vector& alpha,  const df1b2variable& pmax)
{
	df1b2vector y;
	y=elem_prod(pow(2.0*theta, -1.0), (elem_prod(alpha, x)+pmax-pow(pow(elem_prod(alpha, x)+pmax, 2.0) - 4.0*elem_prod(theta, elem_prod(alpha, x))*pmax, 0)));

    return(y);
}


/*---------------------------------------------------------3rd variable is a vector in a random effects model*/
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** nonrectangular hyperbolic function; random effects vectorized
\param x independent variable; data vector
\param theta ; differentiable scalar in a random effects model
\param alpha ; differentiable scalar in a random effects model
\param pmax ; differentiable vector in a random effects model
\return  \f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
\ingroup ECOL
**/
df1b2vector nonrectangular_hyperbola(const dvector& x,  const df1b2variable& theta,  const df1b2variable& alpha,  const df1b2vector& pmax)
{
	df1b2vector y;
	y=pow(2.0*theta, -1.0)*(alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*theta*alpha*elem_prod(x, pmax), 0));

    return(y);
}
/** nonrectangular hyperbolic function; random effects vectorized
\param x independent variable; data vector
\param theta ; differentiable vector in a random effects model
\param alpha ; differentiable scalar in a random effects model
\param pmax ; differentiable vector in a random effects model
\return  \f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
\ingroup ECOL
**/
df1b2vector nonrectangular_hyperbola(const dvector& x,  const df1b2vector& theta,  const df1b2variable& alpha,  const df1b2vector& pmax)
{
	df1b2vector y;
	y=elem_prod(pow(2.0*theta, -1.0), (alpha*x+pmax-pow(pow(alpha*x+pmax, 2.0) - 4.0*elem_prod(elem_prod(theta, x), pmax)*alpha, 0)));

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** nonrectangular hyperbolic function; random effects vectorized
\param x independent variable; data vector
\param theta ; differentiable scalar in a random effects model
\param alpha ; differentiable vector in a random effects model
\param pmax ; differentiable vector in a random effects model
\return  \f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
\ingroup ECOL
**/
df1b2vector nonrectangular_hyperbola(const dvector& x,  const df1b2variable& theta,  const df1b2vector& alpha,  const df1b2vector& pmax)
{
	df1b2vector y;
	y=pow(2.0*theta, -1.0)*(elem_prod(alpha, x)+pmax-pow(pow(elem_prod(alpha, x)+pmax, 2.0) - 4.0*theta*elem_prod(elem_prod(alpha, x), pmax), 0));

    return(y);
}
/** nonrectangular hyperbolic function; random effects vectorized
\param x independent variable; data vector
\param theta ; differentiable vector in a random effects model
\param alpha ; differentiable vector in a random effects model
\param pmax ; differentiable vector in a random effects model
\return  \f$ \frac{1}{2\theta} (\alpha x +p_{max} - \sqrt{(\alpha x +p_{max})^2-4\theta \alpha x p_{max}}) \f$
\ingroup ECOL
**/
df1b2vector nonrectangular_hyperbola(const dvector& x,  const df1b2vector& theta,  const df1b2vector& alpha,  const df1b2vector& pmax)
{
	df1b2vector y;
	y=elem_prod(pow(2.0*theta, -1.0), (elem_prod(alpha, x)+pmax-pow(pow(elem_prod(alpha, x)+pmax, 2.0) - 4.0*elem_prod(elem_prod(theta, elem_prod(alpha, x)), pmax), 0)));

    return(y);
}
