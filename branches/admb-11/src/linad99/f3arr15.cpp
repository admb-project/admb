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
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
 dvar3_array::dvar3_array(ad_integer sl,ad_integer  sh,
     const index_type& nrl, const index_type& nrh,
     const index_type& ncl, const index_type& nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
   #ifdef SAFE_ARRAYS
     initialize();
   #endif
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar3_array::allocate(ad_integer sl,ad_integer  sh,
     const index_type& nrl, const index_type& nrh,
     const index_type& ncl, const index_type& nch)
 {
  
   if (sh<sl)
   {
     allocate();
   }
   else
   {
     #ifdef DIAG
       myheapcheck("Entering d3_array matrix(sl,sh,nrl,nrh,ncl,nch)" );
     #endif
     if ( (nrl.isinteger() && (sl !=nrl.indexmin() || sh !=nrl.indexmax())) ||
         (nrh.isinteger() && (sl !=nrh.indexmin() || sh !=nrh.indexmax())) )
     {
       cerr << nrl.isinteger() << " " << nrh.isinteger() << endl;
       cerr << sl << " " << nrl.indexmin() << endl;
       cerr << sh << " " << nrl.indexmax() << endl;
       cerr << sl << " " << nrh.indexmin() << endl;
       cerr << sh << " " << nrh.indexmax() << endl;
       cerr << "Incompatible array bounds in dvar3_array(int nrl,int nrh,"
        "const index_type& nrl,const index_type& nrh," 
        "const index_type& ncl,const index_type& nch)" << endl;
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
       t[i].allocate(nrl[i],nrh[i],ncl[i],nch[i]);
     }
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar3_array::allocate(ad_integer sl,ad_integer  sh,
     const index_type& nrl, const index_type& nrh)
 {
   if (sh<sl)
   {
     allocate();
   }
   else
   {
     #ifdef DIAG
       myheapcheck("Entering d3_array matrix(sl,sh,nrl,nrh,ncl,nch)" );
     #endif
     if ( (nrl.isinteger() && (sl !=nrl.indexmin() || sh !=nrl.indexmax())) ||
         (nrh.isinteger() && (sl !=nrh.indexmin() || sh !=nrh.indexmax())) )
     {
       cerr << nrl.isinteger() << " " << nrh.isinteger() << endl;
       cerr << sl << " " << nrl.indexmin() << endl;
       cerr << sh << " " << nrl.indexmax() << endl;
       cerr << sl << " " << nrh.indexmin() << endl;
       cerr << "Incompatible array bounds in dvar3_array(int nrl,int nrh,"
        "const index_type& nrl,const index_type& nrh," 
        "const index_type& ncl,const index_type& nch)" << endl;
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
       t[i].allocate(nrl[i],nrh[i]);
     }
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar3_array::allocate(ad_integer sl,ad_integer  sh)
 {
  
   if (sh<sl)
   {
     allocate();
   }
   else
   
   {
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
       t[i].allocate();
     }
   }
 }
