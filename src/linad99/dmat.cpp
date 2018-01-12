/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
 struct dvec_ptr_ptr
 {
   void ** m;
 };

/**
 * Description not yet available.
 * \param
 */
dmatrix::dmatrix(int nrl, int nrh, int ncl, int nch)
{
  allocate(nrl, nrh, ncl, nch);
}
/**
Allocate dmatrix with dimension [nrl to nrh] x [ncl to nch]
where ncl to nch are vector of indexes.

\param nrl lower row index
\param nrh upper row index
\param ncl lower column index
\param nch upper column index
*/
void dmatrix::allocate(int nrl, int nrh, int ncl, int nch)
{
  allocate(nrl, nrh);
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i).allocate(ncl, nch);
  }
}
/**
 * Description not yet available.
 * \param
 */
 dmatrix dmatrix::sub(int nrl,int nrh)
 {
   if (allocated(*this))
   {
     dmatrix tmp(nrl,nrh);
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
 * Description not yet available.
 * \param
 */
 dmatrix::dmatrix(int nrl,int nrh)
 {
   allocate(nrl,nrh);
 }

/**
Allocate dmatrix with row dimension [nrl to nrh] and empty columns. 

\param nrl lower row index
\param nrh upper row index
*/
void dmatrix::allocate(int nrl, int nrh)
{
  if (nrh < nrl)
  {
    allocate();
  }
  else
  {
    index_min = nrl;
    index_max = nrh;
    if ((m = new dvector[rowsize()]) == 0)
    {
      cerr << " Error allocating in dmatrix::allocate(int, int)\n";
      ad_exit(1);
    }
    if ((shape = new mat_shapex(m)) == 0)
    {
      cerr << " Error allocating in dmatrix::allocate(int, int)\n";
      ad_exit(1);
    }
    m -= rowmin();
  }
}
/**
Allocate dmatrix with row dimension [nrl to nrh] and empty columns. 

\param nrl lower row index
*/
void dmatrix::allocate(ad_integer nrl, ad_integer nrh)
{
  allocate(static_cast<int>(nrl), static_cast<int>(nrh));
}
/**
Returns the minimum value of matrix m.
Note: m is an allocated matrix.

\param m scalar matrix
*/
double min(const dmatrix& m)
{
  double minimum = min(m(m.rowmin()));
  for (int i = m.rowmin() + 1; i <= m.rowmax(); ++i)
  {
    double value = min(m(i));
    if (value < minimum) minimum = value;
  }
  return minimum;
}
/**
Returns the minimum value of matrix m.
Note: m is an allocated matrix.

\param m scalar matrix
*/
double max(const dmatrix& m)
{
  double maximum = max(m(m.rowmin()));
  for (int i = m.rowmin() + 1; i <= m.rowmax(); ++i)
  {
    double value = max(m(i));
    if (value > maximum) maximum = value;
  }
  return maximum;
}
/**
Allocate dmatrix using the same dimensions as other.

\param other dmatrix
*/
void dmatrix::allocate(const dmatrix& other)
{
  allocate(other.rowmin(), other.rowmax());
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i).allocate(other.elem(i));
  }
}
/**
Return true if vector dimensions match with indexmin and indexmax,
otherwise false.

\param vector ivector
\param indexmin
\param indexmax
*/
bool ivector_check(const ivector& vector, int indexmin, int indexmax)
{
  return !(vector.indexmin() == indexmin && vector.indexmax() == indexmax);
}
/**
Allocate dmatrix with dimension [nrl to nrh] x [ncl to nch]
where ncl to nch are vector of indexes.

\param nrl lower row index
\param nrh upper row index
\param ncl vector of lower column indexes
\param nch vector of upper column indexes
*/
void dmatrix::allocate(int nrl, int nrh, const ivector& ncl, const ivector& nch)
{
  if (nrl != ncl.indexmin() || nrh != ncl.indexmax()
      || nrl != nch.indexmin() || nrh != nch.indexmax())
  {
    cerr << "Incompatible array bounds in "
         << "dmatrix(int, int, const ivector&,const ivector&)\n";
    ad_exit(1);
  }
  allocate(nrl, nrh);
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i).allocate(ncl(i), nch(i));
  }
}
/**
Allocate dmatrix with dimension [nrl to nrh] x [ncl to nch]
where nch is vector of indexes.

\param nrl lower row index
\param nrh upper row index
\param ncl lower column index
\param nch vector of upper column indexes
*/
void dmatrix::allocate(int nrl, int nrh, int ncl, const ivector& nch)
{
  allocate(nrl, nrh);
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i).allocate(ncl, nch(i));
  }
}
/**
Allocate dmatrix with dimension [nrl to nrh] x [ncl to nch]
where nch is vector of indexes.

\param nrl lower row index
\param nrh upper row index
\param ncl vector of lower column indexes
\param nch upper column index
*/
void dmatrix::allocate(int nrl, int nrh, const ivector& ncl, int nch)
{
  if (nrl != ncl.indexmin() || nrh != ncl.indexmax())
  {
    cerr << "Incompatible array bounds in "
         << "dmatrix(int nrl, int nrh, int ncl, const ivector& nch)\n";
    ad_exit(1);
  }
  allocate(nrl, nrh);
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i).allocate(ncl(i), nch);
  }
}

/*
 dmatrix::dmatrix(void)
 {
   #ifdef DIAG
     myheapcheck("Entering dmatrix(nrl,nrh,ncl,nch)" );
   #endif

   shape = NULL;
   m=NULL;
 }
*/

/**
 * Description not yet available.
 * \param
 */
dmatrix::dmatrix(int nrl, int nrh, const ivector& ncl, const ivector& nch)
 {
   allocate(nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
dmatrix::dmatrix(int nrl, int nrh, int ncl, const ivector& nch)
 {
   allocate(nrl,nrh,ncl,nch);
 }

/// Copy constructor
dmatrix::dmatrix(const dmatrix& other)
{
  allocate();
  shallow_copy(other);
}
/**
Shallow copy values and dimensions from other to dmatrix.

\param other dmatrix
*/
void dmatrix::shallow_copy(const dmatrix& other)
{
  if (other.shape)
  {
    shape = other.shape;
    ++(shape->ncopies);
    m = other.m;

    index_min = other.index_min;
    index_max = other.index_max;
  }
#ifdef DEBUG
  else
  {
    cerr << "Warning -- Unable to shallow copy an unallocated dmatrix.\n";
  }
#endif
}
/// Destructor
dmatrix::~dmatrix()
{
  deallocate();
}
/**
Returns dvector with cube value of each element in vec.
Note: vec is allocated vector.

\param vec scalar vector
*/
dvector cube(const dvector& vec)
{
  dvector results;
  results.allocate(vec);
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results(i) = cube(vec(i));
  }
  return results;
}
/**
Returns dmatrix with cube value of each element in mat.
Note: mat is allocated matrix.

\param mat scalar matrix.
*/
dmatrix cube(const dmatrix& mat)
{
  dmatrix results;
  results.allocate(mat);
  for (int i = results.rowmin(); i <= results.rowmax(); ++i)
  {
    results(i) = cube(mat(i));
  }
  return results;
}
/// Deallocate dmatrix memory.
void dmatrix::deallocate()
{
  if (shape)
  {
    if (shape->ncopies)
    {
      --(shape->ncopies);
    }
    else
    {
      m = static_cast<dvector*>(shape->get_pointer());
      delete [] m;
      delete shape;
    }
    allocate();
  }
#ifdef DEBUG
  else
  {
    cerr << "Warning -- Unable to deallocate an unallocated dmatrix.\n";
  }
#endif
}
