/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009 ADMB Foundation
 *
 */
#if !defined(__DF12FUN__)
#  define __DF12FUN__
#ifndef FVAR_HPP
#  include <fvar.hpp>
#endif
//class df1b2variable;

  class df1_three_variable
  {
    double v[4];
  public:
    static prevariable * ind_var[];
    static int num_ind_var;
    double * get_u(void) const {return (double*) (&(v[0]));}
    double * get_u_x(void)const {return (double*) (&(v[1]));}
    double * get_u_y(void)const {return (double*) (&(v[2]));}
    double * get_u_z(void)const {return (double*) (&(v[3]));}
    df1_three_variable& operator = (const df1_three_variable& v);
    df1_three_variable& operator = (double v);
    df1_three_variable& operator += (const df1_three_variable& v);
    df1_three_variable& operator *= (const df1_three_variable& v);
    df1_three_variable& operator *= (double v);
    df1_three_variable& operator += (double v);
    df1_three_variable& operator -= (const df1_three_variable& v);
    df1_three_variable& operator -= (double v);
    df1_three_variable& operator /= (const df1_three_variable& v);
    df1_three_variable& my_diveq (const df1_three_variable& v);
    df1_three_variable& operator /= (double v);
    df1_three_variable(void);
    df1_three_variable(const df1_three_variable& );
    void initialize(void);
  };

  inline  double value(const df1_three_variable& x) { return double(*x.get_u()); }

  class init_df1_three_variable : public df1_three_variable
  {
  public:
    ~init_df1_three_variable();
    void deallocate(void);
    init_df1_three_variable(const prevariable& );
    init_df1_three_variable(double );
  };



  class df1_three_vector
  {
    int index_min;
    int index_max;
    vector_shapex * shape;
    df1_three_variable * v;
  public:
    int indexmin(void) const { return int(index_min); }
    int indexmax(void) const { return int(index_max); }
    df1_three_vector(int min,int max);
    df1_three_vector(void);
    void allocate(void);
    void allocate(int min,int max);
    df1_three_variable& operator () (int i) const 
    { 
      return (df1_three_variable&) (*(v+i));
    }
    df1_three_variable& operator [] (int i) const 
    { 
      return (df1_three_variable&) (*(v+i));
    }
    void initialize(void);
    void deallocate(void);
    ~df1_three_vector();
    df1_three_vector(const df1_three_vector& m2);
  };



 dvector value(const df1_three_vector& v);
 dvector first_derivatives(const df1_three_vector& v);

    
  class df1_three_matrix
  {
    int index_min;
    int index_max;
    mat_shapex * shape;
    df1_three_vector * v;
  public:
    int indexmin(void) const { return int(index_min); }
    int indexmax(void) const { return int(index_max); }
    df1_three_matrix(int rmin,int rmax,int cmin,int cmax);
    df1_three_vector& operator () (int i) const 
    { 
      return (df1_three_vector&) *(v+i); 
    }
    df1_three_vector& operator [] (int i) const 
    { 
      return (df1_three_vector&) *(v+i); 
    }
    df1_three_variable& operator () (int i,int j) const 
    { 
      return (df1_three_variable&) (*(v+i))(j); 
    }
    void initialize(void);
    //df1_three_variable& operator () (int i,int j) const { return *((v+i)->(v+j)); }
    void deallocate(void);
    ~df1_three_matrix();
    df1_three_matrix(const df1_three_matrix& m2);
  };

 dmatrix value(const df1_three_matrix& v);
   
 dmatrix first_derivatives(const df1_three_matrix& v);
 dmatrix second_derivatives(const df1_three_matrix& v);
 dmatrix third_derivatives(const df1_three_matrix& v);
    
/*
  df1_three_variable operator F(const df1_three_variable& x)
  {
    df1_three_variable z;

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

  df1_three_variable sin(const df1_three_variable& x);
  df1_three_variable fabs(const df1_three_variable& x);
  df1_three_variable sqrt(const df1_three_variable& x);
  df1_three_variable atan(const df1_three_variable& x);
  df1_three_variable cos(const df1_three_variable& x);
  df1_three_variable tan(const df1_three_variable& x);
  df1_three_variable log(const df1_three_variable& x);
  df1_three_variable square(const df1_three_variable& x);
  df1_three_variable cube(const df1_three_variable& x);
  df1_three_variable pow(const df1_three_variable& x,
    const df1_three_variable& y);

  df1_three_variable sqrt(const df1_three_variable& x);
  df1_three_variable exp(const df1_three_variable& x);
  df1_three_variable inv(const df1_three_variable& x);
  df1_three_variable operator * (const df1_three_variable& x,
    const df1_three_variable& y);
  df1_three_variable operator * (double x,
    const df1_three_variable& y);
  df1_three_variable operator * (const df1_three_variable& x,
    double y);
  df1_three_variable operator / (const df1_three_variable& x,
    const df1_three_variable& y);

  df1_three_variable operator / (const double x,const df1_three_variable& y);

  df1_three_variable operator / (const df1_three_variable& x,
    const double y);

  df1_three_variable operator + (const double x,
    const df1_three_variable& y);

  df1_three_variable operator + (const df1_three_variable& x,
    const double y);

  df1_three_variable operator + (const df1_three_variable& x,
    const df1_three_variable& y);
  df1_three_variable operator - (double x,const df1_three_variable& y);
  df1_three_variable operator - (const df1_three_variable& x,double y);

  df1_three_variable operator - (const df1_three_variable& x,
    const df1_three_variable& y);
  df1_three_variable operator - (const df1_three_variable& x,
    const df1_three_variable& y);
  df1_three_variable operator / (const df1_three_variable& x,
    const df1_three_variable& y);
  df1_three_variable operator * (const df1_three_variable& x,
    const df1_three_variable& y);


  df1_three_variable operator - (const df1_three_variable& v);
  df1_three_matrix choleski_decomp(const df1_three_matrix& MM);
 
  df1_three_variable cumd_gamma(const df1_three_variable& x,
    const df1_three_variable& a);


  df1_three_variable gammln(const df1_three_variable& xx);

  int operator <(const df1_three_variable & x, double n);
  int operator >(const df1_three_variable & x, const df1_three_variable & n);
  int operator <(const df1_three_variable & x, const df1_three_variable & n);
  int operator ==(double x, const df1_three_variable & n);
  int operator ==(const df1_three_variable & x, double n);
  int operator ==(const df1_three_variable & x, const df1_three_variable & n);
  int operator >=(const df1_three_variable & x, double n);
  int operator >(const df1_three_variable & x, double n);

#endif  // __DF12FUN__
