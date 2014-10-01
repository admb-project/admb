/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 *
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "BSD" license.
 *
 * License:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2.  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3.  Neither the name of the  University of California, Otter Research,
 * nor the ADMB Foundation nor the names of its contributors may be used
 * to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
 * \file
 * Description not yet available.
 */

#if !defined(__AD_POOL__)
#define  __AD_POOL__
#include <fvar.hpp>
extern void * pchecker;
//#define __CHECK_MEMORY__

/**
 * Description not yet available.
 */
class adpool
{
  static int num_adpools;
  int adpool_vector_flag;
public:
  adpool();
  adpool(const size_t);
 ~adpool();

  int depth_check(void);
  int nvar;
  int& on_adpool_vector(void) {return adpool_vector_flag;}
  char * last_chunk;
  struct link { link * next; };
  int num_allocated;
  int num_chunks;
  int nelem;
  size_t size;
  link* head;
  double* first;
  adpool(adpool&);  // copy protection
  void operator=(adpool&); // copy protection
  void grow(void);
#if defined(__CHECK_MEMORY__)
  int maxchunks;
  char * minaddress[2000];
  char * maxaddress[2000];
  int * pvalues;
  int nalloc;
#endif
public:
  void clean(void);
  void set_size(const size_t);
  void* alloc(void);
  void free(void* b);
  void deallocate(void);
#if defined(__CHECK_MEMORY__)
  int bad(link * p);
  int badaddress(link * p);
  void sanity_check(void);
  void sanity_check(void *);
  void sanity_check2(void);
  void write_pointers(int m,int max);
#endif
};

#endif //defined(__AD_POOL__)
