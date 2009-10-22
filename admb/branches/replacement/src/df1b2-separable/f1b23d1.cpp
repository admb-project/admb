/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <df1b2fun.h>


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

df1b23array::df1b23array(void)
{
  allocate();
}

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

void df1b23array::allocate(int nrl,int nrh,
  const index_type& ncl, const index_type& nch,
  const index_type& nxl, const index_type& nxh,
  const char * s)
{
  allocate(nrl,nrh,ncl,nch,nxl,nxh);
}

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

void df1b23array::allocate(int nrl,int nrh,int ncl,int nch)
{
  index_min=nrl;
  index_max=nrh;
  int rs=size();
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

df1b23array::df1b23array(const df1b23array & x)
{
  index_min=x.index_min;
  index_max=x.index_max;
  v=x.v;
  shape=x.shape;
  if (shape) (shape->ncopies)++;
}

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
void df1b23array::deallocate()
{
  if (shape)
  {
    v=(df1b2matrix*)(shape->trueptr);
    delete [] v;
    v=0;
    delete shape;
    shape=0;
  }
}


void df1b23array::allocate(void)
{
  index_min=1;
  index_max=0;
  v=0;
  shape=0;
}


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
df1b2variable& df1b23array::operator () (int i,int j,int k)
{
  if (i<indexmin() || i>indexmax())
  {
    cerr << "Index out of bounds in access operator" << endl;
    ad_exit(1);
  }
  return v[i][j][k];
}

df1b2vector& df1b23array::operator () (int i,int j)
{
  if (i<indexmin() || i>indexmax())
  {
    cerr << "Index out of bounds in access operator" << endl;
    ad_exit(1);
  }
  return v[i][j];
}

df1b2matrix& df1b23array::operator () (int i)
{
  if (i<indexmin() || i>indexmax())
  {
    cerr << "Index out of bounds in access operator" << endl;
    ad_exit(1);
  }
  return v[i];
}

df1b2matrix& df1b23array::operator [] (int i)
{
  if (i<indexmin() || i>indexmax())
  {
    cerr << "Index out of bounds in access operator" << endl;
    ad_exit(1);
  }
  return v[i];
}

#endif // #if !defined(OPT_LIB)


void df1b23array::initialize(void)
{
  int rmin=indexmin();
  int rmax=indexmax();
  for (int i=rmin;i<=rmax;i++)
  {
    (*this)(i).initialize();
  }
}

