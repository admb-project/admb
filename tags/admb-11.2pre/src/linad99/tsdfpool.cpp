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
#if defined(THREAD_SAFE)
#include <fvar.hpp>
//#undef USE_VECTOR_SHAPE_POOL

#include <dfpool.h>


#if defined(THREAD_SAFE)
  extern pthread_mutex_t mutex_dfpool;
  extern pthread_key_t admb_pthread_key;
  //pthread_mutex_t mutex_dfpool = PTHREAD_MUTEX_INITIALIZER;
  //pthread_key_t admb_pthread_key;
#endif

tsdfpool::tsdfpool(int n) : dfpool(n) {}

//ofstream xofs("allocation");
typedef ts_vector_shape_pool * pts_vector_shape_pool;


#if defined(USE_VECTOR_SHAPE_POOL)
ts_vector_shape_pool ** ts_vector_shapex::xpool = 0;
#endif

/**
 * Description not yet available.
 * \param
 */
  void ts_vector_shapex::shift(int min)
  {
    index_max=index_max-index_min+min;
    index_min=min;
  }

const int max_number_threads=10;

/**
 * Description not yet available.
 * \param
 */
  int get_pthread_number(void)
  {
    int* p_keyval = (int*)pthread_getspecific(admb_pthread_key);
     int tmp;
    if (p_keyval)
    {
      tmp=*p_keyval;
    }
    else
    {
      tmp=0;
    }
    return tmp;
  }

#if defined(USE_VECTOR_SHAPE_POOL)

/**
 * Description not yet available.
 * \param
 */
void * ts_vector_shapex::operator new(size_t n)
{
  if (xpool==0)
  {
    pthread_mutex_lock(&mutex_dfpool);
    if (xpool==0)
    {
      xpool = new pts_vector_shape_pool[max_number_threads];
      for (int i=0;i<max_number_threads;i++)
      {
        xpool[i]=0;
      }
      pthread_mutex_unlock(&mutex_dfpool);
    }
  }

  int pnum=get_pthread_number();
  if (xpool[pnum]==0)
  {
    xpool[pnum]=new ts_vector_shape_pool(sizeof(ts_vector_shapex));
  }
# if defined(SAFE_ALL)
  if (n != xpool[pnum]->size)
  {
    cerr << "incorrect size requested in dfpool" << endl;
    ad_exit(1);
  }
# endif
  return xpool[pnum]->alloc();
}

/**
 * Description not yet available.
 * \param
 */
  void ts_vector_shapex::operator delete(void * ptr,size_t n)
  {
    xpool[get_pthread_number()]->free(ptr);
  }
#endif // defined(THREAD_SAFE)
#endif // defined(THREAD_SAFE)
