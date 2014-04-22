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

/**
 * Description not yet available.
 * \param
 */
void local_init_df1b2variable::dot_calcs(local_dep_df1b2variable& v,int j)
{
  if (adpool_stack_pointer<1)
  {
    cerr << "this can't happen" << endl;
    ad_exit(1);
  }
  int global_nvar=adpool_nvar_stack[adpool_stack_pointer-1];
  double * xd=p->get_u_dot();
  double * ud=v.get_u_dot();
  double * zd=(v.p)->get_u_dot();
  for (int i=0;i<global_nvar;i++)
  {
    //for (int j=0;j<nvar;j++)
    {
      *zd+=ud[j] * *xd;
    }
    zd++;
    xd++;
  }
}

/**
 * Description not yet available.
 * \param
 */
local_init_df1b2variable::local_init_df1b2variable
  (void) : df1b2variable(newadkl)
{
  p=0;
}

/**
 * Description not yet available.
 * \param
 */
local_init_df1b2variable::local_init_df1b2variable
  (double _xu, double * _xdot) : df1b2variable()
{
  *get_u()=_xu;
  p=0;
  xdot=_xdot;
  set_dot(num_vars-1);
}

/**
 * Description not yet available.
 * \param
 */
local_init_df1b2variable::local_init_df1b2variable
  (const df1b2variable & _x) : df1b2variable(newadkl)
{
  ADUNCONST(df1b2variable,x)
  p=&_x;
  xu=*(x.get_u());
}

/**
 * Description not yet available.
 * \param
 */
local_init_df1b2vector::local_init_df1b2vector(const df1b2vector & _x)
{
  ADUNCONST(df1b2vector,x)
  p=&_x;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  //int ind_index = x(mmin).get_ind_index();
  df1b2variable::noallocate=1;
  df1b2vector::allocate(mmin,mmax);
  df1b2variable::noallocate=0;
}

 // #define USE_BARD_PEN
 // class newadkludge;
 // extern newadkludge * newadkl=0;
 //
 //
  typedef local_init_var  * PLOCAL_INIT_VAR;
 //
 // class laplace_approximation_calculator;
 // laplace_approximation_calculator * funnel_init_var::lapprox=0;
 // df1b2variable * funnel_init_var::funnel_constraints_penalty=0;
  int local_init_var::num_vars=0;
 // //int funnel_init_var::num_all_vars=0;
  int local_init_var::num_inactive_vars=0;
  int local_init_var::num_active_parameters=0;
 // //funnel_init_var ** funnel_init_var::all_list=new PFUNNEL_INIT_VAR[200];
  local_init_var ** local_init_var::list=new PLOCAL_INIT_VAR[200];
  local_init_var ** local_init_var::inactive_list=new PLOCAL_INIT_VAR[200];
  init_df1b2vector * local_init_var::py=0;
  imatrix * local_init_var::plist=0;
 //
 // void  xxx(init_df1b2vector & tmp,int x){;}
 //

/**
 * Description not yet available.
 * \param
 */
  void local_init_var::add_to_list(void)
  {
    index=num_vars;
    list[num_vars++]=this;
    //all_list[num_all_vars++]=this;
  }
 //
 // void funnel_init_var::delete_from_list(void)
 // {
 //   if (index!=num_vars-1)
 //   {
 //     cerr << "can only delete last member" << endl;
 //     ad_exit(1);
 //   }
 //   num_vars--;
 //   index=-1;
 // }
 //

/**
 * Description not yet available.
 * \param
 */
  void local_init_var::add_to_inactive_list(void)
  {
    index=-1;
    inactive_list[num_inactive_vars++]=this;
  }

/**
 * Description not yet available.
 * \param
 */
  void local_init_var::allocate(void)
  {
    //cout << "In allocate" << endl;
  }

/**
 * Description not yet available.
 * \param
 */
  void local_init_var::allocate_all(void)
  {
    num_active_parameters=local_init_var::nvarcalc_all();
    if (py)
    {
      if (py->indexmax() != num_active_parameters)
      {
        delete py;
        py=0;
      }
    }

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

      if (!py)
      {
        py = new init_df1b2vector(1,num_active_parameters);
      }
      if (!py)
      {
        cerr << "memory allocation error" << endl;
        ad_exit(1);
      }
      //init_df1b2vector& tmp = *py;

    if (plist)
    {
      if (plist->indexmax() != num_active_parameters)
      {
        delete plist;
        plist=0;
      }
    }
    if (!plist)
    {
      plist = new imatrix(1,num_active_parameters,1,2);
    }
    if (!plist)
    {
      cerr << "memory allocation error" << endl;
      ad_exit(1);
    }

    int ii=1;
    int i;
      for(i=0;i<num_vars;i++)
      {
        list[i]->xinit(*py,ii);
      }

    ii=1;
    for(i=0;i<num_vars;i++)
    {
      list[i]->set_index(*plist,ii);
    }

    for(i=0;i<num_inactive_vars;i++)
    {
      inactive_list[i]->allocate();
    }

    local_init_var::reset(*py);
  }

 // funnel_init_df1b2variable::funnel_init_df1b2variable
 //   (const df1b2_init_number & _x) : df1b2variable(newadkl)
 //   //(df1b2_init_number & x) : df1b2variable()
 // {
 //   ADUNCONST(df1b2_init_number,x)
 //   type=0;
 //   pointer=0;
 //   ind_index=x.get_ind_index();
 //   if (ind_index<0)
 //   {
 //     add_to_inactive_list();
 //   }
 //   else
 //   {
 //     add_to_list();
 //     lapprox->used_flags(ind_index)+=1;
 //   }
 //   //cout << "ind_index = " << ind_index << endl;
 //   xu=*(x.get_u());
 // }
 //
 //
 // funnel_init_df1b2variable::funnel_init_df1b2variable
 //   (const random_effects_bounded_vector_info & _u)
 //   : df1b2variable(newadkl)
 // {
 //   ADUNCONST(random_effects_bounded_vector_info,u)
 //   df1b2variable& x = (*(u.pv)).df1b2vector::operator () (u.i);
 //
 //   type=1;
 //   pointer=u.pv;
 //   ind_index = x.get_ind_index();
 //   if (ind_index<0)
 //   {
 //     add_to_inactive_list();
 //   }
 //   else
 //   {
 //     add_to_list();
 //     lapprox->used_flags(ind_index)+=1;
 //   }
 //   xu=*(x.get_u());
 //
 // }
 //

/**
 * Description not yet available.
 * \param
 */
  void local_init_df1b2variable::allocate(const df1b2variable& x)
  {
    cerr << "Haven't defined htis yet" << endl;
    ad_exit(1);
  }
 //
 // funnel_init_df1b2variable::funnel_init_df1b2variable
 //   (void) : df1b2variable(newadkl)
 // {
 //   type=0;
 //   pointer=0;
 //   ind_index = -1;
 //   if (ind_index<0)
 //   {
 //     add_to_inactive_list();
 //   }
 //   else
 //   {
 //     add_to_list();
 //   }
 // }
 //

/**
 * Description not yet available.
 * \param
 */
  void local_init_df1b2variable::
    preallocate(const df1b2variable & _x)
  {
    ADUNCONST(df1b2variable,x)
    type=0;
    pointer=0;
    ind_index = x.get_ind_index();
    if (ind_index<0)
    {
      add_to_inactive_list();
    }
    else
    {
      add_to_list();
    }
    xu=*(x.get_u());
  }

 //
 // funnel_init_df1b2variable::funnel_init_df1b2variable
 //   (const df1b2variable & _x) : df1b2variable(newadkl)
 // {
 //   ADUNCONST(df1b2variable,x)
 //   type=0;
 //   pointer=0;
 //   ind_index = x.get_ind_index();
 //   if (ind_index<0)
 //   {
 //     add_to_inactive_list();
 //   }
 //   else
 //   {
 //     add_to_list();
 //   }
 //   xu=*(x.get_u());
 // }
 //

/**
 * Description not yet available.
 * \param
 */
  void local_init_df1b2variable::allocate(void)
  {
    df1b2variable::allocate();
    *(get_u())=xu;
    if (index>=0)
      get_u_dot()[index]=1.0;
  }
 //
 // funnel_dependent_df1b2variable::funnel_dependent_df1b2variable
 //   (const df1b2variable& x)
 // {
 //   df1b2variable::operator = (x);
 //   if (!df1b2_gradlist::no_derivatives)
 //   {
 //     df1b2variable * tmp = (df1b2variable *) (this);
 //     //set_dependent_variable(*tmp);
 //   }
 //   df1b2_gradlist::set_no_derivatives();
 // }
 //

/**
 * Description not yet available.
 * \param
 */
  void local_init_df1b2variable::set_value(const init_df1b2vector& _x,
    const int& _ii)
  {
    //df1b2variable pen=0.0;
    ADUNCONST(init_df1b2vector,x)
    ADUNCONST(int,ii)
    df1b2variable::operator = (x(ii++));
  }

/**
 * Description not yet available.
 * \param
 */
  void local_init_df1b2variable::set_value(const init_df1b2vector& _x,
    const int& _ii,const df1b2variable& _pen)
  {
    ADUNCONST(init_df1b2vector,x)
    ADUNCONST(int,ii)
    ADUNCONST(df1b2variable,pen)
    if (!pointer)
    {
      df1b2variable::operator = (x(ii++));
    }
    else
    {
      switch (type)
      {
        case 1:   // vector
        {
          df1b2_init_bounded_vector & b = *(df1b2_init_bounded_vector*)pointer;
          //laplace_approximation_calculator * l =lapprox;
          //int uf=-1;
          if (ind_index>0)
          {
           // uf=l->used_flags(ind_index);
          }
          else
          {
            if (!initial_params::straight_through_flag)
            {
              df1b2variable::operator = (boundp(x(ii++),b.getminb(),b.getmaxb(),
                pen));
            }
            else
            {
              df1b2variable::operator = (x(ii++));
              *get_u()=boundp(*get_u(),b.getminb(),b.getmaxb());
              double diff=b.getmaxb()-b.getminb();
              df1b2variable ss=((*this)-b.getminb())/diff;
  #           ifdef USE_BARD_PEN
                const double l4=log(4.0);
                double wght=.000001/diff;
                pen-=wght*(log(ss+double(1.e-40))+log((double(1.0)-ss)
                   +double(1.e-40))+l4);
  #           else
               XXXX
  #           endif
            }
          }
          break;
        }
        case 2:  // matrix
        default:
        {
          cerr << "the bounded matrix case in "
            " void funnel_init_df1b2variable::xinit  has not bee implemented"
            << endl;
            ad_exit(1);
        }
      }
    }
  }

/**
 * Description not yet available.
 * \param
 */
  int local_init_var::nvarcalc_all(void)
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
  void local_init_var::set_dot_all(void)
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
  void local_init_var::dot_calcs_all(local_dep_df1b2variable& v)
  {
    for (int i=0;i<num_vars;i++)
    {
      list[i]->dot_calcs(v,i);
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void local_init_df1b2variable::xinit(init_df1b2vector& y,int& ii)
  {
    y(ii)= xu;
    ii++;
  }

/**
 * Description not yet available.
 * \param
 */
  void local_init_df1b2variable::xinit(dvector& y,int& ii)
  {
    if (!pointer)
    {
      y(ii)= xu;
    }
    else
    {
      switch (type)
      {
        case 1:   // vector
        {
          df1b2_init_bounded_vector & b = *(df1b2_init_bounded_vector*)pointer;
          y(ii)=boundpin(xu,b.getminb(),b.getmaxb());
          break;
        }
        case 2:  // matrix
        default:
        {
          cerr << "the bounded matrix case in "
            " void local_init_df1b2variable::xinit  has not bee implemented"
            << endl;
            ad_exit(1);
        }
      }
    }
    ii++;
  }

 // /*
 // void funnel_init_df1b2variable::xinit(dvector& y,int& ii)
 // {
 //   y(ii)= xu;
 //   ii++;
 // }
 // */
 //

/**
 * Description not yet available.
 * \param
 */
  void local_init_df1b2variable::set_index(imatrix& y,int& ii)
  {
    //cout << ind_index << " " << ii << endl;
    y(ii,1)= ind_index;
    y(ii,2)= ii;
    ii++;
  }

/**
 * Description not yet available.
 * \param
 */
  void local_init_var::reset(init_df1b2vector& x)
  {
    int ii=1;
    //df1b2variable pen=0.0;
    for (int i=0;i<num_vars;i++)
    {
      //list[i]->set_value(x,ii,pen);
      list[i]->set_value(x,ii);
    }
  }
 //
 //
 // funnel_init_df1b2vector::funnel_init_df1b2vector(
 //   const df1b2_init_vector& _x)
 // {
 //   ADUNCONST(df1b2_init_vector,x)
 //   //type=0;
 //   //pointer=0;
 //   p=&_x;
 //   int mmin=p->indexmin();
 //   int mmax=p->indexmax();
 //   int ind_index = (*p)(mmin).get_ind_index();
 //   if (ind_index<0)
 //   {
 //     add_to_inactive_list();
 //   }
 //   else
 //   {
 //     add_to_list();
 //   }
 //   df1b2variable::noallocate=1;
 //   df1b2vector::allocate(mmin,mmax);
 //   df1b2variable::noallocate=0;
 // }
 //
 //

/**
 * Description not yet available.
 * \param
 */
  int local_init_df1b2vector::nvar_calc(void)
  {
    return p->indexmax()-p->indexmin()+1;
  }


/**
 * Description not yet available.
 * \param
 */
  void local_init_df1b2vector::xinit(init_df1b2vector& y,int& ii)
  {
    df1b2vector * vp = (df1b2vector*)(p);
    int mmin=vp->indexmin();
    int mmax=vp->indexmax();
    int i;
    for (i=mmin;i<=mmax;i++)
    {
      y(ii)= value((*vp)(i));
      ii++;
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void local_init_df1b2vector::set_index(imatrix& y,int& ii)
  {
    int mmin=p->indexmin();
    int mmax=p->indexmax();
    int i;
    for (i=mmin;i<=mmax;i++)
    {
      //y(ii,1)= ( *(df1b2_init_vector *)(p) )(i).get_ind_index();
      y(ii,2)= ii;
      ii++;
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void local_init_df1b2vector::set_value(const init_df1b2vector& _x,
    const int& _ii)
  {
    ADUNCONST(int,ii)
    ADUNCONST(init_df1b2vector,x)
    int mmin=p->indexmin();
    int mmax=p->indexmax();
    int i;
    for (i=mmin;i<=mmax;i++)
    {
      (*this)(i) = (x(ii++));
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void local_init_df1b2vector::set_value(const init_df1b2vector& _x,
    const int& _ii,const df1b2variable& pen)
  {
    ADUNCONST(int,ii)
    ADUNCONST(init_df1b2vector,x)
    int mmin=p->indexmin();
    int mmax=p->indexmax();
    int i;
    for (i=mmin;i<=mmax;i++)
    {
      (*this)(i) = (x(ii++));
    }
  }
