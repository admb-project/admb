/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <fvar.hpp>

sdmatrix::sdmatrix(int irh)
{
  allocate(irh);
}

sdmatrix::sdmatrix()
{
   unsigned nrl = 0;
   unsigned nrh = 0;
   shape=NULL;
   m=NULL;
}

void sdmatrix::allocate(int irh)
{
   unsigned nrl = 1;
   unsigned nrh = irh;
   index_min=nrl;
   index_max=nrl;

   #ifdef DIAG
     myheapcheck("Entering sdmatrix(nrh)" );
   #endif

   #ifdef DIAG
     cerr << "created a ncopies with address "<< farptr_tolong(ncopies)<<"\n";
   #endif
   m = new dvector [rowsize()];

   #ifdef DIAG
     cerr << "Created a sdmatrix with adress "<< farptr_tolong(m)<<"\n";
   #endif

   shape= new mat_shapex(m);
   m -= rowmin();

   for (int i=rowmin(); i<=rowmax(); i++)
   {
     m[i].allocate(1, i);
     #ifdef DIAG
       cerr << "Created a dvector with address "<< farptr_tolong(*(m+i))<<"\n";
     #endif
   }
   #ifdef DIAG
     myheapcheck("Leaving sdmatrix(nrh)" );
   #endif

}

sdmatrix::~sdmatrix()
{
  #ifdef DIAG
     myheapcheck("Entering ~sdmatrix() ");
  #endif
  deallocate();
}

void sdmatrix::deallocate()
{
  dmatrix::deallocate();
}

