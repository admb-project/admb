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
#include "fvar.hpp"
#if defined(__TURBOC__)
  #pragma hdrstop
  #include <alloc.h>
#endif

#include <stdlib.h>

#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

/**
 * Description not yet available.
 * \param
 */
dvar_vector& dvar_vector::shift(int min)
{
  va += indexmin()-min;
  index_max=index_max-index_min+min;
  index_min=min;
  shape->shift(min);
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
dvar_vector::dvar_vector(const independent_variables& t)
{
  int min = t.indexmin();
  int max = t.indexmax();
  allocate(min, max);
  if (va)
  {
    double_and_int* pva = va + min;
    double* pt = t.get_v() + min;
    for (int i = min; i <= max; ++i)
    {
      pva->x = *pt;
      ++pt;
      ++pva;
    }
    make_indvar_list(*this);
  }
}

/**
 * Description not yet available.
 * \param
 */
dvar_vector::dvar_vector(const dvector& t): va(nullptr)
{
  if (!t)
  {
    allocate();
  }
  else
  {
    int min = t.indexmin();
    int max = t.indexmax();
    allocate(min, max);
    initialize();
    double_and_int* pva = va + min;
    double* pt = t.get_v() + min;
    for (int i = min; i <= max; ++i)
    {
      va[i].x=(t.v)[i];
      pva->x = *pt;
      ++pt;
      ++pva;
    }
  }
}


//#ifdef __BORLANDC__
 //prevariable dvar_vector::elem(int i) { return (va+i); }
//#endif

/**
 * Description not yet available.
 * \param
 */
dvar_vector::dvar_vector(unsigned int sz, double* x)
{
#ifndef OPT_LIB
  assert(sz > 0 && sz <= INT_MAX);
#endif
  allocate(0, (int)(sz - 1));
  for (unsigned int i = 0; i < sz; i++)
  {
    va[i].x = x[i];
  }
}

/**
 * Description not yet available.
 * \param
 */
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

/**
Default constructor
*/
dvar_vector::dvar_vector()
{
  allocate();
}

/**
 * Description not yet available.
 * \param
 */
void make_indvar_list(const dvar_vector& t)
{
  gradient_structure::_instance->make_indvar_list(t);
}
void gradient_structure::make_indvar_list(const dvar_vector& t)
{
  int min = t.indexmin();
  int max = t.indexmax();
  unsigned int size = (unsigned int)(max - min + 1);
  if (size > gradient_structure::MAX_NVAR_OFFSET)
  {
    printf("Current maximum number of independent variables is %d\n",
      gradient_structure::MAX_NVAR_OFFSET);
    printf("  You need to increase the global variable "
      "MAX_NVAR_OFFSET to %d\n", size);
    printf("  This can be done by putting the line\n"
      "    gradient_structure::set_MAX_NVAR_OFFSET(%d);\n", size);
    printf("  before the declaration of the gradient_structure object.\n"
      " or the command line option -mno %d\n", size);
    /*
    cerr << "Current maximum number of independent variables is "
         << gradient_structure::MAX_NVAR_OFFSET << "\n"
         <<  "  You need to increase the global variable MAX_NVAR_OFFSET to "
         << size << "\n"
         << "  This can be done by putting the line\n"
         << "    'gradient_structure::set_MAX_NVAR_OFFSET("
         << size << ");'\n"
         << "  before the declaration of the gradient_structure object.\n"
         << " or use the -mno 1149 command line option in AD Model Builder\n";
    */
    ad_exit(1);
  }

  double_and_int* pt = t.va + min;
  for (int i = min; i <= max; ++i)
  {
    unsigned int tmp = (unsigned int)(i - min);
    INDVAR_LIST->put_address(tmp, &(pt->x));
    ++pt;
  }
  NVAR = size;
}

/**
 * Description not yet available.
 * \param
 */
void copy_status(const ostream& _s, const dvar_vector& v)
   {
     ostream& s= (ostream&) _s;
     s << " copy_flag ";
     s <<"\n";
   }

/**
Does not allocate, but initializes dvar_vector to empty.
*/
void dvar_vector::allocate()
{
  va = NULL;
  link_ptr = NULL;
  shape = NULL;
  index_min = 0;
  index_max = -1;
}
/**
Allocate dvar_vector using indexes from v1.
*/
void dvar_vector::allocate(const dvector& v1)
{
  allocate(v1.indexmin(), v1.indexmax());
}
/**
Allocate dvar_vector using indexes from v1.
*/
void dvar_vector::allocate(const dvar_vector& v1)
{
  allocate(v1.indexmin(), v1.indexmax());
}

/**
 * Description not yet available.
 * \param
 */
void dvar_vector::allocatec(const dvar_vector& t)
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

/**
Allocate dvar_vector with indexmin = ncl and indexmax = nch.
*/
void dvar_vector::allocate(int ncl, int nch)
{
  if (ncl > nch)
  {
    allocate();
  }
  else
  {
    index_min=ncl;
    index_max=nch;
    unsigned int itemp = (unsigned int)(nch - ncl + 1);
#ifdef DEBUG
    if (itemp<=0)
    {
         cerr << "Error in dvar_vector constructor max index must be"
                 " >= minindex\n"
            << "minindex = " << ncl << " maxindex = " << nch <<endl;
         ad_exit(1);
    }
#endif
    gradient_structure* gs = gradient_structure::_instance;
    if (!gs)
    {
      cerr << "Error: instance of gradient_structure is a nullptr.\n";
      ad_exit(1);
    }
    if ((va = gs->ARR_LIST1->arr_new(itemp)) == 0)
    {
      cerr << " Error trying to allocate memory for dvar_vector\n";
      ad_exit(1);
    }
    else
    {
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
}

/**
 * Description not yet available.
 * \param
 */
   void dvar_vector::allocate(const ad_integer& ncl,const ad_integer& nch)
   {
     allocate(int(ncl),int(nch));
   }
