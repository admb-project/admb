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
  do_separable_stuff_x_u_block_diagonal(df1b2variable& ff)
{
   // we need g_xu g_uu f_x and f_u
  set_dependent_variable(ff);
  df1b2_gradlist::set_no_derivatives();
  df1b2variable::passnumber=1;
  df1b2_gradcalc1();

  init_df1b2vector & locy= *funnel_init_var::py;
  imatrix& list=*funnel_init_var::plist;

  int us=0; int xs=0;
#ifndef OPT_LIB
  assert(funnel_init_var::num_active_parameters <= INT_MAX);
#endif
  ivector lre_index(1, (int)funnel_init_var::num_active_parameters);
  ivector lfe_index(1, (int)funnel_init_var::num_active_parameters);

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
  dvector local_uadjoint(1,us);

  int* plfe_indexi = lfe_index.get_v() + 1;
  double* plocal_xadjointi = local_xadjoint.get_v() + 1;
  for (int i=1;i<=xs;i++)
  {
    int ii = *plfe_indexi;
    *plocal_xadjointi = (*grad_x_u)(list(ii,1));

    ++plfe_indexi;
    ++plocal_xadjointi;
  }
  int* plre_indexi = lre_index.get_v() + 1;
  double* plocal_uadjointi = local_xadjoint.get_v() + 1;
  for (int i=1;i<=us;i++)
  {
    int ii=*plre_indexi;
    *plocal_uadjointi = (*grad_x_u)(list(ii,1));

    ++plre_indexi;
    ++plocal_uadjointi;
  }
  dvector tmp;
  if (us>0)
  {
    dmatrix local_Hess(1,us,1,us);
    dvector local_grad(1,us);
    dmatrix local_Dux(1,us,1,xs);
    local_Hess.initialize();

    dvector* plocal_Hessi = &local_Hess(1);
    plre_indexi = lre_index.get_v() + 1;
    for (int i=1;i<=us;i++)
    {
      int i2=list(*plre_indexi, 2);

      double* plocal_Hessij = plocal_Hessi->get_v() + 1;
      int* plre_indexj = lre_index.get_v() + 1;
      for (int j=1;j<=us;j++)
      {
        int j2=list(*plre_indexj, 2);
        *plocal_Hessij += locy(i2).u_bar[j2-1];

        ++plocal_Hessij;
        ++plre_indexj;
      }

      ++plocal_Hessi;
      ++plre_indexi;
    }
    dvector* plocal_Duxi = &local_Dux(1);
    plre_indexi = lre_index.get_v() + 1;
    for (int i=1;i<=us;i++)
    {
      int i2=list(*plre_indexi, 2);

      double* plocal_Duxij = plocal_Duxi->get_v() + 1;
      int* plfe_indexj = lfe_index.get_v() + 1;
      for (int j=1;j<=xs;j++)
      {
        int j2=list(*plfe_indexj, 2);
        *plocal_Duxij = locy(i2).u_bar[j2-1];

        ++plfe_indexj;
        ++plocal_Duxij;
      }

      ++plre_indexi;
      ++plocal_Duxi;
    }
    tmp=solve(local_Hess,local_uadjoint)*local_Dux;
  }

  plfe_indexi = lfe_index.get_v() + 1;
  double* ptmpi = tmp.get_v() + 1;
  for (int i=1;i<=xs;i++)
  {
    int ii = *plfe_indexi;
    (*grad_x)(list(ii,1)) += *ptmpi;

    ++plfe_indexi;
    ++ptmpi;
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
Calculates the Laplace approximation for a single separable function
in the "block diagonal", i.e. each u(i) occurs only in a single separable
function.
\param ff value of separable function (???)
This function will be called multiple times (once for each separable function).
Notation: x = fixed effects (parameters) and u = random effects.
*/
void laplace_approximation_calculator::
  do_separable_stuff_laplace_approximation_block_diagonal(df1b2variable& ff)
{
  set_dependent_variable(ff);// Initializs "dot_bar" for reverse mode AD
  df1b2_gradlist::set_no_derivatives();
  df1b2variable::passnumber=1;
  df1b2_gradcalc1();// Forward mode AD follow by a series of reverse sweeps

  // Independent variables for separable function
  init_df1b2vector& locy= *funnel_init_var::py;
  imatrix& list=*funnel_init_var::plist; // Index into "locy"

  int us=0; int xs=0; // us = #u's and xs = #x's
#ifndef OPT_LIB
  assert(funnel_init_var::num_active_parameters <= INT_MAX);
#endif
  ivector lre_index(1, (int)funnel_init_var::num_active_parameters);
  ivector lfe_index(1, (int)funnel_init_var::num_active_parameters);

  // count to find us and xs, and find indexes of fixed and random effects
  for (int i=1;i<=(int)funnel_init_var::num_active_parameters;i++)
  {
    if (list(i,1)>xsize) // x's are stored first in the joint vector
    {
      lre_index(++us)=i;
    }
    else if (list(i,1)>0)
    {
      lfe_index(++xs)=i;
    }
  }

  dvector local_xadjoint(1,xs);  // First order derivative of ff wrt x
  int* plfe_indexj = lfe_index.get_v() + 1;
  for (int j=1;j<=xs;j++)
  {
    int j2=list(*plfe_indexj, 2);
    local_xadjoint(j)=ff.u_dot[j2-1];  // u_dot is the result of forward AD

    ++plfe_indexj;
  }

  if (us>0)
  {
    // Find Hessian matrix needed for Laplace approximation
    dmatrix local_Hess(1,us,1,us);
    dvector local_grad(1,us);
    dmatrix local_Dux(1,us,1,xs);
    local_Hess.initialize();
    dvector local_uadjoint(1,us);

    dvector* plocal_Hessi = &local_Hess(1);
    int* plre_indexi = lre_index.get_v() + 1;
    for (int i=1;i<=us;i++)
    {
      int i2 = list(*plre_indexi, 2);

      double* plocal_Hessij = plocal_Hessi->get_v() + 1;
      int* plre_indexj = lre_index.get_v() + 1;
      for (int j=1;j<=us;j++)
      {
        int j2=list(*plre_indexj, 2);
        *plocal_Hessij += locy(i2).u_bar[j2-1];

	++plocal_Hessij;
        ++plre_indexj;
      }
      ++plocal_Hessi;
      ++plre_indexi;
    }

    // First order derivative of separable function wrt u
    plre_indexi = lre_index.get_v() + 1;
    double* plocal_uadjointi = local_uadjoint.get_v() + 1;
    for (int i=1;i<=us;i++)
    {
      int i2=list(*plre_indexi, 2);
      *plocal_uadjointi = ff.u_dot[i2-1];

      ++plre_indexi;
      ++plocal_uadjointi;
    }

    // Mixed derivatives wrt x and u needed in the sensitivity of u_hat wrt x
    dvector* plocal_Duxi = &local_Dux(1);
    plre_indexi = lre_index.get_v() + 1;
    for (int i=1;i<=us;i++)
    {
      int i2=list(*plre_indexi,2);

      plfe_indexj = lfe_index.get_v() + 1;
      double* plocal_Duxij = plocal_Duxi->get_v() + 1;
      for (int j=1;j<=xs;j++)
      {
        int j2=list(*plfe_indexj, 2);
        *plocal_Duxij = locy(i2).u_bar[j2-1];

	++plocal_Duxij;
        ++plfe_indexj;
      }
      ++plocal_Duxi;
      ++plre_indexi;
    }

    // Enter calculations for the derivative of log(det(Hessian))

    //if (initial_df1b2params::separable_calculation_type==3)
    {
    //int nvar=us*us;
    double f;// 0.5*log(det(local_Hess))
    dmatrix local_Hessadjoint=get_gradient_for_hessian_calcs(local_Hess,f);
    initial_df1b2params::cobjfun+=f;  // Adds 0.5*log(det(local_Hess))

    dvector* pHessadjointi = &local_Hessadjoint(1);
    plre_indexi = lre_index.get_v() + 1;
    for (int i=1;i<=us;i++)
    {
      int i2=list(*plre_indexi, 2);

      double* pHessadjointij = pHessadjointi->get_v() + 1;
      int* plre_indexj = lre_index.get_v() + 1;
      for (int j=1;j<=us;j++)
      {
        int j2=list(*plre_indexj, 2);
        locy(i2).get_u_bar_tilde()[j2-1] = *pHessadjointij;

        ++pHessadjointij;
        ++plre_indexj;
      }

      ++pHessadjointi;
      ++plre_indexi;
    }

     df1b2variable::passnumber=2;
     df1b2_gradcalc1();

     df1b2variable::passnumber=3;
     df1b2_gradcalc1();
      dvector xtmp(1,xs);
      xtmp.initialize();

      int* plfe_indexi = lfe_index.get_v() + 1;
      double* pxtmpi = xtmp.get_v() + 1;
      double* plocal_xadjointi = local_xadjoint.get_v() + 1;
      for (int i=1;i<=xs;i++)
      {
        int i2=list(*plfe_indexi, 2);
        *pxtmpi += locy[i2].u_tilde[0];
        *plocal_xadjointi += locy[i2].u_tilde[0];

	++plfe_indexi;
	++pxtmpi;
	++plocal_xadjointi;
      }

      dvector utmp(1,us);
      utmp.initialize();

      plre_indexi = lre_index.get_v() + 1;
      double* putmpi = utmp.get_v() + 1;
      plocal_uadjointi = local_uadjoint.get_v() + 1;
      for (int i=1;i<=us;i++)
      {
        int i2=list(*plre_indexi, 2);
        *putmpi += locy[i2].u_tilde[0];
        *plocal_uadjointi += locy[i2].u_tilde[0];

	++putmpi;
	++plre_indexi;
	++plocal_uadjointi;
      }
      if (xs>0)
        local_xadjoint -= local_uadjoint*inv(local_Hess)*local_Dux;
    }
  }
  int* plfe_indexi = lfe_index.get_v() + 1;
  double* plocal_xadjointi = local_xadjoint.get_v() + 1;
  for (int i=1;i<=xs;i++)
  {
    int ii = *plfe_indexi;
    // Ads contribution to "global" gradient vector
    xadjoint(list(ii,1)) += *plocal_xadjointi;

    ++plocal_xadjointi;
    ++plfe_indexi;
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
dmatrix laplace_approximation_calculator::get_gradient_for_hessian_calcs
  (const dmatrix& local_Hess,double & f)
{
  int us=local_Hess.indexmax();
  int local_nvar=us*us;
  independent_variables cy(1,local_nvar);
  cy.initialize();

  double* pcyii = cy.get_v() + 1;
  const dvector* plocal_Hessi = &local_Hess(1);
  for (int i=1;i<=us;i++)
  {
    double* plocal_Hessij = plocal_Hessi->get_v() + 1;
    for (int j=1;j<=us;j++)
    {
      *pcyii = *plocal_Hessij;

      ++pcyii;
      ++plocal_Hessij;
    }
    ++plocal_Hessi;
  }

  dvar_vector vy=dvar_vector(cy);
  dvar_matrix vHess(1,us,1,us);

  int ii=1;
  dvar_vector* pvHessi = &vHess(1);
  for (int i=1;i<=us;i++)
  {
    for (int j=1;j<=us;j++)
    {
      (*pvHessi)(j) = vy(ii++);
    }
    ++pvHessi;
  }

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
  dvector g(1,local_nvar);
  gradcalc(local_nvar,g);

  dmatrix hessadjoint(1,us,1,us);

  dvector* phessadjointi = &hessadjoint(1);
  double* pgii = g.get_v() + 1;
  for (int i=1;i<=us;i++)
  {
    double* phessadjointij = phessadjointi->get_v() + 1;
    for (int j=1;j<=us;j++)
    {
      *phessadjointij = *pgii;

      ++phessadjointij;
      ++pgii;
    }

    ++phessadjointi;
  }

  return hessadjoint;
}
