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
#include <adpool.h>
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif
//#define (_USE_VALGRIND_)

/**
 * Description not yet available.
 * \param
 */
int adpool::depth_check(void)
{
  link * p=head;
  int depth=0;
  while (p)
  {
    depth++;
    p=p->next;
  }
  return depth;
}


  int adpool::num_adpools=0;

#if defined(__CHECK_MEMORY__)
/**
 * Description not yet available.
 * \param
 */
void adpool::sanity_check(void)
{
  link * p=head;
  int depth=0;
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
  link * p=head;
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
Allocate memory for link*.
*/
void* adpool::alloc(void)
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
  num_allocated++;

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
 * Description not yet available.
 * \param
 */
void adpool::free(void * b)
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
  //cout << "freeing " << b << endl;
  link * p = (link*) b;
  p->next = head;
  num_allocated--;
  head = p;
}

/**
 * Description not yet available.
 * \param
 */
adpool::~adpool(void)
{
  num_adpools--;
  deallocate();
}

/**
 * Description not yet available.
 * \param
 */
adpool::adpool(const size_t sz):
  size(sz < sizeof(link*) ? sizeof(link*) : sz)
{
  num_adpools++;
  adpool_vector_flag=0;
  if (!sz) size=0;
  last_chunk=0;
  head = 0;
  num_allocated=0;
  num_chunks=0;
#if defined(__CHECK_MEMORY__)
  nalloc=0;
  pvalues=0;
  maxchunks=0;
#endif
}

/**
Default constructor
*/
adpool::adpool()
{
  num_adpools++;
  int i1=sizeof(twointsandptr);
  int i2=2*sizeof(double);
  if (i1>i2)
  {
    cout << "Error because sizeof(twointsandptr)>2*sizeof(double)" << endl;
    ad_exit(1);
  }
  adpool_vector_flag=0;
  size=0;
  last_chunk=0;
  head = 0;
  num_allocated=0;
  num_chunks=0;
#if defined(__CHECK_MEMORY__)
  nalloc=0;
  pvalues=0;
  maxchunks=0;
#endif
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
 * Description not yet available.
 * \param
 */
void adpool::deallocate(void)
{
#if defined(__CHECK_MEMORY__)
  sanity_check();
  sanity_check2();
#endif
  while (last_chunk)
  {
    num_chunks--;
    char * tmp=*(char**) last_chunk;
    delete [] last_chunk;
    last_chunk=tmp;
  }
  size=0;
  head=0;
  num_allocated=0;
  first=0;
#if defined(__CHECK_MEMORY__)
  nalloc=0;
  delete [] pvalues;
  pvalues=0;
#endif
}
/*
void adpool::deallocate(void)
{
  last_chunk=0
  size=0;
  head = 0;
}
*/

/**
*/
void adpool::grow(void)
{
#if defined(__CHECK_MEMORY__)
  const int pvalues_size=500000;
  if (!pvalues)
  {
    maxchunks=20000;
    nalloc=0;
    pvalues=new int[pvalues_size];
  }
#endif

  const int overhead = 12 + sizeof(char*);
  const int chunk_size = 16 * 65000 - overhead;
  char* real_start = new char[chunk_size];

  if (size > 0)
  {
    nelem = chunk_size / size;
  }
  else
  {
    cerr << "error in adpool object " // << poolname
         << " you must set the unit size " << endl;
    ad_exit(1);
  }

#if defined(_USE_VALGRIND_)
   VALGRIND_MAKE_MEM_NOACCESS(realstart,chunk_size);
#endif

  char* start = real_start + sizeof(char*);
  char* last = &start[(nelem - 1) * size];
  num_chunks++;

#if defined(__CHECK_MEMORY__)
  if (num_chunks<maxchunks)
  {
    minaddress[num_chunks]=(real_start);
    maxaddress[num_chunks]=(real_start+chunk_size-1);
  }
#endif

  if (last_chunk == 0)
  {
    last_chunk = real_start;
    *(char**)real_start = 0;
  }
  else
  {
    *(char**)real_start = last_chunk;
    last_chunk = real_start;
  }

#if defined(__CHECK_MEMORY__)
  if (nalloc>pvalues_size-1)
  {
    cerr << "Error in check memory need to make pvalues bigger than "
      << pvalues_size << endl;
    ad_exit(1);
  }
  pvalues[nalloc++]=int(start);
#endif

  for (char* p = start; p < last; p += size)
  {
    ((link *)p)->next = (link*)(p+size);
#if defined(__CHECK_MEMORY__)
    pvalues[nalloc++]=int((link*)(p+size));
#endif
  }

  ((link*)last)->next = 0;
  head = (link*)start;
  first = (double*)start;
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
  for (int i=1;i<=nelem;i++)
  {
    ptr++;
    for(unsigned int j=1;j<=size/sizeof(double)-2;j++) *ptr++=0.0;
    ptr++;
  }
}
