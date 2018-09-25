/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include <admodel.h>

/// Default constructor
index_guts::index_guts()
{
  ncopies = new int;
  *ncopies=0;
}
/// Copy constructor
index_guts::index_guts(const index_guts& ig)
{
  ncopies = ig.ncopies;
  (*ncopies)++;
}
/// Destructor
index_guts::~index_guts()
{
  if (!(*ncopies))
  {
    delete ncopies;
    ncopies = NULL;
  }
}
/// Default constructor
smart_counter::smart_counter()
{
  ncopies = new int;
  *ncopies = 0;
}
/// Copy constructor
smart_counter::smart_counter(const smart_counter& sc)
{
    ncopies = sc.ncopies;
    (*ncopies)++;
}
/// Destructor
smart_counter::~smart_counter()
{
  if (*ncopies == 0)
  {
    delete ncopies;
    ncopies = 0;
  }
  else
  {
    (*ncopies)--;
  }
}
int* smart_counter::get_ncopies()
{
  return ncopies;
}
/// Copy constructor
index_type::index_type(const index_type& it): smart_counter(it)
{
  p = it.p;
}
/*
index_type::index_type(const data_int& x)
{
  p = new number_index(int(data_int(x)));
}
*/
/**
 * Description not yet available.
 * \param
 */
index_type::index_type(int x)
{
  p = new number_index(x);
}
/**
 * Description not yet available.
 * \param
 */
index_type::index_type(const ivector& x)
{
  p = new vector_index((const ivector&)(x));
}
/**
 * Description not yet available.
 * \param
 */
index_type::index_type(const imatrix& x)
{
  p = new matrix_index((const imatrix&)(x));
}
/**
 * Description not yet available.
 * \param
 */
index_type::index_type(const i3_array& x)
{
  p = new i3_index((i3_array&)(x));
}
/**
 * Description not yet available.
 * \param
 */
index_type::index_type(const i4_array& x)
{
  p = new i4_index((i4_array&)(x));
}
/**
 * Description not yet available.
 * \param
 */
index_type::index_type(const pre_index_type& pit)
{
  p = (*(*(pit.a)).p)[pit.i];
  // Dave uncommented this august 1998 because program crashed
  // (*p->ncopies)++;
}
/// Destructor
index_type::~index_type()
{
  if (*get_ncopies()==0)
  {
    if (!p)
    {
      cerr << "trying to delete a NULL optr in ~index_type()"  << endl;
    }
    else
    {
      if (!(*(p->ncopies)))
      {
        delete p;
        p = NULL;
      }
      else
      {
        (*(p->ncopies))--;
      }
    }
  }
}
/**
 * Description not yet available.
 * \param
 */
index_type index_type::operator[](int i) const
{
  return pre_index_type(this,i);
}

/**
 * Description not yet available.
 * \param
 */
index_type index_type::operator()(int i) const
{
  return pre_index_type(this,i);
}

/**
 * Description not yet available.
 * \param
 */
index_type index_type::operator[](int i)
{
  return pre_index_type(this,i);
}
/**
 * Description not yet available.
 * \param
 */
index_type index_type::operator()(int i)
{
  return pre_index_type(this,i);
}
int index_type::integer(void) const
{
  return int(*p);
}

/// Constructor for ivector
vector_index::vector_index(const ivector& v): ivector(v)
{
}
/// Destructor
vector_index::~vector_index() {}

/**
 * Description not yet available.
 * \param
 */
 dmatrix::dmatrix(const ad_integer& nrl,const ad_integer& nrh,
   const index_type& ncl,const index_type& nch)
 {
   allocate(nrl,nrh,ncl,nch);
 }

/**
Allocate matrix with dimensions [nrl to nrh] x [ncl to nch]
\param nrl lower matrix row index
\param nrl upper matrix row index
\param ncl lower matrix column index
\param ncl upper matrix column index
*/
void dmatrix::allocate(
  const ad_integer& nrl, const ad_integer& nrh,
  const index_type& ncl, const index_type& nch)
{
  if (nrh < nrl)
  {
    allocate();
  }
  else
  {
    if ((ncl.isinteger() && (nrl != ncl.indexmin() || nrh != ncl.indexmax()))
       || (nch.isinteger() && (nrl != nch.indexmin() || nrh != nch.indexmax())))
    {
      cerr << "Incompatible dmatrix bounds in " << __FILE__ << ':' << __LINE__ << ".\n";
      ad_exit(1);
    }
    index_min = int(nrl);
    index_max = int(nrh);
    if ((m = new dvector[rowsize()]) == 0)
    {
      cerr << " Error: dmatrix unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(1);
    }
    if ((shape = new mat_shapex(m)) == 0)
    {
      cerr << " Error: dmatrix unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(1);
    }
    m -= int(nrl);
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
 d3_array::d3_array(const ad_integer& sl,const ad_integer& sh,
   const index_type& nrl,const index_type& nrh,
   const index_type& ncl,const index_type& nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
 i3_array::i3_array(int sl,int sh,const index_type& nrl,const index_type& nrh,
   const index_type& ncl,const index_type& nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
 }

/**
Allocate array of matrices with dimensions
[sl to sh] x [nrl to nrh] x [ncl to nch].
\param sl lower vector index
\param sh upper vector index
\param nrl lower matrix row index
\param nrl upper matrix row index
\param ncl lower matrix column index
\param ncl upper matrix column index
*/
void i3_array::allocate(
  int sl, int sh,
  const index_type& nrl, const index_type& nrh,
  const index_type& ncl, const index_type& nch)
{
  if (sl > sh)
  {
    allocate();
  }
  else
  {  
    if ((nrl.isinteger() && (sl !=nrl.indexmin() || sh !=nrl.indexmax()))
       || (nch.isinteger() && (sl !=nch.indexmin() || sh !=nch.indexmax()))
       || (ncl.isinteger() && (sl !=ncl.indexmin() || sh !=ncl.indexmax()))
       || (nrh.isinteger() && (sl !=nrh.indexmin() || sh !=nrh.indexmax())))
    {
      cerr << "Incompatible i3_array bounds in " << __FILE__ << ':' << __LINE__ << ".\n";
      ad_exit(1);
    }
    if ((shape = new three_array_shape(sl,sh)) == 0)
    {
      cerr << " Error: d3_array unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(1);
    }
    if ((t = new imatrix[slicesize()]) == 0)
    {
      cerr << " Error: d3_array unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(1);
    }
    t -= slicemin();
    for (int i = sl; i <= sh; ++i)
    {
      t[i].allocate(nrl(i), nrh(i), ncl(i), nch(i));
    }
  }
}
/**
Allocate array of matrices with dimensions
[sl to sh] x [nrl to nrh] x [ncl to nch].
\param sl lower vector index
\param sh upper vector index
\param nrl lower matrix row index
\param nrl upper matrix row index
\param ncl lower matrix column index
\param ncl upper matrix column index
*/
void d3_array::allocate(
  const ad_integer& sl, const ad_integer& sh,
  const index_type& nrl, const index_type& nrh,
  const index_type& ncl, const index_type& nch)
{
  if (int(sl) > int(sh))
  {
    allocate();
  }
  else
  {
    if ((nrl.isinteger() && (sl !=nrl.indexmin() || sh !=nrl.indexmax()))
       || (nrh.isinteger() && (sl !=nrh.indexmin() || sh !=nrh.indexmax())))
    {
      cerr << "Incompatible d3_array bounds in " << __FILE__ << ':' << __LINE__ << ".\n";
      ad_exit(1);
    }
    if ((shape = new three_array_shape(sl, sh)) == 0)
    {
      cerr << " Error: d3_array unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(1);
    }
    if ((t = new dmatrix[slicesize()]) == 0)
    {
      cerr << " Error: d3_array unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(1);
    }
    t -= indexmin();
    for (int i = sl; i <= sh; ++i)
    {
      t[i].allocate(nrl[i], nrh[i], ncl[i], nch[i]);
    }
  }
}
/**
Allocate matrix on integers with dimension [nrl to nrh] x [ncl to nch].
\param nrl lower row matrix index
\param nrh upper row matrix index
\param ncl lower column matrix index
\param nch upper column matrix index
*/
void imatrix::allocate(
  const ad_integer& nrl, const ad_integer& nrh,
  const index_type& ncl, const index_type& nch)
{
  if (nrl > nrh)
  {
    allocate();
  }
  else
  {
    index_min = nrl;
    index_max = nrh;
    if ((ncl.isinteger() && (nrl != ncl.indexmin() || nrh != ncl.indexmax()))
       || (nch.isinteger() && (nrl != nch.indexmin() || nrh != nch.indexmax())))
    {
      cerr << "Incompatible imatrix bounds in " << __FILE__ << ':' << __LINE__ << ".\n";
      if(nrh==0) 
      {
        // Some models use 0 for columns to "turn off" a parameter, so we
        // don't want to exit in this case, just throw error.
        cerr << "0 columns - was this intentional?\n" ;
      }
      else
      {
        ad_exit(1);
      }
    }
    unsigned int ss = static_cast<unsigned int>(nrh - nrl + 1);
    if ((m = new ivector[ss]) == 0)
    {
      cerr << " Error: imatrix unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(1);
    }
    if ((shape = new mat_shapex(m)) == 0)
    {
      cerr << " Error: imatrix unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(1);
    }
    m -= int(nrl);
    for (int i = nrl; i <= nrh; ++i)
    {
      m[i].allocate(ncl(i), nch(i));
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
 dvector::dvector(const ad_integer& ncl,const index_type& nch)
 {
   allocate(ncl,nch);
 }

/**
Allocate vector of reals with dimension [_ncl to _nch].

\param _ncl lower vector index 
\param _nch upper vector index 
*/
void dvector::allocate(const ad_integer& _ncl,const index_type& _nch)
{
  int ncl = _ncl;
  int nch = ad_integer(_nch);
  unsigned int ss =
    static_cast<unsigned int>(nch < ncl ? 0 : nch - ncl + 1);
  if (ss > 0)
  {
    if ((v = new double[ss]) == 0)
    {
      cerr << " Error: dvector unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(1);
    }
#if defined(THREAD_SAFE)
    if ((shape = new ts_vector_shapex(ncl, nch, v)) == NULL)
#else
    if ((shape = new vector_shapex(ncl, nch, v)) == NULL)
#endif
    {
      cerr << " Error: dvector unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(1);
    }
    index_min = ncl;
    index_max = nch;
    v -= indexmin();
#ifdef SAFE_INITIALIZE
    for (int i = indexmin(); i <= indexmax(); ++i)
    {
      v[i] = 0.0;
    }
#endif
  }
  else
  {
    allocate();
  }
}

/**
 * Description not yet available.
 * \param
 */
 ivector::ivector(const ad_integer& ncl,const index_type& nch)
 {
   allocate(ncl,nch);
 }

/**
Allocate vector of integers with dimension [_ncl to _nch].

\param _ncl lower vector index 
\param _nch upper vector index 
*/
void ivector::allocate(const ad_integer& _ncl, const index_type& _nch)
{
  index_min = _ncl;
  index_max = ad_integer(_nch);
  unsigned int ss = static_cast<unsigned int>(
    index_max < index_min ? 0 : index_max - index_min + 1);
  if (ss > 0)
  {
   if ((v = new int[ss]) == 0)
   {
     cerr << " Error: ivector unable to allocate memory in "
          << __FILE__ << ':' << __LINE__ << '\n';
     ad_exit(1);
   }
   if ((shape = new vector_shapex(index_min, index_max, v)) == NULL)
   {
     cerr << " Error: ivector unable to allocate memory in "
          << __FILE__ << ':' << __LINE__ << '\n';
     ad_exit(1);
   }
   v -= indexmin();
#ifdef SAFE_INITIALIZE
   for (int i = indexmin(); i <= indexmax(); ++i)
   {
     v[i] = 0;
   }
#endif
  }
  else
  {
    allocate();
  }
}

/**
 * Description not yet available.
 * \param
 */
index_guts * number_index::operator [] (int i)
{
  return new number_index(int(*this));
}
ad_integer::ad_integer(const index_type& it) : d(it.integer()) {}
index_guts* matrix_index::operator [] (int i)
{
  return new vector_index(imatrix::operator [](i));
}
/// Destructor
matrix_index::~matrix_index()
{
  //cout << "in ~matrix_index()" << endl;
}
