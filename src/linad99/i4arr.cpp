/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>
#include "admb_messages.h"

/// Does NOT allocate, but initializes empty i4_array.
void i4_array::allocate()
{
  t = nullptr;
  shape = nullptr;
}
/// Initializes elements of i4_array to zero.
void i4_array::initialize()
{
  for (int i = hslicemin(); i <= hslicemax(); ++i)
  {
    if (allocated(elem(i)))
    {
      elem(i).initialize();
    }
  }
}
/// Default constructor
i4_array::i4_array()
{
  allocate();
}
/**
Construct vector of empty i3_array with dimension
[hsl to hsu].

\param hsl lower vector index
\param hsu upper vector index
*/
i4_array::i4_array(int hsl, int hsu)
{
  allocate(hsl, hsu);
}
/**
Allocate vector of empty i3_array with dimension
[hsl to hsu].

\param hsl lower vector index
\param hsu upper vector index
*/
void i4_array::allocate(int hsl, int hsu)
{
  if (hsl > hsu)
  {
    return allocate();
  }
  if ((t = new i3_array[static_cast<unsigned int>(hsu - hsl + 1)]) == 0)
  {
    cerr << " Error: i4_array unable to allocate t in "
         << "i4_array::allocate(int, int).\n";
    ad_exit(1);
  }
  if ((shape=new vector_shapex(hsl, hsu, t)) == 0)
  {
    cerr << " Error: i4_array unable to allocate shape in "
         << "i4_array::allocate(int, int).\n";
    ad_exit(1);
  }
  t -= indexmin();
  for (int i = hsl; i <= hsu; ++i)
  {
    elem(i).allocate();
  }
}
/**
 * Description not yet available.
 * \param
 */
i4_array::i4_array(
  int hsl, int hsu,
  int sl, const ivector& sh,
  int nrl, const imatrix& nrh,
  int ncl, const i3_array& nch)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
}
/**
Construct integer array with dimensions
[hsl to hsu] x [sl to sh] x [nrl to nrh] x [ncl to nch].

\param hsl lower i4_array index
\param hsu upper i4_array index
\param sl lower i3_array index
\param su upper i3_array index
\param nrl lower matrix row index
\param nrh upper matrix row index
\param ncl lower matrix column index
\param nch upper matrix column index
*/
i4_array::i4_array(
  int hsl, int hsu,
  int sl, int sh,
  int nrl, int nrh,
  int ncl, int nch)
{
  allocate(hsl, hsu, sl, sh, nrl, nrh, ncl, nch);
}
/**
Allocate array with dimensions
[hsl to hsu] x [sl to sh] x [nrl to nrh] x [ncl to nch].

\param hsl lower i4_array index
\param hsu upper i4_array index
\param sl lower i3_array index
\param su upper i3_array index
\param nrl lower matrix row index
\param nrh upper matrix row index
\param ncl lower matrix column index
\param nch upper matrix column index
*/
void i4_array::allocate(
  int hsl, int hsu,
  int sl, int sh,
  int nrl, int nrh,
  int ncl, int nch)
{
  if (hsl > hsu)
  {
    return allocate();
  }
  allocate(hsl, hsu);
  for (int i = hslicemin(); i <= hslicemax(); ++i)
  {
    elem(i).allocate(sl, sh, nrl, nrh, ncl, nch);
  }
}
/**
Allocate array with dimensions
[hsl to hsu] x [sl to sh] x [nrl to nrh] x [ncl to nch].

\param hsl lower i4_array index
\param hsu upper i4_array index
\param sl lower i3_array index
\param su upper i3_array index
\param nrl lower matrix row index
\param nrh upper matrix row index
\param ncl lower matrix column index
\param nch upper matrix column index
*/
void i4_array::allocate(
  const ad_integer& hsl, const ad_integer& hsu,
  const index_type& sl, const index_type& sh,
  const index_type& nrl, const index_type& nrh,
  const index_type& ncl, const index_type& nch)
{
  unsigned int ss =
    static_cast<unsigned int>(hsu < hsl ? 0 : hsu - hsl + 1);
  if (ss > 0)
  {
    if ((t = new i3_array[ss]) == 0)
    {
      cerr << " Error: i4_array unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(1);
    }
    if ((shape = new vector_shapex(hsl, hsu, t)) == 0)
    {
       cerr << " Error: i4_array unable to allocate memory in "
            << __FILE__ << ':' << __LINE__ << '\n';
       ad_exit(1);
    }
    t -= indexmin();
    for (int i = hsl; i <= hsu; ++i)
    {
      (*this)(i).allocate(
         ad_integer(sl(i)), ad_integer(sh(i)),
         nrl(i), nrh(i),
         ncl(i), nch(i));
    }
  }
  else
  {
    t = 0;
    shape = 0;
  }
}
/// Copy constructor
i4_array::i4_array(const i4_array& other)
{
  if (other.shape)
  {
    shape = other.shape;
    (shape->ncopies)++;
    t = other.t;
  }
  else
  {
    allocate();
  }
}
/// Destructor
i4_array::~i4_array()
{
  deallocate();
}
/// Deallocate i4_array memory.
void i4_array::deallocate()
{
  if (shape)
  {
    if (shape->ncopies)
    {
      (shape->ncopies)--;
    }
    else
    {
      t = static_cast<i3_array*>(shape->get_truepointer());
      delete [] t;
      delete shape;
      allocate();
    }
  }
}

#if !defined (OPT_LIB)

/**
 * Description not yet available.
 * \param
 */
    i3_array& i4_array::operator ( ) (int i)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("Index out of bounds",
        "i3_array& i4_array::operator ( ) (int i)", indexmin(), indexmax(), i);
      }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    i3_array& i4_array::operator [] (int i)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("Index out of bounds",
        "i3_array& i4_array::operator [] (int i)", indexmin(), indexmax(), i);
      }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    imatrix& i4_array::operator ( ) (int i ,int j)
    {
      return ((*this)(i))(j);
    }

/**
 * Description not yet available.
 * \param
 */
    ivector& i4_array::operator ( ) (int i,int j,int k)
    {
      return (((*this)(i,j))(k));
    }

/**
 * Description not yet available.
 * \param
 */
    int& i4_array::operator ( ) (int i,int j,int k,int l)
    {
      return ( ((*this)(i,j,k))(l));
    }

/**
 * Description not yet available.
 * \param
 */
const i3_array& i4_array::operator()(int i) const
    {
      if (i<indexmin() || i>indexmax())
      {
        cerr << "Index out of bounds in i4_array::operator () (int)"
             << endl;
        ad_exit(1);
      }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
const i3_array& i4_array::operator[](int i) const
    {
      if (i<indexmin() || i>indexmax())
      {
        cerr << "Index out of bounds in i4_array::operator () (int)"
             << endl;
        ad_exit(1);
      }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
const imatrix& i4_array::operator()(int i, int j) const
    {
      return ((*this)(i))(j);
    }

/**
 * Description not yet available.
 * \param
 */
const ivector& i4_array::operator()(int i, int j, int k) const
    {
      return (((*this)(i,j))(k));
    }

/**
 * Description not yet available.
 * \param
 */
const int& i4_array::operator()(int i, int j, int k, int l) const
    {
      return ( ((*this)(i,j,k))(l));
    }
#endif
