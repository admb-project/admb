/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"
#if defined(__TURBOC__) && !defined(__linux__)
  #pragma hdrstop
   #include <alloc.h>
#endif

#include <stdlib.h>

//extern double * NULL_ADDRESS;
//extern grad_stack  * GRAD_STACK1; //js
//extern indvar_offset_list * INDVAR_LIST;
//extern unsigned  MAX_NVAR_OFFSET;

void * farptr_norm(void *);
long int farptr_tolong(void *) ;


dvar_vector& dvar_vector::shift(int min) 
{
  va += indexmin()-min;
  index_max=index_max-index_min+min;
  index_min=min;
  shape->shift(min);
  return *this;
}


 dvar_vector::dvar_vector(BOR_CONST independent_variables& t)
 {
   int i;
   allocate(t.indexmin(),t.indexmax());

   for ( i=indexmin(); i<=indexmax(); i++)
   {
     va[i].x=(t.v)[i];
   }

   make_indvar_list(*this);
 }

 dvar_vector::dvar_vector(_CONST dvector& t)
 {
   int i;
   if (!t)
   {
     allocate();
   }
   else
   {
     va=NULL;
     allocate(t.indexmin(),t.indexmax());
     initialize();
     for ( i=indexmin(); i<=indexmax(); i++)
     {
       va[i].x=(t.v)[i];
     }
   }
 }


//#ifdef __BORLANDC__
 //prevariable dvar_vector::elem(int i) { return (va+i); }
//#endif


 dvar_vector::dvar_vector( unsigned int sz, double * x )
 {
   allocate(0,sz-1);
   for (int i=0; i<sz; i++)
   {
     va[i].x = x[i];
   }
 }

 dvar_vector::dvar_vector(int ncl,int nch)
 {
   if (ncl>nch)
     allocate();
   else
   {
     va=NULL;
     allocate(ncl,nch);
   }
   #ifdef SAFE_INITIALIZE
     initialize();
   #endif

   #ifdef DIAG
     cout << " Allocating dvar_vector with ptr_address\n  "
         << &va << "  pointing at  " << (va+indexmin()) << "\n";
   #endif
 }

/*
 dvar_vector::dvar_vector(const ad_integer& ncl,const ad_integer& nch)
 {
   allocate(ncl,nch);
   #ifdef SAFE_INITIALIZE
     initialize();
   #endif

   #ifdef DIAG
     cout << " Allocating dvar_vector with ptr_address\n  "
         << &va << "  pointing at  " << (va+indexmin()) << "\n";
   #endif
 }
 */

 dvar_vector::dvar_vector(void)
 {
   allocate();
 }

void make_indvar_list(_CONST dvar_vector& t)
{
  if (!gradient_structure::instances)
  {
    return;
  }
  if ( (t.indexmax()-t.indexmin()+1)> gradient_structure::MAX_NVAR_OFFSET)
  {
   #if defined(__SPDLL__)
   if (ad_printf)
   {
     (*ad_printf)("Current maximum number of independent variables is %d\n",
        gradient_structure::MAX_NVAR_OFFSET);
     (*ad_printf)("  You need to increase the global variable "
     "MAX_NVAR_OFFSET to %d\n",t.indexmax()-t.indexmin()+1);
     (*ad_printf)("  This can be done by putting the line\n"
         "    gradient_structure::set_MAX_NVAR_OFFSET(%d);\n",
        t.indexmax()-t.indexmin()+1);
     (*printf)("  before the declaration of the gradient_structure object.\n"
        " or the command line option -mno %d\n",
        t.indexmax()-t.indexmin()+1);
   }
   #else
   cerr << "Current maximum number of independent variables is "
        << gradient_structure::MAX_NVAR_OFFSET << "\n"
        <<  "  You need to increase the global variable MAX_NVAR_OFFSET to "
        << (t.indexmax()-t.indexmin()+1) << "\n"
        << "  This can be done by putting the line\n"
        << "    'gradient_structure::set_MAX_NVAR_OFFSET("
        << (t.indexmax()-t.indexmin()+1) << ");'\n"
        << "  before the declaration of the gradient_structure object.\n"
        << " or use the -mno 1149 command line option in AD Model Builder\n";
    #endif
      ad_exit(21);
  }

  for (int i=t.indexmin(); i<=t.indexmax(); i++)
  {
    unsigned int tmp=i-t.indexmin();
    gradient_structure::INDVAR_LIST->put_address(tmp,&(t.va[i].x));
  }
  gradient_structure::NVAR=t.indexmax()-t.indexmin()+1;
} 

   void  copy_status(BOR_CONST ostream& _s,_CONST dvar_vector& v)
   {
     ostream& s= (ostream&) _s;
     s << " copy_flag ";
     s <<"\n";
   }

   void dvar_vector::allocate(void)
   {
     shape=NULL;
     va=NULL;
   }
 
   void dvar_vector::allocate(_CONST dvector& v1)
   {
     allocate(v1.indexmin(),v1.indexmax());
   }

   void dvar_vector::allocate(_CONST dvar_vector& v1)
   {
     allocate(v1.indexmin(),v1.indexmax());
   }

   void dvar_vector::allocatec(_CONST dvar_vector& t)
   {
     if (!(*this)) 
     {
       if (t.shape)
       {
         shape=t.shape;
         (shape->ncopies)++;
       }
       else
       {
         //cerr << "Making a copy of an unallocated dvar_vector"<<endl;
       }
       link_ptr=t.link_ptr;
       index_min=t.index_min;
       index_max=t.index_max;
       va = t.va;
     }
     else
     {
       cerr << "Trying to alocate to an already allocated dvar_vector" << endl;
     }
   }

   void dvar_vector::allocate(int ncl,int nch)
   {
     if (ncl>nch)
       allocate();
     else
     {  
       index_min=ncl;
       index_max=nch;
       int itemp=nch-ncl+1;
       if (itemp<=0)
       {
         cerr << "Error in dvar_vector constructor max index must be"
                 " >= minindex\n"
            << "minindex = " << ncl << " maxindex = " << nch <<endl;
         ad_exit(1);
       }
       if ( (va = arr_new(itemp)) ==0)
       {
         cerr << " Error trying to allocate memory for dvar_vector\n";
         ad_exit(1);
       }
  
       if ( (shape=new vector_shapex(ncl,nch,va)) == NULL)
       {
         cerr << "Error trying to allocate memory for dvar_vector\n";
         ad_exit(1);
       }
  
       link_ptr=* (arr_link **) va;
       va -= indexmin();
       // if ( ((int)va) %8) cerr << "Array is not QWORD alligned" << endl;
       
       #ifdef DIAG
         myheapcheck("Leaving dvar_vector::allocate(ncl,nch)");
       #endif
     }
   }

   void dvar_vector::allocate(const ad_integer& ncl,const ad_integer& nch)
   {
     allocate(int(ncl),int(nch));
   }

