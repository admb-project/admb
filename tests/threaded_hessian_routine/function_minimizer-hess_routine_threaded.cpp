/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#if defined(USE_LAPLACE)
#  include <df1b2fun.h>
#else
#  include <admodel.h>
#endif

void hess_calcreport(int i,int nvar);
void hess_errorreport(void);
void set_labels_for_hess(int);

// estimate the matrix of second derivatives
void ad_update_hess_stats_report(int i,int nvar);

void function_minimizer::hess_routine_threaded(void)
{

  int nvar=initial_params::nvarcalc(); // get the number of active parameters
  //if (adjm_ptr) set_labels_for_hess(nvar);
  independent_variables x(1,nvar);
  initial_params::xinit(x);        // get the initial values into the x vector
  double f;
  double delta=1.e-5;
  dvector g1(1,nvar);
  dvector g2(1,nvar);
  dvector gbest(1,nvar);
  dvector hess(1,nvar);
  dvector hess1(1,nvar);
  dvector hess2(1,nvar);
  double eps=.1;
  gradient_structure::set_YES_DERIVATIVES();
  gbest.fill_seqadd(1.e+50,0.);

/*
  adstring tmpstring="admodel.hes-threaded";
  if (ad_comm::wd_flag)
     tmpstring = ad_comm::adprogram_name + ".hes-threaded";
  uostream ofs((char*)tmpstring);

  ofs << nvar;
*/
      dvariable vf;
if (true) return;
  {
    {
      dvariable vf=0.0;
if (true) return;
      vf=initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      pre_userfunction();
      vf+=*objective_function_value::pobjfun;
      f=value(vf);
      gradcalc(nvar,g1);
    }
    double sdelta1;
    double sdelta2;
    for (int i=1;i<=nvar;i++)
    {
#if defined (__SPDLL__)
      hess_calcreport(i,nvar);
#else
      cout << "Estimating row " << i << " out of " << nvar
	   << " for hessian" << endl;
#endif

      double f=0.0;
      double xsave=x(i);
      sdelta1=x(i)+delta;
      sdelta1-=x(i);
      x(i)=xsave+sdelta1;
      dvariable vf=0.0;
      vf=initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      pre_userfunction();
      vf+=*objective_function_value::pobjfun;
      f=value(vf);
      gradcalc(nvar,g1);

      sdelta2=x(i)-delta;
      sdelta2-=x(i);
      x(i)=xsave+sdelta2;
      vf=0.0;
      vf=initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      pre_userfunction();
      vf+=*objective_function_value::pobjfun;
      f=value(vf);
      gradcalc(nvar,g2);
      x(i)=xsave;
      hess1=(g1-g2)/(sdelta1-sdelta2);

      sdelta1=x(i)+eps*delta;
      sdelta1-=x(i);
      x(i)=xsave+sdelta1;
      vf=0.0;
      vf=initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      pre_userfunction();
      vf+=*objective_function_value::pobjfun;
      f=value(vf);
      gradcalc(nvar,g1);

      x(i)=xsave-eps*delta;
      sdelta2=x(i)-eps*delta;
      sdelta2-=x(i);
      x(i)=xsave+sdelta2;
      vf=0.0;
      vf=0.0;
      vf=initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      pre_userfunction();
      vf+=*objective_function_value::pobjfun;
      f=value(vf);
      gradcalc(nvar,g2);
      x(i)=xsave;

      vf=initial_params::reset(dvar_vector(x));
      double eps2=eps*eps;
      hess2=(g1-g2)/(sdelta1-sdelta2);
      hess=(eps2*hess1-hess2) /(eps2-1.);

/*
      ofs << hess;
      //if (adjm_ptr) ad_update_hess_stats_report(nvar,i);
*/
    }
  }
/*
  ofs << gradient_structure::Hybrid_bounded_flag;
  dvector tscale(1,nvar);   // need to get scale from somewhere
  initial_params::stddev_scale(tscale,x);
  ofs << tscale;
*/
}
