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

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::
   do_separable_stuff_laplace_approximation_banded_adjoint
   (const df1b2variable& ff)
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
  int num_local_fe=0;

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
      lfe_index(++num_local_fe)=i;
    }
  }

  if (num_local_re > 0)
  {
    if (hesstype==3)
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
          if (i1>=j1) (*bHess)(i1,j1)+=locy(i2).u_bar[j2-1];
        }
      }
    }
    else if (hesstype==4)
    {
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
    }
  }

  // Now the adjoint code

  if (num_local_re > 0)
  {
    if (hesstype==3)
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
          if (i1>=j1)
          {
            //(*bHess)(i1,j1)+=locy(i2).u_bar[j2-1];
            locy(i2).get_u_bar_tilde()[j2-1]=(*bHessadjoint)(i1,j1);
          }
        }
      }
    }
    else if (hesstype==4)
    {
      if (pmin->lapprox->sparse_hessian_flag==0)
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
            {
              //(*bHess)(i1,j1)+=locy(i2).u_bar[j2-1];
              locy(i2).get_u_bar_tilde()[j2-1]=Hessadjoint(i1,j1);
            }
          }
        }
      }
      else
      {
        dcompressed_triplet * vsparse_triplet_adjoint =
          pmin->lapprox->vsparse_triplet_adjoint;
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
            {
              //(*bHess)(i1,j1)+=locy(i2).u_bar[j2-1];
              //locy(i2).get_u_bar_tilde()[j2-1]=Hessadjoint(i1,j1);
              if (i1<=j1)
              {
                //(*sparse_triplet2)((*sparse_iterator)(sparse_count_adjoint))
                //  +=locy(i2).u_bar[j2-1];
                sparse_count_adjoint++;
                locy(i2).get_u_bar_tilde()[j2-1]=
                  (*vsparse_triplet_adjoint)
                    ((*sparse_iterator)(sparse_count_adjoint));
              }
            }
          }
        }
      }
    }
  }

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


  for (int i=1;i<=num_local_fe;i++)
  {
    int lfei=lfe_index(i);
    int i1=list(lfei,1);
    //if (lfei - list(lfei,2))
     // cout << lfei << " " <<  list(lfei,2) << endl;
    local_dtemp(i1)+=*locy(lfei).get_u_tilde();
#if !defined(OPT_LIB)
    int mmin=xadjoint.indexmin();
    int mmax=xadjoint.indexmax();
    if (i1<mmin || i1> mmax)
    {
       cerr << "this can't happen" << endl;
      ad_exit(1);
    }
#endif
  }

  for (int i=1;i<=num_local_re;i++)
  {
    int i1=list(lre_index(i),1)-xsize;
    int i2=list(lre_index(i),2);
    uadjoint(i1)+=*locy(i2).get_u_tilde();
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
