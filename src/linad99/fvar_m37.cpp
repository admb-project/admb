/**
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/
#include <fvar.hpp>

#ifndef OPT_LIB
  #include <cassert>
#endif

/**
Construct AD variable matrix with dimensions nrl to nrh by ncl to nch.

\param nrl lower row index
\param nrh higher row index
\param ncl lower column index
\param nch higher column index
*/
dvar_matrix::dvar_matrix(
  const ad_integer& nrl, const ad_integer& nrh,
  const index_type& ncl, const index_type& nch)
{
  allocate(nrl,nrh,ncl,nch);
#ifndef OPT_LIB
  initialize();
#endif
}
/**
Allocates AD variable matrix with dimensions nrl to nrh by ncl to nch.

\param nrl lower row index
\param nrh higher row index
\param ncl lower column index
\param nch higher column index
*/
void dvar_matrix::allocate(
  const ad_integer& nrl, const ad_integer& nrh,
  const index_type& ncl, const index_type& nch)
{
  if (nrl>nrh)
  {
    allocate();
  }
  else
  {
    //if (nrl !=ncl.indexmin() || nrh !=ncl.indexmax() ||
    //  nrl !=nch.indexmin() || nrh !=nch.indexmax())
    if ((ncl.isinteger() && (nrl !=ncl.indexmin() || nrh !=ncl.indexmax())) ||
       (nch.isinteger() && (nrl !=nch.indexmin() || nrh !=nch.indexmax())))
    {
      cerr << "Incompatible array bounds in dvar_matrix(int nrl,int nrh,"
              "const ivector& ncl, const ivector& nch)" << endl;
      ad_exit(1);
    }
    index_min=int(nrl);
    index_max=int(nrh);
    if ((m = new dvar_vector[rowsize()]) == 0)
    {
      cerr << " Error allocating memory in dmatrix contructor" << endl;
      ad_exit(21);
    }
    if ((shape = new mat_shapex(m)) == 0)
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
