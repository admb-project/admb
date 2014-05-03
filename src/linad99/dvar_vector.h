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

#ifndef __ADMB_DVAR_VECTOR_H__
#define __ADMB_DVAR_VECTOR_H__

#include <double_and_int.h>
#include <prevariable.h>

class double_and_int;
class arr_link;

class predvar_vector
{
   dvar_vector *p;
   int lb;
   int ub;
   inline predvar_vector(dvar_vector * _p, int _lb, int _ub)
   {
      p = _p;
      lb = _lb, ub = _ub;
   }
   friend class dvar_vector;
};


class dvar_vector
{
 public:
   double_and_int * va;
   int index_min;
   int index_max;
   arr_link *link_ptr;
   vector_shapex *shape;
 public:
   dvar_vector operator -();

   dvar_vector & operator --(void)
   {
      index_min--;
      index_max--;
      va++;
      return *this;
   }
   dvar_vector & operator ++(void)
   {
      index_min++;
      index_max++;
      va--;
      return *this;
   }
   dvar_vector sub(int lb, int ub)
   {
      return predvar_vector(this, lb, ub);
   }
   dvar_vector operator () (int lb, int ub)
   {
      return predvar_vector(this, lb, ub);
   }
   void shallow_copy(const dvar_vector &);
   int operator!(void) const
   {
      return (shape == NULL);
   }
   friend class dvar_matrix;
   friend class dvar3_array;
   friend class banded_symmetric_dvar_matrix;
   friend class banded_lower_triangular_dvar_matrix;
   friend class banded_symmetric_dmatrix;
   friend class banded_lower_triangular_dmatrix;

   void fill_randpoisson(double lambda, const random_number_generator & rng);
   void fill_randnegbinomial(double lambda, double tau,
     const random_number_generator & rng);
   prevariable elem(int i)
   {
      return (va + i);
   }

   double &elem_value(int i)
   {
      return (va[i].x);
   }

   double_and_int *get_va()
   {
      return va;
   }

   prevariable elem(int i) const
   {
      return (va + i);
   }

   double &elem_value(int i) const
   {
      return (va[i].x);
   }

   double_and_int *get_va() const
   {
      return va;
   }

   friend dvar_matrix operator*(const dvar_matrix & m1, const dmatrix & m2);

   void deallocate();
   dvar_vector(const dvar_vector &);
   dvar_vector(const predvar_vector &);
   dvar_vector();
   dvar_vector(int ncl, int ncu); // makes an array [ncl..ncu]
   dvar_vector(int ncl, int ncu, kkludge_object);

   //dvar_vector(const ad_integer&,const ad_integer&);
   dvar_vector(unsigned int sz, double *x);
   dvar_vector(const independent_variables &);
   friend char *fform(const char *, const dvar_vector &);
#   if defined(__NUMBERVECTOR__)
   dvar_vector(const param_init_number_vector &);
   dvar_vector(const param_init_bounded_number_vector &);
#   endif
   dvar_vector(const dvector &);
   dvar_vector(const char *);
   ~dvar_vector();
   void allocate(int, int);
   void allocate(void);
   void allocate(const dvector &);
   void allocatec(const dvar_vector &);
   void allocate(const dvar_vector &);

   void allocate(const ad_integer &, const ad_integer &);
   void initialize(const dvector & ww);
   void initialize(void);
   void save_dvar_vector_position(void) const;
   void save_dvar_vector_value(void) const;
   void write_on(const ostream &) const;
   void write_on(const uostream &) const;
   void read_from(const istream &);
   void read_from(const uistream &);
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
   // returns the number of elements
   int size() const
   {
      return (index_max - index_min + 1);
   }
   dvar_vector & shift(int min);

#ifdef OPT_LIB
#if defined(__NDPX__) || defined(__SUN__)
   inline prevariable operator() (register int i)
   {
      return (va + i);
   }
   inline prevariable operator[] (register int i)
   {
      return (va + i);
   }
   inline const prevariable operator() (int i) const
   {
      return (va + i);
   }
   inline const prevariable operator[] (int i) const
   {
      return (va + i);
   }
#else
   inline prevariable operator() (int i)
   {
      return (va + i);
   }
   inline prevariable operator[] (int i)
   {
      return (va + i);
   }
   inline const prevariable operator() (int i) const
   {
      return (va + i);
   }
   inline const prevariable operator[] (int i) const
   {
      return (va + i);
   }
#endif
#else
   prevariable operator[] (int i);
   prevariable operator() (int i);
   const prevariable operator[] (int i) const;
   const prevariable operator() (int i) const;
#endif

   double *initpointer(void)
   {
      return ((double *) (va + indexmin()));
   }
   const double *initpointer(void) const
   {
      return ((double *) (va + indexmin()));
   }
   dvar_vector operator() (const lvector &);
   //dvar_vector operator()(int,int);
   dvar_vector operator () (const ivector & u);
   dvar_vector & operator+=(const prevariable & d);
   dvar_vector & operator+=(double d);
   dvar_vector & operator/=(const prevariable & d);
   //dvar_vector& operator*=(const dvariable& d);
   dvar_vector & operator*=(const prevariable & d);
   dvar_vector & operator*=(double d);
   dvar_vector & operator/=(double d);
   dvar_vector & operator-=(const prevariable & d);
   dvar_vector & operator-=(double d);
   dvar_vector & operator+=(const dvector & v1);
   dvar_vector & operator-=(const dvector & v1);
   dvar_vector & operator+=(const dvar_vector & v1);
   dvar_vector & operator-=(const dvar_vector & v1);
   dvar_vector & operator=(const dvar_vector & t);
   dvar_vector & operator=(const dvector & t);
   dvar_vector & operator =(double t);
   dvar_vector & operator=(const prevariable & t);
   void fill(const char *);
   void fill_randu(long int &n);
   void fill_randn(long int &n);
   void fill_randbi(long int &n, double);

   void fill_randu_ni(long int &n);
   void fill_randn_ni(long int &n);
   void fill_randbi_ni(long int &n, double);

   void fill_seqadd(double, double);
   void fill_multinomial(const int &seed, const dvector & p);
   void fill_multinomial(const random_number_generator& rng, const dvector& p);
   friend dvar_vector operator+(const dvar_vector &, const dvar_vector &);
   friend dvar_vector operator+(const dvar_vector &, const dvector &);
   friend dvar_vector operator+(const dvector &, const dvar_vector &);
   friend dvar_vector operator-(const dvar_vector &, const dvar_vector &);

   friend dvar_vector operator-(const dvector &, const dvar_vector &);

   friend dvar_vector operator-(const dvar_vector &, const dvector &);

   friend dvar_vector sigmoid(const dvar_vector & t1);

   friend dvariable operator*(const dvar_vector &, const dvar_vector &);

   friend dvar_vector elem_div(const dvar_vector &, const dvar_vector &);

   friend dvariable operator*(const dvector &, const dvar_vector &);

   friend dvariable operator*(const dvar_vector &, const dvector &);

   friend dvar_vector operator*(const prevariable &, const dvar_vector &);

   friend dvar_vector operator*(const prevariable &, const dvector &);

   friend dvar_vector operator*(double, const dvar_vector &);

   friend dvar_vector operator*(const dvar_vector &, const dmatrix &);

   friend dvar_vector operator*(const dmatrix &, const dvar_vector &);

   friend dvar_vector operator*(const dvar_vector &, const dvar_matrix &);

   friend dvar_vector operator*(const dvar_matrix &, const dvar_vector &);

   friend dvar_matrix operator*(const dvar_matrix &, const dvar_matrix &);

   friend dvar_matrix operator*(const dmatrix &, const dvar_matrix &);

   friend dvar_vector elem_prod(const dvar_vector &, const dvar_vector &);

   friend dvar_vector first_difference(const dvar_vector &);
   friend dvar_vector second_difference(const dvar_vector &);

   // js, see above
   //friend dvar_vector elem_div(const dvar_vector&, const dvar_vector&);

   friend dvar_vector elem_prod(const dvector &, const dvar_vector &);

   friend dvar_vector elem_div(const dvector &, const dvar_vector &);

   friend dvar_vector elem_prod(const dvar_vector &, const dvector &);

   friend dvar_vector elem_div(const dvar_vector &, const dvector &);

   friend dvariable norm(const dvar_vector &);
   friend dvariable norm2(const dvar_vector &);
   friend dvariable sumsq(const dvar_vector &);

   friend void copy_status(const ostream & s, const dvar_vector & v);

   friend dvar_vector exp(const dvar_vector &);

   friend dvar_vector log(const dvar_vector &);

   friend dvar_vector sin(const dvar_vector &);

   friend dvar_vector fabs(const dvar_vector &);

   friend dvector value(const dvar_vector & v1);

   friend dvar_vector sfabs(const dvar_vector &);

   friend void make_indvar_list(const dvar_vector &);
   friend class array_size;
};
#endif
