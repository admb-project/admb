
 /** 
	* \file	qfc_est.cpp
	*	\date 7/18/2011
	* \author Weihai Liu
	* \ingroup QFC
	*
	*  Following user defined functions are more useful for doing estimation model in admb,
  *  the easy way to use these functions is put this cpp file in the same directory with your tpl file
  *  and under the GLOBALS_SECTION , add a line on top as   #include "qfc_est.cpp" ,
	*	 there is a testfunction.tpl file within this folder show how to use these functions.
  *
  *  ================  brief list for usage  ============================\n
  *  1. want to constrain the vector of probability sum as 1 and each as (0,1),  
  *     see logitProp() and its inverse invLogitProp()\n
  *  2. overloaded posfun() for vector and matrix  \n
	*  3. want to constrain the parameter within some upper bound only, see mf_upper_bound2() \n
  *  4. nll(neg. log. likelihood) for some distributions  \n 
  *  5. nll for multinomial, binomial and possion, see nllBinomial(), nllMultiNomial(), nllPoisson() \n
  *  6. nll for dirichlet, see nllDirichlet()  \n
  *  7. nll for gamma and beta, see nllGamma(), nllBeta()  \n
  *  8. nll for negative binomial N(m,s) with its tau version, see nllNegativeBinomial(), nllNegativeBinomial2()\n
  *  9. nll for normal N(m,sigma) and its tau version N(m,tau), see nllNormal(), nllNormal2()  \n 
  *  10. nll for lognormal LN(m,sigma0 and its tau version LN(m,tau), see nllLognormal(), nllLognormal2()  \n 
  *  =============================================================\n
  *
  *  found any bug , contact Weihai Liu at liuweih@msu.edu \n
  *  Quantitative Fisheries Center(QFC), Michigan State University
  */

#define __QFC_EST__
#if !defined(__QFC_SIM__) //only include the following header file and constants once
  #include <math.h>
  #include <admodel.h>
  #include <df1b2fun.h>
  #include <adrndeff.h>

  // define constant variable
  const double EPS = 1.e-30;          //tiny number to avoid 0 in log

#endif




  /** constrain probability vector as 1 and 
	 * I forgot who create this first, may give credit to Punt., 
	 * let logit(p)=log(p/(1-p))=a, so p=exp(a)/(1+exp(a)) ~[0,1]
   * \ingroup QFC
	 * \param a : defined as real number without bounds in parameter_section, one element less than return p
   * \return return the prob. vector p in procedure_section
   */	
  dvar_vector logitProp(const dvar_vector& a)
  {
    int dim; 
    dim=a.size()+1;
    dvar_vector p(1,dim);
    dvar_vector expa=mfexp(a);
    p(1,dim-1)=expa/(1.+sum(expa));
    //p(dim)=1.-sum(p(1,dim-1));  //original version was buggy for the last term
    p(dim)=1./(1.+sum(expa));
    return p;
  }

  /** reverse function for LogitProp 
   * \ingroup QFC
	 * \param p : the prob. vector
   * \return return the a, one element less than input p
   */	
  dvar_vector invLogitProp(const dvar_vector& p)
  {
    int dim; 
    dim=p.size()-1;
    dvar_vector a(1,dim); 
    dvar_vector lp(1,dim+1);
  
    lp=log(p+EPS);//take log for each p
    a=lp(1,dim)-lp(dim+1);//each subtract the last one
    return a;
  }





  /** overloading functions for posfun for vector and matrix,  
	 *  not sure if admb already do this in latest version 
   * \ingroup QFC
	 * \param x : defined as real number without bounds in parameter_section, one element less than return p
   * \param eps : positive vector as lower thresholds 
	 * \param pen : hold extra penalty, need add to objective function value later
	 * \return return value between (0,eps) with penalty fpen for input x< eps,
	 * or return x itself if x>=eps with no penalty
   */	 
  dvar_vector posfun(dvar_vector& x,const dvector& eps, dvariable& pen) //x and eps both are vector
  { 
    for(int i=x.indexmin();i<=x.indexmax();i++)
    {
      x(i)=posfun(x(i),eps(i),pen);
    }
    return x;
  }

  /** overloading functions for posfun for vector and matrix,  
	 *  not sure if admb already do this in latest version \n
	 * overloading function for matrix
   * \ingroup QFC
	 * \param x : defined as real number without bounds in parameter_section, one element less than return p
   * \param eps : positive vector as lower thresholds 
	 * \param pen : hold extra penalty, need add to objective function value later
	 * \return return value between (0,eps) with penalty fpen for input x< eps,
	 * or return x itself if x>=eps with no penalty
   */	   
	dvar_matrix posfun(dvar_matrix& x,const dmatrix & eps, dvariable& pen)
  {
    for(int i=x.rowmin();i<=x.rowmax();i++)
    {
      for(int j=x.colmin();j<=x.colmax();j++)
      {
        x(i,j)=posfun(x(i,j),eps(i,j),pen);
      }
    }
    return x;
  }



	
 
  /** constrain parameter with upper threshold, if return bigger than it, then with penalty
   * ADMB have built in function mf_upper_bound(), which have more constrain
	 *  on the values higher than the bounds with bigger penalty than this version
	 * \ingroup QFC
	 * \param x : mean parameter
   * \param fmax : upper threshold or maximum value, be positive
	 * \param fpen :  penalty 
	 * \return return itself without penalty if input value <fmax , or 
	 * return ajusted value which >fmax but with penalty
   */	
  dvariable mf_upper_bound2(const dvariable & x,const double fmax, dvariable & fpen)
  {
    if (x<=fmax) return x;
    else
    {
      fpen+=.01*square(x-fmax);
      return x-x/(2-fmax/x)+fmax;
    }
  }







  /** nll for negative binomial N(m,s) for one sample, 
	 * admb built in log_negbinomial_density(obs,mu,tau), in which tau=1.+mu/s for NB(m,s),
   * winbug us NB(p,r), in which p=s/(m+s) and r=s, \n 
   * \f[ -\ln(\Gamma(x+s))+ \ln(\Gamma(s))+\ln(x!)-s\ln(\frac{s}{m+s})-x\ln(\frac{m}{m+s})   \f]
   * \ingroup QFC
   * \param m : mean
	 * \param s : scaling factor, some use r NB(p,r)
   * \param obs : observation data x
	 * \return return the nll for neg. binomial for one sample
   */	
  double  nllNegativeBinomial(const double m, const double s, const double obs)
  {
    double nll=0; 
    nll= -gammln(obs+s)+ gammln(s)- s*log(s/(m+s)+EPS)- obs*log(m/(m+s)+EPS)+ gammln(obs+1.);
    return nll;
  }

  /** nll for negative binomial N(m,s) for one sample, 
	 * admb built in log_negbinomial_density(obs,mu,tau), in which tau=1.+mu/s for NB(m,s),
   * winbug us NB(p,r), in which p=s/(m+s) and r=s \n
   * \f[ -\ln(\Gamma(x+s))+ \ln(\Gamma(s))+\ln(x!)-s\ln(\frac{s}{m+s})-x\ln(\frac{m}{m+s})   \f]
   * \ingroup QFC
   * \param m : mean
	 * \param s : scaling factor, some use r NB(p,r)
   * \param obs : observation data
	 * \return return the nll for neg. binomial for one sample
   */	
  dvariable  nllNegativeBinomial(const double m, const double s, const dvariable & obs)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 
    nll= -gammln(obs+s)+ gammln(s)- s*log(s/(m+s)+EPS)- obs*log(m/(m+s)+EPS)+ gammln(obs+1.);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for negative binomial N(m,s) for one sample, 
	 * admb built in log_negbinomial_density(obs,mu,tau), in which tau=1.+mu/s for NB(m,s),
   * winbug us NB(p,r), in which p=s/(m+s) and r=s, \n
   * \f[ -\ln(\Gamma(x+s))+ \ln(\Gamma(s))+\ln(x!)-s\ln(\frac{s}{m+s})-x\ln(\frac{m}{m+s})   \f]
   * \ingroup QFC
   * \param m : mean
	 * \param s : scaling factor
   * \param obs : observation data
	 * \return return the nll for neg. binomial for one sample
   */	
  dvariable  nllNegativeBinomial(const dvariable & m, const dvariable & s, const double obs)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 
    nll= -gammln(obs+s)+ gammln(s)- s*log(s/(m+s)+EPS)- obs*log(m/(m+s)+EPS)+ gammln(obs+1.);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for negative binomial N(m,s) for one sample, 
	 * admb built in log_negbinomial_density(obs,mu,tau), in which tau=1.+mu/s for NB(m,s),
   * winbug us NB(p,r), in which p=s/(m+s) and r=s, \n
   * \f[ -\ln(\Gamma(x+s))+ \ln(\Gamma(s))+\ln(x!)-s\ln(\frac{s}{m+s})-x\ln(\frac{m}{m+s})   \f]
   * \ingroup QFC
   * \param m : mean
	 * \param s : scaling factor
   * \param obs : observation data
	 * \return return the nll for neg. binomial for one sample
   */	
  dvariable  nllNegativeBinomial(const dvariable & m, const dvariable & s, const dvariable & obs)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 
    nll= -gammln(obs+s)+ gammln(s)- s*log(s/(m+s)+EPS)- obs*log(m/(m+s)+EPS)+ gammln(obs+1.);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for negative binomial N(m,s) for many samples, 
	 * admb built in log_negbinomial_density(obs,mu,tau), in which tau=1.+mu/s for NB(m,s),
   * winbug us NB(p,r), in which p=s/(m+s) and r=s, \n
   * \f[ -\sum(\ln(\Gamma(x+s)))+ n\ln(\Gamma(s))+\sum(\ln(x!))-ns\ln(\frac{s}{m+s})-\sum(x)\ln(\frac{m}{m+s})   \f]
   * \ingroup QFC
   * \param m : mean
	 * \param s : scaling factor
   * \param obs : observation data
	 * \return return the nll for neg. binomial for many samples
   */	
  dvariable  nllNegativeBinomial(const dvariable & m, const dvariable & s, const dvector & obs)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 
    double n=double(obs.size());
    nll= -sum(gammln(obs+s))+ n*gammln(s)- n*s*log(s/(m+s)+EPS)- sum(obs)*log(m/(m+s)+EPS)+ sum(gammln(obs+1.));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for negative binomial N(m,s) for many samples, 
	 * admb built in log_negbinomial_density(obs,mu,tau), in which tau=1.+mu/s for NB(m,s),
   * winbug us NB(p,r), in which p=s/(m+s) and r=s, \n
   * \f[ -\sum(\ln(\Gamma(x+s)))+ n\ln(\Gamma(s))+\sum(\ln(x!))-ns\ln(\frac{s}{m+s})-\sum(x)\ln(\frac{m}{m+s})   \f]
   * \ingroup QFC
   * \param m : mean
	 * \param s : scaling factor
   * \param obs : observation data
	 * \return return the nll for neg. binomial for many samples
   */	
  dvariable  nllNegativeBinomial(const double m, const double s, const dvar_vector & obs)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 
    double n=double(obs.size());
    nll= -sum(gammln(obs+s))+ n*gammln(s)- n*s*log(s/(m+s)+EPS)- sum(obs)*log(m/(m+s)+EPS)+ sum(gammln(obs+1.));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for negative binomial N(m,s) for many samples, 
	 * admb built in log_negbinomial_density(obs,mu,tau), in which tau=1.+mu/s for NB(m,s),
   * winbug us NB(p,r), in which p=s/(m+s) and r=s, \n
   * \f[ -\sum(\ln(\Gamma(x+s)))+ n\ln(\Gamma(s))+\sum(\ln(x!))-ns\ln(\frac{s}{m+s})-\sum(x)\ln(\frac{m}{m+s})   \f]
   * \ingroup QFC
   * \param m : mean
	 * \param s : scaling factor
   * \param obs : observation data
	 * \return return the nll for neg. binomial for many samples
   */	
  dvariable  nllNegativeBinomial(const dvariable & m, const dvariable & s, const dvar_vector & obs)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 
    double n=double(obs.size());
    nll= -sum(gammln(obs+s))+ n*gammln(s)- n*s*log(s/(m+s)+EPS)- sum(obs)*log(m/(m+s)+EPS)+ sum(gammln(obs+1.));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }





  /** nll for negative binomial N(mu,tau) for one sample, 
	 * admb built in log_negbinomial_density(obs,mu,tau), in which tau=1.+mu/s for NB(m,s),
   * winbug us NB(p,r), in which p=s/(m+s) and r=s, \n
   * \ingroup QFC
   * \param m : mean
	 * \param tau : overdispersion parameter,
   * \param obs : observation data
	 * \return return the nll for neg. binomial for one sample
   */	
  double nllNegativeBinomial2(const double m, const double tau, const double obs)
  {
    return -log_density_negbinomial (obs,m,tau);
  } 

  /** nll for negative binomial N(mu,tau) for one sample, 
	 * admb built in log_negbinomial_density(obs,mu,tau), in which tau=1.+mu/s for NB(m,s),
   * winbug us NB(p,r), in which p=s/(m+s) and r=s
   * \ingroup QFC
   * \param m : mean
	 * \param tau : overdispersion parameter,
   * \param obs : observation data
	 * \return return the nll for neg. binomial for one sample
   */	
  dvariable nllNegativeBinomial2(const dvariable & m, const dvariable & tau, const double obs)
  {
    return -1.*log_negbinomial_density(obs,m,tau);
  } 

  /** nll for negative binomial N(mu,tau) for one sample, 
	 * admb built in log_negbinomial_density(obs,mu,tau), in which tau=1.+mu/s for NB(m,s),
   * winbug us NB(p,r), in which p=s/(m+s) and r=s
   * \ingroup QFC
   * \param m : mean
	 * \param tau : overdispersion parameter,
   * \param obs : observation data
	 * \return return the nll for neg. binomial for one sample
   */	
  dvariable nllNegativeBinomial2(const double m, const double tau, const dvariable & obs)
  {
    return nllNegativeBinomial(m,m/(tau-1.+EPS),obs);
  } 

  /** nll for negative binomial N(mu,tau) for one sample, 
	 * admb built in log_negbinomial_density(obs,mu,tau), in which tau=1.+mu/s for NB(m,s),
   * winbug us NB(p,r), in which p=s/(m+s) and r=s
   * \ingroup QFC
   * \param m : mean
	 * \param tau : overdispersion parameter,
   * \param obs : observation data
	 * \return return the nll for neg. binomial for one sample
   */	
  dvariable nllNegativeBinomial2(const dvariable & m, const dvariable & tau, const dvariable & obs)
  {
    return nllNegativeBinomial(m,m/(tau-1.+EPS),obs);
  } 








  /** nll for Multinomial for one sample
   * \f$  -\sum_{i}(n_{i}\ln(p_{i})) -\ln((\sum_{i}n_{i})!) +\sum_{i}(\ln(n_{i}!)) \f$
   * \ingroup QFC
	 * \param p : proportion vector
   * \param obsN : observation data
	 * \return return the nll for Multinomial for one sample
   */	
  double  nllMultiNomial(const dvector & p,const dvector & obsN)
  {
    double nll=0;  
    nll= -1.*(obsN*log(p+EPS) + gammln(sum(obsN)+1.) - sum(gammln(obsN+1.))); //full likelihood
    return nll;
  }

  /** nll for Multinomial for one sample
   * \f$  -\sum_{i}(n_{i}\ln(p_{i})) -\ln((\sum_{i}n_{i})!) +\sum_{i}(\ln(n_{i}!)) \f$
   * \ingroup QFC
	 * \param p : proportion vector
   * \param obsN : observation data
	 * \return return the nll for Multinomial for one sample
   */	
  dvariable  nllMultiNomial(const dvar_vector & p,const dvector & obsN)
  {
    RETURN_ARRAYS_INCREMENT(); 
    dvariable nll=0;  
    nll= -1.*(obsN*log(p+EPS) + gammln(sum(obsN)+1.) - sum(gammln(obsN+1.))); //full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for Multinomial for one sample
   * \f$  -\sum_{i}(n_{i}\ln(p_{i})) -\ln((\sum_{i}n_{i})!) +\sum_{i}(\ln(n_{i}!)) \f$
   * \ingroup QFC
	 * \param p : proportion vector
   * \param obsN : observation data
	 * \return return the nll for Multinomial for one sample
   */	
  dvariable  nllMultiNomial(const dvector & p,const dvar_vector & obsN)
  {
    RETURN_ARRAYS_INCREMENT(); 
    dvariable nll=0;  
    nll= -1.*(obsN*log(p+EPS) + gammln(sum(obsN)+1.) - sum(gammln(obsN+1.))); //full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  } 

  /** nll for Multinomial for one sample
   * \f$  -\sum_{i}(n_{i}\ln(p_{i})) -\ln((\sum_{i}n_{i})!) +\sum_{i}(\ln(n_{i}!)) \f$
   * \ingroup QFC
	 * \param p : proportion vector
   * \param obsN : observation data
	 * \return return the nll for Multinomial for one sample
   */	
  dvariable  nllMultiNomial(const dvar_vector & p,const dvar_vector & obsN)
  {
    RETURN_ARRAYS_INCREMENT(); 
    dvariable nll=0;  
    nll= -1.*(obsN*log(p+EPS) + gammln(sum(obsN)+1.) - sum(gammln(obsN+1.))); //full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }    
  






  /** nll for dirichlet for one sample
   * \f$  -\ln\Gamma(\sum_{i}(\alpha_{i})) -\sum_{i}(\ln(\Gamma(\alpha_{i}))) +\sum_{i}((\alpha_{i}-1)\ln(p_{i}))  \f$
   * \ingroup QFC
	 * \param shape : alpha parameter
   * \param p : observation 
	 * \return return the nll for dirichlet for one sample
   */	
  double nllDirichlet(const dvector & shape, const dvector & p)
  {
    double nll=0;  
    nll= -1.*(gammln(sum(shape)) - sum(gammln(shape)) + (shape-1.)*log(p+EPS));
    return nll;
  }

  /** nll for dirichlet for one sample
   * \f$  -\ln\Gamma(\sum_{i}(\alpha_{i})) -\sum_{i}(\ln(\Gamma(\alpha_{i}))) +\sum_{i}((\alpha_{i}-1)\ln(p_{i}))  \f$
   * \ingroup QFC
	 * \param shape : alpha parameter
   * \param p : observation 
	 * \return return the nll for dirichlet for one sample
   */	
  dvariable nllDirichlet(const dvector & shape, const dvar_vector & p)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll= -1.*(gammln(sum(shape)) - sum(gammln(shape)) + (shape-1.)*log(p+EPS));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for dirichlet for one sample
   * \f$  -\ln\Gamma(\sum_{i}(\alpha_{i})) -\sum_{i}(\ln(\Gamma(\alpha_{i}))) +\sum_{i}((\alpha_{i}-1)\ln(p_{i}))  \f$
   * \ingroup QFC
	 * \param shape : alpha parameter
   * \param p : observation 
	 * \return return the nll for dirichlet for one sample
   */	
  dvariable nllDirichlet(const dvar_vector & shape, const dvector & p)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll= -1.*(gammln(sum(shape)) - sum(gammln(shape)) + (shape-1.)*log(p+EPS));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for dirichlet for one sample
   * \f$  -\ln\Gamma(\sum_{i}(\alpha_{i})) -\sum_{i}(\ln(\Gamma(\alpha_{i}))) +\sum_{i}((\alpha_{i}-1)\ln(p_{i}))  \f$
   * \ingroup QFC
	 * \param shape : alpha parameter
   * \param p : observation 
	 * \return return the nll for dirichlet for one sample
   */	
  dvariable nllDirichlet(const dvar_vector & shape, const dvar_vector & p)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll= -1.*(gammln(sum(shape)) - sum(gammln(shape)) + (shape-1.)*log(p+EPS));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  
  

 


  /** nll for gamma for one sample
   * Gamma(a,b) similar to log_gamma_density(r,mu) in admb, in which a=r, b=mu
   * \f$ -a \ln(b) + \ln(\Gamma(a)) - (a-1)\ln(x)+ bx   \f$
   * \ingroup QFC
	 * \param a : alpha parameter
   * \param b : beta parameter
	 * \param x :  data
	 * \return return the nll for gamma for one sample
   */	
  double nllGamma(const double a, const double b, const double & x)
  {
    return -1.*log_gamma_density(x,a,b);  //call admb built infunction
  }

  /** nll for gamma for one sample
   * \f$ -a \ln(b) + \ln(\Gamma(a)) - (a-1)\ln(x)+ bx   \f$
   * \ingroup QFC
	 * \param a : alpha parameter
   * \param b : beta parameter
	 * \param x :  data
	 * \return return the nll for gamma for one sample
   */	
  dvariable nllGamma(const double a, const double b, const dvariable & x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll= gammln(a) - a*log(b) -(a-1.)*log(x+EPS) + b*x;  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for gamma for one sample
   * \f$ -a \ln(b) + \ln(\Gamma(a)) - (a-1)\ln(x)+ bx   \f$
   * \ingroup QFC
	 * \param a : alpha parameter
   * \param b : beta parameter
	 * \param x :  data
	 * \return return the nll for gamma for one sample
   */	
  dvariable nllGamma(const dvariable & a, const dvariable & b, const double x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll= gammln(a) - a*log(b) -(a-1.)*log(x+EPS) + b*x;  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for gamma for one sample
   * \f$ -a \ln(b) + \ln(\Gamma(a)) - (a-1)\ln(x)+ bx   \f$
   * \ingroup QFC
	 * \param a : alpha parameter
   * \param b : beta parameter
	 * \param x :  data
	 * \return return the nll for gamma for one sample
   */	
  dvariable nllGamma(const dvariable & a, const dvariable & b, const dvariable & x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll= gammln(a) - a*log(b) -(a-1.)*log(x+EPS) + b*x;  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for gamma for many samples
   * \f$ -na\ln(b) + n\ln(\Gamma(a)) - (a-1)\sum(\ln(x))+ b\sum(x)   \f$
   * \ingroup QFC
	 * \param a : alpha parameter
   * \param b : beta parameter
	 * \param x :  data
	 * \return return the nll for gamma for many samples
   */	
	double nllGamma(const double a, const double b, const dvector & x)
  {
		double nll=0;  
    double n=double(x.size());
    nll=n*gammln(a) - n*a*log(b) -(a-1.)*sum(log(x+EPS)) + b*sum(x);  
		return nll;
  }

  /** nll for gamma for many samples
   * \f$ -na\ln(b) + n\ln(\Gamma(a)) - (a-1)\sum(\ln(x))+ b\sum(x)   \f$
   * \ingroup QFC
	 * \param a : alpha parameter
   * \param b : beta parameter
	 * \param x :  data
	 * \return return the nll for gamma for many samples
   */	
	dvariable nllGamma(const double a, const double b, const dvar_vector & x)
  {
    RETURN_ARRAYS_INCREMENT();
		dvariable nll=0;  
    double n=double(x.size());
    nll=n*gammln(a) - n*a*log(b) -(a-1.)*sum(log(x+EPS)) + b*sum(x);  
    RETURN_ARRAYS_DECREMENT();
		return nll;
  }

  /** nll for gamma for many samples
   * \f$ -na\ln(b) + n\ln(\Gamma(a)) - (a-1)\sum(\ln(x))+ b\sum(x)   \f$
   * \ingroup QFC
	 * \param a : alpha parameter
   * \param b : beta parameter
	 * \param x :  data
	 * \return return the nll for gamma for many samples
   */	
	dvariable nllGamma(const dvariable & a, const dvariable & b, const dvector & x)
  {
    RETURN_ARRAYS_INCREMENT();
		dvariable nll=0;  
    double n=double(x.size());
    nll=n*gammln(a) - n*a*log(b) -(a-1.)*sum(log(x+EPS)) + b*sum(x);  
    RETURN_ARRAYS_DECREMENT();
		return nll;
  }

  /** nll for gamma for many samples
   * \f$ -na\ln(b) + n\ln(\Gamma(a)) - (a-1)\sum(\ln(x))+ b\sum(x)   \f$
   * \ingroup QFC
	 * \param a : alpha parameter
   * \param b : beta parameter
	 * \param x :  data
	 * \return return the nll for gamma for many samples
   */	
	dvariable nllGamma(const dvariable & a, const dvariable & b, const dvar_vector & x)
  {
    RETURN_ARRAYS_INCREMENT();
		dvariable nll=0;  
    double n=double(x.size());
    nll=n*gammln(a) - n*a*log(b) -(a-1.)*sum(log(x+EPS)) + b*sum(x);  
    RETURN_ARRAYS_DECREMENT();
		return nll;
  }
  
  





  
  /** nll for beta for one sample
   * \f$ -\ln(\Gamma(a+b)) +\ln(\Gamma(a)) + \ln(\Gamma(b))-(a-1)\ln(x)-(b-1)\ln(1-x)   \f$
   * \ingroup QFC
	 * \param a : alpha parameter
   * \param b : beta parameter
	 * \param x :  data
	 * \return return the nll for beta for one sample
   */	
  double nllBeta(const double a, const double b, const double x)
  {
    double nll=0;  
    nll=gammln(a)+gammln(b)-gammln(a+b)-(a-1.)*log(x+EPS)-(b-1.)*log(1.-x+EPS);  
    return nll;
  }    
  
  /** nll for beta for one sample
   * \f$ -\ln(\Gamma(a+b)) +\ln(\Gamma(a)) + \ln(\Gamma(b))-(a-1)\ln(x)-(b-1)\ln(1-x)   \f$
   * \ingroup QFC
	 * \param a : alpha parameter
   * \param b : beta parameter
	 * \param x :  data
	 * \return return the nll for beta for one sample
   */	
  dvariable nllBeta(const double a, const double b, const dvariable & x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll=gammln(a)+gammln(b)-gammln(a+b)-(a-1.)*log(x+EPS)-(b-1.)*log(1.-x+EPS);  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }   

  /** nll for beta for one sample
   * \f$ -\ln(\Gamma(a+b)) +\ln(\Gamma(a)) + \ln(\Gamma(b))-(a-1)\ln(x)-(b-1)\ln(1-x)   \f$
   * \ingroup QFC
	 * \param a : alpha parameter
   * \param b : beta parameter
	 * \param x :  data
	 * \return return the nll for beta for one sample
   */	
  dvariable nllBeta(const dvariable & a, const dvariable & b, const double x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll=gammln(a)+gammln(b)-gammln(a+b)-(a-1.)*log(x+EPS)-(b-1.)*log(1.-x+EPS);  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  

  /** nll for beta for one sample
   * \f$ -\ln(\Gamma(a+b)) +\ln(\Gamma(a)) + \ln(\Gamma(b))-(a-1)\ln(x)-(b-1)\ln(1-x)   \f$
   * \ingroup QFC
	 * \param a : alpha parameter
   * \param b : beta parameter
	 * \param x :  data
	 * \return return the nll for beta for one sample
   */	
  dvariable nllBeta(const dvariable & a, const dvariable & b, const dvariable & x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll=gammln(a)+gammln(b)-gammln(a+b)-(a-1.)*log(x+EPS)-(b-1.)*log(1.-x+EPS);  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  

  /** nll for beta for many samples
   * \f$ -n\ln(\Gamma(a+b)) +n\ln(\Gamma(a)) + n\ln(\Gamma(b))-(a-1)\sum(\ln(x)) -(b-1)\sum(\ln(1-x))   \f$
   * \ingroup QFC
	 * \param a : alpha parameter
   * \param b : beta parameter
	 * \param x :  data
	 * \return return the nll for beta for many samples
   */	
	dvariable nllBeta(const double a, const double b, const dvar_vector & x)
  {
    RETURN_ARRAYS_INCREMENT();
		dvariable nll=0;  
    double n=double(x.size());
    nll=n*gammln(a)+n*gammln(b)-n*gammln(a+b)-(a-1.)*sum(log(x+EPS))-(b-1.)*sum(log(1.-x+EPS));  
    RETURN_ARRAYS_DECREMENT();
		return nll;
  }

  /** nll for beta for many samples
   * \f$ -n\ln(\Gamma(a+b)) +n\ln(\Gamma(a)) + n\ln(\Gamma(b))-(a-1)\sum(\ln(x)) -(b-1)\sum(\ln(1-x))   \f$
   * \ingroup QFC
	 * \param a : alpha parameter
   * \param b : beta parameter
	 * \param x :  data
	 * \return return the nll for beta for many samples
   */	
	dvariable nllBeta(const dvariable & a, const dvariable & b, const dvector & x)
  {
    RETURN_ARRAYS_INCREMENT();
		dvariable nll=0;  
    double n=double(x.size());
    nll=n*gammln(a)+n*gammln(b)-n*gammln(a+b)-(a-1.)*sum(log(x+EPS))-(b-1.)*sum(log(1.-x+EPS));  
    RETURN_ARRAYS_DECREMENT();
		return nll;
  }

  /** nll for beta for many samples
   * \f$ -n\ln(\Gamma(a+b)) +n\ln(\Gamma(a)) + n\ln(\Gamma(b))-(a-1)\sum(\ln(x)) -(b-1)\sum(\ln(1-x))   \f$
   * \ingroup QFC
	 * \param a : alpha parameter
   * \param b : beta parameter
	 * \param x :  data
	 * \return return the nll for beta for many samples
   */	
	dvariable nllBeta(const dvariable & a, const dvariable & b, const dvar_vector & x)
  {
    RETURN_ARRAYS_INCREMENT();
		dvariable nll=0;  
    double n=double(x.size());
    nll=n*gammln(a)+n*gammln(b)-n*gammln(a+b)-(a-1.)*sum(log(x+EPS))-(b-1.)*sum(log(1.-x+EPS));  
    RETURN_ARRAYS_DECREMENT();
		return nll;
  }
  
  
  






  /** nll for normal for one sample
   * \f$ 0.5\ln(2 \pi) + \ln(\sigma) + 0.5(\frac{x-\mu}{\sigma})^2  \f$
   * \ingroup QFC
	 * \param mu : mean parameter
   * \param sigma : std deviation parameter
	 * \param x :  data
	 * \return return the nll for normal for one sample
   */	
  double nllNormal(const double mu, const double sigma, const double x)
  {
    double nll=0;  
    nll=log(sigma*sqrt(2.*M_PI)+EPS) +0.5*square((x-mu)/(sigma+EPS));  
    return nll;
  }

  /** nll for normal for one sample
   * \f$ 0.5\ln(2 \pi) + \ln(\sigma) + 0.5(\frac{x-\mu}{\sigma})^2  \f$
   * \ingroup QFC
	 * \param mu : mean parameter
   * \param sigma : std deviation parameter
	 * \param x :  data
	 * \return return the nll for normal for one sample
   */	
  dvariable nllNormal(const double mu, const double sigma, const dvariable & x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll=log(sigma*sqrt(2.*M_PI)+EPS) +0.5*square((x-mu)/(sigma+EPS));  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for normal for one sample
   * \f$ 0.5\ln(2 \pi) + \ln(\sigma) + 0.5(\frac{x-\mu}{\sigma})^2  \f$
   * \ingroup QFC
	 * \param mu : mean parameter
   * \param sigma : std deviation parameter
	 * \param x :  data
	 * \return return the nll for normal for one sample
   */	
  dvariable nllNormal(const dvariable & mu, const dvariable & sigma, const double x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll=log(sigma*sqrt(2.*M_PI)+EPS) +0.5*square((x-mu)/(sigma+EPS));  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for normal for one sample
   * \f$ 0.5\ln(2 \pi) + \ln(\sigma) + 0.5(\frac{x-\mu}{\sigma})^2  \f$
   * \ingroup QFC
	 * \param mu : mean parameter
   * \param sigma : std deviation parameter
	 * \param x :  data
	 * \return return the nll for normal for one sample
   */	
  dvariable nllNormal(const dvariable & mu, const dvariable & sigma, const dvariable & x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll=log(sigma*sqrt(2.*M_PI)+EPS) +0.5*square((x-mu)/(sigma+EPS));  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for normal for many samples, but mu is for common
   * \f$ 0.5n\ln(2 \pi) + n\ln(\sigma) + 0.5\sum(\frac{x-\mu}{\sigma})^2  \f$
   * \ingroup QFC
	 * \param mu : mean parameter
   * \param sigma : std deviation parameter
	 * \param x :  data
	 * \return return the nll for normal for many samples sharing one mu
   */	
  double nllNormal(const double mu, const double sigma, const dvector & x)
  {
		double nll=0;  
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +0.5*norm2((x-mu)/(sigma+EPS));  
		return nll;
  }

  /** nll for normal for many samples, but mu is for common
   * \f$ 0.5n\ln(2 \pi) + n\ln(\sigma) + 0.5\sum(\frac{x-\mu}{\sigma})^2  \f$
   * \ingroup QFC
	 * \param mu : mean parameter
   * \param sigma : std deviation parameter
	 * \param x :  data
	 * \return return the nll for normal for many samples sharing one mu
   */	
  dvariable nllNormal(const double mu, const double sigma, const dvar_vector& x)
  {
    RETURN_ARRAYS_INCREMENT();
		dvariable nll=0;  
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +0.5*norm2((x-mu)/(sigma+EPS));  
    RETURN_ARRAYS_DECREMENT();
		return nll;
  }

  /** nll for normal for many samples, but mu is for common
   * \f$ 0.5n\ln(2 \pi) + n\ln(\sigma) + 0.5\sum(\frac{x-\mu}{\sigma})^2  \f$
   * \ingroup QFC
	 * \param mu : mean parameter
   * \param sigma : std deviation parameter
	 * \param x :  data
	 * \return return the nll for normal for many samples sharing one mu
   */	
  dvariable nllNormal(const dvariable & mu, const dvariable & sigma, const dvector & x)
  {
    RETURN_ARRAYS_INCREMENT();
		dvariable nll=0;  
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +0.5*norm2((x-mu)/(sigma+EPS));  
    RETURN_ARRAYS_DECREMENT();
		return nll;
  }

  /** nll for normal for many samples, but mu is for common
   * \f$ 0.5n\ln(2 \pi) + n\ln(\sigma) + 0.5\sum(\frac{x-\mu}{\sigma})^2  \f$
   * \ingroup QFC
	 * \param mu : mean parameter
   * \param sigma : std deviation parameter
	 * \param x :  data
	 * \return return the nll for normal for many samples sharing one mu
   */	
  dvariable nllNormal(const dvariable & mu, const dvariable & sigma, const dvar_vector & x)
  {
    RETURN_ARRAYS_INCREMENT();
		dvariable nll=0;  
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +0.5*norm2((x-mu)/(sigma+EPS));  
    RETURN_ARRAYS_DECREMENT();
		return nll;
  }
  
  /** nll for normal for many samples, each has its own mean
   * \f$ 0.5n\ln(2 \pi) + n\ln(\sigma) + 0.5\sum(\frac{x-\mu}{\sigma})^2  \f$
   * \ingroup QFC
	 * \param mu : mean parameter
   * \param sigma : std deviation parameter
	 * \param x :  data
	 * \return return the nll for normal for many samples, each has own mean
   */	
  dvariable nllNormal(const dvar_vector & mu, const dvariable & sigma, const dvar_vector & x)
  {
    RETURN_ARRAYS_INCREMENT();
		dvariable nll=0;  
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +0.5*norm2((x-mu)/(sigma+EPS));  
    RETURN_ARRAYS_DECREMENT();
		return nll;
  }








  /** nll for normal(mu,tau) for one sample
   * \f$ 0.5\ln(2 \pi) -0.5 \ln(\tau) + 0.5\tau(x-\mu)^2  \f$
   * \ingroup QFC
	 * \param mu : mean parameter
   * \param tau : precision, 1/variance
	 * \param x :  data
	 * \return return the nll for normal for one sample
   */	
  dvariable nllNormal2(const double mu, const double tau, const dvariable & x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll = -0.5*log(tau+EPS)+0.5*tau*square(x-mu)+0.5*log(2.*M_PI);//full likelihood, can drop last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for normal(mu,tau) for one sample
   * \f$ 0.5\ln(2 \pi) -0.5 \ln(\tau) + 0.5\tau(x-\mu)^2  \f$
   * \ingroup QFC
	 * \param mu : mean parameter
   * \param tau : precision, 1/variance
	 * \param x :  data
	 * \return return the nll for normal for one sample
   */	
  dvariable nllNormal2(const dvariable & mu, const dvariable & tau, const double x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll = -0.5*log(tau+EPS)+0.5*tau*square(x-mu)+0.5*log(2.*M_PI);//full likelihood, can drop last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for normal(mu,tau) for one sample
   * \f$ 0.5\ln(2 \pi) -0.5 \ln(\tau) + 0.5\tau(x-\mu)^2  \f$
   * \ingroup QFC
	 * \param mu : mean parameter
   * \param tau : precision, 1/variance
	 * \param x :  data
	 * \return return the nll for normal for one sample
   */	
  dvariable nllNormal2(const dvariable & mu, const dvariable & tau, const dvariable & x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll = -0.5*log(tau+EPS)+0.5*tau*square(x-mu)+0.5*log(2.*M_PI);//full likelihood, can drop last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for normal(mu,tau) for many samples
   * \f$ 0.5n\ln(2 \pi) -0.5n\ln(\tau) + 0.5\tau\sum(x-\mu)^2  \f$
   * \ingroup QFC
	 * \param mu : mean parameter
   * \param tau : precision, 1/variance
	 * \param x :  data
	 * \return return the nll for normal for many samples
   */	
  dvariable nllNormal2(const double mu, const double tau, const dvar_vector & x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll = -0.5*n*log(tau+EPS)+0.5*tau*norm2(x-mu)+0.5*n*log(2.*M_PI);//full likelihood, can drop last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  
  /** nll for normal(mu,tau) for many samples
   * \f$ 0.5n\ln(2 \pi) -0.5n\ln(\tau) + 0.5\tau\sum(x-\mu)^2  \f$
   * \ingroup QFC
	 * \param mu : mean parameter
   * \param tau : precision, 1/variance
	 * \param x :  data
	 * \return return the nll for normal for many samples
   */	
  dvariable nllNormal2(const dvariable & mu, const dvariable & tau, const dvector & x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll = -0.5*n*log(tau+EPS)+0.5*tau*norm2(x-mu)+0.5*n*log(2.*M_PI);//full likelihood, can drop last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for normal(mu,tau) for many samples
   * \f$ 0.5n\ln(2 \pi) -0.5n\ln(\tau) + 0.5\tau\sum(x-\mu)^2  \f$
   * \ingroup QFC
	 * \param mu : mean parameter
   * \param tau : precision, 1/variance
	 * \param x :  data
	 * \return return the nll for normal for many samples
   */	
  dvariable nllNormal2(const dvariable & mu, const dvariable & tau, const dvar_vector & x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll = -0.5*n*log(tau+EPS)+0.5*tau*norm2(x-mu)+0.5*n*log(2.*M_PI);//full likelihood, can drop last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }







  /** nll for binomial for one sample
   * \f$ \ln(x!) + \ln((n-x)!) -\ln(n!)  - x \ln(p) - (n-x) \ln(1-p)  \f$
   * \ingroup QFC
   * \param n : number of trials
   * \param p : probability
   * \param x :  data
   * \return return the nll for binomial for one samples
   */	 
  double nllBinomial(const double n,const double p, const double x)
  {		
    double nll=0;
    nll=-x*log(p+EPS)-(n-x)*log(1.-p+EPS)-log_comb(n,x); //full likelihood, can drop the last term
    return nll;
  }

  /** nll for binomial for one sample
   * \f$ \ln(x!) + \ln((n-x)!) -\ln(n!)  - x \ln(p) - (n-x) \ln(1-p)  \f$
   * \ingroup QFC
   * \param n : number of trials
   * \param p : probability
   * \param x :  data
   * \return return the nll for binomial for one samples
   */	 
  dvariable nllBinomial(const double n,const double p, const dvariable & x)
  {		
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    nll=-x*log(p+EPS)-(n-x)*log(1.-p+EPS)-log_comb(n,x); //full likelihood, can drop the last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for binomial for one sample
   * \f$ \ln(x!) + \ln((n-x)!) -\ln(n!)  - x \ln(p) - (n-x) \ln(1-p)  \f$
   * \ingroup QFC
   * \param n : number of trials
   * \param p : probability
   * \param x :  data
   * \return return the nll for binomial for one samples
   */	 
  dvariable nllBinomial(const dvariable & n,const dvariable & p, const double x)
  {		
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    nll=-x*log(p+EPS)-(n-x)*log(1.-p+EPS)-log_comb(n,x); //full likelihood, can drop the last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for binomial for one sample
   * \f$ \ln(x!) + \ln((n-x)!) -\ln(n!)  - x \ln(p) - (n-x) \ln(1-p)  \f$
   * \ingroup QFC
   * \param n : number of trials
   * \param p : probability
   * \param x :  data
   * \return return the nll for binomial for one samples
   */	 
  dvariable nllBinomial(const dvariable & n,const dvariable & p, const dvariable & x)
  {		
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    nll=-x*log(p+EPS)-(n-x)*log(1.-p+EPS)-log_comb(n,x); //full likelihood, can drop the last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }







  /** nll for lognormal for one sample
   * \f$ 0.5\ln(2 \pi) + \ln(x) +\ln(\sigma) + 0.5(\frac{\ln(x)-\mu}{\sigma})^2  \f$
   * \ingroup QFC
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \param x :  data
   * \return return the nll for lognormal for one sample
   */	
  double nllLognormal(const double mu, const double sigma, const double x )
  {	
    double nll=0; 		
    nll=log(sigma*sqrt(2.*M_PI)+EPS)+log(x+EPS)+0.5*square((log(x+EPS)-mu)/(sigma+EPS));//full likelihood
    return nll;
  }

  /** nll for lognormal for one sample
   * \f$ 0.5\ln(2 \pi) + \ln(x) +\ln(\sigma) + 0.5(\frac{\ln(x)-\mu}{\sigma})^2  \f$
   * \ingroup QFC
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \param x :  data
   * \return return the nll for lognormal for one sample
   */	
  dvariable nllLognormal(const double mu, const double sigma, const dvariable& x )
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 		
    nll=log(sigma*sqrt(2.*M_PI)+EPS)+log(x+EPS)+0.5*square((log(x+EPS)-mu)/(sigma+EPS));//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for lognormal for one sample
   * \f$ 0.5\ln(2 \pi) + \ln(x) +\ln(\sigma) + 0.5(\frac{\ln(x)-\mu}{\sigma})^2  \f$
   * \ingroup QFC
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \param x :  data
   * \return return the nll for lognormal for one sample
   */	
  dvariable nllLognormal(const dvariable & mu, const dvariable & sigma, const double x )
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 		
    nll=log(sigma*sqrt(2.*M_PI)+EPS)+log(x+EPS)+0.5*square((log(x+EPS)-mu)/(sigma+EPS));//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for lognormal for one sample
   * \f$ 0.5\ln(2 \pi) + \ln(x) +\ln(\sigma) + 0.5(\frac{\ln(x)-\mu}{\sigma})^2  \f$
   * \ingroup QFC
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \param x :  data
   * \return return the nll for lognormal for one sample
   */	
  dvariable nllLognormal(const dvariable & mu, const dvariable & sigma, const dvariable & x )
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 		
    nll=log(sigma*sqrt(2.*M_PI)+EPS)+log(x+EPS)+0.5*square((log(x+EPS)-mu)/(sigma+EPS));//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
 
  /** nll for lognormal for many samples
   * \f$ 0.5n\ln(2 \pi) + \sum\ln(x) +n\ln(\sigma) + 0.5\sum(\frac{\ln(x)-\mu}{\sigma})^2  \f$
   * \ingroup QFC
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \param x :  data
   * \return return the nll for lognormal for many samples
   */	
  dvariable nllLognormal(const double mu, const double sigma, const dvar_vector & x )
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 	
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +sum(log(x+EPS))+0.5*norm2((log(x+EPS)-mu)/(sigma+EPS));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  

  /** nll for lognormal for many samples
   * \f$ 0.5n\ln(2 \pi) + \sum\ln(x) +n\ln(\sigma) + 0.5\sum(\frac{\ln(x)-\mu}{\sigma})^2  \f$
   * \ingroup QFC
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \param x :  data
   * \return return the nll for lognormal for many samples
   */	
  dvariable nllLognormal(const dvariable & mu, const dvariable & sigma, const dvector & x )
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 	
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +sum(log(x+EPS))+0.5*norm2((log(x+EPS)-mu)/(sigma+EPS));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  

  /** nll for lognormal for many samples
   * \f$ 0.5n\ln(2 \pi) + \sum\ln(x) +n\ln(\sigma) + 0.5\sum(\frac{\ln(x)-\mu}{\sigma})^2  \f$
   * \ingroup QFC
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \param x :  data
   * \return return the nll for lognormal for many samples
   */	
  dvariable nllLognormal(const dvariable & mu, const dvariable & sigma, const dvar_vector & x )
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 	
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +sum(log(x+EPS))+0.5*norm2((log(x+EPS)-mu)/(sigma+EPS));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  







  /** nll for lognormal(mu,tau) for one sample
   * \f$ 0.5\ln(2 \pi) + \ln(x) -0.5\ln(\tau) + 0.5\tau(\ln(x)-\mu)^2  \f$
   * \ingroup QFC
   * \param mu : mean parameter
   * \param tau : precision parameter, 1/variance
   * \param x :  data
   * \return return the nll for lognormal for one sample
   */	
  dvariable nllLognormal2(const dvariable & mu, const dvariable & tau, const double x )
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 	
    nll= -0.5*log(tau+EPS)+log(x+EPS)+0.5*tau*square(log(x+EPS)-mu)+0.5*log(2.*M_PI);//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for lognormal(mu,tau) for one sample
   * \f$ 0.5\ln(2 \pi) + \ln(x) -0.5\ln(\tau) + 0.5\tau(\ln(x)-\mu)^2  \f$
   * \ingroup QFC
   * \param mu : mean parameter
   * \param tau : precision parameter, 1/variance
   * \param x :  data
   * \return return the nll for lognormal for one sample
   */	
  dvariable nllLognormal2(const double mu, const double tau, const dvariable & x )
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 	
    nll= -0.5*log(tau+EPS)+log(x+EPS)+0.5*tau*square(log(x+EPS)-mu)+0.5*log(2.*M_PI);//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for lognormal(mu,tau) for one sample
   * \f$ 0.5\ln(2 \pi) + \ln(x) -0.5\ln(\tau) + 0.5\tau(\ln(x)-\mu)^2  \f$
   * \ingroup QFC
   * \param mu : mean parameter
   * \param tau : precision parameter, 1/variance
   * \param x :  data
   * \return return the nll for lognormal for one sample
   */	
  dvariable nllLognormal2(const dvariable & mu, const dvariable & tau, const dvariable & x )
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 	
    nll= -0.5*log(tau+EPS)+log(x+EPS)+0.5*tau*square(log(x+EPS)-mu)+0.5*log(2.*M_PI);//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for lognormal(mu,tau) for many samples
   * \f$ 0.5n\ln(2 \pi) + \sum\ln(x) -0.5n\ln(\tau) + 0.5\tau\sum(\ln(x)-\mu)^2  \f$
   * \ingroup QFC
   * \param mu : mean parameter
   * \param tau : precision parameter, 1/variance
   * \param x :  data
   * \return return the nll for lognormal for many samples
   */	
  dvariable nllLognormal2(const double mu, const double tau, const dvar_vector & x )
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    double n=double(x.size());
    nll=-0.5*n*log(tau+EPS)+sum(log(x+EPS))+0.5*tau*norm2(log(x+EPS)-mu)+0.5*n*log(2.*M_PI);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for lognormal(mu,tau) for many samples
   * \f$ 0.5n\ln(2 \pi) + \sum\ln(x) -0.5n\ln(\tau) + 0.5\tau\sum(\ln(x)-\mu)^2  \f$
   * \ingroup QFC
   * \param mu : mean parameter
   * \param tau : precision parameter, 1/variance
   * \param x :  data
   * \return return the nll for lognormal for many samples
   */	
  dvariable nllLognormal2(const dvariable & mu, const dvariable & tau, const dvector & x )
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    double n=double(x.size());
    nll=-0.5*n*log(tau+EPS)+sum(log(x+EPS))+0.5*tau*norm2(log(x+EPS)-mu)+0.5*n*log(2.*M_PI);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for lognormal(mu,tau) for many samples
   * \f$ 0.5n\ln(2 \pi) + \sum\ln(x) -0.5n\ln(\tau) + 0.5\tau\sum(\ln(x)-\mu)^2  \f$
   * \ingroup QFC
   * \param mu : mean parameter
   * \param tau : precision parameter, 1/variance
   * \param x :  data
   * \return return the nll for lognormal for many samples
   */	
  dvariable nllLognormal2(const dvariable & mu, const dvariable & tau, const dvar_vector & x )
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    double n=double(x.size());
    nll=-0.5*n*log(tau+EPS)+sum(log(x+EPS))+0.5*tau*norm2(log(x+EPS)-mu)+0.5*n*log(2.*M_PI);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }







  /** nll for poisson for one sample
   * \f$  \lambda -x\ln(\lambda)+\ln(x!) \f$
   * \ingroup QFC
   * \param lambda : mean parameter
   * \param x :  data
   * \return return the nll for poisson for one sample
   */	 
  double nllPoisson(const double lambda, const double x)
  {
    double nll=0;
    nll = lambda- x*log(lambda+EPS)+gammln(x+1.0);//full likelihood
    return nll;
  }

  /** nll for poisson for one sample
   * \f$  \lambda -x\ln(\lambda)+\ln(x!) \f$
   * \ingroup QFC
   * \param lambda : mean parameter
   * \param x :  data
   * \return return the nll for poisson for one sample
   */	 
  dvariable nllPoisson(const double lambda, const dvariable & x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    nll = lambda- x*log(lambda+EPS)+gammln(x+1.0);//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for poisson for one sample
   * \f$  \lambda -x\ln(\lambda)+\ln(x!) \f$
   * \ingroup QFC
   * \param lambda : mean parameter
   * \param x :  data
   * \return return the nll for poisson for one sample
   */	 
  dvariable nllPoisson(const dvariable & lambda, const double x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    nll = lambda- x*log(lambda+EPS)+gammln(x+1.0);//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for poisson for one sample
   * \f$  \lambda -x\ln(\lambda)+\ln(x!) \f$
   * \ingroup QFC
   * \param lambda : mean parameter
   * \param x :  data
   * \return return the nll for poisson for one sample
   */	 
  dvariable nllPoisson(const dvariable & lambda, const dvariable & x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    nll = lambda- x*log(lambda+EPS)+gammln(x+1.0);//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for poisson for many samples
   * \f$  n\lambda -\sum(x)\ln(\lambda)+\sum(\ln(x!)) \f$
   * \ingroup QFC
   * \param lambda : mean parameter
   * \param x :  data
   * \return return the nll for poisson for many samples
   */	 
  dvariable nllPoisson(const double lambda, const dvar_vector & x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    double n=double(x.size());
    nll = n*lambda- sum(x)*log(lambda+EPS)+sum(gammln(x+1.0));//full likelihood, can drop the last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  

  /** nll for poisson for many samples
   * \f$  n\lambda -\sum(x)\ln(\lambda)+\sum(\ln(x!)) \f$
   * \ingroup QFC
   * \param lambda : mean parameter
   * \param x :  data
   * \return return the nll for poisson for many samples
   */	 
  dvariable nllPoisson(const dvariable & lambda, const dvector & x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    double n=double(x.size());
    nll = n*lambda- sum(x)*log(lambda+EPS)+sum(gammln(x+1.0));//full likelihood, can drop the last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  

  /** nll for poisson for many samples
   * \f$  n\lambda -\sum(x)\ln(\lambda)+\sum(\ln(x!)) \f$
   * \ingroup QFC
   * \param lambda : mean parameter
   * \param x :  data
   * \return return the nll for poisson for many samples
   */	 
  dvariable nllPoisson(const dvariable & lambda, const dvar_vector & x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    double n=double(x.size());
    nll = n*lambda- sum(x)*log(lambda+EPS)+sum(gammln(x+1.0));//full likelihood, can drop the last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  



