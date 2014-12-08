
 /** 
  * \file	priors.cpp
  * \brief negative log likelihood functions with other functions useful for model estimation
  * \date 7/28/2011
  * \author Weihai Liu
  * \ingroup QFC
  *
  *  Following user defined functions are more useful for doing estimation model in admb,
  *  the easy way to use these functions is put this cpp file in the same directory with your tpl file
  *  and under the GLOBALS_SECTION , add a line on top as   #include "qfc_est.cpp" ,
  *  there is a testfunction.tpl file within this folder show how to use these functions.
  *
  *  ================  brief list for usage  ============================\n
  *  1. want to constrain the vector of probability sum as 1 and each as (0,1),  
  *     see logitProp() and its inverse invLogitProp()\n
  *  2. overloaded posfun(), boundp() for vector and matrix  \n
  *  3. constrain parameter within some upper bound only, see mf_upper_bound2(), 
  *     constrain the sum as 1 use normalize_p() with penalty\n
  *  4. nll(neg. log. likelihood) for inverse gamma, see nllInverseGamma()  \n 
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

  #if !defined(__QFC_EST__)
  #define __QFC_EST__
    #include <math.h>
    #include <admodel.h>
    #include <df1b2fun.h>
    #include <adrndeff.h>
    // define constant variable
    const double EPS = 1.e-30;          //tiny number to avoid 0 in log
  







  /** overloading function for log_comb(n choose x) for randome effect, used in nllBinomial below,
   *  ADMB built in function log_comb() not for vector type in RE
   * \ingroup QFC
   * \param n : number of trials
   * \param x : number of selected trial
   * \return return n choose x \f$ {{n}\choose{x}}  \f$
   */	
  df1b2vector log_comb(const df1b2vector & n,const df1b2vector & x)
  {
    df1b2vector tmp(n.indexmin(),n.indexmax());
    for(int i=n.indexmin();i<=n.indexmax();i++)
      tmp(i)=log_comb(n(i),x(i));
    return tmp;
  }
  df1b2vector log_comb(const df1b2vector & n,const dvector & x)
  {
    df1b2vector tmp(n.indexmin(),n.indexmax());
    for(int i=n.indexmin();i<=n.indexmax();i++)
      tmp(i)=log_comb(n(i),x(i));
    return tmp;
  }
  df1b2vector log_comb(const dvector & n,const df1b2vector & x)
  {
    df1b2vector tmp(n.indexmin(),n.indexmax());
    for(int i=n.indexmin();i<=n.indexmax();i++)
      tmp(i)=log_comb(n(i),x(i));
    return tmp;
  }	 







  ////////////////////////////////////////////////////////////////////////////////////////////
  //
  //                                    Negative Binomial 
  //
  ///////////////////////////////////////////////////////////////////////////////////////////

  /** nll for negative binomial N(m,s) for one sample, 
   * admb built in log_negbinomial_density(obs,mu,tau), in which tau=1.+mu/s for NB(m,s),
   * winbug use NB(p,r), in which p=s/(m+s) and r=s, \n 
   * \f[ -\ln(\Gamma(x+s))+ \ln(\Gamma(s))+\ln(x!)-s\ln(\frac{s}{m+s})-x\ln(\frac{m}{m+s})   \f]
   * \ingroup QFC
   * \param obs : observation data x
   * \param m : mean
   * \param s : scaling factor, some use r NB(p,r)
   * \return return the nll for neg. binomial for one sample
   */	
  double  nllNegativeBinomial(const double obs, const double m, const double s )
  {
    double nll=0; 
    nll= -gammln(obs+s)+ gammln(s)- s*log(s/(m+s)+EPS)- obs*log(m/(m+s)+EPS)+ gammln(obs+1.);
    return nll;
  }
  dvariable  nllNegativeBinomial(const dvariable & obs, const double m, const double s )
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 
    nll= -gammln(obs+s)+ gammln(s)- s*log(s/(m+s)+EPS)- obs*log(m/(m+s)+EPS)+ gammln(obs+1.);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }	
  dvariable  nllNegativeBinomial(const double obs, const dvariable & m, const dvariable & s)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 
    nll= -gammln(obs+s)+ gammln(s)- s*log(s/(m+s)+EPS)- obs*log(m/(m+s)+EPS)+ gammln(obs+1.);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }	
  dvariable  nllNegativeBinomial(const dvariable & obs, const dvariable & m, const double s)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 
    nll= -gammln(obs+s)+ gammln(s)- s*log(s/(m+s)+EPS)- obs*log(m/(m+s)+EPS)+ gammln(obs+1.);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable  nllNegativeBinomial(const dvariable & obs, const double m, const dvariable & s)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 
    nll= -gammln(obs+s)+ gammln(s)- s*log(s/(m+s)+EPS)- obs*log(m/(m+s)+EPS)+ gammln(obs+1.);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable  nllNegativeBinomial(const dvariable & obs, const dvariable & m, const dvariable & s)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 
    nll= -gammln(obs+s)+ gammln(s)- s*log(s/(m+s)+EPS)- obs*log(m/(m+s)+EPS)+ gammln(obs+1.);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for negative binomial N(m,s) for one sample,overload for random effect, 
   * admb built in log_negbinomial_density(obs,mu,tau), in which tau=1.+mu/s for NB(m,s),
   * winbug use NB(p,r), in which p=s/(m+s) and r=s, \n 
   * \f[ -\ln(\Gamma(x+s))+ \ln(\Gamma(s))+\ln(x!)-s\ln(\frac{s}{m+s})-x\ln(\frac{m}{m+s})   \f]
   * \ingroup QFC
   * \param obs : observation data x   
   * \param m : mean
   * \param s : scaling factor, some use r NB(p,r)
   * \return return the nll for neg. binomial for one sample
   */	
  df1b2variable  nllNegativeBinomial(const df1b2variable & obs, const double m, const double s)
  {
    df1b2variable nll=.0; 
    nll= -gammln(obs+s)+ gammln(s)- s*log(s/(m+s)+EPS)- obs*log(m/(m+s)+EPS)+ gammln(obs+1.);
    return nll;
  }
  df1b2variable  nllNegativeBinomial(const double obs, const df1b2variable & m, const df1b2variable & s)
  {
    df1b2variable nll=.0; 
    nll= -gammln(obs+s)+ gammln(s)- s*log(s/(m+s)+EPS)- obs*log(m/(m+s)+EPS)+ gammln(obs+1.);
    return nll;
  }
  df1b2variable  nllNegativeBinomial(const df1b2variable & obs, const df1b2variable & m, const double s)
  {
    df1b2variable nll=.0; 
    nll= -gammln(obs+s)+ gammln(s)- s*log(s/(m+s)+EPS)- obs*log(m/(m+s)+EPS)+ gammln(obs+1.);
    return nll;
  }
  df1b2variable  nllNegativeBinomial(const df1b2variable & obs, const double m, const df1b2variable & s)
  {
    df1b2variable nll=.0; 
    nll= -gammln(obs+s)+ gammln(s)- s*log(s/(m+s)+EPS)- obs*log(m/(m+s)+EPS)+ gammln(obs+1.);
    return nll;
  }
  df1b2variable  nllNegativeBinomial(const df1b2variable & obs, const df1b2variable & m, const df1b2variable & s)
  {
    df1b2variable nll=.0; 
    nll= -gammln(obs+s)+ gammln(s)- s*log(s/(m+s)+EPS)- obs*log(m/(m+s)+EPS)+ gammln(obs+1.);
    return nll;
  }





  /** nll for negative binomial N(m,s) for many samples, 
   * admb built in log_negbinomial_density(obs,mu,tau), in which tau=1.+mu/s for NB(m,s),
   * winbug use NB(p,r), in which p=s/(m+s) and r=s, \n
   * \f[ -\sum(\ln(\Gamma(x+s)))+ n\ln(\Gamma(s))+\sum(\ln(x!))-ns\ln(\frac{s}{m+s})-\sum(x)\ln(\frac{m}{m+s})   \f]
   * \ingroup QFC
   * \param obs : observation data
   * \param m : mean
   * \param s : scaling factor
   * \return return the nll for neg. binomial for many samples
   */	
  dvariable  nllNegativeBinomial(const dvector & obs, const dvariable & m, const dvariable & s)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 
    double n=double(obs.size());
    nll= -sum(gammln(obs+s))+ n*gammln(s)- n*s*log(s/(m+s)+EPS)- sum(obs)*log(m/(m+s)+EPS)+ sum(gammln(obs+1.));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable  nllNegativeBinomial(const dvar_vector & obs, const double m, const double s)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 
    double n=double(obs.size());
    nll= -sum(gammln(obs+s))+ n*gammln(s)- n*s*log(s/(m+s)+EPS)- sum(obs)*log(m/(m+s)+EPS)+ sum(gammln(obs+1.));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable  nllNegativeBinomial(const dvar_vector & obs, const dvariable & m, const dvariable & s)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 
    double n=double(obs.size());
    nll= -sum(gammln(obs+s))+ n*gammln(s)- n*s*log(s/(m+s)+EPS)- sum(obs)*log(m/(m+s)+EPS)+ sum(gammln(obs+1.));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for negative binomial N(m,s) for many samples, overload for random effect,
   * admb built in log_negbinomial_density(obs,mu,tau), in which tau=1.+mu/s for NB(m,s),
   * winbug use NB(p,r), in which p=s/(m+s) and r=s, \n
   * \f[ -\sum(\ln(\Gamma(x+s)))+ n\ln(\Gamma(s))+\sum(\ln(x!))-ns\ln(\frac{s}{m+s})-\sum(x)\ln(\frac{m}{m+s})   \f]
   * \ingroup QFC
   * \param obs : observation data
   * \param m : mean
   * \param s : scaling factor  
   * \return return the nll for neg. binomial for many samples
   */	
  df1b2variable  nllNegativeBinomial(const df1b2vector & obs, const double m, const double s)
  {
    df1b2variable nll=.0; 
    double n=double(size_count(obs));
    nll= -sum(gammln(obs+s))+ n*gammln(s)- n*s*log(s/(m+s)+EPS)- sum(obs)*log(m/(m+s)+EPS)+ sum(gammln(obs+1.));
    return nll;
  }
  df1b2variable  nllNegativeBinomial(const dvector & obs, const df1b2variable & m, const df1b2variable & s)
  {
    df1b2variable nll=.0; 
    double n=double(size_count(obs));
    nll= -sum(gammln(obs+s))+ n*gammln(s)- n*s*log(s/(m+s)+EPS)- sum(obs)*log(m/(m+s)+EPS)+ sum(gammln(obs+1.));
    return nll;
  }
  df1b2variable  nllNegativeBinomial(const df1b2vector & obs, const df1b2variable & m, const df1b2variable & s)
  {
    df1b2variable nll=.0; 
    double n=double(size_count(obs));
    nll= -sum(gammln(obs+s))+ n*gammln(s)- n*s*log(s/(m+s)+EPS)- sum(obs)*log(m/(m+s)+EPS)+ sum(gammln(obs+1.));
    return nll;
  }




  ////////////////////////////////////////////////////////////////////////////////////////////
  //
  //                                    Negative Binomial with tau
  //
  ///////////////////////////////////////////////////////////////////////////////////////////

  /** nll for negative binomial N(mu,tau) for one sample, 
   * admb built in log_negbinomial_density(obs,mu,tau), in which tau=1.+mu/s for NB(m,s),
   * winbug us NB(p,r), in which p=s/(m+s) and r=s, \n
   * \ingroup QFC
   * \param obs : observation data   
   * \param m : mean
   * \param tau : overdispersion parameter,
   * \return return the nll for neg. binomial for one sample
   */	
  double nllNegativeBinomial2(const double obs, const double m, const double tau)
  {
    return -log_density_negbinomial (obs,m,tau); //use admb built in function
  } 
  dvariable nllNegativeBinomial2(const double obs, const dvariable & m, const dvariable & tau)
  {
    return -1.*log_negbinomial_density(obs,m,tau); //use admb built in function
  } 	
  dvariable nllNegativeBinomial2(const dvariable & obs, const double m, const double tau)
  {
    return nllNegativeBinomial(obs,m,m/(tau-1.+EPS));
  } 	
  dvariable nllNegativeBinomial2(const dvariable & obs, const dvariable & m, const double tau)
  {
    return nllNegativeBinomial(obs,m,m/(tau-1.+EPS));
  } 
  dvariable nllNegativeBinomial2(const dvariable & obs, const double m, const dvariable & tau)
  {
    return nllNegativeBinomial(obs,m,m/(tau-1.+EPS));
  } 
  dvariable nllNegativeBinomial2(const dvariable & obs, const dvariable & m, const dvariable & tau)
  {
    return nllNegativeBinomial(obs, m,m/(tau-1.+EPS));
  } 

  /** nll for negative binomial N(mu,tau) for one sample,overload for random effect 
   * admb built in log_negbinomial_density(obs,mu,tau), in which tau=1.+mu/s for NB(m,s),
   * winbug us NB(p,r), in which p=s/(m+s) and r=s, \n
   * \ingroup QFC
   * \param obs : observation data   
   * \param m : mean
   * \param tau : overdispersion parameter,
   * \return return the nll for neg. binomial for one sample
   */
  df1b2variable nllNegativeBinomial2(const df1b2variable & obs, const double m, const double tau)
  {
    return nllNegativeBinomial(obs,m,m/(tau-1.+EPS));
  }
  df1b2variable nllNegativeBinomial2(const double obs, const df1b2variable & m, const df1b2variable & tau)
  {
    return nllNegativeBinomial(obs,m,m/(tau-1.+EPS));
  }
  df1b2variable nllNegativeBinomial2(const df1b2variable & obs, const df1b2variable & m, const df1b2variable & tau)
  {
    return nllNegativeBinomial(obs,m,m/(tau-1.+EPS));
  }






  ////////////////////////////////////////////////////////////////////////////////////////////
  //
  //                                    Multinomial
  //
  ///////////////////////////////////////////////////////////////////////////////////////////

  /** nll for Multinomial for one sample
   * \f$  -\sum_{i}(n_{i}\ln(p_{i})) -\ln((\sum_{i}n_{i})!) +\sum_{i}(\ln(n_{i}!)) \f$
   * \ingroup QFC
   * \param obsN : observation data   
   * \param p : proportion vector, sum as 1
   * \return return the nll for Multinomial for one sample
   */	
  double  nllMultiNomial(const dvector & obsN, const dvector & p)
  {
    double nll=0;  
    nll= -1.*(obsN*log(p+EPS) + gammln(sum(obsN)+1.) - sum(gammln(obsN+1.))); //full likelihood
    return nll;
  }	
  dvariable  nllMultiNomial(const dvector & obsN, const dvar_vector & p)
  {
    RETURN_ARRAYS_INCREMENT(); 
    dvariable nll=0;  
    nll= -1.*(obsN*log(p+EPS) + gammln(sum(obsN)+1.) - sum(gammln(obsN+1.))); //full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable  nllMultiNomial(const dvar_vector & obsN, const dvector & p)
  {
    RETURN_ARRAYS_INCREMENT(); 
    dvariable nll=0;  
    nll= -1.*(obsN*log(p+EPS) + gammln(sum(obsN)+1.) - sum(gammln(obsN+1.))); //full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  } 	
  dvariable  nllMultiNomial(const dvar_vector & obsN, const dvar_vector & p)
  {
    RETURN_ARRAYS_INCREMENT(); 
    dvariable nll=0;  
    nll= -1.*(obsN*log(p+EPS) + gammln(sum(obsN)+1.) - sum(gammln(obsN+1.))); //full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }    

  /** nll for Multinomial for one sample for random effect
   * \f$  -\sum_{i}(n_{i}\ln(p_{i})) -\ln((\sum_{i}n_{i})!) +\sum_{i}(\ln(n_{i}!)) \f$
   * \ingroup QFC
   * \param obsN : observation data   
   * \param p : proportion vector, sum as 1
   * \return return the nll for Multinomial for one sample
   */	
  df1b2variable  nllMultiNomial(const df1b2vector & obsN, const dvector & p)
  {
    df1b2variable nll=.0;  
    nll= -1.*(obsN*log(p+EPS) + gammln(sum(obsN)+1.) - sum(gammln(obsN+1.))); //full likelihood
    return nll;
  }
  df1b2variable  nllMultiNomial(const dvector & obsN, const df1b2vector & p)
  {
    df1b2variable nll=.0;  
    nll= -1.*(obsN*log(p+EPS) + gammln(sum(obsN)+1.) - sum(gammln(obsN+1.))); //full likelihood
    return nll;
  }  
  df1b2variable  nllMultiNomial(const df1b2vector & obsN, const df1b2vector & p)
  {
    df1b2variable nll=.0;  
    nll= -1.*(obsN*log(p+EPS) + gammln(sum(obsN)+1.) - sum(gammln(obsN+1.))); //full likelihood
    return nll;
  }




  ////////////////////////////////////////////////////////////////////////////////////////////
  //
  //                                    Dirichlet
  //
  ///////////////////////////////////////////////////////////////////////////////////////////

  /** nll for dirichlet for one sample
   * \f$  -\ln\Gamma(\sum_{i}(\alpha_{i})) -\sum_{i}(\ln(\Gamma(\alpha_{i}))) +\sum_{i}((\alpha_{i}-1)\ln(p_{i}))  \f$
   * \ingroup QFC
   * \param p : observation proportion, sum as 1    
   * \param shape : alpha parameter, >0
   * \return return the nll for dirichlet for one sample
   */	
  double nllDirichlet(const dvector & p, const dvector & shape)
  {
    double nll=0;  
    nll= -1.*(gammln(sum(shape)) - sum(gammln(shape)) + (shape-1.)*log(p+EPS));
    return nll;
  }
  dvariable nllDirichlet(const dvar_vector & p, const dvector & shape)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll= -1.*(gammln(sum(shape)) - sum(gammln(shape)) + (shape-1.)*log(p+EPS));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }	
  dvariable nllDirichlet(const dvector & p, const dvar_vector & shape)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll= -1.*(gammln(sum(shape)) - sum(gammln(shape)) + (shape-1.)*log(p+EPS));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllDirichlet(const dvar_vector & p, const dvar_vector & shape)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll= -1.*(gammln(sum(shape)) - sum(gammln(shape)) + (shape-1.)*log(p+EPS));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for dirichlet for one sample for random effect
   * \f$  -\ln\Gamma(\sum_{i}(\alpha_{i})) -\sum_{i}(\ln(\Gamma(\alpha_{i}))) +\sum_{i}((\alpha_{i}-1)\ln(p_{i}))  \f$
   * \ingroup QFC
   * \param p : observation proportion, sum as 1    
   * \param shape : alpha parameter, >0
   * \return return the nll for dirichlet for one sample
   */	
  df1b2variable nllDirichlet(const df1b2vector & p, const dvector & shape)
  {
    df1b2variable nll=.0;  
    nll= -1.*(gammln(sum(shape)) - sum(gammln(shape)) + (shape-1.)*log(p+EPS));
    return nll;
  }  
  df1b2variable nllDirichlet(const dvector & p, const df1b2vector & shape)
  {
    df1b2variable nll=.0;  
    nll= -1.*(gammln(sum(shape)) - sum(gammln(shape)) + (shape-1.)*log(p+EPS));
    return nll;
  }
  df1b2variable nllDirichlet(const df1b2vector & p, const df1b2vector & shape)
  {
    df1b2variable nll=.0;  
    nll= -1.*(gammln(sum(shape)) - sum(gammln(shape)) + (shape-1.)*log(p+EPS));
    return nll;
  }  

 


  ////////////////////////////////////////////////////////////////////////////////////////////
  //
  //                                    Gamma
  //
  ///////////////////////////////////////////////////////////////////////////////////////////

  /** nll for gamma for one sample
   * Gamma(a,b) similar to log_gamma_density(r,mu) in admb, in which a=r, b=mu
   * \f$ -a \ln(b) + \ln(\Gamma(a)) - (a-1)\ln(x)+ bx   \f$
   * \ingroup QFC
   * \param x :  data   
   * \param a : alpha parameter,also call shape,>0
   * \param b : beta parameter,also call rate,>0
   * \return return the nll for gamma for one sample
   */	
  double nllGamma(const double & x, const double a, const double b)
  {
    return -1.*log_gamma_density(x,a,b);  //call admb built in function
  }
  dvariable nllGamma(const dvariable & x, const double a, const double b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll= gammln(a) - a*log(b) -(a-1.)*log(x+EPS) + b*x;  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }	
  dvariable nllGamma(const double x, const dvariable & a, const dvariable & b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll= gammln(a) - a*log(b) -(a-1.)*log(x+EPS) + b*x;  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }	
  dvariable nllGamma(const dvariable & x, const dvariable & a, const double b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll= gammln(a) - a*log(b) -(a-1.)*log(x+EPS) + b*x;  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllGamma(const dvariable & x, const double a, const dvariable & b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll= gammln(a) - a*log(b) -(a-1.)*log(x+EPS) + b*x;  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllGamma(const dvariable & x, const dvariable & a, const dvariable & b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll= gammln(a) - a*log(b) -(a-1.)*log(x+EPS) + b*x;  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for gamma for one sample for random effect
   * Gamma(a,b) similar to log_gamma_density(r,mu) in admb, in which a=r, b=mu
   * \f$ -a \ln(b) + \ln(\Gamma(a)) - (a-1)\ln(x)+ bx   \f$
   * \ingroup QFC
   * \param x :  data  
   * \param a : alpha parameter,>0
   * \param b : beta parameter,>0
   * \return return the nll for gamma for one sample
   */	
  df1b2variable nllGamma(const df1b2variable & x, const double a, const double b)
  {
    df1b2variable nll=.0;  
    nll= gammln(a) - a*log(b) -(a-1.)*log(x+EPS) + b*x;  
    return nll;
  }
  df1b2variable nllGamma(const double x, const df1b2variable & a, const df1b2variable & b)
  {
    df1b2variable nll=.0;  
    nll= gammln(a) - a*log(b) -(a-1.)*log(x+EPS) + b*x;  
    return nll;
  }
  df1b2variable nllGamma(const df1b2variable & x, const df1b2variable & a, const double b)
  {
    df1b2variable nll=.0;  
    nll= gammln(a) - a*log(b) -(a-1.)*log(x+EPS) + b*x;  
    return nll;
  }
  df1b2variable nllGamma(const df1b2variable & x, const double a, const df1b2variable & b)
  {
    df1b2variable nll=.0;  
    nll= gammln(a) - a*log(b) -(a-1.)*log(x+EPS) + b*x;  
    return nll;
  }
  df1b2variable nllGamma(const df1b2variable & x, const df1b2variable & a, const df1b2variable & b)
  {
    df1b2variable nll=.0;  
    nll= gammln(a) - a*log(b) -(a-1.)*log(x+EPS) + b*x;  
    return nll;
  }



  /** nll for gamma for many samples
   * \f$ -na\ln(b) + n\ln(\Gamma(a)) - (a-1)\sum(\ln(x))+ b\sum(x)   \f$
   * \ingroup QFC
   * \param x :  data   
   * \param a : alpha parameter,>0
   * \param b : beta parameter,>0
   * \return return the nll for gamma for many samples
   */	
  double nllGamma(const dvector & x, const double a, const double b)
  {
    double nll=0;  
    double n=double(x.size());
    nll=n*gammln(a) - n*a*log(b) -(a-1.)*sum(log(x+EPS)) + b*sum(x);  
    return nll;
  }
  dvariable nllGamma(const dvar_vector & x, const double a, const double b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll=n*gammln(a) - n*a*log(b) -(a-1.)*sum(log(x+EPS)) + b*sum(x);  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }	
  dvariable nllGamma(const dvector & x, const dvariable & a, const dvariable & b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll=n*gammln(a) - n*a*log(b) -(a-1.)*sum(log(x+EPS)) + b*sum(x);  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllGamma(const dvar_vector & x, const dvariable & a, const dvariable & b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll=n*gammln(a) - n*a*log(b) -(a-1.)*sum(log(x+EPS)) + b*sum(x);  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for gamma for many samples for random effect
   * \f$ -na\ln(b) + n\ln(\Gamma(a)) - (a-1)\sum(\ln(x))+ b\sum(x)   \f$
   * \ingroup QFC
   * \param x :  data   
   * \param a : alpha parameter,>0
   * \param b : beta parameter,>0
   * \return return the nll for gamma for many samples
   */	
  df1b2variable nllGamma(const df1b2vector & x, const double a, const double b)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x));
    nll=n*gammln(a) - n*a*log(b) -(a-1.)*sum(log(x+EPS)) + b*sum(x);  
    return nll;
  }  
  df1b2variable nllGamma(const dvector & x, const df1b2variable & a, const df1b2variable & b)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x));
    nll=n*gammln(a) - n*a*log(b) -(a-1.)*sum(log(x+EPS)) + b*sum(x);  
    return nll;
  }    
  df1b2variable nllGamma(const df1b2vector & x, const df1b2variable & a, const df1b2variable & b)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x));
    nll=n*gammln(a) - n*a*log(b) -(a-1.)*sum(log(x+EPS)) + b*sum(x);  
    return nll;
  }  




  ////////////////////////////////////////////////////////////////////////////////////////////
  //
  //                                    Beta
  //
  ///////////////////////////////////////////////////////////////////////////////////////////
   
  /** nll for beta for one sample
   * \f$ -\ln(\Gamma(a+b)) +\ln(\Gamma(a)) + \ln(\Gamma(b))-(a-1)\ln(x)-(b-1)\ln(1-x)   \f$
   * \ingroup QFC
   * \param x :  data   
   * \param a : alpha parameter,>0
   * \param b : beta parameter,>0
   * \return return the nll for beta for one sample
   */
  double nllBeta(const double x, const double a, const double b)
  {
    double nll=0;  
    nll=gammln(a)+gammln(b)-gammln(a+b)-(a-1.)*log(x+EPS)-(b-1.)*log(1.-x+EPS);  
    return nll;
  }
  dvariable nllBeta(const dvariable & x, const double a, const double b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll=gammln(a)+gammln(b)-gammln(a+b)-(a-1.)*log(x+EPS)-(b-1.)*log(1.-x+EPS);  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }   
  dvariable nllBeta(const double x, const dvariable & a, const dvariable & b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll=gammln(a)+gammln(b)-gammln(a+b)-(a-1.)*log(x+EPS)-(b-1.)*log(1.-x+EPS);  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  } 
  dvariable nllBeta(const dvariable & x, const dvariable & a, const double b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll=gammln(a)+gammln(b)-gammln(a+b)-(a-1.)*log(x+EPS)-(b-1.)*log(1.-x+EPS);  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  
  dvariable nllBeta(const dvariable & x, const double a, const dvariable & b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll=gammln(a)+gammln(b)-gammln(a+b)-(a-1.)*log(x+EPS)-(b-1.)*log(1.-x+EPS);  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  
  dvariable nllBeta(const dvariable & x, const dvariable & a, const dvariable & b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll=gammln(a)+gammln(b)-gammln(a+b)-(a-1.)*log(x+EPS)-(b-1.)*log(1.-x+EPS);  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  

  /** nll for beta for one sample for random effect
   * \f$ -\ln(\Gamma(a+b)) +\ln(\Gamma(a)) + \ln(\Gamma(b))-(a-1)\ln(x)-(b-1)\ln(1-x)   \f$
   * \ingroup QFC
   * \param x :  data   
   * \param a : alpha parameter,>0
   * \param b : beta parameter,>0
   * \return return the nll for beta for one sample
   */
  df1b2variable nllBeta(const df1b2variable & x, const double a, const double b)
  {
    df1b2variable nll=.0;  
    nll=gammln(a)+gammln(b)-gammln(a+b)-(a-1.)*log(x+EPS)-(b-1.)*log(1.-x+EPS);  
    return nll;
  } 	
  df1b2variable nllBeta(const df1b2variable & x, const df1b2variable & a, const double b)
  {
    df1b2variable nll=.0;  
    nll=gammln(a)+gammln(b)-gammln(a+b)-(a-1.)*log(x+EPS)-(b-1.)*log(1.-x+EPS);  
    return nll;
  } 
  df1b2variable nllBeta(const df1b2variable & x, const double a, const df1b2variable & b)
  {
    df1b2variable nll=.0;  
    nll=gammln(a)+gammln(b)-gammln(a+b)-(a-1.)*log(x+EPS)-(b-1.)*log(1.-x+EPS);  
    return nll;
  } 
  df1b2variable nllBeta(const double x, const df1b2variable & a, const df1b2variable & b)
  {
    df1b2variable nll=.0;  
    nll=gammln(a)+gammln(b)-gammln(a+b)-(a-1.)*log(x+EPS)-(b-1.)*log(1.-x+EPS);  
    return nll;
  } 
  df1b2variable nllBeta(const df1b2variable & x, const df1b2variable & a, const df1b2variable & b)
  {
    df1b2variable nll=.0;  
    nll=gammln(a)+gammln(b)-gammln(a+b)-(a-1.)*log(x+EPS)-(b-1.)*log(1.-x+EPS);  
    return nll;
  } 



  /** nll for beta for many samples
   * \f$ -n\ln(\Gamma(a+b)) +n\ln(\Gamma(a)) + n\ln(\Gamma(b))-(a-1)\sum(\ln(x)) -(b-1)\sum(\ln(1-x))   \f$
   * \ingroup QFC
   * \param x :  data   
   * \param a : alpha parameter
   * \param b : beta parameter
   * \return return the nll for beta for many samples
   */	
  dvariable nllBeta(const dvar_vector & x, const double a, const double b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll=n*gammln(a)+n*gammln(b)-n*gammln(a+b)-(a-1.)*sum(log(x+EPS))-(b-1.)*sum(log(1.-x+EPS));  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllBeta(const dvector & x, const dvariable & a, const dvariable & b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll=n*gammln(a)+n*gammln(b)-n*gammln(a+b)-(a-1.)*sum(log(x+EPS))-(b-1.)*sum(log(1.-x+EPS));  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllBeta(const dvar_vector & x, const dvariable & a, const dvariable & b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll=n*gammln(a)+n*gammln(b)-n*gammln(a+b)-(a-1.)*sum(log(x+EPS))-(b-1.)*sum(log(1.-x+EPS));  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  
  /** nll for beta for many samples for random effect
   * \f$ -n\ln(\Gamma(a+b)) +n\ln(\Gamma(a)) + n\ln(\Gamma(b))-(a-1)\sum(\ln(x)) -(b-1)\sum(\ln(1-x))   \f$
   * \ingroup QFC
   * \param x :  data   
   * \param a : alpha parameter
   * \param b : beta parameter
   * \return return the nll for beta for many samples
   */	
  df1b2variable nllBeta(const df1b2vector & x, const double a, const double b)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x));
    nll=n*gammln(a)+n*gammln(b)-n*gammln(a+b)-(a-1.)*sum(log(x+EPS))-(b-1.)*sum(log(1.-x+EPS));  
    return nll;
  }  
  df1b2variable nllBeta(const dvector & x, const df1b2variable & a, const df1b2variable & b)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x));
    nll=n*gammln(a)+n*gammln(b)-n*gammln(a+b)-(a-1.)*sum(log(x+EPS))-(b-1.)*sum(log(1.-x+EPS));  
    return nll;
  }   
  df1b2variable nllBeta(const df1b2vector & x, const df1b2variable & a, const df1b2variable & b)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x));
    nll=n*gammln(a)+n*gammln(b)-n*gammln(a+b)-(a-1.)*sum(log(x+EPS))-(b-1.)*sum(log(1.-x+EPS));  
    return nll;
  } 




  ////////////////////////////////////////////////////////////////////////////////////////////
  //
  //                                    Normal
  //
  ///////////////////////////////////////////////////////////////////////////////////////////

  /** nll for normal for one sample
   * \f$ 0.5\ln(2 \pi) + \ln(\sigma) + 0.5(\frac{x-\mu}{\sigma})^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \return return the nll for normal for one sample
   */	
  double nllNormal(const double x, const double mu, const double sigma)
  {
    double nll=0;  
    nll=log(sigma*sqrt(2.*M_PI)+EPS) +0.5*square((x-mu)/(sigma+EPS));  
    return nll;
  }
  dvariable nllNormal(const dvariable & x, const double mu, const double sigma)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll=log(sigma*sqrt(2.*M_PI)+EPS) +0.5*square((x-mu)/(sigma+EPS));  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllNormal(const double x, const dvariable & mu, const dvariable & sigma)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll=log(sigma*sqrt(2.*M_PI)+EPS) +0.5*square((x-mu)/(sigma+EPS));  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }	
  dvariable nllNormal(const dvariable & x, const dvariable & mu, const double sigma)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll=log(sigma*sqrt(2.*M_PI)+EPS) +0.5*square((x-mu)/(sigma+EPS));  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }	
  dvariable nllNormal(const dvariable & x, const double mu, const dvariable & sigma)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll=log(sigma*sqrt(2.*M_PI)+EPS) +0.5*square((x-mu)/(sigma+EPS));  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllNormal(const dvariable & x, const dvariable & mu, const dvariable & sigma)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll=log(sigma*sqrt(2.*M_PI)+EPS) +0.5*square((x-mu)/(sigma+EPS));  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for normal for one sample for random effect
   * \f$ 0.5\ln(2 \pi) + \ln(\sigma) + 0.5(\frac{x-\mu}{\sigma})^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \return return the nll for normal for one sample
   */	
  df1b2variable nllNormal(const df1b2variable & x, const double mu, const double sigma)
  {
    df1b2variable nll=.0;  
    nll=log(sigma*sqrt(2.*M_PI)+EPS) +0.5*square((x-mu)/(sigma+EPS));  
    return nll;
  }
  df1b2variable nllNormal(const df1b2variable & x, const df1b2variable & mu, const double sigma)
  {
    df1b2variable nll=.0;  
    nll=log(sigma*sqrt(2.*M_PI)+EPS) +0.5*square((x-mu)/(sigma+EPS));  
    return nll;
  }
  df1b2variable nllNormal(const df1b2variable & x, const double mu, const df1b2variable & sigma)
  {
    df1b2variable nll=.0;  
    nll=log(sigma*sqrt(2.*M_PI)+EPS) +0.5*square((x-mu)/(sigma+EPS));  
    return nll;
  }
  df1b2variable nllNormal(const double x, const df1b2variable & mu, const df1b2variable & sigma)
  {
    df1b2variable nll=.0;  
    nll=log(sigma*sqrt(2.*M_PI)+EPS) +0.5*square((x-mu)/(sigma+EPS));  
    return nll;
  }
  df1b2variable nllNormal(const df1b2variable & x, const df1b2variable & mu, const df1b2variable & sigma)
  {
    df1b2variable nll=.0;  
    nll=log(sigma*sqrt(2.*M_PI)+EPS) +0.5*square((x-mu)/(sigma+EPS));  
    return nll;
  }



  /** nll for normal for many samples, but mu is for common
   * \f$ 0.5n\ln(2 \pi) + n\ln(\sigma) + 0.5\sum(\frac{x-\mu}{\sigma})^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \return return the nll for normal for many samples sharing one mu
   */	
  double nllNormal(const dvector & x, const double mu, const double sigma)
  {
    double nll=0;  
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +0.5*norm2((x-mu)/(sigma+EPS));  
    return nll;
  }
  dvariable nllNormal(const dvar_vector& x, const double mu, const double sigma)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +0.5*norm2((x-mu)/(sigma+EPS));  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllNormal(const dvector & x, const dvariable & mu, const dvariable & sigma)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +0.5*norm2((x-mu)/(sigma+EPS));  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllNormal(const dvar_vector & x, const dvariable & mu, const dvariable & sigma)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +0.5*norm2((x-mu)/(sigma+EPS));  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
 
  /** nll for normal for many samples, but mu is for common, overload for random effect
   * \f$ 0.5n\ln(2 \pi) + n\ln(\sigma) + 0.5\sum(\frac{x-\mu}{\sigma})^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \return return the nll for normal for many samples sharing one mu
   */	
  df1b2variable nllNormal(const df1b2vector & x, const double mu, const double sigma)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x));
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +0.5*norm2((x-mu)/(sigma+EPS));  
    return nll;
  }
  df1b2variable nllNormal(const dvector & x, const df1b2variable & mu, const df1b2variable & sigma)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x));
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +0.5*norm2((x-mu)/(sigma+EPS));  
    return nll;
  }
  df1b2variable nllNormal(const df1b2vector & x, const df1b2variable & mu, const df1b2variable & sigma)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x));
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +0.5*norm2((x-mu)/(sigma+EPS));  
    return nll;
  }
 


  /** nll for normal for many samples, each has its own mean
   * \f$ 0.5n\ln(2 \pi) + n\ln(\sigma) + 0.5\sum(\frac{x_{i}-\mu_{i}}{\sigma})^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \return return the nll for normal for many samples, each has own mean
   */	
  dvariable nllNormal(const dvar_vector & x, const dvector & mu, const double sigma)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +0.5*norm2((x-mu)/(sigma+EPS));  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  } 	
  dvariable nllNormal(const dvector & x, const dvar_vector & mu, const dvariable & sigma)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +0.5*norm2((x-mu)/(sigma+EPS));  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllNormal(const dvar_vector & x, const dvar_vector & mu, const dvariable & sigma)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +0.5*norm2((x-mu)/(sigma+EPS));  
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for normal for many samples, each has its own mean for random effect
   * \f$ 0.5n\ln(2 \pi) + n\ln(\sigma) + 0.5\sum(\frac{x_{i}-\mu_{i}}{\sigma})^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \return return the nll for normal for many samples, each has own mean
   */	
  df1b2variable nllNormal(const df1b2vector & x, const dvector & mu, const double sigma)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x));
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +0.5*norm2((x-mu)/(sigma+EPS));  
    return nll;
  } 	
  df1b2variable nllNormal(const dvector & x, const df1b2vector & mu, const df1b2variable & sigma)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x));
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +0.5*norm2((x-mu)/(sigma+EPS));  
    return nll;
  } 
  df1b2variable nllNormal(const df1b2vector & x, const df1b2vector & mu, const df1b2variable & sigma)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x));
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +0.5*norm2((x-mu)/(sigma+EPS));  
    return nll;
  } 






  ////////////////////////////////////////////////////////////////////////////////////////////
  //
  //                                    Normal with tau
  //
  ///////////////////////////////////////////////////////////////////////////////////////////

  /** nll for normal(mu,tau) for one sample
   * \f$ 0.5\ln(2 \pi) -0.5 \ln(\tau) + 0.5\tau(x-\mu)^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param tau : precision, 1/variance
   * \return return the nll for normal for one sample
   */	
  dvariable nllNormal2(const dvariable & x, const double mu, const double tau)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll = -0.5*log(tau+EPS)+0.5*tau*square(x-mu)+0.5*log(2.*M_PI);//full likelihood, can drop last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllNormal2(const double x, const dvariable & mu, const dvariable & tau)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll = -0.5*log(tau+EPS)+0.5*tau*square(x-mu)+0.5*log(2.*M_PI);//full likelihood, can drop last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllNormal2(const dvariable & x, const dvariable & mu, const dvariable & tau)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll = -0.5*log(tau+EPS)+0.5*tau*square(x-mu)+0.5*log(2.*M_PI);//full likelihood, can drop last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for normal(mu,tau) for one sample for random effect
   * \f$ 0.5\ln(2 \pi) -0.5 \ln(\tau) + 0.5\tau(x-\mu)^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param tau : precision, 1/variance
   * \return return the nll for normal for one sample
   */	
  df1b2variable nllNormal2(const df1b2variable & x, const double mu, const double tau)
  {
    df1b2variable nll=.0;  
    nll = -0.5*log(tau+EPS)+0.5*tau*square(x-mu)+0.5*log(2.*M_PI);//full likelihood, can drop last term
    return nll;
  }
  df1b2variable nllNormal2(const double x, const df1b2variable & mu, const df1b2variable & tau)
  {
    df1b2variable nll=.0;  
    nll = -0.5*log(tau+EPS)+0.5*tau*square(x-mu)+0.5*log(2.*M_PI);//full likelihood, can drop last term
    return nll;
  }
  df1b2variable nllNormal2(const df1b2variable & x, const df1b2variable & mu, const df1b2variable & tau)
  {
    df1b2variable nll=.0;  
    nll = -0.5*log(tau+EPS)+0.5*tau*square(x-mu)+0.5*log(2.*M_PI);//full likelihood, can drop last term
    return nll;
  }




  /** nll for normal(mu,tau) for many samples
   * \f$ 0.5n\ln(2 \pi) -0.5n\ln(\tau) + 0.5\tau\sum(x-\mu)^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param tau : precision, 1/variance
   * \return return the nll for normal for many samples
   */	
  dvariable nllNormal2(const dvar_vector & x, const double mu, const double tau)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll = -0.5*n*log(tau+EPS)+0.5*tau*norm2(x-mu)+0.5*n*log(2.*M_PI);//full likelihood, can drop last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllNormal2(const dvector & x, const dvariable & mu, const dvariable & tau)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll = -0.5*n*log(tau+EPS)+0.5*tau*norm2(x-mu)+0.5*n*log(2.*M_PI);//full likelihood, can drop last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllNormal2(const dvar_vector & x, const dvariable & mu, const dvariable & tau)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll = -0.5*n*log(tau+EPS)+0.5*tau*norm2(x-mu)+0.5*n*log(2.*M_PI);//full likelihood, can drop last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for normal(mu,tau) for many samples for random effect
   * \f$ 0.5n\ln(2 \pi) -0.5n\ln(\tau) + 0.5\tau\sum(x-\mu)^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param tau : precision, 1/variance
   * \return return the nll for normal for many samples
   */	
  df1b2variable nllNormal2(const df1b2vector & x, const double  mu, const double tau)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x));
    nll = -0.5*n*log(tau+EPS)+0.5*tau*norm2(x-mu)+0.5*n*log(2.*M_PI);//full likelihood, can drop last term
    return nll;
  }
  df1b2variable nllNormal2(const dvector & x, const df1b2variable &  mu, const df1b2variable & tau)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x));
    nll = -0.5*n*log(tau+EPS)+0.5*tau*norm2(x-mu)+0.5*n*log(2.*M_PI);//full likelihood, can drop last term
    return nll;
  }
  df1b2variable nllNormal2(const df1b2vector & x, const df1b2variable &  mu, const df1b2variable & tau)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x));
    nll = -0.5*n*log(tau+EPS)+0.5*tau*norm2(x-mu)+0.5*n*log(2.*M_PI);//full likelihood, can drop last term
    return nll;
  }



  /** nll for normal(mu,tau) for many samples, each has its own mean
   * \f$ 0.5n\ln(2 \pi) + n\ln(\sigma) + 0.5\tau\sum(x_{i}-\mu_{i})^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param tau : precision, 1/variance
   * \return return the nll for normal for many samples, each has own mean
   */	
  dvariable nllNormal2(const dvar_vector & x, const dvector & mu, const double tau)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll = -0.5*n*log(tau+EPS)+0.5*tau*norm2(x-mu)+0.5*n*log(2.*M_PI);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  } 
  dvariable nllNormal2(const dvector & x, const dvar_vector & mu, const dvariable & tau)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll = -0.5*n*log(tau+EPS)+0.5*tau*norm2(x-mu)+0.5*n*log(2.*M_PI);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  } 
  dvariable nllNormal2(const dvar_vector & x, const dvar_vector & mu, const dvariable & tau)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll = -0.5*n*log(tau+EPS)+0.5*tau*norm2(x-mu)+0.5*n*log(2.*M_PI);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  } 

  /** nll for normal(mu,tau) for many samples, each has its own mean, overload for random effect,
   * \f$ 0.5n\ln(2 \pi) + n\ln(\sigma) + 0.5\tau\sum(x_{i}-\mu_{i})^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param tau : precision, 1/variance   
   * \return return the nll for normal for many samples, each has own mean
   */	
  df1b2variable nllNormal2(const df1b2vector & x, const dvector & mu, const double tau)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x));
    nll = -0.5*n*log(tau+EPS)+0.5*tau*norm2(x-mu)+0.5*n*log(2.*M_PI);
    return nll;
  } 
  df1b2variable nllNormal2(const dvector & x, const df1b2vector & mu, const df1b2variable & tau)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x));
    nll = -0.5*n*log(tau+EPS)+0.5*tau*norm2(x-mu)+0.5*n*log(2.*M_PI);
    return nll;
  } 
  df1b2variable nllNormal2(const df1b2vector & x, const df1b2vector & mu, const df1b2variable & tau)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x));
    nll = -0.5*n*log(tau+EPS)+0.5*tau*norm2(x-mu)+0.5*n*log(2.*M_PI);
    return nll;
  } 







  ////////////////////////////////////////////////////////////////////////////////////////////
  //
  //                                    Binomial
  //
  ///////////////////////////////////////////////////////////////////////////////////////////

  /** nll for binomial for one sample
   * \f$ \ln(x!) + \ln((n-x)!) -\ln(n!)  - x \ln(p) - (n-x) \ln(1-p)  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param n : number of trials
   * \param p : probability
   * \return return the nll for binomial for one samples
   */	 
  double nllBinomial(const double x, const double n,const double p)
  {		
    double nll=0;
    nll=-x*log(p+EPS)-(n-x)*log(1.-p+EPS)-log_comb(n,x); //full likelihood, can drop the last term
    return nll;
  }
  dvariable nllBinomial(const dvariable & x, const double n,const double p)
  {		
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    nll=-x*log(p+EPS)-(n-x)*log(1.-p+EPS)-log_comb(n,x); //full likelihood, can drop the last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllBinomial(const double x, const dvariable & n,const dvariable & p)
  {		
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    nll=-x*log(p+EPS)-(n-x)*log(1.-p+EPS)-log_comb(n,x); //full likelihood, can drop the last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllBinomial(const dvariable & x, const dvariable & n,const dvariable & p)
  {		
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    nll=-x*log(p+EPS)-(n-x)*log(1.-p+EPS)-log_comb(n,x); //full likelihood, can drop the last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for binomial for one sample for random effect
   * \f$ \ln(x!) + \ln((n-x)!) -\ln(n!)  - x \ln(p) - (n-x) \ln(1-p)  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param n : number of trials
   * \param p : probability
   * \return return the nll for binomial for one samples
   */	 
  df1b2variable nllBinomial(const df1b2variable & x, const double n,const double p)
  {		
    df1b2variable nll=.0;
    nll=-x*log(p+EPS)-(n-x)*log(1.-p+EPS)-log_comb(n,x); //full likelihood, can drop the last term
    return nll;
  }
  df1b2variable nllBinomial(const double x, const df1b2variable & n,const df1b2variable & p)
  {		
    df1b2variable nll=.0;
    nll=-x*log(p+EPS)-(n-x)*log(1.-p+EPS)-log_comb(n,x); //full likelihood, can drop the last term
    return nll;
  }
  df1b2variable nllBinomial(const df1b2variable & x, const df1b2variable & n,const df1b2variable & p)
  {		
    df1b2variable nll=.0;
    nll=-x*log(p+EPS)-(n-x)*log(1.-p+EPS)-log_comb(n,x); //full likelihood, can drop the last term
    return nll;
  }




  /** nll for binomial for many samples
   * \f$ -\sum\ln{{n_{i}}\choose{x_{i}}}- \sum(x_{i})\ln(p)- \sum(n_{i}-x_{i})\ln(1-p)  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param n : number of trials
   * \param p : probability
   * \return return the nll for binomial for many samples
   */	 
  dvariable nllBinomial(const dvar_vector & x, const dvector & n,const double p)
  {		
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    nll=-sum(x)*log(p+EPS)-sum(n-x)*log(1.-p+EPS)-sum(log_comb(n,x)); //full likelihood, can drop the last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllBinomial(const dvector & x, const dvar_vector & n,const dvariable & p)
  {		
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    nll=-sum(x)*log(p+EPS)-sum(n-x)*log(1.-p+EPS)-sum(log_comb(n,x)); //full likelihood, can drop the last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllBinomial(const dvar_vector & x, const dvar_vector & n,const dvariable & p)
  {		
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    nll=-sum(x)*log(p+EPS)-sum(n-x)*log(1.-p+EPS)-sum(log_comb(n,x)); //full likelihood, can drop the last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for binomial for many samples for random effect
   * \f$ -\sum\ln{{n_{i}}\choose{x_{i}}}- \sum(x_{i})\ln(p)- \sum(n_{i}-x_{i})\ln(1-p)  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param n : number of trials
   * \param p : probability
   * \return return the nll for binomial for many samples
   */
  df1b2variable nllBinomial(const dvector & x, const df1b2vector & n,const df1b2variable & p)
  {		
    df1b2variable nll=.0;
    nll=-sum(x)*log(p+EPS)-sum(n-x)*log(1.-p+EPS)-sum(log_comb(n,x)); //full likelihood, can drop the last term
    return nll;
  }
  df1b2variable nllBinomial(const df1b2vector & x, const dvector & n,const double p)
  {		
    df1b2variable nll=.0;
    nll=-sum(x)*log(p+EPS)-sum(n-x)*log(1.-p+EPS)-sum(log_comb(n,x)); //full likelihood, can drop the last term
    return nll;
  }
  df1b2variable nllBinomial(const df1b2vector & x, const df1b2vector & n,const df1b2variable & p)
  {		
    df1b2variable nll=.0;
    nll=-sum(x)*log(p+EPS)-sum(n-x)*log(1.-p+EPS)-sum(log_comb(n,x)); //full likelihood, can drop the last term
    return nll;
  }








  ////////////////////////////////////////////////////////////////////////////////////////////
  //
  //                                    Lognormal
  //
  ///////////////////////////////////////////////////////////////////////////////////////////

  /** nll for lognormal for one sample
   * \f$ 0.5\ln(2 \pi) + \ln(x) +\ln(\sigma) + 0.5(\frac{\ln(x)-\mu}{\sigma})^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \return return the nll for lognormal for one sample
   */	
  double nllLognormal(const double x, const double mu, const double sigma)
  {	
    double nll=0; 		
    nll=log(sigma*sqrt(2.*M_PI)+EPS)+log(x+EPS)+0.5*square((log(x+EPS)-mu)/(sigma+EPS));//full likelihood
    return nll;
  }
  dvariable nllLognormal(const dvariable& x, const double mu, const double sigma)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 		
    nll=log(sigma*sqrt(2.*M_PI)+EPS)+log(x+EPS)+0.5*square((log(x+EPS)-mu)/(sigma+EPS));//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllLognormal(const double x, const dvariable & mu, const dvariable & sigma)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 		
    nll=log(sigma*sqrt(2.*M_PI)+EPS)+log(x+EPS)+0.5*square((log(x+EPS)-mu)/(sigma+EPS));//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllLognormal(const dvariable & x, const dvariable & mu, const double sigma)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 		
    nll=log(sigma*sqrt(2.*M_PI)+EPS)+log(x+EPS)+0.5*square((log(x+EPS)-mu)/(sigma+EPS));//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllLognormal(const dvariable & x, const double mu, const dvariable & sigma)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 		
    nll=log(sigma*sqrt(2.*M_PI)+EPS)+log(x+EPS)+0.5*square((log(x+EPS)-mu)/(sigma+EPS));//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllLognormal(const dvariable & x, const dvariable & mu, const dvariable & sigma)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 		
    nll=log(sigma*sqrt(2.*M_PI)+EPS)+log(x+EPS)+0.5*square((log(x+EPS)-mu)/(sigma+EPS));//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for lognormal for one sample for random effect
   * \f$ 0.5\ln(2 \pi) + \ln(x) +\ln(\sigma) + 0.5(\frac{\ln(x)-\mu}{\sigma})^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \return return the nll for lognormal for one sample
   */	
  df1b2variable nllLognormal(const df1b2variable & x, const double mu, const double sigma)
  {	
    df1b2variable nll=.0; 		
    nll=log(sigma*sqrt(2.*M_PI)+EPS)+log(x+EPS)+0.5*square((log(x+EPS)-mu)/(sigma+EPS));//full likelihood
    return nll;
  }
  df1b2variable nllLognormal(const double x, const df1b2variable & mu, const df1b2variable & sigma)
  {	
    df1b2variable nll=.0; 		
    nll=log(sigma*sqrt(2.*M_PI)+EPS)+log(x+EPS)+0.5*square((log(x+EPS)-mu)/(sigma+EPS));//full likelihood
    return nll;
  }
  df1b2variable nllLognormal(const df1b2variable & x, const df1b2variable & mu, const double sigma)
  {	
    df1b2variable nll=.0; 		
    nll=log(sigma*sqrt(2.*M_PI)+EPS)+log(x+EPS)+0.5*square((log(x+EPS)-mu)/(sigma+EPS));//full likelihood
    return nll;
  }
  df1b2variable nllLognormal(const df1b2variable & x, const double mu, const df1b2variable & sigma)
  {	
    df1b2variable nll=.0; 		
    nll=log(sigma*sqrt(2.*M_PI)+EPS)+log(x+EPS)+0.5*square((log(x+EPS)-mu)/(sigma+EPS));//full likelihood
    return nll;
  }
  df1b2variable nllLognormal(const df1b2variable & x, const df1b2variable & mu, const df1b2variable & sigma)
  {	
    df1b2variable nll=.0; 		
    nll=log(sigma*sqrt(2.*M_PI)+EPS)+log(x+EPS)+0.5*square((log(x+EPS)-mu)/(sigma+EPS));//full likelihood
    return nll;
  }




  /** nll for lognormal for many samples
   * \f$ 0.5n\ln(2 \pi) + \sum\ln(x) +n\ln(\sigma) + 0.5\sum(\frac{\ln(x)-\mu}{\sigma})^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \return return the nll for lognormal for many samples
   */	
  dvariable nllLognormal(const dvar_vector & x, const double mu, const double sigma)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 	
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +sum(log(x+EPS))+0.5*norm2((log(x+EPS)-mu)/(sigma+EPS));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  
  dvariable nllLognormal(const dvector & x, const dvariable & mu, const dvariable & sigma)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 	
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +sum(log(x+EPS))+0.5*norm2((log(x+EPS)-mu)/(sigma+EPS));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  
  dvariable nllLognormal(const dvar_vector & x, const dvariable & mu, const dvariable & sigma)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 	
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +sum(log(x+EPS))+0.5*norm2((log(x+EPS)-mu)/(sigma+EPS));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  

  /** nll for lognormal for many samples for random effect
   * \f$ 0.5n\ln(2 \pi) + \sum\ln(x) +n\ln(\sigma) + 0.5\sum(\frac{\ln(x)-\mu}{\sigma})^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \return return the nll for lognormal for many samples
   */	
  df1b2variable nllLognormal(const df1b2vector & x, const double mu, const double sigma)
  {	
    df1b2variable nll=.0; 	
    double n=double(size_count(x));
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +sum(log(x+EPS))+0.5*norm2((log(x+EPS)-mu)/(sigma+EPS));
    return nll;
  }  
  df1b2variable nllLognormal(const dvector & x, const df1b2variable & mu, const df1b2variable & sigma)
  {	
    df1b2variable nll=.0; 	
    double n=double(size_count(x));
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +sum(log(x+EPS))+0.5*norm2((log(x+EPS)-mu)/(sigma+EPS));
    return nll;
  }  
  df1b2variable nllLognormal(const df1b2vector & x, const df1b2variable & mu, const df1b2variable & sigma)
  {	
    df1b2variable nll=.0; 	
    double n=double(size_count(x));
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +sum(log(x+EPS))+0.5*norm2((log(x+EPS)-mu)/(sigma+EPS));
    return nll;
  }  



  /** nll for lognormal for many samples, each has its mean
   * \f$ 0.5n\ln(2 \pi) + \sum\ln(x_{i}) +n\ln(\sigma) + 0.5\sum(\frac{\ln(x_{i})-\mu_{i}}{\sigma})^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \return return the nll for lognormal for many samples
   */	
  dvariable nllLognormal(const dvar_vector & x, const dvector & mu, const double sigma)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 	
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +sum(log(x+EPS))+0.5*norm2((log(x+EPS)-mu)/(sigma+EPS));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  
  dvariable nllLognormal(const dvector & x, const dvar_vector & mu, const dvariable & sigma)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 	
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +sum(log(x+EPS))+0.5*norm2((log(x+EPS)-mu)/(sigma+EPS));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  
  dvariable nllLognormal(const dvar_vector & x, const dvar_vector & mu, const dvariable & sigma)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 	
    double n=double(x.size());
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +sum(log(x+EPS))+0.5*norm2((log(x+EPS)-mu)/(sigma+EPS));
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  

  /** nll for lognormal for many samples, each has its mean, for random effect
   * \f$ 0.5n\ln(2 \pi) + \sum\ln(x_{i}) +n\ln(\sigma) + 0.5\sum(\frac{\ln(x_{i})-\mu_{i}}{\sigma})^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param sigma : std deviation parameter
   * \return return the nll for lognormal for many samples
   */	
  df1b2variable nllLognormal(const df1b2vector & x, const dvector & mu, const double sigma)
  {	
    df1b2variable nll=.0; 	
    double n=double(size_count(x));
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +sum(log(x+EPS))+0.5*norm2((log(x+EPS)-mu)/(sigma+EPS));
    return nll;
  }  
  df1b2variable nllLognormal(const dvector & x, const df1b2vector & mu, const df1b2variable & sigma)
  {	
    df1b2variable nll=.0; 	
    double n=double(size_count(x));
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +sum(log(x+EPS))+0.5*norm2((log(x+EPS)-mu)/(sigma+EPS));
    return nll;
  } 
  df1b2variable nllLognormal(const df1b2vector & x, const df1b2vector & mu, const df1b2variable & sigma)
  {	
    df1b2variable nll=.0; 	
    double n=double(size_count(x));
    nll=n*log(sigma*sqrt(2.*M_PI)+EPS) +sum(log(x+EPS))+0.5*norm2((log(x+EPS)-mu)/(sigma+EPS));
    return nll;
  } 






  ////////////////////////////////////////////////////////////////////////////////////////////
  //
  //                                    Lognormal with tau
  //
  ///////////////////////////////////////////////////////////////////////////////////////////

  /** nll for lognormal(mu,tau) for one sample
   * \f$ 0.5\ln(2 \pi) + \ln(x) -0.5\ln(\tau) + 0.5\tau(\ln(x)-\mu)^2  \f$
   * \ingroup QFC
   * \param x :  data  
   * \param mu : mean parameter
   * \param tau : precision parameter, 1/variance
   * \return return the nll for lognormal for one sample
   */	
  dvariable nllLognormal2(const double x, const dvariable & mu, const dvariable & tau)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 	
    nll= -0.5*log(tau+EPS)+log(x+EPS)+0.5*tau*square(log(x+EPS)-mu)+0.5*log(2.*M_PI);//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllLognormal2(const dvariable & x, const double mu, const double tau)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 	
    nll= -0.5*log(tau+EPS)+log(x+EPS)+0.5*tau*square(log(x+EPS)-mu)+0.5*log(2.*M_PI);//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllLognormal2(const dvariable & x, const dvariable & mu, const dvariable & tau)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 	
    nll= -0.5*log(tau+EPS)+log(x+EPS)+0.5*tau*square(log(x+EPS)-mu)+0.5*log(2.*M_PI);//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for lognormal(mu,tau) for one sample for random effect
   * \f$ 0.5\ln(2 \pi) + \ln(x) -0.5\ln(\tau) + 0.5\tau(\ln(x)-\mu)^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param tau : precision parameter, 1/variance
   * \return return the nll for lognormal for one sample
   */	
  df1b2variable nllLognormal2(const df1b2variable x, const double mu, const double tau)
  {	
    df1b2variable nll=.0; 	
    nll= -0.5*log(tau+EPS)+log(x+EPS)+0.5*tau*square(log(x+EPS)-mu)+0.5*log(2.*M_PI);//full likelihood
    return nll;
  }
  df1b2variable nllLognormal2(const double x, const df1b2variable & mu, const df1b2variable & tau)
  {	
    df1b2variable nll=.0; 	
    nll= -0.5*log(tau+EPS)+log(x+EPS)+0.5*tau*square(log(x+EPS)-mu)+0.5*log(2.*M_PI);//full likelihood
    return nll;
  }
  df1b2variable nllLognormal2(const df1b2variable x, const df1b2variable & mu, const double tau)
  {	
    df1b2variable nll=.0; 	
    nll= -0.5*log(tau+EPS)+log(x+EPS)+0.5*tau*square(log(x+EPS)-mu)+0.5*log(2.*M_PI);//full likelihood
    return nll;
  }
  df1b2variable nllLognormal2(const df1b2variable x, const double mu, const df1b2variable & tau)
  {	
    df1b2variable nll=.0; 	
    nll= -0.5*log(tau+EPS)+log(x+EPS)+0.5*tau*square(log(x+EPS)-mu)+0.5*log(2.*M_PI);//full likelihood
    return nll;
  }
  df1b2variable nllLognormal2(const df1b2variable x, const df1b2variable & mu, const df1b2variable & tau)
  {	
    df1b2variable nll=.0; 	
    nll= -0.5*log(tau+EPS)+log(x+EPS)+0.5*tau*square(log(x+EPS)-mu)+0.5*log(2.*M_PI);//full likelihood
    return nll;
  }




  /** nll for lognormal(mu,tau) for many samples
   * \f$ 0.5n\ln(2 \pi) + \sum\ln(x) -0.5n\ln(\tau) + 0.5\tau\sum(\ln(x)-\mu)^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param tau : precision parameter, 1/variance
   * \return return the nll for lognormal for many samples
   */	
  dvariable nllLognormal2(const dvar_vector & x, const double mu, const double tau)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    double n=double(x.size());
    nll=-0.5*n*log(tau+EPS)+sum(log(x+EPS))+0.5*tau*norm2(log(x+EPS)-mu)+0.5*n*log(2.*M_PI);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllLognormal2(const dvector & x, const dvariable & mu, const dvariable & tau)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    double n=double(x.size());
    nll=-0.5*n*log(tau+EPS)+sum(log(x+EPS))+0.5*tau*norm2(log(x+EPS)-mu)+0.5*n*log(2.*M_PI);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllLognormal2(const dvar_vector & x, const dvariable & mu, const dvariable & tau)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    double n=double(x.size());
    nll=-0.5*n*log(tau+EPS)+sum(log(x+EPS))+0.5*tau*norm2(log(x+EPS)-mu)+0.5*n*log(2.*M_PI);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for lognormal(mu,tau) for many samples for random effect
   * \f$ 0.5n\ln(2 \pi) + \sum\ln(x) -0.5n\ln(\tau) + 0.5\tau\sum(\ln(x)-\mu)^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param tau : precision parameter, 1/variance
   * \return return the nll for lognormal for many samples
   */	
  df1b2variable nllLognormal2(const dvector & x, const df1b2variable & mu, const df1b2variable & tau)
  {	
    df1b2variable nll=.0;
    double n=double(size_count(x)); 
    nll=-0.5*n*log(tau+EPS)+sum(log(x+EPS))+0.5*tau*norm2(log(x+EPS)-mu)+0.5*n*log(2.*M_PI);
    return nll;
  }
  df1b2variable nllLognormal2(const df1b2vector & x, const double mu, const double tau)
  {	
    df1b2variable nll=.0;
    double n=double(size_count(x)); 
    nll=-0.5*n*log(tau+EPS)+sum(log(x+EPS))+0.5*tau*norm2(log(x+EPS)-mu)+0.5*n*log(2.*M_PI);
    return nll;
  }
  df1b2variable nllLognormal2(const df1b2vector & x, const df1b2variable & mu, const double tau)
  {	
    df1b2variable nll=.0;
    double n=double(size_count(x)); 
    nll=-0.5*n*log(tau+EPS)+sum(log(x+EPS))+0.5*tau*norm2(log(x+EPS)-mu)+0.5*n*log(2.*M_PI);
    return nll;
  }
  df1b2variable nllLognormal2(const df1b2vector & x, const double mu, const df1b2variable & tau)
  {	
    df1b2variable nll=.0;
    double n=double(size_count(x)); 
    nll=-0.5*n*log(tau+EPS)+sum(log(x+EPS))+0.5*tau*norm2(log(x+EPS)-mu)+0.5*n*log(2.*M_PI);
    return nll;
  }
  df1b2variable nllLognormal2(const df1b2vector & x, const df1b2variable & mu, const df1b2variable & tau)
  {	
    df1b2variable nll=.0;
    double n=double(size_count(x)); 
    nll=-0.5*n*log(tau+EPS)+sum(log(x+EPS))+0.5*tau*norm2(log(x+EPS)-mu)+0.5*n*log(2.*M_PI);
    return nll;
  }




  /** nll for lognormal(mu,tau) for many samples, each has its mean
   * \f$ 0.5n\ln(2 \pi) + \sum\ln(x_{i}) -0.5n\ln(\tau) + 0.5\tau\sum(\ln(x_{i})-\mu_{i})^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param tau : precision parameter, 1/variance
   * \return return the nll for lognormal for many samples
   */	
  dvariable nllLognormal2(const dvar_vector & x, const dvector & mu, const double tau)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 	
    double n=double(x.size());
    nll=-0.5*n*log(tau+EPS)+sum(log(x+EPS))+0.5*tau*norm2(log(x+EPS)-mu)+0.5*n*log(2.*M_PI);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  
  dvariable nllLognormal2(const dvector & x, const dvar_vector & mu, const dvariable & tau)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 	
    double n=double(x.size());
    nll=-0.5*n*log(tau+EPS)+sum(log(x+EPS))+0.5*tau*norm2(log(x+EPS)-mu)+0.5*n*log(2.*M_PI);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  
  dvariable nllLognormal2(const dvar_vector & x, const dvar_vector & mu, const dvariable & tau)
  {	
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0; 	
    double n=double(x.size());
    nll=-0.5*n*log(tau+EPS)+sum(log(x+EPS))+0.5*tau*norm2(log(x+EPS)-mu)+0.5*n*log(2.*M_PI);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  

  /** nll for lognormal(mu,tau) for many samples, each has its mean, overload for random effect,
   * \f$ 0.5n\ln(2 \pi) + \sum\ln(x_{i}) -0.5n\ln(\tau) + 0.5\tau\sum(\ln(x_{i})-\mu_{i})^2  \f$
   * \ingroup QFC
   * \param x :  data   
   * \param mu : mean parameter
   * \param tau : precision parameter, 1/variance
   * \return return the nll for lognormal for many samples
   */	
  df1b2variable nllLognormal2(const df1b2vector & x, const dvector & mu, const double tau)
  {	
    df1b2variable nll=.0; 	
    double n=double(size_count(x));
    nll=-0.5*n*log(tau+EPS)+sum(log(x+EPS))+0.5*tau*norm2(log(x+EPS)-mu)+0.5*n*log(2.*M_PI);
    return nll;
  }  
  df1b2variable nllLognormal2(const dvector & x, const df1b2vector & mu, const df1b2variable & tau)
  {	
    df1b2variable nll=.0; 	
    double n=double(size_count(x));
    nll=-0.5*n*log(tau+EPS)+sum(log(x+EPS))+0.5*tau*norm2(log(x+EPS)-mu)+0.5*n*log(2.*M_PI);
    return nll;
  } 
  df1b2variable nllLognormal2(const df1b2vector & x, const df1b2vector & mu, const df1b2variable & tau)
  {	
    df1b2variable nll=.0; 	
    double n=double(size_count(x));
    nll=-0.5*n*log(tau+EPS)+sum(log(x+EPS))+0.5*tau*norm2(log(x+EPS)-mu)+0.5*n*log(2.*M_PI);
    return nll;
  } 







  ////////////////////////////////////////////////////////////////////////////////////////////
  //
  //                                    Poisson
  //
  ///////////////////////////////////////////////////////////////////////////////////////////

  /** nll for poisson for one sample
   * \f$  \lambda -x\ln(\lambda)+\ln(x!) \f$
   * \ingroup QFC
   * \param x :  data   
   * \param lambda : mean parameter
   * \return return the nll for poisson for one sample
   */	 
  double nllPoisson(const double x, const double lambda)
  {
    double nll=0;
    nll = lambda- x*log(lambda+EPS)+gammln(x+1.0);//full likelihood
    return nll;
  }
  dvariable nllPoisson(const dvariable & x, const double lambda)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    nll = lambda- x*log(lambda+EPS)+gammln(x+1.0);//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllPoisson(const double x, const dvariable & lambda)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    nll = lambda- x*log(lambda+EPS)+gammln(x+1.0);//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllPoisson(const dvariable & x, const dvariable & lambda)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    nll = lambda- x*log(lambda+EPS)+gammln(x+1.0);//full likelihood
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for poisson for one sample for random effect
   * \f$  \lambda -x\ln(\lambda)+\ln(x!) \f$
   * \ingroup QFC
   * \param x :  data   
   * \param lambda : mean parameter
   * \return return the nll for poisson for one sample
   */	 
  df1b2variable nllPoisson(const df1b2variable & x, const double lambda)
  {
    df1b2variable nll=.0;
    nll = lambda- x*log(lambda+EPS)+gammln(x+1.0);//full likelihood
    return nll;
  }
  df1b2variable nllPoisson(const double x, const df1b2variable & lambda)
  {
    df1b2variable nll=.0;
    nll = lambda- x*log(lambda+EPS)+gammln(x+1.0);//full likelihood
    return nll;
  }
  df1b2variable nllPoisson(const df1b2variable & x, const df1b2variable & lambda)
  {
    df1b2variable nll=.0;
    nll = lambda- x*log(lambda+EPS)+gammln(x+1.0);//full likelihood
    return nll;
  }



  /** nll for poisson for many samples
   * \f$  n\lambda -\sum(x)\ln(\lambda)+\sum(\ln(x!)) \f$
   * \ingroup QFC
   * \param x :  data   
   * \param lambda : mean parameter
   * \return return the nll for poisson for many samples
   */	 
  dvariable nllPoisson(const dvar_vector & x, const double lambda)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    double n=double(x.size());
    nll = n*lambda- sum(x)*log(lambda+EPS)+sum(gammln(x+1.0));//full likelihood, can drop the last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  
  dvariable nllPoisson(const dvector & x, const dvariable & lambda)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    double n=double(x.size());
    nll = n*lambda- sum(x)*log(lambda+EPS)+sum(gammln(x+1.0));//full likelihood, can drop the last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  
  dvariable nllPoisson(const dvar_vector & x, const dvariable & lambda)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;
    double n=double(x.size());
    nll = n*lambda- sum(x)*log(lambda+EPS)+sum(gammln(x+1.0));//full likelihood, can drop the last term
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }  

  /** nll for poisson for many samples for random effect
   * \f$  n\lambda -\sum(x)\ln(\lambda)+\sum(\ln(x!)) \f$
   * \ingroup QFC
   * \param x :  data   
   * \param lambda : mean parameter
   * \return return the nll for poisson for many samples
   */	 
  df1b2variable nllPoisson(const dvector & x, const df1b2variable & lambda)
  {
    df1b2variable nll=.0;
    double n=double(size_count(x)); 
    nll = n*lambda- sum(x)*log(lambda+EPS)+sum(gammln(x+1.0));//full likelihood, can drop the last term
    return nll;
  }  
  df1b2variable nllPoisson(const df1b2vector & x, const double lambda)
  {
    df1b2variable nll=.0;
    double n=double(size_count(x)); 
    nll = n*lambda- sum(x)*log(lambda+EPS)+sum(gammln(x+1.0));//full likelihood, can drop the last term
    return nll;
  }  
  df1b2variable nllPoisson(const df1b2vector & x, const df1b2variable & lambda)
  {
    df1b2variable nll=.0;
    double n=double(size_count(x)); 
    nll = n*lambda- sum(x)*log(lambda+EPS)+sum(gammln(x+1.0));//full likelihood, can drop the last term
    return nll;
  }  






  ////////////////////////////////////////////////////////////////////////////////////////////
  //
  //                                    Inverse Gamma
  //
  ///////////////////////////////////////////////////////////////////////////////////////////

  /** nll for inverse gamma for one sample
   * \f$ -a \ln(b) + \ln(\Gamma(a)) - (a-1)\ln(x)+ b/x   \f$
   * \ingroup QFC
   * \param x :  data   
   * \param a : alpha parameter,>0
   * \param b : beta parameter,>0
   * \return return the nll for inverse gamma for one sample
   */	
  double nllInverseGamma(const double x, const double a, const double b)
  {
    double nll=0;  
    nll= - a*log(b)+gammln(a)  -(a-1.)*log(x+EPS) + b/(x+EPS);
    return nll;
  }
  dvariable nllInverseGamma(const dvariable & x, const double a, const double b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll= - a*log(b)+gammln(a)  -(a-1.)*log(x+EPS) + b/(x+EPS);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllInverseGamma(const double x, const dvariable & a, const dvariable & b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll= - a*log(b)+gammln(a)  -(a-1.)*log(x+EPS) + b/(x+EPS);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllInverseGamma(const dvariable & x, const dvariable & a, const dvariable & b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    nll= - a*log(b)+gammln(a)  -(a-1.)*log(x+EPS) + b/(x+EPS);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for inverse gamma for one sample for random effect
   * \f$ -a \ln(b) + \ln(\Gamma(a)) - (a-1)\ln(x)+ b/x   \f$
   * \ingroup QFC
   * \param x :  data   
   * \param a : alpha parameter,>0
   * \param b : beta parameter,>0
   * \return return the nll for inverse gamma for one sample
   */	
  df1b2variable nllInverseGamma(const df1b2variable & x, const double a, const double b)
  {
    df1b2variable nll=.0;  
    nll= - a*log(b)+gammln(a)  -(a-1.)*log(x+EPS) + b/(x+EPS);
    return nll;
  }
  df1b2variable nllInverseGamma(const double x, const df1b2variable & a, const df1b2variable & b)
  {
    df1b2variable nll=.0;  
    nll= - a*log(b)+gammln(a)  -(a-1.)*log(x+EPS) + b/(x+EPS);
    return nll;
  }
  df1b2variable nllInverseGamma(const df1b2variable & x, const df1b2variable & a, const double b)
  {
    df1b2variable nll=.0;  
    nll= - a*log(b)+gammln(a)  -(a-1.)*log(x+EPS) + b/(x+EPS);
    return nll;
  }
  df1b2variable nllInverseGamma(const df1b2variable & x, const double a, const df1b2variable & b)
  {
    df1b2variable nll=.0;  
    nll= - a*log(b)+gammln(a)  -(a-1.)*log(x+EPS) + b/(x+EPS);
    return nll;
  }
  df1b2variable nllInverseGamma(const df1b2variable & x, const df1b2variable & a, const df1b2variable & b)
  {
    df1b2variable nll=.0;  
    nll= - a*log(b)+gammln(a)  -(a-1.)*log(x+EPS) + b/(x+EPS);
    return nll;
  }




  /** nll for inverse gamma for many samples
   * \f$ -na \ln(b) + n\ln(\Gamma(a)) - (a-1)\sum(\ln(x))+ b/\sum(x)   \f$
   * \ingroup QFC
   * \param x :  data   
   * \param a : alpha parameter,>0
   * \param b : beta parameter,>0
   * \return return the nll for inverse gamma for many samples
   */	
  dvariable nllInverseGamma(const dvar_vector & x, const double a, const double b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll= - n*a*log(b)+ n*gammln(a)  -(a-1.)*sum(log(x+EPS)) + b/sum(x+EPS);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllInverseGamma(const dvector & x, const dvariable & a, const dvariable & b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll= - n*a*log(b)+ n*gammln(a)  -(a-1.)*sum(log(x+EPS)) + b/sum(x+EPS);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }
  dvariable nllInverseGamma(const dvar_vector & x, const dvariable & a, const dvariable & b)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable nll=0;  
    double n=double(x.size());
    nll= - n*a*log(b)+ n*gammln(a)  -(a-1.)*sum(log(x+EPS)) + b/sum(x+EPS);
    RETURN_ARRAYS_DECREMENT();
    return nll;
  }

  /** nll for inverse gamma for many samples for random effect
   * \f$ -na \ln(b) + n\ln(\Gamma(a)) - (a-1)\sum(\ln(x))+ b/\sum(x)   \f$
   * \ingroup QFC
   * \param x :  data   
   * \param a : alpha parameter,>0
   * \param b : beta parameter,>0
   * \return return the nll for inverse gamma for many samples
   */	
  df1b2variable nllInverseGamma(const dvector & x, const df1b2variable & a, const df1b2variable & b)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x)); 
    nll= - n*a*log(b)+ n*gammln(a)  -(a-1.)*sum(log(x+EPS)) + b/sum(x+EPS);
    return nll;
  }
  df1b2variable nllInverseGamma(const df1b2vector & x, const double a, const double b)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x)); 
    nll= - n*a*log(b)+ n*gammln(a)  -(a-1.)*sum(log(x+EPS)) + b/sum(x+EPS);
    return nll;
  }
  df1b2variable nllInverseGamma(const df1b2vector & x, const df1b2variable & a, const df1b2variable & b)
  {
    df1b2variable nll=.0;  
    double n=double(size_count(x)); 
    nll= - n*a*log(b)+ n*gammln(a)  -(a-1.)*sum(log(x+EPS)) + b/sum(x+EPS);
    return nll;
  }

  #endif