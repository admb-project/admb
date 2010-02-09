

#if !defined(__DF12FUN__)
#  define __DF12FUN__
#ifndef FVAR_HPP
#  include <fvar.hpp>
#endif
//class df1b2variable;

  class df1_two_variable
  {
    double v[3];
  public:
    static prevariable * ind_var[];
    static int num_ind_var;
    double * get_u(void) const {return (double*) (&(v[0]));}
    double * get_u_x(void)const {return (double*) (&(v[1]));}
    double * get_u_y(void)const {return (double*) (&(v[2]));}
    df1_two_variable& operator = (const df1_two_variable& v);
    df1_two_variable& operator = (double v);
    df1_two_variable& operator += (const df1_two_variable& v);
    df1_two_variable& operator *= (const df1_two_variable& v);
    df1_two_variable& operator *= (double v);
    df1_two_variable& operator += (double v);
    df1_two_variable& operator -= (const df1_two_variable& v);
    df1_two_variable& operator -= (double v);
    df1_two_variable& operator /= (const df1_two_variable& v);
    df1_two_variable& my_diveq (const df1_two_variable& v);
    df1_two_variable& operator /= (double v);
    df1_two_variable(void);
    df1_two_variable(const df1_two_variable& );
  };

  inline  double value(const df1_two_variable& x) { return double(*x.get_u()); }

  class init_df1_two_variable : public df1_two_variable
  {
  public:
    ~init_df1_two_variable();
    void deallocate(void);
    init_df1_two_variable(const prevariable& );
    init_df1_two_variable(double );
  };



  class df1_two_vector
  {
    int index_min;
    int index_max;
    vector_shapex * shape;
    df1_two_variable * v;
  public:
    int indexmin(void) const { return int(index_min); }
    int indexmax(void) const { return int(index_max); }
    df1_two_vector(int min,int max);
    df1_two_vector(void);
    void df1_two_vector::allocate(void);
    void allocate(int min,int max);
    df1_two_variable& operator () (int i) const 
    { 
      return (df1_two_variable&) (*(v+i));
    }
    df1_two_variable& operator [] (int i) const 
    { 
      return (df1_two_variable&) (*(v+i));
    }
    void initialize(void);
    void deallocate(void);
    ~df1_two_vector();
    df1_two_vector(const df1_two_vector& m2);
  };



 dvector value(const df1_two_vector& v);
 dvector first_derivatives(const df1_two_vector& v);

    
  class df1_two_matrix
  {
    int index_min;
    int index_max;
    mat_shapex * shape;
    df1_two_vector * v;
  public:
    int indexmin(void) const { return int(index_min); }
    int indexmax(void) const { return int(index_max); }
    df1_two_matrix(int rmin,int rmax,int cmin,int cmax);
    df1_two_vector& operator () (int i) const 
    { 
      return (df1_two_vector&) *(v+i); 
    }
    df1_two_vector& operator [] (int i) const 
    { 
      return (df1_two_vector&) *(v+i); 
    }
    df1_two_variable& operator () (int i,int j) const 
    { 
      return (df1_two_variable&) (*(v+i))(j); 
    }
    void initialize(void);
    //df1_two_variable& operator () (int i,int j) const { return *((v+i)->(v+j)); }
    void deallocate(void);
    ~df1_two_matrix();
    df1_two_matrix::df1_two_matrix(const df1_two_matrix& m2);
  };

 dmatrix value(const df1_two_matrix& v);
   
 dmatrix first_derivatives(const df1_two_matrix& v);
 dmatrix second_derivatives(const df1_two_matrix& v);
 dmatrix third_derivatives(const df1_two_matrix& v);
    
/*
  df1_two_variable operator F(const df1_two_variable& x)
  {
    df1_two_variable z;

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

  df1_two_variable sin(const df1_two_variable& x);
  df1_two_variable fabs(const df1_two_variable& x);
  df1_two_variable sqrt(const df1_two_variable& x);
  df1_two_variable atan(const df1_two_variable& x);
  df1_two_variable cos(const df1_two_variable& x);
  df1_two_variable tan(const df1_two_variable& x);
  df1_two_variable log(const df1_two_variable& x);
  df1_two_variable square(const df1_two_variable& x);
  df1_two_variable cube(const df1_two_variable& x);
  df1_two_variable pow(const df1_two_variable& x,
    const df1_two_variable& y);

  df1_two_variable sqrt(const df1_two_variable& x);
  df1_two_variable exp(const df1_two_variable& x);
  df1_two_variable inv(const df1_two_variable& x);
  df1_two_variable operator * (const df1_two_variable& x,
    const df1_two_variable& y);
  df1_two_variable operator * (double x,
    const df1_two_variable& y);
  df1_two_variable operator * (const df1_two_variable& x,
    double y);
  df1_two_variable operator / (const df1_two_variable& x,
    const df1_two_variable& y);

  df1_two_variable operator / (const double x,const df1_two_variable& y);

  df1_two_variable operator / (const df1_two_variable& x,
    const double y);

  df1_two_variable operator + (const double x,
    const df1_two_variable& y);

  df1_two_variable operator + (const df1_two_variable& x,
    const double y);

  df1_two_variable operator + (const df1_two_variable& x,
    const df1_two_variable& y);
  df1_two_variable operator - (double x,const df1_two_variable& y);
  df1_two_variable operator - (const df1_two_variable& x,double y);

  df1_two_variable operator - (const df1_two_variable& x,
    const df1_two_variable& y);
  df1_two_variable operator - (const df1_two_variable& x,
    const df1_two_variable& y);
  df1_two_variable operator / (const df1_two_variable& x,
    const df1_two_variable& y);
  df1_two_variable operator * (const df1_two_variable& x,
    const df1_two_variable& y);


  df1_two_variable operator - (const df1_two_variable& v);
  df1_two_matrix choleski_decomp(const df1_two_matrix& MM);
 
  df1_two_variable cumd_gamma(const df1_two_variable& x,
    const df1_two_variable& a);


  df1_two_variable gammln(const df1_two_variable& xx);
#endif  // __DF12FUN__

