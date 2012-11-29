
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
  dvector operator * (const dcompressed_triplet& _M,const dvector& _v)
  {
    ADUNCONST(dcompressed_triplet,M)
    ADUNCONST(dvector,v)
    
    if (v.indexmin()!=1 ||
         M.get_m() !=v.indexmax() )
    {
      cerr << "Indices do not match in "
        " operator * (const dcompressed_triplet& _M,const dvector& _v)"
        << endl;
      ad_exit(1);
    }
    imatrix coords= M.get_coords();
    dvector x= M.get_x();
    dvector tmp(1,v.indexmax());
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
    
