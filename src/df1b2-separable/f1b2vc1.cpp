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
df1b2vector operator + (const df1b2vector& _x,const df1b2vector& _y)
{
  ADUNCONST(df1b2vector,x)
  ADUNCONST(df1b2vector,y)
  check_shape(x,y,"operator +");

  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);

  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=x(i)+y(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector operator + (const df1b2vector& _x,const dvector& _y)
{
  ADUNCONST(df1b2vector,x)
  ADUNCONST(dvector,y)
  check_shape(x,y,"operator +");

  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);

  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=x(i)+y(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector operator + (const dvector& _x,const df1b2vector& _y)
{
  ADUNCONST(dvector,x)
  ADUNCONST(df1b2vector,y)
  check_shape(x,y,"operator +");

  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);

  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=x(i)+y(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector exp(const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x)
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);

  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=exp(x(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector log(const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x)
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);

  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=log(x(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector sin(const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x)
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);

  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=sin(x(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector tan(const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x)
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);

  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=tan(x(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector sqrt(const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x)
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);

  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=sqrt(x(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector cos(const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x)
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);

  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=cos(x(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector operator - (const df1b2vector& _x,const df1b2vector& _y)
{
  ADUNCONST(df1b2vector,x)
  ADUNCONST(df1b2vector,y)
  check_shape(x,y,"operator -");

  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);

  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=x(i)-y(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector operator - (const df1b2vector& _x,const dvector& _y)
{
  ADUNCONST(df1b2vector,x)
  ADUNCONST(dvector,y)
  check_shape(x,y,"operator -");

  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);

  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=x(i)-y(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector operator - (const dvector& _x,const df1b2vector& _y)
{
  ADUNCONST(dvector,x)
  ADUNCONST(df1b2vector,y)
  check_shape(x,y,"operator -");

  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);

  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=x(i)-y(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector& df1b2vector::operator += (const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x)
  check_shape(*this,x,"operator +=");

  int mmin=x.indexmin();
  int mmax=x.indexmax();

  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i)+=x(i);
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector& df1b2vector::operator += (const dvector& _x)
{
  ADUNCONST(dvector,x)
  check_shape(*this,x,"operator +=");

  int mmin=x.indexmin();
  int mmax=x.indexmax();

  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i)+=x(i);
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector& df1b2vector::operator -= (const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x)
  check_shape(*this,x,"operator -");

  int mmin=x.indexmin();
  int mmax=x.indexmax();

  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i)-=x(i);
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector& df1b2vector::operator -= (const dvector& _x)
{
   ADUNCONST(dvector,x)
   check_shape(*this,x,"operator -");

   int mmin=x.indexmin();
   int mmax=x.indexmax();

   for (int i=mmin;i<=mmax;i++)
   {
     (*this)(i)-=x(i);
   }
   return *this;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector& df1b2vector::operator *= (const df1b2variable& _x)
{
  ADUNCONST(df1b2variable,x)
  int mmin=indexmin();
  int mmax=indexmax();

  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i)*=x;
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector& df1b2vector::operator -= (const df1b2variable& _x)
{
  ADUNCONST(df1b2variable,x)
  int mmin=indexmin();
  int mmax=indexmax();

  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i)-=x;
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector& df1b2vector::operator += (const df1b2variable& _x)
{
  ADUNCONST(df1b2variable,x)
  int mmin=indexmin();
  int mmax=indexmax();

  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i)+=x;
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector& df1b2vector::operator += (double x)
{
  int mmin=indexmin();
  int mmax=indexmax();

  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i)+=x;
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector& df1b2vector::operator *= (const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x)
  check_shape(*this,x,"operator *");

  int mmin=x.indexmin();
  int mmax=x.indexmax();

  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i)*=x(i);
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector& df1b2vector::operator /= (const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x)
  check_shape(*this,x,"operator /");

  int mmin=x.indexmin();
  int mmax=x.indexmax();

  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i)/=x(i);
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector& df1b2vector::operator /= (const df1b2variable& _x)
{
  ADUNCONST(df1b2variable,x)
  int mmin=indexmin();
  int mmax=indexmax();

  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i)/=x;
  }
  return *this;
}

#if !defined(OPT_LIB)
/**
 * Description not yet available.
 * \param
 */
df1b2variable& df1b2matrix::operator () (int i,int j) const
{
  if (i < indexmin())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index too low",
    "df1b2variable& df1b2matrix::operator () (int i, int j) const",
    indexmin(), indexmax(), i);
  }
  if (i > indexmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index too high",
    "df1b2variable& df1b2matrix::operator () (int i, int j) const",
    indexmin(), indexmax(), i);
  }
  return (df1b2variable&)(v[i][j]);
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector& df1b2matrix::operator [] (int i) const
{
  if (i < indexmin())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index too low",
    "df1b2vector& df1b2matrix::operator [] (int i) const",
    indexmin(), indexmax(), i);
  }
  if (i > indexmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index too high",
    "df1b2vector& df1b2matrix::operator [] (int i) const",
    indexmin(), indexmax(), i);
  }
  return (df1b2vector&)(v[i]);
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector& df1b2matrix::operator () (int i) const
{
  if (i < indexmin())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index too low",
    "df1b2vector& df1b2matrix::operator () (int i) const",
    indexmin(), indexmax(), i);
  }
  if (i > indexmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index too high",
    "df1b2vector& df1b2matrix::operator () (int i) const",
    indexmin(), indexmax(), i);
  }
  return (df1b2vector&)(v[i]);
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable& df1b2vector::operator () (int i) const
{
  if (i < indexmin())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index too low",
    "df1b2variable& df1b2vector::operator () (int i) const",
    indexmin(), indexmax(), i);
  }
  if (i > indexmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index too high",
    "df1b2variable& df1b2vector::operator () (int i) const",
    indexmin(), indexmax(), i);
  }
  return *(v+i);
  //return *((df1b2variable*)((char*)(v)+i*pointersize()));
}
/*
const df1b2variable& df1b2vector::operator () (int i) const
{
  if (i<indexmin())
  {
    cerr << "Index too low in df1b2variable& operator () (int i)"
      " value = " << i << endl;
    ad_exit(1);
  }
  if (i>indexmax())
  {
    cerr << "Index too high in df1b2variable& operator () (int i)"
      " value = " << i << endl;
    ad_exit(1);
  }
  //return *(v+i);
  return *((df1b2variable*)((char*)(v)+i*pointersize()));
}
*/

/**
 * Description not yet available.
 * \param
 */
df1b2variable& df1b2vector::operator [] (int i) const
{
  if (i < indexmin())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index too low",
    "df1b2variable& df1b2vector::operator [] (int i) const",
    indexmin(), indexmax(), i);
  }
  if (i > indexmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index too high",
    "df1b2variable& df1b2vector::operator [] (int i) const",
    indexmin(), indexmax(), i);
  }
  //return *(v+i);
  return *((df1b2variable*)((char*)(v)+i*pointersize()));
}
#endif

/// Default constructor
df1b2vector::df1b2vector():
  v(NULL), shape(NULL)
{
}
/**
 * Description not yet available.
 * \param
 */
df1b2vector::df1b2vector(int lb, int ub):
  v(NULL), shape(NULL)
{
  if (lb <= ub)
  {
    allocate(lb, ub);
  }
}
/**
 * Construct df1b2vector from dvector v.
 */
df1b2vector::df1b2vector(const dvector& v):
  v(NULL), shape(NULL)
{
  if (v.allocated())
  {
    const int lb = v.indexmin();
    const int ub = v.indexmax();
    if (lb <= ub)
    {
      allocate(lb, ub);
      for (int i = lb; i <= ub; i++)
      {
        (*this)[i] = v[i];
      }
    }
  }
}
/**
 * Description not yet available.
 * \param
 */
void df1b2vector::allocate(void)
{
  shape=0;
  v=0;
}

/**
 * Description not yet available.
 * \param
 */
void df1b2vector::allocate(int lb,int ub,const char * s)
{
  allocate(lb,ub);
}

/**
 * Description not yet available.
 * \param
 */
void df1b2vector::allocate(const ad_integer& lb,const ad_integer& ub)
{
  allocate(int(lb),int(ub));
}

/**
 * Description not yet available.
 * \param
 */
void df1b2vector::allocate(int lb,int ub)
{
  index_min=lb;
  index_max=ub;
  int sz=ub-lb+1;
  if (index_min>index_max)
  {
    shape=0;
    v=0;
    sz=0;
  }
  else
  {
    if (v)
    {
      deallocate();
    }
    //AD_ALLOCATE(v,df1b2variable,sz,df1b2vector);
    v = new df1b2variable[sz];
    if ( (shape=new vector_shapex(lb,ub,v)) == NULL)
    {
      cerr << "Error trying to allocate memory for df1b2vector\n";
      ad_exit(1);
    }
    v-=index_min;
  }
  if (sz>0)
  {
    int mmin=indexmin();
    int mmax=indexmax();
    int ind_1 = 0;
    if (mmax>mmin)
    {
      ind_1=adptr_diff((*this)(mmin+1).get_u(), (*this)(mmin).get_u());
    }
   /*
#  if defined(SAFE_ALL)
    int i;
    for (i=mmin+1;i<mmax;i++)
    {
      int ind_i=ptrdiff_t((*this)(i+1).get_u())-ptrdiff_t((*this)(i).get_u());
      if (ind_i !=ind_1)
      {
        cerr << "Offset in df1b2vector constructor is not constant" << endl;
        ad_exit(1);
      }
      else
      {
        ind_1=ind_i;
      }
    }
#endif
   */
  /*
    if (ind_1%sizeof(double))
    {
        cerr << "Offset in df1b2vector constructor is not"
          " multiple of sizeof(double)"  << endl;
        ad_exit(1);
    }
    offset=ind_1/sizeof(double);
  */
    offset=ind_1;
  }
  else
  {
    offset=0;
  }
}

/**
 * Description not yet available.
 * \param
 */
void df1b2vector::noallocate(int lb,int ub)
{
  index_min=lb;
  index_max=ub;
  int sz=ub-lb+1;
  df1b2variable::noallocate=1;
  AD_ALLOCATE(v,df1b2variable,sz,df1b2vector);
  df1b2variable::noallocate=0;
  if ( (shape=new vector_shapex(lb,ub,v)) == NULL)
  {
    cerr << "Error trying to allocate memory for df1b2vector\n";
    ad_exit(1);
  }
  v-=index_min;
  offset=0;
}
/**
Destructor
*/
df1b2vector::~df1b2vector()
{
  deallocate();
}
/**
If no other copies exists, free allocated memory.
*/
void df1b2vector::deallocate()
{
  if (shape)
  {
    if (shape->ncopies)
    {
      (shape->ncopies)--;
    }
    else
    {
      if (shape->trueptr)
      {
        v = (df1b2variable*)shape->trueptr;
        delete [] v;
      }

      delete shape;
    }
    v = NULL;
    shape = NULL;
  }
}
/**
Copy from constructor
*/
df1b2vector::df1b2vector(const df1b2vector& from):
  v(NULL), shape(NULL)
{
  copy(from);
}
/**
 * Description not yet available.
 * \param
 */
void df1b2vector::copy(const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x)
  if (x.shape)
  {
    shape=x.shape;
    (shape->ncopies)++;

    v=x.v;

    index_min=x.index_min;
    index_max=x.index_max;
  }
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector::df1b2vector(const predf1b2vector& pdv)
{
  shape=pdv.p->shape;
  if (shape)
  {
    (shape->ncopies)++;
  }
  else
  {
    cerr << "Taking a subvector  of an unallocated dvector"<<endl;
  }
  v = pdv.p->v;
  index_min=pdv.lb;
  index_max=pdv.ub;
}

/**
 * Description not yet available.
 * \param
 */
 void ADMB_getcallindex(const df1b2variable& x)
 {
   cout << "HERE" << endl;
 }

/**
 * Description not yet available.
 * \param
 */
 void ADMB_getcallindex(const df1b2vector& x)
 {
   cout << "HERE" << endl;
 }

/**
 * Description not yet available.
 * \param
 */
 void ADMB_getcallindex(const df1b2matrix& x)
 {
   cout << "HERE" << endl;
 }
