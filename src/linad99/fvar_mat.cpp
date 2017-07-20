/**
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/

#include "fvar.hpp"
#include "param_init_bounded_number_matrix.h"
#ifndef OPT_LIB
  #include <cassert>
#endif
#ifdef __OPEN64__
  #define nullptr NULL
#endif

/**
Default constructor
*/
dvar_matrix::dvar_matrix()
{
  allocate();
}
/**
Copy constructor.

\param other
*/
dvar_matrix::dvar_matrix(const dvar_matrix& other)
{
  if (!(other))
  {
    //cerr << "Making a copy of an unallocated dvar_matrix" << endl;
    allocate();
  }
  else
  {
    index_min = other.index_min;
    index_max = other.index_max;
    shape = other.shape;
    if (shape)
    {
      (shape->ncopies)++;
    }
    m = other.m;
  }
}
/**
Copy constructor
*/
dvar_matrix::dvar_matrix(const dmatrix& other)
{
  index_min = other.index_min;
  index_max = other.index_max;
  if ((m = new dvar_vector[rowsize()]) == 0)
  {
     cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
     ad_exit(21);
  }
  if ( (shape =new mat_shapex(m)) == 0)
  {
     cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
  }

  m -= rowmin();
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    m[i].allocate(other(i).indexmin(), other(i).indexmax());
    elem(i) = other.elem(i);
  }
}
/**
Destructor
*/
dvar_matrix::~dvar_matrix()
{
  if (shape)
  {
    if (shape->ncopies)
    {
      (shape->ncopies)--;
    }
    else
    {
      deallocate();
    }
  }
}

/**
Constructs AD variable matrix with dimensions nrl to nrh by ncl to nch.

\param nrl row lower index
\param nrh row higher index
\param ncl column lower index
\param nch column higher index
*/
dvar_matrix::dvar_matrix(int nrl, int nrh, int ncl, int nch)
{
  allocate(nrl,nrh,ncl,nch);
#ifndef OPT_LIB
  initialize();
#endif
}

/**
 * Description not yet available.
 * \param
 */
 dvar_matrix::dvar_matrix(int nrl, int nrh, kkludge_object kk)
 {
   allocate(nrl,nrh);
#ifndef OPT_LIB
   initialize();
#endif
 }

/**
 * Description not yet available.
 * \param
 */
 dvar_matrix::dvar_matrix(int nrl,int nrh)
 {
   allocate(nrl,nrh);
#ifndef OPT_LIB
   initialize();
#endif
 }

/**
 * Description not yet available.
 * \param
 */
 dvar_matrix::dvar_matrix(const param_init_bounded_number_matrix& pibnm)
 {
   int indexmin = pibnm.indexmin();
   int indexmax = pibnm.indexmax();
   allocate(indexmin, indexmax);

#ifndef OPT_LIB
   initialize();
#endif

   for (int i = indexmin; i <= indexmax; i++)
   {
     dvar_vector v(pibnm(i));
     this->operator()(i) = v;
   }
 }

/**
 * Description not yet available.
 * \param
 */
 dvar_matrix dvar_matrix::sub(int nrl,int nrh)
 {
   if (allocated(*this))
   {
     dvar_matrix tmp(nrl,nrh);
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
Allocate variable matrix with dimension [nrl to nrh] where
columns are empty.  If nrl greater than nrh, then dvar_matrix
is initialized as empty.

\param nrl lower index
\param nrh upper index
*/
void dvar_matrix::allocate(int nrl, int nrh)
{
  if (nrl > nrh)
  {
    allocate();
  }
  else
  {
    index_min = nrl;
    index_max = nrh;
    if ((m = new dvar_vector[rowsize()]) == 0)
    {
      cerr << " Error allocating memory in dvar_matrix::allocate(int, int)\n";
      ad_exit(1);
    }
    if ((shape = new mat_shapex(m)) == 0)
    {
      cerr << " Error allocating memory in dvar_matrix::allocate(int, int)\n";
      ad_exit(1);
    }
    m -= rowmin();
    for (int i = nrl; i <= nrh; ++i)
    {
      elem(i).allocate();
    }
  }
}
/**
Allocates AD variable matrix with dimensions nrl to nrh by ncl to nch.

\param nrl row lower index
\param nrh row higher index
\param ncl column lower index
\param nch column higher index
*/
void dvar_matrix::allocate(int nrl, int nrh, int ncl, int nch)
{
  allocate(nrl, nrh);
  for (int i = nrl; i <= nrh; ++i)
  {
    elem(i).allocate(ncl, nch);
  }
}
/**
 * Description not yet available.
 * \param
 */
 void dvar_matrix::allocate(ad_integer nrl,ad_integer nrh)
 {
   if (nrl>nrh)
     allocate();
   else
   {
     index_min=nrl;
     index_max=nrh;
     if ( (m = new dvar_vector [rowsize()]) == 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor\n";
       ad_exit(21);
     }
     if ( (shape=new mat_shapex(m)) == 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor\n";
     }
     m -= rowmin();
   }
 }

/**
Allocate variable matrix using the same dimensions as m1.
*/
void dvar_matrix::allocate(const dmatrix& m1)
{
  if (m1.shape)
  {
    int nrl = m1.rowmin();
    int nrh = m1.rowmax();
    index_min = nrl;
    index_max = nrh;
    if ((m = new dvar_vector[rowsize()]) == 0)
    {
      cerr << " Error allocating memory in dvar_matrix contructor\n";
      ad_exit(21);
    }
    if ((shape = new mat_shapex(m)) == 0)
    {
      cerr << " Error allocating memory in dvar_matrix contructor\n";
    }
    m -= rowmin();
    for (int i = nrl; i <= nrh; ++i)
    {
      m[i].allocate(m1(i));
    }
  }
  else
  {
    //cerr << "Warning -- trying to make a dvar_matrix copy of an "
    // " unallocated dmatrix" << endl;
    allocate();
  }
}
/**
Allocate variable matrix using the same dimensions as m1.
*/
void dvar_matrix::allocate(const dvar_matrix& m1)
{
  if (m1.shape)
  {
    int nrl = m1.rowmin();
    int nrh = m1.rowmax();
    index_min = nrl;
    index_max = nrh;
    if ((m = new dvar_vector[rowsize()]) == 0)
    {
      cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
      ad_exit(21);
    }
    if ((shape=new mat_shapex(m)) == 0)
    {
      cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
    }
    m -= rowmin();
    for (int i = nrl; i <= nrh; ++i)
    {
      m[i].allocate(m1(i));
    }
  }
  else
  {
    //cerr << "Warning -- trying to make a dvar_matrix copy of an "
    //  "unallocated dvar_matrix" << endl;
    allocate();
  }
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix::dvar_matrix(int nrl, int nrh, const ivector& ncl,
  const ivector& nch)
 {
   allocate(nrl,nrh,ncl,nch);
#ifndef OPT_LIB
   initialize();
#endif
 }

/**
Allocate variable matrix with dimensions
[nrl to nrh] x [ncl to nch] where ncl and nch.

\param nrl lower row index
\param nrl upper row index
\param ncl vector of lower column indexes
\param nch vector of upper column indexes
*/
void dvar_matrix::allocate(
  int nrl, int nrh,
  const ivector& ncl, const ivector& nch)
{
  if (nrl > nrh)
  {
    allocate();
  }
  else
  {
    if (nrl != ncl.indexmin() || nrh != ncl.indexmax()
        || nrl != nch.indexmin() || nrh != nch.indexmax())
    {
      cerr << "Incompatible array bounds in "
       "dvar_matrix(int nrl, int nrh, const ivector& ncl, const ivector& nch)"
            << endl ;
      ad_exit(1);
    }
    index_min = nrl;
    index_max = nrh;
    if ((m = new dvar_vector[rowsize()]) == 0)
    {
       cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
       ad_exit(21);
    }
    if ((shape = new mat_shapex(m)) == 0)
    {
       cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
    }
    m -= rowmin();
    for (int i = nrl; i <= nrh; ++i)
    {
      m[i].allocate(ncl[i], nch[i]);
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix::dvar_matrix(int nrl, int nrh, int ncl, const ivector& nch)
 {
   allocate(nrl,nrh,ncl,nch);
#ifndef OPT_LIB
   initialize();
#endif
 }

/**
Allocate variable matrix with dimensions [nrl to nrh] x [ncl to nch]
where nch is a vector of indexes.
\param nrl lower row index
\param nrh upper row index
\param ncl lower column index
\param nch vector upper column indexes
*/
void dvar_matrix::allocate(int nrl, int nrh, int ncl, const ivector& nch)
{
  if (nrl>nrh)
  {
    allocate();
  }
  else
  {
    if (nrl != nch.indexmin() || nrh != nch.indexmax())
    {
      cerr << "Incompatible array bounds in "
       "dvar_matrix(int nrl, int nrh, const int& ncl, const ivector& nch)"
      << endl;
      ad_exit(1);
    }
    index_min = nrl;
    index_max = nrh;
    if ((m = new dvar_vector[rowsize()]) == 0)
    {
      cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
      ad_exit(21);
    }
    if ((shape = new mat_shapex(m)) == 0)
    {
      cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
    }
    m -= rowmin();
    for (int i = nrl; i <= nrh; ++i)
    {
      m[i].allocate(ncl,nch[i]);
    }
  }
}
/**
Allocate variable matrix with dimensions [nrl to nrh] x [ncl to nch]
where ncl is a vector of indexes.
\param nrl lower row index
\param nrh upper row index
\param ncl vector lower column indexes
\param nch upper column index
*/
void dvar_matrix::allocate(int nrl, int nrh, const ivector& ncl, int nch)
{
  if (nrl>nrh)
  {
    allocate();
  }
  else
  {
    if (nrl != ncl.indexmin() || nrh != ncl.indexmax())
    {
      cerr << "Incompatible array bounds in "
       "dvar_matrix(int nrl, int nrh, const ivector& ncl,int nch)"
       << endl;
      ad_exit(1);
    }
    index_min=nrl;
    index_max=nrh;
    if ( (m = new dvar_vector[rowsize()]) == 0)
    {
      cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
      ad_exit(21);
    }
    if ( (shape=new mat_shapex(m)) == 0)
    {
      cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
    }
    m -= rowmin();
    for (int i=nrl; i<=nrh; i++)
    {
      m[i].allocate(ncl[i],nch);
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
 void dvar_matrix::shallow_copy(const dvar_matrix& m2)
 {
   if (!(m2))
   {
     //cerr << "Making a copy of an unallocated dvar_matrix" << endl;
     index_min=0;
     index_max=-1;
     shape=NULL;
     m=NULL;
   }
   else
   {
     index_min=m2.index_min;
     index_max=m2.index_max;
     shape=m2.shape;
     (shape->ncopies)++;
     m = m2.m;
   }
 }
/**
Does not allocate, but initializes members.
*/
void dvar_matrix::allocate()
{
  index_min = 1;
  index_max = -1;
  shape = nullptr;
  m = nullptr;
}
/**
Deallocates memory.
*/
void dvar_matrix::deallocate()
{
   if (shape)
   {
     m = (dvar_vector*)(shape->get_pointer());
     delete [] m;
     m = NULL;

     delete shape;
     shape = NULL;
   }
#if defined(ADDEBUG_PRINT)
   else
   {
     cerr << "Warning -- trying to delete an unallocated dvar_matrix"<<endl;
   }
#endif
}
/**
Assigns dvar_matrix values to dvar_matrix.

\param values dmatrix
*/
dvar_matrix& dvar_matrix::operator=(const dvar_matrix& values)
{
  if (!allocated(*this))
  {
    shallow_copy(values);
  }
  else
  {
    if (rowmin() != values.rowmin() || rowmax() != values.rowmax())
    {
      cerr << "Error: Incompatible array bounds in "
            "dvar_matrix& operator=(const dvar_matrix&)\n";
      ad_exit(21);
    }
    // check for condition that both matrices don't point to the same object
    if (m != values.m)
    {
      for (int i = rowmin(); i <= rowmax(); ++i)
      {
        (*this)[i] = values[i];
      }
    }
  }
  return *this;
}
/**
Assigns dmatrix values to dvar_matrix.

\param values dmatrix
*/
dvar_matrix& dvar_matrix::operator=(const dmatrix& values)
{
  if (rowmin() != values.rowmin() || rowmax() != values.rowmax()
      || colmin() != values.colmin() || colmax() != values.colmax())
  {
    cerr << "Error: Incompatible array bounds in "
            "dvar_matrix& operator=(const dmatrix&)\n";
    ad_exit(21);
  }
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    (*this)[i] = values[i];
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
void copy_status(const ostream& _s, const dvar_matrix& m1)
  {
    ostream& s= (ostream&) _s;
    s << " matrix_copy flags \n";

    for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
    {
      copy_status(s,m1[i]);
    }
    s <<"\n";
  }
