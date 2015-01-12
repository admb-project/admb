/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <df1b2fnl.h>
#include <adrndeff.h>

void laplace_approximation_calculator::
  get_block_diagonal_hessian(df1b2variable& ff)
{
  //***********************************************************
  //***********************************************************
  num_separable_calls++;
  set_dependent_variable(ff);
  df1b2_gradlist::set_no_derivatives();
  df1b2variable::passnumber=1;
  df1b2_gradcalc1();
   
  init_df1b2vector & locy= *funnel_init_var::py;
  imatrix& list=*funnel_init_var::plist;
  int num_local_re=0;
  int num_fixed_effects=0;

  int i;
  //cout << list << endl;
  ivector lre_index(1,funnel_init_var::num_active_parameters);
  ivector lfe_index(1,funnel_init_var::num_active_parameters);

  for (i=1;i<=funnel_init_var::num_active_parameters;i++)
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
    dmatrix& local_Hess=(*block_diagonal_hessian)(num_separable_calls); 
    dmatrix& local_Dux=(*block_diagonal_Dux)(num_separable_calls); 
    ivector& local_re_list=(*block_diagonal_re_list)(num_separable_calls); 
    ivector& local_fe_list=(*block_diagonal_fe_list)(num_separable_calls); 
    local_re_list.initialize();
    local_fe_list.initialize();
    local_Hess.initialize();
    int j;
    for (i=1;i<=num_local_re;i++)
    {
      local_re_list(i)=list(lre_index(i),1);
    }
      
    for (i=1;i<=num_fixed_effects;i++)
    {
      local_fe_list(i)=list(lfe_index(i),1);
    }
      
    for (i=1;i<=num_local_re;i++)
    {
      int lrei=lre_index(i);
      for (j=1;j<=num_local_re;j++)
      {
        int lrej=lre_index(j);
        int i2=list(lrei,2);
        int j2=list(lrej,2);
        local_Hess(i,j)+=locy(i2).u_bar[j2-1];
      }
    }

    for (i=1;i<=num_local_re;i++)
    {
      for (j=1;j<=num_fixed_effects;j++)
      {
        int i2=list(lre_index(i),2);
        int j2=list(lfe_index(j),2);
        local_Dux(i,j)=locy(i2).u_bar[j2-1];
      }
    }
  
    
    have_bounded_random_effects=0;
    if (have_bounded_random_effects)
    {
  
      for (i=1;i<=num_local_re;i++)
      {
        int lrei=lre_index(i);
        int i1=list(lrei,1);
        for (j=1;j<=num_local_re;j++)
        {
          int lrej=lre_index(j);
          int j1=list(lrej,1);
          local_Hess(i,j)*=scale(i1-xsize)*scale(j1-xsize);
        }
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

void laplace_approximation_calculator::
  do_separable_stuff_laplace_approximation_importance_sampling_adjoint
  (df1b2variable& ff)
{
  num_separable_calls++;
  set_dependent_variable(ff);
  //df1b2_gradlist::set_no_derivatives();
  df1b2variable::passnumber=1;
  df1b2_gradcalc1();
   
  init_df1b2vector & locy= *funnel_init_var::py;
  imatrix& list=*funnel_init_var::plist;

  int i; int j; int us=0; int xs=0;
  ivector lre_index(1,funnel_init_var::num_active_parameters);
  ivector lfe_index(1,funnel_init_var::num_active_parameters);

  for (i=1;i<=funnel_init_var::num_active_parameters;i++)
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
  
  dvector local_xadjoint(1,xs);
  
  if (us>0)
  {
    dmatrix local_Hess(1,us,1,us); 
    dvector local_grad(1,us); 
    dmatrix local_Dux(1,us,1,xs); 
    local_Hess.initialize();
    dvector local_uadjoint(1,us);
    for (i=1;i<=us;i++)
    {
      for (j=1;j<=us;j++)
      {
        int i2=list(lre_index(i),2);
        int j2=list(lre_index(j),2);
        local_Hess(i,j)+=locy(i2).u_bar[j2-1];
      }
    }
  
    for (i=1;i<=us;i++)
    {
      for (j=1;j<=xs;j++)
      {
        int i2=list(lre_index(i),2);
        int j2=list(lfe_index(j),2);
        local_Dux(i,j)=locy(i2).u_bar[j2-1];
      }
    }
  
  
    double f=0.0;
    initial_df1b2params::cobjfun+=f;
  
    for (i=1;i<=us;i++)
    {
      for (j=1;j<=us;j++)
      {
        int i2=list(lre_index(i),2);
        int j2=list(lre_index(j),2);
        locy(i2).get_u_bar_tilde()[j2-1]=
          (*block_diagonal_vhessianadjoint)(num_separable_calls)(i,j);
      }
    }
    
    df1b2variable::passnumber=2;
    df1b2_gradcalc1();
  
    df1b2variable::passnumber=3;
    df1b2_gradcalc1();
    dvector xtmp(1,xs);
    xtmp.initialize();

    local_uadjoint.initialize();
    local_xadjoint.initialize();
    for (i=1;i<=xs;i++)
    {
      int i2=list(lfe_index(i),2);
      xtmp(i)+=locy[i2].u_tilde[0];
      local_xadjoint(i)+=locy[i2].u_tilde[0];
    }
    dvector utmp(1,us);
    utmp.initialize();
    for (i=1;i<=us;i++)
    {
      int i2=list(lre_index(i),2);
      utmp(i)+=locy[i2].u_tilde[0];
      local_uadjoint(i)+=locy[i2].u_tilde[0];
    }
    if (xs>0)
      local_xadjoint -= solve(local_Hess,local_uadjoint)*local_Dux;
  }
  for (i=1;i<=xs;i++)
  {
    int ii=lfe_index(i);
    check_local_xadjoint2(list(ii,1))+=local_xadjoint(i);
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

