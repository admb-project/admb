/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <df1b2fnl.h>
#include <adrndeff.h>


void laplace_approximation_calculator::
  do_separable_stuff_x_u_block_diagonal(df1b2variable& ff)
{
   // we need g_xu g_uu f_x and f_u
  set_dependent_variable(ff);
  df1b2_gradlist::set_no_derivatives();
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
  dvector local_uadjoint(1,us);
  for (i=1;i<=xs;i++)
  {
    int ii=lfe_index(i);
    local_xadjoint(i)=(*grad_x_u)(list(ii,1));
  }
  for (i=1;i<=us;i++)
  {
    int ii=lre_index(i);
    local_uadjoint(i)=(*grad_x_u)(list(ii,1));
  }
  dvector tmp;
  if (us>0)
  {
    dmatrix local_Hess(1,us,1,us); 
    dvector local_grad(1,us); 
    dmatrix local_Dux(1,us,1,xs); 
    local_Hess.initialize();
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
    tmp=solve(local_Hess,local_uadjoint)*local_Dux;
  }

  for (i=1;i<=xs;i++)
  {
    int ii=lfe_index(i);
    (*grad_x)(list(ii,1))+=tmp(i);
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
  do_separable_stuff_laplace_approximation_block_diagonal(df1b2variable& ff)
{
  set_dependent_variable(ff);
  df1b2_gradlist::set_no_derivatives();
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
  for (j=1;j<=xs;j++)
  {
    int j2=list(lfe_index(j),2);
    local_xadjoint(j)=ff.u_dot[j2-1];
  }
  
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
      int i2=list(lre_index(i),2);
      local_uadjoint(i)= ff.u_dot[i2-1];
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
  
  
    //if (initial_df1b2params::separable_calculation_type==3)
    {
  
    //int nvar=us*us;
    double f;
    dmatrix Hessadjoint=get_gradient_for_hessian_calcs(local_Hess,f);
    initial_df1b2params::cobjfun+=f;
  
    for (i=1;i<=us;i++)
    {
      for (j=1;j<=us;j++)
      {
        int i2=list(lre_index(i),2);
        int j2=list(lre_index(j),2);
        locy(i2).get_u_bar_tilde()[j2-1]=Hessadjoint(i,j);
      }
    }
    
     df1b2variable::passnumber=2;
     df1b2_gradcalc1();
  
     df1b2variable::passnumber=3;
     df1b2_gradcalc1();
      dvector xtmp(1,xs);
      xtmp.initialize();
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
        local_xadjoint -= local_uadjoint*inv(local_Hess)*local_Dux;
    }
  }
  for (i=1;i<=xs;i++)
  {
    int ii=lfe_index(i);
    xadjoint(list(ii,1))+=local_xadjoint(i);
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


dmatrix laplace_approximation_calculator::get_gradient_for_hessian_calcs
  (const dmatrix& local_Hess,double & f)
{
  int us=local_Hess.indexmax();
  int nvar=us*us;
  independent_variables cy(1,nvar);
  cy.initialize();
  int ii=1; int i,j;
  for (i=1;i<=us;i++)
    for (j=1;j<=us;j++)
      cy(ii++)=local_Hess(i,j);

  dvar_vector vy=dvar_vector(cy); 
  dvar_matrix vHess(1,us,1,us);
  
  ii=1;
  for (i=1;i<=us;i++)
    for (j=1;j<=us;j++)
      vHess(i,j)=vy(ii++);

  dvariable vf=0.0;
  int sgn=0;
  if (pmin->multinomial_weights==0)
  {
    vf+=0.5*ln_det(vHess,sgn);
  }
  else
  {
    dvector & w= *(pmin->multinomial_weights); 
    double w_i=w[separable_calls_counter];
    double d=vHess.indexmax()-vHess.indexmin()+1;
    vf+=w_i*(0.5*ln_det(vHess,sgn)-0.5*d*log(w_i));
    vf-=w_i*d*.91893853320467241; 
  }
  f=value(vf);
  dvector g(1,nvar);
  gradcalc(nvar,g);
  dmatrix hessadjoint(1,us,1,us);
  ii=1;
  for (i=1;i<=us;i++)
    for (j=1;j<=us;j++)
      hessadjoint(i,j)=g(ii++);

  return hessadjoint;
}
  
