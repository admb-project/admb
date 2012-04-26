/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>
//#include <iomanip.h>
#ifdef __GNUDOS__
  #include <gccmanip.h>
#endif

void hess_calcreport(int i,int nvar);
void hess_errorreport(void);
void set_labels_for_hess(int);

class admb_javapointers;
extern admb_javapointers * adjm_ptr;
void useless(BOR_CONST double& sdelta2);
// estimate the matrix of second derivatives
void ad_update_hess_stats_report(int i,int nvar);

#if defined(USE_ADPVM)
void function_minimizer::hess_routine_master()
{

  int nvar=initial_params::nvarcalc(); // get the number of active parameters
  //if (adjm_ptr) set_labels_for_hess(nvar);
  independent_variables x(1,nvar);
  initial_params::xinit(x);        // get the initial values into the x vector
  double f;
  double delta=1.e-6;
  dvector g1(1,nvar);
  dvector g2(1,nvar);
  dvector gbest(1,nvar);
  dvector hess(1,nvar);
  dvector hess1(1,nvar);
  dvector hess2(1,nvar);
  double eps=.1;
  gradient_structure::set_YES_DERIVATIVES();
  gbest.fill_seqadd(1.e+50,0.);

  adstring tmpstring="admodel.hes";
  if (ad_comm::wd_flag)
     tmpstring = ad_comm::adprogram_name + ".hes";
  uostream ofs((char*)tmpstring);
    
  ofs << nvar;
  {
    pvm_master_function_evaluation(f,x,g1,nvar);
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
      useless(sdelta1);
      sdelta1-=x(i);
      x(i)=xsave+sdelta1;

      pvm_master_function_evaluation(f,x,g1,nvar);

      sdelta2=x(i)-delta;
      useless(sdelta2);
      sdelta2-=x(i);
      x(i)=xsave+sdelta2;

      pvm_master_function_evaluation(f,x,g2,nvar);

      x(i)=xsave;
      hess1=(g1-g2)/(sdelta1-sdelta2);
 
      sdelta1=x(i)+eps*delta;
      useless(sdelta1);
      sdelta1-=x(i);
      x(i)=xsave+sdelta1;

      pvm_master_function_evaluation(f,x,g1,nvar);

      x(i)=xsave-eps*delta;
      sdelta2=x(i)-eps*delta;
      useless(sdelta2);
      sdelta2-=x(i);
      x(i)=xsave+sdelta2;

      pvm_master_function_evaluation(f,x,g2,nvar);

      x(i)=xsave;

      dvariable vf=initial_params::reset(dvar_vector(x));
      double eps2=eps*eps;
      hess2=(g1-g2)/(sdelta1-sdelta2);
      hess=(eps2*hess1-hess2) /(eps2-1.);
   
      ofs << hess;
      //if (adjm_ptr) ad_update_hess_stats_report(nvar,i);
    }
  }
  gradient_structure::set_NO_DERIVATIVES();
}

void function_minimizer::hess_routine_slave()
{
  int nvar=initial_params::nvarcalc(); // get the number of active parameters
  gradient_structure::set_YES_DERIVATIVES();

  pvm_slave_function_evaluation();
  for (int i=1;i<=nvar;i++)
  {
    for (int it=1;it<=4;it++) pvm_slave_function_evaluation();
  }
  gradient_structure::set_NO_DERIVATIVES();
}
#endif // #if defined(USE_ADPVM)

