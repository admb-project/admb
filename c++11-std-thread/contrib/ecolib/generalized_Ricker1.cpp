#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 

/*---------------------------------------------------------3rd variable is a scalar*/
/*---------------------------------------------2nd variable is a scalar*/
/**  generalized Ricker function, first parameerization; scalar
\param x independent variable; data scalar
\param x0 ; differentiable scalar
\param A ; differentiable scalar
\param alpha ; differentiable scalar
\return  \f$ A(\frac{x}{x0}e^{(1.0-\frac{x}{x0})})^{\alpha} \f$
\ingroup ECOL
**/
dvariable generalized_Ricker1(const double& x,  const prevariable& x0,  const prevariable& A,  const prevariable& alpha)
{
    RETURN_ARRAYS_INCREMENT();	
	dvariable y;
	y=A*pow((x/x0*exp(1.0-x/x0)), alpha);

	RETURN_ARRAYS_DECREMENT();
	return (y);
}
/**  generalized Ricker function, first parameerization; vectorized
\param x independent variable; data vector
\param x0 ; differentiable scalar
\param A ; differentiable scalar
\param alpha ; differentiable scalar
\return  \f$ A(\frac{x}{x0}e^{(1.0-\frac{x}{x0})})^{\alpha} \f$
\ingroup ECOL
**/
dvar_vector generalized_Ricker1(const dvector& x,  const prevariable& x0,  const prevariable& A,  const prevariable& alpha)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=A*pow(elem_prod(x/x0, exp(1.0-x/x0)), alpha);

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  generalized Ricker function, first parameerization; vectorized
\param x independent variable; data vector
\param x0 ; differentiable vector
\param A ; differentiable scalar
\param alpha ; differentiable scalar
\return  \f$ A(\frac{x}{x0}e^{(1.0-\frac{x}{x0})})^{\alpha} \f$
\ingroup ECOL
**/
dvar_vector generalized_Ricker1(const dvector& x,  const dvar_vector& x0,  const prevariable& A,  const prevariable& alpha)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=A*pow(elem_prod(elem_div(x, x0), exp(1.0-elem_div(x, x0))), alpha);

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  generalized Ricker function, first parameerization; vectorized
\param x independent variable; data vector
\param x0 ; differentiable scalar
\param A ; differentiable vector
\param alpha ; differentiable scalar
\return  \f$ A(\frac{x}{x0}e^{(1.0-\frac{x}{x0})})^{\alpha} \f$
\ingroup ECOL
**/
dvar_vector generalized_Ricker1(const dvector& x,  const prevariable& x0,  const dvar_vector& A,  const prevariable& alpha)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(A, pow(elem_prod(x/x0, exp(1.0-x/x0)), alpha));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  generalized Ricker function, first parameerization; vectorized
\param x independent variable; data vector
\param x0 ; differentiable vector
\param A ; differentiable vector
\param alpha ; differentiable scalar
\return  \f$ A(\frac{x}{x0}e^{(1.0-\frac{x}{x0})})^{\alpha} \f$
\ingroup ECOL
**/
dvar_vector generalized_Ricker1(const dvector& x,  const dvar_vector& x0,  const dvar_vector& A,  const prevariable& alpha)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(A, pow(elem_prod(elem_div(x, x0), exp(1.0-elem_div(x, x0))), alpha));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------------------3rd variable is a vector*/
/*---------------------------------------------2nd variable is a scalar*/
/**  generalized Ricker function, first parameerization; vectorized
\param x independent variable; data vector
\param x0 ; differentiable scalar
\param A ; differentiable scalar
\param alpha ; differentiable vector
\return  \f$ A(\frac{x}{x0}e^{(1.0-\frac{x}{x0})})^{\alpha} \f$
\ingroup ECOL
**/
dvar_vector generalized_Ricker1(const dvector& x,  const prevariable& x0,  const prevariable& A,  const dvar_vector& alpha)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=A*pow(elem_prod(x/x0, exp(1.0-x/x0)), alpha);

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  generalized Ricker function, first parameerization; vectorized
\param x independent variable; data vector
\param x0 ; differentiable vector
\param A ; differentiable scalar
\param alpha ; differentiable vector
\return  \f$ A(\frac{x}{x0}e^{(1.0-\frac{x}{x0})})^{\alpha} \f$
\ingroup ECOL
**/
dvar_vector generalized_Ricker1(const dvector& x,  const dvar_vector& x0,  const prevariable& A,  const dvar_vector& alpha)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=A*pow(elem_prod(elem_div(x, x0), exp(1.0-elem_div(x, x0))), alpha);

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------2nd variable is a vector*/
/**  generalized Ricker function, first parameerization; vectorized
\param x independent variable; data vector
\param x0 ; differentiable scalar
\param A ; differentiable vector
\param alpha ; differentiable vector
\return  \f$ A(\frac{x}{x0}e^{(1.0-\frac{x}{x0})})^{\alpha} \f$
\ingroup ECOL
**/
dvar_vector generalized_Ricker1(const dvector& x,  const prevariable& x0,  const dvar_vector& A,  const dvar_vector& alpha)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(A, pow(elem_prod(x/x0, exp(1.0-x/x0)), alpha));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/**  generalized Ricker function, first parameerization; vectorized
\param x independent variable; data vector
\param x0 ; differentiable vector
\param A ; differentiable vector
\param alpha ; differentiable vector
\return  \f$ A(\frac{x}{x0}e^{(1.0-\frac{x}{x0})})^{\alpha} \f$
\ingroup ECOL
**/
dvar_vector generalized_Ricker1(const dvector& x,  const dvar_vector& x0,  const dvar_vector& A,  const dvar_vector& alpha)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y;
	y=elem_prod(A, pow(elem_prod(elem_div(x, x0), exp(1.0-elem_div(x, x0))), alpha));

	RETURN_ARRAYS_DECREMENT();	
    return (y);
}
/*---------------------------------------------------------3rd variable is a scalar in a random effects model*/
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** generalized Ricker function, first parameerization; random effects scalar
\param x independent variable; data scalar
\param x0 ; differentiable scalar in a random effects model
\param A ; differentiable scalar in a random effects model
\param alpha ; differentiable scalar in a random effects model
\return  \f$ A(\frac{x}{x0}e^{(1.0-\frac{x}{x0})})^{\alpha} \f$
\ingroup ECOL
**/
df1b2variable generalized_Ricker1(const double& x,  const df1b2variable& x0,  const df1b2variable& A,  const df1b2variable& alpha)
{
	df1b2variable y;
	y=A*pow((x/x0*exp(1.0-x/x0)), alpha);

    return (y);
}
/** generalized Ricker function, first parameerization; random effects vectorized
\param x independent variable; data vector
\param x0 ; differentiable scalar in a random effects model
\param A ; differentiable scalar in a random effects model
\param alpha ; differentiable scalar in a random effects model
\return  \f$ A(\frac{x}{x0}e^{(1.0-\frac{x}{x0})})^{\alpha} \f$
\ingroup ECOL
**/
df1b2vector generalized_Ricker1(const dvector& x,  const df1b2variable& x0,  const df1b2variable& A,  const df1b2variable& alpha)
{
	df1b2vector y;
	y=A*pow(elem_prod(x/x0, exp(1.0-x/x0)), alpha);

    return(y);
}
/** generalized Ricker function, first parameerization; random effects vectorized
\param x independent variable; data vector
\param x0 ; differentiable vector in a random effects model
\param A ; differentiable scalar in a random effects model
\param alpha ; differentiable scalar in a random effects model
\return  \f$ A(\frac{x}{x0}e^{(1.0-\frac{x}{x0})})^{\alpha} \f$
\ingroup ECOL
**/
df1b2vector generalized_Ricker1(const dvector& x,  const df1b2vector& x0,  const df1b2variable& A,  const df1b2variable& alpha)
{
	df1b2vector y;
	y=A*pow(elem_prod(elem_div(x, x0), exp(1.0-elem_div(x, x0))), alpha);

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** generalized Ricker function, first parameerization; random effects vectorized
\param x independent variable; data vector
\param x0 ; differentiable scalar in a random effects model
\param A ; differentiable vector in a random effects model
\param alpha ; differentiable scalar in a random effects model
\return  \f$ A(\frac{x}{x0}e^{(1.0-\frac{x}{x0})})^{\alpha} \f$
\ingroup ECOL
**/
df1b2vector generalized_Ricker1(const dvector& x,  const df1b2variable& x0,  const df1b2vector& A,  const df1b2variable& alpha)
{
	df1b2vector y;
	y=elem_prod(A, pow(elem_prod(x/x0, exp(1.0-x/x0)), alpha));

    return(y);
}
/** generalized Ricker function, first parameerization; random effects vectorized
\param x independent variable; data vector
\param x0 ; differentiable vector in a random effects model
\param A ; differentiable vector in a random effects model
\param alpha ; differentiable scalar in a random effects model
\return  \f$ A(\frac{x}{x0}e^{(1.0-\frac{x}{x0})})^{\alpha} \f$
\ingroup ECOL
**/
df1b2vector generalized_Ricker1(const dvector& x,  const df1b2vector& x0,  const df1b2vector& A,  const df1b2variable& alpha)
{
	df1b2vector y;
	y=elem_prod(A, pow(elem_prod(elem_div(x, x0), exp(1.0-elem_div(x, x0))), alpha));

    return(y);
}


/*---------------------------------------------------------3rd variable is a vector in a random effects model*/
/*---------------------------------------------2nd variable is a scalar in a random effects model*/
/*----------------------1st varible contains random effects*/
/** generalized Ricker function, first parameerization; random effects vectorized
\param x independent variable; data vector
\param x0 ; differentiable scalar in a random effects model
\param A ; differentiable scalar in a random effects model
\param alpha ; differentiable vector in a random effects model
\return  \f$ A(\frac{x}{x0}e^{(1.0-\frac{x}{x0})})^{\alpha} \f$
\ingroup ECOL
**/
df1b2vector generalized_Ricker1(const dvector& x,  const df1b2variable& x0,  const df1b2variable& A,  const df1b2vector& alpha)
{
	df1b2vector y;
	y=A*pow(elem_prod(x/x0, exp(1.0-x/x0)), alpha);

    return(y);
}
/** generalized Ricker function, first parameerization; random effects vectorized
\param x independent variable; data vector
\param x0 ; differentiable vector in a random effects model
\param A ; differentiable scalar in a random effects model
\param alpha ; differentiable vector in a random effects model
\return  \f$ A(\frac{x}{x0}e^{(1.0-\frac{x}{x0})})^{\alpha} \f$
\ingroup ECOL
**/
df1b2vector generalized_Ricker1(const dvector& x,  const df1b2vector& x0,  const df1b2variable& A,  const df1b2vector& alpha)
{
	df1b2vector y;
	y=A*pow(elem_prod(elem_div(x, x0), exp(1.0-elem_div(x, x0))), alpha);

    return(y);
}

/*---------------------------------------------2nd variable is a vector in a random effects model*/
/*----------------------1st varible contains random effects*/
/** generalized Ricker function, first parameerization; random effects vectorized
\param x independent variable; data vector
\param x0 ; differentiable scalar in a random effects model
\param A ; differentiable vector in a random effects model
\param alpha ; differentiable vector in a random effects model
\return  \f$ A(\frac{x}{x0}e^{(1.0-\frac{x}{x0})})^{\alpha} \f$
\ingroup ECOL
**/
df1b2vector generalized_Ricker1(const dvector& x,  const df1b2variable& x0,  const df1b2vector& A,  const df1b2vector& alpha)
{
	df1b2vector y;
	y=elem_prod(A, pow(elem_prod(x/x0, exp(1.0-x/x0)), alpha));

    return(y);
}
/** generalized Ricker function, first parameerization; random effects vectorized
\param x independent variable; data vector
\param x0 ; differentiable vector in a random effects model
\param A ; differentiable vector in a random effects model
\param alpha ; differentiable vector in a random effects model
\return  \f$ A(\frac{x}{x0}e^{(1.0-\frac{x}{x0})})^{\alpha} \f$
\ingroup ECOL
**/
df1b2vector generalized_Ricker1(const dvector& x,  const df1b2vector& x0,  const df1b2vector& A,  const df1b2vector& alpha)
{
	df1b2vector y;
	y=elem_prod(A, pow(elem_prod(elem_div(x, x0), exp(1.0-elem_div(x, x0))), alpha));

    return(y);
}
