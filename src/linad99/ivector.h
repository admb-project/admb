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

#ifndef __ADMB_IVECTOR_H__
#define __ADMB_IVECTOR_H__

#include "vector_shapex.h"

/**
*/
class ivector
{
protected:
  int index_min;
  int index_max;
  int *v;
  vector_shapex *shape;

public:
  ivector();
  ivector(const lvector&);
  ~ivector();

   int allocated() const
   {
      return (shape != NULL);
   }
   ivector& operator--()
   {
      index_min--;
      index_max--;
      v++;
      return *this;
   }
   void reallocate(double size);

   ivector& operator++()
   {
      index_min++;
      index_max++;
      v--;
      return *this;
   }
   int operator!() const
   {
      return (shape == NULL);
   }

   unsigned int get_ncopies() const
   {
     return shape ? shape->get_ncopies() : 0;
   }

   int& elem(int i)
   {
      return (v[i]);
   }
   const int& elem(int i) const
   {
      return v[i];
   }
   // returns the minimum allowable index
   int indexmin() const
   {
      return index_min;
   }
   // returns the maximum allowable index
   int indexmax() const
   {
      return index_max;
   }
   // returns the maximum allowable index
  int size() const
  {
    return v ? index_max - index_min + 1 : 0;
  }
   int *get_v() const
   {
      return v;
   }
   ivector& shift(int min);
   //ivector(unsigned int sz); //makes an array [0..sz]
   //inline allocated(void) {return ::allocated(this);}

   ivector(const dvector&);

   void fill(const char *s);
   void fill_seqadd(int, int);
   void fill_multinomial(const int& seed, const dvector& p);
   void fill_multinomial(const random_number_generator& rng,
     const dvector& p);
   ivector(int ncl, int ncu);
   ivector(const ad_integer& ncl, const index_type& ncu);
   void allocate(const ad_integer& ncl, const index_type& ncu);
   // makes an array [ncl..ncu]

   ivector(unsigned int sz, long int *x);

   void safe_allocate(int ncl, int ncu);
   void allocate(int ncl, int ncu);
   void allocate(const ivector& iv);
   void allocate(const dvector& dv);
   void allocate(const char *);
   void allocate();
   void deallocate();
   void safe_deallocate();

   //operator int* () {return v;}

   void save_ivector_position() const;

   void save_ivector_value() const;

   void write_on(const ostream& s) const;

   void read_from(const istream& s);

   void write_on(const uostream& s) const;

   void read_from(const uistream& s);

   int& operator[](int i);
   int& operator()(int i);
   const int& operator[](int i) const;
   const int& operator()(int i) const;

   ivector sub(int lb, int ub)
   {
      return preivector(this, lb, ub);
   }
   ivector operator()(int lb, int ub)
   {
      return preivector(this, lb, ub);
   }
   ivector(const preivector& pd);

   ivector operator()(const ivector& u);

   ivector(const ivector& t);
   void shallow_copy(const ivector& t);

   ivector& operator=(const ivector& t);
   ivector& operator=(int t);

   ivector& operator=(const lvector& t);

   void initialize(void);
   ivector& operator+=(const ivector& t);
   ivector& operator+=(int t);

  friend class vector_index;
  friend class imatrix;
  friend class i3_array;
};

#ifdef OPT_LIB
inline int& ivector::operator[](int i)
{
  return *(v + i);
}
inline int& ivector::operator()(int i)
{
  return *(v + i);
}
inline const int& ivector::operator[](int i) const
{
  return *(v + i);
}
inline const int& ivector::operator()(int i) const
{
  return *(v + i);
}
#endif

ivector operator+(const ivector& v, const ivector& w);
ivector operator-(const ivector& v, const ivector& w);
ivector operator+(const ivector& v, int w);
ivector operator-(const ivector& v, int w);
ivector operator+(int v, const ivector& w);
ivector operator-(int v, const ivector& w);

#endif
