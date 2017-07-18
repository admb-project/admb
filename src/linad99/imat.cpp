/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"
#ifdef __TURBOC__
  #pragma hdrstop
#endif

/**
 * Description not yet available.
 * \param
 */
void imatrix::rowshift(int min )
{
  m = m + rowmin() - min;
  index_max+=min-index_min;
  index_min=min;
}

/**
Construct integer matrix with row dimension [nrl to nrh] where
each column is empty.

\param nrl lower row index
\param nrh upper row index
*/
imatrix::imatrix(int nrl, int nrh)
{
  allocate(nrl, nrh);
}

/**
 * Description not yet available.
 * \param
 */
 imatrix imatrix::sub(int nrl,int nrh)
 {
   if (allocated(*this))
   {
     imatrix tmp(nrl,nrh);
     for (int i=nrl; i<=nrh; i++)
     {
       tmp[i].shallow_copy((*this)(i));
     }
     return tmp;
   }
   else
   {
     return *this;
   }
 }
/**
Construct integer matrix with the dimensions 
[nrl to nrh] x [ncl to nch]

\param nrl lower row index
\param nrh upper row index
\param ncl lower column index
\param nch upper column index
*/
imatrix::imatrix(int nrl, int nrh, int ncl, int nch)
{
  allocate(nrl, nrh, ncl, nch);
}
/**
 * Description not yet available.
 * \param
 */
 imatrix::imatrix(const ad_integer& nrl,const ad_integer& nrh,
   const index_type& ncl,const index_type& nch)
 {
   allocate(nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
imatrix::imatrix(int nrl, int nrh, const ivector& iv)
 {
   allocate(nrl,nrh,iv);
 }

/**
Allocate integer matrix with row dimension [nrl to nrh] where
each column is equal to iv.

\param nrl lower row index
\param nrh upper row index
\param iv vector for each column
*/
void imatrix::allocate(int nrl, int nrh, const ivector& iv)
{
  if (nrl > nrh)
  {
    allocate();
  }
  else
  {
    index_min = nrl;
    index_max = nrh;

    if ((m = new ivector [rowsize()]) == 0)
    {
      cerr << " Error allocating memory in imatrix contructor\n";
      ad_exit(21);
    }
    if ((shape = new mat_shapex(m)) == 0)
    {
      cerr << " Error allocating memory in imatrix contructor\n";
      ad_exit(21);
    }
    m -= rowmin();
    for (int i = rowmin(); i <= rowmax(); ++i)
    {
      m[i].index_min=iv.index_min;
      m[i].index_max=iv.index_max;
      m[i].shape=iv.shape;
      if (m[i].shape)
      {
        (m[i].shape->ncopies)++;
        m[i].v = iv.v;
      }
    }
  }
}
/**
Allocate integer matrix with the dimensions 
[nrl to nrh] x [ncl to nch]

\param nrl lower row index
\param nrh upper row index
\param ncl lower column index
\param nch upper column index
*/
void imatrix::allocate(int nrl, int nrh, int ncl, int nch)
{
  allocate(nrl, nrh);
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i).allocate(ncl, nch);
  }
}
/// Does not allocate, but initializes imatrix members.
void imatrix::allocate()
{
  index_min = 1;
  index_max = -1;
  m = NULL;
  shape = NULL;
}
/**
Allocate ragged matrix with dimensions 
[nrl to nrh] x [ncl to nch] where ncl and nch are vectors on lower and upper
column indexes.

\param nrl lower row index
\param nrh upper row index
\param ncl vector of lower column indexes
\param nch vector of upper column indexes
*/
void imatrix::allocate(int nrl, int nrh, const ivector& ncl, const ivector& nch)
{
  allocate(nrl, nrh);
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i).allocate(ncl(i), nch(i));
  }
}
/**
Allocate ragged matrix with dimensions 
[nrl to nrh] x [ncl to nch] where nch is vector of upper column indexes.

\param nrl lower row index
\param nrh upper row index
\param ncl lower column index
\param nch vector of upper column indexes
*/
void imatrix::allocate(int nrl, int nrh, int ncl, const ivector& nch)
{
  allocate(nrl, nrh);
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i).allocate(ncl, nch(i));
  }
}
/// Copy constructor - Shallow
imatrix::imatrix(const imatrix& other)
{
  shallow_copy(other);
}
/**
Copy dimension and pointers in other.

\param other imatrix
*/
void imatrix::shallow_copy(const imatrix& other)
{
  index_min = other.index_min;
  index_max = other.index_max;
  if (other.shape)
  {
    shape = other.shape;
    (shape->ncopies)++;
    m = other.m;
  }
  else
  {
    shape = NULL;
    m = NULL;
  }
}

/**
 * Description not yet available.
 * \param
 */
imatrix::imatrix(int nrl, int nrh, const ivector& ncl, const ivector& nch)
 {
   allocate(nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
imatrix::imatrix(int nrl, int nrh, int ncl, const ivector& nch)
 {
   allocate(nrl,nrh,ncl,nch);
 }

/// Default constructor
imatrix::imatrix()
{
  allocate();
}
/// Destructor
imatrix::~imatrix()
{
  deallocate();
}
/**
Deallocate imatrix memory.
*/
void imatrix::deallocate()
{
  if (shape)
  {
    if (shape->ncopies)
    {
      (shape->ncopies)--;
    }
    else
    {
      m = static_cast<ivector*>(shape->get_pointer());
      delete [] m;
      m = NULL;
      delete shape;
      shape = NULL;
    }
  }
}

/**
Allocate integer matrix with row dimension [nrl to nrh] where
each column is empty.

\param nrl lower row index
\param nrh upper row index
*/
void imatrix::allocate(int nrl, int nrh)
{
  if (nrl > nrh)
  {
    allocate();
  }
  else
  {
    index_min = nrl;
    index_max = nrh;
    if ((m = new ivector[rowsize()]) == 0)
    {
      cerr << " Error allocating memory in imatrix contructor\n";
      ad_exit(21);
    }
    if ((shape = new mat_shapex(m)) == 0)
    {
      cerr << " Error allocating memory in imatrix contructor\n";
      ad_exit(21);
    }
    m -= indexmin();
  }
}
