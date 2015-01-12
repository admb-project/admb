/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"


 dvar_matrix::dvar_matrix(int nrl,int nrh,int ncl,int nch)
 {
   allocate(nrl,nrh,ncl,nch);
   #ifdef SAFE_ARRAYS
     initialize();
   #endif 
 }

 dvar_matrix::dvar_matrix(int nrl,int nrh,kkludge_object kk)
 {
   allocate(nrl,nrh);
   #ifdef SAFE_ARRAYS
     initialize();
   #endif 
 }

 dvar_matrix::dvar_matrix(int nrl,int nrh)
 {
   allocate(nrl,nrh);
   #ifdef SAFE_ARRAYS
     initialize();
   #endif 
 }

 dvar_matrix dvar_matrix::sub(int nrl,int nrh)
 {
   if (allocated(*this))
   {
     dvar_matrix tmp(nrl,nrh);
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

 void dvar_matrix::allocate(int nrl,int nrh)
 {
   if (nrl>nrh)
     allocate();
   else
   {
     index_min=nrl;
     index_max=nrh;
     int rs=rowsize();
     if ( (m = new dvar_vector [rs]) == 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor\n";
       ad_exit(21);
     }
     if ( (shape=new mat_shapex(m)) == 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor\n";
     }
     m -= rowmin();
   }
 }


 void dvar_matrix::allocate(int nrl,int nrh,int ncl,int nch)
 {
   if (nrl>nrh)
     allocate();
   else
   {
     index_min=nrl;
     index_max=nrh;
     int rs=rowsize();
     if ( (m = new dvar_vector [rs]) == 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor\n";
       ad_exit(21);
     }
     if ( (shape=new mat_shapex(m)) == 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor\n";
     }
     m -= rowmin();
     for (int i=nrl; i<=nrh; i++)
     {
       m[i].allocate(ncl,nch);
     }
   }
 }
 void dvar_matrix::allocate(ad_integer nrl,ad_integer nrh)
 {
   if (nrl>nrh)
     allocate();
   else
   {
     index_min=nrl;
     index_max=nrh;
     if ( (m = new dvar_vector [rowsize()]) == 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor\n";
       ad_exit(21);
     }
     if ( (shape=new mat_shapex(m)) == 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor\n";
     }
     m -= rowmin();
   }
 }


 void dvar_matrix::allocate(_CONST dmatrix& m1)
 {
   if (m1.shape)
   {
     int nrl=m1.rowmin();
     int nrh=m1.rowmax();
     index_min=nrl;
     index_max=nrh;
     int rs=rowsize();
     if ( (m = new dvar_vector [rs]) == 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor\n";
       ad_exit(21);
     }
     if ( (shape=new mat_shapex(m)) == 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor\n";
     }
     m -= rowmin();
     for (int i=nrl; i<=nrh; i++)
     {
       m[i].allocate(m1(i));
     }
   }
   else
   {
     //cerr << "Warning -- trying to make a dvar_matrix copy of an "
      // " unallocated dmatrix" << endl;
     allocate();
   }
 }
 
 void dvar_matrix::allocate(_CONST dvar_matrix& m1)
 {
   if (m1.shape)
   {
     int nrl=m1.rowmin();
     int nrh=m1.rowmax();
     index_min=nrl;
     index_max=nrh;
     int rs=rowsize();
     //if ( (m = new dvar_vector [rowsize()]) == 0)
     if ( (m = new dvar_vector [rs]) == 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
      ad_exit(21);
     }
     if ( (shape=new mat_shapex(m)) == 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
     }
     m -= rowmin();
     for (int i=nrl; i<=nrh; i++)
     {
       m[i].allocate(m1(i));
     }
   }
   else
   {
     //cerr << "Warning -- trying to make a dvar_matrix copy of an "
     //  "unallocated dvar_matrix" << endl;
     allocate();
   }
 }

 dvar_matrix::dvar_matrix(int nrl,int nrh,_CONST ivector& ncl,_CONST ivector& nch)
 {
   allocate(nrl,nrh,ncl,nch);
   #ifdef SAFE_ARRAYS
     initialize();
   #endif 
 }

 void dvar_matrix::allocate(int nrl,int nrh,_CONST ivector& ncl,_CONST ivector& nch)
 {
   if (nrl>nrh)
     allocate();
   else
   {
     if (nrl !=ncl.indexmin() || nrh !=ncl.indexmax() ||
       nrl !=nch.indexmin() || nrh !=nch.indexmax())
     {
       cerr << "Incompatible array bounds in dvar_matrix(int nrl,int nrh,_CONST ivector& ncl,_CONST ivector& nch)"
  	  << endl ;
       ad_exit(1);
     }
     index_min=nrl;
     index_max=nrh;
  
     int rs=rowsize();
     if ( (m = new dvar_vector [rs]) == 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
       ad_exit(21);
     }
     if ( (shape=new mat_shapex(m)) == 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
     }
  
     m -= rowmin();
  
     for (int i=nrl; i<=nrh; i++)
     {
       m[i].allocate(ncl[i],nch[i]);
     }
   }
 }

 dvar_matrix::dvar_matrix(int nrl,int nrh,int ncl,_CONST ivector& nch)
 {
   allocate(nrl,nrh,ncl,nch);
   #ifdef SAFE_ARRAYS
     initialize();
   #endif 
 }

 void dvar_matrix::allocate(int nrl,int nrh,int ncl,_CONST ivector& nch)
 {  
   if (nrl>nrh)
     allocate();
   else
   {
     if (nrl !=nch.indexmin() || nrh !=nch.indexmax())
     {
       cerr << "Incompatible array bounds in dvar_matrix(int nrl,int nrh,BOR_CONST int& ncl,_CONST ivector& nch)"
  	  << endl;
       ad_exit(1);
     }
     index_min=nrl;
     index_max=nrh;
  
     int rs=rowsize();
     if ( (m = new dvar_vector [rs]) == 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
       ad_exit(21);
     }
  
     if ( (shape=new mat_shapex(m)) == 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
     }
     m -= rowmin();
  
     for (int i=nrl; i<=nrh; i++)
     {
       m[i].allocate(ncl,nch[i]);
     }
   }
 }

 void dvar_matrix::allocate(int nrl,int nrh,_CONST ivector& ncl,int nch)
 {
   if (nrl>nrh)
     allocate();
   else
   {
     if (nrl !=ncl.indexmin() || nrh !=ncl.indexmax())
     {
       cerr << "Incompatible array bounds in dvar_matrix(int nrl,int nrh,_CONST ivector& ncl,int nch)"
  	  << endl;
       ad_exit(1);
     }
     index_min=nrl;
     index_max=nrh;
  
     int rs=rowsize();
     if ( (m = new dvar_vector [rs]) == 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
       ad_exit(21);
     }
  
     if ( (shape=new mat_shapex(m)) == 0)
     {
       cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
     }
     m -= rowmin();
  
     for (int i=nrl; i<=nrh; i++)
     {
       m[i].allocate(ncl[i],nch);
     }
   }
 }


 dvar_matrix::dvar_matrix(_CONST dvar_matrix& m2)
 {
   if (!(m2))
   {
     //cerr << "Making a copy of an unallocated dvar_matrix" << endl;
     index_min=0;
     index_max=-1;
     shape=NULL;
     m=NULL;
   }
   else
   {
     index_min=m2.index_min;
     index_max=m2.index_max;
     shape=m2.shape;
     (shape->ncopies)++;
     m = m2.m;
   }
 }

 void dvar_matrix::shallow_copy(const dvar_matrix& m2)
 {
   if (!(m2))
   {
     //cerr << "Making a copy of an unallocated dvar_matrix" << endl;
     index_min=0;
     index_max=-1;
     shape=NULL;
     m=NULL;
   }
   else
   {
     index_min=m2.index_min;
     index_max=m2.index_max;
     shape=m2.shape;
     (shape->ncopies)++;
     m = m2.m;
   }
 }

 void dvar_matrix::allocate(void)
 {
   index_min=1;
   index_max=0;
   shape=NULL;
   m = NULL;
 }


 dvar_matrix::dvar_matrix(void)
 {
   allocate();
 }

 dvar_matrix::dvar_matrix(_CONST dmatrix& m2)
 {
   index_min=m2.index_min;
   index_max=m2.index_max;
   int rs=rowsize();
   if ( (m = new dvar_vector [rs]) == 0)
   {
     cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
     ad_exit(21);
   }
   if ( (shape =new mat_shapex(m)) == 0)
   {
     cerr << " Error allocating memory in dvar_matrix contructor"<<endl;
   }

   m -= rowmin();
   for (int i=rowmin(); i<=rowmax(); i++)
   {
     m[i].allocate(m2(i).indexmin(),m2(i).indexmax());
     elem(i)=m2.elem(i);
   }
 }


 dvar_matrix::~dvar_matrix()
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


 void dvar_matrix::deallocate()
 {
   if (shape)
   {
     m=(dvar_vector*)(shape->get_pointer());
     delete [] m;
     delete shape;
     m=NULL;
     shape=NULL;
   }
   else
   {
     //cerr << "Warning -- trying to delete an unallocated dvar_matrix"<<endl;
   }
 }

 dvar_matrix& dvar_matrix::operator= (_CONST dvar_matrix& m1)
 {
   if (!allocated(*this))
   {
     shallow_copy(m1);
   }
   else
   {
     if (rowmin() != m1.rowmin() || rowmax() != m1.rowmax())
     {
       cerr << " Incompatible array bounds in dvar_matrix& operator = "
         "(_CONST dvar_matrix&)\n";
       ad_exit(21);
     }
  
     if (m != m1.m)            // check for condition that both matrices
     {                         // don't point to the same object
       for (int i=rowmin(); i<=rowmax(); i++)
       {
         (*this)[i]= m1[i];
       }
     }
   }
   return(*this);
 }

 dvar_matrix& dvar_matrix::operator= (_CONST dmatrix& m1)
 {
   if (rowmin() != m1.rowmin() || rowmax() != m1.rowmax() ||
     colmin() != m1.colmin() || colmax() != m1.colmax() )
   {
     cerr << " Incompatible array bounds in dvar_matrix& operator = (_CONST dvar_vector&)\n";
     ad_exit(21);
   }

   for (int i=rowmin(); i<=rowmax(); i++)
   {
     (*this)[i]= m1[i];
   }
   return(*this);
 }



  void copy_status(BOR_CONST ostream& _s,_CONST dvar_matrix& m1)
  {
    ostream& s= (ostream&) _s;
    s << " matrix_copy flags \n";

    for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
    {
      copy_status(s,m1[i]);
    }
    s <<"\n";
  }
