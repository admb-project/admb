#include "statsLib.h"

/**
* \file baranov.cpp
* \brief Routines for iteratively solving the Baranov catch equation.
* \ingroup STATLIB
* \author Steven Martell
* \date 2/28/2011
* 
* The general form of the Baranov catch equation is given by:
* 
* \f[
*    C = \frac{N F(1-\exp(-F-M))}{F+M}
* \f]
* where \f$ C \f$ is the catch (in either total numbers or total weight)
* \f$N\f$ is the abundance at the start of the time step, \f$ F\f$ is the 
* instantaneous fishing mortality rate \f$M\f$ is the instantaneous natural mortality rate.
* The Baranov catch equation is a transcedental equation; here Newtons root finding
* method is implemented to determine \f$F\f$.
* 
* The basic algorithm is as follows:
* 
* 1) Set initial guess for \f$F\f$ based on Popes approximation \f$ F=\frac{C}{N \exp(-0.5M)}\f$.
* 
* 2) Calculate the predicted catch \f$\acute{C}\f$ based on initial \f$F\f$
* 
* 3) Calculate the derivative of the catch equation 
* 	\f$ \frac{\partial{C}}{\partial{F}} ={\frac {N \left( 1-{{\rm e}^{-M-F}} \right) }{M+F}}+{\frac {NF{
{\rm e}^{-M-F}}}{M+F}}-{\frac {NF \left( 1-{{\rm e}^{-M-F}} \right) }{
 \left( M+F \right) ^{2}}}
 \f$
 * 
 * 4) Update estimate of \f$ F \f$ using
 *  \f$ F_{i+1} = F_i - \frac{\acute{C}-C}{\frac{\partial{C}}{\partial{F}}}
 *  \f$
 * 
 * 
 * At present this function is only implemented for data-type variables.
**/

/** 
	\author Steven James Dean Martell UBC Fisheries Centre
	\date 2011-07-12
	\param  ct the observed catch
	\param  m the instantaneous natural mortality rate
	\param va a vector of age-specific selectivities.
	\param ba the initial numbers or biomass (same units as the catch) at age.
	\return ft the instantaneous fishing mortality rate for fully selected (va=1) individuals.
	\sa
**/	
double get_ft(const double& ct, const double& m, const dvector& va, const dvector& ba)
{
	double ft;
	//initial guess for ft
	ft=ct/(va*(ba*exp(-m/2.)));
	
	for(int i=1;i<=50;i++)
	{
		dvector f = ft*va;
		dvector z = m+f;
		dvector s = exp(-z);
		dvector o = (1.-s);
		
		dvector t1 = elem_div(f,z);
		dvector t2 = elem_prod(t1,o);
		dvector t3 = elem_prod(o,ba);
		//predicted catch
		double pct = t2*ba;
		
		//derivative of catch wrt ft
		double dct = sum(
			elem_div(t3,z) 
			- elem_div(elem_prod(f,t3),square(z))
			+ elem_prod(elem_prod(t1,s),ba));
		
		ft -= (pct-ct)/dct;  //newton step
		//if(fabs(pct-ct)<1.e-9) break; //do not use for dvariables
	}
	
	return(ft);
}

/** \brief Solving the Baranov catch equation for multiple fleets.
	\author Steven James Dean Martell UBC Fisheries Centre
	\date 2011-07-12
	\param  ct a vector of observed catch for each fleet.
	\param  m the instantaneous natural mortality rate (age-independent).
	\param V a matrix of age-specific selectivities where each row corresponds to the fleet.
	\param ba the initial numbers or biomass (same units as the catch) at age.
	\return ft a vector of instantaneous fishing mortality rate for fully selected (va=1) individuals
	* for each fishing fleet.
	\sa
**/
dvector get_ft( dvector& ct,const double& m, const dmatrix& V,const dvector& ba )
{
	/*  ARGUMENTS:
	   ct is the observed catch for each fleet
	   m is the natural mortality rate
	   va is the vulnerability row fleet, col age va(1,ngear,1,nage)
	   ba is the start of year biomass at age
	*/
	
	int i,a,A;
	double minsurv = 0.05;
	int ng=size_count(ct);	//number of gears
	a=ba.indexmin(); A=ba.indexmax();
	dvector ft(1,ng); ft=0;
	dvector ctmp(1,ng);
	dvector ct_hat(1,ng);	//predicted catch
	dvector dct_hat(1,ng);	//derivative
	dvector zage(a,A);
	dvector sage(a,A);
	dvector ominus(a,A);
	dmatrix F(1,ng,a,A);
	
	
	//initial guess for ft=ct/(0.98 Bt);
	ctmp=ct;
	
	for(i=1;i<=ng;i++)
	{   
		ft(i) = ctmp(i)/(0.98*ba*V(i)*exp(-0.5*m));
		if(1.-ft(i)<minsurv)
		{
			ft(i)=1.-minsurv;
			ctmp=ft(i)*ba*V(i)*exp(-0.5*m);
		}
	}
	ct=ctmp;	//don't do this for the differentiable version.
	
	//now solve baranov catch equation iteratively.
	for(int iter=1; iter<=17; iter++)
	{
		for(i=1;i<=ng;i++)F(i)=ft(i)*V(i);
		zage=m+colsum(F);
		sage=mfexp(-zage);
		ominus=(1.-sage);
		
		for(i=1;i<=ng;i++)
		{   
			dvector t1 = elem_div(F(i),zage);
			dvector t2 = elem_prod(t1,ominus);
			dvector t3 = elem_prod(ominus,ba);
			
			ct_hat(i) = t2*ba;
			
			dct_hat(i) = sum(
						elem_div(t3,zage)
						- elem_div(elem_prod(F(i),t3),square(zage))
						+ elem_prod(elem_prod(t1,sage),ba));
				 
		    ft(i) -= (ct_hat(i)-ctmp(i))/dct_hat(i);
		}
		//cout<<iter<<"\t"<<ft<<"\t"<<ct_hat-ct<<endl;
	}
	//cout<<ft<<"\t\t"<<ct<<"\t\t"<<ctmp<<endl;
	
	return(ft);
}  

/** \brief Solving the Baranov catch equation for multiple fleets.
	\author Steven James Dean Martell UBC Fisheries Centre
	\date 2011-07-12
	\param  ct a vector of observed catch for each fleet.
	\param  m the instantaneous natural mortality rate (age-independent).
	\param V a matrix of age-specific selectivities where each row corresponds to the fleet.
	\param na a vector of initial numbers or biomass (same units as the catch) at age.
	\param wa a vector of mean weights-at-age
	\return ft a vector of instantaneous fishing mortality rate for fully selected (va=1) individuals
	* for each fishing fleet.
	\sa
**/

dvector get_ft( dvector& ct,const double& m, const dmatrix& V,const dvector& na, const dvector& wa )
{
	/*  ARGUMENTS:
	   ct is the observed catch for each fleet
	   m is the natural mortality rate
	   va is the vulnerability row fleet, col age va(1,ngear,1,nage)
	   na is the start of year numbers at age
	   wa is the mean weight-at-age
	*/

	int i,a,A;
	double minsurv = 0.05;
	int ng=size_count(ct);	//number of gears
	a=na.indexmin(); A=na.indexmax();
	dvector ft(1,ng); ft=0;
	dvector ctmp(1,ng);
	dvector ct_hat(1,ng);	//predicted catch
	dvector dct_hat(1,ng);	//derivative
	dvector ba(a,A);		//biomass at age
	dvector ca(a,A);		//catch-at-age in numbers
	dvector zage(a,A);
	dvector sage(a,A);
	dvector ominus(a,A);
	dmatrix F(1,ng,a,A);
	
	
	//initial guess for ft=ct/(0.98 Bt);
	ctmp=ct;
	ba = elem_prod(na,wa);
	for(i=1;i<=ng;i++)
	{   
		ft(i) = ctmp(i)/(0.98*ba*V(i)*exp(-0.5*m));
		if(1.-ft(i)<minsurv)
		{
			ft(i)=1.-minsurv;
			ctmp(i)=ft(i)*ba*V(i)*exp(-0.5*m);
		}
	}
	ct=ctmp;	//don't do this for the differentiable version.
	
	//now solve baranov catch equation iteratively.
	for(int iter=1; iter<=17; iter++)
	{
		for(i=1;i<=ng;i++)F(i)=ft(i)*V(i);
		zage=m+colsum(F);
		sage=mfexp(-zage);
		ominus=(1.-sage);
		
		for(i=1;i<=ng;i++)
		{   
			dvector t1 = elem_div(F(i),zage);
			dvector t2 = elem_prod(t1,ominus);
			dvector t3 = elem_prod(ominus,na);
			ca = elem_prod(t2,na);
			
			ct_hat(i) = ca*wa;
			
			dvector t4 = ft(i)*square(V(i));
			
			dvector t5 = elem_div(elem_prod(elem_prod(V(i),ominus),na),zage)
				- elem_div(elem_prod(elem_prod(t4,ominus),na),square(zage))
				+ elem_div(elem_prod(elem_prod(t4,sage),na),zage);
			dct_hat(i) = t5*wa;
				 
		    ft(i) -= (ct_hat(i)-ctmp(i))/dct_hat(i);
		}
		//cout<<iter<<"\t"<<ft<<"\t"<<ct_hat-ctmp<<endl;
		//SJDM, this algorithm does converge niceley for multiple fleets
	}
	//cout<<ft<<"\t\t"<<ct<<"\t\t"<<ctmp<<endl;
	//cout<<ct<<endl;
	return(ft);
}  

