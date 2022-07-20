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
#include <df1b2fnl.h>
#include <adrndeff.h>
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

/**
 * Description not yet available.
 * \param
 */
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

  //cout << list << endl;
#ifndef OPT_LIB
  assert(funnel_init_var::num_active_parameters <= INT_MAX);
#endif
  ivector lre_index(1,(int)funnel_init_var::num_active_parameters);
  ivector lfe_index(1,(int)funnel_init_var::num_active_parameters);

  for (int i=1;i<=(int)funnel_init_var::num_active_parameters;i++)
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

    int* plocal_re_listi = local_re_list.get_v() + 1;
    int* plre_indexi = lre_index.get_v() + 1;
    for (int i = 1;i <= num_local_re; ++i)
    {
      *plocal_re_listi = list(*plre_indexi, 1);

      ++plocal_re_listi;
      ++plre_indexi;
    }

    int* plocal_fe_listi = local_fe_list.get_v() + 1;
    int* plfe_indexi = lfe_index.get_v() + 1;
    for (int i=1;i<=num_fixed_effects;i++)
    {
      *plocal_fe_listi = list(*plfe_indexi, 1);

      ++plocal_fe_listi;
      ++plfe_indexi;
    }

    dvector* plocal_Hessi = &local_Hess(1);
    plre_indexi = lre_index.get_v() + 1;
    for (int i=1;i<=num_local_re;i++)
    {
      int lrei = *plre_indexi;
      int i2=list(lrei,2);

      double* plocal_Hessij = plocal_Hessi->get_v() + 1;
      int* plre_indexj = lre_index.get_v() + 1;
      for (int j=1;j<=num_local_re;j++)
      {
        int lrej = *plre_indexj;
        int j2=list(lrej,2);

        *plocal_Hessij += locy(i2).u_bar[j2-1];

	++plocal_Hessij;
        ++plre_indexj;
      }

      ++plocal_Hessi;
      ++plre_indexi;
    }

    dvector* plocal_Duxi = &local_Dux(1);
    plre_indexi = lre_index.get_v() + 1;
    for (int i=1;i<=num_local_re;i++)
    {
      int i2=list(*plre_indexi, 2);

      double* plocal_Duxij = plocal_Duxi->get_v() + 1;
      int* plfe_indexj = lfe_index.get_v() + 1;
      for (int j=1;j<=num_fixed_effects;j++)
      {
        int j2=list(*plfe_indexj, 2);
        *plocal_Duxij = locy(i2).u_bar[j2-1];

	++plocal_Duxij;
        ++plfe_indexj;
      }

      ++plocal_Duxi;
      ++plre_indexi;
    }

    have_bounded_random_effects=0;
    if (have_bounded_random_effects)
    {
      plocal_Hessi = &local_Hess(1);
      plre_indexi = lre_index.get_v() + 1;
      for (int i=1;i<=num_local_re;i++)
      {
        int lrei = *plre_indexi;
        int i1=list(lrei,1);
        double* plocal_Hessij = plocal_Hessi->get_v() + 1;
        int* plre_indexj = lre_index.get_v() + 1;
        for (int j=1;j<=num_local_re;j++)
        {
          int lrej = *plre_indexj;
          int j1=list(lrej,1);
          *plocal_Hessij *= scale(i1-xsize)*scale(j1-xsize);

	  ++plocal_Hessij;
          ++plre_indexj;
        }
        ++plocal_Hessi;
        ++plre_indexi;
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

  int us=0; int xs=0;
#ifndef OPT_LIB
  assert(funnel_init_var::num_active_parameters <= INT_MAX);
#endif
  ivector lre_index(1,(int)funnel_init_var::num_active_parameters);
  ivector lfe_index(1,(int)funnel_init_var::num_active_parameters);

  for (int i=1;i<=(int)funnel_init_var::num_active_parameters;i++)
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
    for (int i=1;i<=us;i++)
    {
      for (int j=1;j<=us;j++)
      {
        int i2=list(lre_index(i),2);
        int j2=list(lre_index(j),2);
        local_Hess(i,j)+=locy(i2).u_bar[j2-1];
      }
    }

    for (int i=1;i<=us;i++)
    {
      for (int j=1;j<=xs;j++)
      {
        int i2=list(lre_index(i),2);
        int j2=list(lfe_index(j),2);
        local_Dux(i,j)=locy(i2).u_bar[j2-1];
      }
    }

    double f=0.0;
    initial_df1b2params::cobjfun+=f;

    for (int i=1;i<=us;i++)
    {
      for (int j=1;j<=us;j++)
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
    for (int i=1;i<=xs;i++)
    {
      int i2=list(lfe_index(i),2);
      xtmp(i)+=locy[i2].u_tilde[0];
      local_xadjoint(i)+=locy[i2].u_tilde[0];
    }
    dvector utmp(1,us);
    utmp.initialize();
    for (int i=1;i<=us;i++)
    {
      int i2=list(lre_index(i),2);
      utmp(i)+=locy[i2].u_tilde[0];
      local_uadjoint(i)+=locy[i2].u_tilde[0];
    }
    if (xs>0)
      local_xadjoint -= solve(local_Hess,local_uadjoint)*local_Dux;
  }
  for (int i=1;i<=xs;i++)
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
