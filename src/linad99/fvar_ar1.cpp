/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
 dvar_vector::~dvar_vector()
 {
   if (shape)                  //if *ncopies == 0
   {
     if (shape->ncopies)                  //if *ncopies == 0
     {
       #ifdef DIAG
         cout << " Decrementing copy flag for dvar_vector with ptr_address\n "
	   << &ptr << "  pointing at  " << (ptr+indexmin()) << "\n";
       #endif
       (shape->ncopies)--;
     }
     else
     {
       deallocate();
     }
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar_vector::deallocate()
 {
   if (shape)
   {
     #ifdef DIAG
       cout << " Deallocating dvar_vector with ptr_address\n  "
	 << &ptr << "  pointing at  " << (ptr+indexmin()) << "\n";
     #endif

     va = (double_and_int*) shape->trueptr;
     * (arr_link **) va = link_ptr;
     arr_free(va);
     delete shape;
     va=NULL;
     shape=NULL;
   }
   //else
   //{
   //  cerr << "Warning -- trying to delete an unallocated dvar_vector"
    //	  << endl;
   //}
 } 

/**
 * Description not yet available.
 * \param
 */
 dvar_vector::dvar_vector(_CONST dvar_vector& t)
 {
   index_min=t.index_min;
   index_max=t.index_max;
   shape=t.shape;
   link_ptr=t.link_ptr;
   if (shape) (shape->ncopies)++;
   va = t.va;
   #ifdef DIAG
     cout << " Making copy for dvar_vector with ptr_address\n  " 
           << &va << "  pointing at  " << (va+indexmin()) << "\n";
   #endif
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar_vector::shallow_copy(const dvar_vector& t)
 {
   index_min=t.index_min;
   index_max=t.index_max;
   shape=t.shape;
   link_ptr=t.link_ptr;
   if (shape) (shape->ncopies)++;
   va = t.va;
   #ifdef DIAG
     cout << " Making copy for dvar_vector with ptr_address\n  " 
           << &va << "  pointing at  " << (va+indexmin()) << "\n";
   #endif
 }

/**
 * Description not yet available.
 * \param
 */
 dvar_vector::dvar_vector(_CONST predvar_vector& pdv)
 {
 #ifdef SAFE_ALL
   if (pdv.ub<pdv.lb) 
   {
     cerr << "lower index greater than upper index in dvar_vector::"
       " dvar-vector(const predvar_vector&) " << endl;
     ad_exit (1);
   }
   if ((pdv.lb<pdv.p->indexmin()) || (pdv.lb>pdv.p->indexmax()))
   {
     cerr << "lower index out of bounds in dvar_vector::"
       " operator(int lb,int ub) " << endl;
     ad_exit (1);
   }
  
   if ((pdv.ub<pdv.p->indexmin()) || (pdv.ub>pdv.p->indexmax()))
   {
     cerr << " upper index out of bounds in dvar_vector::"
       " operator(int lb,int ub) " << endl;
     ad_exit (1);
   }
  #endif
   index_min=pdv.lb;
   index_max=pdv.ub;
   shape=pdv.p->shape;
   link_ptr=pdv.p->link_ptr;
   (shape->ncopies)++;
   va = pdv.p->va;
   #ifdef DIAG
     cout << " Making copy for dvar_vector with ptr_address\n  " 
           << &va << "  pointing at  " << (va+indexmin()) << "\n";
   #endif
 }

/*
 dvar_vector::dvar_vector(_CONST dvar_vector& t,int lb,int ub)
 {
 #ifdef SAFE_ALL
   if (ub<lb) 
   {
     cerr << "lower index greater than upper index in dvar_vector::"
       " operator(int lb,int ub) " << endl;
     ad_exit (1);
   }
   if ((lb<t.indexmin()) || (lb>t.indexmax()))
   {
     cerr << "lower index out of bounds in dvar_vector::"
       " operator(int lb,int ub) " << endl;
     ad_exit (1);
   }
  
   if ((ub<t.indexmin()) || (ub>t.indexmax()))
   {
     cerr << " upper index out of bounds in dvar_vector::"
       " operator(int lb,int ub) " << endl;
     ad_exit (1);
   }
  #endif
  

   index_min=lb;
   index_max=ub;
   shape=t.shape;
   link_ptr=t.link_ptr;
   (shape->ncopies)++;
   va = t.va;
   #ifdef DIAG
     cout << " Making copy for dvar_vector with ptr_address\n  " 
           << &va << "  pointing at  " << (va+indexmin()) << "\n";
   #endif
 }
*/
