/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
//#define USE_DD_STUFF
//#define USE_DD
#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h>
double calculate_laplace_approximation(const dvector& x,const dvector& u0,
  const banded_symmetric_dmatrix& bHess,const dvector& _xadjoint,
  const dvector& _uadjoint,
  const banded_symmetric_dmatrix& _bHessadjoint,function_minimizer * pmin);
double calculate_laplace_approximation(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin);

double calculate_importance_sample_shess(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin);

int use_dd_nr=0;
int admb_ssflag=0;
dvector solve(const dmatrix & st,const dmatrix & Hess,
  const dvector& grad);

#if defined(USE_DD_STUFF)
#  if defined(_MSC_VER)
    extern "C" _export  void dd_newton_raphson(int n,double * v,double * diag,
      double * ldiag, double * yy);
#  else
    extern "C" void dd_newton_raphson(int n,double * v,double * diag,
      double * ldiag, double * yy);
#  endif
#endif

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::
  do_newton_raphson_banded(function_minimizer * pfmin,double f_from_1,
  int& no_converge_flag)
{
  //quadratic_prior * tmpptr=quadratic_prior::ptr[0];
  //cout << tmpptr << endl;


  laplace_approximation_calculator::where_are_we_flag=2;
  double maxg=fabs(evaluate_function(uhat,pfmin));


  laplace_approximation_calculator::where_are_we_flag=0;
  dvector uhat_old(1,usize);
  for(int ii=1;ii<=num_nr_iters;ii++)
  {
    // test newton raphson
    switch(hesstype)
    {
    case 3:
      bHess->initialize();
      break;
    case 4:
      Hess.initialize();
      break;
    default:
      cerr << "Illegal value for hesstype here" << endl;
      ad_exit(1);
    }



    grad.initialize();
    //int check=initial_params::stddev_scale(scale,uhat);
    //check=initial_params::stddev_curvscale(curv,uhat);
    //max_separable_g=0.0;
    sparse_count = 0;

    step=get_newton_raphson_info_banded(pfmin);
    //if (bHess)
     // cout << "norm(*bHess) = " << norm(*bHess) << endl;
    //cout << "norm(Hess) = " << norm(Hess) << endl;
    //cout << grad << endl;
    //check_pool_depths();
    if (!initial_params::mc_phase)
      cout << "Newton raphson " << ii << "  ";
    if (quadratic_prior::get_num_quadratic_prior()>0)
    {
      quadratic_prior::get_cHessian_contribution(Hess,xsize);
      quadratic_prior::get_cgradient_contribution(grad,xsize);
    }

    int ierr=0;
    if (hesstype==3)
    {
      if (use_dd_nr==0)
      {
        banded_lower_triangular_dmatrix bltd=choleski_decomp(*bHess,ierr);
        if (ierr && no_converge_flag ==0)
        {
          no_converge_flag=1;
          //break;
        }
        if (ierr)
        {
          double oldval;
          evaluate_function(oldval,uhat,pfmin);
          uhat=banded_calculations_trust_region_approach(uhat,pfmin);
        }
        else
        {
          if (dd_nr_flag==0)
          {
            dvector v=solve(bltd,grad);
            step=-solve_trans(bltd,v);
            //uhat_old=uhat;
            uhat+=step;
          }
          else
          {
#if defined(USE_DD_STUFF)
            int n=grad.indexmax();
            maxg=fabs(evaluate_function(uhat,pfmin));
            uhat=dd_newton_raphson2(grad,*bHess,uhat);
#else
            cerr << "high precision Newton Raphson not implemented" << endl;
            ad_exit(1);
#endif
          }
          maxg=fabs(evaluate_function(uhat,pfmin));
          if (f_from_1< pfmin->lapprox->fmc1.fbest)
          {
            uhat=banded_calculations_trust_region_approach(uhat,pfmin);
            maxg=fabs(evaluate_function(uhat,pfmin));
          }
        }
      }
      else
      {
        cout << "error not used" << endl;
        ad_exit(1);
       /*
        banded_symmetric_ddmatrix bHessdd=banded_symmetric_ddmatrix(*bHess);
        ddvector gradd=ddvector(grad);
        //banded_lower_triangular_ddmatrix bltdd=choleski_decomp(bHessdd,ierr);
        if (ierr && no_converge_flag ==0)
        {
          no_converge_flag=1;
          break;
        }
        if (ierr)
        {
          double oldval;
          evaluate_function(oldval,uhat,pfmin);
          uhat=banded_calculations_trust_region_approach(uhat,pfmin);
          maxg=fabs(evaluate_function(uhat,pfmin));
        }
        else
        {
          ddvector v=solve(bHessdd,gradd);
          step=-make_dvector(v);
          //uhat_old=uhat;
          uhat=make_dvector(ddvector(uhat)+step);
          maxg=fabs(evaluate_function(uhat,pfmin));
          if (f_from_1< pfmin->lapprox->fmc1.fbest)
          {
            uhat=banded_calculations_trust_region_approach(uhat,pfmin);
            maxg=fabs(evaluate_function(uhat,pfmin));
          }
        }
        */
      }

      if (maxg < 1.e-13)
      {
        break;
      }
    }
    else if (hesstype==4)
    {
      dvector step;

#     if defined(USE_ATLAS)
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
        if (!ierr) break;
#     else
        if (sparse_hessian_flag)
        {
          //step=-solve(*sparse_triplet,Hess,grad,*sparse_symbolic);
          dvector temp=solve(*sparse_triplet2,grad,*sparse_symbolic2,ierr);
          if (ierr)
          {
            step=-temp;
          }
          else
          {
            cerr << "matrix not pos definite in sparse choleski"  << endl;
            pfmin->bad_step_flag=1;

            int on;
            int nopt;
            if ((on=option_match(ad_comm::argc,ad_comm::argv,"-ieigvec",nopt))
              >-1)
            {
              dmatrix M=make_dmatrix(*sparse_triplet2);

              ofstream ofs3("inner-eigvectors");
              ofs3 << "eigenvalues and eigenvectors " << endl;
              dvector v=eigenvalues(M);
              dmatrix ev=trans(eigenvectors(M));
              ofs3 << "eigenvectors" << endl;
              int i;
              for (i=1;i<=ev.indexmax();i++)
               {
                  ofs3 << setw(4) << i  << " "
                   << setshowpoint() << setw(14) << setprecision(10) << v(i)
                   << " "
                   << setshowpoint() << setw(14) << setprecision(10)
                   << ev(i) << endl;
               }
            }
          }
          //cout << norm2(step-tmpstep) << endl;
          //dvector step1=-solve(Hess,grad);
          //cout << norm2(step-step1) << endl;
        }
        else
        {
          step=-solve(Hess,grad);
        }
#     endif
      if (pmin->bad_step_flag)
        break;
      uhat_old=uhat;
      uhat+=step;

      double maxg_old=maxg;
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

    if (sparse_hessian_flag==0)
    {
      for (int i=1;i<=usize;i++)
      {
        y(i+xsize)=uhat(i);
      }
    }
    else
    {
      for (int i=1;i<=usize;i++)
      {
        value(y(i+xsize))=uhat(i);
      }
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
double laplace_approximation_calculator::
  inner_optimization_banded(/*dvector& uhat,*/ dvector& x,
  function_minimizer * pfmin,int& no_converge_flag)
{
  if (no_converge_flag)
  {
    no_converge_flag=0;
  }

  if (!inner_lmnflag)
  {
    if (!ADqd_flag)
    {
      uhat=get_uhat_quasi_newton(x,pfmin);
      double maxg=fabs(fmc1.gmax);
      if (maxg>1.0)
      {
        uhat=get_uhat_quasi_newton(x,pfmin);
      }
    }
    else
    {
      uhat=get_uhat_quasi_newton_qd(x,pfmin);
    }
  }
  else
  {
    uhat=get_uhat_lm_newton(x,pfmin);
    //uhat=get_uhat_lm_newton2(x,pfmin);
    //maxg=objective_function_value::gmax;
  }
  return fmc1.fbest;
}

/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::banded_calculations
  (const dvector& _x,const double& _f,function_minimizer * pfmin)
{
  // for use when there is no separability
  ADUNCONST(dvector,x)
  ADUNCONST(double,f)
  //int i,j;
  int i;

  initial_params::set_inactive_only_random_effects();
  gradient_structure::set_NO_DERIVATIVES();
  initial_params::reset(x);    // get current x values into the model
  gradient_structure::set_YES_DERIVATIVES();

  initial_params::set_active_only_random_effects();
  if (init_switch==0)
  {
    gradient_structure::set_NO_DERIVATIVES();
    initial_params::xinit(ubest);
    gradient_structure::set_YES_DERIVATIVES();
  }
  //double maxg;
  //double maxg_save;
  //dvector uhat(1,usize);
  double f_from_1=0.0;

  int no_converge_flag=0;

  // this is the main loop to do inner optimization
  for (;;)
  {
    int icount=0;
    do
    {
      icount++;
      // do the inner optimziation
      if (inner_maxfn>0)
      {
        f_from_1=inner_optimization_banded(/*uhat,*/ x,pfmin,
          no_converge_flag);
      }

      if (sparse_hessian_flag==0)
      {
        for (i=1;i<=xsize;i++) { y(i)=x(i); }
        for (i=1;i<=usize;i++) { y(i+xsize)=uhat(i); }
      }
      else
      {
        for (i=1;i<=xsize;i++) { value(y(i))=x(i); }
        for (i=1;i<=usize;i++) { value(y(i+xsize))=uhat(i); }
      }

      laplace_approximation_calculator::where_are_we_flag=2;
      if (admb_ssflag==0)
      {
        do_newton_raphson_banded(pfmin,f_from_1,no_converge_flag);
      }
      else
      {
        do_newton_raphson_state_space(pfmin,f_from_1,no_converge_flag);
      }
      laplace_approximation_calculator::where_are_we_flag=0;

      if (num_nr_iters<=0) { evaluate_function(uhat,pfmin); }

      if (sparse_hessian_flag==0)
      {
        for (i=1;i<=usize;i++) { y(i+xsize)=uhat(i); }
      }
      else
      {
        for (i=1;i<=usize;i++) { value(y(i+xsize))=uhat(i); }
      }
      if (icount>2) pfmin->bad_step_flag=1;
      if (pfmin->bad_step_flag)
        return xadjoint;
    }
    while(no_converge_flag);

    /* If we are in mcmc phase we just need to calcualte the
       ln_det(Hess) and return
    */
    hs_symbolic & ssymb=*(pmin->lapprox->sparse_symbolic2);
    if (initial_params::mc_phase)
    {
      do_newton_raphson_banded(pfmin,f_from_1,no_converge_flag);
      int sgn=0;
      double& f = (double&) _f;
      f=initial_df1b2params::cobjfun;
     if (pmin->lapprox->sparse_hessian_flag==0)
     {
        if (bHess==0)
        {
          cerr << "Block diagonal Hessian is unallocated" << endl;
          ad_exit(1);
        }
        f+=0.5*ln_det_choleski(*bHess,sgn);
      }
      else
      {
        //hs_symbolic & ssymb=*(pmin->lapprox->sparse_symbolic2);
        //dvariable tmp=0.5*ln_det(*(pmin->lapprox->vsparse_triplet),
        //  ssymb,*(pmin->lapprox->sparse_triplet2));
        f+=0.5*ln_det(*(pmin->lapprox->sparse_triplet2),ssymb);
      }
    }
    else
    {
      xadjoint.initialize();
      uadjoint.initialize();
      Dux.initialize();

      if (hesstype==3)
        bHess->initialize();
      else if (hesstype==4)
        Hess.initialize();

      block_diagonal_flag=2;
      used_flags.initialize();
      funnel_init_var::lapprox=this;
      sparse_count = 0;

      initial_params::straight_through_flag=1;

      if (sparse_triplet2)
        sparse_triplet2->initialize();

      pfmin->user_function();
      initial_params::straight_through_flag=0;

      int ierr=0;

      laplace_approximation_calculator::where_are_we_flag=3;
      if (!ierr)
      {
        if (num_importance_samples==0)
        {
          if (hesstype==3)
          {
            f=calculate_laplace_approximation(x,uhat,*bHess,xadjoint,uadjoint,
              *bHessadjoint,pfmin);
          }
          else if (hesstype==4)
          {
            //cout << "Hess" << endl << Hess << endl;
            f=calculate_laplace_approximation(x,uhat,Hess,xadjoint,uadjoint,
              Hessadjoint,pfmin);
          }
          else
          {
            cerr << "Error in hesstype" << endl;
            ad_exit(1);
          }
        }
        else
        {
          if (hesstype==3)
          {
            //cerr << "Error not implemented yet" << endl;
            //ad_exit(1);
            f=calculate_importance_sample(x,uhat,*bHess,xadjoint,uadjoint,
              *bHessadjoint,pfmin);
          }
          else if (hesstype==4)
          {
            if (pmin->lapprox->sparse_hessian_flag==0)
              f=calculate_importance_sample(x,uhat,Hess,xadjoint,uadjoint,
                Hessadjoint,pfmin);
            else
              f=calculate_importance_sample_shess(x,uhat,Hess,xadjoint,uadjoint,
                Hessadjoint,pfmin);
          }
          else
          {
            cerr << "Error in hesstype" << endl;
            ad_exit(1);
          }
        }
      }
      else
      {
        f=1.e+30;
      }

      // set flag for thrid erivatvies and call function again because
      // stack is wiped out

      if (hesstype==3)
      {
        bHess->initialize();
      }
      else if (hesstype==4)
      {
        if (sparse_hessian_flag==0)
        {
          Hess.initialize();
        }
        else
        {
          sparse_triplet2->initialize();
        }
      }
      else
      {
        cerr << "Illegal value for hesstype" << endl;
        ad_exit(1);
      }
      initial_params::straight_through_flag=1;
      block_diagonal_flag=3;
      local_dtemp.initialize();

      // *****  Note for quadratic prior code: I don't think that this
      // part gets added to the Hessian here.
      sparse_count=0;
      sparse_count_adjoint=0;
      pfmin->user_function();

      // *** Hessian calculated just above did not have quadratic prior
      // in it so can save this part for quadratci prioer adjoint calculations
      if (quadratic_prior::get_num_quadratic_prior()>0)
      {
        if (pHess_non_quadprior_part)
        {
          if (pHess_non_quadprior_part->indexmax() != Hess.indexmax())
          {
            delete pHess_non_quadprior_part;
            pHess_non_quadprior_part=0;
          }
        }
        if (!pHess_non_quadprior_part)
        {
          pHess_non_quadprior_part=new dmatrix(1,usize,1,usize);
          if (!pHess_non_quadprior_part)
          {
            cerr << "Error allocating memory for Hesssian part" << endl;
            ad_exit(1);
          }
        }
        (*pHess_non_quadprior_part)=Hess;
      }

      block_diagonal_flag=0;
      initial_params::straight_through_flag=1;

      //dmatrix tHess=dmatrix(*bHess);
      initial_params::straight_through_flag=0;
      funnel_init_var::lapprox=0;
      //cout << initial_df1b2params::cobjfun << endl;
      //f=initial_df1b2params::cobjfun;
      block_diagonal_flag=0;
      dvector scale1(1,nvar);   // need to get scale from somewhere
      initial_params::set_inactive_only_random_effects();
      /*int check=*/initial_params::stddev_scale(scale1,x);
      //for (i=1;i<=xadjoint.indexmax();i++)
      //  xadjoint(i)*=scale1(i);
      laplace_approximation_calculator::where_are_we_flag=0;

      if (df1b2quadratic_prior::get_num_quadratic_prior()>0)
      {
       // !!!! need to fix this!!!!!!!!!!!!!!!!!!!!!!!
        laplace_approximation_calculator::where_are_we_flag=3;
        quadratic_prior::in_qp_calculations=1;
        funnel_init_var::lapprox=this;
        df1b2_gradlist::set_no_derivatives();
        df1b2quadratic_prior::get_Lxu_contribution(Dux);
        quadratic_prior::in_qp_calculations=0;
        funnel_init_var::lapprox=0;
        laplace_approximation_calculator::where_are_we_flag=0;
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
        local_dtemp=elem_prod(local_dtemp,sscale);
      }
      //cout << trans(Dux)(1) << endl;
      //cout << trans(Dux)(3) << endl;
      if (quadratic_prior::get_num_quadratic_prior()>0)
      {
        dvector tmp=evaluate_function_with_quadprior(x,usize,pfmin);
        local_dtemp+=tmp;
      }

      for (i=1;i<=xsize;i++)
      {
        xadjoint(i)+=local_dtemp(i);
      }
      if (df1b2quadratic_prior::get_num_quadratic_prior()>0)
      {
       // !!!! need to fix this!!!!!!!!!!!!!!!!!!!!!!!
        quadratic_prior::get_cHessian_contribution_from_vHessian(Hess,xsize);
      }

      if (hesstype==3)
      {
        //xadjoint -= uadjoint*solve(*bHess,Dux);
        if (bHess_pd_flag==0)
        {
          xadjoint -= solve(*bHess,uadjoint)*Dux;
        }
      }
      else if (hesstype==4)
      {
        if (sparse_hessian_flag)
        {
//dvector tmp=solve(*sparse_triplet,Hess,uadjoint,*sparse_symbolic)*Dux;
          dvector tmp=solve(*sparse_triplet2,uadjoint,*sparse_symbolic2)*Dux;
          xadjoint -= tmp;
        }
        else
        {
          xadjoint -= solve(Hess,uadjoint)*Dux;
        }
      }
    }
    if (bHess_pd_flag==0) break;
  }

  return xadjoint;
}
  //int check_pool_flag1=0;

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::
  do_separable_stuff_newton_raphson_banded(df1b2variable& ff)
{
  //***********************************************************
  //***********************************************************
  set_dependent_variable(ff);
  df1b2_gradlist::set_no_derivatives();
  df1b2variable::passnumber=1;
  //if (check_pool_flag1)
   // check_pool_depths();
  df1b2_gradcalc1();
  //if (check_pool_flag1)
  //  check_pool_depths();

  init_df1b2vector & locy= *funnel_init_var::py;
  imatrix& list=*funnel_init_var::plist;
  int num_local_re=0;
  int num_fixed_effects=0;

  ivector lre_index(1,funnel_init_var::num_active_parameters);
  ivector lfe_index(1,funnel_init_var::num_active_parameters);

  for (int i=1;i<=funnel_init_var::num_active_parameters;i++)
  {
    if (list(i,1)>xsize)
    {
      lre_index(++num_local_re)=i;
    }
    else if (list(i,1)>0)
    {
      lfe_index(++num_fixed_effects)=i;
    }
  }

  if (num_local_re > 0)
  {
    switch(hesstype)
    {
    case 3:
      for (int i=1;i<=num_local_re;i++)
      {
        int lrei=lre_index(i);
        for (int j=1;j<=num_local_re;j++)
        {
          int lrej=lre_index(j);
          int i1=list(lrei,1)-xsize;
          int i2=list(lrei,2);
          int j1=list(lrej,1)-xsize;
          int j2=list(lrej,2);
          if (i1>=j1) (*bHess)(i1,j1)+=locy(i2).u_bar[j2-1];
        }
      }
      break;
    case 4:
      if (sparse_hessian_flag==0)
      {
        for (int i=1;i<=num_local_re;i++)
        {
          int lrei=lre_index(i);
          for (int j=1;j<=num_local_re;j++)
          {
            int lrej=lre_index(j);
            int i1=list(lrei,1)-xsize;
            int i2=list(lrei,2);
            int j1=list(lrej,1)-xsize;
            int j2=list(lrej,2);
            Hess(i1,j1)+=locy(i2).u_bar[j2-1];
          }
        }
      }
      else
      {
        for (int i=1;i<=num_local_re;i++)
        {
          int lrei=lre_index(i);
          for (int j=1;j<=num_local_re;j++)
          {
            int lrej=lre_index(j);
            int i1=list(lrei,1)-xsize;
            int i2=list(lrei,2);
            int j1=list(lrej,1)-xsize;
            int j2=list(lrej,2);

            if (i1<=j1)
            {
              sparse_count++;
              (*sparse_triplet2)((*sparse_iterator)(sparse_count))
                +=locy(i2).u_bar[j2-1];
            }
          }
        }
      }
      break;
    default:
      cerr << "illegal value for hesstype" << endl;
      ad_exit(1);
    }

    for (int i=1;i<=num_local_re;i++)
    {
      int lrei=lre_index(i);
      int i1=list(lrei,1);
      int i2=list(lrei,2);
      //grad(i1-xsize)= re_objective_function_value::pobjfun->u_dot[i2-1];
      grad(i1-xsize)+=ff.u_dot[i2-1];
    }
  }

  f1b2gradlist->reset();
  f1b2gradlist->list.initialize();
  f1b2gradlist->list2.initialize();
  f1b2gradlist->list3.initialize();
  f1b2gradlist->nlist.initialize();
  f1b2gradlist->nlist2.initialize();
  f1b2gradlist->nlist3.initialize();
  funnel_init_var::num_vars=0;
  funnel_init_var::num_active_parameters=0;
  funnel_init_var::num_inactive_vars=0;
}
//int tmp_testcount=0;
df1b2variable * tmp_pen=00;

/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::
  get_newton_raphson_info_banded (function_minimizer * pfmin)
{
  int nv=initial_df1b2params::set_index();
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

  for (int ip=1;ip<=num_der_blocks;ip++)
  {
    if (ip>1)   // change to combine sparse matrix stuff with num der blocks
    {           // df  3-4-09
      sparse_count=0;
    }
    used_flags.initialize();
    // do we need to reallocate memory for df1b2variables?
    check_for_need_to_reallocate(ip);
    df1b2_gradlist::set_no_derivatives();
    //cout << re_objective_function_value::pobjfun << endl;
    //cout << re_objective_function_value::pobjfun->ptr << endl;
    (*re_objective_function_value::pobjfun)=0;
    df1b2variable pen=0.0;
    tmp_pen=&pen;
    df1b2variable zz=0.0;

    initial_df1b2params::reset(y,pen);

    // call function to do block diagonal newton-raphson
    // the step vector from the newton-raphson is in the vector step
    df1b2_gradlist::set_yes_derivatives();

    funnel_init_var::lapprox=this;
    //cout << funnel_init_var::lapprox << endl;
    block_diagonal_flag=1;
   /*
    tmp_testcount++;
    if (tmp_testcount>=9)
    {
      pen.deallocate();
    }
    */

    if (ip==1)
    {
      if (sparse_triplet2)
        sparse_triplet2->initialize();
    }

    pfmin->user_function();
    /*
    if (tmp_testcount>=9)
    {
      pen.deallocate();
    }
     */
    funnel_init_var::lapprox=0;
    block_diagonal_flag=0;
    pen.deallocate();
  }

  return step;
}

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::
  do_separable_stuff_laplace_approximation_banded(df1b2variable& ff)
{
  set_dependent_variable(ff);
  //df1b2_gradlist::set_no_derivatives();
  df1b2variable::passnumber=1;
  df1b2_gradcalc1();

  init_df1b2vector & locy= *funnel_init_var::py;
  imatrix& list=*funnel_init_var::plist;

  int us=0; int xs=0;
  ivector lre_index(1,funnel_init_var::num_active_parameters);
  ivector lfe_index(1,funnel_init_var::num_active_parameters);

  for (int i=1;i<=funnel_init_var::num_active_parameters;i++)
  {
    if (list(i,1)>xsize)
    {
      lre_index(++us)=i;
    }
    else if (list(i,1)>0)
    {
      lfe_index(++xs)=i;
    }
  }

  for (int j=1;j<=xs;j++)
  {
    int j1=list(lfe_index(j),1);
    int j2=list(lfe_index(j),2);
    xadjoint(j1)+=ff.u_dot[j2-1];
  }

  if (us>0)
  {
    if (hesstype==3)
    {
      for (int i=1;i<=us;i++)
      {
        for (int j=1;j<=us;j++)
        {
          int i1=list(lre_index(i),1)-xsize;
          int i2=list(lre_index(i),2);
          int j1=list(lre_index(j),1)-xsize;
          int j2=list(lre_index(j),2);
          if (i1>=j1) (*bHess)(i1,j1)+=locy(i2).u_bar[j2-1];
        }
      }
    }
    else if (hesstype==4)
    {
      if (sparse_hessian_flag==0)
      {
        for (int i=1;i<=us;i++)
        {
          for (int j=1;j<=us;j++)
          {
            int i1=list(lre_index(i),1)-xsize;
            int i2=list(lre_index(i),2);
            int j1=list(lre_index(j),1)-xsize;
            int j2=list(lre_index(j),2);
            Hess(i1,j1)+=locy(i2).u_bar[j2-1];
          }
        }
      }
      else
      {
        for (int i=1;i<=us;i++)
        {
          for (int j=1;j<=us;j++)
          {
            int i1=list(lre_index(i),1)-xsize;
            int i2=list(lre_index(i),2);
            int j1=list(lre_index(j),1)-xsize;
            int j2=list(lre_index(j),2);

            if (i1<=j1)
            {
              sparse_count++;
              (*sparse_triplet2)((*sparse_iterator)(sparse_count))
                +=locy(i2).u_bar[j2-1];
            }
          }
        }
      }
    }

    for (int i=1;i<=us;i++)
    {
      int i1=list(lre_index(i),1)-xsize;
      int i2=list(lre_index(i),2);
      uadjoint(i1)+=ff.u_dot[i2-1];
    }

    for (int i=1;i<=us;i++)
    {
      for (int j=1;j<=xs;j++)
      {
        int i1=list(lre_index(i),1)-xsize;
        int i2=list(lre_index(i),2);
        int j1=list(lfe_index(j),1);
        int j2=list(lfe_index(j),2);
        Dux(i1,j1)+=locy(i2).u_bar[j2-1];
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
  funnel_init_var::num_vars=0;
  funnel_init_var::num_active_parameters=0;
  funnel_init_var::num_inactive_vars=0;
}

/**
 * Description not yet available.
 * \param
 */
double calculate_laplace_approximation(const dvector& x,const dvector& u0,
  const banded_symmetric_dmatrix& bHess,const dvector& _xadjoint,
  const dvector& _uadjoint,
  const banded_symmetric_dmatrix& _bHessadjoint,function_minimizer * pmin)
{
  ADUNCONST(dvector,xadjoint)
  ADUNCONST(dvector,uadjoint)
  ADUNCONST(banded_symmetric_dmatrix,bHessadjoint)
  int bw=bHess.bandwidth();
  const int xs=x.size();
  const int us=u0.size();
  gradient_structure::set_YES_DERIVATIVES();
  int nvar=x.size()+u0.size()+((bw+1)*(2*u0.size()-bw))/2;
  independent_variables y(1,nvar);

  // need to set random effects active together with whatever
  // init parameters should be active in this phase
  initial_params::set_inactive_only_random_effects();
  initial_params::set_active_random_effects();
  /*int onvar=*/initial_params::nvarcalc();
  initial_params::xinit(y);    // get the initial values into the
  y(1,xs)=x;

 // Here need hooks for sparse matrix structures
  int ii=xs+us+1;
  for (int i=1;i<=us;i++)
  {
    int jmin=admax(1,i-bw+1);
    for (int j=jmin;j<=i;j++)
      y(ii++)=bHess(i,j);
  }

  dvar_vector vy=dvar_vector(y);
  banded_symmetric_dvar_matrix vHess(1,us,bw);
  initial_params::reset(vy);    // get the initial values into the
  ii=xs+us+1;
  for (int i=1;i<=us;i++)
  {
    int jmin=admax(1,i-bw+1);
    for (int j=jmin;j<=i;j++)
      vHess(i,j)=vy(ii++);
  }

   dvariable vf=0.0;

   *objective_function_value::pobjfun=0.0;
   pmin->AD_uf_outer();
   vf+=*objective_function_value::pobjfun;

   int sgn=0;
   dvariable ld;

   int eigswitch=0;
   if (eigswitch)
   {
     ofstream ofs("ee");
     dvector ev(bHess.indexmin(),bHess.indexmax());
     dmatrix evecs=eigenvectors(dmatrix(bHess),ev);
     ofs << setprecision(3) << setw(12) << setscientific() << dmatrix(bHess)
         << endl << endl;
     ofs << ev << endl << endl << evecs << endl;
   }
   ld=0.5*ln_det_choleski(vHess,sgn);
   if (sgn==1)
   {
     cout << "Choleski failed" << endl;
     pmin->lapprox->bHess_pd_flag=1;
   }

   vf+=ld;
   const double ltp=0.5*log(2.0*PI);
   vf-=us*ltp;
   double f=value(vf);
   dvector g(1,nvar);
   gradcalc(nvar,g);

  ii=1;
  for (int i=1;i<=xs;i++)
    xadjoint(i)=g(ii++);
  for (int i=1;i<=us;i++)
    uadjoint(i)=g(ii++);
  for (int i=1;i<=us;i++)
  {
    int jmin=admax(1,i-bw+1);
    for (int j=jmin;j<=i;j++)
      bHessadjoint(i,j)=g(ii++);
  }
  return f;
}

/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::
  banded_calculations_trust_region_approach(const dvector& _uhat,
  function_minimizer * pfmin)
{
  dvector& uhat=(dvector&) _uhat;
  dvector uhat_old(uhat.indexmin(),uhat.indexmax());
  dvector uhat_new(uhat.indexmin(),uhat.indexmax());
  dvector uhat_best(uhat.indexmin(),uhat.indexmax());

  double wght=0.0;
  double delta=5.e-5;
  //do
  dvector values(1,300);
  double oldfbest=pmin->lapprox->fmc1.fbest;
  double newfbest = 0.0;
  int have_value=0;
  //for (int jj=1;jj<=300;jj++)
  int jj=1;
  double lastval=oldfbest;
  do
  {
    jj++;
    wght+=delta;
    //double wght=0.0;
    double newval=0.0;
    //cout << "Enter weight size " << endl;
    //cin >> wght;
    if (wght<0.0)
      break;
    int mmin=bHess->indexmin();
    int mmax=bHess->indexmax();
    banded_symmetric_dmatrix tmp(mmin,mmax,bHess->bandwidth());
    tmp=*bHess;
    uhat_old=uhat;
    int ierr=0;
    for (int i=mmin;i<=mmax;i++)
    {
      tmp(i,i)+=wght;
    }
    banded_lower_triangular_dmatrix bltd=choleski_decomp(tmp,ierr);
    if (!ierr)
    {
      dvector v=solve(bltd,grad);
      step=-solve_trans(bltd,v);

      uhat_old=uhat;
      uhat+=step;
      //cout << "norm(uhat_old) = " << norm(uhat_old)
       //    << "   norm(uhat) = " << norm(uhat)  << endl;

      /*double maxg=*/evaluate_function(newval,uhat,pfmin);
      if (have_value && newval>newfbest)
      {
        break;
      }
      if (jj>1)
      {
        if (newval<lastval)  // we are doing better so increasse step size
        {
          delta*=2;
        }
        if (newval>lastval && !have_value)  // we have gone to far go back
        {
          wght-=delta;
          delta/=16;
        }
      }
      lastval=newval;

      if (newval<newfbest)
      {
        newfbest=newval;
        uhat_best=uhat;
        have_value=jj;
      }
      uhat_new=uhat;
      uhat=uhat_old;
    }
    else
    {
      delta*=2;
    }
  }
  while(jj<10);
  if (!have_value)
  {
    cerr << "can't improve function value in trust region calculations"
         << endl;
    //ad_exit(1);
  }
  return uhat_best;
  initial_params::set_active_only_random_effects();
  if (!inner_lmnflag)
  {
    if (!ADqd_flag)
    {
      uhat=get_uhat_quasi_newton(uhat_new,pfmin);
      //double maxg=fabs(fmc1.gmax);
      //double f_from_1=fmc1.fbest;
    }
    else
    {
      uhat=get_uhat_quasi_newton_qd(uhat_new,pfmin);
    }
  }
  else
  {
    uhat=get_uhat_lm_newton(uhat_new,pfmin);
  }
  return uhat;
}
