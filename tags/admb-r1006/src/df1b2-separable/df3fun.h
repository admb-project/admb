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


#if !defined(__DF3FUN__)
#  define __DF3FUN__

  class df3_one_variable
  {
    double v[4];
  public:
    static df1b2variable * ind_var;
    double * get_u(void) const {return (double*) (&(v[0]));}
    double * get_udot(void)const {return (double*) (&(v[1]));}
    double * get_udot2(void) const {return (double*) (&(v[2]));}
    double * get_udot3(void) const {return (double*) (&(v[3]));}
    df3_one_variable& operator = (const df3_one_variable& v);
    df3_one_variable& operator = (double v);
    df3_one_variable& operator += (const df3_one_variable& v);
    df3_one_variable& operator -= (const df3_one_variable& v);
    df3_one_variable& operator -= (double);
    df3_one_variable& operator *= (const df3_one_variable& v);
    df3_one_variable& operator /= (const df3_one_variable& v);
    df3_one_variable(void);
    df3_one_variable(const df3_one_variable& );
  };

  inline  double value(const df3_one_variable& x) { return double(*x.get_u()); }

  class init_df3_one_variable : public df3_one_variable
  {
  public:
    init_df3_one_variable(const df1b2variable& );
    init_df3_one_variable(double );
  };



  class df3_one_vector
  {
    int index_min;
    int index_max;
    vector_shapex * shape;
    df3_one_variable * v;
  public:
    int indexmin(void) const { return int(index_min); }
    int indexmax(void) const { return int(index_max); }
    df3_one_vector(int min,int max);
    df3_one_vector(void);
    void allocate(void);
    void allocate(int min,int max);
    df3_one_variable& operator () (int i) const 
    { 
      return (df3_one_variable&) (*(v+i));
    }
    df3_one_variable& operator [] (int i) const 
    { 
      return (df3_one_variable&) (*(v+i));
    }
    void initialize(void);
    void deallocate(void);
    ~df3_one_vector();
    df3_one_vector(const df3_one_vector& m2);
  };



 dvector value(const df3_one_vector& v);
   
 dvector first_derivatives(const df3_one_vector& v);

 dvector second_derivatives(const df3_one_vector& v);
   
 dvector third_derivatives(const df3_one_vector& v);
    
  class df3_one_matrix
  {
    int index_min;
    int index_max;
    mat_shapex * shape;
    df3_one_vector * v;
  public:
    int indexmin(void) const { return int(index_min); }
    int indexmax(void) const { return int(index_max); }
    df3_one_matrix(int rmin,int rmax,int cmin,int cmax);
    df3_one_vector& operator () (int i) const 
    { 
      return (df3_one_vector&) *(v+i); 
    }
    df3_one_vector& operator [] (int i) const 
    { 
      return (df3_one_vector&) *(v+i); 
    }
    df3_one_variable& operator () (int i,int j) const 
    { 
      return (df3_one_variable&) (*(v+i))(j); 
    }
    void initialize(void);
    //df3_one_variable& operator () (int i,int j) const { return *((v+i)->(v+j)); }
    void deallocate(void);
    ~df3_one_matrix();
    df3_one_matrix(const df3_one_matrix& m2);
  };

 dmatrix value(const df3_one_matrix& v);
   
 dmatrix first_derivatives(const df3_one_matrix& v);
 dmatrix second_derivatives(const df3_one_matrix& v);
 dmatrix third_derivatives(const df3_one_matrix& v);
    
/*
  df3_one_variable operator F(const df3_one_variable& x)
  {
    df3_one_variable z;

    *z.get_u() = ::F(*x.get_u());

    *z.get_udot() = ::D1F(*x.get_u())* *x.get_udot();

    *z.get_udot2() = ::D2F(*x.get_u())* square(*x.get_udot())
                   + ::D1F(*x.get_u())* *x.get_udot2();

    *z.get_udot3() = ::D3F(*x.get_u()) * cube(*x.get_udot())
                   + 3.0 * ::D2F(*x.get_u()) * *x.get_udot() * *x.get_udot2()
                   + ::D1F(*x.get_u()) * *x.get_udot3();
    return z;
  }

*/

  df3_one_variable sqrt(const df3_one_variable& x);
  df3_one_variable exp(const df3_one_variable& x);
  df3_one_variable log(const df3_one_variable& x);
  df3_one_variable inv(const df3_one_variable& x);
  df3_one_variable operator * (const df3_one_variable& x,
    const df3_one_variable& y);
  df3_one_variable operator * (double x,
    const df3_one_variable& y);
  df3_one_variable operator * (const df3_one_variable& x,
    double y);
  df3_one_variable operator / (const df3_one_variable& x,
    const df3_one_variable& y);

  df3_one_variable operator / (const double x,const df3_one_variable& y);

  df3_one_variable operator / (const df3_one_variable& x,
    const double y);

  df3_one_variable operator + (const double x,
    const df3_one_variable& y);

  df3_one_variable operator + (const df3_one_variable& x,
    const double y);

  df3_one_variable operator + (const df3_one_variable& x,
    const df3_one_variable& y);

  df3_one_variable operator - (const df3_one_variable& x,
    double);
  df3_one_variable operator - (const df3_one_variable& x,
    const df3_one_variable& y);
  df3_one_variable operator - (const df3_one_variable& x,
    const df3_one_variable& y);
  df3_one_variable operator / (const df3_one_variable& x,
    const df3_one_variable& y);
  df3_one_variable operator * (const df3_one_variable& x,
    const df3_one_variable& y);


  df3_one_variable operator - (const df3_one_variable& v);
  df3_one_matrix choleski_decomp(const df3_one_matrix& MM);
 
#endif  // __DF3FUN__

