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

typedef df1b2_header* ad_df1b2_header_ptr;
typedef double* ad_double_ptr;

/**
Constructor vector of ad_df1b2_header_ptr with dimension
[mmin to mmax].

\param mmin lower vector index
\param mmax upper vector index
*/
df1b2_header_ptr_vector::df1b2_header_ptr_vector(int mmin, int mmax)
{
  index_min = mmin;
  index_max = mmax;
  v = new ad_df1b2_header_ptr[
    static_cast<unsigned int>(mmax < mmin ? 0 : mmax - mmin + 1)];
  if (v == 0)
  {
    cerr << "error allocating memory for df1b2_header_ptr_vector\n";
    ad_exit(1);
  }
  v -= indexmin();
}
/**
Destructor
*/
df1b2_header_ptr_vector::~df1b2_header_ptr_vector()
{
  if (v !=0)
  {
    v += indexmin();
    delete [] v;
    v = 0;
    index_min = 0;
    index_max = -1;
  }
}
/**
Constructor vector of ad_double_ptr with dimension
[mmin to mmax].

\param mmin lower vector index
\param mmax upper vector index
*/
double_ptr_vector::double_ptr_vector(int mmin,int mmax)
{
  index_min = mmin;
  index_max = mmax;
  v = new ad_double_ptr[
    static_cast<unsigned int>(mmax < mmin ? 0 : mmax - mmin + 1)];
  if (v == 0)
  {
    cerr << "error allocating memory for double_ptr_vector\n.";
    ad_exit(1);
  }
  v-=indexmin();
}
/**
Destructor
*/
double_ptr_vector::~double_ptr_vector()
{
  if (v !=0)
  {
    v += indexmin();
    delete [] v;
    v = 0;
    index_min = 0;
    index_max = -1;
  }
}
