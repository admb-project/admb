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

/*
funnel_init_df1b2vector::funnel_init_df1b2vector
  (const df1b2_init_bounded_vector & _x)
{
  ADUNCONST(df1b2_init_bounded_vector,x)
  type=1;
  pointer=&x;
  int mmin=x.indexmin();
  int mmax=x.indexmin();
  ind_index=x(mmin).get_ind_index();
  vxu.allocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    vxu(i)=*(x(i).get_u());
  }
  cout << "HERE" << endl;
}

  void funnel_init_df1b2vector::allocate(void){;}
  void funnel_init_df1b2vector::xinit(init_df1b2vector&,int& ii){;}
  void funnel_init_df1b2vector::xinit(dvector&,int& ii){;}
  void funnel_init_df1b2vector::set_value(const init_df1b2vector&,const int& ii){;}
  void funnel_init_df1b2vector::set_value(const init_df1b2vector&,const int& ii,
    const df1b2variable&){;}
  void funnel_init_df1b2vector::set_index(imatrix&,int& ii){;}
*/

/**
 * Description not yet available.
 * \param
 */
void funnel_init_df1b2vector::allocate(void)
{
  int mmin=p->indexmin();
  int mmax=p->indexmax();

  df1b2vector::allocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i)=value((*p)(i));
  }
  //cout << "HERE" << endl;
}
