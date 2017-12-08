/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/// Destructor
dvar_vector::~dvar_vector()
{
  deallocate();
}
/// Deallocate dvar_vector memory.
void dvar_vector::deallocate()
{
  if (shape)
  {
#ifdef DIAG
     cout << " Deallocating dvar_vector with ptr_address\n  "
          << &ptr << "  pointing at  " << (ptr+indexmin()) << "\n";
#endif
    if (shape->ncopies > 0)
    {
      --(shape->ncopies);
    }
    else
    {
      va = (double_and_int*) shape->trueptr;
      *(arr_link**) va = link_ptr;
      arr_free(va);
      delete shape;
    }
    allocate();
  }
#ifdef DEBUG
  else
  {
    cerr << "Warning -- Unable to deallocate an unallocated dvar_vector.\n";
  }
#endif
}
/// Copy constructor
dvar_vector::dvar_vector(const dvar_vector& other)
{
  shallow_copy(other);

#ifdef DEBUG
  cout << " Making copy for dvar_vector with ptr_address\n  "
       << &va << "  pointing at  " << (va+indexmin()) << "\n";
#endif
}
/**
Shallow copy other data structure pointers.

\param other dvar_vector
*/
void dvar_vector::shallow_copy(const dvar_vector& other)
{
  if (other.shape)
  {
    shape = other.shape;
    ++(shape->ncopies);

    index_min = other.index_min;
    index_max = other.index_max;

    link_ptr = other.link_ptr;
    va = other.va;
  }
  else
  {
#ifdef DEBUG
    cerr << "Warning -- Unable to shallow copy an unallocated dvar_vector.\n";
#endif
    allocate();
  }
}

/**
 * Description not yet available.
 * \param
 */
dvar_vector::dvar_vector(const predvar_vector& pdv)
 {
#ifndef OPT_LIB
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
dvar_vector::dvar_vector(const dvar_vector& t, int lb, int ub)
 {
#ifndef OPT_LIB
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

