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
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <string.h>
#include <ctype.h>
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

/**
 * Description not yet available.
 * \param
 */
 struct dvec_ptr_ptr
 {
   void ** m;
 };

const int MAXROWS = 5050;

/**
Fill values of dvar_matrix with text input from s with
format rowmin...rowmax where ith row is {colmin,...,colmax}.

Example dvar_matrix::fill("{1,2}{3,4}") produces 
dvar_matrix = 
1 2
3 4
\param s string
*/
void dvar_matrix::fill(const char* s)
{
  const size_t len = strlen(s);
#ifndef OPT_LIB
  assert(len <= INT_MAX);
#endif
  int n = static_cast<int>(len);
  int braces = 0;
  int nrow = 0;
  int ncol = 0;

  ivector columns(1, MAXROWS);
  ivector k1(1, MAXROWS);
  ivector k2(1, MAXROWS);

  for (int k = 0; k < n; k++)
  {
    if (s[k] == '{')
    {
      braces ++;
      if (braces != 1)
      {
        cerr << "Unbalanced braces in dvar_matrix::fill(const char * s)\n";
        cerr << "at character " << k << "\n";
        ad_exit(1);
      }
      ncol = 1;
      k1[nrow+1] = k;
    }
    else if (s[k] == '}')
    {
      braces --;
      if (braces != 0)
      {
        cerr << "Unbalanced braces in dvar_matrix::fill(const char * s)\n";
        cerr << "at character " << k << "\n";
        ad_exit(1);
      }
      k2[nrow+1] = k;
      nrow ++;
      if (nrow > MAXROWS)
      {
        cerr << "Too many rows in dvar_matrix::fill(const char * s)\n";
        ad_exit(1);
      }
      columns[nrow] = ncol;
    }
    else if (s[k] == ',')
    {
      if (braces != 0)
      {
        ncol++;
      }
    }
  }

  if (braces != 0)
  {
    cerr << "Unbalanced braces in dvar_matrix::fill(const char * s)\n";
    cerr << s << "\n";
    ad_exit(1);
  }

#if defined(__cplusplus) && (__cplusplus >= 201103L)
  [](unsigned int nrow, unsigned int rowsize)
  {
    if (nrow != rowsize)
    {
      if (nrow < rowsize)
      {
        cerr << " Not enough rows in the data for "
        "dvar_matrix::fill(const char*)\n";
        ad_exit(1);
      }
      else
      {
        cerr << " Too many rows in the data for "
        "dvar_matrix::fill(const char*)\n";
        ad_exit(1);
      }
    }
  } (static_cast<unsigned int>(nrow), rowsize());
#endif

  int i;
  for (i=1; i<=nrow; i++)
  {
    unsigned int size = ((*this)[rowmin()+i-1]).size();
    unsigned int column = static_cast<unsigned int>(columns[i]);
    if (size > column)
    {
      cerr << " Not enough columns in the data in row "
           << i << " for dvar_matrix::fill(const char *) \n";
      ad_exit(1);
    }
    else if (size < column)
    {
      cerr << " Too many columns in the data in row "
           << i << " for dvar_matrix::fill(const char *) \n";
      ad_exit(1);
    }
  }

  for (i=rowmin(); i<=rowmax(); i++)
  {
    char * t;
//    t = (char*) new[strlen(s)+1];
    t = new char[strlen(s)+1];

    for (int k = k1[i]; k <= k2[i]; k++)
    {
      t[k-k1[i]] = s[k];
    }
    t[k2[i]-k1[i]+1] = '\0';

    dvector tt(t);
    tt.shift(( (*this)(i)).indexmin() );

    (*this)(i)=tt;

    delete[] t;
    t = 0;
  }
}
