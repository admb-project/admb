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

#include <stdint.h>
#include <df1b2fun.h>
#include <adpool.h>
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif
//#define (_USE_VALGRIND_)
int adpool::num_adpools = 0;

/**
 * Description not yet available.
 * \param
 */
int adpool::depth_check()
{
  int depth = 0;

  link* p = head;
  while (p)
  {
    ++depth;
    p = p->next;
  }

  return depth;
}

#if defined(__CHECK_MEMORY__)
/**
 * Description not yet available.
 * \param
 */
void adpool::sanity_check(void)
{
  link* p = head;
  int depth = 0;
  while (p)
  {
    depth++;
    if(bad(p))
      cerr << "Error in adpool structure" << endl;
    p=p->next;
  }
  cout << "Depth = " << depth << endl;
}

/**
 * Description not yet available.
 * \param
 */
void adpool::sanity_check2(void)
{
  link * p=head;
  int depth=0;
  while (p)
  {
    depth++;
    if(badaddress(p))
      cerr << "Error in adpool adresses" << endl;
    p=p->next;
  }
  cout << "Depth = " << depth << endl;
}

/**
 * Description not yet available.
 * \param
 */
void adpool::sanity_check(void * ptr)
{
  link * p=head;
  int depth=0;
  while (p)
  {
    depth++;
    if (p == ptr)
    {
      cerr << "both allocated and unallocated memory at entry "
           << depth << endl;
      break;
    }
    p=p->next;
  }
}

/**
 * Description not yet available.
 * \param mmin Integer
 * \param mmax Integer
 */
void adpool::write_pointers(int mmin,int mmax)
{
  link* p = head;
  int index=0;
  while (p)
  {
    index++;
    if (index >=mmin && index <=mmax)
      cout << index << "  "  << int(p) << endl;
    p=p->next;
  }
}
#endif

/**
Return a ptr from adpool space.
*/
void* adpool::alloc()
{
  if (!head)
  {
    grow();
  }
  link* p = head;

#if defined(__CHECK_MEMORY__)
  if(bad(p))
  {
    cerr << "Error in adpool structure" << endl;
    ad_exit(1);
  }
  if (p->next)
  {
    if(bad(p->next))
    {
      cerr << "Error in adpool structure" << endl;
      ad_exit(1);
    }
  }
#endif

  head = p->next;
  ++num_allocated;

#if defined(__CHECK_MEMORY__)
  if (p == pchecker)
  {
    cout << "trying to allocate already allocated object " << endl;
  }
#endif

#ifndef OPT_LIB
  assert(nvar <= SHRT_MAX);
#endif
  ((twointsandptr*)p)->nvar=(short)nvar;
  ((twointsandptr*)p)->ptr=this;
#if defined (INCLUDE_BLOCKSIZE)
  ((twointsandptr*)p)->blocksize=size;
#endif

  return p;
}

#if defined(__CHECK_MEMORY__)
/**
 * Description not yet available.
 */
int adpool::bad(link * p)
{
  int flag=1;
  //if (!df1b2variable::adpool_counter)
  {
    //int ip=(int)p;
    for (int i=1;i<maxchunks;i++)
    {
      if ( p >= minaddress[i] && p <= maxaddress[i])
      {
        flag=0;
        break;
      }
    }
  }
  //else
  //{
  //  flag=0;
  //}
  if (flag)
  {
    cerr << "bad pool object" << endl;
  }
  return flag;
}

/**
 * Description not yet available.
 * \param
 */
int adpool::badaddress(link * p)
{
  int flag=1;
  int ip=(int)p;
  for (int i=0;i<=nalloc;i++)
  {
    if ( ip == pvalues[i])
    {
      flag=0;
      break;
    }
  }
  return flag;
}
void * pchecker=0;
#endif

/**
Put back ptr from adpool::alloc to adpool space.
*/
void adpool::free(void* b)
{
#if defined(SAFE_ALL)
  twointsandptr* tmp = (twointsandptr*)(b);
  if (tmp->nvar != nvar)
  {
    cerr << "trying to add wrong sized memory block to adpool" << endl;
    ad_exit(1);
  }
#endif

#if defined (INCLUDE_BLOCKSIZE)

  {
    twointsandptr* tmp = (twointsandptr*)(b);
    if (tmp->blocksize != size)
    {
      cerr << "trying to add wrong sized memory block to adpool" << endl;
      ad_exit(1);
    }
  }
#endif

#if defined(__CHECK_MEMORY__)
   if (pchecker)
   {
     if (b == pchecker)
     {
       cout << "trying to deallocate allocated object " << endl;
     }
   }
#endif
  ((link*)b)->next = head;
  head = (link*)b;
  num_allocated--;
}
/**
Default constructor
*/
adpool::adpool()
{
#ifndef OPT_LIB
  //Error because sizeof(twointsandptr)>2*sizeof(double)
  assert(sizeof(twointsandptr) <= sizeof(double) * 2);
#endif

  ++num_adpools;
  adpool_vector_flag=0;
  size=0;
  last_chunk = NULL;
  head = 0;
  num_allocated=0;
  num_chunks=0;
  first = NULL;
  nelem = 0;
  nvar = 0;
#if defined(__CHECK_MEMORY__)
  nalloc=0;
  pvalues=0;
  maxchunks=0;
#endif
}
/**
 * Description not yet available.
 * \param
 */
adpool::adpool(const size_t sz):
  size(sizeof(link*))
{
  num_adpools++;
  adpool_vector_flag=0;
  if (sz > size) size = sz;
  last_chunk = NULL;
  head = 0;
  num_allocated=0;
  num_chunks=0;
  first = NULL;
  nelem = 0;
  nvar = 0;
#if defined(__CHECK_MEMORY__)
  nalloc=0;
  pvalues=0;
  maxchunks=0;
#endif
}
/**
Destructor
*/
adpool::~adpool()
{
  num_adpools--;
  deallocate();
}

/**
Set size of adpool.

/param sz is a non-negative integer
*/
void adpool::set_size(const size_t sz)
{
  if (size != sz && size != 0)
  {
    cerr << "You can not change the allocation size in mid stream\n"
         << " current size is " << size << " trying to change to "
         << sz << '\n';
  }
  size = sz;
}

/**
Free all adpool space.
*/
void adpool::deallocate()
{
#if defined(__CHECK_MEMORY__)
  sanity_check();
  sanity_check2();
#endif
  intptr_t address;
  while (last_chunk)
  {
    --num_chunks;
    memcpy(&address, &last_chunk[0], sizeof(intptr_t));
    delete [] last_chunk;
    last_chunk = (char*)address;
  }
  size = 0;
  head = NULL;
  num_allocated = 0;
  first = NULL;
  nelem = 0;
#if defined(__CHECK_MEMORY__)
  nalloc=0;
  delete [] pvalues;
  pvalues=0;
#endif
}
/**
Allocate more adpool space.
*/
void adpool::grow()
{
#ifndef OPT_LIB
  //error in adpool object you must set the unit size
  assert(size > 0);
#endif

  const size_t overhead = sizeof(intptr_t);
  const size_t chunk_size = 16 * 65000;
  nelem = (chunk_size - overhead)/ size;

  size_t length = overhead + nelem * size;
  char* real_start = new char[length];
  memset(real_start, 0, length);

  if (last_chunk)
  {
    intptr_t address = (intptr_t)&last_chunk[0];
    memcpy(&real_start[0], &address, overhead);
  }
  last_chunk = real_start;
  ++num_chunks;

  char* start = real_start + overhead;
  head = (link*)start;
  first = (double*)start;

  char* last = start + size * (nelem - 1);
  for (char* p = start; p < last; p += size)
  {
    ((link*)p)->next = (link*)(p + size);
  }
  ((link*)last)->next = NULL;
}

/**
 * Description not yet available.
 * \param
 */
void adpool::clean(void)
{
  if (!size)
  {
    cerr << "error in adpool object " // << poolname
         << " you must set the unit size " << endl;
  }
  //const int overhead = 12;

  double *ptr=first;
  for (size_t i=1;i<=nelem;i++)
  {
    ptr++;
    for(unsigned int j=1;j<=size/sizeof(double)-2;j++) *ptr++=0.0;
    ptr++;
  }
}
