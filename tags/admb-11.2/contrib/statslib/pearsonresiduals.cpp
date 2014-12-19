#include "statsLib.h"

/**
* @file pearsonresiduals.cpp
* @brief // Pearson residuals
* 
* \ingroup STATLIB
* @author Chris Grandin, Steve Martell
* 
* @date 12/13/2011
* @remarks
* This function calculates the pearson residuals for a multinomial
* distribution.
*/

dvector pearson_residuals(long m, dvector obs_p, dvector pred_p)
{
	{
		dvector O=obs_p/sum(obs_p);
		dvector P=pred_p/sum(pred_p);

		//double neff;		//effective sample size
		//neff=norm(elem_prod(pred_p,1.-pred_p))/norm2(obs_p-pred_p);
		dvector var=elem_prod(P,(1.-P))/m;
		//max(var)<=0 ? var=1.: var=var;
		if(max(var)<=0) var=1;
		dvector r=elem_div(O-P,sqrt(var+0.01/14));
		if(sum(P)==0) r=0;
		return(r);
	}
}

