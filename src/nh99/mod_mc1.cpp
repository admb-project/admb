/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>

#ifdef __GNUDOS__
  #include <gccmanip.h>
#endif

void initial_params::add_random_vector(BOR_CONST dvector& x)
{
  int ii=1;
  for (int i=0;i<num_initial_params;i++)
  {
    if (withinbound(0,(varsptr[i])->phase_start,current_phase))
    {
      (varsptr[i])->add_value((BOR_CONST dvector&)(x),ii);
    }
  }
}


void param_init_number::add_value(BOR_CONST dvector& ndev,BOR_CONST int& _ii)
{
  int& ii=(int&) _ii;
  (*this)+=ndev(ii);
  ii++;
}

void param_init_bounded_number::add_value(BOR_CONST dvector& ndev,BOR_CONST int& _ii)
{
  int& ii=(int&) _ii;
  (*this)+=ndev(ii);
  ii++;
}



void param_init_vector::add_value(BOR_CONST dvector& ndev,BOR_CONST int& _ii)
{
  int& ii=(int&) _ii;
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i)+=ndev(ii);
    ii++;
  }
}

void param_init_bounded_vector::add_value(BOR_CONST dvector& ndev,BOR_CONST int& _ii)
{
  int& ii=(int&) _ii;
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i)+=ndev(ii);
    ii++;
  }
}

void param_init_matrix::add_value(BOR_CONST dvector& ndev,BOR_CONST int& _ii)
{
  int& ii=(int&) _ii;
  int rmin=rowmin();
  int rmax=rowmax();
  for (int i=rmin;i<=rmax;i++)
  {
    int cmin=(*this)(i).indexmin();
    int cmax=(*this)(i).indexmax();
    for (int j=cmin;j<=cmax;j++)
    {
      (*this)(i,j)+=ndev(ii); 
      ii++;
    }
  }
}

void param_init_bounded_matrix::add_value(BOR_CONST dvector& ndev,BOR_CONST int& _ii)
{
  int& ii=(int&) _ii;
  int rmin=rowmin();
  int rmax=rowmax();
  for (int i=rmin;i<=rmax;i++)
  {
    int cmin=(*this)(i).indexmin();
    int cmax=(*this)(i).indexmax();
    for (int j=cmin;j<=cmax;j++)
    {
      (*this)(i,j)+=ndev(ii); 
      ii++;
    }
  }
}



