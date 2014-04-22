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
#include <df1b2fun.h>
#include "f1b2locl.h"
class newadkludge;
extern newadkludge * newadkl;

typedef local_init_pass1_var  * PLOCAL_INIT_PASS1_VAR;
local_init_pass1_var** local_init_pass1_var::list =
  new PLOCAL_INIT_PASS1_VAR[200];
int local_init_pass1_var::num_active_parameters=0;
int local_init_pass1_var::num_vars=0;

/**
 * Description not yet available.
 * \param
 */
void local_init_pass1_var::allocate_all(void)
{
  num_active_parameters=local_init_pass1_var::nvarcalc_all();

  df1b2variable::save_adpool_pointer();
  adpool * tmppool=df1b2variable::pool;
  if (!localf1b2gradlist)
  {
    localf1b2gradlist = new df1b2_gradlist(400000U,20000U,800000U,40000U,
      200000U,10000U,adstring("lf1b2list1"));
    if (!localf1b2gradlist)
    {
      cerr << "Error allocating memory for local df1b2gradlist" << endl;
      ad_exit(1);
    }
  }
  globalf1b2gradlist=f1b2gradlist;
  f1b2gradlist=localf1b2gradlist;

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
          df1b2variable::pool=df1b2variable::adpool_vector[i];
          if (!tmp->on_adpool_vector())
          {
            df1b2variable::adpool_vector[df1b2variable::adpool_counter]=tmp;
            df1b2variable::nvar_vector[df1b2variable::adpool_counter]=
              tmp->nvar;
            //df1b2variable::adpool_counter++;
            df1b2variable::increment_adpool_counter();
            tmp->on_adpool_vector()=1;
          }
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
        if (!df1b2variable::pool->on_adpool_vector())
        {
          df1b2variable::adpool_vector[df1b2variable::adpool_counter]=
            df1b2variable::pool;
          df1b2variable::nvar_vector[df1b2variable::adpool_counter]=
            df1b2variable::pool->nvar;
          //df1b2variable::adpool_counter++;
          df1b2variable::increment_adpool_counter();
          df1b2variable::pool->on_adpool_vector()=1;
        }
        df1b2variable::pool=new adpool();
        if (!df1b2variable::pool)
        {
          cerr << "Memory allocation error" << endl;
          ad_exit(1);
        }

        df1b2variable::nvar=num_active_parameters;
        df1b2variable::set_blocksize();

        if (!df1b2variable::pool->on_adpool_vector())
        {
          df1b2variable::adpool_vector[df1b2variable::adpool_counter]=
            df1b2variable::pool;
          df1b2variable::nvar_vector[df1b2variable::adpool_counter]=
            df1b2variable::pool->nvar;
          //df1b2variable::adpool_counter++;
          df1b2variable::increment_adpool_counter();
          df1b2variable::pool->on_adpool_vector()=1;
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
    df1b2variable::nvar=num_active_parameters;
    df1b2variable::set_blocksize();
    df1b2variable::adpool_vector[df1b2variable::adpool_counter]=
      df1b2variable::pool;
    df1b2variable::nvar_vector[df1b2variable::adpool_counter]=
      df1b2variable::pool->nvar;
    //df1b2variable::adpool_counter++;
    df1b2variable::increment_adpool_counter();
  }
  df1b2variable::nvar=num_active_parameters;
  df1b2variable::set_blocksize();

  for (int i=0;i<num_vars;i++)
  {
    list[i]->allocate();
  }
}

/**
 * Description not yet available.
 * \param
 */
void local_init_pass1_var::add_to_list(void)
{
  list[num_vars++]=this;
}

/**
 * Description not yet available.
 * \param
 */
void local_init_pass1_var::set_dot_all(void)
{
  int ii=0;
  for (int i=0;i<num_vars;i++)
  {
    list[i]->set_dot(ii);
  }
}

/**
 * Description not yet available.
 * \param
 */
void local_init_pass1_df1b2variable::dot_calcs(local_dep_df1b2variable& v,int j)
{
  if (adpool_stack_pointer<1)
  {
    cerr << "this can't happen" << endl;
    ad_exit(1);
  }
  int global_nvar=adpool_nvar_stack[adpool_stack_pointer-1];
  double * xd=xudot;
  double * ud=v.get_u_dot();
  double * zd=(v.p)->get_u_dot();
  for (int i=0;i<global_nvar;i++)
  {
    *zd+=ud[j] * *xd;
    zd++;
    xd++;
  }
}

/**
 * Description not yet available.
 * \param
 */
void local_init_pass1_df1b2variable::allocate(void)
{
  df1b2variable::allocate();
  *get_u()=xu;
};

/**
 * Description not yet available.
 * \param
 */
int local_init_pass1_var::nvarcalc_all(void)
{
  int n=0;
  for (int i=0;i<num_vars;i++)
  {
    n+=list[i]->nvar_calc();
  }
  return n;
}

/**
 * Description not yet available.
 * \param
 */
local_init_pass1_df1b2variable::local_init_pass1_df1b2variable(double _xu,
  double* _xudot)
{
  xu=_xu;
  *get_u()=_xu;
  xudot=_xudot;
}
