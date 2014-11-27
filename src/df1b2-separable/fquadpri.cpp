/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <df1b2fun.h>
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

// this should be a resizeable array
df1b2quadratic_prior* df1b2quadratic_prior::ptr[100];

 int df1b2quadratic_prior::num_quadratic_prior=0;
 const int df1b2quadratic_prior::max_num_quadratic_prior=100;


  void df1b2quadratic_prior::add_to_list(void)
  {
    if (num_quadratic_prior>=max_num_quadratic_prior) ad_exit(1);
    xmyindex=num_quadratic_prior;
    ptr[num_quadratic_prior++]=this;
  }
void df1b2quadratic_prior::get_Lxu(dmatrix& M)
{
  bool isallocated = Lxu && allocated(*Lxu) && index;
#ifndef OPT_LIB
  assert(isallocated);
#endif
  if (isallocated)
  {
    int mmin=(*pu)(pu->indexmin()).get_ind_index();
    int size=pu->size();
    int offset=mmin-M(M.indexmin()).indexmax()-1;  // subtract x offset
    int nvar = index->indexmax();
    {
      switch(old_style_flag)
      {
      case 0:
        for (int i=1;i<=nvar;i++)
        {
          int jcol=(*index)(i);
          for (int ii=1;ii<=size;ii++)
          {
            M(ii+offset,jcol)+=(*Lxu)(i,ii);
          }
        }
        break;
      case 1:
        break;
        //@todo Check break statement
        for (int i=1;i<=nvar;i++)
        {
          int jcol=(*index)(i);
          for (int ii=1;ii<=size;ii++)
          {
            M(ii+offset,jcol)+=(*Lxu)(i,ii);
          }
        }
      case 2:
        for (int i=1;i<=nvar;i++)
        {
          int jcol=(*index)(i);
          for (int ii=1;ii<=size;ii++)
          {
            M(ii+offset,jcol)+=(*Lxu)(i,ii);
          }
        }
        break;
      default:
         cerr << "Illegal valueinswitch statement" << endl;
         ad_exit(1);
      }
    }
  }
}

  df1b2quadratic_prior::df1b2quadratic_prior(void)
  {
    add_to_list();
    num_active_parameters=0;
    M=0;
    pu=0;
    index=0;
    Lxu=0;
  }
  df1b2quadratic_prior::~df1b2quadratic_prior(void)
  {
    if (index) delete index;
    index=0;
    if (Lxu) delete Lxu;
    Lxu=0;
    if (M) delete M;
    M=0;
    if (pu) delete pu;
    pu=0;
  }

void df1b2quadratic_prior::allocate(const df1b2_init_vector& _u,
  const char* s)
  {
    allocate(_u);
  }
  void df1b2quadratic_prior::allocate(const df1b2matrix & _M,
    const df1b2_init_vector & _u, const char * s)
  {
    allocate(_M,_u);
  }
  void df1b2quadratic_prior::allocate(const df1b2_init_vector & _u)
  {
    pu = new df1b2_init_vector(_u);
  }
  void df1b2quadratic_prior::allocate(const df1b2matrix & _M,
    const df1b2_init_vector & _u)
  {
    M =new df1b2matrix(_M);
    pu = new df1b2_init_vector(_u);
  }
  void df1b2quadratic_prior::operator = (const df1b2matrix & M)
  {
    quadratic_prior::in_qp_calculations=0;
    num_active_parameters=funnel_init_var::num_vars;
    df1b2_gradlist::no_derivatives=1;
    dvector cu=value(*pu);

    if (laplace_approximation_calculator::where_are_we_flag==3)
    {
      df1b2variable::noallocate=1;
      df1b2vector v(M.indexmin(),M.indexmax());
      df1b2variable::noallocate=0;
      switch (old_style_flag)
      {
      case 0:
      case 1:
        v = solve(M,cu);
        break;
      case 2:
        v = M*cu;
        break;
      default:
        cerr << "Illegal value for quadratic_prior::old_style_flag"
             << endl;
        ad_exit(1);
      }
      int mmin=v.indexmin();
      int mmax=v.indexmax();

#ifndef OPT_LIB
      assert(num_active_parameters <= INT_MAX);
#endif
      if (index)
      {
        if (index->indexmax() != (int)num_active_parameters)
        {
          delete index;
          index=0;
        }
      }

      if (num_active_parameters>0)
      {
        if (!index)
        {
          index=new ivector(column(*funnel_init_var::plist,1));
        }
        if (Lxu)
        {
          int tmin = Lxu->indexmin();
          if ((Lxu->indexmin() != mmin)
              || (Lxu->indexmax() != mmax)
              || ((*Lxu)(tmin).indexmin() != 1)
              || ((*Lxu)(tmin).indexmax() != (int)num_active_parameters))
          {
            delete Lxu;
            Lxu=0;
          }
        }
        if (!Lxu)
        {
          Lxu=new dmatrix(1, (int)num_active_parameters, mmin-1, mmax);
        }
        for (int i=1;i<=(int)num_active_parameters;i++)
        {
          (*Lxu)(i,mmin-1)=(*funnel_init_var::plist)(i,1);
        }
        for (int j=mmin;j<=mmax;j++)
        {
          for (int i=1;i<=(int)num_active_parameters;i++)
          {
            switch (old_style_flag)
            {
            case 0:
              (*Lxu)(i,j)=v(j).get_u_dot()[i-1];
              break;
            case 1:
            case 2:
              (*Lxu)(i,j)=2.0*v(j).get_u_dot()[i-1];
              break;
            default:
              cerr << "Illegal value for quadratic_prior::old_style_flag"
                   << endl;
              ad_exit(1);
            }
          }
        }
      }
      else
      {
        if (Lxu)
        {
          delete Lxu;
          Lxu=0;
        }
      }
    }
    df1b2_gradlist::no_derivatives=0;
  }

 void df1b2quadratic_prior::get_Lxu_contribution(dmatrix& M)
 {
   for (int i=0;i<num_quadratic_prior;i++)
   {
     //cout << ptr[i]->get_num_active_parameters() << endl;
     //if (ptr[i]->get_num_active_parameters()>0)
     {
       ptr[i]->get_Lxu(M);
     }
   }
 }

normal_df1b2quadratic_prior::normal_df1b2quadratic_prior(void)
{
  set_old_style_flag();
}

void normal_df1b2quadratic_prior::set_old_style_flag(void)
{
  old_style_flag=0;
}
void normal_df1b2quadratic_prior::operator = (const df1b2matrix & M)
{
  df1b2quadratic_prior::operator = (M);
}

void df1b2quadratic_re_penalty::set_old_style_flag(void)
{
  old_style_flag=2;
}
void df1b2quadratic_re_penalty::operator = (const df1b2matrix & M)
{
  df1b2quadratic_prior::operator = (M);
}
void df1b2quadratic_re_penalty::operator = (const dmatrix & M)
{
  df1b2quadratic_prior::operator = (M);
}


df1b2quadratic_re_penalty::df1b2quadratic_re_penalty(void)
{
  set_old_style_flag();
}
// *******************************************************
// *******************************************************
// *******************************************************
// *******************************************************
constant_df1b2quadratic_re_penalty::constant_df1b2quadratic_re_penalty(void)
{
  set_old_style_flag();
}

void constant_df1b2quadratic_re_penalty::set_old_style_flag(void)
{
  old_style_flag=2;
}
void constant_df1b2quadratic_re_penalty::operator = (const dmatrix & M)
{
  //df1b2quadratic_prior::operator = (M);
}
void df1b2quadratic_prior::operator = (const dmatrix & M)
{
  quadratic_prior::in_qp_calculations=0;
  num_active_parameters=funnel_init_var::num_vars;
  df1b2_gradlist::no_derivatives=1;
  dvector cu=value(*pu);

  if (laplace_approximation_calculator::where_are_we_flag==3)
  {
    df1b2variable::noallocate=1;
    //df1b2vector v(M.indexmin(),M.indexmax());
    df1b2variable::noallocate=0;
    switch (old_style_flag)
    {
    case 0:
    case 1:
      cout << "this can't happen" << endl;
      ad_exit(1);
      break;
    case 2:
      //v = M*cu;
      break;
    default:
      cerr << "Illegal value for quadratic_prior::old_style_flag"
           << endl;
      ad_exit(1);
    }
    //int mmin=v.indexmin();
    //int mmax=v.indexmax();

    if (index)
    {
      //if (index->indexmax() != nvar)
      cout << "this can't happen" << endl;
      ad_exit(1);
      delete index;
      index=0;
    }

    if (Lxu)
    {
      cout << "this can't happen" << endl;
      ad_exit(1);
      delete Lxu;
      Lxu=0;
    }
  }
  df1b2_gradlist::no_derivatives=0;
}


