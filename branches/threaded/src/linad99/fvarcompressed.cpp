/*
 * $Id: dvector.cpp 422 2012-04-12 23:02:36Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

  // this is for a symmetrixc matrix
  dvar_vector operator * (const dvar_compressed_triplet& _M,
    const dvar_vector& _v)
  {
    ADUNCONST(dvar_compressed_triplet,M)
    ADUNCONST(dvar_vector,v)
    
    if (v.indexmin()!=1 ||
         M.get_m() !=v.indexmax() )
    {
      cerr << "Indices do not match in "
        " operator * (const dcompressed_triplet& _M,const dvector& _v)"
        << endl;
      ad_exit(1);
    }
    imatrix coords= M.get_coords();
    dvar_vector& x= M.get_x();
    dvar_vector tmp(1,v.indexmax());
    int mmin=x.indexmin();
    int mmax=x.indexmax();
    tmp.initialize();
    for (int i=mmin;i<=mmax;i++)
    {
      tmp(coords(1,i))+=x(i)*v(coords(2,i));
      if(coords(1,i)!=coords(2,i))
        tmp(coords(2,i))+=x(i)*v(coords(1,i));
    }
     
    return tmp;
  } 
    
  dvar_compressed_triplet::dvar_compressed_triplet(void)
  {
    n=-1;
    m=-1;
  }

   dvar_compressed_triplet & dvar_compressed_triplet::operator = 
     (const dvar_compressed_triplet& _M)
   {
     ADUNCONST(dvar_compressed_triplet,M)
     n=M.get_n();
     m=M.get_m();
     coords=M.get_coords();
     x=M.get_x();
     return *this;
   }

   dvar_compressed_triplet & dvar_compressed_triplet::operator = 
     (const dcompressed_triplet& _M)
   {
     ADUNCONST(dcompressed_triplet,M)
     n=M.get_n();
     m=M.get_m();
     coords=M.get_coords();
     x=M.get_x();
     return *this;
   }

