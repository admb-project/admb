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
#if !defined(__DF_POOL__)
#define  __DF_POOL__
#include <fvar.hpp>
extern void * pchecker;
//#define __CHECK_MEMORY__
class link;

/**
 * Description not yet available.
 * \param
 */
class dfpool
{
  int dfpool_vector_flag;
public:
  int nvar;
  int& on_dfpool_vector(void) {return dfpool_vector_flag;}
  char * last_chunk;
  struct link { link * next; };
  int num_allocated;
  int num_chunks;
  size_t nelem;
  size_t size;
  link * head;
  double * first;
  void grow(void);
#if defined(__CHECK_MEMORY__)
  int maxchunks;
  char * minaddress[100];
  char * maxaddress[100];
  int * pvalues;
  int nalloc;
#endif

public:
  dfpool();
  dfpool(const dfpool&) = delete;
  dfpool(const size_t);
  ~dfpool();

  dfpool& operator=(const dfpool&) = delete;

  void clean(void);
  void set_size(const size_t);
  void * alloc(void);
  void free(void * b);
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

/**
 * Description not yet available.
 * \param
 */
class tsdfpool : public dfpool
{
public:
  tsdfpool(int n);
  void * alloc(void);
  void free(void * b);
};

#endif //defined(__DF_POOL__)
