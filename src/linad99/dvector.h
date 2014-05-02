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

#ifndef __ADMB_DVECTOR_H__
#define __ADMB_DVECTOR_H__

/** Vector of double precision numbers.
A basic container class for a one dimensional array of double precision
floating point numbers.
Fundamental building block for higher dimensional arrays.
All ADMB vector classes have similar functionality.
*/
class dvector
{
 protected:
   double *v; ///< pointer to the data
   int index_min; ///< minimum valid subscript
   int index_max; ///< maximum valid subscript
   /// pointer to vector "shape"
#if defined(THREAD_SAFE)
   ts_vector_shapex *shape;
#else
   vector_shapex *shape;
#endif

 public:
   dvector operator -();
   /// Returns 1 (TRUE) if memory is NOT allocated
   int operator!(void) const
   {
      return (shape == NULL);
   }
   /// Returns 1 (TRUE) if memory is allocated.
   int allocated(void) const
   {
      return (shape != NULL);
   }
   /// Decrement vector indices array pointer.
   dvector & operator --(void)
   {
      index_min--;
      index_max--;
      v++;
      return *this;
   }
   /// Increment vector indices array pointer.
   dvector & operator ++(void)
   {
      index_min++;
      index_max++;
      v--;
      return *this;
   }
   void reallocate(double size);
   /** Get subvector.
   \param lb starting index of subvector
   \param ub ending index of subvector
   \return dvector contining a shallow copy of calling instance of dvector
    with valid subscripts from lb to ub.
   */
   dvector sub(int lb, int ub)
   {
      return predvector(this, lb, ub);
   }
   /** Get subvector.
   \param lb starting index of subvector
   \param ub ending index of subvector
   \return dvector contining a shallow copy of calling instance of dvector
    with valid subscripts from lb to ub.
   */
   dvector operator () (int lb, int ub)
   {
      return predvector(this, lb, ub);
   }

   dvector(const predvector & pd);

   void fill_randpoisson(double lambda, const random_number_generator & rng);
   void fill_randnegbinomial(double lambda, double tau,
     const random_number_generator & rng);
   void shallow_copy(const dvector &);

   friend class banded_symmetric_dvar_matrix;
   friend class banded_lower_triangular_dvar_matrix;
   friend class banded_symmetric_dmatrix;
   friend class banded_lower_triangular_dmatrix;

   void allocate(int ncl, int ncu);
   void allocate(const dvector & dv);
   void allocatec(const dvector & dv);
   void allocate(const dvar_vector &);
   void allocate(const char *);
   void allocate(void);
   void deallocate(void);
   void safe_deallocate(void);
   void safe_allocate(int, int);

   const double *address() const
   {
      return v;
   }
   double *&get_v(void)
   {
      return (v);
   }
   double &elem(int i)
   {
      return (v[i]);
   }
   double *initpointer(void)
   {
      return (v + indexmin());
   }
   const double *initpointer(void) const
   {
      return (v + indexmin());
   }
   double *get_v(void) const
   {
      return v;
   }
   const double &elem(int i) const
   {
      return v[i];
   }

   void fill(const char *s);
   void fill_randu_ni(long int &n);
   void fill_randn_ni(long int &n);
   void fill_randbi_ni(long int &n, double);

   void fill_randu(long int &n);
   void fill_randn(long int &n);
   void fill_randbi(long int &n, double);


   void fill_randbi(double p, const random_number_generator & rng);
   void fill_randu(const random_number_generator & rng);
   void fill_randn(const random_number_generator & rng);
   void fill_randcau(const random_number_generator & rng);

   void fill_seqadd(double, double);
   void fill_multinomial(const int &seed, const dvector & p);
   void fill_multinomial(const random_number_generator& rng, const dvector& p);
   void initialize(void);

   // returns the minimum allowable index
   int &testmin()
   {
      return shape->index_min;
   }

   // returns the minimum allowable index
   int &testmax()
   {
      return shape->index_max;
   }

   /// Get minimum valid index.
   int indexmin() const
   {
      return index_min;
   }

   /// Get maximum valid index.
   int indexmax() const
   {
      return index_max;
   }

   /// Get number of elements in array.
   int size() const
   {
      return (index_max - index_min + 1);
   }

   dvector & shift(int min);

   dvector(const dvar_vector_position & dvp, const kkludge_object &);

   dvector(const ad_integer &, const index_type &);
   void allocate(const ad_integer &, const index_type &);
   dvector(void);
   dvector(const dvector &);
   //dvector(const dvector&,int lb,int ub);

   dvector(const ivector &);

   dvector(const lvector &);

   dvector(const char *);

   dvector(int ncl, int ncu);
   // makes an array [ncl..ncu]

   dvector(unsigned int sz, double *x);

   dvector(char *filename, const int &column);

   //operator double* () { return v;}

   ~dvector();

   void save_dvector_position(void) const;
   void save_dvector_derivatives(const dvar_vector_position & pos) const;
   void save_dvector_derivatives_na(const dvar_vector_position & pos)
      const;
   void save_dvector_derivatives(void) const;
   void save_dvector_value(void) const;

   //dvector operator()(int,int);
   dvector operator() (const lvector &);
   dvector operator() (const ivector & u);

   dvector & operator+=(const dvector & v1);
   dvector & operator-=(const dvector & v1);
   dvector & operator +=(double v1);
   dvector & operator /=(double v1);
   dvector & operator *=(double v1);
   dvector & operator -=(double v1);

   void read_from(const uistream &);

   friend class sdmatrix;
   friend double norm(const dvector &);
   friend double norm2(const dvector &);
   friend double sumsq(const dvector &);
   friend class dvar_vector;
   friend class dmatrix;
   friend class d3_array;
   friend char *fform(const char *, const dvector &);

   void write_on(const ostream &) const;
   void write_on(const uostream &) const;
   void read_from(const istream &);
   friend double operator*(const dvector &, const dvector &);

   friend dvariable operator*(const dvector &, const dvar_vector &);

   friend dvariable operator*(const dvar_vector &, const dvector &);

   friend dvar_vector operator*(const prevariable &, const dvector &);

   friend dvector operator*(double, const dvector &);

   friend dvector operator+(const dvector &, const dvector &);

   friend dvector elem_prod(const dvector &, const dvector &);

   friend dvector first_difference(const dvector &);
   friend dvector second_difference(const dvector &);

   friend dvector elem_div(const dvector &, const dvector &);

   friend dvar_vector elem_prod(const dvector &, const dvar_vector &);

   friend dvar_vector elem_div(const dvector &, const dvar_vector &);

   friend dvar_vector elem_prod(const dvar_vector &, const dvector &);

   friend dvar_vector elem_div(const dvar_vector &, const dvector &);

   friend dvar_vector operator+(const dvar_vector &, const dvector &);

   friend dvar_vector operator+(const dvector &, const dvar_vector &);

   friend dvector operator-(const dvector &, const dvector &);

   friend dvar_vector operator-(const dvar_vector &, const dvector &);

   friend dvar_vector operator-(const dvector &, const dvar_vector &);

   friend dvector operator*(const dvector & x, const dmatrix & m);

   friend dvector operator*(const dmatrix & x, const dvector & m);

   friend dvar_vector operator*(const dvector & x, const dvar_matrix & m);

   friend dvar_vector operator*(const dvar_matrix & x, const dvector & m);

   double& operator[](int i);
   double& operator()(int i);
   const double& operator[](int i) const;
   const double& operator()(int i) const;

   dvector & operator=(const dvector & t);

   dvector & operator =(double x);

   friend dvector exp(const dvector &);

   friend dvector log(const dvector &);

   friend dvector fabs(const dvector &);

   friend double max(const dvector &);

   friend double min(const dvector &);
};

#ifdef OPT_LIB
inline double& dvector::operator[](int i)
{
  return *(v + i);
}
inline double& dvector::operator()(int i)
{
  return *(v + i);
}
inline const double& dvector::operator[](int i) const
{
  return *(v + i);
}
inline const double& dvector::operator()(int i) const
{
  return *(v + i);
}
#endif

#endif
