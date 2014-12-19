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
 dvar_matrix::dvar_matrix(const ad_integer& nrl,const ad_integer& nrh,
   const index_type& ncl,const index_type& nch)
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
 void dvar_matrix::allocate(const ad_integer& nrl,const ad_integer& nrh,
   const index_type& ncl,const index_type& nch)
 {
   if (nrl>nrh)
     allocate();
   else
   {
     //if (nrl !=ncl.indexmin() || nrh !=ncl.indexmax() ||
     //  nrl !=nch.indexmin() || nrh !=nch.indexmax())
     if ( (ncl.isinteger() && (nrl !=ncl.indexmin() || nrh !=ncl.indexmax())) ||
       (nch.isinteger() && (nrl !=nch.indexmin() || nrh !=nch.indexmax())))
     {
       cerr << "Incompatible array bounds in dvar_matrix(int nrl,int nrh,"
        "const ivector& ncl, const ivector& nch)" << endl;
       ad_exit(1);
     }
     index_min=int(nrl);
     index_max=int(nrh);

     int rs=rowsize();
     if ( (m = new dvar_vector [rs]) == 0)
     {
       cerr << " Error allocating memory in dmatrix contructor" << endl;
       ad_exit(21);
     }
     if ( (shape = new mat_shapex(m))== 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor" << endl;
       ad_exit(21);
     }
     m -= int(nrl);
     for (int i=nrl; i<=nrh; i++)
     {
       m[i].allocate(ncl[i],nch[i]);
     }
   }
 }
