/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

#ifndef OPT_LIB
    prevariable dvar_matrix::operator () (int i, int j)
    {
      #ifdef SAFE_ARRAYS
        if (i<rowmin())
        {
          cerr << "array bound exceeded -- index too low in dvar_matrix::operator(int,int)"
               << " first argument was " << i << endl;
      
          ad_exit(21);
        }
        if (i>rowmax())
        {
          cerr << "array bound exceeded -- index too high in dvar_matrix::operator(int,int)"
               << " first argument was " << i << endl;
          ad_exit(22);
        }
        if (j<elem(i).indexmin())
        {
          cerr << "array bound exceeded -- index too low in dvar_matrix::operator(int,int)"
               << " second argument was " << j << endl;
          ad_exit(23);
        }
        if (j>elem(i).indexmax())
        {
          cerr << "array bound exceeded -- index too high in dvar_matrix::operator(int,int)"
               << " second argument was " << j << endl;
          ad_exit(24);
        }
      #endif
      return ( m[i].va+j );
    }

 dvar_vector& dvar_matrix::operator[] (int i)
 {
   #ifdef SAFE_ARRAYS
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in dvar_matrix::operator[]"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>rowsize()+rowmin()-1)
     {
       cerr << "matrix bound exceeded -- row index too high in dvar_matrix::operator[]"
             << "value was" << i;
       ad_exit(22);
     }
   #endif
   return (m[i]);
 }

#ifdef USE_CONST
    _CONST prevariable dvar_matrix::operator () (int i, int j) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<rowmin())
        {
          cerr << "array bound exceeded -- index too low in dvar_matrix::operator(int,int)"
               << " first argument was " << i << endl;
          ad_exit(21);
        }
        if (j<elem(i).indexmin())
        {
          cerr << "array bound exceeded -- index too low in dvar_matrix::operator(int,int)"
               << " first argument was " << i << endl;
          ad_exit(22);
        }
        if (i>rowmax())
        {
          cerr << "array bound exceeded -- index too high in dvar_matrix::operator(int,int)"
               << " second argument was " << j << endl;
          ad_exit(23);
        }
        if (j>elem(i).indexmax())
        {
          cerr << "array bound exceeded -- index too high in dvar_matrix::operator(int,int)"
               << " second argument was " << j << endl;
          ad_exit(24);
        }
      #endif
      return ( m[i].va+j );
    }

  _CONST dvar_vector& dvar_matrix::operator[] (int i) _CONST
 {
   #ifdef SAFE_ARRAYS
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in dvar_matrix::operator[]"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>rowsize()+rowmin()-1)
     {
       cerr << "matrix bound exceeded -- row index too high in dvar_matrix::operator[]"
             << "value was" << i;
       ad_exit(22);
     }
   #endif
   return (m[i]);
 }

#endif

#endif

