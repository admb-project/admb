/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"
#include "admb_messages.h"

/**
Construct vector with dimension [nrl to nrh]
of empty d3_array.

\param nrl lower vector index
\param nrh upper vector index
*/
d4_array::d4_array(int nrl, int nrh)
{
  allocate(nrl, nrh);
}
/**
Construct four_array_shape with initial values and
setting min and max. 

\param hsl used to set slice min
\param hsu used to set slice max
*/
four_array_shape::four_array_shape(int hsl, int hsu):
  ncopies(0),
  hslice_min(hsl),
  hslice_max(hsu)
{
  //,int sl,int su,int rl,
  // int ru,int cl,int cu)
  //slice_min=sl;
  //slice_max=su;
  //row_min=rl;
  //row_max=ru;
  //col_min=cl;
  //col_max=cu;
}
/**
Return the sum total of all the elements in arr4.

\param arr4 d4_array
*/
double sum(const d4_array& arr4)
{
  double total = 0.0;
  for (int i = arr4.indexmin(); i <= arr4.indexmax(); ++i)
  {
    total += sum(arr4.elem(i));
  }
  return total;
}

/**
 * Description not yet available.
 * \param
 */
 d4_array d4_array::sub(int nrl,int nrh)
 {
   if (allocated(*this))
   {
     d4_array tmp(nrl,nrh);
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
 d4_array::d4_array(const d4_array& m2)
 {
   if (m2.shape)
   {
     shape=m2.shape;
     (shape->ncopies)++;
     t = m2.t;
   }
   else
   {
     shape=NULL;
     t=NULL;
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void d4_array::shallow_copy(const d4_array& m2)
 {
   if (m2.shape)
   {
     shape=m2.shape;
     (shape->ncopies)++;
     t = m2.t;
   }
   else
   {
     shape=NULL;
     t=NULL;
   }
 }

/**
 * Description not yet available.
 * \param
 */
void d4_array::deallocate()
{
  if (shape)
  {
    if (shape->ncopies)
    {
      (shape->ncopies)--;
    }
    else
    {
      t += hslicemin();
      delete [] t;
      delete shape;
    }
  }
#if defined(DEBUG)
  else
  {
    cerr << "Warning -- trying to deallocate an unallocated d4_array.\n";
    ad_exit(1);
  }
#endif
}
/// Destructor
d4_array::~d4_array()
{
  deallocate();
}

/**
 * Description not yet available.
 * \param
 */
d4_array& d4_array::operator=(const d4_array& m)
 {
   int mmin=hslicemin();
   int mmax=hslicemax();
   if (mmin!=m.hslicemin() || mmax!=m.hslicemax())
   {
     cerr << "Incompatible bounds in"
      " d4_array& d4_array:: operator =  (const d4_array& m)"
      << endl;
     ad_exit(1);
    }
   for (int i=mmin; i<=mmax; i++)
   {
     (*this)(i)=m(i);
   }
   return *this;
 }

/**
Allocate d4_array with same dimensions as m1.
*/
void d4_array::allocate(const d4_array& m1)
{
  if ((shape = new four_array_shape(m1.hslicemin(),m1.hslicemax())) == 0)
  {
    cerr << " Error: d4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ( (t = new d3_array[hslicesize()]) == 0)
  {
    cerr << " Error: d4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= hslicemin();
  for (int i = hslicemin(); i <= hslicemax(); ++i)
  {
    t[i].allocate(m1[i]);
  }
}

  #ifndef OPT_LIB

/**
 * Description not yet available.
 * \param
 */
    d3_array& d4_array::operator () (int i)
    {
      if (i < hslicemin() || i > hslicemax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "d3_array& d4_array::operator() (int i)", hslicemin(), hslicemax(), i);
      }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    d3_array& d4_array::operator [] (int i)
    {
      if (i < hslicemin() || i > hslicemax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "d3_array& d4_array::operator[] (int i)",
        hslicemin(), hslicemax(), i);
      }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    dmatrix& d4_array::operator ( ) (int i ,int j)
    {
      if (i < hslicemin() || i > hslicemax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "dmatrix& d4_array::operator() (int i, int j)",
        hslicemin(), hslicemax(), i);
      }
      return ((*this)(i))(j);
    }

/**
 * Description not yet available.
 * \param
 */
    dvector& d4_array::operator ( ) (int i,int j,int k)
    {
      if (i < hslicemin() || i > hslicemax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "dvector& d4_array::operator() (int i, int j, int k)",
        hslicemin(), hslicemax(), i);
      }
      return (((*this)(i,j))(k));
    }

/**
 * Description not yet available.
 * \param
 */
    double& d4_array::operator ( ) (int i,int j,int k,int l)
    {
      if (i < hslicemin() || i > hslicemax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "double& d4_array::operator() (int i, int j, int k, int l)",
        hslicemin(), hslicemax(), i);
      }
      return ( ((*this)(i,j,k))(l));
    }

/**
 * Description not yet available.
 * \param
 */
const d3_array& d4_array::operator()(int i) const
    {
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "d3_array& d4_array::operator ( )" << endl;
          ad_exit(1);
        }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
const d3_array& d4_array::operator[](int i) const
    {
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "d3_array& d4_array::operator ( )" << endl;
          ad_exit(1);
        }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
const dmatrix& d4_array::operator()(int i, int j) const
    {
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "dmatrix& d4_array::operator ( )" << endl;
          ad_exit(1);
        }
      return ((*this)(i))(j);
    }

/**
 * Description not yet available.
 * \param
 */
const dvector& d4_array::operator()(int i, int j, int k) const
    {
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
          "dvector& d4_array::operator ( )" << endl;
          ad_exit(1);
        }
      return (((*this)(i,j))(k));
    }

/**
 * Description not yet available.
 * \param
 */
const double& d4_array::operator()(int i, int j, int k, int l) const
    {
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "double& d4_array::operator ( )"  << endl;
          ad_exit(1);
        }
      return ( ((*this)(i,j,k))(l));
    }

#endif

/**
Allocate arrays with dimension
[hsl to hsu] x [sl to sh] x [nrl to nrh] x [ncl to nch].

\param hsl lower d4_array index
\param hsu upper d4_array index
\param sl lower d3_array index
\param sh upper d3_array index
\param nrl lower row matrix index
\param nrh upper row matrix index
\param ncl lower column matrix index
\param nch upper column matrix index
*/
void d4_array::allocate(
  int hsl, int hsu,
  int sl, int sh,
  int nrl, int nrh,
  int ncl, int nch)
{
  if ((shape = new four_array_shape(hsl, hsu)) == 0)
  {
    cerr << " Error: d4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ( (t = new d3_array[hslicesize()]) == 0)
  {
    cerr << " Error: d4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= hslicemin();
  for (int i = hsl; i <= hsu; ++i)
  {
    (*this)(i).allocate(sl, sh, nrl, nrh, ncl, nch);
  }
}
/**
Allocate arrays with dimension
[hsl to hsu] x [sl to sh] x [nrl to nrh] x [ncl to nch].

\param hsl lower d4_array index
\param hsu upper d4_array index
\param sl lower d3_array index
\param sh upper d3_array index
\param nrl lower row matrix index
\param nrh upper row matrix index
\param ncl lower column matrix index
\param nch upper column matrix index
*/
void d4_array::allocate(
  int hsl, int hsu,
  int sl, int sh,
  int nrl, int nrh,
  const ivector& ncl, const ivector& nch)
{
  if ((shape = new four_array_shape(hsl, hsu)) == 0)
  {
    cerr << " Error: d4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new d3_array[hslicesize()]) == 0)
  {
    cerr << " Error: d4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= hslicemin();
  for (int i = hsl; i <= hsu; ++i)
  {
    (*this)(i).allocate(sl, sh, nrl, nrh, ncl, nch);
  }
}
/**
Allocate arrays with dimension
[hsl to hsu] x [sl to sh] x [nrl to nrh] x [ncl to nch].

\param hsl lower d4_array index
\param hsu upper d4_array index
\param sl lower d3_array index
\param sh upper d3_array index
\param nrl lower row matrix index
\param nrh upper row matrix index
\param ncl lower column matrix index
\param nch upper column matrix index
*/
void d4_array::allocate(
  int hsl, int hsu,
  int sl, int sh,
  const ivector& nrl, const ivector& nrh,
  const ivector& ncl, const ivector& nch)
{
  if ( (shape = new four_array_shape(hsl, hsu)) == 0)
  {
    cerr << " Error: d4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ( (t = new d3_array[hslicesize()]) == 0)
  {
    cerr << " Error: d4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= hslicemin();
  for (int i = hsl; i <= hsu; ++i)
  {
    (*this)(i).allocate(sl, sh, nrl(i), nrh(i), ncl(i), nch(i));
  }
}
/**
 * Description not yet available.
 * \param
 */
d4_array::d4_array(int hsl, int hsu, int sl, const ivector& sh,
  int nrl, const imatrix& nrh, int ncl, int nch)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
}

/**
Allocate arrays with dimension
[hsl to hsu] x [sl to sh] x [nrl to nrh] x [ncl to nch].

\param hsl lower d4_array index
\param hsu upper d4_array index
\param sl lower d3_array index
\param sh upper d3_array index
\param nrl lower row matrix index
\param nrh upper row matrix index
\param ncl lower column matrix index
\param nch upper column matrix index
*/
void d4_array::allocate(
  int hsl, int hsu,
  int sl, const ivector& sh,
  int nrl, const imatrix& nrh,
  int ncl, int nch)
{
  if ((shape = new four_array_shape(hsl, hsu)) == 0)
  {
    cerr << " Error: d4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new d3_array[hslicesize()]) == 0)
  {
    cerr << " Error: d4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= hslicemin();
  for (int i = hsl; i <= hsu; ++i)
  {
    (*this)(i).allocate(sl, sh(i), nrl, nrh(i), ncl, nch);
  }
}

/**
 * Description not yet available.
 * \param
 */
 d4_array::d4_array(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch)
 {
   allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
d4_array::d4_array(int hsl,int hsu, int sl,int sh,ivector nrl,ivector nrh,
  ivector ncl,ivector nch)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
}

/**
 * Description not yet available.
 * \param
 */
 void d4_array::initialize()
 {
   if (!(!(*this)))  // only initialize allocated objects
   {
     for (int i=hslicemin();i<=hslicemax();i++)
     {
       elem(i).initialize();
     }
   }
 }

/**
 * Description not yet available.
 * \param
 */
d4_array::d4_array(int hsl, int hsu, int sl, const ivector& sh, int nrl,
  const imatrix& nrh, int ncl, const i3_array& nch)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
}

/**
 * Description not yet available.
 * \param
 */
void d4_array::allocate(
  int hsl, int hsu,
  int sl, const ivector& sh,
  int nrl, const imatrix& nrh,
  int ncl, const i3_array& nch)
{
  if ((shape = new four_array_shape(hsl, hsu)) == 0)
  {
    cerr << " Error: d4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new d3_array[hslicesize()]) == 0)
  {
    cerr << " Error: d4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= hslicemin();
  for (int i = hsl; i <= hsu; ++i)
  {
    (*this)(i).allocate(sl, sh(i), nrl, nrh(i), ncl, nch(i));
  }
}

/**
 * Description not yet available.
 * \param
 */
d4_array::d4_array(int hsl,int hsu,const index_type& sl,
    const index_type& sh,const index_type& nrl,const index_type& nrh,
    const index_type& ncl,const index_type& nch)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
}

/**
Allocate arrays with dimension
[hsl to hsu] x [sl to sh] x [nrl to nrh] x [ncl to nch].

\param hsl lower d4_array index
\param hsu upper d4_array index
\param sl lower d3_array index
\param sh upper d3_array index
\param nrl lower row matrix index
\param nrh upper row matrix index
\param ncl lower column matrix index
\param nch upper column matrix index
*/
void d4_array::allocate(
  ad_integer hsl, ad_integer hsu,
  const index_type& sl, const index_type& sh,
  const index_type& nrl, const index_type& nrh,
  const index_type& ncl, const index_type& nch)
{
  unsigned int ss =
    static_cast<unsigned int>(hsu < hsl ? 0 : hsu - hsl + 1);
  if (ss > 0)
  {
    if ( (t = new d3_array[ss]) == 0)
    {
      cerr << " Error: d4_array unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(1);
    }
    if ( (shape=new four_array_shape(hsl,hsu)) == 0)
    {
      cerr << " Error: d4_array unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(1);
    }
    t -= int(hsl);
    for (int i=hsl; i<=hsu; i++)
    {
      const index_type& rsl=sl[i];
      const index_type& rsh=sh[i];
      const index_type& rnrl=nrl[i];
      const index_type& rnrh=nrh[i];
      const index_type& rncl=ncl[i];
      const index_type& rnch=nch[i];
      const ad_integer& aa=ad_integer(rsl);
      const ad_integer& bb=ad_integer(rsh);
      (*this)(i).allocate(aa,bb,rnrl,rnrh,rncl,rnch);
      //(*this)(i).allocate(sl[i],sh[i],nrl[i],nrh[i],ncl[i],nch[i]);
    }
  }
  else
  {
    allocate();
  }
}
/**
Allocate arrays with dimension
[hsl to hsu] x [sl to sh] x [nrl to nrh] x [ncl to nch].

\param hsl lower d4_array index
\param hsu upper d4_array index
\param sl lower d3_array index
\param sh upper d3_array index
\param nrl lower row matrix index
\param nrh upper row matrix index
\param ncl lower column matrix index
\param nch upper column matrix index
 */
void d4_array::allocate(
  int hsl, int hsu,
  const index_type& sl, const index_type& sh,
  const index_type& nrl, const index_type& nrh,
  const index_type& ncl,const index_type& nch)
{
  unsigned int ss =
    static_cast<unsigned int>(hsu < hsl ? 0 : hsu - hsl + 1);
  if (ss > 0)
  {
    if ((t = new d3_array[ss]) == 0)
    {
      cerr << " Error: d4_array unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
    }
    if ((shape = new four_array_shape(hsl, hsu)) == 0)
    {
      cerr << " Error: d4_array unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
    }
    t -= hsl;
    for (int i=hsl; i<=hsu; i++)
    {
      const index_type& rsl=sl[i];
      const index_type& rsh=sh[i];
      const index_type& rnrl=nrl[i];
      const index_type& rnrh=nrh[i];
      const index_type& rncl=ncl[i];
      const index_type& rnch=nch[i];
      const ad_integer& aa=ad_integer(rsl);
      const ad_integer& bb=ad_integer(rsh);
      (*this)(i).allocate(aa,bb,rnrl,rnrh,rncl,rnch);
      //(*this)(i).allocate(sl[i],sh[i],nrl[i],nrh[i],ncl[i],nch[i]);
    }
  }
  else
  {
    allocate();
  }
}
/**
Allocate arrays with empty columns matrices with dimension
[hsl to hsu] x [sl to sh] x [nrl to nrh].

\param hsl lower d4_array index
\param hsu upper d4_array index
\param sl lower d3_array index
\param sh upper d3_array index
\param nrl lower row matrix index
\param nrh upper row matrix index
*/
void d4_array::allocate(
  ad_integer hsl, ad_integer hsu,
  const index_type& sl, const index_type& sh,
  const index_type& nrl, const index_type& nrh)
{
  unsigned int ss =
    static_cast<unsigned int>(hsu < hsl ? 0 : hsu - hsl + 1);
  if (ss > 0)
  {
    if ((t = new d3_array[ss]) == 0)
    {
      cerr << " Error: d4_array unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
    }
    if ((shape=new four_array_shape(hsl, hsu)) == 0)
    {
      cerr << " Error: d4_array unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
    }
    t -= int(hsl);
    for (int i = hsl; i <= hsu; ++i)
    {
      const index_type& rsl = sl[i];
      const index_type& rsh = sh[i];
      const index_type& rnrl = nrl[i];
      const index_type& rnrh = nrh[i];
      const ad_integer& aa = ad_integer(rsl);
      const ad_integer& bb = ad_integer(rsh);
      (*this)(i).allocate(aa, bb, rnrl, rnrh);
    }
  }
  else
  {
    allocate();
  }
}

/**
Allocate 2d arrays with empty matrices with dimension
[hsl to hsu] x [sl to sh].

\param hsl lower d4_array index
\param hsu upper d4_array index
\param sl lower d3_array index
\param sh upper d3_array index
*/
void d4_array::allocate(
  ad_integer hsl,ad_integer hsu,
  const index_type& sl, const index_type& sh)
{
  unsigned int ss =
    static_cast<unsigned int>(hsu < hsl ? 0 : hsu - hsl + 1);
  if (ss > 0)
  {
    if ( (t = new d3_array[ss]) == 0)
    {
      cerr << " Error: d4_array unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(21);
    }
    if ( (shape=new four_array_shape(hsl,hsu)) == 0)
    {
      cerr << " Error: d4_array unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(21);
    }
    t -= int(hsl);
    for (int i=hsl; i<=hsu; i++)
    {
      const index_type& rsl=sl[i];
      const index_type& rsh=sh[i];
      const ad_integer& aa=ad_integer(rsl);
      const ad_integer& bb=ad_integer(rsh);
      (*this)(i).allocate(aa,bb);
    }
  }
  else
  {
    allocate();
  }
}
/**
Allocate vector of empty i3_array with dimension
[hsl to hsu].

\param hsl lower vector index
\param hsu upper vector index
*/
void d4_array::allocate(ad_integer hsl, ad_integer hsu)
{
  if (hsl > hsu)
  {
    allocate();
  }
  else
  {
    unsigned int size = static_cast<unsigned int>(hsu - hsl + 1);
    if ((t = new d3_array[size]) == 0)
    {
      cerr << " Error: d4_array unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(1);
    }
    if ((shape = new four_array_shape(hsl, hsu)) == 0)
    {
      cerr << " Error: d4_array unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(1);
    }
    t -= static_cast<int>(hsl);
    for (int i = hsl; i <= hsu; ++i)
    {
      elem(i).allocate();
    }
  }
}
