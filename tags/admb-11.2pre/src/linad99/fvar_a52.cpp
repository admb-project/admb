/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"
/*
    dvar_vector dvar_vector::operator()(int low,int high)
    {
      if (low>high)
      {
        cerr << " low index > high index in"
                 " dvar_vector::operator()(int low,int high)"  << endl;
        ad_exit(1);
      }
      if (low<indexmin())
      {
        cerr << "lower index out of bounds in"
                " dvar_vector::operator()(int low,int high)" << endl ;
        ad_exit(1);
      }
      if (high>indexmax())
      {
        cerr << "upper index out of bounds in"
                " dvar_vector::operator()(int low,int high)" << endl;
        ad_exit(1);
      }
      dvar_vector tmp(low,high);
      for (int i=low;i<=high;i++)
      {
        tmp(i)=(*this)(i);
      }
      return tmp;
    }
*/
