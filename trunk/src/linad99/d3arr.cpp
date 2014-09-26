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
#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
double sum(const d3_array& m)
{
  double tmp=0.;
  for (int i=m.indexmin();i<=m.indexmax();i++)
  {
    tmp+=sum(m.elem(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
 d3_array d3_array::sub(int nrl,int nrh)
 {
   if (allocated(*this))
   {
     d3_array tmp(nrl,nrh);
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
 d3_array::d3_array(const d3_array_position& tpos)
 {
   int nrl=tpos.indexmin();
   int nrh=tpos.indexmax();
   allocate(nrl,nrh);
 }

/**
 * Description not yet available.
 * \param
 */
 d3_array::d3_array(int nrl,int nrh)
 {
   allocate(nrl,nrh);
 }

/**
 * Description not yet available.
 * \param
 */
 d3_array::d3_array(int sl,int sh,int nrl,int nrh,int ncl,int nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
#ifndef OPT_LIB
   initialize();
#endif
 }

/**
 * Description not yet available.
 * \param
 */
d3_array::d3_array(int sl, int sh, int nrl, int nrh, const ivector& ncl,
  int nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
#ifndef OPT_LIB
   initialize();
#endif
 }

/**
 * Description not yet available.
 * \param
 */
d3_array::d3_array(int sl, int sh, int nrl, int nrh, const ivector& ncl,
  const ivector& nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
#ifndef OPT_LIB
   initialize();
#endif
 }

/**
 * Description not yet available.
 * \param
 */
void d3_array::allocate(int sl, int sh, int nrl, int nrh, const ivector& ncl,
  int nch)
 {
   #ifdef DIAG
     myheapcheck("Entering d3_array matrix(sl,sh,nrl,nrh,ncl,nch)" );
   #endif
   if (sl !=ncl.indexmin() || sh !=ncl.indexmax())
   {
     cerr << "Incompatible array bounds in "
     " dmatrix(int nrl,int nrh,const ivector& ncl,const ivector& nch)" << endl;
     ad_exit(1);
   }
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dmatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl,nrh,ncl(i),nch);
   }
 }

/**
 * Description not yet available.
 * \param
 */
void d3_array::allocate(int sl, int sh, int nrl, int nrh, int ncl,
  const ivector& nch)
 {
   #ifdef DIAG
     myheapcheck("Entering d3_array matrix(sl,sh,nrl,nrh,ncl,nch)" );
   #endif
   if (sl !=nch.indexmin() || sh !=nch.indexmax())
   {
     cerr << "Incompatible array bounds in "
     " dmatrix(int nrl,int nrh, const ivector& ncl, const ivector& nch)"
     << endl;
     ad_exit(1);
   }
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dmatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl,nrh,ncl,nch(i));
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void d3_array::allocate(int sl,int sh,int nrl,int nrh,int ncl,int nch)
 {
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dmatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl,nrh,ncl,nch);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void d3_array::allocate(int sl,int sh,int nrl,int nrh)
 {
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dmatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl,nrh);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void d3_array::allocate(int sl,int sh,
  const index_type& nrl,const index_type& nrh)
 {
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dmatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl(i),nrh(i));
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void d3_array::allocate(int sl,int sh)
 {
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dmatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate();
   }
 }

/**
 * Description not yet available.
 * \param
 */
void d3_array::allocate(const d3_array& d3v)
 {
   int sl=d3v.slicemin();
   int sh=d3v.slicemax();
   //int nrl=d3v.rowmin();
   //int nrh=d3v.rowmax();
   //int ncl=d3v.colmin();
   //int nch=d3v.colmax();
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dmatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(d3v(i));
   }
 }

/**
 * Description not yet available.
 * \param
 */
void d3_array::allocate(int sl, int sh, const ivector& nrl, const ivector& nrh,
  const imatrix& ncl, const imatrix& nch)
 {
   if (sl !=nrl.indexmin() || sh !=nrl.indexmax() ||
       sl !=nrh.indexmin() || sh !=nrh.indexmax())
   {
     cerr << "Incompatible array bounds in "
     " dmatrix(int nrl,int nrh,const ivector& ncl,const ivector& nch)" << endl;
     ad_exit(1);
   }
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dmatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl(i),nrh(i),ncl(i),nch(i));
   }
 }

/**
 * Description not yet available.
 * \param
 */
void d3_array::allocate(int sl, int sh, const ivector& nrl, const ivector& nrh,
  int ncl, int nch)
 {
   if (sl !=nrl.indexmin() || sh !=nrl.indexmax() ||
       sl !=nrh.indexmin() || sh !=nrh.indexmax())
   {
     cerr << "Incompatible array bounds in "
     " dmatrix(int nrl,int nrh,const ivector& ncl, const ivector& nch)" << endl;
     ad_exit(1);
   }
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dmatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl(i),nrh(i),ncl,nch);
   }
 }

/**
 * Description not yet available.
 * \param
 */
void d3_array::allocate(int sl, int sh, const ivector& nrl, int nrh, int ncl,
  int nch)
 {
   if (sl !=nrl.indexmin() || sh !=nrl.indexmax())
   {
     cerr << "Incompatible array bounds in "
     "dmatrix(int nrl,int nrh, const ivector& ncl, const ivector& nch)" << endl;
     ad_exit(1);
   }
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dmatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl(i),nrh,ncl,nch);
   }
 }

/**
 * Description not yet available.
 * \param
 */
void d3_array::allocate(int sl, int sh, int nrl, const ivector& nrh, int ncl,
  int nch)
 {
   if ( sl !=nrh.indexmin() || sh !=nrh.indexmax())
   {
     cerr << "Incompatible array bounds in "
     "dmatrix(int nrl,int nrh,const ivector& ncl,const ivector& nch)" << endl;
     ad_exit(1);
   }
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dmatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl,nrh(i),ncl,nch);
   }
 }

/**
 * Description not yet available.
 * \param
 */
void d3_array::allocate(int sl, int sh, const ivector& nrl, const ivector& nrh,
  int ncl, const imatrix& nch)
 {
   if (sl !=nrl.indexmin() || sh !=nrl.indexmax() ||
       sl !=nrh.indexmin() || sh !=nrh.indexmax())
   {
     cerr << "Incompatible array bounds in "
     "dmatrix(int nrl,int nrh,int ncl,const ivector& nch)" << endl;
     ad_exit(1);
   }
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dmatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl(i),nrh(i),ncl,nch(i));
   }
 }

/**
 * Description not yet available.
 * \param
 */
void d3_array::allocate(int sl, int sh, int nrl, const ivector& nrh, int ncl,
  const imatrix& nch)
 {
   if (sl !=nrh.indexmin() || sh !=nrh.indexmax())
   {
     cerr << "Incompatible array bounds in "
     "dmatrix(int nrl,int nrh,int ncl,const ivector& nch)" << endl;
     ad_exit(1);
   }
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dmatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl,nrh(i),ncl,nch(i));
   }
 }

/**
 * Description not yet available.
 * \param
 */
void d3_array::allocate(int sl, int sh, const ivector& nrl, const ivector& nrh,
  const ivector& ncl, const ivector& nch)
 {
   if (sl !=nrl.indexmin() || sh !=nrl.indexmax() ||
       sl !=nrh.indexmin() || sh !=nrh.indexmax())
   {
     cerr << "Incompatible array bounds in "
     "dmatrix(int nrl,int nrh,const ivector& ncl,const ivector& nch)" << endl;
     ad_exit(1);
   }
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dmatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl(i),nrh(i),ncl(i),nch(i));
   }
 }

/**
 * Description not yet available.
 * \param
 */
void d3_array::allocate(int sl, int sh, int nrl, int nrh, const ivector& ncl,
  const ivector& nch)
 {
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dmatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl,nrh,ncl(i),nch(i));
   }
 }

/**
 * Description not yet available.
 * \param
 */
void d3_array::allocate(int sl, int sh, int nrl, const ivector& nrh, int ncl,
  const ivector& nch)
 {
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dmatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl,nrh(i),ncl,nch(i));
   }
 }

/**
 * Description not yet available.
 * \param
 */
d3_array::d3_array(int sl, int sh, int nrl, const ivector& nrh, int ncl,
  const ivector& nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
d3_array::d3_array(int sl, int sh, const ivector& nrl, const ivector& nrh,
  const imatrix& ncl, const imatrix& nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
d3_array::d3_array(int sl, int sh, const ivector& nrl, const ivector& nrh,
  int ncl, const imatrix& nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
d3_array::d3_array(int sl, int sh, int nrl, const ivector& nrh, int ncl,
  const imatrix& nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
d3_array::d3_array(int sl, int sh, int nrl, const ivector& nrh, int ncl,
  int nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
d3_array::d3_array(const d3_array& m2)
 {
   shape=m2.shape;
   if (shape)
   {
     (shape->ncopies)++;
   }
#ifdef SAFE_ALL
   else
   {
     cerr << "Making a copy of an unallocated d3_array"<<endl;
   }
#endif
   t = m2.t;
 }

/**
 * Description not yet available.
 * \param
 */
void d3_array::shallow_copy(const d3_array& m2)
 {
   shape=m2.shape;
   if (shape)
   {
     (shape->ncopies)++;
   }
#ifdef SAFE_ALL
   else
   {
     cerr << "Making a copy of an unallocated d3_array"<<endl;
   }
#endif
   t = m2.t;
 }

/**
 * Description not yet available.
 * \param
 */
 void d3_array::initialize()
 {
   if (!(!(*this)))  // only initialize allocated objects
   {
     for (int i=slicemin();i<=slicemax();i++)
     {
       elem(i).initialize();
     }
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void d3_array::deallocate()
 {
   if (shape)
   {
     //static int testflag=0;
     //if (testflag) test_the_pointer();
     t += slicemin();
     //int ss=slicesize();
     delete [] t;
     //if (testflag) test_the_pointer();
     delete shape;
     //if (testflag) test_the_pointer();
     t=NULL;
     shape=NULL;
   }
#ifdef SAFE_ALL
   else
   {
     cerr << "Warning -- trying to deallocate an unallocated dmatrix"<<endl;
   }
#endif
 }

/**
Destructor
*/
d3_array::~d3_array()
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
#ifdef SAFE_ALL
  else
  {
    cerr << "Warning -- trying to deallocate an unallocated d3_array"<<endl;
  }
#endif
}
/**
 * Description not yet available.
 * \param
 */
three_array_shape::three_array_shape(int sl,int su)
{
  slice_min=sl;
  slice_max=su;
  //row_min=rl;
  //row_max=ru;
  //col_min=cl;
  //col_max=cu;
  //nslices=su-sl+1;
  //nrows=ru-rl+1;
  //ncols=cu-cl+1;
  ncopies=0;
}
