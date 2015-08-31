/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
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
/**
 * \file
 * Description not yet available.
 */

#if !defined(__DF1B2FUN__)
#  define __DF1B2FUN__

#if defined(__GNUC__) && (__GNUC__ < 3)
  #pragma interface
#endif

#include <adpool.h>
#ifndef FVAR_HPP
#  include <fvar.hpp>
#endif
#include <sys/stat.h>
#if !defined(_MSC_VER)
  #include <stddef.h>
  #include <fcntl.h>
#endif

#define USE_BARD_PEN

void ncount_checker(int ncount,int ncount_check);

class named_dvar_matrix;

int withinbound(int lb,int n,int ub);

class do_naught_kludge;
class newadkludge;


/**
 * Description not yet available.
 * \param
 */
class twointsandptr
{
public:
  short int ncopies;
  short int nvar;
#if defined (INCLUDE_BLOCKSIZE)
  int blocksize;
#endif
  adpool * ptr;
};


#if defined(__DERCHECK__)
/**
 * Description not yet available.
 * \param
 */
class dercheck_info
{
  int ind_index;
public:
  virtual void get_ind_index(void)
  {
    cerr << "cannot use this type here" << endl; ad_exit(1);
  }

  int node_number;
  int counter;
  int pass_number;
  int vartype;
  int dotflag;
  double der_value;
  double f1;
  double f2;
  double f3;
  double fd;
  double delta;
  dercheck_info(int _node_number,double _delta,int _index);
  void set_delta(double d){delta=d;}
  void set_node_number(int n){node_number=n;}
  void set_pass_number(int n){pass_number=n;}
  void set_index(int n){index=n;}
  void set_dotflag(int n){dotflag=n;}
  void set_vartype(int n){vartype=n;}
  void set_counter(int n){counter=n;}
  void set_f1(double d){f1=d;}
  void set_f2(double d){f2=d;}
  void set_f3(double d){f3=d;}
  void set_fd(void){fd=(f2-f3)/(2.0*delta);}
};
extern dercheck_info * derchecker;
#endif

typedef void * &  vreference;

/*
#if !defined(_MSC_VER)
inline void increment_pointer(vreference p,int n)
{
  char * cs =(char*)(p);
  cs+=n;
}
#endif
*/

#include <df32fun.h>
class df1b2_gradlist;
extern df1b2_gradlist* f1b2gradlist;
extern df1b2_gradlist* localf1b2gradlist;
extern df1b2_gradlist* globalf1b2gradlist;
extern df1b2_gradlist** f1b2gradlist_stack;
extern int max_num_init_df1b2variable;

void df1b2_gradcalc1(void);

extern char AD_allocation_error_message[];

#if defined(__BORLANDC__)
int adptr_diff(void * x, void * y) { return int(x)-int(y); }
#else
int adptr_diff(void* x, void* y);
#endif

void read_pass1_1(void);
void read_pass1_2(void);

#undef AD_ALLOCATE
#define AD_ALLOCATE(ptr,type,n,classname) \
  if ( (ptr = new type[n])==NULL) \
  { \
    cerr << AD_allocation_error_message << "classname" << endl; \
    ad_exit(1); \
  }


#undef ADUNCONST
#define ADUNCONST(type,obj) type & obj = (type&) _##obj;

/**
 * Description not yet available.
 * \param
 */
struct df1b2_header
{
  //double* ptr;
  double* u;
  double* u_dot;
  double* u_bar;
  double* u_dot_bar;
  double* u_tilde;
  double* u_dot_tilde;
  double* u_bar_tilde;
  double* u_dot_bar_tilde;
#if defined(__x86_64) || (defined(_MSC_VER) && defined(_M_X64))
  long indindex;
#else
  int indindex;
#endif

  //double * get_ptr(void){return ptr;}

  double* get_u(void) const {return (double*)u;}
  double* get_u_dot(void) const {return (double*)u_dot;}
  double* get_u_bar(void) const {return (double*)u_bar;}
  double* get_u_dot_bar(void) const {return (double*)u_dot_bar;}
  double* get_u_tilde(void) const {return (double*)u_tilde;}
  double* get_u_dot_tilde(void) const {return (double*)u_dot_tilde;}
  double* get_u_bar_tilde(void) const {return (double*)u_bar_tilde;}
  double* get_u_dot_bar_tilde(void) const {return (double*)u_dot_bar_tilde;}
};
  class adkludge1;

  class df1b2vector;

/**
 * Description not yet available.
 * \param
 */
  class predf1b2vector
  {
    df1b2vector * p;
    int lb;
    int ub;
    inline predf1b2vector(df1b2vector * _p,int _lb,int _ub)
      {p=_p;lb=_lb,ub=_ub;}
    friend class df1b2vector;
  };

  class df3_one_variable;
  class df3_two_variable;
  class df3_three_variable;
  class random_effects_bounded_vector_info;

/**
 * Description not yet available.
 * \param
 */
  class df1b2variable : public df1b2_header
  {
  public:
    double* ptr;
    int get_local_nvar(void) const {return int(((twointsandptr*)ptr)->nvar);}
    int allocated(void){return ptr!=0;}
    int unallocated(void){return ptr==0;}
    static adpool* pool;
    static int current_allocation_index;
    static int adpool_use_index[];
    static int pool_allocation_number[];
    static int allocation_counter;
    static const int adpool_vectorsize;
    static int adpool_counter;
    static void increment_adpool_counter(void);
    static const int adpool_stack_size;
    static adpool* adpool_vector[];
    static adpool* adpool_stack[];
    static unsigned int adpool_nvar_stack[];
    static int adpool_stack_pointer;
    static void save_adpool_pointer(void);
    static void restore_adpool_pointer(void);
    static unsigned int nvar_vector[];
    static int passnumber;
    static unsigned int nvar;  // the number of independent variables
    static int minder;  // the number of independent variables
    static int maxder;  // the number of independent variables
    static unsigned int blocksize;
    static int noallocate;

    static int get_passnumber(void){return passnumber;}
    static void set_nvar(unsigned int n) { nvar = n;}
    static unsigned int get_nvar() { return nvar; }
    static void set_minder(int n){minder=n;}
    static void set_maxder(int n){maxder=n;}
    static void set_blocksize(void);
    static unsigned int get_blocksize(void);
    static unsigned int get_blocksize(const unsigned int n);
#if defined(__x86_64) || (defined(_MSC_VER) && defined(_M_X64))
    long& get_ind_index() { return indindex; }
    const long& get_ind_index() const { return indindex; }
#else
    int& get_ind_index() { return indindex; }
    const int& get_ind_index() const { return indindex; }
#endif
    short int* ncopies;
    // for fixed size n whole thing is 6n+2
    void initialize(void);
    void initialize(const unsigned int n);

    df1b2variable(const do_naught_kludge&){ ptr = 0; }

#if defined(USE_DDOUBLE)
#undef double
    df1b2variable(double d);
#define double dd_real
#endif
    df1b2variable(double d);
    df1b2variable(void);
    void allocate(void);
    void allocate(const char *);

    df1b2variable(adkludge1 * );
    df1b2variable(const random_effects_bounded_vector_info& rebv);

    df1b2variable(const newadkludge * );

    df1b2variable(const df1b2variable& v);

    df1b2variable& operator = (const df3_one_variable& v);
    df1b2variable& operator = (const df3_two_variable& v);
    df1b2variable& operator = (const df3_three_variable& v);
    df1b2variable& operator = (const df1b2variable& v);
    df1b2variable& operator += (const df1b2variable& v);
    df1b2variable& operator -= (const df1b2variable& v);
    df1b2variable& operator *= (const df1b2variable& v);
    df1b2variable& operator /= (const df1b2variable& v);

    void operator = (double x);

    virtual ~df1b2variable();
    void deallocate(void);
  };

void print_dot_derivatives(df1b2_header * px,const char * s);
void print_derivatives(const adstring&, double f, double df,
  double d2f,double d3f,int bflag=0);
void print_derivatives(const adstring&, double f, double df1,
  double df2,double df11,double df12, double df22,
  double df111, double df112, double df122, double df222,int bflag=0);

void print_derivatives(df1b2_header * px,const char * s,
  int bflag=0);

/**
 * Description not yet available.
 * \param
 */
  class init_df1b2variable : public df1b2variable
  {
  public:
    int ind_index;
    int get_index(void){return ind_index;}
    static int num_variables;
    static init_df1b2variable ** list;
    init_df1b2variable(double v=0.0);
    void operator = (double x);
    void set_u_dot(void);
  };

/**
 * Description not yet available.
 * \param
 */
  class init_df1b2vector
  {
    int index_min;
    int index_max;
    int * ncopies;
    init_df1b2variable * trueptr;
    init_df1b2variable * ptr;
  public:
    void deallocate(void);
    void reallocate(void);
    void allocate(int lib,int ub);
    void allocate(void);
    init_df1b2vector(int lib,int ub);
    init_df1b2vector(void);
    init_df1b2vector(const init_df1b2vector& v);
    int indexmin(void) const {return index_min;}
    int indexmax(void) const {return index_max;}

#if defined(OPT_LIB)
    init_df1b2variable& operator () (int i) { return ptr[i];}
    init_df1b2variable& operator [] (int i) { return ptr[i];}
#else
    init_df1b2variable& operator () (int i);
    init_df1b2variable& operator [] (int i);
#endif
    void set_value(const dvector&);
    ~init_df1b2vector();
  };

/**
 * This is a function object for a function of one variable which
 * stores the functions which calculate the first second and third
 * derivatives
 */
class df1b2function1
{
public:
  double (*f)(double);
  double (*df)(double);
  double (*d2f)(double);
  double (*d3f)(double);
  adstring funname;

  df1b2function1(double (*_f)(double),double (*_df)(double),
      double (*d2f)(double),double (*_d3f)(double),
      const adstring& s="unnamed");

  df1b2variable operator () (const df1b2variable& x);
  //df1b2variable& operator () (const df1b2variable& z,const df1b2variable& x);
  df1b2variable& operator () (const df1b2variable& z,const df1b2variable& x,
    int s); // s is a switch for picking special function for simple
               // operations like +=
};

/**
 * Description not yet available.
 * \param
 */
  class df1b2function2
  {
  public:
    double (*f)(double,double);
    double (*df1)(double,double);
    double (*df2)(double,double);
    double (*d2f11)(double,double);
    double (*d2f12)(double,double);
    double (*d2f22)(double,double);
    double (*d3f111)(double,double);
    double (*d3f112)(double,double);
    double (*d3f122)(double,double);
    double (*d3f222)(double,double);
    adstring funname;

    df1b2function2
    (
      double (*_f)(double,double),
      double (*_df1)(double,double),double (*_df2)(double,double),
      double (*d2f11)(double,double),
      double (*d2f12)(double,double),
      double (*d2f22)(double,double),
      double (*_d3f111)(double,double),
      double (*_d3f112)(double,double),
      double (*_d3f122)(double,double),
      double (*_d3f222)(double,double),
      const adstring & funame="unnamed"
    );

    df1b2variable operator () (const df1b2variable& x,const df1b2variable& y);
  };

/**
 * Description not yet available.
 * \param
 */
  class mydf1b2function2
  {
  public:
    double (*f)(double,double);
    double (*df1)(double,double);
    double (*df2)(double,double);
    double (*d2f11)(double,double);
    double (*d2f12)(double,double);
    double (*d2f22)(double,double);
    double (*d3f111)(double,double);
    double (*d3f112)(double,double);
    double (*d3f122)(double,double);
    double (*d3f222)(double,double);

    mydf1b2function2
    (
      double (*_f)(double,double),
      double (*_df1)(double,double),double (*_df2)(double,double),
      double (*d2f11)(double,double),
      double (*d2f12)(double,double),
      double (*d2f22)(double,double),
      double (*_d3f111)(double,double),
      double (*_d3f112)(double,double),
      double (*_d3f122)(double,double),
      double (*_d3f222)(double,double)
    );

    df1b2variable operator () (const df1b2variable& x,const df1b2variable& y);
  };

/**
 * Description not yet available.
 * \param
 */
class smartlist
{
public:
  char* buffer;
  char* buffend;
  char* bptr;
  char* sbptr;
  unsigned int bufsize;
  adstring filename;
  int fp;
  void saveposition(void){sbptr=bptr;}
  void reset(void){bptr=buffer;}
  void restoreposition(void){bptr=sbptr;}
  void restoreposition(int offset){bptr=sbptr+offset;}
  smartlist(unsigned int bufsize,const adstring& filename);
  double report_usage(void)
  {
    return double(size_t(bptr)-size_t(buffer))
           / double(size_t(buffend)-size_t(buffer));
  }
};

/**
 * Description not yet available.
 * \param
 */
  class test_smartlist
  {
  public:
    int direction;
    int written_flag;
    int noreadflag;
    void save_end(void);
    void restore_end(void);
    int eof_flag;
    int end_saved;
    char * true_buffer;
    char * true_buffend;
    char * recend;
    char * buffer;
    char * buffend;
    char * bptr;
    char * sbptr;
    size_t bufsize;
    adstring filename;
    int fp;
public:
    test_smartlist(void);
    ~test_smartlist();

    void saveposition(void){sbptr=bptr;}
    void set_recend(){bptr=recend+1;} // one passed the end so that when
                                      // you back up n bytes it points to the
                                      // beginning of an n byte record
    void reset(void);
    int eof(void){ return eof_flag;}
    int get_noreadflag(void){ return noreadflag; }
    void set_noreadflag(int n){ noreadflag=n; }
    void restoreposition(void){bptr=sbptr;}
    void restoreposition(int offset){bptr=sbptr+offset;}
    test_smartlist(const size_t bufsize,const adstring& filename);
    void allocate(const size_t bufsize,const adstring& filename);
    void read_buffer(void);
    void set_forward(void){direction=0;}
    void set_backword(void){direction=-1;}
    void set_reverse(void){direction=-1;}
    void rewind(void);
    void initialize(void);
    void operator-=(const int);
    void operator+=(const int);
    double report_usage(void)
    {
      return double(size_t(bptr)-size_t(buffer))
             / double(size_t(buffend)-size_t(buffer));
    }
    //void write(void * p,const size_t n);
    void write(const size_t n);
    void write_buffer(void);
    void check_buffer_size(const size_t);
    void add_buffer_fringe(int n){buffend-=n;}
    int written(void){return written_flag;}
  };

  typedef void (*ADrfptr)(void);

/**
 * Description not yet available.
 * \param
 */
  class fixed_list_entry
  {
  public:
    int numbytes;
    ADrfptr pf;
  };

/**
 * Description not yet available.
 * \param
 */
  class fixed_smartlist
  {
  public:
    fixed_smartlist();
    fixed_smartlist(const size_t bufsize,const adstring& filename);
    ~fixed_smartlist();

    void operator ++ (void);
    void operator -- (void);
    size_t nentries;
    int direction;
    off_t endof_file_ptr;
    int written_flag;
    int noreadflag;
    void save_end(void);
    void restore_end(void);
    int eof_flag;
    int end_saved;
    fixed_list_entry * true_buffer;
    fixed_list_entry * true_buffend;
    fixed_list_entry * recend;
    fixed_list_entry * buffer;
    fixed_list_entry * buffend;
    fixed_list_entry * bptr;
    fixed_list_entry * sbptr;
    size_t bufsize;
    adstring filename;
    int fp;
    void saveposition(void){sbptr=bptr;}
    void set_recend(){bptr=recend+1;} // one passed the end so that when
                                      // you back up n bytes it points to the
                                      // beginning of an n byte record
    void reset(void);
    int eof(void){ return eof_flag;}
    void read_file(void);
    int get_noreadflag(void){ return noreadflag; }
    void set_noreadflag(int n){ noreadflag=n; }
    void restoreposition(void){bptr=sbptr;}
    void restoreposition(int offset){bptr=sbptr+offset;}
    void allocate(const size_t bufsize,const adstring& filename);
    void read_buffer(void);
    void set_forward(void){direction=0;}
    void set_backword(void){direction=-1;}
    void set_reverse(void){direction=-1;}
    void rewind(void);
    void initialize(void);
    void operator -= (int);
    void operator += (int);
    double report_usage(void)
    {
      return double(size_t(bptr)-size_t(buffer))
             / double(size_t(buffend)-size_t(buffer));
    }
    //void write(void * p,int n);
    void write(const size_t);
    void write_buffer(void);
    void write_buffer_one_less(void);
    void check_buffer_size(const size_t);
    void add_buffer_fringe(int n){buffend-=n;}
    int written(void){return written_flag;}
  };

/**
 * Description not yet available.
 * \param
 */
  class fixed_smartlist2
  {
  public:
    fixed_smartlist2(void);
    fixed_smartlist2(const size_t bufsize,const adstring& filename);
    ~fixed_smartlist2();

    void operator ++ (void);
    void operator -- (void);
    size_t nentries;
    int direction;
    off_t endof_file_ptr;
    int written_flag;
    int noreadflag;
    void save_end(void);
    void restore_end(void);
    int eof_flag;
    int end_saved;
    int * true_buffer;
    int * true_buffend;
    int * recend;
    int * buffer;
    int * buffend;
    int * bptr;
    int * sbptr;
    size_t bufsize;
    adstring filename;
    int fp;
    void saveposition(void){sbptr=bptr;}
    void set_recend(){bptr=recend+1;} // one passed the end so that when
                                      // you back up n bytes it points to the
                                      // beginning of an n byte record
    void reset(void){bptr=buffer;}
    int eof(void){ return eof_flag; /*eof_flag=0;*/}

    void read_file(void);
    int get_noreadflag(void){ return noreadflag; }
    void set_noreadflag(int n){ noreadflag=n; }
    void restoreposition(void){bptr=sbptr;}
    void restoreposition(int offset){bptr=sbptr+offset;}
    void allocate(const size_t bufsize,const adstring& filename);
    void read_buffer(void);
    void set_forward(void){direction=0;}
    void set_backword(void){direction=-1;}
    void set_reverse(void){direction=-1;}
    void rewind(void);
    void initialize(void);
    void operator -= (int);
    void operator += (int);
    double report_usage(void)
    {
      return double(size_t(bptr)-size_t(buffer)) /
             double(size_t(buffend)-size_t(buffer));
    }
    //void write(void * p,int n);
    void write(const size_t n);
    void write_buffer(void);
    void write_buffer_one_less(void);
    void check_buffer_size(const size_t);
    void add_buffer_fringe(int n){buffend-=n;}
    int written(void){return written_flag;}
  };


  void write(const test_smartlist &,void *,int nsize);
  void read(const test_smartlist &,void *,int nsize);
  void memcpy(test_smartlist&, void*, const size_t nsize);
  void memcpy(void*, test_smartlist&, const size_t nsize);

  class df1b2function2c;

/**
 * Description not yet available.
 * \param
 */
  class df1b2_gradlist
  {
  public:
#if defined(CHECK_COUNT)
    static int ncount_check;
    static set_ncount_check(int n){ncount_check=n;}
#endif
    int ncount;
    test_smartlist list;
    fixed_smartlist nlist;
    test_smartlist list2;
    fixed_smartlist2 nlist2;
    test_smartlist list3;
    fixed_smartlist2 nlist3;
    static int no_derivatives;
    static void set_no_derivatives(void) {no_derivatives=1;}
    static void set_yes_derivatives(void) {no_derivatives=0;}
    df1b2_gradlist(unsigned int bufsize,unsigned int nbufsize,
     unsigned int bufsize1, unsigned int nbufsize1,
     unsigned int bufsize2, unsigned int nbufsize2,const adstring& filename);
    int mywrite_pass1(const df1b2variable * px, const df1b2variable * py,
      df1b2variable * pz, mydf1b2function2 * pf);
    int write_pass1_sum(double x, const df1b2variable * py,
      df1b2variable * pz);
    int write_pass1_sum(const df1b2variable * px, const df1b2variable * py,
      df1b2variable * pz);
    int write_pass1_prod(double x, const df1b2variable * py,
      df1b2variable * pz);
    int write_pass1_prod(const df1b2variable * px, double py,
      df1b2variable * pz);
    int write_pass1x(const df1b2variable * _px, df1b2variable * pz,
      df1b2function1 * pf);

    int write_pass1_prod(const df1b2vector * px, const df1b2vector * py,
      df1b2variable * pz);

    int write_pass1_prod(const df1b2variable * px, const df1b2variable * py,
      df1b2variable * pz);
    int write_pass1_minuscv(const df1b2variable * py,df1b2variable * pz);
    int write_pass1_minusvc(const df1b2variable * py,df1b2variable * pz);
    int write_pass1_minus(const df1b2variable * px, const df1b2variable * py,
      df1b2variable * pz);
    int write_pass1c(const df1b2variable * px, double y, df1b2variable * pz,
      df1b2function2c * pf);
    int write_pass1c(double x,const df1b2variable * py, df1b2variable * pz,
      df1b2function2c * pf);
    int write_pass1(const df1b2variable * px, const df1b2variable * py,
      df1b2variable * pz, df1b2function2 * pf);
    int write_pass1_pluseq(const df1b2variable * px,df1b2variable * pz);
    int write_pass1_minuseq(const df1b2variable * px,df1b2variable * pz);
    int write_pass1_initialize(df1b2variable * pz);
    int write_pass1_eq(const df1b2variable * px,df1b2variable * pz);
    int write_pass1(const df1b2variable * px,
      df1b2variable * pz, df1b2function1 * pf);
    int write_pass1(const df1b2variable * px,
      df1b2variable * pz, double df, double d2f, double d3f );

    int write_pass1(const df1b2variable * _px,
      const df1b2variable * _py,df1b2variable * pz,double df_x,
      double df_y,
      double df_xx,
      double df_xy,
      double df_yy,
      double df_xxx,
      double df_xxy,
      double df_xyy,
      double df_yyy);

 int write_pass1(const df1b2variable * _px,
   const df1b2variable * _py,const df1b2variable * pw,
   const df1b2variable * pz,
   double df_x, double df_y, double df_z,
   double df_xx, double df_xy,double df_xz,double df_yy,
   double df_yz,double df_zz,
   double df_xxx,
   double df_xxy,
   double df_xxz,
   double df_xyy,
   double df_xyz,
   double df_xzz,
   double df_yyy,
   double df_yyz,
   double df_yzz,
   double df_zzz);



    int write_save_pass2_tilde_values(const df1b2variable * px);
    void reset(void);
  };

/**
 * Description not yet available.
 * \param
 */
class ad_dstar
{
public:
  static unsigned int n;
  static void allocate(const unsigned int _n);
  double* p;
  ad_dstar(void);
  ~ad_dstar(void);
  operator double* (){return p;}
};

typedef void (**ADprfptr)(void);
typedef void (*ADrfptr)(void);

void set_dependent_variable(const df1b2variable& _x);

dmatrix get_hessian(const init_df1b2vector& x);
//df1b2variable user_function(const init_df1b2vector& x);

dmatrix check_second_derivatives(const init_df1b2vector& x);
d3_array check_third_derivatives(const init_df1b2vector& x);

// ************************************************************
// ************************************************************

df1b2variable mfexp(const df1b2variable& x);
df1b2variable mfexp(const df1b2variable& x,double b);

// ************************************************************
// ************************************************************

df1b2variable fabs(const df1b2variable& x);
df1b2variable max(const df1b2vector& t1);
df1b2variable sfabs(const df1b2variable& x);
df1b2variable pow(const df1b2variable& x,const df1b2variable& y);
df1b2variable pow(const df1b2variable& x,double y);
df1b2variable mypow(const df1b2variable& x,double y);
df1b2variable pow(double x,const df1b2variable& y);
df1b2variable sin(const df1b2variable& x);
df1b2variable atan(const df1b2variable& x);
df1b2variable tan(const df1b2variable& x);
df1b2variable inv(const df1b2variable& x);
df1b2variable sqrt(const df1b2variable& x);
df1b2variable cos(const df1b2variable& x);
df1b2variable exp(const df1b2variable& x);
df1b2variable log(const df1b2variable& x);
df1b2variable square(const df1b2variable& x);
df1b2variable cube(const df1b2variable& x);
df1b2variable fourth(const df1b2variable& x);
df1b2variable operator * (const df1b2variable& x,double y);
df1b2variable operator * (const df1b2variable& x,const df1b2variable& y);
df1b2variable operator * (double x,const df1b2variable& y);
df1b2variable mult_add(const df1b2variable& x,const df1b2variable& y);
df1b2variable operator + (const df1b2variable& x,const df1b2variable& y);
df1b2variable div(const df1b2variable& x,const df1b2variable& y);
df1b2variable operator + (double x,const df1b2variable& y);
df1b2variable operator + (const df1b2variable& x,double y);

/**
 * Description not yet available.
 * \param
 */
inline df1b2variable operator + (const df1b2variable& x,double y)
{
  return y+x;
}

df1b2variable operator - (const df1b2variable& x,const df1b2variable& y);
df1b2variable operator - (double x,const df1b2variable& y);
df1b2variable operator / (const df1b2variable& x,const df1b2variable& y);
df1b2variable operator / (const df1b2variable& x,double y);
df1b2variable operator - (const df1b2variable& x,double y);
df1b2variable operator / (double x,const df1b2variable& y);

df1b2variable lgamma2(const df1b2variable& _x);//new log gamma using forward AD
df1b2variable gammln(const df1b2variable& _xx);
df1b2vector gammln(const df1b2vector&  _xx);
df1b2variable log_comb(const df1b2variable& n, double k);
df1b2variable log_comb(const df1b2variable& n, const df1b2variable& k);
df1b2variable log_comb(double n, const df1b2variable& k);
df1b2variable factln(const df1b2variable& n);

// vector and matrix stuff

/**
 * Description not yet available.
 * \param
 */
class df1b2vector_header
{
protected:
  int offset;
  int index_min;
  int index_max;
};

class df3_one_vector;
class funnel_init_df1b2vector;
class df3_two_vector;

 // class predf1b2vector
 // {
 //   df1b2vector * p;
 //   int lb;
 //   int ub;
 //inline predf1b2vector(df1b2vector * _p,int _lb,int _ub) {p=_p;lb=_lb,ub=_ub;}
 //   friend class df1b2vector;
 // };

/**
 * Description not yet available.
 * \param
 */
class df1b2vector : public df1b2vector_header
{
  df1b2variable * v;
  vector_shapex * shape;
public:
  inline df1b2vector& operator -- (void)
  {
    index_min--;index_max--;v++; return *this;
  }
  inline df1b2vector& operator ++ (void)
  {
    index_min++;index_max++;v--; return *this;
  }
  int pointersize() const { return (int)sizeof(df1b2variable); }
  inline df1b2variable * getv(void) {return v;}
  int allocated(void){return v!=0;}
  int indexmin(void)const {return index_min;}
  int indexmax(void)const {return index_max;}
  int size(){return index_max-index_min+1;}
  df1b2vector(int lb,int ub);
  df1b2vector(const dvector& v);
  ~df1b2vector();
  df1b2vector(const df1b2vector&);
  void copy(const df1b2vector&);
  df1b2vector(void);
  void allocate(int lb,int ub,const char *);
  void allocate(int lb,int ub);
  void allocate(const ad_integer&,const ad_integer& ub);
  void noallocate(int lib,int ub);
  df1b2vector& shift(int);
  void allocate(void);
  void initialize(void);
  void deallocate(void);
  int get_offset(void){return offset;}
  df1b2vector& operator = (const df3_one_vector&);
  df1b2vector& operator = (const df1b2vector&);
  df1b2vector& operator = (const dvector&);
  df1b2vector& operator = (double);
  df1b2vector& operator = (const df1b2variable&);
  df1b2vector& operator = (const df3_two_vector& M);
#  if defined(OPT_LIB)
  df1b2variable& operator () (int i) const
  {
   return *((df1b2variable*)((char*)(v)+i*pointersize()));
  }
  df1b2variable& operator [] (int i) const
  {
   return *((df1b2variable*)((char*)(v)+i*pointersize()));
  }
 //  df1b2vector operator () (int i,int j)
 //  {
 //    return predf1b2vector(this,i,j);
 //  }
 // df1b2vector(const predf1b2vector&);
#  else
  //df1b2vector operator () (int i,int j);
  //df1b2variable& operator () const (int i);
  df1b2variable& operator () (int i) const;
  df1b2variable& operator [] (int i) const;
#  endif
  df1b2vector operator() (const ivector & iv);
  df1b2vector& operator += (const df1b2vector& x);
  df1b2vector& operator += (const dvector& x);
  df1b2vector& operator += (double x);
  df1b2vector& operator -= (const df1b2vector& x);
  df1b2vector& operator -= (const dvector& x);
  df1b2vector& operator /= (const df1b2vector& x);
  df1b2vector& operator *= (const df1b2vector& x);
  df1b2vector& operator *= (const df1b2variable& x);
  df1b2vector& operator -= (const df1b2variable& x);
  df1b2vector& operator += (const df1b2variable& x);
  df1b2vector& operator /= (const df1b2variable& x);
  df1b2vector(const predf1b2vector&);
  inline df1b2vector operator () (int lb,int ub)
  {
    return predf1b2vector(this,lb,ub);
  }
  friend class random_effects_bounded_vector_info;
  friend class df1b2variable;
  friend class xf_df1b2vector;
  //df1b2vector(const funnel_init_df1b2vector& _s);
};
class df3_one_matrix;
class df3_two_matrix;

/**
 * Description not yet available.
 * \param
 */
class df1b2matrix
{
  int index_min;
  int index_max;
  df1b2vector * v;
  mat_shapex * shape;
public:
  int allocated(void){return v!=0;}
  void initialize(void);
  ~df1b2matrix();
  void colfill(const int j, const df1b2vector& v);
  int rowmin(void) const {return index_min;}
  int indexmin(void) const {return index_min;}
  int indexmax(void) const {return index_max;}
  int rowmax(void) const {return index_max;}
  int size(void) const {return index_max-index_min+1;}
  df1b2matrix(int nrl,int nrh,int ncl,int nch);
  df1b2matrix(int nrl,int nrh);
  df1b2matrix(const df1b2matrix&);
  df1b2matrix(int nrl,int nrh,const index_type& ncl,
    const index_type& nch);
  df1b2matrix& operator =(const df3_one_matrix&);

  df1b2matrix& operator =(const df1b2matrix&);
  df1b2matrix& operator =(const dmatrix&);
  df1b2matrix& operator =(const df1b2variable&);
  df1b2matrix& operator =(double);
  df1b2matrix& operator = (const df3_two_matrix& M);
  df1b2matrix(void);
  df1b2matrix& operator +=(const df1b2matrix& M);
  df1b2matrix& operator -=(const df1b2matrix& M);
  void allocate(int nrl,int nrh,int ncl,int nch);
  void allocate(int nrl,int nrh);
  void allocate(int nrl,int nrh,int ncl,int nch,const char *);
  void allocate(int nrl,int nrh,const index_type& ncl,
    const index_type& nch);
  void allocate(int nrl,int nrh,const index_type& ncl,
    const index_type& nch,const char *);
  void allocate(void);
  void deallocate(void);
  df1b2variable& operator()(int i,int j) const;
  df1b2vector& operator[](int i) const;
  df1b2vector& operator()(int i) const;
  int colmin(void) const {return (*(df1b2matrix*)(this))(index_min).indexmin();}
  int colmax(void) const {return (*(df1b2matrix*)(this))(index_min).indexmax();}
  int colsize(void)const {return colmax()-colmin()+1;}
  df1b2matrix& operator *= (const df1b2variable& x);
  df1b2matrix& operator /= (const df1b2variable& x);
  df1b2matrix& operator *= (double x);
  df1b2matrix& operator /= (double x);
};
#if defined(OPT_LIB)
inline df1b2variable& df1b2matrix::operator()(int i,int j) const
{
  return (df1b2variable&)(v[i][j]);
}
inline df1b2vector& df1b2matrix::operator[](int i) const
{
  return (df1b2vector&)(v[i]);
}
inline df1b2vector& df1b2matrix::operator()(int i) const
{
  if (!v)
    throw std::bad_alloc();
  else
    return v[i];
}
#endif

/**
 * Description not yet available.
 * \param
 */
class df1b23array
{
  int index_min;
  int index_max;
  df1b2matrix * v;
  vector_shapex * shape;
public:
  int allocated(void){return v!=0;}
  void initialize(void);
  ~df1b23array();
  int indexmin(void){return index_min;}
  int indexmax(void){return index_max;}
  int size(void){return index_max-index_min+1;}
  df1b23array(int nrl,int nrh,int ncl,int nch,int,int);
  df1b23array(int nrl,int nrh);
  df1b23array(int nrl,int nrh,int,int);
  df1b23array(const df1b23array&);
  //df1b23array& operator =(const df3_one_matrix&);

  df1b23array& operator =(const df1b23array&);
  df1b23array& operator =(const df1b2variable&);
  df1b23array& operator =(double);
  df1b23array(void);
  df1b23array& operator +=(const df1b23array& M);
  df1b23array& operator -=(const df1b23array& M);
  void allocate(int nrl,int nrh,int ncl,int nch,int,int);
  void allocate(int nrl,int nrh,int,int);
  void allocate(int nrl,int nrh);
  void allocate(int nrl,int nrh,int ncl,int nch,int,int,const char *);

  void allocate(int nrl,int nrh,
    const index_type& ncl, const index_type& nch);


  void allocate(int nrl,int nrh,
    const index_type& ncl, const index_type& nch,
    const index_type& nxl, const index_type& nxh);

  void allocate(int nrl,int nrh,
    const index_type& ncl,const index_type& nch,
    const index_type& nxl,const index_type& nxh,
    const char *);
  void allocate(void);
  void deallocate(void);
#  if defined(OPT_LIB)
  df1b2variable& operator () (int i,int j,int k){return v[i](j,k);}
  df1b2vector& operator () (int i,int j){return v[i][j];}
  df1b2matrix& operator () (int i){return v[i];}
  df1b2matrix& operator [] (int i){return v[i];}
#else
  df1b2variable& operator () (int i,int j,int k);
  df1b2vector& operator () (int i,int j);
  df1b2matrix& operator () (int i);
  df1b2matrix& operator [] (int i);
#endif
};


// **************************************
// **************************************
df1b2vector fabs(const df1b2vector& t1);
df1b2vector mfexp(const df1b2vector& x);
df1b2vector exp(const df1b2vector& x);
df1b2vector sqrt(const df1b2vector& x);
df1b2vector sin(const df1b2vector& x);
df1b2vector tan(const df1b2vector& x);
df1b2vector cos(const df1b2vector& x);
df1b2vector log(const df1b2vector& x);

df1b2matrix mfexp(const df1b2matrix& M);
df1b2matrix log(const df1b2matrix& M);
df1b2matrix trans(const df1b2matrix& M);
df1b2matrix choleski_decomp(const df1b2matrix& M);
df1b2matrix choleski_decomp_extra(const df1b2matrix& M);
df1b2matrix exp(const df1b2matrix& M);
df1b2vector column(const df1b2matrix&,int i);
df1b2vector colsum(const df1b2matrix&);
df1b2vector rowsum(const df1b2matrix&);

df1b2vector operator * (double,const df1b2vector& y);
df1b2vector operator * (const df1b2vector& y,const double);
df1b2variable operator * (const df1b2vector& y,const dvector&);
df1b2variable operator * (const dvector&,const df1b2vector& y);
df1b2vector operator * (const df1b2vector& y,const df1b2variable&);
df1b2vector operator * (const df1b2variable&,const df1b2vector& y);

df1b2matrix outer_prod(const df1b2vector& x,const df1b2vector& y);
df1b2matrix operator + (const df1b2matrix& M,const df1b2variable& x);

df1b2matrix operator + (const df1b2matrix& M,const df1b2matrix& N);
df1b2matrix operator + (const df1b2matrix& M,const dmatrix& N);

df1b2matrix operator * (const df1b2matrix& M,const df1b2variable& x);
df1b2matrix operator * (const dmatrix& M,const df1b2variable& x);
df1b2vector operator * (const dmatrix& M,const df1b2vector& x);
df1b2matrix operator * (const df1b2variable& x,const dmatrix& M);

df1b2matrix operator * (const df1b2matrix& M,const df1b2matrix& x);
df1b2matrix operator * (const dmatrix& M,const df1b2matrix& x);
df1b2matrix operator + (const dmatrix& M,const df1b2matrix& x);
df1b2matrix operator + (const df1b2variable&, const df1b2matrix& M);
df1b2vector operator + (const df1b2variable&, const dvector& M);
df1b2matrix operator * (const df1b2variable&, const df1b2matrix& M);
df1b2matrix operator + (const df1b2matrix& M,const double x);
df1b2matrix operator * (const df1b2matrix& M,const double x);

df1b2matrix operator - (const df1b2matrix& M,const dmatrix& x);
df1b2matrix operator - (const df1b2matrix& M,const double x);
df1b2matrix operator - (const df1b2matrix& M,const df1b2variable& x);
df1b2matrix operator - (const df1b2matrix& M,const df1b2matrix& x);
df1b2matrix operator - (const dmatrix& M,const df1b2matrix& x);
df1b2matrix operator - (const df1b2variable&, const df1b2matrix& M);
df1b2matrix operator - (const double, const df1b2matrix& M);

df1b2matrix operator + (const df1b2variable&, const df1b2matrix& M);

df1b2matrix operator + (const double, const df1b2matrix& M);
df1b2matrix operator * (const double, const df1b2matrix& M);
df1b2matrix elem_prod(const df1b2matrix& x,const df1b2matrix& y);
df1b2matrix elem_prod(const dmatrix& x,const df1b2matrix& y);
df1b2matrix elem_prod(const df1b2matrix& x,const dmatrix& y);
df1b2matrix elem_div(const df1b2matrix& x,const df1b2matrix& y);
df1b2matrix elem_div(const dmatrix& x,const df1b2matrix& y);
df1b2matrix elem_div(const df1b2matrix& x,const dmatrix& y);

df1b2vector elem_prod(const df1b2vector& x,const df1b2vector& y);
df1b2vector elem_prod(const df1b2vector& x,const dvector& y);
df1b2vector elem_prod(const dvector& x,const df1b2vector& y);
df1b2vector elem_div(const df1b2vector& x,const df1b2vector& y);
df1b2vector elem_div(const dvector& x,const df1b2vector& y);
df1b2vector elem_div(const df1b2vector& x,const dvector& y);

df1b2vector operator + (const df1b2variable& x,const df1b2vector& y);
df1b2vector operator + (double x,const df1b2vector& y);
df1b2vector operator + (const df1b2vector& x,const df1b2vector& y);
df1b2vector operator + (const df1b2vector& x,const df1b2variable& y);
df1b2vector operator + (const dvector& x,const df1b2vector& y);
df1b2vector operator + (const df1b2vector& y,const dvector& x);

df1b2vector operator - (const df1b2vector& x,const df1b2vector& y);
df1b2vector operator - (const dvector& x,const df1b2vector& y);
df1b2vector operator - (const df1b2variable& x,const df1b2vector& y);
df1b2vector operator - (const df1b2vector& x,const df1b2vector& y);
df1b2vector operator - (const df1b2variable& x,const df1b2vector& y);
df1b2vector operator - (const df1b2variable& x,const dvector& y);
df1b2vector operator - (const df1b2vector& x,const df1b2variable& y);
df1b2vector operator - (const df1b2vector& x,const dvector& y);

df1b2vector operator * (const df1b2variable& y,const dvector&);

df1b2vector operator * (const df1b2vector& x,const df1b2variable& y);
df1b2vector operator * (const df1b2vector& x,double y);

df1b2vector operator / (const df1b2variable& y,const df1b2vector& x);
df1b2vector operator / (const double& y,const df1b2vector& x);

df1b2vector operator / (const df1b2vector& x,const df1b2variable& y);
df1b2vector operator / (const df1b2vector& x,double y);
df1b2vector pow(const df1b2vector& x,double y);
df1b2vector pow(const df1b2vector& v,const df1b2variable & x);
df1b2vector pow(const df1b2vector& v,const df1b2vector & x);
df1b2vector pow(const df1b2variable& v,const df1b2vector & x);
df1b2vector pow(df1b2vector const& _x,dvector const& v);
df1b2vector pow(double v,const df1b2vector & x);
df1b2vector pow(const dvector& x,  const df1b2vector& a);
df1b2vector pow(const dvector& x,  const df1b2variable& a);

df1b2vector operator / (const dvector& x,const df1b2variable& y);
df1b2vector operator + (const dvector& x,const df1b2variable& y);
df1b2vector operator - (const dvector& x,const df1b2variable& y);
df1b2vector operator * (const dvector& x,const df1b2variable& y);
// **************************************
// **************************************
df1b2variable sum(const df1b2vector& x);
df1b2variable mean(const df1b2vector& x);
df1b2variable norm2(const df1b2vector& x);
df1b2variable sumsq(const df1b2vector& x);
df1b2variable norm(const df1b2vector& x);

df1b2variable norm2(const df1b2matrix& x);
df1b2variable sumsq(const df1b2matrix& x);
df1b2variable norm(const df1b2matrix& x);
df1b2variable mean(const df1b2matrix& x);
df1b2variable sum(const df1b2matrix& x);
df1b2matrix square(const df1b2matrix& x);
df1b2vector square(const df1b2vector& x);
df1b2vector cube(const df1b2vector& x);
df1b2vector solve(const df1b2matrix& x,const dvector&);
df1b2vector solve(const df1b2matrix& x,const df1b2vector&);

int size_count(const df1b2matrix& x);
int size_count(const df1b2vector& x);

df1b2vector first_difference(const df1b2vector& x);

df1b2vector operator * (const dvector& ,const df1b2matrix& );
df1b2vector operator * (const df1b2vector& ,const df1b2matrix& );
df1b2vector operator * (const df1b2vector& ,const dmatrix& );
df1b2variable operator * (const df1b2vector& x,const df1b2vector& y);
df1b2vector operator * (const df1b2matrix& M,const df1b2vector& x);
df1b2vector operator * (const df1b2matrix& M,const dvector& x);
void check_shape(const df1b2vector & x,const df1b2vector & y,const char * s);
void check_shape(const df1b2vector & x,const dvector & y,const char * s);
void check_shape(const dvector & x,const df1b2vector & y,const char * s);
void check_shape(const df1b2vector & x,const df1b2matrix & y,const char * s);

void checkidentiferstring(const char * ids,test_smartlist& list);

double& value(const df1b2variable& _x);
dvector value(const df1b2vector& _x);
dmatrix value(const df1b2matrix& _x);

/**
 * Description not yet available.
 * \param
 */
class initial_df1b2params
{
public:
  static int stddev_scale(const dvector& d,const dvector& x);
  static int current_phase;
  static int separable_flag;
  static int separable_calculation_type;
  static int have_bounded_random_effects;
  int phase_start;
  int phase_save;
  int ind_index;
  double scalefactor;

  static void save_varsptr(void);
  static double cobjfun;
  static void restore_varsptr(void);
#if defined(__x86_64) || (defined(_MSC_VER) && defined(_M_X64))
  static lmatrix* pointer_table;
#else
  static imatrix* pointer_table;
#endif
  static initial_df1b2params **  varsptr;  // this should be a resizeable
  static initial_df1b2params **  varsptr_sav;  // this should be a resizeable
  static int num_initial_df1b2params;         // array
  static int num_initial_df1b2params_sav;         // array
  virtual void set_value(const dvector&,const int& ii)=0;
  virtual void set_index(int aflag,const int& ii)=0;
  static int set_index(void);
  virtual void set_value(const init_df1b2vector&,const int& ii,
    const df1b2variable&)=0;
  static void reset(const init_df1b2vector&,const df1b2variable&);
  static void reset_all(const dvector&);
  static void reset(const df1b2vector&,const df1b2variable&);
  virtual void add_to_list(void);
  initial_df1b2params(void);
  void set_phase_start(int n){phase_start=n; phase_save=n;}
  virtual void sd_scale(const dvector& d,const dvector& x,const int& ii)=0;
  double get_scalefactor();
  void set_scalefactor(const double);
};

typedef initial_df1b2params * P_INITIAL_DF1B2PARAMS;

/**
 * Description not yet available.
 * \param
 */
class do_naught_kludge
{
};

/**
 * Description not yet available.
 * \param
 */
class df1b2_init_vector : public df1b2vector, public initial_df1b2params
{
public:
  virtual ~df1b2_init_vector() {;}

  virtual void sd_scale(const dvector& d,const dvector& x,const int& ii);
  void set_phase_start(int n){phase_start=n; phase_save=n;}
  virtual void set_value(const dvector& x,const int& _ii);
  virtual void set_value(const init_df1b2vector& x,const int& _ii,
    const df1b2variable& pen);
  void allocate(int min, int max,int phase_start, const adstring& s="unnamed");
  void allocate(int min, int max,const adstring& s="unnamed");
  virtual void set_index(int aflag,const int& ii);
};

/**
 * Description not yet available.
 * \param
 */
class df1b2_init_matrix : public df1b2matrix, public initial_df1b2params
{
public:
  virtual void sd_scale(const dvector& d,const dvector& x,const int& ii);

  inline void allocate(int rmin,int rmax,const index_type& cmin,
    const index_type& cmax,int ps,const char * s)
  {
    set_phase_start(ps);
    df1b2matrix::allocate(rmin,rmax,cmin,cmax,s);
  }

  inline void allocate(int rmin,int rmax,const index_type& cmin,
    const index_type& cmax,const char * s)
  {
    df1b2matrix::allocate(rmin,rmax,cmin,cmax,s);
  }

  inline void allocate(int rmin,int rmax,int cmin,int cmax)
  {
    df1b2matrix::allocate(rmin,rmax,cmin,cmax);
  }
  inline void allocate(int rmin,int rmax,int cmin,int cmax,int ps,
    const char * s)
  {
    set_phase_start(ps);
    df1b2matrix::allocate(rmin,rmax,cmin,cmax,s);
  }
  inline void allocate(int rmin,int rmax,int cmin,int cmax,const char * s)
  {
    df1b2matrix::allocate(rmin,rmax,cmin,cmax,s);
  }
  inline void allocate(int rmin, int rmax, int cmin, int cmax, double, double,
    const char* s)
  {
    df1b2matrix::allocate(rmin,rmax,cmin,cmax,s);
  }
  void set_phase_start(int n){phase_start=n; phase_save=n;}
  virtual void set_value(const dvector& x,const int& _ii);
  virtual void set_value(const init_df1b2vector& x,const int& _ii,
    const df1b2variable& pen);
  virtual void set_index(int aflag,const int& ii);
};


/**
 * Description not yet available.
 * \param
 */
class df1b2_init_number : public df1b2variable, public initial_df1b2params
{
  static do_naught_kludge do_naught_kludge_a;
public:
  virtual void sd_scale(const dvector& d,const dvector& x,const int& ii);
  virtual int & get_ind_index(void) { return ind_index; }
  void set_phase_start(int n){phase_start=n; phase_save=n;}
  virtual void set_value(const dvector& x,const int& _ii);
  virtual void set_value(const init_df1b2vector&,const int& ii,
    const df1b2variable&);
  virtual void set_index(int aflag,const int& ii);

  void allocate(const adstring&);
  void allocate(int,const adstring&);
  df1b2_init_number();
  void operator = (const df1b2variable& _x);
};

/**
 * Description not yet available.
 * \param
 */
class df1b2_init_number_vector
{
  df1b2_init_number * v;
  int index_min;
  int index_max;
  double_index_type * it;
public:
  df1b2_init_number_vector();

#if defined(OPT_LIB)
   df1b2_init_number& operator [] (int i) { return v[i];}
   df1b2_init_number& operator () (int i) { return v[i];}
#else
   df1b2_init_number& operator [] (int i);
   df1b2_init_number& operator () (int i);
#endif
  void allocate(int min1,int max1,const index_type& phase_start,
    const char * s);

  void allocate(int min1,int max1,const char * s);

  int allocated(void) { return (v!=NULL); }
  int indexmin(void) {return (index_min);}
  int indexmax(void) {return (index_max);}
  ~df1b2_init_number_vector();
  void deallocate(void);
};

class df1b2_init_bounded_number;

/**
 * Description not yet available.
 * \param
 */
class df1b2_init_bounded_number :public df1b2_init_number
{
  double minb;
  double maxb;
public:
  void allocate(double _minb,double _maxb,int _phase_start,
    const char * s="UNNAMED");
  virtual void sd_scale(const dvector& d,const dvector& x,const int& ii);

  void allocate(double _minb,double _maxb,const char * s="UNNAMED");
  //void allocate(const ad_double& _minb,const ad_double& _maxb,
   // const char * s="UNNAMED");

  virtual void set_value(const dvector& x,const int& _ii);
  virtual void set_value(const init_df1b2vector& x,const int& _ii,
    const df1b2variable& pen);
};

/**
 * Description not yet available.
 * \param
 */
class df1b2_init_bounded_number_vector
{
  df1b2_init_bounded_number * v;
  int index_min;
  int index_max;
  double_index_type * it;
public:
  //virtual void sd_scale(const dvector& d,const dvector& x,const int& ii);
  df1b2_init_bounded_number_vector();

#if defined(OPT_LIB)
   df1b2_init_bounded_number& operator [] (int i) { return v[i];}
   df1b2_init_bounded_number& operator () (int i) { return v[i];}
#else
   df1b2_init_bounded_number& operator [] (int i);
   df1b2_init_bounded_number& operator () (int i);
#endif
  void allocate(int min1,int max1, const double_index_type& bmin,
   const double_index_type& bmax, const char * s);

  void allocate(int min1,int max1, const double_index_type& bmin,
   const double_index_type& bmax, const index_type& phase_start,
    const char * s);


  int allocated(void) { return (v!=NULL); }
  int indexmin(void) {return (index_min);}
  int indexmax(void) {return (index_max);}
  ~df1b2_init_bounded_number_vector();
  void deallocate(void);
};

/**
 * Description not yet available.
 * \param
 */
class df1b2_init_bounded_vector : public df1b2_init_vector
{
protected:
  double minb;
  double maxb;
public:
  virtual void sd_scale(const dvector& d,const dvector& x,const int& ii);
  void allocate(int,int,double,double,int,const char *);
  void allocate(int,int,double,double,const char *);
  void allocate(int,int,double,double);
  //void allocate(int,int);
  virtual void set_value(const dvector& x,const int& _ii);
  virtual void set_value(const init_df1b2vector& x,const int& _ii,
    const df1b2variable& pen);
  inline double getminb(void){return minb;}
  inline double getmaxb(void){return maxb;}
};

class re_df1b2_init_bounded_vector;

/**
 * Description not yet available.
 * \param
 */
class random_effects_bounded_vector_info
{
  re_df1b2_init_bounded_vector * pv;
  int i;
public:
  random_effects_bounded_vector_info
    ( re_df1b2_init_bounded_vector * _pv,int _i) : pv(_pv), i(_i) {}
  friend class funnel_init_df1b2variable;
  friend class df1b2variable;
  virtual void set_value(const init_df1b2vector& x,const int& _ii,
    const df1b2variable& pen);
};

/**
 * Description not yet available.
 * \param
 */
class re_df1b2_init_bounded_vector : public df1b2_init_bounded_vector
{
public:
  random_effects_bounded_vector_info operator () (int i)
  {
    return random_effects_bounded_vector_info(this,i);
  }
  virtual void set_value(const init_df1b2vector& x,const int& _ii,
    const df1b2variable& pen);
  virtual void set_value(const dvector& x,const int& _ii);
  re_df1b2_init_bounded_vector(void);
};

/**
 * Description not yet available.
 * \param
 */
class df1b2_init_bounded_matrix : public df1b2_init_matrix
{
protected:
  double minb;
  double maxb;
public:
  virtual void sd_scale(const dvector& d,const dvector& x,const int& ii);
  void allocate(int,int,int,int,double,double,int,const char *);
  void allocate(int,int,const index_type& ,const index_type& ,double,double,int,
    const char *);
  void allocate(int,int,int,int,double,double,const char *);
  void allocate(int,int,const index_type& ,const index_type& ,double,double,
    const char *);
  void allocate(int,int,int,int,double,double);
  //void allocate(int,int);
  virtual void set_value(const dvector& x,const int& _ii);
  virtual void set_value(const init_df1b2vector& x,const int& _ii,
    const df1b2variable& pen);
};

/**
 * Description not yet available.
 * \param
 */
class df1b2_init_bounded_dev_vector : public df1b2_init_bounded_vector
{
public:
  virtual void set_value(const dvector& x,const int& _ii);
  virtual void set_value(const init_df1b2vector& x,const int& _ii,
    const df1b2variable& pen);
};

void set_value(const df1b2variable& u,const init_df1b2vector& x,const int& _ii,
  double fmin,double fmax,const df1b2variable& fpen);

void set_value(const df1b2variable& u,const init_df1b2vector& x,const int& _ii,
  double fmin,double fmax,const df1b2variable& fpen,double s);

df1b2variable boundp(const df1b2variable& x, double fmin, double fmax);
df1b2variable boundp(const df1b2variable& x, double fmin, double fmax,
  const df1b2variable& _fpen);
df1b2variable boundp(const df1b2variable& x, double fmin, double fmax,
  const df1b2variable& _fpen,double s);

  ostream& operator << (const ostream& _os, const df1b2variable& _x);
  ostream& operator << (const ostream& _os, const df1b2vector& _x);
  ostream& operator << (const ostream& _os, const df1b2matrix& _x);

  class re_objective_function_value : public df1b2variable
  {
  public:
    static re_objective_function_value * pobjfun;
    static double fun_without_pen;
    re_objective_function_value(void);
    ~re_objective_function_value();
    re_objective_function_value& operator = (const df1b2variable& v);
    re_objective_function_value& operator = (double v);
    void allocate(void);
    void allocate(const char *);
  };

df1b2variable posfun(const df1b2variable&x,const double eps);
df1b2variable posfun2(const df1b2variable&x,const double eps,
  const df1b2variable& _pen);
df1b2variable posfun(const df1b2variable&x,const double eps,
  const df1b2variable& _pen);

/**
 * Description not yet available.
 * \param
 */
inline df1b2variable operator - (const df1b2variable& x)
{
  return -double(1.0)*x;
}

/**
 * Description not yet available.
 * \param
 */
inline df1b2vector operator - (const df1b2vector& x)
{
  return -double(1.0)*x;
}

df1b2variable gamma_density(const df1b2variable& _x,double r, double mu);
df1b2variable gamma_density(const df1b2variable& _x,const df1b2variable& _r,
  const  df1b2variable& _mu);

df1b2variable log_gamma_density(const df1b2variable& _x,double r, double mu);
df1b2variable log_gamma_density(const df1b2variable& _x,const df1b2variable& _r,
  const  df1b2variable& _mu);


df1b2variable log_negbinomial_density(double x,const df1b2variable& mu,
  const df1b2variable& tau);

df1b2variable log_density_poisson(double x,const df1b2variable& mu);

ostream& operator << (const ostream& ostr,const df1b2variable& z);
ostream& operator << (const ostream& ostr,const df1b2vector& z);
ostream& operator << (const ostream& ostr,const df1b2matrix& z);
ostream& operator << (const ostream& ostr,const df1b2_init_number_vector& z);
ostream& operator << (const ostream& ostr,const init_df1b2vector& z);
ostream& operator << (const ostream& ostr,
  const df1b2_init_bounded_number_vector& z);

class adkludge1;


/**
 * Description not yet available.
 * \param
 */
  class df1b2_header_ptr_vector
  {
    int index_min;
    int index_max;
    df1b2_header ** v;
  public:
    df1b2_header_ptr_vector(int mmin,int mmax);
    ~df1b2_header_ptr_vector();
    inline df1b2_header * & operator () (int i) { return *(v+i); }
    inline df1b2_header * & operator [] (int i) { return *(v+i); }
    int indexmin(void) {return index_min;}
    int indexmax(void) {return index_max;}
  };

/**
 * Description not yet available.
 * \param
 */
  class double_ptr_vector
  {
    int index_min;
    int index_max;
    double ** v;
  public:
    double_ptr_vector(int mmin,int mmax);
    ~double_ptr_vector();
    inline double * & operator () (int i) { return *(v+i); }
    inline double * & operator [] (int i) { return *(v+i); }
    int indexmin(void) {return index_min;}
    int indexmax(void) {return index_max;}
  };

int active(const df1b2_init_vector& x);
int active(const df1b2_init_number& x);
int active(const df1b2_init_matrix& x);
//int active(const df1b2_init_bounded_vector& x);

//int active (const df1b2_init_vector &);
//int active(const initial_df1b2params& x);
//int active(const df1b2vector& x);
//int active(const df1b2matrix& x);

double evaluate_function_quiet(const dvector& x,function_minimizer * pfmin);
double evaluate_function(const dvector& x,function_minimizer * pfmin);
double evaluate_function(double& fval,const dvector& x,
  function_minimizer * pfmin);
double evaluate_function(double& fval,const dvector& x,const dvector&,
  function_minimizer * pfmin);


double evaluate_function_no_derivatives(const dvector& x,
  function_minimizer * pfmin);

#include <df1b2fnl.h>

int allocated(const df1b2_init_vector&);
int allocated(const df1b2vector&);
int allocated(const df1b2_init_matrix&);
#include <df3fun.h>

/*
df1b2variable betai(const df1b2variable & _a, const df1b2variable & _b,
		     const df1b2variable & _x);
df1b2variable betai(const df1b2variable & _a, const df1b2variable & _b,
		     double _x);
*/

df1b2variable betai(const df1b2variable& a, const df1b2variable& b,
  double x, int maxit=100);

double do_gauss_hermite_block_diagonal(const dvector& x,
  const dvector& u0,const dmatrix& Hess,const dvector& _xadjoint,
  const dvector& _uadjoint,const dmatrix& _Hessadjoint,
  function_minimizer * pmin);

double do_gauss_hermite_block_diagonal_multi(const dvector& x,
  const dvector& u0,const dmatrix& Hess,const dvector& _xadjoint,
  const dvector& _uadjoint,const dmatrix& _Hessadjoint,
  function_minimizer * pmin);

double calculate_importance_sample_block_diagonal(const dvector& x,
  const dvector& u0,const dmatrix& Hess,const dvector& _xadjoint,
  const dvector& _uadjoint,const dmatrix& _Hessadjoint,
  function_minimizer * pmin);

double calculate_importance_sample_block_diagonal_option2(const dvector& x,
  const dvector& u0,const dmatrix& Hess,const dvector& _xadjoint,
  const dvector& _uadjoint,const dmatrix& _Hessadjoint,
  function_minimizer * pmin);

double calculate_importance_sample_block_diagonal_option_antithetical
  (const dvector& x,const dvector& u0,const dmatrix& Hess,
  const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin);

double calculate_importance_sample_block_diagonal_funnel(const dvector& x,
  const dvector& u0,const dmatrix& Hess,const dvector& _xadjoint,
  const dvector& _uadjoint,const dmatrix& _Hessadjoint,
  function_minimizer * pmin);

double calculate_importance_sample(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin);

double calculate_importance_sample_shess(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin);
double calculate_importance_sample(const dvector& x,const dvector& u0,
  const banded_symmetric_dmatrix& bHess,const dvector& _xadjoint,
  const dvector& _uadjoint,
  const banded_symmetric_dmatrix& _bHessadjoint,function_minimizer * pmin);

dvector evaluate_function_with_quadprior(const dvector& x,int usize,
  function_minimizer * pfmin);

/**
 * Description not yet available.
 * \param
 */
class style_flag_class
{
public:
  int old_style_flag;
  virtual void set_old_style_flag(void)=0;
  //style_flag_class(void) {set_old_style_flag();}
};

/**
 * Description not yet available.
 * \param
 */
class quadratic_prior : public style_flag_class
{
  dmatrix * pMinv;
  dvar_matrix * dfpMinv;
  dvar_vector * pu;
  int xmyindex;
public:
  static int qflag;
  static quadratic_prior * ptr[]; // this should be a resizeable array
  static void get_M_calculations(void);
  static void cleanup_pMinv();
  static void cleanup_dfpMinv();
  static int num_quadratic_prior;
  static const int max_num_quadratic_prior;
  void add_to_list(void);
public:
  static int in_qp_calculations;
  int get_offset(int xs);
  int get_myindex(void) { return xmyindex;}
  static quadratic_prior * get_ptr(int i){ return ptr[i];}
  void operator = (const dvar_matrix &);
  void operator = (const dmatrix &);
  static int get_in_qp_calculations() { return in_qp_calculations; }
  static int get_num_quadratic_prior(void) { return num_quadratic_prior;}
  static dvariable get_quadratic_priors(void);
  dvariable get_function(void);
  quadratic_prior(void);
  ~quadratic_prior(void);
  void allocate(const dvar_vector & _u,const char * s);
  void allocate(const dvar_vector & _u);
  void allocate(const dvar_matrix & _M, const dvar_vector & _u,const char * s);
  void allocate(const dvar_matrix & _M, const dvar_vector & _u);
  //dmatrix get_cHessian(void);
  void get_cHessian(dmatrix,int);
  void get_cHessian(dvar_matrix,int);
  void get_cHessian_from_vHessian(dmatrix ,int);
  void get_vHessian(dvar_matrix ,int);
  void get_cgradient(dvector,int);
  dvar_matrix get_Hessian(void);
  dvar_vector get_gradient(void);
  static dvar_vector get_gradient_contribution(void);
  static dvar_matrix get_Hessian_contribution(void);
  static void get_cgradient_contribution(dvector,int);
  static void get_cHessian_contribution(dmatrix,int);
  static void get_vHessian_contribution(dvar_matrix  ,int );
  static void get_cHessian_contribution_from_vHessian(dmatrix,int);
  friend class df1b2quadratic_prior;
  virtual void get_cM(void)=0;
};

/**
 * Description not yet available.
 * \param
 */
class df1b2quadratic_prior : public style_flag_class
{
  ivector * index;
  df1b2matrix * M;
  dmatrix * CM;
public:
  dmatrix * Lxu;
  df1b2_init_vector * pu;
  int xmyindex;
  static df1b2quadratic_prior * ptr[]; // this should be a resizeable array
  static int num_quadratic_prior;
  static const int max_num_quadratic_prior;
  void add_to_list(void);
public:
  static df1b2quadratic_prior * get_ptr(int i){ return ptr[i];}
  unsigned int num_active_parameters;
  unsigned int get_num_active_parameters(void) { return num_active_parameters; }
  int get_myindex(void) { return xmyindex;}
  void operator = (const df1b2matrix &);
  void operator = (const dmatrix &);
  static int get_num_quadratic_prior(void) { return num_quadratic_prior;}
  static dvariable get_quadratic_priors(void);
  df1b2variable get_function(void);
  df1b2quadratic_prior(void);
  ~df1b2quadratic_prior(void);
  void allocate(const df1b2_init_vector & _u,const char * s);
  void allocate(const df1b2_init_vector & _u);
  void allocate(const df1b2matrix & _M, const df1b2_init_vector & _u,
    const char * s);
  void allocate(const df1b2matrix & _M, const df1b2_init_vector & _u);
  void allocate(const dvar_matrix & _M, const dvar_vector & _u,const char * s);
  void allocate(const dvar_matrix & _M, const dvar_vector & _u);
  dmatrix get_cHessian(void);
  dvector get_cgradient(void);
  dvar_matrix get_Hessian(void);
  dvar_vector get_gradient(void);
  static dvar_vector get_gradient_contribution(void);
  static dvar_matrix get_Hessian_contribution(void);
  static dvector get_cgradient_contribution(void);
  static dmatrix get_cHessian_contribution(void);
  static void get_Lxu_contribution(dmatrix&);
  virtual void get_Lxu(dmatrix&)=0;
  friend class quadratic_prior;
  friend class df1b2_parameters;
};

/**
 * Description not yet available.
 * \param
 */
class normal_quadratic_prior : public quadratic_prior
{
  virtual void set_old_style_flag(void);
public:
  normal_quadratic_prior(void);
  void operator = (const dvar_matrix & M);
};

/**
 * Description not yet available.
 * \param
 */
class normal_df1b2quadratic_prior : public df1b2quadratic_prior
{
  virtual void set_old_style_flag(void);
public:
  void operator = (const df1b2matrix & M);
  normal_df1b2quadratic_prior(void);
};

/**
 * Description not yet available.
 * \param
 */
class quadratic_re_penalty : public quadratic_prior
{
  virtual void set_old_style_flag(void);
public:
  quadratic_re_penalty(void);
  void operator = (const dvar_matrix & M);
  void operator = (const dmatrix & M);
};

/**
 * Description not yet available.
 * \param
 */
class df1b2quadratic_re_penalty : public df1b2quadratic_prior
{
  virtual void set_old_style_flag(void);
public:
  void operator = (const df1b2matrix & M);
  void operator = (const dmatrix & M);
  df1b2quadratic_re_penalty(void);
};

dvar_vector solve(const named_dvar_matrix &,const random_effects_vector&);

/**
 * Description not yet available.
 * \param
 */
class constant_quadratic_re_penalty : public quadratic_prior
{
  virtual void set_old_style_flag(void);
public:
  constant_quadratic_re_penalty(void);
  void operator = (const dmatrix & M);
};

/**
 * Description not yet available.
 * \param
 */
class constant_df1b2quadratic_re_penalty : public df1b2quadratic_prior
{
  virtual void set_old_style_flag(void);
public:
  void operator = (const dmatrix & M);
  constant_df1b2quadratic_re_penalty(void);
};

df1b2vector solve(df1b2matrix& M,df1b2vector& v,const df1b2variable& ln_det);

df1b2vector solve(df1b2matrix& M,df1b2vector& v,const df1b2variable& ln_det,
  const int& sgn);
df1b2vector lower_triangular_solve(const df1b2matrix& m,const df1b2vector& v);
df1b2vector lower_triangular_solve_trans(const df1b2matrix& m,
  const df1b2vector& v);

//df1b2variable ln_det(df1b2matrix& M);
// line above replaced with line below based on issue #37
df1b2variable ln_det(const df1b2matrix & m1);

df1b2variable ln_det(df1b2matrix& M,int & sgn);

//df1b2vector solve(df1b2matrix& M,df1b2vector& v);

df1b2matrix expm(const df1b2matrix & A);
df1b2matrix solve(const df1b2matrix& aa,const df1b2matrix& tz,
  df1b2variable ln_unsigned_det,df1b2variable& sign);
df1b2matrix solve(const df1b2matrix& aa,const df1b2matrix& tz);
df1b2vector solve(const df1b2matrix& aa,const df1b2vector& z,
  const df1b2variable& ld, df1b2variable& sign);

void check_pool_depths();

df1b2variable lower_triangular_ln_det(const df1b2matrix& m);
df1b2variable lower_triangular_ln_det(const df1b2matrix& m,int& sgn);
df1b2variable bounder(const df1b2variable&  x,double min,double max,
  double scale);

df1b2variable inv_cumd_beta_stable(const df1b2variable& a,
  const df1b2variable& b,const df1b2variable& x,double eps=1.e-7);

df1b2variable bounded_cumd_norm(const df1b2variable& _x,double beta);
df1b2variable cumd_norm(const df1b2variable& _x);
df1b2variable inv_cumd_exponential(const df1b2variable& y);
df1b2variable cumd_exponential(const df1b2variable& x);
extern int make_sure_df1b2fun_gets_linked;

df1b2variable inv_cumd_normal_mixture(const df1b2variable& _x,double _a);
df1b2variable inv_cumd_normal_logistic_mixture(const df1b2variable& _x,
  double _a);

df1b2variable beta_deviate(const df1b2variable& _x,const df1b2variable& _a,
  const df1b2variable& _b,double eps=1.e-7);
df1b2variable robust_normal_logistic_mixture_deviate(const df1b2variable& x,
  double spread=3.0);
df1b2variable robust_normal_mixture_deviate(const df1b2variable& x,
  double spread=3.0);

df1b2variable gamma_deviate(const df1b2variable& _x,const df1b2variable& _a);
df1b2variable inv_cumd_gamma(const df1b2variable& _y,const df1b2variable& _a);
double inv_cumd_gamma(double y,double _a);

df1b2variable inv_cumd_cauchy(const df1b2variable& n);
df1b2variable inv_cumd_t(const df1b2variable& n,const df1b2variable&  u,
  double eps=1.e-7);

/**
 * Description not yet available.
 * \param
 */
  class df1b2function_tweaker
  {
    double mult;
    double eps;
    dvector coffs;
  public:
    df1b2function_tweaker(double eps,double mult);
    df1b2variable operator () (const df1b2variable&);
  };

df1b2vector posfun(const df1b2vector& x,double eps,
  const df1b2variable& _pen);

df1b2variable norm_to_gamma(const df1b2variable & v,const df1b2variable& alpha,
  double bound=0.999999);

void print_is_diagnostics(laplace_approximation_calculator *lapprox);

  ofstream &  operator << (const ofstream& _s,const nested_calls_shape& m);

  df1b2variable log_der_logistic(double a,double b,const df1b2variable& x);
  df1b2variable logistic(double a,double b,const df1b2variable& x);
  df1b2variable dflogistic(double a,double b,const df1b2variable& x);

  df1b2variable dfposfun(const df1b2variable& x,const double eps);
  void ADMB_getcallindex(const df1b2variable& x);
  void ADMB_getcallindex(const df1b2vector& x);
  void ADMB_getcallindex(const df1b2matrix& x);

df1b2variable asin(const df1b2variable& xx);
#endif //!defined(__DF1B2FUN__)
