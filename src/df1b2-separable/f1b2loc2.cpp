/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include <df1b2fun.h>
#include <f1b2locl.h>
class newadkludge;
extern newadkludge * newadkl;

local_dep_df1b2variable::local_dep_df1b2variable(void) :
  df1b2variable(newadkl)
{
  //adpool * tmppool=df1b2variable::pool;
  //int tmpnvar=df1b2variable::nvar;
  //df1b2variable::restore_adpool_pointer(); 
  p=new df1b2variable();
  //df1b2variable::save_adpool_pointer(); 
  //df1b2variable::pool=tmppool;
  //df1b2variable::nvar=tmpnvar;
}
local_dep_df1b2variable::~local_dep_df1b2variable()
{
  delete (df1b2variable *) p;
}

local_dep_df1b2variable&  local_dep_df1b2variable::operator = 
  (const df1b2variable& x)  
{
  df1b2variable::operator = (x);
  *(p->get_u()) = *get_u();
  local_init_var::dot_calcs_all(*this);
  /*
  int global_nvar=adpool_nvar_stack[adpool_stack_pointer-1];
  if (p)
  {
    p->initialize(global_nvar);
    *(p->get_u()) = *get_u();
  }
  */
  return *this;
}

local_dep_df1b2variable::local_dep_df1b2variable
  (double*  _xdot,double * _pxdot) : df1b2variable()
{
  p=0;
  xdot=_xdot;
  pxdot=_pxdot;
}


local_dep_df1b2variable::local_dep_df1b2variable
  (const df1b2variable & _x) : df1b2variable(newadkl)
{
  ADUNCONST(df1b2variable,x)
  p=&_x;
  xu=*(x.get_u()); 
}

local_dep_df1b2vector::local_dep_df1b2vector(const df1b2vector & _x)
{
  ADUNCONST(df1b2vector,x)
  p=&_x;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int ind_index = x(mmin).get_ind_index();
  df1b2variable::noallocate=1;
  df1b2vector::allocate(mmin,mmax);
  df1b2variable::noallocate=0;
}

 
 // #define USE_BARD_PEN
 // class newadkludge;
 // extern newadkludge * newadkl=0;
 // 
 // 
  typedef local_dep_var  * PLOCAL_INIT_VAR;
 // 
 // class laplace_approximation_calculator;
 // laplace_approximation_calculator * funnel_dep_var::lapprox=0;
 // df1b2variable * funnel_dep_var::funnel_constraints_penalty=0;
  int local_dep_var::num_vars=0;
 // //int funnel_dep_var::num_all_vars=0;
  int local_dep_var::num_inactive_vars=0;
  int local_dep_var::num_active_parameters=0;
 // //funnel_dep_var ** funnel_dep_var::all_list=new PFUNNEL_INIT_VAR[200];
  local_dep_var ** local_dep_var::list=new PLOCAL_INIT_VAR[200];
  local_dep_var ** local_dep_var::inactive_list=new PLOCAL_INIT_VAR[200];
  //dep_df1b2vector * local_dep_var::py=0;
  imatrix * local_dep_var::plist=0;
 // 
 // void  xxx(dep_df1b2vector & tmp,int x){;}
 // 
  void local_dep_var::add_to_list(void)
  {
    index=num_vars;
    list[num_vars++]=this;
    //all_list[num_all_vars++]=this;
  }
 // 
 // void funnel_dep_var::delete_from_list(void)
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
  void local_dep_var::add_to_inactive_list(void)
  {
    index=-1;
    inactive_list[num_inactive_vars++]=this;
  }
 // 
  void local_init_var::end_local_calculations(void)
  {
    local_dep_var::deallocate_all();
    reset_counters();
    f1b2gradlist=globalf1b2gradlist;
    df1b2_gradlist::set_yes_derivatives();  
    df1b2variable::restore_adpool_pointer();
  }

  
  void local_dep_var::allocate_all(void)
  {
    for (int i=0;i<num_vars;i++)
    {
      list[i]->allocate();
    }
  }
  void local_dep_var::deallocate_all(void)
  {
    for (int i=0;i<num_vars;i++)
    {
      list[i]->deallocate();
    }
  }
  
  void local_dep_df1b2variable::allocate(void)
  {
    df1b2variable::allocate();
  }

  void local_dep_df1b2variable::deallocate(void)
  {
    df1b2variable::deallocate();
  }

  int local_dep_var::nvarcalc_all(void)
  {
    int n=0;
    for (int i=0;i<num_vars;i++)
    {
      n+=list[i]->nvar_calc();
    }
    return n;
  }
  void local_dep_df1b2variable::set_index(imatrix& y,int& ii)
  {
    //cout << "FUCK " << ind_index << " " << ii << endl;
    y(ii,1)= ind_index;
    y(ii,2)= ii;
    ii++;
  }
 //   
 // 
 // 
  int local_dep_df1b2vector::nvar_calc(void)
  {
    return p->indexmax()-p->indexmin()+1;
  }
 // 
  void local_dep_df1b2vector::set_index(imatrix& y,int& ii)
  {
    
    int mmin=p->indexmin();
    int mmax=p->indexmax();
    int i;
    for (i=mmin;i<=mmax;i++)
    {
      //y(ii,1)= ( *(df1b2_dep_vector *)(p) )(i).get_ind_index();
      y(ii,2)= ii;
      ii++;
    }
  }

