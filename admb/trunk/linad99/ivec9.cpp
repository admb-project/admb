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

