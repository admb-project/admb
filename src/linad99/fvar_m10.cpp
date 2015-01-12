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

const unsigned int MAX_LINE_LENGTH = 10000;
const int MAX_FIELD_LENGTH = 500;
const int MAX_NUMBER_COLUMNS = 6550;
const int MAX_NUMBER_ROWS = 6550;

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
 * Description not yet available.
 * \param
 */
void dvar_matrix::fill( const char * s)
{

  int n = strlen(s);
  int braces = 0;
  int nrow = 0;
  int ncol = 0;

  ivector columns(1, MAXROWS);
  ivector k1(1, MAXROWS);
  ivector k2(1, MAXROWS);

  int k;
  for (k = 0; k < n; k++)
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

  if (nrow != rowsize())
  {
    if (nrow < rowsize())
    {
      cerr << " Not enough rows in the data for dvar_matrix::fill(const char *) \n";
      ad_exit(1);
    }
    else
    {
      cerr << " Too many rows in the data for dvar_matrix::fill(const char *) \n";
      ad_exit(1);
    }
  }

  int i;
  for (i=1; i<=nrow; i++)
  {
    if ( ((*this)[rowmin()+i-1]).size() != columns[i])
    {
      if ( ((*this)[rowmin()+i-1]).size() > columns[i])
      {
        cerr << " Not enough columns in the data in row "
             << i << " for dvar_matrix::fill(const char *) \n";
        ad_exit(1);
      }
      else
      {
        cerr << " Too many columns in the data in row "
             << i << " for dvar_matrix::fill(const char *) \n";
        ad_exit(1);
      }
    }
  }
    
  k = 0;
  for (i=rowmin(); i<=rowmax(); i++)
  {
    char * t;
//    t = (char*) new[strlen(s)+1];
    t = new char[strlen(s)+1];

    for (k = k1[i]; k <= k2[i]; k++)
    {
      t[k-k1[i]] = s[k];
    }
    t[k2[i]-k1[i]+1] = '\0';

    dvector tt(t);
    tt.shift(( (*this)(i)).indexmin() );

    (*this)(i)=tt;

    delete t;
  }
}
