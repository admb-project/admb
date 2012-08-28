#include "statsLib.h"

/**
* @file alk.cpp
* @brief Age-length probability transition matrix.
* @remarks
* This file contains a function for computing a conditional
* probability transition from age-to-length. This is also known
* as an age-length-key in standard Fisheries Stock assessment jargon.
* This function is useful for converting proportions-at-age to 
* length-at-age by mulitplying a vector of age proportions times
* the age-length-key.  The result is a vector of lengths.
* Note that in this function the rows are ages, and colums are length
* intervals.
*  
* 
* @author Steven Martell
* @date 2/27/2011
* 
* The function is implemented as
* \f[
* 	P(x|a)
* \f]
* where \f$P(x|a)\f$ is the probabilty of being in the length interval \f$x\f$
* for a given age \f$a\f$.
*/


/** \brief Age Length Key
	
	
	\author Steven James Dean Martell UBC Fisheries Centre
	\date 2011-06-28
	\param  mu is the mean length-at-age
	\param  sig is the std in mean length-at-age
	\param x is the vector of break points for the length bins
	\return dvar_matrix containing the probability of length(x) for a given age(a)
	\sa
        \ingroup STATLIB
**/
dvar_matrix ageLengthKey(const dvar_vector& mu, const dvar_vector& sig, const dvector& x)
{
	RETURN_ARRAYS_INCREMENT();
	int i, j;
	dvariable z1;
	dvariable z2;
	int si,ni; si=mu.indexmin(); ni=mu.indexmax();
	int sj,nj; sj=x.indexmin(); nj=x.indexmax()-1;
	dvar_matrix pdf(si,ni,sj,nj);
	pdf.initialize();
	//double xs=0.5*(x[sj+1]-x[sj]);
	for(i=si;i<=ni;i++) //loop over ages
	{
		 for(j=sj;j<=nj;j++) //loop over length bins
		{
			z1=(x(j)-mu(i))/sig(i);
			z2=(x(j+1)-mu(i))/sig(i);
			pdf(i,j)=cumd_norm(z2)-cumd_norm(z1);
		}//end nbins
		pdf(i)/=sum(pdf(i));
	}//end nage
	
	RETURN_ARRAYS_DECREMENT();
	return(pdf);
}


/** \brief Age Length Key
	
	
	\author Steven James Dean Martell UBC Fisheries Centre
	\date 2011-06-28
	\param  mu is the mean length-at-age
	\param  sig is the std in mean length-at-age
	\param x is the vector of break points for the length bins
	\return dmatrix containing the probability of length(x) for a given age(a)
	\sa
**/
dmatrix ageLengthKey(const dvector& mu, const dvector& sig, const dvector& x)
{
	RETURN_ARRAYS_INCREMENT();
	int i, j;
	double z1;
	double z2;
	int si,ni; si=mu.indexmin(); ni=mu.indexmax();
	int sj,nj; sj=x.indexmin(); nj=x.indexmax()-1;
	dmatrix pdf(si,ni,sj,nj);
	pdf.initialize();
	//double xs=0.5*(x[sj+1]-x[sj]);
	for(i=si;i<=ni;i++) //loop over ages
	{
		 for(j=sj;j<=nj;j++) //loop over length bins
		{
			z1=(x(j)-mu(i))/sig(i);
			z2=(x(j+1)-mu(i))/sig(i);
			pdf(i,j)=cumd_norm(z2)-cumd_norm(z1);
		}//end nbins
		pdf(i)/=sum(pdf(i));
	}//end nage
	
	RETURN_ARRAYS_DECREMENT();
	return(pdf);
}

dvar_matrix ALK(dvar_vector mu, dvar_vector sig, dvector x)
{
	RETURN_ARRAYS_INCREMENT();
	int i, j;
	dvariable z1;
	dvariable z2;
	int si,ni; si=mu.indexmin(); ni=mu.indexmax();
	int sj,nj; sj=x.indexmin(); nj=x.indexmax();
	dvar_matrix pdf(si,ni,sj,nj);
	pdf.initialize();
	double xs=0.5*(x[sj+1]-x[sj]);
	for(i=si;i<=ni;i++) //loop over ages
	{
		 for(j=sj;j<=nj;j++) //loop over length bins
		{
			z1=((x(j)-xs)-mu(i))/sig(i);
			z2=((x(j)+xs)-mu(i))/sig(i);
			pdf(i,j)=cumd_norm(z2)-cumd_norm(z1);
		}//end nbins
		pdf(i)/=sum(pdf(i));
	}//end nage
	//pdf/=sum(pdf);
	RETURN_ARRAYS_DECREMENT();
	return(pdf);
}

