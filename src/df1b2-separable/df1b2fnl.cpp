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
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

#define USE_BARD_PEN
class newadkludge;
newadkludge * newadkl=0;


typedef funnel_init_var  * PFUNNEL_INIT_VAR;

class laplace_approximation_calculator;
laplace_approximation_calculator * funnel_init_var::lapprox=0;
df1b2variable * funnel_init_var::funnel_constraints_penalty=0;
unsigned int funnel_init_var::num_vars=0;
//int funnel_init_var::num_all_vars=0;
int funnel_init_var::num_inactive_vars=0;
unsigned int funnel_init_var::num_active_parameters=0;
//funnel_init_var ** funnel_init_var::all_list=new PFUNNEL_INIT_VAR[2000];
funnel_init_var ** funnel_init_var::list=new PFUNNEL_INIT_VAR[2000];
funnel_init_var ** funnel_init_var::inactive_list=new PFUNNEL_INIT_VAR[2000];
init_df1b2vector * funnel_init_var::py=0;
imatrix * funnel_init_var::plist=0;

  int funnel_check_flag=0;

/**
 * Description not yet available.
 * \param
 */
void funnel_init_var::add_to_list(void)
{
#ifndef OPT_LIB
  assert(num_vars <= INT_MAX);
#endif
  index = (int)num_vars;
  list[num_vars++]=this;
  //all_list[num_all_vars++]=this;
}

/**
 * Description not yet available.
 * \param
 */
void funnel_init_var::delete_from_list(void)
{
#ifndef OPT_LIB
  assert(num_vars <= INT_MAX);
#endif
  if (index != (int)(num_vars - 1))
  {
    cerr << "can only delete last member" << endl;
    ad_exit(1);
  }
  num_vars--;
  index=-1;
}

/**
 * Description not yet available.
 * \param
 */
void funnel_init_var::add_to_inactive_list(void)
{
  index=-1;
  inactive_list[num_inactive_vars++]=this;
}

/**
 * Description not yet available.
 * \param
 */
void funnel_init_var::allocate(void)
{
  //cout << "In allocate" << endl;
}

/**
 * Description not yet available.
 * \param
 */
void check_pool_depths(void)
{
  for (int i=0;i<df1b2variable::adpool_counter;i++)
  {
    cout << " Pool depth " << i << "  "
         << df1b2variable::adpool_vector[i]->depth_check()
         << "  " << df1b2variable::adpool_vector[i]  << endl;
  }
}

/**
Release memory.
*/
void funnel_init_var::deallocate_all(void)
{
  if (plist)
  {
#ifndef OPT_LIB
  assert(num_active_parameters <= INT_MAX);
#endif
    if (plist->indexmax() != (int)num_active_parameters)
    {
      delete plist;
      plist = 0;
    }
  }
  if (py)
  {
    delete py;
    py = 0;
  }
}

/**
 * Description not yet available.
 * \param
 */
void funnel_init_var::allocate_all(void)
{
  re_objective_function_value::pobjfun->deallocate();
  if (lapprox)
  {
    if (lapprox->calling_set)
    {
      (*lapprox->calling_set)(0,0)++;
    }
  }
  num_active_parameters=funnel_init_var::nvarcalc_all();
#ifndef OPT_LIB
  assert(num_active_parameters <= INT_MAX);
#endif
  if (py)
  {
    if (py->indexmax() != (int)num_active_parameters)
    {
      delete py;
      py=0;
    }
  }
  f1b2gradlist->reset();

  adpool * tmppool=df1b2variable::pool;
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
          df1b2variable::pool=df1b2variable::adpool_vector[i];
          found_pool_flag=1;
          break;
        }
      }
      if (!found_pool_flag)
      {
        df1b2variable::pool=new adpool();
        if (!df1b2variable::pool)
        {
          cerr << "Memory allocation error" << endl;
          ad_exit(1);
        }
        if (df1b2variable::adpool_counter>df1b2variable::adpool_vectorsize)
        {
          //cerr << "Need to increase adpool_vectorsize" << endl;
          //ad_exit(1);
          //int offset=get_unused_pool_index();
          int offset=1;
          adpool * tmp= df1b2variable::adpool_vector[offset];
          delete tmp;
          df1b2variable::adpool_vector[offset]=df1b2variable::pool;
          df1b2variable::nvar_vector[offset]=num_active_parameters;
          df1b2variable::adpool_use_index[offset]=
            df1b2variable::current_allocation_index;
        }
        else
        {
          df1b2variable::adpool_vector[df1b2variable::adpool_counter]=
            df1b2variable::pool;
          df1b2variable::nvar_vector[df1b2variable::adpool_counter]=
            num_active_parameters;
          //df1b2variable::adpool_counter++;
          df1b2variable::increment_adpool_counter();
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
    if (df1b2variable::adpool_counter>df1b2variable::adpool_vectorsize)
    {
      int offset=1;
      adpool * tmp= df1b2variable::adpool_vector[offset];
      delete tmp;
      df1b2variable::adpool_vector[offset]=df1b2variable::pool;
      df1b2variable::nvar_vector[offset]=num_active_parameters;
      df1b2variable::adpool_use_index[offset]=
        df1b2variable::current_allocation_index;
    }
    else
    {
      df1b2variable::adpool_use_index[df1b2variable::adpool_counter]=
        df1b2variable::current_allocation_index;
      df1b2variable::adpool_vector[df1b2variable::adpool_counter]=
        df1b2variable::pool;
      df1b2variable::nvar_vector[df1b2variable::adpool_counter]=
        num_active_parameters;
      //df1b2variable::adpool_counter++;
      df1b2variable::increment_adpool_counter();
    }
  }
  df1b2variable::current_allocation_index++;
  df1b2variable::nvar=num_active_parameters;
  df1b2variable::set_blocksize();

  re_objective_function_value::pobjfun->allocate();
  //if (funnel_check_flag)
   // check_pool_depths();
  df1b2variable::minder=1;
  int maxdersave=df1b2variable::maxder;
  df1b2variable::maxder=(int)num_active_parameters;
  if (!py)
  {
    py = new init_df1b2vector(1,(int)num_active_parameters);
  }
  //if (funnel_check_flag)
  //  check_pool_depths();
  if (!py)
  {
    cerr << "memory allocation error" << endl;
    ad_exit(1);
  }
  //init_df1b2vector& tmp = *py;


  if (plist)
  {
    if (plist->indexmax() != (int)num_active_parameters)
    {
      delete plist;
      plist=0;
    }
  }
  if (!plist)
  {
    plist = new imatrix(1,(int)num_active_parameters,1,2);
  }
  if (!plist)
  {
    cerr << "memory allocation error" << endl;
    ad_exit(1);
  }

  int ii=1;
  for(unsigned int i=0;i<num_vars;i++)
  {
    list[i]->xinit(*py,ii);
  }

  ii=1;
  for(unsigned int i=0;i<num_vars;i++)
  {
    list[i]->set_index(*plist,ii);
  }

  for(int i=0;i<num_inactive_vars;i++)
  {
    inactive_list[i]->allocate();
  }

  funnel_init_var::reset(*py);
  //if (funnel_check_flag)
  //  check_pool_depths();
  df1b2variable::maxder=maxdersave;
}

/**
 * Description not yet available.
 * \param
 */
funnel_init_df1b2variable::funnel_init_df1b2variable
  (const df1b2_init_number & _x) : df1b2variable(newadkl)
  //(df1b2_init_number & x) : df1b2variable()
{
  ADUNCONST(df1b2_init_number,x)
  type=0;
  pointer=0;
  ind_index=x.get_ind_index();
  if (ind_index<0)
  {
    add_to_inactive_list();
  }
  else
  {
    add_to_list();
#ifdef DIAG
    if (lapprox==0)
    {
      cout << "This can't happen" << endl;
      ad_exit(1);
    }
#endif
    lapprox->used_flags(ind_index)+=1;
  }
  //cout << "ind_index = " << ind_index << endl;
  xu=*(x.get_u());
}

/**
 * Description not yet available.
 * \param
 */
funnel_init_df1b2variable::funnel_init_df1b2variable
  (const random_effects_bounded_vector_info & _u)
  : df1b2variable(newadkl)
{
  ADUNCONST(random_effects_bounded_vector_info,u)
  df1b2variable& x = (*(u.pv)).df1b2vector::operator () (u.i);

  type=1;
  pointer=u.pv;
  ind_index = x.get_ind_index();
  if (ind_index<0)
  {
    add_to_inactive_list();
  }
  else
  {
    add_to_list();
    lapprox->used_flags(ind_index)+=1;
  }
  xu=*(x.get_u());
}

/**
 * Description not yet available.
 * \param
 */
void funnel_init_df1b2variable::allocate(const df1b2variable& x)
{
  cerr << "Haven't defined htis yet" << endl;
  ad_exit(1);
}

/**
 * Description not yet available.
 * \param
 */
funnel_init_df1b2variable::funnel_init_df1b2variable
  (void) : df1b2variable(newadkl)
{
  type=0;
  pointer=0;
  ind_index = -1;
  if (ind_index<0)
  {
    add_to_inactive_list();
  }
  else
  {
    add_to_list();
  }
}

/**
 * Description not yet available.
 * \param
 */
void funnel_init_df1b2variable::
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
    lapprox->used_flags(ind_index)+=1;
  }
  xu=*(x.get_u());
}

/**
 * Description not yet available.
 * \param
 */
funnel_init_df1b2variable::funnel_init_df1b2variable
  (const funnel_init_df1b2variable& x):
  funnel_init_var(),
  df1b2variable(x)
{}

/**
 * Description not yet available.
 * \param
 */
funnel_init_df1b2variable::funnel_init_df1b2variable
  (const df1b2variable & _x) : df1b2variable(newadkl)
{
  ADUNCONST(df1b2variable,x)
  type=0;
  pointer=0;
  ind_index = x.get_ind_index();
  get_ind_index() = x.get_ind_index();
  if (ind_index<0)
  {
    add_to_inactive_list();
  }
  else
  {
    add_to_list();
    lapprox->used_flags(ind_index)+=1;
    if (lapprox->calling_set)
    {
      int j=++(*lapprox->calling_set)(ind_index,0);
      int k=lapprox->used_flags(ind_index);
      if (j != k)
      {
        cerr << "This can't happen" << endl;
        ad_exit(1);
      }
      (*lapprox->calling_set)(ind_index,j)=(*lapprox->calling_set)(0,0);
    }
  }
  xu=*(x.get_u());
}

/**
 * Description not yet available.
 * \param
 */
void funnel_init_df1b2variable::allocate(void)
{
  df1b2variable::allocate();
  *(get_u())=xu;
  if (index>=0)
    get_u_dot()[index]=1.0;
}

/**
 * Description not yet available.
 * \param
 */
funnel_dependent_df1b2variable::funnel_dependent_df1b2variable
  (const df1b2variable& x)
{
  df1b2variable::operator = (x);
  if (!df1b2_gradlist::no_derivatives)
  {
    //df1b2variable * tmp = (df1b2variable *) (this);
    //set_dependent_variable(*tmp);
  }
  df1b2_gradlist::set_no_derivatives();
}

/**
 * Description not yet available.
 * \param
 */
void funnel_init_df1b2variable::set_value(const init_df1b2vector& _x,
  const int& _ii)
{
  df1b2variable pen=0.0;
  ADUNCONST(init_df1b2vector,x)
  ADUNCONST(int,ii)
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
        if (!initial_params::straight_through_flag)
        {
          // df1b2variable& tmp = boundp(x(ii++),b.getminb(),b.getmaxb(),pen);
          // df1b2variable::operator = (tmp);
          df1b2variable::operator =
            (boundp(x(ii++),b.getminb(),b.getmaxb()));
        }
        else
        {
          df1b2variable::operator = (x(ii));
          *get_u()=boundp(*(x(ii++).get_u()),b.getminb(),b.getmaxb());
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
void funnel_init_df1b2variable::set_value(const init_df1b2vector& _x,
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
        laplace_approximation_calculator * l =lapprox;
        int uf=-1;
        if (ind_index>0)
        {
          uf=l->used_flags(ind_index);
        }
        if (uf > 1 && (l->hesstype ==2))
        {
          if (ind_index <=lapprox->xsize )
          {
            cout << " fixed effect used " << uf << " times" << endl;
            df1b2variable::operator = (boundp(x(ii++),b.getminb(),
              b.getmaxb()));
          }
          else
          {
             cout << lapprox->hesstype << endl;
             cout << " Error random effect used " << uf << " times" << endl;
             ad_exit(1);
          }
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
unsigned int funnel_init_var::nvarcalc_all(void)
{
  int n = 0;
  for (unsigned int i=0;i<num_vars;i++)
  {
    n += list[i]->nvar_calc();
  }
#ifndef OPT_LIB
  assert(n >= 0);
#endif
  return (unsigned int)n;
}

/**
 * Description not yet available.
 * \param
 */
void funnel_init_df1b2variable::xinit(init_df1b2vector& y,int& ii)
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
        //cout << setprecision(15) <<  << b.getminb() << " "
         // << b.getmaxb() << " " << y(ii) << " " << xu << endl;
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
  ii++;
}

/**
 * Description not yet available.
 * \param
 */
void funnel_init_df1b2variable::xinit(dvector& y,int& ii)
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
          " void funnel_init_df1b2variable::xinit  has not bee implemented"
          << endl;
          ad_exit(1);
      }
    }
  }
  ii++;
}

/*
void funnel_init_df1b2variable::xinit(dvector& y,int& ii)
{
  y(ii)= xu;
  ii++;
}
*/

/**
 * Description not yet available.
 * \param
 */
void funnel_init_df1b2variable::set_index(imatrix& y,int& ii)
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
void funnel_init_var::reset(init_df1b2vector& x)
{
  int ii=1;
  df1b2variable pen=0.0;
  for (unsigned int i=0;i<num_vars;i++)
  {
    list[i]->set_value(x,ii,pen);
    //list[i]->set_value(x,ii);
  }
  if (funnel_init_var::funnel_constraints_penalty)
  {
    delete funnel_init_var::funnel_constraints_penalty;
  }
  funnel_init_var::funnel_constraints_penalty=new df1b2variable(pen);
}


/*
funnel_init_df1b2vector::funnel_init_df1b2vector(const df1b2_init_vector & _x)
{
  ADUNCONST(df1b2_init_vector,x)
  //type=0;
  //pointer=0;
  p=&_x;
  int mmin=p->indexmin();
  int mmax=p->indexmax();
  int ind_index = (*p)(mmin).get_ind_index();
  if (ind_index<0)
  {
    add_to_inactive_list();
  }
  else
  {
    add_to_list();
  }
  df1b2variable::noallocate=1;
  df1b2vector::allocate(mmin,mmax);
  df1b2variable::noallocate=0;
}
*/

/**
 * Description not yet available.
 * \param
 */
funnel_init_df1b2vector::funnel_init_df1b2vector(const df1b2vector & _x)
{
  //ADUNCONST(df1b2_init_vector,x)
  // this seems to be right and not the above although it seemed to work
  ADUNCONST(df1b2_init_vector,x)
  p=&_x;
  int mmin=p->indexmin();
  int mmax=p->indexmax();
  int ind_index = x(mmin).get_ind_index();
  if (ind_index<0)
  {
    add_to_inactive_list();
  }
  else
  {
    add_to_list();
    for (int i=mmin;i<=mmax;i++)
    {
      ind_index = x(i).get_ind_index();
      lapprox->used_flags(ind_index)+=1;
    }
    df1b2variable::noallocate=1;
    df1b2vector::allocate(mmin,mmax);
    df1b2variable::noallocate=0;
  }
}
/**
Destructor
*/
funnel_init_df1b2vector::~funnel_init_df1b2vector()
{
  df1b2vector::deallocate();
}
/**
 * Description not yet available.
 * \param
 */
int funnel_init_df1b2vector::nvar_calc(void)
{
  return p->indexmax()-p->indexmin()+1;
}

/**
 * Description not yet available.
 * \param
 */
void funnel_init_df1b2vector::xinit(init_df1b2vector& y,int& ii)
{
  //df1b2_init_vector * vp = (df1b2_init_vector *) p;
  //int mmin=vp->indexmin();
  //int mmax=vp->indexmax();
  int mmin=p->indexmin();
  int mmax=p->indexmax();
  int i;
  for (i=mmin;i<=mmax;i++)
  {
    //y(ii)= value((*vp)(i));
    y(ii)= value((*p)(i));
    ii++;
  }
}

/**
 * Description not yet available.
 * \param
 */
void funnel_init_df1b2vector::set_index(imatrix& y,int& ii)
{
  df1b2_init_vector * vp = (df1b2_init_vector *) p;
  int mmin=vp->indexmin();
  int mmax=vp->indexmax();
  int i;
  for (i=mmin;i<=mmax;i++)
  {
    y(ii,1)= ( *vp)(i).get_ind_index();
    y(ii,2)= ii;
    ii++;
  }
}

/**
 * Description not yet available.
 * \param
 */
void funnel_init_df1b2vector::set_value(const init_df1b2vector& _x,
  const int& _ii,const df1b2variable& _pen)
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
// *****************************************************************
// *****************************************************************
// *****************************************************************

/**
 * Description not yet available.
 * \param
 */
funnel_init_bounded_df1b2vector::funnel_init_bounded_df1b2vector(
  const df1b2_init_bounded_vector& _x)
{
  ADUNCONST(df1b2_init_bounded_vector,x)
  //type=0;
  //pointer=0;
  p=&_x;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int ind_index = x(mmin).get_ind_index();
  if (ind_index<0)
  {
    add_to_inactive_list();
  }
  else
  {
    add_to_list();
  }
  df1b2variable::noallocate=1;
  df1b2vector::allocate(mmin,mmax);
  df1b2variable::noallocate=0;
}

/**
 * Description not yet available.
 * \param
 */
int funnel_init_bounded_df1b2vector::nvar_calc(void)
{
  return p->indexmax()-p->indexmin()+1;
}

/**
 * Description not yet available.
 * \param
 */
void funnel_init_bounded_df1b2vector::xinit(init_df1b2vector& y,int& ii)
{
  df1b2_init_bounded_vector * vp = (df1b2_init_bounded_vector *) p;
  int mmin=p->indexmin();
  int mmax=p->indexmax();
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
void funnel_init_bounded_df1b2vector::set_index(imatrix& y,int& ii)
{
  int mmin=p->indexmin();
  int mmax=p->indexmax();
  int i;
  for (i=mmin;i<=mmax;i++)
  {
    y(ii,1)= ( *(df1b2_init_bounded_vector *)(p) )(i).get_ind_index();
    y(ii,2)= ii;
    ii++;
  }
}

/**
 * Description not yet available.
 * \param
 */
void funnel_init_bounded_df1b2vector::set_value(const init_df1b2vector& _x,
  const int& _ii,const df1b2variable& _pen)
{
  ADUNCONST(int,ii)
  ADUNCONST(init_df1b2vector,x)
  df1b2_init_bounded_vector * vp = (df1b2_init_bounded_vector *) p;
  int mmin=p->indexmin();
  int mmax=p->indexmax();
  int i;
  for (i=mmin;i<=mmax;i++)
  {
    (*this)(i) = (x(ii++));
    if (!initial_params::straight_through_flag)
    {
      // df1b2variable& tmp = boundp(x(ii++),b.getminb(),b.getmaxb(),pen);
      // df1b2variable::operator = (tmp);
      (*this)(i) = (boundp(x(ii++),vp->getminb(),vp->getmaxb()));
    }
    else
    {
      (*this)(i) = (x(ii));
      *((*this)(i).get_u()) =
        boundp(*(x(ii++).get_u()),vp->getminb(),vp->getmaxb());
    }
  }
}
