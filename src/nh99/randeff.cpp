/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

#if defined(max)
#  undef max
#endif

typedef int integer;
typedef long int logical;

#ifdef __cplusplus
extern "C" {
#endif

int xlbfgs_(integer *n, integer *m, dvar_vector & x, dvariable & f,
  dvar_vector & g, logical *diagco, dvar_vector & diag, integer *iprint,
  double*  eps, double*  xtol, dvar_vector & w, integer *iflag, integer* iter);

#ifdef __cplusplus
}
#endif

dvariable function_minimizer::random_effects_maximization(const dvar_vector& _x)
{
  integer m=5;
  double crit=0.0;
  //double crit=1.e-3;
  int maxfn=400;
  int maxiter=50;
  int iprint=-10;

  dvar_vector& x = (dvar_vector&)(_x);

  integer nvar=x.indexmax()-x.indexmin()+1; // get the number of active
  if (m<=0)
  {
    cerr << "illegal value for number of steps in limited memory"
      " quasi-newton method -- set equal to 10" << endl;
  }
  integer noprintx=0;
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
  double _crit=0;
  integer itn=0;
  int ifn=0;
  int nopt = 0;
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
  dvector convergence_criteria;
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
  dvector maximum_function_evaluations;
  if (!(!maximum_function_evaluations) && !maxfn_option)
  {
    int ind=min(maximum_function_evaluations.indexmax(),
      initial_params::current_phase);
    maxfn= (int) maximum_function_evaluations(ind);
  }
  dvariable vf=0.0;

  double xtol;
  dvariable f;
  dvar_vector diag(1,nvar);
  //int j, n, icall;
  int icall;
  integer iflag;
  dvariable fbest=1.e+100;
  dvar_vector g(1,nvar);
  dvar_vector xbest(1,nvar);
  dvar_vector gbest(1,nvar);
  g.initialize();
  //double t1, t2;
  long int diagco = 0;
  integer iprintx[2];
  //double epsx;
  //m = 35;
  dvar_vector w(1,nvar+2*m+2*nvar*m);
  iprintx[0] = iprint;
  iprintx[1] = 0;
  crit = 1e-5;
  xtol = 1e-16;
  icall = 0;
  iflag = 0;

L20:
  f = 0.;
  //vf=initial_params::reset(dvar_vector(x));
  f=user_randeff(x);
  ifn++;
  if (f<fbest)
  {
    fbest=f;
    xbest=x;
    gbest=g;
  }

  //gradcalc(nvar,g);
  g=user_dfrandeff(x);

#if defined(USE_DDOUBLE)
#undef double
  if(fmod(double(itn),double(iprint)) == 0)
#define double dd_real
#else
  if(fmod(double(itn),double(iprint)) == 0)
#endif
  {
    if (iprint>0)
    {
      if (!itn)
      {
        if (ad_printf) (*ad_printf)("\nInitial statistics: ");
      }
      else
      {
        if (ad_printf) (*ad_printf)("\nIntermediate statistics: ");
      }

      if (ad_printf)
        (*ad_printf)("%d variables; iteration %ld; function evaluation %ld\n",
        nvar, itn, ifn);

      if (!itn)
      {
        double xf=value(f);
        double xg=max(value(g));
        if (ad_printf)
          (*ad_printf)(
            "Function value %12.4le; maximum gradient component mag %12.4le\n",
            xf, xg);
      }
      else
      {
        double xf=value(fbest);
        double xg=max(value(gbest));
        if (ad_printf)
          (*ad_printf)(
            "Function value %12.4le; maximum gradient component mag %12.4le\n",
            xf, xg);
      }
      if (!noprintx)
      {
        if (!itn)
          fmmdisp(value(x), value(g), nvar, 0,noprintx);
        else
          fmmdisp(value(xbest), value(gbest), nvar, 0,noprintx);
      }
    }
  }
  crit=1.e-15;
  xlbfgs_(&nvar, &m, x , f, g, &diagco, diag,
    iprintx, &crit, &xtol, w, &iflag,&itn);

  if (iflag <= 0)
  {
    goto L50;
  }
  if (iflag > 1)
  {
    goto L50;
  }
  ++icall;
  if (icall > maxfn)
  if (itn > maxiter)
  {
    cout << "Exceeded maxiter" << endl;
    goto L50;
  }
  goto L20;
L50:
  if (f<fbest)
  {
    fbest=f;
    xbest=x;
    gbest=g;
  }
  if (iprint>0)
  {
    double xf=value(f);
    double xg=max(value(g));
    if (ad_printf)
    {
      (*ad_printf)("\nfinal statistics: ");
      (*ad_printf)("%d variables; iteration %ld; function evaluation %ld\n",
        nvar, itn, ifn);
      (*ad_printf)(
        "Function value %12.4le; maximum gradient component mag %12.4le\n",
        xf, xg);
    }
    fmmdisp(value(x),value(g), nvar, 0,noprintx);
  }
  //gradient_structure::set_NO_DERIVATIVES();
  //objective_function_value::gmax=fabs(max(value(gbest)));
  //user_d2frandeff(x);
  int sgn=1;
  dvar_matrix hess=symmetrize(user_d2frandeff(x));
  dvariable ld=ln_det(hess,sgn);
  if (sgn==-1)
  {
    dmatrix v=eigenvectors(value(hess));
    dvector e=eigenvalues(value(hess));
    cout << endl << e << endl;
    for (int i=e.indexmin();i<=e.indexmax();i++)
    {
      if (e(i)<0.0)
        cout << i << " " << v(i) << endl;
    }
  }
  x=xbest;
  return fbest+0.5*ln_det(user_d2frandeff(xbest),sgn);
}
