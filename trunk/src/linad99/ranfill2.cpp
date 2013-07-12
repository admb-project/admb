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
  void dvar_vector::fill_randu(long int& n)
  {
    long int nn;
    RETURN_ARRAYS_INCREMENT();
    nn=n;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)=auto_rand(nn,1);
    }
    reinitialize_auto_rand();
    RETURN_ARRAYS_DECREMENT();
  }

/**
 * Description not yet available.
 * \param
 */
  void dvar_vector::fill_randbi(long int& n, double p)
  {
    if ( p<0 || p>1)
    {
      cerr << "Error in dvar_vector::fill_randbi proportions of"
       " successes must lie between 0 and 1\n";
      ad_exit(1);
    }
    long int nn;
    RETURN_ARRAYS_INCREMENT();
    nn=n;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      if (auto_rand(nn,1)<=p)
      {
        elem(i)=1.;
      }
      else
      {
        elem(i)=0.;
      }
    }
    reinitialize_auto_rand();
    RETURN_ARRAYS_DECREMENT();
  }

/**
 * Description not yet available.
 * \param
 */
void dvar_matrix::colfill_randu(const int &j, long int &n)
  {
    long int nn;
    RETURN_ARRAYS_INCREMENT();
    nn=n;
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i,j)=auto_rand(nn,1);
    }
    reinitialize_auto_rand();
    RETURN_ARRAYS_DECREMENT();
  }

/**
 * Description not yet available.
 * \param
 */
void dvar_matrix::rowfill_randu(const int& i, long int& n)
  {
    long int nn;
    RETURN_ARRAYS_INCREMENT();
    nn=n;
    for (int j=colmin(); j<=colmax(); j++)
    {
      elem(i,j)=auto_rand(nn,1);
    }
    RETURN_ARRAYS_DECREMENT();
    reinitialize_auto_rand();
  }

/**
 * Description not yet available.
 * \param
 */
  void dvar_vector::fill_randn(long int& n)
  {
    long int nn;
    RETURN_ARRAYS_INCREMENT();
    nn=n;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)=randn(nn);
    }
    reinitialize_auto_rand();
    RETURN_ARRAYS_DECREMENT();
  }

/**
 * Description not yet available.
 * \param
 */
void dvar_matrix::colfill_randn(const int &j, long int &n)
  {
    long int nn;
    RETURN_ARRAYS_INCREMENT();
    nn=n;
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i,j)=randn(nn);
    }
    reinitialize_auto_rand();
    RETURN_ARRAYS_DECREMENT();
  }

/**
 * Description not yet available.
 * \param
 */
void dvar_matrix::rowfill_randn(const int& i, long int& n)
  {
    long int nn;
    RETURN_ARRAYS_INCREMENT();
    nn=n;
    for (int j=colmin(); j<=colmax(); j++)
    {
      elem(i,j)=randn(nn);
    }
    reinitialize_auto_rand();
    RETURN_ARRAYS_DECREMENT();
  }

/**
 * Description not yet available.
 * \param
 */
  void dvar_matrix::fill_randn(long int& n)
  {
    long int nn=n;
    RETURN_ARRAYS_INCREMENT();
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i).fill_randn_ni(nn);
      nn+=2;
    }
    reinitialize_auto_rand();
    RETURN_ARRAYS_DECREMENT();
  }

/**
 * Description not yet available.
 * \param
 */
  void dvar_matrix::fill_randu(long int& n)
  {
    long int nn=n;
    RETURN_ARRAYS_INCREMENT();
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i).fill_randn_ni(nn);
      nn+=2;
    }
    reinitialize_auto_rand();
    RETURN_ARRAYS_DECREMENT();
  }

/**
 * Description not yet available.
 * \param
 */
  void dvar3_array::fill_randn(long int& n)
  {
    long int nn;
    nn=n;
    for (int i=slicemin(); i<=slicemax(); i++)
    {
      elem(i).fill_randn_ni(nn);
      nn+=2;
    }
    reinitialize_auto_rand();
  }

/**
 * Description not yet available.
 * \param
 */
  void dvar3_array::fill_randu(long int& n)
  {
    long int nn;
    nn=n;
    for (int i=slicemin(); i<=slicemax(); i++)
    {
      elem(i).fill_randu_ni(nn);
      nn+=2;
    }
    reinitialize_auto_rand();
  }
