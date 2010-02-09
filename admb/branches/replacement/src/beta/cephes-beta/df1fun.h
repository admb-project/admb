#include <admodel.h>
#if !defined(__DF1FUN__)
#  define __DF1FUN__

  class df1_one_variable
  {
    double v[2];
  public:
    static prevariable * ind_var;
    double * get_u(void) const {return (double*) (&(v[0]));}
    double * get_udot(void)const {return (double*) (&(v[1]));}
    virtual df1_one_variable& operator = (const df1_one_variable& v);
    df1_one_variable& operator = (double v);
    df1_one_variable& operator += (const df1_one_variable& v);
    df1_one_variable& operator += (double);
    df1_one_variable& operator -= (const df1_one_variable& v);
    df1_one_variable& operator -= (double);
    df1_one_variable& operator *= (const df1_one_variable& v);
    df1_one_variable& operator /= (const df1_one_variable& v);
    df1_one_variable(void);
    df1_one_variable(const df1_one_variable& );
  };

  inline  double& value(const df1_one_variable& _x) 
  { 
    ADUNCONST(df1_one_variable,x)
    return (*x.get_u()); 
  }

  class init_df1_one_variable : public df1_one_variable
  {
  public:
    static int num_vars;
    init_df1_one_variable(const prevariable& );
    init_df1_one_variable(double );
    ~init_df1_one_variable();
    virtual df1_one_variable& operator = (const df1_one_variable& v)
    { 
      cerr << "can't do this" << endl; ad_exit(1); 
    }
  };

  df1_one_variable sin(const df1_one_variable& );
  df1_one_variable fabs(const df1_one_variable& );
  df1_one_variable cos(const df1_one_variable& );
  df1_one_variable exp(const df1_one_variable& );
  df1_one_variable log(const df1_one_variable& );
  df1_one_variable square(const df1_one_variable& );
  df1_one_variable cube(const df1_one_variable& );


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

  df1_one_variable operator - (const df1_one_variable& x,
    double y);
  df1_one_variable operator - (double x,const df1_one_variable& y);
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
 
#endif  // __DF1FUN__

