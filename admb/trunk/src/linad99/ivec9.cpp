/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include "fvar.hpp"


  ivector& ivector::operator +=(const ivector& j)
  {
     int mmin=indexmin();
     int mmax=indexmax();
     if (mmin != j.indexmin() || mmax != j.indexmax())
     {
       cerr << " Incompatible array sizes in ivector::operator +=" << endl;
       exit(1);
     }    
     for (int i=mmin; i<=mmax; i++)
     {
       (*this)(i)+=j(i);
     }
     return(*this);
  }

  ivector& ivector::operator +=(int j)
  {
     int mmin=indexmin();
     int mmax=indexmax();
     for (int i=mmin; i<=mmax; i++)
     {
       (*this)(i)+=j;
     }
     return(*this);
  }

