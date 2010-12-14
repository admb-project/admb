/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <admodel.h>

#ifdef __GNUDOS__
  #include <gccmanip.h>
#endif

void useless(BOR_CONST double& sdelta2);
// estimate the matrix of second derivatives

dmatrix function_minimizer::dep_hess_routine(BOR_CONST dvariable& dep)
{
  int nvar=initial_params::nvarcalc(); // get the number of active parameters
  independent_variables x(1,nvar);
  initial_params::xinit(x);        // get the initial values into the x vector
  dvector scale(1,nvar);   // need to get scale from somewhere
  dvector tscale(1,nvar);   // need to get scale from somewhere
  int check=initial_params::stddev_scale(scale,x);
  //check=initial_params::stddev_curvscale(curv,x);
  double f;
  double delta=1.e-7;
  dvector g1(1,nvar);
  dvector depg(1,nvar);
  dvector g2(1,nvar);
  dvector gbest(1,nvar);
  dmatrix hess(1,nvar,1,nvar);
  dvector hess1(1,nvar);
  dvector hess2(1,nvar);
  double eps=.1;
  gradient_structure::set_YES_DERIVATIVES();
  gbest.fill_seqadd(1.e+50,0.);
  {
    gradcalc(0,depg);
    dvariable vf=0.0;
    vf=initial_params::reset(dvar_vector(x));
    userfunction();
    vf=dep;
    f=value(vf);
    gradcalc(nvar,depg);
  }
  double sdelta1;
  double sdelta2;
  int i;
  for (i=1;i<=nvar;i++)
  {
    cout << "Estimating row " << i << " out of " << nvar
         << " for dependent variable hessian" << endl;

    double f=0.0;
    double xsave=x(i);
    sdelta1=x(i)+delta;
    useless(sdelta1);
    sdelta1-=x(i);
    x(i)=xsave+sdelta1;
    dvariable vf=0.0;
    check=initial_params::stddev_scale(tscale,x);
    gradcalc(0,depg);
    vf=initial_params::reset(dvar_vector(x));
    userfunction();
    vf=dep;
    f=value(vf);
    gradcalc(nvar,g1);
    g1=elem_div(g1,tscale);

    sdelta2=x(i)-delta;
    useless(sdelta2);
    sdelta2-=x(i);
    x(i)=xsave+sdelta2;
    check=initial_params::stddev_scale(tscale,x);
    //gradcalc(nvar,depg);
    vf=0.0;
    vf=initial_params::reset(dvar_vector(x));
    userfunction();
    vf=dep;
    f=value(vf);
    gradcalc(nvar,g2);
    g2=elem_div(g2,tscale);
    x(i)=xsave;
    hess1=(g1-g2)/(sdelta1-sdelta2)/scale(i);

    sdelta1=x(i)+eps*delta;
    useless(sdelta1);
    sdelta1-=x(i);
    x(i)=xsave+sdelta1;
    check=initial_params::stddev_scale(tscale,x);
    //gradcalc(nvar,depg);
    vf=0.0;
    vf=initial_params::reset(dvar_vector(x));
    userfunction();
    vf=dep;
    f=value(vf);
    gradcalc(nvar,g1);
    g1=elem_div(g1,tscale);

    x(i)=xsave-eps*delta;
    sdelta2=x(i)-eps*delta;
    useless(sdelta2);
    sdelta2-=x(i);
    x(i)=xsave+sdelta2;
    check=initial_params::stddev_scale(tscale,x);
    //gradcalc(nvar,depg);
    vf=0.0;
    vf=initial_params::reset(dvar_vector(x));
    userfunction();
    vf=dep;
    f=value(vf);
    gradcalc(nvar,g2);
    g2=elem_div(g2,tscale);
    x(i)=xsave;

    hess2=(g1-g2)/(sdelta1-sdelta2)/scale(i);
    double eps2=eps*eps;
    hess(i)=(eps2*hess1-hess2) /(eps2-1.);
  }
  /*
  for (i=1;i<=nvar;i++)
  {
    hess(i,i)/=(scale(i)*scale(i));
    for (int j=1;j<i;j++)
    {
      double tmp=(hess(i,j)+hess(j,i))/(2.*scale(i)*scale(j));
      hess(i,j)=tmp;
      hess(j,i)=tmp;
    }
    hess(i,i)-=depg(i)*curv(i)/(scale(i)*scale(i)*scale(i));
  }  
 */
  return hess;
}


