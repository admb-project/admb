/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California
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

#if !defined(__DF11FUN__)
#  define __DF11FUN__
#include <fvar.hpp>
//class df1b2variable;

  class df1_one_variable
  {
    double v[2];
  public:
    static prevariable * ind_var[];
    static int num_ind_var;
    double * get_u(void) const {return (double*) (&(v[0]));}
    double * get_u_x(void)const {return (double*) (&(v[1]));}
    df1_one_variable& operator = (const df1_one_variable& v);
    df1_one_variable& operator = (double v);
    df1_one_variable& operator += (const df1_one_variable& v);
    df1_one_variable& operator *= (const df1_one_variable& v);
    df1_one_variable& operator += (double v);
    df1_one_variable& operator -= (const df1_one_variable& v);
    df1_one_variable& operator -= (double v);
    df1_one_variable& operator /= (const df1_one_variable& v);
    df1_one_variable(void);
    df1_one_variable(const df1_one_variable& );
  };

  inline  double value(const df1_one_variable& x) { return double(*x.get_u()); }

  class init_df1_one_variable : public df1_one_variable
  {
  public:
    ~init_df1_one_variable();
    void deallocate(void);
    init_df1_one_variable(const prevariable& );
    init_df1_one_variable(double );
  };



  class df1_one_vector
  {
    int index_min;
    int index_max;
    vector_shapex * shape;
    df1_one_variable * v;
  public:
    int indexmin(void) const { return int(index_min); }
    int indexmax(void) const { return int(index_max); }
    df1_one_vector(int min,int max);
    df1_one_vector(void);
    void df1_one_vector::allocate(void);
    void allocate(int min,int max);
    df1_one_variable& operator () (int i) const 
    { 
      return (df1_one_variable&) (*(v+i));
    }
    df1_one_variable& operator [] (int i) const 
    { 
      return (df1_one_variable&) (*(v+i));
    }
    void initialize(void);
    void deallocate(void);
    ~df1_one_vector();
    df1_one_vector(const df1_one_vector& m2);
  };



 dvector value(const df1_one_vector& v);
 dvector first_derivatives(const df1_one_vector& v);

    
  class df1_one_matrix
  {
    int index_min;
    int index_max;
    mat_shapex * shape;
    df1_one_vector * v;
  public:
    int indexmin(void) const { return int(index_min); }
    int indexmax(void) const { return int(index_max); }
    df1_one_matrix(int rmin,int rmax,int cmin,int cmax);
    df1_one_vector& operator () (int i) const 
    { 
      return (df1_one_vector&) *(v+i); 
    }
    df1_one_vector& operator [] (int i) const 
    { 
      return (df1_one_vector&) *(v+i); 
    }
    df1_one_variable& operator () (int i,int j) const 
    { 
      return (df1_one_variable&) (*(v+i))(j); 
    }
    void initialize(void);
    //df1_one_variable& operator () (int i,int j) const { return *((v+i)->(v+j)); }
    void deallocate(void);
    ~df1_one_matrix();
    df1_one_matrix::df1_one_matrix(const df1_one_matrix& m2);
  };

 dmatrix value(const df1_one_matrix& v);
   
 dmatrix first_derivatives(const df1_one_matrix& v);
 dmatrix second_derivatives(const df1_one_matrix& v);
 dmatrix third_derivatives(const df1_one_matrix& v);
    

  df1_one_variable sin(const df1_one_variable& x);
  df1_one_variable sqrt(const df1_one_variable& x);
  df1_one_variable atan(const df1_one_variable& x);
  df1_one_variable cos(const df1_one_variable& x);
  df1_one_variable tan(const df1_one_variable& x);
  df1_one_variable log(const df1_one_variable& x);
  df1_one_variable square(const df1_one_variable& x);
  df1_one_variable cube(const df1_one_variable& x);
  df1_one_variable pow(const df1_one_variable& x,
    const df1_one_variable& y);

  df1_one_variable sqrt(const df1_one_variable& x);
  df1_one_variable exp(const df1_one_variable& x);
  df1_one_variable inv(const df1_one_variable& x);
  df1_one_variable operator * (const df1_one_variable& x,
    const df1_one_variable& y);
  df1_one_variable operator * (double x,
    const df1_one_variable& y);
  df1_one_variable operator * (const df1_one_variable& x,
    double y);
  df1_one_variable operator / (const df1_one_variable& x,
    const df1_one_variable& y);

  df1_one_variable operator / (const double x,const df1_one_variable& y);

  df1_one_variable operator / (const df1_one_variable& x,
    const double y);

  df1_one_variable operator + (const double x,
    const df1_one_variable& y);

  df1_one_variable operator + (const df1_one_variable& x,
    const double y);

  df1_one_variable operator + (const df1_one_variable& x,
    const df1_one_variable& y);
  df1_one_variable operator - (double x,const df1_one_variable& y);
  df1_one_variable operator - (const df1_one_variable& x,double y);

  df1_one_variable operator - (const df1_one_variable& x,
    const df1_one_variable& y);
  df1_one_variable operator - (const df1_one_variable& x,
    const df1_one_variable& y);
  df1_one_variable operator / (const df1_one_variable& x,
    const df1_one_variable& y);
  df1_one_variable operator * (const df1_one_variable& x,
    const df1_one_variable& y);


  df1_one_variable operator - (const df1_one_variable& v);
  df1_one_matrix choleski_decomp(const df1_one_matrix& MM);
 
  df1_one_variable cumd_gamma(const df1_one_variable& x,
    const df1_one_variable& a);


  df1_one_variable gammln(const df1_one_variable& xx);
#endif  // __DF11FUN__

