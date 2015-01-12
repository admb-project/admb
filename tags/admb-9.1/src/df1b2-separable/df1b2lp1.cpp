/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#if defined(USE_LAPLACE)
#  include <fvar.hpp>
#  include <admodel.h>
#  include <df1b2fun.h>
#  include <adrndeff.h>
void evaluate_function_gradient(double& f,const dvector& x,
  function_minimizer * pfmin,dvector&,dvector&);
double evaluate_function(const dvector& x,function_minimizer * pfmin);
void get_second_ders(int xs,int us,const init_df1b2vector y,dmatrix& Hess,
  dmatrix& Dux, df1b2_gradlist * f1b2gradlist,function_minimizer * pfmin,
  laplace_approximation_calculator* lap);
double calculate_laplace_approximation(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin);
      
double calculate_importance_sample(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin);
      
double calculate_importance_sample_funnel(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin);
      
dmatrix choleski_decomp_positive(const dmatrix& M,double b);

dvector laplace_approximation_calculator::default_calculations
  (const dvector& _x,const double& _f,function_minimizer * pfmin)
{
  // for use when there is no separability
  ADUNCONST(dvector,x)
  ADUNCONST(double,f)
  int i,j;

  initial_params::set_inactive_only_random_effects(); 
  gradient_structure::set_NO_DERIVATIVES();
  initial_params::reset(x);    // get current x values into the model
  gradient_structure::set_YES_DERIVATIVES();

  initial_params::set_active_only_random_effects(); 
  int lmn_flag=0;
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
      double time=ad_comm::ptm->get_elapsed_time();
      if (ad_comm::global_logfile)
      {
        (*ad_comm::global_logfile) << " Time pos 0 "
          << time << endl;
      }
    }
  }
  
  double maxg=1.e+200;
  double maxg_save;
  dvector uhat_old(1,usize);
  double f_from_1=0.0;
  if (inner_maxfn>0)
  {
    if (!inner_lmnflag)
    {
      if (!ADqd_flag)
      {
        uhat=get_uhat_quasi_newton(x,pfmin);
        maxg=fabs(fmc1.gmax);
        f_from_1=fmc1.fbest;
      }
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
  }

  for (i=1;i<=xsize;i++)
  {
    y(i)=x(i);
  }
  for (i=1;i<=usize;i++)
  {
    y(i+xsize)=uhat(i);
  }
        
  int ierr=0;
  int niters=0;
  if (function_minimizer::first_hessian_flag)
    niters=num_nr_iters+1;
  else
    niters=num_nr_iters;

  int nv=0;
  if (quadratic_prior::get_num_quadratic_prior()>0)
  {
    nv=initial_df1b2params::set_index();
    if (allocated(used_flags))
    {
      if (used_flags.indexmax() != nv)
      {
        used_flags.safe_deallocate();
      }
    }
    if (!allocated(used_flags))
    {
      used_flags.safe_allocate(1,nv);
    }
  }
  
  for(int ii=1;ii<=niters;ii++)
  {  
    if (quadratic_prior::get_num_quadratic_prior()>0)
    {
      check_pool_size();
    }
    {   
      // test newton raphson
      Hess.initialize();
     cout << "Newton raphson " << ii << endl;
      pmin->inner_opt_flag=1;
      get_newton_raphson_info(pfmin);
      pmin->inner_opt_flag=0;

      if (quadratic_prior::get_num_quadratic_prior()>0)
      {
        laplace_approximation_calculator::where_are_we_flag=2; 
        double maxg=fabs(evaluate_function_quiet(uhat,pfmin));
        laplace_approximation_calculator::where_are_we_flag=0; 
        quadratic_prior::get_cHessian_contribution(Hess,xsize);
        quadratic_prior::get_cgradient_contribution(grad,xsize);
      }

      if (ii==1)
      {
        double diff= fabs(re_objective_function_value::fun_without_pen-
          objective_function_value::fun_without_pen);
       /*
        if (diff>1.e-7)
        {
          cout << "there is a difference in the the user_functions " 
            << setprecision(15) <<  re_objective_function_value::fun_without_pen
            <<  " from autodif  we have " 
            << setprecision(15) << objective_function_value::fun_without_pen
            << " diff = "
            << diff  << endl;
          //ad_exit(1);
        }
       */
      }
  
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
      int print_hess_in_newton_raphson_flag=0;
      if (print_hess_in_newton_raphson_flag)
      {
        cout << norm2(Hess-trans(Hess)) << endl;
        if (ad_comm::global_logfile)
        {
          (*ad_comm::global_logfile) << setprecision(4) << setscientific()  
            << setw(12) << sort(eigenvalues(Hess)) << endl;
          (*ad_comm::global_logfile) << setprecision(4) << setscientific()  
            << setw(12) << Hess << endl;
        }
      }
     
#if defined(USE_ATLAS)   
      if (!ad_comm::no_atlas_flag) 
      {
        step=-atlas_solve_spd(Hess,grad,ierr);
      }
      else
      {
        dmatrix A=choleski_decomp_positive(Hess,ierr);
        if (!ierr)
        {
          step=-solve(Hess,grad);
          //step=-solve(A*trans(A),grad);
        }
      }
      if (ierr)
      {
        f1b2gradlist->reset();
        f1b2gradlist->list.initialize();
        f1b2gradlist->list2.initialize();
        f1b2gradlist->list3.initialize();
        f1b2gradlist->nlist.initialize();
        f1b2gradlist->nlist2.initialize();
        f1b2gradlist->nlist3.initialize();
        break;
      }
#else
      //step=-solve(Hess,grad);
      int ierror=0;
      int icount=0;
      int trust_update_flag=0;
      do
      {
        icount++;
        if (saddlepointflag==1 || saddlepointflag==2)
        {
          step=choleski_solve_neghess_error(Hess,grad,ierror);
        }
        else
        {
          step=-choleski_solve_error(Hess,grad,ierror);
        }
        if (ierror==1)
        {
          trust_update_flag=1;
          uhat_old=uhat;
          dvector vv=sort(eigenvalues(Hess));
          // matrix is not positive definite
          // do minimization
          dvector s(grad.indexmin(),grad.indexmax());
          double lambda=0.01;
          if (saddlepointflag==2) // max not min 
          {
            const dmatrix  & cmHess=-Hess;
            const dvector & cmgrad = -grad;
            dmatrix  & mHess = (dmatrix  &) (cmHess);
            dvector & mgrad = (dvector &) (cmgrad);
            step=local_minimization(s,mHess,mgrad,lambda);
          }
          else
          {
            step=local_minimization(s,Hess,grad,lambda);
          }
          uhat+=step;
          for (i=1;i<=usize;i++)
          {
            y(i+xsize)=uhat(i);
          }

          f1b2gradlist->reset();
          f1b2gradlist->list.initialize();
          f1b2gradlist->list2.initialize();
          f1b2gradlist->list3.initialize();
          f1b2gradlist->nlist.initialize();
          f1b2gradlist->nlist2.initialize();
          f1b2gradlist->nlist3.initialize();
          
          get_newton_raphson_info(pfmin);

          if (quadratic_prior::get_num_quadratic_prior()>0)
          {
            laplace_approximation_calculator::where_are_we_flag=2; 
            double maxg=fabs(evaluate_function_quiet(uhat,pfmin));
            laplace_approximation_calculator::where_are_we_flag=0; 
            quadratic_prior::get_cHessian_contribution(Hess,xsize);
            quadratic_prior::get_cgradient_contribution(grad,xsize);
          }

        }
        else if (trust_update_flag==1)
        {
          cout << "Found positive definite Hessian with trust region method" 
               << endl;
        }
      }
      while (ierror==1 && icount<100);
      if (ierror==1)
      {
        cerr << "Can't make a positive definite Hessian" << endl;
        ad_exit(1);
      }
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
     
      f1b2gradlist->reset();
      f1b2gradlist->list.initialize();
      f1b2gradlist->list2.initialize();
      f1b2gradlist->list3.initialize();
      f1b2gradlist->nlist.initialize();
      f1b2gradlist->nlist2.initialize();
      f1b2gradlist->nlist3.initialize();
    
    
      if (trust_update_flag==0)
      {
        uhat_old=uhat;
        uhat+=step;
      }
      else
      {
        trust_update_flag=0;
      }
    
      double maxg_old=maxg;
      pmin->inner_opt_flag=1;
      maxg=fabs(evaluate_function(uhat,pfmin));
      if (maxg>maxg_old)
      {
        uhat=uhat_old;
        evaluate_function(uhat,pfmin);
        break;
      }
      if (maxg < 1.e-13) 
      {
        break;
      }
    }
    for (i=1;i<=usize;i++)
    {
      y(i+xsize)=uhat(i);
    }
  }
    
  
  if (num_nr_iters<=0)
  {
    evaluate_function(uhat,pfmin);
  }
  
  for (i=1;i<=usize;i++)
  {
    y(i+xsize)=uhat(i);
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
  pmin->inner_opt_flag=0;


  if (saddlepointflag==2)  
  {
    dvector localx(1,xsize+usize);
    for (int i=1;i<=xsize+usize;i++)
    {
      localx(i)=value(y(i));
    }
    initial_params::set_inactive_only_random_effects(); 
    initial_params::set_active_random_effects(); 
    int nnn=initial_params::nvarcalc();  
    evaluate_function_gradient(f,localx,pfmin,xadjoint,uadjoint);
    pmin->inner_opt_flag=1;
    get_second_ders(xsize,usize,y,Hess,Dux,f1b2gradlist,pfmin,this);
    pmin->inner_opt_flag=0;
    xadjoint -= solve(Hess,uadjoint)*Dux;
    f1b2gradlist->reset();
    f1b2gradlist->list.initialize();
    f1b2gradlist->list2.initialize();
    f1b2gradlist->list3.initialize();
    f1b2gradlist->nlist.initialize();
    f1b2gradlist->nlist2.initialize();
    f1b2gradlist->nlist3.initialize();
  }
  else // don't need this for minimax calculations
  {
    get_second_ders(xsize,usize,y,Hess,Dux,f1b2gradlist,pfmin,this);
    int sgn=0;
    
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
    if (!ierr)
    {
      if (num_importance_samples==0)
      {
        //cout << "Hess " << endl << Hess << endl;
        f=calculate_laplace_approximation(x,uhat,Hess,xadjoint,uadjoint,
          Hessadjoint,pfmin);
      }
      else
      {
        if (isfunnel_flag==0)
        {
          f=calculate_importance_sample(x,uhat,Hess,xadjoint,uadjoint,
            Hessadjoint,pfmin);
        }
        else
        {
          f=calculate_importance_sample_funnel(x,uhat,Hess,xadjoint,uadjoint,
            Hessadjoint,pfmin);
        }
      }
    }
    else
    {
      f=1.e+30;
    }
   
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
  
          re_objective_function_value::fun_without_pen=
            value(*re_objective_function_value::pobjfun);
  
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
      
        int mind=y(1).minder;
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
        int check=initial_params::stddev_scale(scale,x);
        dvector sscale=scale(1,Dux(1).indexmax());
        for (i=1;i<=usize;i++)
        {
          Dux(i)=elem_prod(Dux(i),sscale);
        }
        dtmp=elem_prod(dtmp,sscale);
      }
    
      for (i=1;i<=xsize;i++)
      {
        xadjoint(i)+=dtmp(i);
      }
      for (i=1;i<=usize;i++)
        uadjoint(i)+=*y(xsize+i).get_u_tilde();
    }
   // *****************************************************************
   // new stuff to deal with quadraticprior
   // *****************************************************************
  
      int xstuff=3;
      if (xstuff && df1b2quadratic_prior::get_num_quadratic_prior()>0)
      {
        initial_params::straight_through_flag=0;
        funnel_init_var::lapprox=0;
        block_diagonal_flag=0;
        dvector scale1(1,nvar);   // need to get scale from somewhere
        initial_params::set_inactive_only_random_effects(); 
        int check=initial_params::stddev_scale(scale1,x);
      
        laplace_approximation_calculator::where_are_we_flag=3; 
        quadratic_prior::in_qp_calculations=1;
        funnel_init_var::lapprox=this;
        df1b2_gradlist::set_no_derivatives();
        dvector scale(1,nvar);   // need to get scale from somewhere
        check=initial_params::stddev_scale(scale,x);
        dvector sscale=scale(1,Dux(1).indexmax());
  
        for (i=1;i<=usize;i++)
        {
          Dux(i)=elem_div(Dux(i),sscale);
        }
  
        if (xstuff>1)
        {
          df1b2quadratic_prior::get_Lxu_contribution(Dux);
        }
        quadratic_prior::in_qp_calculations=0;
        funnel_init_var::lapprox=0;
        laplace_approximation_calculator::where_are_we_flag=0; 
     
        for (i=1;i<=usize;i++)
        {
          Dux(i)=elem_prod(Dux(i),sscale);
        }
        //local_dtemp=elem_prod(local_dtemp,sscale);
    
        if (xstuff>2)
        {
          dvector tmp=evaluate_function_with_quadprior(x,usize,pfmin);
          for (i=1;i<=xsize;i++)
          {
            xadjoint(i)+=tmp(i);
          }
        }
    
        if (xstuff>2)
        {
          quadratic_prior::get_cHessian_contribution_from_vHessian(Hess,xsize);
        }
      }
    
   // *****************************************************************
   // new stuff to deal with quadraticprior
   // *****************************************************************
    if (ad_comm::ptm)
    {
      double time=ad_comm::ptm->get_elapsed_time_and_reset();
    }
  
  #if defined(USE_ATLAS)   
        if (!ad_comm::no_atlas_flag) 
        {
          //xadjoint -= uadjoint*atlas_solve_spd_trans(Hess,Dux);
          xadjoint -= atlas_solve_spd_trans(Hess,uadjoint)*Dux;
        }
        else
        {
          //xadjoint -= uadjoint*solve(Hess,Dux);
          xadjoint -= solve(Hess,uadjoint)*Dux;
        }
  #else
        //xadjoint -= uadjoint*solve(Hess,Dux);
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
  }
  return xadjoint;
}
  
void laplace_approximation_calculator::get_newton_raphson_info
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
     //cout << setprecision(15) << y << endl;
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
        double time1=ad_comm::ptm->get_elapsed_time();
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

    re_objective_function_value::fun_without_pen
      =value(*re_objective_function_value::pobjfun);

    (*re_objective_function_value::pobjfun)+=pen;
    (*re_objective_function_value::pobjfun)+=zz;
  
    //cout << setprecision(15) << *re_objective_function_value::pobjfun << endl;
    //cout << setprecision(15) << pen << endl;
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
     /*
      {
        ofstream ofs("hessreport"); 
        ofs << setw(6) << Hess << endl << endl;
        ofs << setw(10) << setfixed() << setprecision(3) << choleski_decomp(Hess) << endl << endl;
        ofs << setw(10) << setfixed() << setprecision(3) << inv(Hess) << endl << endl;
        ofs << setw(10) << setfixed() << setprecision(3) << choleski_decomp(inv(Hess)) << endl << endl;
      }
      */
    // ****************************************************************
    // ****************************************************************
    // ****************************************************************
    // temporary shit  
     /*
      for (i=1;i<=usize;i++)
      {
        for (j=jmin;j<=jmax;j++)
        {
          //Hess(i,j-xsize)=y(i+xsize).u_bar[j-mind];
          y(i+xsize).get_u_bar_tilde()[j-mind]=Hessadjoint(i,j-xsize);
        }
      }
      cout << Hess << endl;
      df1b2variable::passnumber=2;
      df1b2_gradcalc1();
    
      df1b2variable::passnumber=3;
      df1b2_gradcalc1();
     */
    // ****************************************************************
    // ****************************************************************
    // ****************************************************************
    // ****************************************************************
      for (j=jmin;j<=jmax;j++)
        grad(j-xsize)= re_objective_function_value::pobjfun->u_dot[j-mind];
    }
    if (ip<num_der_blocks)
      f1b2gradlist->reset();
  }


  // just to match master pvm routine
  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm)
    {
      double time=ad_comm::ptm->get_elapsed_time();
    }
  }
}


void laplace_approximation_calculator::set_u_dot(int ip)
{
  int mmin=y.indexmin(); 
  int mmax=y.indexmax(); 

  for (int i=mmin;i<=mmax;i++)
  {
    y(i).set_u_dot();
  }
}



void laplace_approximation_calculator::check_pool_size(void)
{
  int num_active_parameters=nvar;
  f1b2gradlist->reset();

  adpool * tmppool=df1b2variable::pool;
  if (tmppool)
  {
    //cout << tmppool << endl;
    // check if current pool is the right size
    if (tmppool->nvar != num_active_parameters)
    {
      // check sizes of other pools
      int found_pool_flag=0;
      for (int i=0;i<df1b2variable::adpool_counter;i++)
      {
        if (df1b2variable::adpool_vector[i]->nvar == num_active_parameters)
        {
          adpool * tmp = df1b2variable::pool;
          //cout << "Old Depth = " << df1b2variable::pool->depth_check() 
           //    << "  "  << df1b2variable::pool  << "  ";
          df1b2variable::pool=df1b2variable::adpool_vector[i];
          //cout << "Depth = " << df1b2variable::pool->depth_check() 
           //    << "  "  << df1b2variable::pool  << endl;
          df1b2variable::adpool_vector[i]=tmp;
          df1b2variable::nvar_vector[i]=df1b2variable::pool->nvar;
          found_pool_flag=1;
          break;
        }
      }
      if (!found_pool_flag)
      {
        if (df1b2variable::adpool_counter>=df1b2variable::adpool_vectorsize)
        {
           cerr << "Need to increase adpool_vectorsize" << endl;
           ad_exit(1);
        }
        df1b2variable::adpool_vector[df1b2variable::adpool_counter]=
          df1b2variable::pool;
        df1b2variable::nvar_vector[df1b2variable::adpool_counter]=
          df1b2variable::pool->nvar;
        //df1b2variable::adpool_counter++;
        df1b2variable::increment_adpool_counter();
        df1b2variable::pool=new adpool();
        if (!df1b2variable::pool)
        {
          cerr << "Memory allocation error" << endl;
          ad_exit(1);
        } 
      }    
    }
  }
  else
  {
    df1b2variable::pool=new adpool();
    if (!df1b2variable::pool)
    {
      cerr << "Memory allocation error" << endl;
      ad_exit(1);
    } 
  }
  df1b2variable::nvar=num_active_parameters;
  df1b2variable::set_blocksize();
}

#endif //#if defined(USE_LAPLACE)
