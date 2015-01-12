/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */



#include "fvar.hpp"




  dvector& dvector::operator /= ( CGNU_DOUBLE x)
  {
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)/=x;
    }
    return(*this);
  }

  dvector& dvector::operator *= ( CGNU_DOUBLE x)
  {
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)*=x;
    }
    return(*this);
  }
