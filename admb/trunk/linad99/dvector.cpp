/**
  * $Id$
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */
#include "fvar.hpp"


long int farptr_tolong(void *);

#ifdef DOSX286
  int heapcheck(void){return 0;}
#else
  int heapcheck(void);
#endif

#ifdef __MSVC32__
#include <memory.h>
#endif

double avg(double x,double y)
{
  return 0.5*(x+y);
}


dvector& dvector::shift(int min)
{
  v += indexmin()-min;
  index_max=index_max-index_min+min;
  index_min=min;
  shape->shift(min);
  return *this;
}


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
  
       #ifdef DIAG
         myheapcheck(" Entering ~dvector");
       #endif
  
       if ( v == NULL)
       {
         cerr << " Trying to delete NULL pointer in ~dvector\n";
         ad_exit(21);
       }
       deallocate();
     }
   }
 }

static int testflag=0;
static int ycounter=0;
  void dvector::deallocate()
  {
   if (testflag)
   {
     ycounter++;
     cout << " C " << ycounter << endl;
     if (ycounter==41)
       cout << "HERE" << endl;
     test_the_pointer();
   }
    if(shape)
    {
      v = (double*) (shape->trueptr);
      if (v)
      {
       if (testflag)
       {
         test_the_pointer();
       }
        delete [] v;
       if (testflag)
       {
         test_the_pointer();
       }
        v = NULL;
      }
      else
      {
        cerr << "error in dvector shape not zero but v=0" << endl;
      }
      delete shape;
      if (testflag)
      {
        test_the_pointer();
      }
    }
    else
    {
      //cerr << "Warning -- trying to deallocate an unitialized dvector"
       //    << endl;
    }
    shape=NULL;
   if (testflag)
   {
     cout << " D " << ycounter << endl;
     test_the_pointer();
   }
  }

  void dvector::safe_deallocate()
  {
    if (shape)
    {
      if (shape->ncopies)
      {
        cerr << "trying to deallocate a dvector with copies" << endl;
        ad_exit(1);
      }
    }
    else
    {
      deallocate();
    }
  }

 dvector::dvector(_CONST dvector& t)
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

 void dvector::shallow_copy(_CONST dvector& t)
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

 dvector::dvector(_CONST predvector& pdv)
 {
   #ifdef DIAG
    // cout << "starting out in dvector contructor\n";
   #endif
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

 dvector& dvector::operator = ( CGNU_DOUBLE x)
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

 dvector& dvector::operator = (_CONST dvector& t)
 {
   if (!(*this))
   {
     allocatec(t);
   }
#  if defined (AD_FAST_ASSIGN)
   else if (!(t.shape->ncopies))
   {
     deallocate();
     allocatec(t);
   }
#  endif
   else
   {
     if (indexmin() != t.indexmin() ||  indexmax() != t.indexmax() )
     {
       cerr << "Index bounds do not match in dvector& operator = (_CONST dvector&)\n";
       ad_exit(1);
     }

     if (v != t.v)
     {
         int min=indexmin();
         int max=indexmax();
         memcpy(&elem(min),&t.elem(min),(max-min+1)*sizeof(double));
     }
   }
   return (*this);
 }

 independent_variables& independent_variables::operator = (_CONST dvector& t)
 {

   #ifdef DIAG
     myheapcheck("Entering dvector =");
   #endif

   if (indexmin() != t.indexmin() ||  indexmax() != t.indexmax() )
   {
     cerr << "Index bounds do not match in dvector& operator = (_CONST dvector&)\n";
     ad_exit(1);
   }
     double tmp;
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


 dvector::dvector( unsigned int sz, double * x )
 {
   allocate(0,sz-1);

   for (int i=0; i<sz; i++)
   {
     cout << "Doing the assignment in constructor\n";
     v[i] = x[i];
   }
 }

/*
 dvector::operator double* ( )
 {
   return(v);
 }
*/

 dvector::dvector(BOR_CONST dvar_vector_position& dvp,BOR_CONST kkludge_object& kk)
 {
   allocate(dvp.indexmin(),dvp.indexmax());
 }

 dvector::dvector( int ncl,  int nch)
 {
   if (ncl>nch)
     allocate();
   else
   allocate(ncl,nch);
 }

 dvector::dvector(void)
 {
   allocate();
 }

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

 void dvector::allocate(int ncl,int nch)
 {
   if (ncl>nch)
     allocate();
   else
   {
     int itemp=nch-ncl;
     if (itemp<0)
     {
       cerr << "Error in dvector constructor max index must be >= minindex\n"
            << "minindex = " << ncl << " maxindex = " << nch <<endl;
       ad_exit(1);
     }
     if ( (v = new double [itemp+2]) ==0)
     {
       cerr << " Error trying to allocate memory for dvector\n";
       ad_exit(21);
     }
#if defined(THREAD_SAFE)
   if ( (shape=new ts_vector_shapex(ncl,nch,v)) == NULL)
#else
   if ( (shape=new vector_shapex(ncl,nch,v)) == NULL)
#endif
     {
       cerr << "Error trying to allocate memory for dvector\n";
       ad_exit(1);
     }
  
     //int align= ((int) v)%8 ;
     //if (align)
     //{
     //  int diff=(8-align)%8;
     //  v=(double*)( ((char*)v)+diff);
     //}     

     index_min=ncl;
     index_max=nch;
     v -= indexmin();
     #ifdef SAFE_INITIALIZE
       for ( int i=indexmin(); i<=indexmax(); i++)
       {
         v[i]=0.;
       }
     #endif
   }
 }

void dvector::allocate(_CONST dvector& dv)
{
  allocate(dv.indexmin(),dv.indexmax());
}

void dvector::allocate(_CONST dvar_vector& dv)
{
  allocate(dv.indexmin(),dv.indexmax());
}

void dvector::allocatec(_CONST dvector& t)
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


 void dvector::allocate(void)
 {
   shape=NULL;
   v = NULL;
  index_min=1;
  index_max=0;
 }


  double operator * (_CONST dvector& t1,_CONST dvector& t2)
  {
     if (t1.indexmin() != t2.indexmin() ||  t1.indexmax() != t2.indexmax())
     {
       cerr << "Index bounds do not match in dvector operator * (_CONST dvector&,_CONST dvector&)\n";
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


  dvector operator + (_CONST dvector& t1,_CONST dvector& t2)
  {
     if (t1.indexmin() != t2.indexmin() ||  t1.indexmax() != t2.indexmax())  
     {
       cerr << "Index bounds do not match in dvector operator + (_CONST dvector&,_CONST dvector&)\n";
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

  dvector operator - (_CONST dvector& t1,_CONST dvector& t2)
  {
     if (t1.indexmin() != t2.indexmin() ||  t1.indexmax() != t2.indexmax())  
     {
       cerr << "Index bounds do not match in dvector operator - (_CONST dvector&,_CONST dvector&)\n";
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

  dvector operator * ( CGNU_DOUBLE x,_CONST dvector& t1)
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
   void myheapcheck(char * msg){}
/*
#endif
*/

int max(int a,int b)
{
  if (a>b)
    return a;
  else
    return b;
}
double cube( CGNU_DOUBLE m)
{
  return m*m*m;
}

double fourth( CGNU_DOUBLE m)
{
  double m2=m*m;
  return m2*m2;
}
#undef HOME_VERSION
