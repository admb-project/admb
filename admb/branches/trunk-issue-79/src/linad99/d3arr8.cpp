/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"
#ifdef USE_CONST
  #ifndef OPT_LIB 
    _CONST double& d3_array::operator () (int k, int i, int j) _CONST 
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


     _CONST dvector& d3_array::operator () (int k, int i) _CONST 
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




 _CONST  dmatrix& d3_array::operator[] (int i) _CONST 
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
#endif

 d3_array& d3_array::operator= (_CONST d3_array& m1)
 {
   if (slicemin() != m1.slicemin() || slicemax() != m1.slicemax())
   {
     cerr << " Incompatible array bounds in d3_array& operator = (_CONST d3_array&)\n";
     ad_exit(21);
   }

   if (t != m1.t)            // check for condition that both matrices
   {                         // don't point to the same object
     for (int i=slicemin();i<=slicemax();i++)
     {
       elem(i)=m1.elem(i);
     }
   }
   return(*this);
 }

 d3_array& d3_array::operator= (double x)
 {
   for (int i=slicemin();i<=slicemax();i++)
   {
     elem(i)=x;
   }
   return(*this);
 }


