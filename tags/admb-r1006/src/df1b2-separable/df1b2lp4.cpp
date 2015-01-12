/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#if defined(USE_LAPLACE)
#  include <admodel.h>
#  include <df1b2fun.h>
#  include <adrndeff.h>
void get_second_ders(int xs,int us,const init_df1b2vector y,dmatrix& Hess,
  dmatrix& Dux, df1b2_gradlist * f1b2gradlist,function_minimizer * pfmin,
  laplace_approximation_calculator* lap);
double calculate_laplace_approximation(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin);
      

/**
 * Description not yet available.
 * \param
 */
void get_second_ders_master(int xs,int us,const init_df1b2vector _y,
  dmatrix& Hess,
  dmatrix& Dux, df1b2_gradlist * f1b2gradlist,function_minimizer * pfmin,
  laplace_approximation_calculator * lpc)
{
  // Note that xs is the number of active non random effects
  // parameters
  // us is the number of random effects parameters
  int j;
  int i;
  ADUNCONST(init_df1b2vector,y)
  int num_der_blocks=lpc->num_der_blocks;
  int xsize=lpc->xsize;
  int usize=lpc->usize;
  
  for (int ip=1;ip<=num_der_blocks;ip++)
  {
    df1b2variable::minder=lpc->minder(ip);
    df1b2variable::maxder=lpc->maxder(ip);
    lpc->set_u_dot(ip);
    df1b2_gradlist::set_yes_derivatives();
    (*re_objective_function_value::pobjfun)=0;
    df1b2variable pen=0.0;
    df1b2variable zz=0.0;
    initial_df1b2params::reset(y,pen);
    if (initial_df1b2params::separable_flag)
    {
      initial_df1b2params::separable_calculation_type=2;
      Hess.initialize();
      Dux.initialize();
    }
    
    //cout << "2D" << endl;
    pfmin->user_function();
    
    //pfmin->user_function(y,zz);
    (*re_objective_function_value::pobjfun)+=pen;
    (*re_objective_function_value::pobjfun)+=zz;
  
    if (!initial_df1b2params::separable_flag)
    {
      set_dependent_variable(*re_objective_function_value::pobjfun);
      df1b2_gradlist::set_no_derivatives();
      df1b2variable::passnumber=1;
      df1b2_gradcalc1();
    
      int mind=y(1).minder;
      int jmin=max(mind,xsize+1);
      int jmax=min(y(1).maxder,xsize+usize);
      for (i=1;i<=usize;i++)
        for (j=jmin;j<=jmax;j++)
          Hess(i,j-xsize)=y(i+xsize).u_bar[j-mind];
  
      jmin=max(mind,1);
      jmax=min(y(1).maxder,xsize);
      for (i=1;i<=usize;i++)
        for (j=jmin;j<=jmax;j++)
          Dux(i,j)=y(i+xsize).u_bar[j-1];
    }
    if (ip<num_der_blocks)
      f1b2gradlist->reset();
  }
  if (ad_comm::pvm_manager)
  {
    if (ad_comm::pvm_manager->timing_flag)
      ad_comm::pvm_manager->tm.get_elapsed_time_and_reset();
  }
  
  d3_array M1=get_dmatrix_from_slaves();

  if (ad_comm::pvm_manager)
  {
    if (ad_comm::pvm_manager->timing_flag)
    {
      double time=ad_comm::pvm_manager->tm.get_elapsed_time_and_reset();
      if (ad_comm::global_logfile)
      {
        (*ad_comm::global_logfile) << "Time in get dmatrix from slaves "
          << time << endl;
      }
    }
  }
  int k;
  int mmin=M1.indexmin();
  int mmax=M1.indexmax();
  for (k=mmin;k<=mmax;k++)
  {
    int imin=M1(k).indexmin();
    int imax=M1(k).indexmax();
    for (i=imin;i<=imax;i++)
    {
      int jmin=M1(k,i).indexmin();
      int jmax=M1(k,i).indexmax();
      dvector & M1_ki=M1(k,i);
      for (int j=jmin;j<=jmax;j++)
      {
        Hess(i,j-xsize)=M1_ki(j);
      }
    }
  }
  if (ad_comm::pvm_manager)
  {
    if (ad_comm::pvm_manager->timing_flag)
      ad_comm::pvm_manager->tm.get_elapsed_time_and_reset();
  }
  
  imatrix flags=get_int_from_slaves();
  d3_array Dux1=get_dmatrix_from_slaves(flags);
  if (ad_comm::pvm_manager)
  {
    if (ad_comm::pvm_manager->timing_flag)
    {
      double time=ad_comm::pvm_manager->tm.get_elapsed_time_and_reset();
      if (ad_comm::global_logfile)
      {
        (*ad_comm::global_logfile) << "Time in get dmatrix Dux from slaves "
          << time << endl;
      }
    }
  }
  
  mmin=Dux1.indexmin();
  mmax=Dux1.indexmax();
  for (k=mmin;k<=mmax;k++)
  {
    if (allocated(Dux1(k)))
    {
      int imin=Dux1(k).indexmin();
      int imax=Dux1(k).indexmax();
      for (i=imin;i<=imax;i++)
      {
        int jmin=Dux1(k,i).indexmin();
        int jmax=Dux1(k,i).indexmax();
        dvector & Dux1_ki=Dux1(k,i);
        for (int j=jmin;j<=jmax;j++)
        {
          Dux(i,j)=Dux1_ki(j);
        }
      }
    }
  }
  //cout << "Hess" << endl;
  //cout << norm2(Hess-trans(Hess)) << endl;
  //cout << "Dux" << endl;
  //cout << setprecision(16) << Dux << endl;
}

/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::default_calculations_parallel_master
  (const dvector& _x,const double& _f,function_minimizer * pfmin)
{
  // for use when there is no separability
  ADUNCONST(dvector,x)
  ADUNCONST(double,f)
  int i,j;

  send_dvector_to_slaves(x);
  initial_params::set_inactive_only_random_effects(); 
  gradient_structure::set_NO_DERIVATIVES();
  initial_params::reset(x);    // get current x values into the model
  gradient_structure::set_YES_DERIVATIVES();

  initial_params::set_active_only_random_effects(); 
  //int lmn_flag=0;
  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm1)
    {
      ad_comm::ptm1->get_elapsed_time_and_reset();
    }
    if (ad_comm::ptm)
    {
      ad_comm::ptm->get_elapsed_time_and_reset();
    }
  }  
  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm)
    {
      double time=ad_comm::ptm->get_elapsed_time_and_reset();
      if (ad_comm::global_logfile)
      {
        (*ad_comm::global_logfile) << endl << " Time pos 0 "
          << time << endl;
      }
    }
  }

  if (!inner_lmnflag)
  {
    if (!ADqd_flag)
      uhat=get_uhat_quasi_newton(x,pfmin);
    else
      uhat=get_uhat_quasi_newton_qd(x,pfmin);
  }
  else
  {
    uhat=get_uhat_lm_newton(x,pfmin);
  }

  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm)
    {
      double time=ad_comm::ptm->get_elapsed_time_and_reset();
      if (ad_comm::global_logfile)
      {
        (*ad_comm::global_logfile) << " Time in inner optimization "
          << time << endl;
      }
    }
  }

  for (i=1;i<=xsize;i++)
  {
    y(i)=x(i);
  }
  for (i=1;i<=usize;i++)
  {
    y(i+xsize)=uhat(i);
  }
  //cout << y << endl;
        
  for(int ii=1;ii<=num_nr_iters;ii++)
  {  
    {   
      // test newton raphson
      Hess.initialize();
     cout << "Newton raphson " << ii << endl;
      get_newton_raphson_info_master(pfmin);
  
   
      if (ad_comm::time_flag)
      {
        if (ad_comm::ptm)
        {
          double time=ad_comm::ptm->get_elapsed_time_and_reset();
          if (ad_comm::global_logfile)
          {
            (*ad_comm::global_logfile) << " Time in newton-raphson " <<  ii << "  "
              << time << endl;
          }
        }
      }
        dvector step;
#if defined(USE_ATLAS)   
      if (!ad_comm::no_atlas_flag) 
        step=-atlas_solve_spd(Hess,grad);
      else
        step=-solve(Hess,grad);
#else
      step=-solve(Hess,grad);
#endif
      if (ad_comm::time_flag)
      {
        if (ad_comm::ptm)
        {
          double time=ad_comm::ptm->get_elapsed_time_and_reset();
          if (ad_comm::global_logfile)
          {
            (*ad_comm::global_logfile) << " time_in solve " <<  ii << "  "
              << time << endl;
          }
        }
      }
      send_dvector_to_slaves(step);
      //cout << norm(step1-step) << endl;
  
      if (ad_comm::time_flag)
      {
        if (ad_comm::ptm)
        {
          double time=ad_comm::ptm->get_elapsed_time_and_reset();
          if (ad_comm::global_logfile)
          {
            (*ad_comm::global_logfile) << " Time in send dvector to slaves " <<  ii <<  "   "
              << time << endl;
          }
        }
      }
     
      f1b2gradlist->reset();
      f1b2gradlist->list.initialize();
      f1b2gradlist->list2.initialize();
      f1b2gradlist->list3.initialize();
      f1b2gradlist->nlist.initialize();
      f1b2gradlist->nlist2.initialize();
      f1b2gradlist->nlist3.initialize();
    
    
      uhat+=step;
    
      evaluate_function(uhat,pfmin);
    }
  
    for (i=1;i<=usize;i++)
    {
      y(i+xsize)=uhat(i);
    }
  }
 
  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm)
    {
      double time=ad_comm::ptm->get_elapsed_time_and_reset();
      if (ad_comm::global_logfile)
      {
        (*ad_comm::global_logfile) << " Time in reset and evaluate function"
          << time << endl;
      }
    }
  }
  get_second_ders_master(xsize,usize,y,Hess,Dux,f1b2gradlist,pfmin,this);
  //int sgn=0;
  
  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm)
    {
      double time=ad_comm::ptm->get_elapsed_time_and_reset();
      if (ad_comm::global_logfile)
      {
        (*ad_comm::global_logfile) << " Time in dget second ders "
          << time << endl;
      }
    }
  }

  f=calculate_laplace_approximation(x,uhat,Hess,xadjoint,uadjoint,
    Hessadjoint,pfmin);
 
  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm)
    {
      double time=ad_comm::ptm->get_elapsed_time_and_reset();
      if (ad_comm::global_logfile)
      {
        (*ad_comm::global_logfile) << " Time in calculate laplace approximation "
          << time << endl;
      }
    }
  }


  for (int ip=num_der_blocks;ip>=1;ip--)
  {
    df1b2variable::minder=minder(ip);
    df1b2variable::maxder=maxder(ip);
    int mind=y(1).minder;
    int jmin=max(mind,xsize+1);
    int jmax=min(y(1).maxder,xsize+usize);
    for (i=1;i<=usize;i++)
    {
      for (j=jmin;j<=jmax;j++)
      {
        //Hess(i,j-xsize)=y(i+xsize).u_bar[j-mind];
        y(i+xsize).get_u_bar_tilde()[j-mind]=Hessadjoint(i,j-xsize);
      }
    }

    int mmin=minder.indexmin();  
    int mmax=minder.indexmax();  
    ivector jjmin(mmin,mmax-1);
    ivector jjmax(mmin,mmax-1);
    for (i=mmin+1;i<=mmax;i++)
    {
      jjmin(i-1)=max(minder(i),xsize+1)-xsize;
      jjmax(i-1)=min(maxder(i),xsize+usize)-xsize;
    }

    if (ad_comm::pvm_manager)
    {
      if (ad_comm::pvm_manager->timing_flag)
        ad_comm::pvm_manager->tm.get_elapsed_time_and_reset();
    }
    send_dmatrix_to_slaves(Hessadjoint,jjmin,jjmax);
    if (ad_comm::pvm_manager)
    {
      if (ad_comm::pvm_manager->timing_flag)
      {
        double time=ad_comm::pvm_manager->tm.get_elapsed_time_and_reset();
        if (ad_comm::global_logfile)
        {
          (*ad_comm::global_logfile) << "Time in send dmatrix to slaves Hessadjoint "
            << time << endl;
        }
      }
    }

    if (initial_df1b2params::separable_flag)
    {
      for (j=1;j<=xsize+usize;j++) 
      {
        *y(j).get_u_tilde()=0;
      }
      Hess.initialize();
      initial_df1b2params::separable_calculation_type=3;
      pfmin->user_function();
    }
    else
    {
      if (ip<num_der_blocks)
      {
        f1b2gradlist->reset();
        set_u_dot(ip);
        df1b2_gradlist::set_yes_derivatives();
        (*re_objective_function_value::pobjfun)=0;
        df1b2variable pen=0.0;
        df1b2variable zz=0.0;
   
        initial_df1b2params::reset(y,pen);
        pfmin->user_function();
        (*re_objective_function_value::pobjfun)+=pen;
        (*re_objective_function_value::pobjfun)+=zz;
  
        set_dependent_variable(*re_objective_function_value::pobjfun);
        df1b2_gradlist::set_no_derivatives();
        df1b2variable::passnumber=1;
        df1b2_gradcalc1();
      }

      for (i=1;i<=usize;i++)
      {
        for (j=jmin;j<=jmax;j++)
        {
          //Hess(i,j-xsize)=y(i+xsize).u_bar[j-mind];
          y(i+xsize).get_u_bar_tilde()[j-mind]=Hessadjoint(i,j-xsize);
        }
      }
    
      //int mind=y(1).minder;
      df1b2variable::passnumber=2;
      df1b2_gradcalc1();
    
      df1b2variable::passnumber=3;
      df1b2_gradcalc1();
    
      f1b2gradlist->reset();
      f1b2gradlist->list.initialize();
      f1b2gradlist->list2.initialize();
      f1b2gradlist->list3.initialize();
      f1b2gradlist->nlist.initialize();
      f1b2gradlist->nlist2.initialize();
      f1b2gradlist->nlist3.initialize();
    } 
   
    if (ad_comm::time_flag)
    {
      if (ad_comm::ptm)
      {
        double time=ad_comm::ptm->get_elapsed_time_and_reset();
        if (ad_comm::global_logfile)
        {
          (*ad_comm::global_logfile) << " time for 3rd derivatives "
            << time << endl;
        }
      }
    }
    dvector dtmp(1,xsize);
    for (i=1;i<=xsize;i++)
    {
      dtmp(i)=*y(i).get_u_tilde();
    }
    if (initial_df1b2params::separable_flag)
    {
      dvector scale(1,nvar);   // need to get scale from somewhere
      /*int check=*/initial_params::stddev_scale(scale,x);
      dvector sscale=scale(1,Dux(1).indexmax());
      for (i=1;i<=usize;i++)
      {
        Dux(i)=elem_prod(Dux(i),sscale);
      }
      dtmp=elem_prod(dtmp,sscale);
    }
    if (ad_comm::time_flag)
    {
      if (ad_comm::ptm)
      {
        ad_comm::ptm->get_elapsed_time_and_reset();
      }
    }
  
    dmatrix slave_dtmps=get_dvector_from_slaves();
    if (ad_comm::time_flag)
    {
      if (ad_comm::ptm)
      {
        double time=ad_comm::ptm->get_elapsed_time_and_reset();
        if (ad_comm::global_logfile)
        {
          (*ad_comm::global_logfile) << " Time in get dvector from slaves slave_dtmp "
            << time << endl;
        }
      }
    }
    mmin=slave_dtmps.indexmin();
    mmax=slave_dtmps.indexmax();
    
    for (j=mmin;j<=mmax;j++)
    {
      dvector& s_j=slave_dtmps(j);
      for (i=1;i<=xsize;i++)
      {
        //xadjoint(i)+=s_j(i);
        dtmp(i)+=s_j(i);
      }
    }
  
    for (i=1;i<=xsize;i++)
    {
      xadjoint(i)+=dtmp(i);
    }
    dmatrix slave_utmps=get_dvector_from_slaves();
    if (ad_comm::ptm)
    {
      double time=ad_comm::ptm->get_elapsed_time_and_reset();
      if (ad_comm::global_logfile)
      {
        (*ad_comm::global_logfile) << " Time in get dvector from slaves slave_utmps "
          << time << endl;
      }
    }
      
    mmin=slave_utmps.indexmin();
    mmax=slave_utmps.indexmax();
    
    for (j=mmin;j<=mmax;j++)
    {
      dvector& s_j=slave_utmps(j);
      for (i=1;i<=usize;i++)
      {
        //xadjoint(i)+=s_j(i);
        uadjoint(i)+=s_j(i);
      }
    }
  
    for (i=1;i<=usize;i++)
      uadjoint(i)+=*y(xsize+i).get_u_tilde();
  }
#if defined(USE_ATLAS)   
  if (!ad_comm::no_atlas_flag) 
  {
    //xadjoint -= uadjoint*atlas_solve_spd_trans(Hess,Dux);
    xadjoint -= atlas_solve_spd_trans(Hess,uadjoint)*Dux;
  }
  else
  {
    //xadjoint -= uadjoint*inv(Hess)*Dux;
    xadjoint -= solve(Hess,uadjoint)*Dux;
  }
#else
  //xadjoint -= uadjoint*inv(Hess)*Dux;
  xadjoint -= solve(Hess,uadjoint)*Dux;
#endif

  if (ad_comm::ptm)
  {
    double time=ad_comm::ptm->get_elapsed_time_and_reset();
    if (ad_comm::global_logfile)
    {
      (*ad_comm::global_logfile) << " Time in second solve "
        << time << endl;
    }
  }
  if (ad_comm::ptm1)
  {
    double time=ad_comm::ptm1->get_elapsed_time_and_reset();
    if (ad_comm::global_logfile)
    {
      (*ad_comm::global_logfile) << " Total time in function evaluation "
        << time << endl << endl;
    }
  }

  return xadjoint;
}

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::get_newton_raphson_info_master
  (function_minimizer * pfmin)
{
  int i,j,ip; 
  
  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm)
    {
        (*ad_comm::global_logfile) << " Starting Newton-Raphson " 
          <<  endl;
    }
  }
  for (ip=1;ip<=num_der_blocks;ip++)
  {
    df1b2variable::minder=minder(ip);
    df1b2variable::maxder=maxder(ip);

    set_u_dot(ip);

    // do we need to reallocate memory for df1b2variables?
    check_for_need_to_reallocate(ip);
    df1b2_gradlist::set_yes_derivatives();
    //cout << re_objective_function_value::pobjfun << endl;
    //cout << re_objective_function_value::pobjfun->ptr << endl;
    (*re_objective_function_value::pobjfun)=0;
    df1b2variable pen=0.0;
    df1b2variable zz=0.0;
    initial_df1b2params::reset(y,pen);
    if (initial_df1b2params::separable_flag)
    {
      Hess.initialize();
      grad.initialize();
    }

    double time1;
    if (ad_comm::time_flag)
    {
      if (ad_comm::ptm)
      {
        /*double time1=*/ad_comm::ptm->get_elapsed_time();
      }
    }

    pfmin->user_function();

    if (ad_comm::time_flag)
    {
      if (ad_comm::ptm)
      {
        double time=ad_comm::ptm->get_elapsed_time();
        if (ad_comm::global_logfile)
        {
          (*ad_comm::global_logfile) << "       Time in user_function() " <<  ip << "  "
            << time-time1 << endl;
        }
      }
    }


    (*re_objective_function_value::pobjfun)+=pen;
    (*re_objective_function_value::pobjfun)+=zz;
  
    if (!initial_df1b2params::separable_flag)
    {
      set_dependent_variable(*re_objective_function_value::pobjfun);
      df1b2_gradlist::set_no_derivatives();
      df1b2variable::passnumber=1;
      df1b2_gradcalc1();
      int mind=y(1).minder;
      int jmin=max(mind,xsize+1);
      int jmax=min(y(1).maxder,xsize+usize);
      for (i=1;i<=usize;i++)
        for (j=jmin;j<=jmax;j++)
          Hess(i,j-xsize)=y(i+xsize).u_bar[j-mind];
  
      for (j=jmin;j<=jmax;j++)
        grad(j-xsize)= re_objective_function_value::pobjfun->u_dot[j-mind];
    }
    if (ip<num_der_blocks)
      f1b2gradlist->reset();
  }
  double time1;
  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm)
    {
      time1=ad_comm::ptm->get_elapsed_time();
    }
  }

  d3_array M1=get_dmatrix_from_slaves();

  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm)
    {
      double time=ad_comm::ptm->get_elapsed_time();
      if (ad_comm::global_logfile)
      {
        (*ad_comm::global_logfile) << "       Time to getdmatrix from slaves in "
          " get newton raphson " <<  ip << "  " << time-time1 << endl;
      }
    }
  }
  int k;
  int mmin=M1.indexmin();
  int mmax=M1.indexmax();
  for (k=mmin;k<=mmax;k++)
  {
    int imin=M1(k).indexmin();
    int imax=M1(k).indexmax();
    for (i=imin;i<=imax;i++)
    {
      int jmin=M1(k,i).indexmin();
      int jmax=M1(k,i).indexmax();
      dvector & M1_ki=M1(k,i);
      for (int j=jmin;j<=jmax;j++)
      {
        Hess(i,j-xsize)=M1_ki(j);
      }
    }
  }
  
  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm)
    {
      /*double time1=*/ad_comm::ptm->get_elapsed_time();
    }
  }
  dmatrix g1=get_dvector_from_slaves();

  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm)
    {
      double time=ad_comm::ptm->get_elapsed_time();
      if (ad_comm::global_logfile)
      {
        (*ad_comm::global_logfile) << "       Time in get dvector "
            " from slaves in get newton raphson " <<  ip << "  "
          << time-time1 << endl;
      }
    }
  }
  mmin=g1.indexmin();
  mmax=g1.indexmax();
  for (k=mmin;k<=mmax;k++)
  {
    int jmin=g1(k).indexmin();
    int jmax=g1(k).indexmax();
    dvector & g1_k=g1(k);
    for (int j=jmin;j<=jmax;j++)
    {
      grad(j-xsize)=g1_k(j); 
    }
  }
  
}


#endif //#if defined(USE_LAPLACE)
