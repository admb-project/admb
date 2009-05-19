/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <df1b2fnl.h>

funnel_init_df1b2matrix::funnel_init_df1b2matrix(const df1b2matrix & _x)
{
  //ADUNCONST(df1b2_init_matrix,x)
  ADUNCONST(df1b2matrix,x)
  p=&_x;
  int mmin=p->indexmin();
  int mmax=p->indexmax();
  
  int jmin=(*p)(mmin).indexmin();
  int ind_index = x(mmin,jmin).get_ind_index();
  if (ind_index<0) 
  {
    add_to_inactive_list();
  }
  else
  {
    add_to_list();
  }
  int i,j;
  ivector lb(mmin,mmax);
  ivector ub(mmin,mmax);
  lb(mmin)=(*p)(mmin).indexmin();
  ub(mmin)=(*p)(mmin).indexmax();
  int lf=0;
  int uf=0;
  for (i=mmin+1;i<=mmax;i++)
  {
    lb(i)=(*p)(i).indexmin();
    ub(i)=(*p)(i).indexmax();
    if (lb(i) !=lb(i-1))
      lf=1;
    if (ub(i) !=ub(i-1))
      uf=1;
  }
  // do we want this DF 01Nov05
  //df1b2variable::noallocate=1;
  if (lf ==1)
  {
    if (uf==1)
    {
      df1b2matrix::allocate(mmin,mmax,lb,ub);
    }
    else
    {
      df1b2matrix::allocate(mmin,mmax,lb,ub(mmin));
    }
  }
  else
  {
    if (uf==1)
    {
      df1b2matrix::allocate(mmin,mmax,lb(mmin),ub);
    }
    else
    {
      df1b2matrix::allocate(mmin,mmax,lb(mmin),ub(mmin));
    }
  }
  df1b2variable::noallocate=0;
}


int funnel_init_df1b2matrix::nvar_calc(void)
{
  int mmin=p->indexmin();
  int mmax=p->indexmax();
  int n=0;
  for (int i=mmin;i<=mmax;i++)
  {
    n+=(*p)(i).indexmax()-(*p)(i).indexmin()+1;
  }
  return n;
}

void funnel_init_df1b2matrix::xinit(init_df1b2vector& y,int& ii)
{ 
  df1b2_init_matrix * vp = (df1b2_init_matrix *) p;
  int mmin=vp->indexmin();
  int mmax=vp->indexmax();
  int i,j;
  for (i=mmin;i<=mmax;i++)
  {
    int jmin=(*vp)(i).indexmin();
    int jmax=(*vp)(i).indexmax();
    for (j=jmin;j<=jmax;j++)
    {
      y(ii)= value((*vp)(i,j));
      ii++;
    }
  }
}

  
void funnel_init_df1b2matrix::set_index(imatrix& y,int& ii)
{
  
  df1b2_init_matrix * vp = (df1b2_init_matrix *) p;
  int mmin=vp->indexmin();
  int mmax=vp->indexmax();
  int i,j;
  for (i=mmin;i<=mmax;i++)
  {
    int jmin=(*vp)(i).indexmin();
    int jmax=(*vp)(i).indexmax();
    for (j=jmin;j<=jmax;j++)
    {
      y(ii,1)= ( *vp)(i,j).get_ind_index();
      y(ii,2)= ii;
      ii++;
    }
  }
}
  
void funnel_init_df1b2matrix::set_value(const init_df1b2vector& _x,
  const int& _ii,const df1b2variable& _pen)
{
  ADUNCONST(int,ii)
  ADUNCONST(init_df1b2vector,x)
  int mmin=p->indexmin();
  int mmax=p->indexmax();
  int i,j;
  for (i=mmin;i<=mmax;i++)
  {
    int jmin=(*p)(i).indexmin();
    int jmax=(*p)(i).indexmax();
    for (j=jmin;j<=jmax;j++)
    {
      (*this)(i,j) = (x(ii++));
    }
  }
}
// *****************************************************************
// *****************************************************************
// *****************************************************************
/*
funnel_init_bounded_df1b2vector::funnel_init_bounded_df1b2vector(const df1b2_init_bounded_vector & _x)
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


int funnel_init_bounded_df1b2vector::nvar_calc(void)
{
  return p->indexmax()-p->indexmin()+1;
}

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
*/
