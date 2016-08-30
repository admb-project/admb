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
#include <df1b2fun.h>
#include "admb_messages.h"

/**
 * Description not yet available.
 * \param
 */
df1b23array::df1b23array(int nrl,int nrh,int ncl,int nch,int nxl,int nxh)
{
  if (nrl>nrh)
  {
    allocate();
  }
  else
  {
    allocate(nrl,nrh,ncl,nch,nxl,nxh);
  }
}

/**
 * Description not yet available.
 * \param
 */
df1b23array::df1b23array(int nrl,int nrh,int ncl,int nch)
{
  if (nrl>nrh)
  {
    allocate();
  }
  else
  {
    allocate(nrl,nrh,ncl,nch);
  }
}

/**
 * Description not yet available.
 * \param
 */
df1b23array::df1b23array(int nrl,int nrh)
{
  if (nrl>nrh)
  {
    allocate();
  }
  else
  {
    allocate(nrl,nrh);
  }
}

/**
 * Description not yet available.
 * \param
 */
df1b23array::df1b23array(void)
{
  allocate();
}

/**
 * Description not yet available.
 * \param
 */
void df1b23array::allocate(int nrl,int nrh,int ncl,int nch,
  int nxl,int nxh,const char * s)
{
  allocate(nrl,nrh,ncl,nch,nxl,nxh);
}

/*
void df1b23array::allocate(int nrl,int nrh,int ncl,int nch,const char * s)
{
  allocate(nrl,nrh,ncl,nch);
}

void df1b23array::allocate(int nrl,int nrh,const index_type& ncl,
  const index_type& nch,const char * s)
{
  allocate(nrl,nrh,ncl,nch);
}
*/

/**
 * Description not yet available.
 * \param
 */
void df1b23array::allocate(int nrl,int nrh,
  const index_type& ncl, const index_type& nch,
  const index_type& nxl, const index_type& nxh,
  const char * s)
{
  allocate(nrl,nrh,ncl,nch,nxl,nxh);
}

/**
 * Description not yet available.
 * \param
 */
void df1b23array::allocate(int nrl,int nrh,int ncl,int nch,
  int nxl,int nxh)
{
  index_min=nrl;
  index_max=nrh;
  int rs=size();
  if ( (v = new df1b2matrix[rs]) == 0)
  {
      cerr << " Error allocating memory in df1b23array contructor\n";
      ad_exit(21);
  }
  if ( (shape=new vector_shapex(nrl,nrh,v)) == 0)
  {
    cerr << " Error allocating memory in df1b23array contructor\n";
  }
  v -= indexmin();
  for (int i=nrl; i<=nrh; i++)
  {
    v[i].allocate(ncl,nch,nxl,nxh);
  }
}

/**
 * Description not yet available.
 * \param
 */
void df1b23array::allocate(int nrl,int nrh,int ncl,int nch)
{
  index_min=nrl;
  index_max=nrh;
  int rs=size();
  if ( (v = new df1b2matrix[rs]) == 0)
  {
      cerr << " Error allocating memory in df1b23array contructor\n";
      ad_exit(21);
  }
  if ( (shape=new vector_shapex(nrl,nrh,v)) == 0)
  {
      cerr << " Error allocating memory in df1b23array contructor\n";
      ad_exit(21);
  }
  v -= indexmin();
  for (int i=nrl; i<=nrh; i++)
  {
    v[i].allocate(ncl,nch);
  }
}

/**
 * Description not yet available.
 * \param
 */
void df1b23array::allocate(int nrl,int nrh,const index_type& ncl,
  const index_type& nch)
{
  index_min=nrl;
  index_max=nrh;
  int rs=size();
  if ( (v = new df1b2matrix[rs]) == 0)
  {
      cerr << " Error allocating memory in df1b23array contructor\n";
      ad_exit(21);
  }
  if ( (shape=new vector_shapex(nrl,nrh,v)) == 0)
  {
    cerr << " Error allocating memory in df1b23array contructor\n";
  }
  v -= indexmin();
  for (int i=nrl; i<=nrh; i++)
  {
    v[i].allocate(ad_integer(ncl(i)),ad_integer(nch(i)));
  }
}

/**
 * Description not yet available.
 * \param
 */
void df1b23array::allocate(int nrl,int nrh,
  const index_type& ncl,const index_type& nch,
  const index_type& nxl,const index_type& nxh)
{
  index_min=nrl;
  index_max=nrh;
  int rs=size();
  if ( (v = new df1b2matrix[rs]) == 0)
  {
      cerr << " Error allocating memory in df1b23array contructor\n";
      ad_exit(21);
  }
  if ( (shape=new vector_shapex(nrl,nrh,v)) == 0)
  {
    cerr << " Error allocating memory in df1b23array contructor\n";
  }
  v -= indexmin();
  for (int i=nrl; i<=nrh; i++)
  {
    v[i].allocate(ad_integer(ncl(i)),ad_integer(nch(i)),nxl(i),nxh(i));
  }
}
/**
Allocate 3array with specified indexes.

\param nrl 3array lower row index
\param nrh 3array upper row index
\param ncl vector of lower row indexes
           for each row element in 3array
\param nch vector of upper row indexes
           for each row element in 3array
\param nxl lower row index
           for each row and column element in 3array
\param nxh upper row index
           for each row and column element in 3array
\param s id
*/
void df1b23array::allocate(
  const int nrl, const int nrh,
  const ivector& ncl, const ivector& nch,
  const int nxl, const int nxh,
  const char* s)
{
  index_min=nrl;
  index_max=nrh;
  int rs=size();
  if ( (v = new df1b2matrix[rs]) == 0)
  {
      cerr << " Error allocating memory in df1b23array contructor\n";
      ad_exit(21);
  }
  if ( (shape=new vector_shapex(nrl,nrh,v)) == 0)
  {
    cerr << " Error allocating memory in df1b23array contructor\n";
  }
  v -= indexmin();
  for (int i=nrl; i<=nrh; i++)
  {
    v[i].allocate(ncl(i), nch(i), nxl, nxh);
  }
}

/**
 * Description not yet available.
 * \param
 */
df1b23array::df1b23array(const df1b23array & x)
{
  index_min=x.index_min;
  index_max=x.index_max;
  v=x.v;
  shape=x.shape;
  if (shape) (shape->ncopies)++;
}

/**
 * Description not yet available.
 * \param
 */
void df1b23array::allocate(int nrl,int nrh)
{
  index_min=nrl;
  index_max=nrh;
  int rs=size();
  if ( (v = new df1b2matrix[rs]) == 0)
  {
      cerr << " Error allocating memory in df1b23array contructor\n";
      ad_exit(21);
  }
  if ( (shape=new vector_shapex(nrl,nrh,v)) == 0)
  {
    cerr << " Error allocating memory in df1b23array contructor\n";
  }
  v -= indexmin();
}

/**
Destructor
*/
df1b23array::~df1b23array()
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
Deallocates class memory memory.
*/
void df1b23array::deallocate()
{
  if (shape)
  {
    v=(df1b2matrix*)(shape->trueptr);
    delete [] v;
    v=0;
    delete shape;
    shape=0;
    index_min=1;
    index_max=0;
  }
}
/**
Does not allocate, but initialize member variables.
*/
void df1b23array::allocate(void)
{
  index_min=1;
  index_max=0;
  v=0;
  shape=0;
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable sum(const df1b23array& _x)
{
  ADUNCONST(df1b23array,x)
  df1b2variable tmp;
  tmp=0.0;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    tmp+=sum(x(i));
  }
  return tmp;
}

#if !defined(OPT_LIB)

/**
 * Description not yet available.
 * \param
 */
df1b2variable& df1b23array::operator () (int i,int j,int k)
{
  if (i < indexmin() || i > indexmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index out of bounds",
    "df1b2variable& df1b23array::operator () (int i,int j,int k)",
    indexmin(), indexmax(), i);
  }
  return v[i][j][k];
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector& df1b23array::operator () (int i,int j)
{
  if (i < indexmin() || i > indexmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index out of bounds",
    "df1b2vector& df1b23array::operator () (int i,int j)",
    indexmin(), indexmax(), i);
  }
  return v[i][j];
}

/**
 * Description not yet available.
 * \param
 */
df1b2matrix& df1b23array::operator () (int i)
{
  if (i < indexmin() || i > indexmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index out of bounds",
    "df1b2matrix& df1b23array::operator () (int i)",
    indexmin(), indexmax(), i);
  }
  return v[i];
}

/**
 * Description not yet available.
 * \param
 */
df1b2matrix& df1b23array::operator [] (int i)
{
  if (i < indexmin() || i > indexmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index out of bounds",
    "df1b2matrix& df1b23array::operator [] (int i)",
    indexmin(), indexmax(), i);
  }
  return v[i];
}

#endif // #if !defined(OPT_LIB)

/**
 * Description not yet available.
 * \param
 */
void df1b23array::initialize(void)
{
  int rmin=indexmin();
  int rmax=indexmax();
  for (int i=rmin;i<=rmax;i++)
  {
    (*this)(i).initialize();
  }
}
