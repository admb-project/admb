/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"


 struct dvec_ptr_ptr
 {
   void ** m;
 };

 dmatrix::dmatrix( int nrl,  int nrh, int ncl,  int nch)
 {
   allocate(nrl,nrh,ncl,nch);
 }

 void dmatrix::allocate(int nrl,int nrh,int ncl,int nch)
 {
   if (nrh<nrl)
   {
     allocate();
     return;
   }
   index_min=nrl;
   index_max=nrh;
   if ( (m = new dvector [rowsize()]) == 0)
   {
     cerr << " Error allocating memory in dmatrix contructor\n";
     ad_exit(21);
   }
   if ( (shape = new mat_shapex(m))== 0)
   {
     cerr << " Error allocating memory in dmatrix contructor\n";
     ad_exit(21);
   }
   m -= rowmin();
   for (int i=rowmin(); i<=rowmax(); i++)
   {
     m[i].allocate(ncl,nch);
   }
 }

 dmatrix dmatrix::sub(int nrl,int nrh)
 {
   if (allocated(*this))
   {
     dmatrix tmp(nrl,nrh);
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
 dmatrix::dmatrix(int nrl,int nrh)
 {
   allocate(nrl,nrh);
 }

 void dmatrix::allocate(int nrl,int nrh)
 {
   if (nrh<nrl)
   {
     allocate();
     return;
   }
   index_min=nrl;
   index_max=nrh;
   if ( (m = new dvector [rowsize()]) == 0)
   {
     cerr << " Error allocating memory in dmatrix contructor\n";
     ad_exit(21);
   }
   if ( (shape = new mat_shapex(m))== 0)
   {
     cerr << " Error allocating memory in dmatrix contructor\n";
     ad_exit(21);
   }
   m -= rowmin();
 }

 void dmatrix::allocate(ad_integer nrl,ad_integer nrh)
 {
   if (nrh<nrl)
   {
     allocate();
     return;
   }
   index_min=nrl;
   index_max=nrh;
   if ( (m = new dvector [rowsize()]) == 0)
   {
     cerr << " Error allocating memory in dmatrix contructor\n";
     ad_exit(21);
   }
   if ( (shape = new mat_shapex(m))== 0)
   {
     cerr << " Error allocating memory in dmatrix contructor\n";
     ad_exit(21);
   }
   m -= rowmin();
 }

double min(const dmatrix& m)
{
  double tmp=max(m(m.rowmin()));
  for (int i=m.rowmin()+1;i<=m.rowmax();i++)
  {
    double tmp1=min(m(i));
    if (tmp>tmp1) tmp=tmp1;
  }
  return tmp;
}

double max(_CONST dmatrix& m)
{
  double tmp=max(m(m.rowmin()));
  for (int i=m.rowmin()+1;i<=m.rowmax();i++)
  {
    double tmp1=max(m(i));
    if (tmp<tmp1) tmp=tmp1;
  }
  return tmp;
}

void dmatrix::allocate(_CONST dmatrix& dm)
{
  int nrl=dm.rowmin();
  int nrh=dm.rowmax();
  index_min=nrl;
  index_max=nrh;

  if ( (m = new dvector [rowsize()]) == 0)
  {
    cerr << " Error allocating memory in dmatrix contructor" << endl;
    ad_exit(21);
  }

  if ( (shape = new mat_shapex(m))== 0)
  {
    cerr << " Error allocating memory in dmatrix contructor" << endl;
    ad_exit(21);
  }
  m -= rowmin();
  for (int i=rowmin(); i<=rowmax(); i++)
  {
    m[i].allocate(dm(i));
  }
}



  int ivector_check(_CONST ivector& v,int l,int u)
  {
    if (v.indexmin()!=l||v.indexmax()!=u) return 1;
    return 0;
  }


 void dmatrix::allocate(int nrl,int nrh,const ivector& ncl,const ivector& nch)
 {
   if (nrh<nrl)
   {
     allocate();
     return;
   }

   if (nrl !=ncl.indexmin() || nrh !=ncl.indexmax() ||
     nrl !=nch.indexmin() || nrh !=nch.indexmax())
   {
     cerr << "Incompatible array bounds in dmatrix(int nrl,int nrh,_CONST ivector& ncl,_CONST ivector& nch)\n";
     ad_exit(1);
   }
   index_min=nrl;
   index_max=nrh;
   if ( (m = new dvector [rowsize()]) == 0)
   {
     cerr << " Error allocating memory in dmatrix contructor\n";
     ad_exit(21);
   }
   if ( (shape = new mat_shapex(m))== 0)
   {
     cerr << " Error allocating memory in dmatrix contructor\n";
     ad_exit(21);
   }

   m -= rowmin();
   for (int i=rowmin(); i<=rowmax(); i++)
   {
     m[i].allocate(ncl(i),nch(i));
   }
 }



 void dmatrix::allocate(int nrl,int nrh,int ncl,const ivector& nch)
 {
   if (nrh<nrl)
   {
     allocate();
     return;
   }
   if (nrl !=nch.indexmin() || nrh !=nch.indexmax())
   {
     cerr << "Incompatible array bounds in dmatrix(int nrl,int nrh,"
       "int ncl,_CONST ivector& nch)\n";
     ad_exit(1);
   }
   index_min=nrl;
   index_max=nrh;
   if ( (m = new dvector [rowsize()]) == 0)
   {
     cerr << " Error allocating memory in dmatrix contructor\n";
     ad_exit(21);
   }
   if ( (shape = new mat_shapex(m))== 0)
   {
     cerr << " Error allocating memory in dmatrix contructor\n";
     ad_exit(21);
   }
   m -= rowmin();
   for (int i=rowmin(); i<=rowmax(); i++)
   {
     m[i].allocate(ncl,nch(i));
   }
 }

 void dmatrix::allocate(int nrl,int nrh,const ivector& ncl,int nch)
 {
   if (nrh<nrl)
   {
     allocate();
     return;
   }
   if (nrl !=ncl.indexmin() || nrh !=ncl.indexmax())
   {
     cerr << "Incompatible array bounds in dmatrix(int nrl,int nrh,"
       " int ncl,_CONST ivector& nch)\n";
     ad_exit(1);
   }
   index_min=nrl;
   index_max=nrh;
   if ( (m = new dvector [rowsize()]) == 0)
   {
     cerr << " Error allocating memory in dmatrix contructor\n";
     ad_exit(21);
   }
   if ( (shape = new mat_shapex(m))== 0)
   {
     cerr << " Error allocating memory in dmatrix contructor\n";
     ad_exit(21);
   }
   m -= rowmin();
   for (int i=rowmin(); i<=rowmax(); i++)
   {
     m[i].allocate(ncl(i),nch);
   }
 }

/*
 dmatrix::dmatrix(void)
 {
   #ifdef DIAG
     myheapcheck("Entering dmatrix(nrl,nrh,ncl,nch)" );
   #endif

   shape = NULL;
   m=NULL;
 }
*/

 dmatrix::dmatrix(int nrl,int nrh,_CONST ivector& ncl,_CONST ivector& nch)
 {
   allocate(nrl,nrh,ncl,nch);
 }

 dmatrix::dmatrix(int nrl,int nrh,int ncl,_CONST ivector& nch)
 {
   allocate(nrl,nrh,ncl,nch);
 }

 dmatrix::dmatrix(_CONST dmatrix& m2)
 {
   index_min=m2.index_min;
   index_max=m2.index_max;
   shape=m2.shape;
   if (shape)
   {
     (shape->ncopies)++;
   }
#ifdef  SAFE_ARRAYS
   else
   {
     cerr << "Making a copy of an unallocated dmatrix"<<endl;
   }
#endif 
   m = m2.m;
 }

 void dmatrix::shallow_copy(_CONST dmatrix& m2)
 {
   index_min=m2.index_min;
   index_max=m2.index_max;
   shape=m2.shape;
   if (shape)
   {
     (shape->ncopies)++;
   }
#ifdef  SAFE_ARRAYS
   else
   {
     cerr << "Making a copy of an unallocated dmatrix"<<endl;
   }
#endif 
   m = m2.m;
 }

 dmatrix::~dmatrix()
 {
   deallocate();
 }
static int testflag=0;
static int ycounter=0;

   dvector cube(_CONST dvector& m)
   {
     dvector tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=cube(m(i));
     }
     return tmp;
   }  

   dmatrix cube(_CONST dmatrix& m)
   {
     dmatrix tmp;
     tmp.allocate(m);
     for (int i=tmp.rowmin();i<=tmp.rowmax();i++)
     {
       tmp(i)=cube(m(i));
     }
     return tmp;
   }  


 void dmatrix::deallocate()
 {
   if (testflag)
   {
     ycounter++;
     cout << " A " << ycounter << endl;
     test_the_pointer();
   }
   if (shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       m= (dvector*) (shape->get_pointer());
       delete [] m;
       m=NULL;
       delete shape;
       shape=NULL;
     }
  
   }
   if (testflag)
   {
     cout << " B " << ycounter << endl;
     test_the_pointer();
   }
     
#ifdef  SAFE_ARRAYS
   else
   {
     //cerr << "Warning -- trying to deallocate an unallocated dmatrix"<<endl;
   }
#endif 
 }
