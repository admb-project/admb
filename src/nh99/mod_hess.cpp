/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <df1b2fun.h>
#include <admodel.h>
//#include <parallel.h>

void hess_calcreport(int i,int nvar);
void hess_errorreport(void);
void set_labels_for_hess(int);

// estimate the matrix of second derivatives
void ad_update_hess_stats_report(int i,int nvar);

void function_minimizer::hess_routine(void)
{
  if (random_effects_flag && lapprox != 0)
  {
    if (laplace_approximation_calculator::alternative_user_function_flag == 1)
    {
      laplace_approximation_calculator::alternative_user_function_flag = 2;
    }
    hess_routine_random_effects();
    if (laplace_approximation_calculator::alternative_user_function_flag == 2)
    {
      laplace_approximation_calculator::alternative_user_function_flag = 1;
    }
  }
#if defined(USE_ADPVM)
  else if (ad_comm::pvm_manager)
  {
    switch (ad_comm::pvm_manager->mode)
    {
    case 1: // master
      hess_routine_master();
      break;
    case 2: // slave
      hess_routine_slave();
      break;
    default:
      cerr << "Error: Illegal value for pvm_manager->mode." << endl;
      ad_exit(1);
    }
    cout << "finished hess routine" << endl;
  }
#endif
  else
  {
    hess_routine_noparallel();
  }
}
void function_minimizer::hess_routine_noparallel(void)
{
  int nvar=initial_params::nvarcalc(); // get the number of active parameters
  //if (adjm_ptr) set_labels_for_hess(nvar);
  independent_variables x(1,nvar);
  initial_params::xinit(x);        // get the initial values into the x vector
  double f = 0.0;
  double delta=1.e-5;
  dvector g1(1,nvar);
  dvector g2(1,nvar);
  dvector gbest(1,nvar);
  dvector hess(1,nvar);
  dvector hess1(1,nvar);
  dvector hess2(1,nvar);
  double eps=.1;
  double eps2=eps*eps;
  gradient_structure::set_YES_DERIVATIVES();
  gbest.fill_seqadd(1.e+50,0.);

  adstring tmpstring="admodel.hes";
  if (ad_comm::wd_flag)
     tmpstring = ad_comm::adprogram_name + ".hes";
  uostream ofs((char*)tmpstring);

  ofs << nvar;
  {
    {
      dvariable vf=0.0;
      vf=initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      pre_userfunction();
      vf+=*objective_function_value::pobjfun;
      f = value(vf);
      gradcalc(nvar, g1);
    }
    double sdelta1;
    double sdelta2;
    for (int i=1;i<=nvar;i++)
    {
      hess_calcreport(i,nvar);

      double xsave=x(i);
      sdelta1=x(i)+delta;
      sdelta1-=x(i);
      x(i)=xsave+sdelta1;
      dvariable vf=0.0;
      vf=initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      pre_userfunction();
      vf+=*objective_function_value::pobjfun;
      f = value(vf);
      gradcalc(nvar, g1);

      sdelta2=x(i)-delta;
      sdelta2-=x(i);
      x(i)=xsave+sdelta2;
      vf=0.0;
      vf=initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      pre_userfunction();
      vf+=*objective_function_value::pobjfun;
      f = value(vf);
      gradcalc(nvar, g2);
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
      f = value(vf);
      gradcalc(nvar, g1);

      x(i)=xsave-eps*delta;
      sdelta2=x(i)-eps*delta;
      sdelta2-=x(i);
      x(i)=xsave+sdelta2;
      vf=0.0;
      vf=initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      pre_userfunction();
      vf+=*objective_function_value::pobjfun;
      f = value(vf);
      gradcalc(nvar, g2);
      x(i)=xsave;

      hess2=(g1-g2)/(sdelta1-sdelta2);

      hess=(eps2*hess1-hess2) /(eps2-1.);

      ofs << hess;
      //if (adjm_ptr) ad_update_hess_stats_report(nvar,i);
    }
  }
  initial_params::reset(dvar_vector(x));
  ofs << gradient_structure::Hybrid_bounded_flag;
  dvector tscale(1,nvar);   // need to get scale from somewhere
  /*int check=*/initial_params::stddev_scale(tscale,x);
  ofs << tscale;
  // Write the MLE (bounded space) to file to be read in later by hybrid
  // methods. This is needed b/c the covar needs to be rescaled and the MLE
  // is needed for that.
  // Added by Cole; 4/2017
  ofs << -987; // unique flag to check for later
  dvector mle(1,nvar);
  initial_params::copy_all_values(mle,1);
  ofs << mle;
}

void function_minimizer::hess_routine_and_constraint(int iprof,
  const dvector& g, dvector& fg)
{
  int nvar=initial_params::nvarcalc(); // get the number of active parameters
  independent_variables x(1,nvar);
  initial_params::xinit(x);        // get the initial values into the x vector
  double f = 0.0;
  double delta=1.e-6;
  dvector g1(1,nvar);
  dvector g2(1,nvar);
  dvector gbest(1,nvar);
  dvector hess(1,nvar);
  dvector hess1(1,nvar);
  dvector hess2(1,nvar);
  //double eps=.1;
  gradient_structure::set_YES_DERIVATIVES();
  gbest.fill_seqadd(1.e+50,0.);
  uostream ofs("admodel.hes");
  //ofstream ofs5("tmphess");
  double lambda=fg*g/norm2(g);
  cout << fg-lambda*g << endl;
  cout << norm(fg-lambda*g) << " " << fg*g/(norm(g)*norm(fg)) << endl;
  ofs << nvar;
  {
    {
      dvariable vf=0.0;
      vf=initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      pre_userfunction();
      vf+=*objective_function_value::pobjfun;
      vf-=lambda*likeprof_params::likeprofptr[iprof]->variable();
      f = value(vf);
      gradcalc(nvar, g1);
    }
    double sdelta1;
    double sdelta2;

    for (int i=1;i<=nvar;i++)
    {
      hess_calcreport(i,nvar);

      double xsave=x(i);
      sdelta1=x(i)+delta;
      sdelta1-=x(i);
      x(i)=xsave+sdelta1;
      dvariable vf=0.0;
      vf=initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      pre_userfunction();
      vf+=*objective_function_value::pobjfun;
      vf-=lambda*likeprof_params::likeprofptr[iprof]->variable();
      f = value(vf);
      gradcalc(nvar, g1);

      sdelta2=x(i)-delta;
      sdelta2-=x(i);
      x(i)=xsave+sdelta2;
      vf=0.0;
      vf=initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      pre_userfunction();
      vf+=*objective_function_value::pobjfun;
      vf-=lambda*likeprof_params::likeprofptr[iprof]->variable();
      f = value(vf);
      gradcalc(nvar, g2);
      x(i)=xsave;
      hess1=(g1-g2)/(sdelta1-sdelta2);
  /*
      sdelta1=x(i)+eps*delta;
      sdelta1-=x(i);
      x(i)=xsave+sdelta1;
      vf=0.0;
      vf=initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      pre_userfunction();
      vf+=*objective_function_value::pobjfun;
      vf-=lambda*likeprof_params::likeprofptr[iprof]->variable();
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
      vf-=lambda*likeprof_params::likeprofptr[iprof]->variable();
      f=value(vf);
      gradcalc(nvar,g2);
      x(i)=xsave;

      double eps2=eps*eps;
      hess2=(g1-g2)/(sdelta1-sdelta2);
      hess=(eps2*hess1-hess2) /(eps2-1.);
    */
      hess=hess1;
      ofs << hess;
    }
  }
  gradient_structure::set_NO_DERIVATIVES();
}
/*
void function_minimizer::hess_routine_and_constraint(int iprof)
{
  int nvar=initial_params::nvarcalc(); // get the number of active parameters
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
  uostream ofs("admodel.hes");
  //ofstream ofs5("tmphess");
  ofs << nvar;
  {
    {
      dvariable vf=0.0;
      vf=initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      pre_userfunction();
      vf+=*objective_function_value::pobjfun;
      f=value(vf);
      gradcalc(nvar,g1);
    }
    for (int i=1;i<=nvar;i++)
    {
      cout << "Estimating row " << i << " out of " << nvar
           << " for hessian" << endl;

      double f=0.0;
      double xsave=x(i);
      double sdelta1=x(i)+delta;
      sdelta1-=x(i);
      x(i)=xsave+sdelta1;
      dvariable vf=0.0;
      vf=initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      pre_userfunction();
      vf+=*objective_function_value::pobjfun;
      f=value(vf);
      gradcalc(nvar,g1);

      double sdelta2=x(i)-delta;
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

      double eps2=eps*eps;
      hess2=(g1-g2)/(sdelta1-sdelta2);
      hess=(eps2*hess1-hess2) /(eps2-1.);
      ofs << hess;
    }
    // do the hessian for the constraint function
    uostream cofs("constrnt.hes");
    cofs << nvar;
    for (i=1;i<=nvar;i++)
    {
      cout << "Estimating row " << i << " out of " << nvar
           << " for hessian" << endl;

      double f=0.0;
      double xsave=x(i);
      sdelta1=x(i)+delta;
      sdelta1-=x(i);
      x(i)=xsave+sdelta1;
      dvariable vf=0.0;
      vf=initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      pre_userfunction();
      vf=likeprof_params::likeprofptr[iprof]->variable();
      f=value(vf);
      gradcalc(nvar,g1);

      sdelta2=x(i)-delta;
      sdelta2-=x(i);
      x(i)=xsave+sdelta2;
      vf=0.0;
      vf=initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      pre_userfunction();
      vf=likeprof_params::likeprofptr[iprof]->variable();
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
      vf=likeprof_params::likeprofptr[iprof]->variable();
      f=value(vf);
      gradcalc(nvar,g1);

      x(i)=xsave-eps*delta;
      sdelta2=x(i)-eps*delta;
      sdelta2-=x(i);
      x(i)=xsave+sdelta2;
      vf=0.0;
      vf=initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      pre_userfunction();
      vf=likeprof_params::likeprofptr[iprof]->variable();
      f=value(vf);
      gradcalc(nvar,g2);
      x(i)=xsave;

      double eps2=eps*eps;
      hess2=(g1-g2)/(sdelta1-sdelta2);
      hess=(eps2*hess1-hess2) /(eps2-1.);
      cofs << hess;
    }
  }
  gradient_structure::set_NO_DERIVATIVES();
}
*/

/**
Calculate the derivatives of dependent variables with respect to
the independent variables.
*/
void function_minimizer::depvars_routine(void)
{
  reset_gradient_stack();
  dvector ggg(1,1);
  gradcalc(0,ggg);
  gradient_structure::set_YES_DERIVATIVES();
  initial_params::restore_start_phase();
  if (lapprox && lapprox->no_re_ders_flag)
  {
    initial_params::set_inactive_random_effects();
  }
  int nvar=initial_params::nvarcalc(); // get the number of active parameters
  int ndvar=stddev_params::num_stddev_calc();
  independent_variables x(1,nvar);
  initial_params::xinit(x);        // get the initial values into the x vector
  //double f;
  //double delta=1.e-7;
  adstring tmpstring="admodel.dep";
  if (ad_comm::wd_flag)
     tmpstring = ad_comm::adprogram_name + ".dep";
  ofstream ofs((char*)tmpstring);
  if (lapprox)
  {
    lapprox->no_function_component_flag=1;
  }

  dvariable vf;
  vf=initial_params::reset(dvar_vector(x));
  *objective_function_value::pobjfun=0.0;
  pre_userfunction();
  vf+=*objective_function_value::pobjfun;

  ofs << nvar << "  "  << ndvar << endl;
  int i;
  for (i=0;i< stddev_params::num_stddev_params;i++)
  {
     stddev_params::stddevptr[i]->set_dependent_variables();
  }
  gradient_structure::jacobcalc(nvar,ofs);
  for (i=0;i< stddev_params::num_stddev_params;i++)
  {
     ofs << stddev_params::stddevptr[i]->label() << "  ";
     ofs << stddev_params::stddevptr[i]->size_count() << endl;
  }
  if (lapprox)
  {
    lapprox->no_function_component_flag=0;
  }
  gradient_structure::set_NO_DERIVATIVES();
}
/**
Symmetrize and invert the hessian
*/
void function_minimizer::hess_inv(void)
{
  initial_params::set_inactive_only_random_effects();
  int nvar=initial_params::nvarcalc(); // get the number of active parameters
  independent_variables x(1,nvar);

  initial_params::xinit(x);        // get the initial values into the x vector
  //double f;
  dmatrix hess(1,nvar,1,nvar);
  uistream ifs("admodel.hes");
  int file_nvar = 0;
  ifs >> file_nvar;
  if (nvar != file_nvar)
  {
    cerr << "Number of active variables in file mod_hess.rpt is wrong"
         << endl;
  }

  for (int i = 1;i <= nvar; i++)
  {
    ifs >> hess(i);
    if (!ifs)
    {
      cerr << "Error reading line " << i  << " of the hessian"
           << " in routine hess_inv()" << endl;
      exit(1);
    }
  }

  _hessian.allocate(1, nvar, 1, nvar);
  _hessian = hess;

  int hybflag = 0;
  ifs >> hybflag;
  dvector sscale(1,nvar);
  ifs >> sscale;
  if (!ifs)
  {
    cerr << "Error reading sscale"
         << " in routine hess_inv()" << endl;
  }

  double maxerr=0.0;
  for (int i = 1;i <= nvar; i++)
  {
    for (int j=1;j<i;j++)
    {
      double tmp=(hess(i,j)+hess(j,i))/2.;
      double tmp1=fabs(hess(i,j)-hess(j,i));
      tmp1/=(1.e-4+fabs(hess(i,j))+fabs(hess(j,i)));
      if (tmp1>maxerr) maxerr=tmp1;
      hess(i,j)=tmp;
      hess(j,i)=tmp;
    }
  }
  /*
  if (maxerr>1.e-2)
  {
    cerr << "warning -- hessian aprroximation is poor" << endl;
  }
 */

  for (int i = 1;i <= nvar; i++)
  {
    int zero_switch=0;
    for (int j=1;j<=nvar;j++)
    {
      if (hess(i,j)!=0.0)
      {
        zero_switch=1;
      }
    }
    if (!zero_switch)
    {
      cerr << " Hessian is 0 in row " << i << endl;
      cerr << " This means that the derivative if probably identically 0 "
              " for this parameter" << endl;
    }
  }

  int ssggnn;
  _ln_det_value = ln_det(hess,ssggnn);
  int on1=0;
  {
    ofstream ofs3((char*)(ad_comm::adprogram_name + adstring(".eva")));
    {
      dvector se=eigenvalues(hess);
      ofs3 << setshowpoint() << setw(14) << setprecision(10)
           << "unsorted:\t" << se << endl;
     se=sort(se);
     ofs3 << setshowpoint() << setw(14) << setprecision(10)
     << "sorted:\t" << se << endl;
     if (se(se.indexmin())<=0.0)
      {
        negative_eigenvalue_flag=1;
        cout << "Warning -- Hessian does not appear to be"
         " positive definite" << endl;
      }
    }
    ivector negflags(0,hess.indexmax());
    int num_negflags=0;
    {
      int on = option_match(ad_comm::argc,ad_comm::argv,"-eigvec");
      on1=option_match(ad_comm::argc,ad_comm::argv,"-spmin");
      if (on > -1 || on1 >-1 )
      {
        ofs3 << setshowpoint() << setw(14) << setprecision(10)
          << eigenvalues(hess) << endl;
        dmatrix ev=trans(eigenvectors(hess));
        ofs3 << setshowpoint() << setw(14) << setprecision(10)
          << ev << endl;
        for (int i=1;i<=ev.indexmax();i++)
        {
          double lam=ev(i)*hess*ev(i);
          ofs3 << setshowpoint() << setw(14) << setprecision(10)
            << lam << "  "  << ev(i)*ev(i) << endl;
          if (lam<0.0)
          {
            num_negflags++;
            negflags(num_negflags)=i;
          }
        }
        if ( (on1>-1) && (num_negflags>0))   // we will try to get away from
        {                                     // saddle point
          negative_eigenvalue_flag=0;
          spminflag=1;
          if(negdirections)
          {
            delete negdirections;
          }
          negdirections = new dmatrix(1,num_negflags);
          for (int i=1;i<=num_negflags;i++)
          {
            (*negdirections)(i)=ev(negflags(i));
          }
        }
        int on2 = option_match(ad_comm::argc,ad_comm::argv,"-cross");
        if (on2>-1)
        {                                     // saddle point
          dmatrix cross(1,ev.indexmax(),1,ev.indexmax());
          for (int i = 1;i <= ev.indexmax(); i++)
          {
            for (int j=1;j<=ev.indexmax();j++)
            {
              cross(i,j)=ev(i)*ev(j);
            }
          }
          ofs3 <<  endl << "  e(i)*e(j) ";
          ofs3 << endl << cross << endl;
        }
      }
    }

    if (spminflag==0)
    {
      if (num_negflags==0)
      {
        hess=inv(hess);
        _hessian_inverse.allocate(1,nvar,1,nvar);
        _hessian_inverse = hess;

        int on=0;
        if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-eigvec"))>-1)
        {
          int i;
          ofs3 << "choleski decomp of correlation" << endl;
          dmatrix ch=choleski_decomp(hess);
          for (i=1;i<=ch.indexmax();i++)
            ofs3 << ch(i)/norm(ch(i)) << endl;
          ofs3 << "parameterization of choleski decomnp of correlation" << endl;
          for (i=1;i<=ch.indexmax();i++)
          {
            dvector tmp=ch(i)/norm(ch(i));
            ofs3 << tmp(1,i)/tmp(i) << endl;
          }
        }
      }
    }
  }
  if (spminflag==0)
  {
    if (on1<0)
    {
      for (int i = 1;i <= nvar; i++)
      {
        if (hess(i,i) <= 0.0)
        {
          hess_errorreport();
          ad_exit(1);
        }
      }
    }
    {
      adstring tmpstring="admodel.cov";
      if (ad_comm::wd_flag)
        tmpstring = ad_comm::adprogram_name + ".cov";
      uostream ofs((char*)tmpstring);
      ofs << nvar << hess;
      ofs << gradient_structure::Hybrid_bounded_flag;
      ofs << sscale;
    }
  }
}
void hess_calcreport(int i,int nvar)
{
  if (ad_printf)
    (*ad_printf)("Estimating row %d out of %d for hessian\n",i,nvar);
  else
    cout << "Estimating row " << i << " out of " << nvar << " for hessian"
         << endl;
}
void hess_errorreport(void)
{
  if (ad_printf)
    (*ad_printf)("Hessian does not appear to be positive definite\n");
  else
    cout << "Hessian does not appear to be positive definite\n" << endl;
}
