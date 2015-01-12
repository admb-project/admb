/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include "fvar.hpp"
/*
    dvector dvector::operator()(int low,int high)
    {
      if (low>high)
      {
        cerr << " low index > high index in" 
                 " dvector::operator()(int low,int high)"  << endl;
        ad_exit(1);
      }
      if (low<indexmin())
      {
        cerr << "lower index out of bounds in"
                " dvector::operator()(int low,int high)" << endl ;
        ad_exit(1);
      }
      if (high>indexmax())
      {
        cerr << "upper index out of bounds in"
                " dvector::operator()(int low,int high)" << endl;
        ad_exit(1);
      }
      dvector tmp(low,high);
      for (int i=low;i<=high;i++)
      {
        tmp(i)=(*this)(i);
      }
      return tmp;
    }
*/
