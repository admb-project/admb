#include "statsLib.h"

/**
* @file multifan.cpp
* @brief /Robust normal approximation to the multinomial distribution
* 
* \ingroup STATLIB
* @author Chris Grandin, Steve Martell
* 
* @date 12/13/2011
* @remarks
*/

dvariable multifan(const dmatrix oprop,const dvar_matrix& pprop, const int& Nsamp)
{	//Vivian Haist.
    dvariable extra=0.1/14.;
    dvar_matrix resid=elem_div((oprop-pprop),sqrt((elem_prod(pprop,1.-pprop)+extra)/Nsamp));
    return sum(0.5*log(elem_prod(pprop,1. -pprop)+extra) -log(mfexp(-0.5*elem_prod(resid,resid))+0.01));
}

dvariable multifan(const int& n, const dmatrix obs, const dvar_matrix pred,double& nef)
{
	int A=obs.colmax()-obs.colmin()+1;
	//dvar_matrix xi=(elem_prod(1.-pred,pred)+0.1/A)/n; //variance from Fourniers paper.
	dvar_matrix xi=(elem_prod(1.-obs,obs)+0.1/A)/n;	 //variance from the multifanCL manual.
	dvar_matrix resid=obs-pred;
	nef=value(sum(elem_prod(1.-pred,pred))/sum(elem_prod(resid,resid)));
	return sum(0.5*log(2.*M_PI*xi)-log(mfexp(-0.5*elem_div(elem_prod(resid,resid),xi))+0.01));
}

dvariable multifan(const double& s,const dvector obsQ,const dvar_vector& preQ, double& nmle)
{
	//using Fournier's robust likelihood for length frequency data.
	//s is the sample size
	//neff is the sample size limit  This seems to be fucked...
	//RETURN_ARRAYS_INCREMENT();
	dvariable like;
	dvariable tau;
	int lb=obsQ.indexmin();
	int nb=obsQ.indexmax();

	dvar_vector epsilon(lb,nb);
	dvar_vector Q=obsQ/sum(obsQ);
	dvar_vector Qhat=preQ/sum(preQ);

	//dvariable nmle;		//effective sample size
	nmle=value(sum(elem_prod(Qhat,1.-Qhat))/norm2(Q-Qhat));
	cout<<nmle<<endl;
	tau=1./s;
	epsilon=elem_prod(1.-Qhat,Qhat);

	like=0.5*sum(log(2.*M_PI*(epsilon+0.1/nb)))+nb*log(sqrt(tau));
	like+= -1.*sum(log(mfexp(-1.*elem_div(square(Q-Qhat),2.*tau*(epsilon+0.1/nb)))+0.01));
	//RETURN_ARRAYS_DECREMENT();
	return like;
}

