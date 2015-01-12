/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <df1b2fun.h>
    typedef df1b2_header * ad_df1b2_header_ptr;
    typedef double * ad_double_ptr;

  df1b2_header_ptr_vector::df1b2_header_ptr_vector(int mmin,int mmax)
  {
    index_min=mmin;
    index_max=mmax;
    v = new ad_df1b2_header_ptr[mmax-mmin+1];
    if (v ==0)
    {
      cerr << "error allocating memory for"
        " df1b2_header_ptr_vector" << endl;
      ad_exit(1);
    }
    v-=indexmin();
  }
    
  df1b2_header_ptr_vector::~df1b2_header_ptr_vector()
  {
    if (v !=0)
    {
      v+=indexmin();
      delete [] v;
      v=0;
      index_min=0;
      index_max=-1;
    }
  }
    
  double_ptr_vector::double_ptr_vector(int mmin,int mmax)
  {
    index_min=mmin;
    index_max=mmax;
    v = new ad_double_ptr[mmax-mmin+1];
    if (v ==0)
    {
      cerr << "error allocating memory for"
        " double_ptr_vector" << endl;
      ad_exit(1);
    }
    v-=indexmin();
  }
    
  double_ptr_vector::~double_ptr_vector()
  {
    if (v !=0)
    {
      v+=indexmin();
      delete [] v;
      v=0;
      index_min=0;
      index_max=-1;
    }
  }
    
  
