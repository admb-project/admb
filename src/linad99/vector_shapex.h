/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 *
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "New BSD" license
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
 */

#ifndef __ADMB_VECTOR_SHAPEX_H__
#define __ADMB_VECTOR_SHAPEX_H__
/**
Holds "shape" information for vector objects.
*/
class vector_shapex
{
 public:
   vector_shapex(int lb, int ub, void *p):index_min(lb),
      index_max(ub), ncopies(0), trueptr(p)
   {
   }
   /// Returns address of first element in the vector.
   void *get_truepointer(void)
   {
      return trueptr;
   }
#if defined(USE_VECTOR_SHAPE_POOL)
  static vector_shape_pool& get_xpool()
  {
    static vector_shape_pool xpool(sizeof(vector_shapex));
    return xpool;
  }
  void* operator new(size_t);
  void operator delete(void* ptr, size_t)
    { vector_shapex::get_xpool().free(ptr); }
#endif
  vector_shapex(const vector_shapex&) = delete;
  vector_shapex& operator=(const vector_shapex&) = delete;

   void shift(int min);
   int index_min;  ///< Minimum valid subscript
   int index_max;  ///< Maximum valid subscript
   /** Copy counter to enable shallow copies.
   Initialized to zero in constructor.
   Incremented by 1 in copy constructor.
   Decremented by 1 in destructor.
   Memory is freed when value of ncopies reaches zero
   in the destructor.
   */
   unsigned int ncopies;
   /** Address of first element in the vector.
   Value set in allocate(...) function. */
   void *trueptr;

public:
   unsigned int decr_ncopies(void)  ///< Decrement copy counter by 1.
   {
      return ncopies == 0 ? 0 : --ncopies;
   }
   unsigned int get_ncopies(void) ///< Return value of copy counter
   {
      return ncopies;
   }
   unsigned int incr_ncopies(void)  ///< Increment copy counter by 1.
   {
      return ++ncopies;
   }
   int indexmin() ///< Return value of minimum valid subscript.
   {
      return index_min;
   }
   int indexmax() ///< Return value of maximum valid subscript.
   {
      return index_max;
   }

  friend class subdvector;
  friend class lvector;
  friend class ptr_vector;
  friend class dvector;
  friend class ivector;
  friend class dvar_vector;
};
#endif
