/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
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
 void dvar3_array::initialize()
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
 dvar3_array dvar3_array::sub(int nrl,int nrh)
 {
   if (allocated(*this))
   {
     dvar3_array tmp(nrl,nrh);
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
 dvar3_array::dvar3_array (int nrl,int nrh)
 {
   allocate(nrl,nrh);
 }

/**
 * Description not yet available.
 * \param
 */
 dvar3_array::dvar3_array(int sl,int sh,int nrl,int nrh,int ncl,int nch)
 {
   if (sh<sl)
   {
     allocate();
     return;
   }
   allocate(sl,sh,nrl,nrh,ncl,nch);
   #ifdef SAFE_ARRAYS
     initialize();
   #endif
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar3_array::allocate(int sl,int sh,int nrl,int nrh,int ncl,int nch)
 {
   if (sh<sl)
   {
     allocate();
     return;
   }
   #ifdef DIAG
     myheapcheck("Entering dvar3_array matrix(sl,sh,nrl,nrh,ncl,nch)" );
   #endif
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dvar_matrix[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
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
 void dvar3_array::allocate(int sl,int sh,int nrl,int nrh)
 {
   if (sh<sl)
   {
     allocate();
     return;
   }
   #ifdef DIAG
     myheapcheck("Entering dvar3_array matrix(sl,sh,nrl,nrh,ncl,nch)" );
   #endif
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dvar_matrix[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
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
 void dvar3_array::allocate(int sl,int sh,
    const index_type& nrl,const index_type& nrh)
 {
   if (sh<sl)
   {
     allocate();
     return;
   }
   #ifdef DIAG
     myheapcheck("Entering dvar3_array matrix(sl,sh,nrl,nrh,ncl,nch)" );
   #endif
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dvar_matrix[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
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
 void dvar3_array::allocate(int sl,int sh)
 {
   if (sh<sl)
   {
     allocate();
     return;
   }
   #ifdef DIAG
     myheapcheck("Entering dvar3_array matrix(sl,sh,nrl,nrh,ncl,nch)" );
   #endif
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dvar_matrix[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
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
 dvar3_array::dvar3_array(int sl,int sh,int nrl,int nrh,
    _CONST ivector& ncl,int nch)
 {
   if (sh<sl)
   {
     allocate();
     return;
   }
   allocate(sl,sh,nrl,nrh,ncl,nch);
   #ifdef SAFE_ARRAYS
     initialize();
   #endif
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar3_array::allocate(int sl,int sh,int nrl,int nrh,
   _CONST ivector& ncl,int nch)
 {
   if (sh<sl)
   {
     allocate();
     return;
   }
   #ifdef DIAG
     myheapcheck("Entering dvar3_array matrix(sl,sh,nrl,nrh,ncl,nch)" );
   #endif
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dvar_matrix[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
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
 void dvar3_array::allocate(int sl,int sh,int nrl,int nrh,
   _CONST ivector& ncl,_CONST ivector& nch)
 {
   if (sh<sl)
   {
     allocate();
     return;
   }
   #ifdef DIAG
     myheapcheck("Entering dvar3_array matrix(sl,sh,nrl,nrh,ncl,nch)" );
   #endif
   if (sl !=ncl.indexmin() || sh !=ncl.indexmax() ||
       sl !=nch.indexmin() || sh !=nch.indexmax())
   {
     cerr << "Incompatible array bounds in dmatrix(int nrl,int nrh,_CONST ivector& ncl,_CONST ivector& nch)" << endl;
     ad_exit(1);
   }
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dvar_matrix[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
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
 void dvar3_array::allocate(int sl,int sh,int nrl,int nrh,
   int ncl,_CONST ivector& nch)
 {
   if (sh<sl)
   {
     allocate();
     return;
   }
   #ifdef DIAG
     myheapcheck("Entering dvar3_array matrix(sl,sh,nrl,nrh,ncl,nch)" );
   #endif
   if (sl !=nch.indexmin() || sh !=nch.indexmax())
   {
     cerr << "Incompatible array bounds in dmatrix(int nrl,int nrh,int ncl,_CONST ivector& nch)" << endl;
     ad_exit(1);
   }
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dvar_matrix[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
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
 dvar3_array::dvar3_array(_CONST d3_array& m1)
 {
   allocate(m1);
   for (int i=slicemin(); i<=slicemax(); i++)
   {
     t[i]=m1[i];
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar3_array::allocate(_CONST d3_array& m1)
 {
   #ifdef DIAG
     myheapcheck("Entering dvar3_array matrix(_CONST d3_array& m1)" );
   #endif
   if ( (shape=new three_array_shape(m1.indexmin(),m1.indexmax())) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dvar_matrix[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=slicemin(); i<=slicemax(); i++)
   {
     t[i].allocate(m1[i]);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar3_array::allocate(_CONST dvar3_array& m1)
 {
   #ifdef DIAG
     myheapcheck("Entering dvar3_array matrix(_CONST d3_array& m1)" );
   #endif
   if ( (shape=new three_array_shape(m1.slicemin(),m1.slicemax())) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dvar_matrix[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=slicemin(); i<=slicemax(); i++)
   {
     t[i].allocate(m1[i]);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 dvar3_array::dvar3_array(int sl,int sh,_CONST ivector& nrl,_CONST ivector& nrh,
    ivector& ncl,_CONST ivector& nch)
 {
   if (sh<sl)
   {
     allocate();
     return;
   }
   allocate(sl,sh,nrl,nrh,ncl,nch);
   #ifdef SAFE_ARRAYS
     initialize();
   #endif
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar3_array::allocate(int sl,int sh,_CONST ivector& nrl,_CONST ivector& nrh,
   _CONST ivector& ncl,_CONST ivector& nch)
 {
   if (sh<sl)
   {
     allocate();
     return;
   }
   #ifdef DIAG
     myheapcheck("Entering d3_array matrix(sl,sh,nrl,nrh,ncl,nch)" );
   #endif
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dvar_matrix[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl[i],nrh[i],ncl[i],nch[i]);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 dvar3_array::dvar3_array(int sl,int sh,int nrl,_CONST ivector& nrh,
    int ncl,_CONST ivector& nch)
 {
   if (sh<sl)
   {
     allocate();
     return;
   }
   allocate(sl,sh,nrl,nrh,ncl,nch);
   #ifdef SAFE_ARRAYS
     initialize();
   #endif
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar3_array::allocate(int sl,int sh,int nrl,_CONST ivector& nrh,
    int ncl,_CONST ivector& nch)
 {
   if (sh<sl)
   {
     allocate();
     return;
   }
   #ifdef DIAG
     myheapcheck("Entering d3_array matrix(sl,sh,nrl,nrh,ncl,nch)" );
   #endif
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dvar_matrix[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl,nrh[i],ncl,nch[i]);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 dvar3_array::dvar3_array(int sl,int sh,int nrl,_CONST ivector& nrh,
    int ncl,int nch)
 {
   if (sh<sl)
   {
     allocate();
     return;
   }
   allocate(sl,sh,nrl,nrh,ncl,nch);
   #ifdef SAFE_ARRAYS
     initialize();
   #endif
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar3_array::allocate(int sl,int sh,int nrl,_CONST ivector& nrh,
    int ncl,int nch)
 {
   #ifdef DIAG
     myheapcheck("Entering d3_array matrix(sl,sh,nrl,nrh,ncl,nch)" );
   #endif
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dvar_matrix [ss]) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl,nrh[i],ncl,nch);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 dvar3_array::dvar3_array(_CONST dvar3_array& m2)
 {
   shape=m2.shape;
   if (shape) (shape->ncopies)++;
   t = m2.t;
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar3_array::shallow_copy(_CONST dvar3_array& m2)
 {
   shape=m2.shape;
   if (shape) (shape->ncopies)++;
   t = m2.t;
 }

/**
 * Description not yet available.
 * \param
 */
 dvar3_array::~dvar3_array() 
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
#  ifdef SAFE_ARRAYS
   else
   {
     //cerr << "Warning -- trying to deallocate an unallocated dmatrix"<<endl;
   }
#  endif
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar3_array::deallocate()
 {
   if (shape)
   {
     t += slicemin();
     //int ss=slicesize();
     delete [] t;
     delete shape;
     t=NULL;
     shape=NULL;
   }
#  ifdef SAFE_ARRAYS
   else
   {
     //cerr << "Warning -- trying to deallocate an unallocated dmatrix"<<endl;
   }
#  endif
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar3_array::allocate(int sl,int sh,_CONST ivector& nrl,_CONST ivector& nrh,
    int ncl,int nch)
 {
   if (sl !=nrl.indexmin() || sh !=nrl.indexmax() ||
       sl !=nrh.indexmin() || sh !=nrh.indexmax())
   {
     cerr << "Incompatible array bounds in dmatrix(int nrl,int nrh,_CONST ivector& ncl,_CONST ivector& nch)" << endl;
     ad_exit(1);
   }
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dvar_matrix[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
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
 void dvar3_array::allocate(int sl,int sh,_CONST ivector& nrl,int nrh,
    int ncl,int nch)
 {
   if (sh<sl)
   {
     allocate();
     return;
   }
   if (sl !=nrl.indexmin() || sh !=nrl.indexmax()) 
   {
     cerr << "Incompatible array bounds in dmatrix(int nrl,int nrh,_CONST ivector& ncl,_CONST ivector& nch)" << endl;
     ad_exit(1);
   }
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new dvar_matrix[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl(i),nrh,ncl,nch);
   }
 }
