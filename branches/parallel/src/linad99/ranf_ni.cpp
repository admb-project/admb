/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <math.h>


double auto_rand(long int& idum, int reset);
void reinitialize_auto_rand();
double randn(long int& n);

/**
 * Description not yet available.
 * \param
 */
  void dvector::fill_randbi_ni(long int& n, double p)
  {
    if ( p<0 || p>1)
    {
      cerr << "Error in dvar_vector::fill_randbi proportions of"
       " successes must lie between 0 and 1\n";
      ad_exit(1);
    }
    long int nn;
    nn=n;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      if (auto_rand(nn,1)<=p)
      {
        elem(i)=1;
      }
      else
      {
        elem(i)=0;
      } 
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void dvector::fill_randu_ni(long int& n)
  {
    long int nn;
    nn=n;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)=auto_rand(nn,1);
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void dmatrix::colfill_randu_ni(BOR_CONST int&j,long int&n)
  {
    long int nn;
    nn=n;
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i,j)=auto_rand(nn,1);
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void dmatrix::rowfill_randu_ni(BOR_CONST int& i,long int& n)
  {
    long int nn;
    nn=n;
    for (int j=colmin(); j<=colmax(); j++)
    {
      elem(i,j)=auto_rand(nn,1);
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void dvector::fill_randn_ni(long int& n)
  {
    long int nn;
    nn=n;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)=randn(nn);
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void dmatrix::fill_randn_ni(long int& n)
  {
    long int nn=n;
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i).fill_randn_ni(nn);
      nn+=2;
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void d3_array::fill_randn_ni(long int& n)
  {
    long int nn;
    nn=n;
    for (int i=slicemin(); i<=slicemax(); i++)
    {
      elem(i).fill_randn_ni(nn);
      nn+=2;  
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void d3_array::fill_randu_ni(long int& n)
  {
    long int nn;
    nn=n;
    for (int i=slicemin(); i<=slicemax(); i++)
    {
      elem(i).fill_randu_ni(nn);
      nn+=2;  
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void dmatrix::fill_randu_ni(long int& n)
  {
    long int nn;
    nn=n;
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i).fill_randu_ni(nn);
      nn+=2;  
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void dmatrix::colfill_randn_ni(BOR_CONST int&j,long int&n)
  {
    long int nn;
    nn=n;
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i,j)=randn(nn);
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void dmatrix::rowfill_randn_ni(BOR_CONST int& i,long int& n)
  {
    long int nn;
    nn=n;
    for (int j=colmin(); j<=colmax(); j++)
    {
      elem(i,j)=randn(nn);
    }
  }
