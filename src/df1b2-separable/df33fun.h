/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California
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




#if !defined(__DF33FUN__)
#  define __DF33FUN__
class df1b2variable;

  class df3_three_variable
  {
    double v[20];
  public:
    static df1b2variable * ind_var[];
    static int num_ind_var;
    static int num_local_ind_var;
    double * get_u(void) const {return (double*) (&(v[0]));}
    double * get_u_x(void)const {return (double*) (&(v[1]));}
    double * get_u_y(void)const {return (double*) (&(v[2]));}

    double * get_u_z(void)const {return (double*) (&(v[3]));}

    double * get_u_xx(void)const {return (double*) (&(v[4]));}

    double * get_u_xy(void)const {return (double*) (&(v[5]));}
    double * get_u_xz(void)const {return (double*) (&(v[6]));}

    double * get_u_yy(void)const {return (double*) (&(v[7]));}

    double * get_u_yz(void)const {return (double*) (&(v[8]));}
    double * get_u_zz(void)const {return (double*) (&(v[9]));}

    double * get_u_xxx(void)const {return (double*) (&(v[10]));}

    double * get_u_xxy(void)const {return (double*) (&(v[11]));}

    double * get_u_xxz(void)const {return (double*) (&(v[12]));}

    double * get_u_xyy(void)const {return (double*) (&(v[13]));}

    double * get_u_xyz(void)const {return (double*) (&(v[14]));}
    double * get_u_xzz(void)const {return (double*) (&(v[15]));}

    double * get_u_yyy(void)const {return (double*) (&(v[16]));}
    double * get_u_yyz(void)const {return (double*) (&(v[17]));}
    double * get_u_yzz(void)const {return (double*) (&(v[18]));}

    double * get_u_zzz(void)const {return (double*) (&(v[19]));}

    df3_three_variable& operator = (const df3_three_variable& v);
    df3_three_variable& operator = (double v);
    df3_three_variable& operator += (const df3_three_variable& v);
    df3_three_variable& operator *= (const df3_three_variable& v);
    df3_three_variable& operator += (double v);
    df3_three_variable& operator -= (const df3_three_variable& v);
    df3_three_variable& operator /= (const df3_three_variable& v);
    df3_three_variable(void);
    df3_three_variable(const df3_three_variable& );
  };

  inline  double value(const df3_three_variable& x) { return double(*x.get_u()); }

  class init_df3_three_variable : public df3_three_variable
  {
  public:
    init_df3_three_variable(const df1b2variable& );
    init_df3_three_variable(double );
    ~init_df3_three_variable();
  };



  class df3_three_vector
  {
    int index_min;
    int index_max;
    vector_shapex * shape;
    df3_three_variable * v;
  public:
    int indexmin(void) const { return int(index_min); }
    int indexmax(void) const { return int(index_max); }
    df3_three_vector(int min,int max);
    df3_three_vector(void);
    void allocate(void);
    void allocate(int min,int max);
    df3_three_variable& operator () (int i) const 
    { 
      return (df3_three_variable&) (*(v+i));
    }
    df3_three_variable& operator [] (int i) const 
    { 
      return (df3_three_variable&) (*(v+i));
    }
    void initialize(void);
    void deallocate(void);
    ~df3_three_vector();
    df3_three_vector(const df3_three_vector& m2);
  };



 dvector value(const df3_three_vector& v);
   
 dvector first_derivatives(const df3_three_vector& v);

 dvector second_derivatives(const df3_three_vector& v);
   
 dvector third_derivatives(const df3_three_vector& v);
    
  class df3_three_matrix
  {
    int index_min;
    int index_max;
    mat_shapex * shape;
    df3_three_vector * v;
  public:
    int indexmin(void) const { return int(index_min); }
    int indexmax(void) const { return int(index_max); }
    df3_three_matrix(int rmin,int rmax,int cmin,int cmax);
    df3_three_vector& operator () (int i) const 
    { 
      return (df3_three_vector&) *(v+i); 
    }
    df3_three_vector& operator [] (int i) const 
    { 
      return (df3_three_vector&) *(v+i); 
    }
    df3_three_variable& operator () (int i,int j) const 
    { 
      return (df3_three_variable&) (*(v+i))(j); 
    }
    void initialize(void);
    //df3_three_variable& operator () (int i,int j) const { return *((v+i)->(v+j)); }
    void deallocate(void);
    ~df3_three_matrix();
    df3_three_matrix(const df3_three_matrix& m2);
  };

 dmatrix value(const df3_three_matrix& v);
   
 dmatrix first_derivatives(const df3_three_matrix& v);
 dmatrix second_derivatives(const df3_three_matrix& v);
 dmatrix third_derivatives(const df3_three_matrix& v);
    
/*
  df3_three_variable operator F(const df3_three_variable& x)
  {
    df3_three_variable z;

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

  df3_three_variable sin(const df3_three_variable& x);
  df3_three_variable sqrt(const df3_three_variable& x);
  df3_three_variable atan(const df3_three_variable& x);
  df3_three_variable cos(const df3_three_variable& x);
  df3_three_variable tan(const df3_three_variable& x);
  df3_three_variable log(const df3_three_variable& x);
  df3_three_variable square(const df3_three_variable& x);
  df3_three_variable cube(const df3_three_variable& x);
  df3_three_variable pow(const df3_three_variable& x,
    const df3_three_variable& y);

  df3_three_variable sqrt(const df3_three_variable& x);
  df3_three_variable exp(const df3_three_variable& x);
  df3_three_variable inv(const df3_three_variable& x);
  df3_three_variable operator * (const df3_three_variable& x,
    const df3_three_variable& y);
  df3_three_variable operator * (double x,
    const df3_three_variable& y);
  df3_three_variable operator * (const df3_three_variable& x,
    double y);
  df3_three_variable operator / (const df3_three_variable& x,
    const df3_three_variable& y);

  df3_three_variable operator / (const double x,const df3_three_variable& y);

  df3_three_variable operator / (const df3_three_variable& x,
    const double y);

  df3_three_variable operator + (const double x,
    const df3_three_variable& y);

  df3_three_variable operator + (const df3_three_variable& x,
    const double y);

  df3_three_variable operator + (const df3_three_variable& x,
    const df3_three_variable& y);
  df3_three_variable operator - (double x,const df3_three_variable& y);
  df3_three_variable operator - (const df3_three_variable& x,double y);

  df3_three_variable operator - (const df3_three_variable& x,
    const df3_three_variable& y);
  df3_three_variable operator - (const df3_three_variable& x,
    const df3_three_variable& y);
  df3_three_variable operator / (const df3_three_variable& x,
    const df3_three_variable& y);
  df3_three_variable operator * (const df3_three_variable& x,
    const df3_three_variable& y);


  df3_three_variable operator - (const df3_three_variable& v);
  df3_three_matrix choleski_decomp(const df3_three_matrix& MM);
 
  df3_three_variable cumd_gamma(const df3_three_variable& x,
    const df3_three_variable& a);


  df3_three_variable gammln(const df3_three_variable& xx);
#endif  // __DF32FUN__

