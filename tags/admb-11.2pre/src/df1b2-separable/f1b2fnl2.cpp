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

int pool_check_flag=0;

extern int noboundepen_flag;

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::do_separable_stuff(void)
{
  df1b2variable& ff=  *re_objective_function_value::pobjfun;
  if (block_diagonal_flag==0)
  {
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
    if (funnel_init_var::funnel_constraints_penalty)
    {
      delete funnel_init_var::funnel_constraints_penalty;
      funnel_init_var::funnel_constraints_penalty=0;
    }
    return;
  }
  if (funnel_init_var::funnel_constraints_penalty)
  {
    if (noboundepen_flag==0)
    {
      ff+=*funnel_init_var::funnel_constraints_penalty;
    }
    delete funnel_init_var::funnel_constraints_penalty;
    funnel_init_var::funnel_constraints_penalty=0;
  }

  // this should not be called a block diagopnal flag but it is for now.
  //if (pool_check_flag)
   // check_pool_depths();
  switch (block_diagonal_flag)
  {
  case 1:
    switch(hesstype)
    {
    case 2:
      do_separable_stuff_newton_raphson_block_diagonal(ff);
      break;
    case 3: //banded
    case 4: // full matrix
      do_separable_stuff_newton_raphson_banded(ff);
  //if (pool_check_flag)
   // check_pool_depths();
      break;
    default:
       cerr << "Illegal value for hesstype" << endl;
       ad_exit(1);
    }
    break;
  case 2:
    switch(hesstype)
    {
    case 2:
      ++separable_calls_counter;
      if (saddlepointflag==2)
      {
        do_separable_stuff_x_u_block_diagonal(ff);
      }
      else
      {
        do_separable_stuff_laplace_approximation_block_diagonal(ff);
      }
      break;
    case 3:
    case 4: // full matrix
      do_separable_stuff_laplace_approximation_banded(ff);
      break;
    default:
       cerr << "Illegal value for hesstype" << endl;
       ad_exit(1);
    }
    break;
  case 3:
    switch(hesstype)
    {
    case 2:
      do_separable_stuff_laplace_approximation_importance_sampling_adjoint(ff);
      break;
    case 3:
    case 4: // full matrix
      do_separable_stuff_laplace_approximation_banded_adjoint(ff);
      break;
    default:
       cerr << "Illegal value for hesstype" << endl;
       ad_exit(1);
    }
    break;
  case 5:   // get hessian type information
      do_separable_stuff_hessian_type_information();
      break;
  case 6:   // get hessian type information
      get_block_diagonal_hessian(ff);
      break;
  default:
    cerr << "illegal value for block_diagonal_flag = "
      << block_diagonal_flag << endl;
    ad_exit(1);
  }
  df1b2variable::pool=df1b2variable::adpool_vector[0];
  df1b2variable::nvar=df1b2variable::pool->nvar;
  if  (df1b2variable::pool->size<=0)
  {
    cerr << "this can't happen" << endl;
    ad_exit(1);
  }
}

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::
  do_separable_stuff_newton_raphson_block_diagonal(df1b2variable& ff)
{
  //***********************************************************
  //***********************************************************
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
  ivector lre_index(1, (int)funnel_init_var::num_active_parameters);
  ivector lfe_index(1, (int)funnel_init_var::num_active_parameters);

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
    //cout << " num_local_re = " << num_local_re << endl;
    //cout << " num_fixed_effects = " << num_fixed_effects << endl;
    //cout << " list = " << endl << list << endl;
    //cout << " lre_index= " << endl <<  lre_index << endl;
    //cout << " lfe_index= " << endl <<  lfe_index << endl;
    //cout << "the number of local res is " << num_local_re << endl;
    dmatrix local_Hess(1,num_local_re,1,num_local_re);
    dvector local_grad(1,num_local_re);
    //dmatrix local_Dux(1,num_local_re,1,
     // funnel_init_var::num_active_parameters-num_local_re);
    //dmatrix Hess1(1,funnel_init_var::num_vars,1,funnel_init_var::num_vars);
    local_Hess.initialize();

    for (int i=1;i<=num_local_re;i++)
    {
      int lrei=lre_index(i);
      for (int j=1;j<=num_local_re;j++)
      {
        int lrej=lre_index(j);
        int i2=list(lrei,2);
        int j2=list(lrej,2);
        //Hess(i1-xsize,j1-xsize)+=locy(i2).u_bar[j2-1];
        local_Hess(i,j)+=locy(i2).u_bar[j2-1];
      }
    }
     // i<=funnel_init_var::num_vars;i++)
    for (int i=1;i<=num_local_re;i++)
    {
      int lrei=lre_index(i);
      //int i1=list(lrei,1);
      int i2=list(lrei,2);
      //grad(i1-xsize)= re_objective_function_value::pobjfun->u_dot[i2-1];
      //grad(i1-xsize)= ff.u_dot[i2-1];
      local_grad(i)= ff.u_dot[i2-1];
    }

    have_bounded_random_effects=0;
    if (have_bounded_random_effects)
    {
      for (int i=1;i<=num_local_re;i++)
      {
        int lrei=lre_index(i);
        int i1=list(lrei,1);
        for (int j=1;j<=num_local_re;j++)
        {
          int lrej=lre_index(j);
          int j1=list(lrej,1);
          local_Hess(i,j)*=scale(i1-xsize)*scale(j1-xsize);
        }
      }

      for (int i=1;i<=num_local_re;i++)
      {
        int lrei=lre_index(i);
        int i1=list(lrei,1);
        local_Hess(i,i)+=local_grad(i)*curv(i1-xsize);
      }

      for (int i=1;i<=num_local_re;i++)
      {
        int lrei=lre_index(i);
        int i1=list(lrei,1);
        local_grad(i)*=scale(i1-xsize);
      }
    }

    double mg=max(fabs(local_grad));
    if (max_separable_g< mg) max_separable_g=mg;
    dvector local_step=-solve(local_Hess,local_grad);

    for (int i=1;i<=num_local_re;i++)
    {
      int lrei=lre_index(i);
      int i1=list(lrei,1);
      //int i2=list(lrei,2);
      step(i1-xsize)=local_step(i);
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
