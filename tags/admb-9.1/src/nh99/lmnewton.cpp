
/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California
 */

#include <admodel.h>

#ifdef __cplusplus
extern "C" {
#endif
  int lbfgs_(long int *, long int *, double *, 
	    double *, double *, long int *, double *, long int *, 
	    double *, double *, double *, long int *,long int *,
            long int *);
#ifdef __cplusplus
	}
#endif

 //char cc[43]={"Copyright (c) 2008 Regents of the University of California"};


void function_minimizer::limited_memory_quasi_newton
  (BOR_CONST independent_variables& _x,int m)
{
  independent_variables& x = (independent_variables&) _x;
  if (m<=0)
  {
    cerr << "illegal value for number of steps in limited memory"
      " quasi-newton method -- set equal to 10" << endl;
  }
  int noprintx=0;
  int on;
  int maxfn_option=0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-maxfn"))>-1)
  {
    maxfn_option=1;
  }
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-nox"))>-1)
  {
    noprintx=1;
  }
  int nvar=initial_params::nvarcalc(); // get the number of active
  double _crit=0;
  int itn=0;
  int ifn=0;
  int nopt;
  // set the convergence criterion by command line
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-crit",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -crit option needs number  -- ignored" << endl;
    }
    else
    {   
      char * end;
      _crit=strtod(ad_comm::argv[on+1],&end);
      if (_crit<=0)
      {
        cerr << "Usage -crit option needs positive number  -- ignored" << endl;
        _crit=0.0;
      } 
    }
  }

  gradient_structure::set_YES_DERIVATIVES();
  // set convergence criterion for this phase
  if (!(!convergence_criteria))
  {
    int ind=min(convergence_criteria.indexmax(),
    initial_params::current_phase);
    crit=convergence_criteria(ind);
  }
  if (_crit)
  {
    crit = _crit;
  } 
  if (!(!maximum_function_evaluations) && !maxfn_option)
  {
    int ind=min(maximum_function_evaluations.indexmax(),
      initial_params::current_phase);
    maxfn= (int) maximum_function_evaluations(ind);
  }
  dvariable vf=0.0;

  double xtol, f;
  dvector diag(1,nvar);
  int j, n, iflag, icall;
  double fbest=1.e+100;
  dvector g(1,nvar);
  g.initialize();
  dvector xbest(1,nvar);
  dvector gbest(1,nvar);
  double t1, t2;
  long int diagco=0.0;
  int iprintx[2];
  double epsx;
  //m = 35;
  dvector w(1,nvar+2*m+2*nvar*m);
  nopt=0;
  int on1;
  if ( (on1=option_match(ad_comm::argc,ad_comm::argv,"-iprint",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -iprint option needs integer  -- ignored" << endl;
    }
    else
    {   
      int jj=atoi(ad_comm::argv[on1+1]);
      iprint=jj;
    }
  }
  iprintx[0] = iprint;
  iprintx[1] = 0;
  crit = 1e-5;
  xtol = 1e-16;
  icall = 0;
  iflag = 0;

L20:
  f = 0.;
  vf=initial_params::reset(dvar_vector(x));
  *objective_function_value::pobjfun=0.0;
  userfunction();
  vf+=*objective_function_value::pobjfun;
  f=value(vf);
  ifn++;
  if (f<fbest)
  {
    fbest=f;
    xbest=x;
    gbest=g;
  }
  
  gradcalc(nvar,g);
  if(fmod(double(itn),double(iprint)) == 0)
  {
    if (iprint>0)
    {
      if (!itn)
        if (ad_printf) (*ad_printf)("\nInitial statistics: ");
      else
        if (ad_printf) (*ad_printf)("\nIntermediate statistics: ");

      if (ad_printf) (*ad_printf)("%d variables; iteration %ld; function evaluation %ld\n",
        nvar, itn, ifn);

      if (!itn)
      {
        if (ad_printf) (*ad_printf)("Function value %12.4le; maximum gradient component mag %12.4le\n",
          f, max(fabs(g)));
      }
      else
      {

        if (ad_printf) (*ad_printf)("Function value %12.4le; maximum gradient component mag %12.4le\n",
          fbest, max(gbest));
      }
      if (!noprintx)
      {
        if (!itn)
          fmmdisp(x, g, nvar, 0,noprintx);
	else
          fmmdisp(xbest, gbest, nvar, 0,noprintx);
      }
    }
  }
  
  long int lnvar=nvar;
  long int litn=itn;
  long int liprintx= *iprintx;
  long int liflag=iflag;
  long int lm=m;
  long int linfo=0;
  lbfgs_(&lnvar, &lm, &(x[1]) , &f, &(g[1]), &diagco, &(diag[1]),
    &liprintx, &crit, &xtol, &(w[1]), &liflag,&litn,&linfo);
  itn=int(litn);
  iflag=int(liflag);

  if (iflag <= 0)
  {
    goto L50;
  }
  ++icall;
  if (icall > maxfn)
  {
    goto L50;
  }
  goto L20;
L50:
  if (iprint>0)
  {
    if (ad_printf) (*ad_printf)("\nfinal statistics: ");

    if (ad_printf) (*ad_printf)("%d variables; iteration %ld; function evaluation %ld\n",
      nvar, itn, ifn);
    if (ad_printf) (*ad_printf)("Function value %12.4le; maximum gradient component mag %12.4le\n",
      f, max(g));
    fmmdisp(x, g, nvar, 0,noprintx);
  }
  gradient_structure::set_NO_DERIVATIVES();
  x=xbest;
  objective_function_value::gmax=fabs(max(gbest));
}

void function_minimizer::limited_memory_quasi_newton
  (double& f,BOR_CONST independent_variables& _x,int m,int noprintx,
  int maxfn,double crit)
{
  independent_variables& x = (independent_variables&) _x;
  if (m<=0)
  {
    cerr << "illegal value for number of steps in limited memory"
      " quasi-newton method -- set equal to 10" << endl;
  }
  int on;

  int nvar=initial_params::nvarcalc(); // get the number of active
  double _crit=0;
  int itn=0;
  int ifn=0;
  int nopt;
  // set the convergence criterion by command line
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-crit",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -crit option needs number  -- ignored" << endl;
    }
    else
    {   
      char * end;
      _crit=strtod(ad_comm::argv[on+1],&end);
      if (_crit<=0)
      {
        cerr << "Usage -crit option needs positive number  -- ignored" << endl;
        _crit=0.0;
      } 
    }
  }
  gradient_structure::set_YES_DERIVATIVES();
  dvariable vf=0.0;

  double xtol;
  dvector diag(1,nvar);
  int j, n, iflag, icall;
  double fbest=1.e+100;
  dvector g(1,nvar);
  g.initialize();
  dvector xbest(1,nvar);
  dvector gbest(1,nvar);
  double t1, t2;
  long int diagco=0;
  int iprintx[2];
  double epsx;
  //m = 35;
  dvector w(1,nvar+2*m+2*nvar*m);
  iprintx[0] = iprint;
  iprintx[1] = 0;
  crit = 1e-5;
  xtol = 1e-16;
  icall = 0;
  iflag = 0;

L20:
  f = 0.;
  vf=initial_params::reset(dvar_vector(x));
  *objective_function_value::pobjfun=0.0;
  userfunction();
  vf+=*objective_function_value::pobjfun;
  f=value(vf);
  ifn++;
  if (f<fbest)
  {
    fbest=f;
    xbest=x;
    gbest=g;
  }
  
  gradcalc(nvar,g);
  if(fmod(double(itn),double(iprint)) == 0)
  {
    if (iprint>0)
    {
      if (!itn)
        if (ad_printf) (*ad_printf)("\nInitial statistics: ");
      else
        if (ad_printf) (*ad_printf)("\nIntermediate statistics: ");

      if (ad_printf) (*ad_printf)("%d variables; iteration %ld; function evaluation %ld\n",
        nvar, itn, ifn);

      if (!itn)
      {
        if (ad_printf) (*ad_printf)("Function value %12.4le; maximum gradient component mag %12.4le\n",
          f, max(g));
      }
      else
      {

        if (ad_printf) (*ad_printf)("Function value %12.4le; maximum gradient component mag %12.4le\n",
          fbest, max(gbest));
      }
      if (!noprintx)
      {
        if (!itn)
          fmmdisp(x, g, nvar, 0,noprintx);
	else
          fmmdisp(xbest, gbest, nvar, 0,noprintx);
      }
    }
  }
  long int lnvar=nvar;
  long int litn=itn;
  long int liprintx= *iprintx;
  long int liflag=iflag;
  long int lm=m;
  long int linfo=0;
  lbfgs_(&lnvar, &lm, &(x[1]) , &f, &(g[1]), &diagco, &(diag[1]),
    &liprintx, &crit, &xtol, &(w[1]), &liflag,&litn,&linfo);
  itn=int(litn);
  iflag=int(liflag);

  if (iflag <= 0)
  {
    goto L50;
  }
  ++icall;
  if (icall > maxfn)
  {
    goto L50;
  }
  goto L20;
L50:
  if (iprint>0)
  {
    if (ad_printf) (*ad_printf)("\nfinal statistics: ");

    if (ad_printf) (*ad_printf)("%d variables; iteration %ld; function evaluation %ld\n",
      nvar, itn, ifn);
    if (ad_printf) (*ad_printf)("Function value %12.4le; maximum gradient component mag %12.4le\n",
      f, max(g));
    fmmdisp(x, g, nvar, 0,noprintx);
  }
  //gradient_structure::set_NO_DERIVATIVES();
  x=xbest;
  f=fbest;
  objective_function_value::gmax=fabs(max(gbest));
}

