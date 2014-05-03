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

#ifndef __ADMB_PREVARIABLE_H__
#define __ADMB_PREVARIABLE_H__

class prevariable_position;

/**
  Base class for dvariable.
  Principle role is to avoid calling a descructor when a pevariable or dvariable
  object is passed on the stack.
  (There is no destructor, ~prevariable().)
  \ingroup BAD
 */
class prevariable
{
 protected:
#ifndef __SUN__
   prevariable(void)
   {
   }
#endif
#ifndef __NDPX__
   prevariable(double_and_int * u)
   {
      v = u;
   }
#endif

 public:
   double_and_int* v; ///< pointer to the data
   friend class dvar_vector_iterator;
   friend class dvar_vector;
   friend class dvar_matrix;
   friend class dvar3_array;
   //shclass sc;
   friend class indvar_offset_list;
   friend class gradient_structure;
   friend double_and_int *gradnew();
   friend void make_indvar_list(int, dvariable *);

   friend class banded_symmetric_dvar_matrix;
   friend class banded_lower_triangular_dvar_matrix;
   friend double &value(const prevariable & v1);

   friend double *address(const prevariable & v1);

   //void gradfree(dlink * v)

   friend prevariable & operator*(const prevariable& v1, const prevariable& v2);

   friend prevariable & operator*(double v1, const prevariable & v2);

   friend prevariable & operator*(const prevariable & v1, double v2);

   friend prevariable & operator/(const prevariable& t1, const prevariable& t2);

   friend prevariable & operator/(double t1, const prevariable & t2);

   friend prevariable & operator/(const prevariable & t1, double t2);

   friend prevariable & sin(const prevariable & t1);

   friend prevariable & fabs(const prevariable & t1);
   friend prevariable & sigmoid(const prevariable & t1);

   //"smoothed absolute value function
   friend prevariable & sfabs(const prevariable & t1);

   friend prevariable & sqrt(const prevariable & t1);
   friend prevariable & sqr(const prevariable & t1);

   friend prevariable & exp(const prevariable & t1);

   friend prevariable & atan(const prevariable & t1);

   friend prevariable & tan(const prevariable & t1);
   friend prevariable & tanh(const prevariable & t1);

   friend prevariable & atan2(const prevariable & t1,
     const prevariable & t2);
   friend prevariable & atan2(const prevariable & t1, double t2);
   friend prevariable & atan2(double t1, const prevariable & t2);

   friend prevariable & acos(const prevariable & t1);

   friend prevariable & asin(const prevariable & t1);

   friend prevariable & cos(const prevariable & t1);
   friend prevariable & sinh(const prevariable & t1);
   friend prevariable & cosh(const prevariable & t1);

   friend prevariable & log(const prevariable & t1);
   friend prevariable & log10(const prevariable & t1);

   friend prevariable & ldexp(const prevariable &, const int &);


 public:
   void save_prevariable_position(void) const;
   prevariable_position restore_prevariable_position(void);
   void save_prevariable_value(void) const;
   double restore_prevariable_value(void);
   double restore_prevariable_derivative(void);


   inline double *xadr()
   {
      return (&(v->x));
   }
   inline double &xval()
   {
      return ((v->x));
   }

   inline double_and_int *&get_v()
   {
      return v;
   }
   inline double_and_int *get_v() const
   {
      return v;
   }

   prevariable & operator=(const prevariable &);
   prevariable & operator=(double);
#if (__BORLANDC__  >= 0x0540)
   prevariable & operator=(const prevariable &) const;
   prevariable & operator=(double) const;
#endif

   int operator==(const prevariable & v1) const;
   int operator<=(const prevariable & v1) const;
   int operator>=(const prevariable & v1) const;
   int operator>(const prevariable & v1) const;
   int operator<(const prevariable & v1) const;
   int operator!=(const prevariable & v1) const;

   int operator==(double v1) const;
   int operator<=(double v1) const;
   int operator>=(double v1) const;
   int operator>(double v1) const;
   int operator<(double v1) const;
   int operator!=(double v1) const;
#if defined(USE_DDOUBLE)
   int operator==(int v1) const;
   int operator<=(int v1) const;
   int operator>=(int v1) const;
   int operator>(int v1) const;
   int operator<(int v1) const;
   int operator!=(int v1) const;
#endif

 public:
#ifdef __SUN__
   prevariable(void)
   {
   }
#endif
#ifdef __NDPX__
   prevariable(double_and_int * u)
   {
      v = u;
   }
#endif

   void initialize(void);

   friend char *fform(const char *, const prevariable &);

   void operator+=(const prevariable & t1);
   void operator +=(double t1);

   void operator-=(const prevariable & t1);
   void operator -=(double t1);

   void operator/=(const prevariable & v1);
   void operator /=(double v1);

   void operator*=(const prevariable & v1);
   void operator *=(double v1);

   friend prevariable& operator+(const prevariable& v1, const prevariable& v2);

   friend prevariable & operator+(double v1, const prevariable & v2);

   friend prevariable & operator+(const prevariable & v1, double v2);

   friend prevariable & operator-(const prevariable & v1);

   friend prevariable & operator-(const prevariable& v1, const prevariable& v2);

   friend prevariable & operator-(double v1, const prevariable & v2);

   friend prevariable & operator-(const prevariable & v1, double v2);

   friend prevariable & pow(const prevariable & t1, const prevariable & t2);

   friend prevariable & pow(const prevariable & t1, double t2);

   friend prevariable & pow(double t1, const prevariable & t2);
};
inline double &value(const prevariable & v1)
{
   return v1.v->x;
}
inline double *address(const prevariable & v1)
{
   return (&(v1.v->x));
}
prevariable & operator<<(const prevariable & v1, const prevariable & v2);
#endif
