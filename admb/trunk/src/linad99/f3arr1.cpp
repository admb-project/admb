/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

#ifndef OPT_LIB
    prevariable dvar3_array::operator () (int k, int i, int j)
    {
      #ifdef SAFE_ARRAYS
       if (!allocated(*this))
       {
         cerr << "trying to access an unallocated object" << endl;
         ad_exit(21);
       }
        if (k<slicemin())
        {
          cerr << "array bound exceeded -- slice index too"
           " low in dvar3_array::operator(int,int,int)\n"
           " mimumum bound is " << slicemin() << "  you have "
           << k << "\n";
          ad_exit(1);
        }
        if (k>slicemax())
        {
          cerr << "array bound exceeded -- slice index too"
           " high in dvar3_array::operator(int,int,int)\n"
           " maximum bound is " << slicemax() << "  you have "
           << k << "\n";
          ad_exit(1);
        }
        return ( (elem(k))(i,j) );
      #else
        return ( (t[k].m[i]).va+j );
      #endif
    }


    dvar_vector& dvar3_array::operator () (int k, int i)
    {
      #ifdef SAFE_ARRAYS
        if (k<slicemin())
        {
          cerr << "array bound exceeded -- slice index too"
           " low in dvar3_array::operator(int,int)\n"
           " mimumum bound is " << slicemin() << "  you have "
           << k << "\n";
          ad_exit(1);
        }
        if (k>slicemax())
        {
          cerr << "array bound exceeded -- slice index too"
           " high in dvar3_array::operator(int,int)\n"
           " maximum bound is " << slicemax() << "  you have "
           << k << "\n";
          ad_exit(1);
        }
      #endif
      return ( (elem(k))(i) );
    }



 dvar_matrix& dvar3_array::operator[] (int i)
 {
   #ifdef SAFE_ARRAYS
     if (i<slicemin())
     {
       cerr << "matrix bound exceeded -- row index too low in dvar3_array::operator[]"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>slicemax())
     {
       cerr << "matrix bound exceeded -- row index too high in dvar3_array::operator[]"
             << "value was" << i;
       ad_exit(22);
     }
   #endif
   return( t[i]);
 }

 dvar_matrix& dvar3_array::operator() (int i)
 {
   #ifdef SAFE_ARRAYS
     if (!allocated(*this))
     {
       cerr << "trying to access an unallocated object" << endl;
       ad_exit(21);
     }
     if (i<slicemin())
     {
       cerr << "matrix bound exceeded -- row index too low in dvar3_array::operator[]"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>slicemax())
     {
       cerr << "matrix bound exceeded -- row index too high in dvar3_array::operator[]"
             << "value was" << i;
       ad_exit(22);
     }
   #endif
   return( t[i]);
 }
#endif
 void s9ee43q(void){int i=1;}

dvariable sum(_CONST dvar3_array& m)
{
  RETURN_ARRAYS_INCREMENT();
  dvariable tmp=0.;
  for (int i=m.indexmin();i<=m.indexmax();i++)
  {
    tmp+=sum(m.elem(i));
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}


