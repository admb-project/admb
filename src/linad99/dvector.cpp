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

#ifndef OPT_LIB
  #ifndef __SUNPRO_CC
    #include <algorithm>
    using std::fill_n;
  #endif
#endif

#include "fvar.hpp"

#ifdef DOSX286
  int heapcheck(void){return 0;}
#else
  /// Does nothing.
  int heapcheck(void);
#endif

#ifdef _MSC_VER
#include <memory.h>
#endif
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

/** Average of two numbers; constant objects.
\ingroup misc
\param x A double
\param y A double
\return \f$0.5*(x+y)\f$
*/
double avg(double x,double y)
{
  return 0.5*(x+y);
}

/** Shift valid range of subscripts.
\ingroup matop
\param min Ingeger value subtracted from the subscripts
\return A %devector containing shifted vector.
*/
dvector& dvector::shift(int min)
{
  v += indexmin()-min;
  index_max=index_max-index_min+min;
  index_min=min;
  shape->shift(min);
  return *this;
}

/**
Default destructor. Invoked by the compiler. Only frees allocated memory
if all shallow copies in scope have been removed.
Produces an error if the double* member v is NULL.
*/
dvector::~dvector()
{
  if (shape)
  {
    if (shape->ncopies)
    {
      (shape->ncopies)--;
    }
    else
    {
#ifdef SAFE_ALL
  #ifdef DIAG
      myheapcheck(" Entering ~dvector");
  #endif
      if (v == NULL)
      {
        cerr << " Trying to delete NULL pointer in ~dvector\n";
        ad_exit(21);
      }
#endif
      deallocate();
    }
  }
}
/**
Called by destructor to deallocate memory for a dvector object.
*/
void dvector::deallocate()
{
  if (shape)
  {
    v = (double*)(shape->trueptr);
    if (v)
    {
      delete [] v;
      v = NULL;
    }

    delete shape;
    shape = NULL;
  }
}
/**
Safely deallocates memory by reporting if shallow copies are still in scope.
*/
void dvector::safe_deallocate()
{
  if (shape)
  {
    if (shape->ncopies)
    {
      cerr << "trying to deallocate a dvector with copies" << endl;
      ad_exit(1);
    }

    deallocate();
  }
}

/**
Copy constructor. This constructor make a "shallow" copy.
Values of existing pointers are copied, and no memory is allocated.
Invoked by the compiler in some circumstances such as function
call containing an argument of class %dvector passed by value.

The following code segments creates the \c dvector object \c x and fills it
with
uniform random numbers (using the constant 79 as seed; \ref fill_randu). The
new \c dvector
object \c y will reference the same memory locations as \c x, and any change
s in \c y
will also appear in \c x. The new \c dvector object \c z does not refer to
the same memory locations as \c x, and any changes in \c z will be unique to
\c z.

\code
dvector x(1,10);
y.fill_randu(79L);
dvector y = x; // shallow copy
dvector z;
z = x;         // "deep" copy
\endcode
*/
dvector::dvector(const dvector& t)
{
#ifdef DIAG
  cout << "starting out in dvector contructor\n";
#endif
  shape=t.shape;
  if (shape)
  {
    (shape->ncopies)++;
  }
  else
  {
    cerr << "Making a copy of an unallocated dvector"<<endl;
  }
  v = t.v;
  index_min = t.index_min;
  index_max = t.index_max;
}

 /**
 Explicit shallow copy.
 \param t %dvector to be copied
 */
void dvector::shallow_copy(const dvector& t)
 {
   #ifdef DIAG
    // cout << "starting out in dvector contructor\n";
   #endif
   shape=t.shape;
   if (shape)
   {
     (shape->ncopies)++;
   }
   else
   {
     cerr << "Making a copy of an unallocated dvector"<<endl;
   }
   v = t.v;
   index_min=t.index_min;
   index_max=t.index_max;
 }

/**
Creates a %dvector from an instance of class %predvector.
Creates a shallow copy.
\param pdv an instance of class %predvector.
Updated by Martell, March 10, 2014, from Dave's email
*/
dvector::dvector(const predvector& pdv)
{
  int mmin = pdv.p->indexmin();
  int mmax = pdv.p->indexmax();
  if (pdv.lb < mmin || pdv.ub > mmax)
  {
    cerr << "index out of bounds in dvector subvector operator" << endl;
    ad_exit(1);
  }

  shape = pdv.p->shape;
  if (shape)
  {
    (shape->ncopies)++;
  }
  else
  {
    cerr << "Waring: Taking a subvector of an unallocated dvector.\n";
  }

  v = pdv.p->v;
  index_min = pdv.lb;
  index_max = pdv.ub;
}

 /**
  Assignment operator for double argument.
  \ingroup matop
  Assigns a the same value to all members of the vector object.
  \param x A double constant.
  \return Reference to a %dvector object.
 */
dvector& dvector::operator=(const double x)
 {
   #ifdef DIAG
     myheapcheck("Entering dvector =");
   #endif

   {
     for (int i=indexmin();i<=indexmax();i++)
     {
       elem(i)=x;
     }
   }
   #ifdef DIAG
     myheapcheck("Leaving dvector =");
   #endif
   return (*this);
 }

/**
\ingroup matop
Assignment operator for %dvector argument.
Assigns the values of the argument to a target %dvector in the LHS of the
assignment operator. The range of valid subscripts in the argument and the
target must be identical.
\param t A %dvector constant
\return Reference to a %dvector object.
*/
dvector& dvector::operator=(const dvector& t)
{
  if (!(*this))
  {
    allocatec(t);
  }
#if defined (AD_FAST_ASSIGN)
  else if (!(t.shape->ncopies))
  {
    deallocate();
    allocatec(t);
  }
#endif
  else
  {
    if (indexmin() != t.indexmin() ||  indexmax() != t.indexmax() )
    {
       cerr << "Index bounds do not match in "
       "dvector& operator = (const dvector&)\n";
       ad_exit(1);
    }

    if (v != t.v)
    {
      int min=indexmin();
      int max=indexmax();
#ifndef OPT_LIB
      assert(max >= min);
#endif
      size_t size = (size_t)(max - min + 1);
      memcpy(&elem(min), &t.elem(min), size * sizeof(double));
    }
  }
  return *this;
}

 /**
  \ingroup matop
  Assignment operator for %dvector argument.
  Assigns the values of the argument to a %independent_variables target in the
  LHS of the
  assignment operator. The range of valid subscripts in the argument and the
  target must be identical.
  \param t A %dvector constant
  \return Reference to a %independent_variables object.
 */
 independent_variables& independent_variables::operator=(const dvector& t)
 {
   #ifdef DIAG
     myheapcheck("Entering dvector =");
   #endif

   if (indexmin() != t.indexmin() ||  indexmax() != t.indexmax() )
   {
     cerr << "Index bounds do not match in "
  "independent_variables& independent_variables::operator=(const dvector& t)\n";
     ad_exit(1);
   }
     //double tmp;
   // disconnect dvector  pointer  from old array
   if (v != t.address())
   {
     for (int i=indexmin();i<=indexmax();i++)
     {
       (*this)[i]=t[i];
     }
   }
   #ifdef DIAG
     myheapcheck("Leaving dvector =");
   #endif
   return (*this);
 }

/**
Construct a %dvector object from a C style array of doubles.
\param sz Number of valid memory locations allocated in the array
The range of valid subscripts for the %dvector object will be [0,sz-1].
\param x Pointer to double pointing to the first element in the array.
*/
dvector::dvector(unsigned int sz, double* x)
{
#ifndef OPT_LIB
  assert(sz > 0 && sz - 1 <= INT_MAX);
#endif
  allocate(0, (int)(sz - 1));
  for (unsigned int i = 0; i < sz; i++)
  {
    //cout << "Doing the assignment in constructor\n";
    v[i] = x[i];
  }
}

/*
 dvector::operator double* ( )
 {
   return(v);
 }
*/

 /**
 Construct a %dvector object from a dvar_vector_position object.
 Used in writing adjoint functions callled by the autodif library,
 \param dvp Reference to a %dvar_vector_position object
 (usually read from stack)
 \param kk Kludge to avoid ambiguous function references
 */
dvector::dvector(const dvar_vector_position& dvp, const kkludge_object& kk)
 {
   allocate(dvp.indexmin(),dvp.indexmax());
 }

 /**
 Construct a %dvector with specified range of valid subscript.
 \param ncl Integer specifying lowest valid subscript.
 \param nch Integer specifying highest valid subscript.
 */
 dvector::dvector( int ncl,  int nch)
 {
   if (ncl>nch)
     allocate();
   else
     allocate(ncl,nch);
 }

 /**
 Construct a %dvector without allocating memory.
 Useful in creating classes containing dvectors.
 */
 dvector::dvector(void)
 {
   allocate();
 }

 /**
 Safely allocate memory for a %dvector.
 Exits with an error message if memory for this instance has already been
 allocated.
 \param ncl Integer specifying lowest valid subscript.
 \param nch Integer specifying highest valid subscript.
 */
 void dvector::safe_allocate(int ncl,int nch)
 {
   if (allocated())
   {
     cerr << "trying to allocate an already allocated dvector " << endl;
     ad_exit(1);
   }
   else
   {
     allocate(ncl,nch);
   }
 }

/**
Allocate memory for a %dvector.
Exits with an error message if subscript range makes no sense.
\param ncl Integer specifying lowest valid subscript.
\param nch Integer specifying highest valid subscript.
*/
void dvector::allocate(int ncl, int nch)
{
  //\todo Should check if v and shape are already allocated.

  if (nch < ncl)
  {
    allocate();
  }
  else
  {
    //Originally +2
    //int size = nch - ncl + 2;

    int size = nch - ncl + 1;

    v = new double[size];
    if (v == NULL)
    {
      cerr << " Error trying to allocate memory for dvector\n";
      ad_exit(21);
    }
#ifndef OPT_LIB
    assert(size >= 0);
    memset(v, 0, sizeof(double) * (unsigned int)size);
#endif

#if defined(THREAD_SAFE)
    shape = new ts_vector_shapex(ncl, nch, v);
#else
    shape = new vector_shapex(ncl, nch, v);
#endif
    if (shape == NULL)
    {
      cerr << "Error trying to allocate memory for dvector\n";
      ad_exit(1);
    }

    index_min = ncl;
    index_max = nch;

    //reset v(index_min) to v[0]
    v -= index_min;
  }
}

 /**
 Allocate memory for a %dvector the same size as it's argument.
 \param dv Reference to a %dvector.
 */
void dvector::allocate(const dvector& dv)
{
  allocate(dv.indexmin(),dv.indexmax());
}

 /**
 Allocate memory for a %dvector the same size as it's argument.
 \param dv Reference to a dvar_vector.
 */
void dvector::allocate(const dvar_vector& dv)
{
  allocate(dv.indexmin(),dv.indexmax());
}

/**
Make shallow copy of %dvector shape.
Copies the shape of its argument.
\param t Reference to a %dvector.
*/
void dvector::allocatec(const dvector& t)
{
  if (!(*this))
  {
    if (t.shape)
    {
      shape=t.shape;
      (shape->ncopies)++;
    }
    v = t.v;
    index_min=t.index_min;
    index_max=t.index_max;
  }
  else
  {
    cerr << "Trying to alocate to an already allocated dvector" << endl;
  }
}

/**
Allocate %dvector without allocating memory.
All pointers set to NULL and subscript range is invalid.
*/
void dvector::allocate()
{
  shape = NULL;
  v = NULL;
  index_min = 1;
  index_max = 0;
}

  /** Compute the dot product of two vectors. The minimum and maxium
  legal subscripts of the arguments must agree; otherwize an error message
   is printed and execution terminates.
  \ingroup matop
  \param t1 A %dvector, \f$a\f$.
  \param t2 A %dvector, \f$b\f$.
  \return A double, \f$z = a\cdot b = \sum_i a_i\cdot b_i\f$  containing
  the value of the dot product of the two arguments.
  */
double operator*(const dvector& t1, const dvector& t2)
  {
     if (t1.indexmin() != t2.indexmin() ||  t1.indexmax() != t2.indexmax())
     {
       cerr << "Index bounds do not match in "
       "dvector operator * (const dvector&, const dvector&)\n";
       ad_exit(1);
     }
     double tmp;
     tmp=0;
   #ifdef OPT_LIB
     const double * pt1=&t1[t1.indexmin()];
     const double * pt1m=&t1[t1.indexmax()];
     const double * pt2=&t2[t2.indexmin()];
     do
     {
       tmp+=*pt1++ * *pt2++;
     }
     while (pt1<=pt1m);

   #else
     #ifndef USE_ASSEMBLER
       int min=t1.indexmin();
       int max=t1.indexmax();
       for (int i=min; i<=max; i++)
       {
         tmp+=t1[i]*t2[i];
       }
     #else
       int min=t1.indexmin();
       int n=t1.indexmax()-min+1;
       dp_dotproduct(&tmp,&(t1(min)),&(t2(min)),n);
     #endif
   #endif

     return(tmp);
  }

  /**
  \ingroup matop
  Add two dvectors.
  Exits with error if bounds of the two arguments differ.
  \param t1 %dvector reference, \f$a\f$.
  \param t2 %dvector reference, \f$b\f$.
  \return A %dvector, \f$z_i = a_i + b_i\f$  containing
  the value of the sum of the two arguments.
  */
dvector operator+(const dvector& t1, const dvector& t2)
  {
     if (t1.indexmin() != t2.indexmin() ||  t1.indexmax() != t2.indexmax())
     {
       cerr << "Index bounds do not match in "
       "dvector operator+(const dvector&, const dvector&)\n";
       ad_exit(1);
     }
     dvector tmp(t1.indexmin(),t1.indexmax());
   #ifdef OPT_LIB
     const double * pt1=&t1[t1.indexmin()];
     const double * pt1m=&t1[t1.indexmax()];
     const double * pt2=&t2[t2.indexmin()];
     double * ptmp=&tmp[t1.indexmin()];
     do
     {
       *ptmp++=*pt1++ + *pt2++;
     }
     while (pt1<=pt1m);

   #else

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp[i]=t1[i]+t2[i];
     }
   #endif
     return(tmp);
  }

  /**
  \ingroup matop
  Subtract two dvectors.
  Exits with error if bounds of the two arguments differ.
  \param t1 %dvector reference, \f$a\f$.
  \param t2 %dvector reference, \f$b\f$.
  \return A %dvector, \f$z_i = a_i - b_i\f$  containing
  the value of the difference of the two arguments.
  */
dvector operator-(const dvector& t1, const dvector& t2)
  {
     if (t1.indexmin() != t2.indexmin() ||  t1.indexmax() != t2.indexmax())
     {
       cerr << "Index bounds do not match in "
       "dvector operator - (const dvector&, const dvector&)\n";
       ad_exit(1);
     }
     dvector tmp(t1.indexmin(),t1.indexmax());
   #ifdef OPT_LIB
     const double * pt1=&t1[t1.indexmin()];
     const double * pt1m=&t1[t1.indexmax()];
     const double * pt2=&t2[t2.indexmin()];
     double * ptmp=&tmp[t1.indexmin()];
     do
     {
       *ptmp++=*pt1++ - *pt2++;
     }
     while (pt1<=pt1m);

   #else

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp[i]=t1[i]-t2[i];
     }
   #endif
     return(tmp);
  }

  /**
  \ingroup matop
  Multiply a %dvector by a constant.
  \param x Double constant, \f$x\f$.
  \param t1 %dvector reference, \f$y\f$.
  \return A %dvector \f$z_i = x*y_i\f$.
  */
dvector operator*(const double x, const dvector& t1)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());
   #ifdef OPT_LIB
     const double * pt1=&t1[t1.indexmin()];
     const double * pt1m=&t1[t1.indexmax()];
     double * ptmp=&tmp[t1.indexmin()];
     do
     {
       *ptmp++=x * *pt1++;
     }
     while (pt1<=pt1m);

   #else

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp[i]=x*t1[i];
     }
   #endif
     return(tmp);
  }
/*
#ifdef __TURBOC__
   void myheapcheck(char * msg)
   {
     if( ::heapcheck() == _HEAPCORRUPT )
     {
       cerr << msg << "Heap is corrupted.\n";
     }
     else
     {
       cerr << msg << "Heap is OK.\n";
     }
   }
#else
*/
   /** Does nothing. This function is only defined for older Borland compilers.
   The user could provide an implementation that might be useful in certain
   circumstances.
   \param msg Pointer to character array.
   */
   void myheapcheck(char * msg){}

/*
#endif
*/

/** Largest of two integer; constant objects
\ingroup misc
\param a An integer
\param b An integer
\return A integer containing  \f$ z = \max(a,b)\f$
*/
int max(int a,int b)
{
  if (a>b)
    return a;
  else
    return b;
}

/** Cube of a number; constant objects.
\ingroup misc
\param m Number to be cubed
\return \f$m^3\f$
*/
double cube(const double m)
{
  return m*m*m;
}

/** Fourth power of a number; constant objects.
\ingroup misc
\param m Number to be taken to the fourth power.
\return \f$m^4\f$
*/
double fourth(const double m)
{
  double m2=m*m;
  return m2*m2;
}

