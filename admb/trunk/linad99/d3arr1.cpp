/**
  * $Id$
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */
#define HOME_VERSION
#include "fvar.hpp"

#ifndef OPT_LIB
    double& d3_array::operator () (int k, int i, int j)
    {
      #ifdef SAFE_ARRAYS
        if (k<slicemin())
        {
          cerr << "array bound exceeded -- slice index too low in d3_array::operator(int,int)";
          ad_exit(1);
        }
        if (k>slicemax())
        {
          cerr << "array bound exceeded -- slice index too high in d3_array::operator(int,int)";
          ad_exit(1);
        }
      #endif
      return ( (elem(k))(i,j) );
    }


    dvector& d3_array::operator () (int k, int i)
    {
      #ifdef SAFE_ARRAYS
        if (k<slicemin())
        {
          cerr << "array bound exceeded -- slice index too low in d3_array::operator(int,int)";
          ad_exit(1);
        }
        if (k>slicemax())
        {
          cerr << "array bound exceeded -- slice index too high in d3_array::operator(int,int)";
          ad_exit(1);
        }
      #endif
      return ( (elem(k))(i) );
    }




 dmatrix& d3_array::operator[] (int i)
 {
   #ifdef SAFE_ARRAYS
     if (i<slicemin())
     {
       cerr << "matrix bound exceeded -- row index too low in 3d_array::operator[]"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>slicemax())
     {
       cerr << "matrix bound exceeded -- row index too high in 3d_array::operator[]"
             << "value was" << i;
       ad_exit(22);
     }
   #endif
   return(t[i]);
 }

 dmatrix& d3_array::operator() (int i)
 {
   #ifdef SAFE_ARRAYS
     if (i<slicemin())
     {
       cerr << "matrix bound exceeded -- row index too low in 3d_array::operator[]"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>slicemax())
     {
       cerr << "matrix bound exceeded -- row index too high in 3d_array::operator[]"
             << "value was" << i;
       ad_exit(22);
     }
   #endif
   return(t[i]);
 }
#endif

void ee51qo(void){int i=1;}

#undef HOME_VERSION

