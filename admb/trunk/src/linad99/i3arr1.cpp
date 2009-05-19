/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"
//#include "i3_array.h"

#ifndef OPT_LIB
    int& i3_array::operator () (int k, int i, int j)
    {
      #ifdef SAFE_ARRAYS
        if (k<slicemin())
        {
	  cerr << "array bound exceeded -- slice index too low in i3_array::operator(int,int)";
          ad_exit(1);
        }
        if (k>slicemax())
        {
	  cerr << "array bound exceeded -- slice index too high in i3_array::operator(int,int)";
          ad_exit(1);
        }
      #endif
      return ( (elem(k))(i,j) );
    }


    ivector& i3_array::operator () (int k, int i)
    {
      #ifdef SAFE_ARRAYS
        if (k<slicemin())
        {
	  cerr << "array bound exceeded -- slice index too low in i3_array::operator(int,int)";
          ad_exit(1);
        }
        if (k>slicemax())
        {
	  cerr << "array bound exceeded -- slice index too high in i3_array::operator(int,int)";
          ad_exit(1);
        }
      #endif
      return ( (elem(k))(i) );
    }

 imatrix& i3_array::operator[] (int i)
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

 imatrix& i3_array::operator() (int i)
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

//void ee51qo(void){int i=1;}


