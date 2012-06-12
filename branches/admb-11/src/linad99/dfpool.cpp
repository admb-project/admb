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
//#define THREAD_SAFE
#include <fvar.hpp>

#include <dfpool.h>

#if defined(USE_VECTOR_SHAPE_POOL)

#if defined(THREAD_SAFE)
  pthread_mutex_t mutex_dfpool = PTHREAD_MUTEX_INITIALIZER;
#endif

  void my_do_nothing(void * t){}
//ofstream xofs("allocation");
vector_shape_pool * vector_shape::xpool = 
    new vector_shape_pool(sizeof(vector_shape));

vector_shape_pool * vector_shapex::xpool = 
    new vector_shape_pool(sizeof(vector_shapex));

vector_shape_pool  * arr_link::xpool = 
    new vector_shape_pool (sizeof(arr_link));

vector_shape_pool::vector_shape_pool(void) : dfpool(sizeof(vector_shape))
{ ;}

#if defined(THREAD_SAFE)
ts_vector_shape_pool::ts_vector_shape_pool(int n) : tsdfpool(n)
{ ;}
#endif

vector_shape_pool::vector_shape_pool(int n) : dfpool(n)
{ ;}

/**
 * Description not yet available.
 * \param
 */
void * vector_shape::operator new(size_t n)
{  
  if (xpool==0) 
  {
    xpool=new vector_shape_pool(sizeof(vector_shape));
  }
# if defined(SAFE_ALL)
  if (n != xpool->size)
  {
    cerr << "incorrect size requested in dfpool" << endl;
    ad_exit(1);
  }
# endif
  return xpool->alloc(); 
}

/**
 * Description not yet available.
 * \param
 */
void * arr_link::operator new(size_t n)
{  
  if (xpool==0) 
  {
    xpool=new vector_shape_pool(sizeof(vector_shape));
  }
# if defined(SAFE_ALL)
  if (n != xpool->size)
  {
    cerr << "incorrect size requested in dfpool" << endl;
    ad_exit(1);
  }
# endif
  return xpool->alloc(); 
}

/**
 * Description not yet available.
 * \param
 */
void * vector_shapex::operator new(size_t n)
{  
  if (xpool==0) 
  {
    xpool=new vector_shape_pool(sizeof(vector_shapex));
  }
# if defined(SAFE_ALL)
  if (n != xpool->size)
  {
    cerr << "incorrect size requested in dfpool" << endl;
    ad_exit(1);
  }
# endif
  return xpool->alloc(); 
}

#if defined(__CHECK_MEMORY__)
/**
 * Description not yet available.
 * \param
 */
void dfpool::sanity_check(void)
{
  link * p=head;
  int depth=0;
  while (p)
  {
    depth++;
    if(bad(p))
      cerr << "Error in dfpool structure" << endl;
    p=p->next;
  }
  cout << "Depth = " << depth << endl;
}

/**
 * Description not yet available.
 * \param
 */
void dfpool::sanity_check2(void)
{
  link * p=head;
  int depth=0;
  while (p)
  {
    depth++;
    if(badaddress(p))
      cerr << "Error in dfpool adresses" << endl;
    p=p->next;
  }
  cout << "Depth = " << depth << endl;
}

/**
 * Description not yet available.
 * \param
 */
void dfpool::sanity_check(void * ptr)
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
 * \param
 */
void dfpool::write_pointers(int mmin,int mmax)
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

dfpool::link ** global_p=0;

/**
 * Description not yet available.
 * \param
 */
void * dfpool::alloc(void)
{
#if defined(THREAD_SAFE)
  pthread_mutex_lock(&mutex_dfpool);
#endif
  if (!head) grow();
  link * p = head;
  global_p = &head;
#if defined(__CHECK_MEMORY__)
  if(bad(p))
  {
    cerr << "Error in dfpool structure" << endl;
    ad_exit(1);
  }
  if (p->next)
  {
    if(bad(p->next))
    {
      cerr << "Error in dfpool structure" << endl;
      ad_exit(1);
    }
  }
#endif
  head = p->next;
  num_allocated++;
  //cout << "allocating " << p << endl;
#if defined(__CHECK_MEMORY__)
  if (p == pchecker)
  {
    cout << "trying to allocate already allocated object " << endl;
  }
#endif
#if defined(THREAD_SAFE)
  pthread_mutex_unlock(&mutex_dfpool);
#endif
  return p;
}
#if defined(THREAD_SAFE)
/**
 * Description not yet available.
 * \param
 */
void * tsdfpool::alloc(void)
{
#if defined(THREAD_SAFE)
 // pthread_mutex_lock(&mutex_dfpool);
#endif
  if (!head) grow();
  link * p = head;
  global_p = &head;
#if defined(__CHECK_MEMORY__)
  if(bad(p))
  {
    cerr << "Error in dfpool structure" << endl;
    ad_exit(1);
  }
  if (p->next)
  {
    if(bad(p->next))
    {
      cerr << "Error in dfpool structure" << endl;
      ad_exit(1);
    }
  }
#endif
  head = p->next;
  num_allocated++;
  //cout << "allocating " << p << endl;
#if defined(__CHECK_MEMORY__)
  if (p == pchecker)
  {
    cout << "trying to allocate already allocated object " << endl;
  }
#endif
#if defined(THREAD_SAFE)
  //pthread_mutex_unlock(&mutex_dfpool);
#endif
  return p;
}
#endif

#if defined(__CHECK_MEMORY__)

/**
 * Description not yet available.
 * \param
 */
int dfpool::bad(link * p)
{
  int flag=1;
  //if (!df1b2variable::dfpool_counter)
  {
    //int ip=(int)p;
    for (int i=1;i<=99;i++)
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
int dfpool::badaddress(link * p)
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
void dfpool::free(void * b)
{
#if defined(SAFE_ALL)
#endif

#if defined(THREAD_SAFE)
  pthread_mutex_lock(&mutex_dfpool);
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
#if defined(THREAD_SAFE)
  pthread_mutex_unlock(&mutex_dfpool);
#endif
}
#if defined(THREAD_SAFE)

/**
 * Description not yet available.
 * \param
 */
void tsdfpool::free(void * b)
{
#if defined(SAFE_ALL)
#endif

#if defined(THREAD_SAFE)
  //pthread_mutex_lock(&mutex_dfpool);
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
#if defined(THREAD_SAFE)
  //pthread_mutex_unlock(&mutex_dfpool);
#endif
}
#endif

/**
 * Description not yet available.
 * \param
 */
dfpool::~dfpool(void)
{
  deallocate();
}

/**
 * Description not yet available.
 * \param
 */
dfpool::dfpool(unsigned sz) : size(sz<sizeof(link *)?sizeof(link*):sz)
{
  dfpool_vector_flag=0;
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
 * Description not yet available.
 * \param
 */
dfpool::dfpool(void) 
{
  dfpool_vector_flag=0;
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
 * Description not yet available.
 * \param
 */
void dfpool::set_size(unsigned int sz)
{
  if (size !=sz && size != 0)
    cerr << "You can not change the allocation size in mid stream" << endl;
  else
    size=sz;
}


//void xxiieeuu(void * tmp0){;}

/**
 * Description not yet available.
 * \param
 */
void dfpool::deallocate(void)
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
void dfpool::deallocate(void)
{
  last_chunk=0
  size=0;
  head = 0;
}
*/

 const int pvalues_size=500000;

/**
 * Description not yet available.
 * \param
 */
void dfpool::grow(void)
{
#if defined(__CHECK_MEMORY__)
  if (!pvalues)
  {
    maxchunks=100;
    nalloc=0;
    pvalues=new int[pvalues_size];
  }
#endif
  if (!size)
  {
    cerr << "error in dfpool object " // << poolname
         << " you must set the unit size " << endl;
    ad_exit(1);
  }
  const int overhead = 12+sizeof(char*);
  const int chunk_size= 65000-overhead;
  nelem= chunk_size/size;
  char * real_start=new char[chunk_size+6];
  char * start=real_start+sizeof(char *);
  char *last = &start[(nelem-1)*size];
  num_chunks++;
#if defined(__CHECK_MEMORY__)
  if (num_chunks<maxchunks)
  {
    minaddress[num_chunks]=real_start;
    maxaddress[num_chunks]=real_start+chunk_size-1;
  }
#endif
  if (last_chunk == 0 ) 
  {
    last_chunk=real_start;
    *(char**) real_start=0;
  }
  else
  {
    *(char**) real_start=last_chunk;
    last_chunk=real_start;
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
  for (char *p=start; p<last; p+=size)
  {
    ((link *)p)->next = (link*)(p+size);
#if defined(__CHECK_MEMORY__)
    pvalues[nalloc++]=int((link*)(p+size));
#endif
  }
  ((link*)last)->next=0;
  head = (link*) start;
  first= (double*) start;
}

/**
 * Description not yet available.
 * \param
 */
void dfpool::clean(void)
{
  if (!size)
  {
    cerr << "error in dfpool object " // << poolname
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

#endif  // #if defined(USE_VECTOR_SHAPE_POOL)
