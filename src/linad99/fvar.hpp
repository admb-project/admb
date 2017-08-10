/**
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
 *
 */
#ifndef FVAR_HPP
#define FVAR_HPP
/** \file fvar.hpp
AUTODIF classes.
Class definitions for reverse mode automatic differentiation.
Function prototypes for math functions.
Macro definitions.
*/
#if defined(__MINGW64__)
  #define OFF_T off64_t
  #define LSEEK lseek64
  #if defined(AD_LONG_INT)
    #error "Error: AD_LONG_INT should not be defined."
  #else
    #define AD_LONG_INT long long int
  #endif
#else
  #define OFF_T off_t
  #ifndef _MSC_VER
    #define LSEEK lseek
  #endif
  #if defined(AD_LONG_INT)
    #error "Error: AD_LONG_INT should not be defined."
  #else
    #define AD_LONG_INT long int
  #endif
#endif

#ifdef __OPENCC__
  #define nullptr 0
#endif

#include <math.h>
// Borrow definition of M_PI from GCC
#ifndef M_PI
#   define M_PI 3.14159265358979323846
#endif
#ifndef PI
#   define PI 3.14159265358979323846
#endif

#if defined(__GNUC__) && (__GNUC__ < 3)
  #pragma interface
#endif

#if defined(THREAD_EXPERIMENT)
#   define THREAD_SAFE
#endif

#if defined(THREAD_SAFE)
#   include <pthread.h>
#endif

#ifndef TINY_AD_USE_TINY_VEC
  #define TINY_AD_USE_TINY_VEC 1
  #include <tiny_ad.hpp>
#endif


#define USE_VECTOR_SHAPE_POOL

#if defined(USE_DDOUBLE)
#   include <qd/qd.h>
#   define  double dd_real
    dd_real operator ++(dd_real & d)
    {
       return d += 1.0;
    }

    dd_real pow(const dd_real & d, int i);
    dd_real pow(const dd_real & d, const dd_real &);
#endif

#if defined(__TURBOC__)
#   define __STL_PTHREADS
#   include <k3stl.h>
#   include <pthread_alloc>
#endif

#define  __NUMBERVECTOR__

/** \def ADUNCONST(type,obj)
  Creates a shallow copy of obj that is not CONST
*/
#define ADUNCONST(type,obj) type & obj = (type&) _##obj;

#define  MFCL2_CONSTRUCTORS

#if defined(_ADEXEP)
#   define USE_EXECPTIONS
#endif

#define __USE_IOSTREAM__

#if defined(__BORLANDC__)
  #if (__BORLANDC__  >= 0x0550)
    #include <fcntl.h>
  #endif
#endif

#if defined(__BORLANDC__) || defined (_MSC_VER) || defined(__WAT32__)
#   include <io.h>
#endif

#if !defined(_MSC_VER)
  #include <fcntl.h> // to get fstreambase
  #if !defined(O_BINARY)
    #define O_BINARY 0
  #endif
  #define __GNU__
#endif

#if defined(__DJGPP__)
  #include <dos.h>
  #include <pc.h>
#endif

#ifndef NO_DERIVS
  #define  NO_DERIVS
#endif

// C language function prototypes
extern "C"
{
   typedef int (*fptr) (const char *format, ...);
   extern fptr ad_printf;
   typedef void (*exitptr) (int);
   extern exitptr ad_exit;

   void spdll_exit(int);
}

/**
Holds the data for the prevariable class.

\ingroup BAD
 */
class double_and_int
{
public:
  ///< value of the variable
  double x;

  /**
  Return the value of the variable.

  \return double reference containing the value of the variable.
  */
  inline double &xvalue()
  {
    return x;
  }
};


// "forward" class definitions
class banded_symmetric_dvar_matrix;
class banded_symmetric_dmatrix;
class banded_lower_triangular_dmatrix;
class banded_lower_triangular_dvar_matrix;
class random_number_generator;
class ad_integer;
class index_type;
class dlink;
class dvector;
class dmatrix;
class tdmatrix;
class imatrix;
class prevariable;
class dvariable;
class dvar_vector;
class ivector;
class lvector;
class dvar_matrix;
class uostream;
class uistream;
class arr_link;
class arr_list;
class d3_array;
class d4_array;
class d5_array;
class d6_array;
class d7_array;
class dvar3_array;
class dvar4_array;
class dvar5_array;
class dvar6_array;
class dvar7_array;
class dlist;
class indvar_offset_list;
class dvar_matrix_position;
class dmatrix_position;
class d3_array_position;
class dvector_position;
class vector_shape;
class ivector_position;
class kkludge_object;
class dvar_vector_position;
dvector restore_dvar_vector_derivatives(void);
class gradient_structure;
class dependent_variables_information;
class vector_shapex;
class predvar_vector;
class independent_variables;

#if defined(__GNUC__) && (__GNUC__ < 3)
  #include <fstream.h>
#elif defined(_MSC_VER) && (_MSC_VER < 1300)
  #include <fstream.h>
#elif defined(__SUNPRO_CC) && (__SUNPRO_CC < 0x5140)
  #include <fstream.h>
#else
  #include <fstream>
#endif

#include <stdio.h>

#if defined(__BORLANDC__)
#   if (__BORLANDC__  < 0x0550)
#      include <fcntl.h> // to get fstreambase
#      include <strstrea.h>
#   else
#      include <strstream>
#   endif
#endif

#if defined(_MSC_VER)
#   if (_MSC_VER < 1300)
#     include <iostream.h>
#     include <strstrea.h>
#   else
#     include <iostream>
#   endif
#   include <stddef.h>
#   include <fcntl.h> // to get fstreambase
#   include <dos.h>
#   undef __ZTC__
#   undef __SUN__
#endif

#ifdef __ZTC__
#   include <fstream.hpp> // to get fstreambase
#   include <iostream.hpp>
#   include <dos.h>
#   undef __SUN__
#endif

#ifdef __SUN__
#   undef __NDPX__
#   include <fstream.h>
#   include <iostream.h>
#   ifndef _FPOS_T_DEFINED
#      ifdef __GNUDOS__
#         if defined(linux) || defined(__ADSGI__)|| defined(__CYGWIN32__)
             typedef long int fpos_t;
#         else
             typedef unsigned long int fpos_t;
#         endif
#         undef __SUN__
          typedef int fpos_t;
#      endif
#      define _FPOS_T_DEFINED
#   endif
#endif

#if defined(__BORLANDC__)
#   if (__BORLANDC__  > 0x0520)
       using std::ofstream;
       using std::ifstream;
#   endif
#endif

#if defined(__cplusplus)
  #include <iostream>
  #include <iomanip>
  #include <sstream>
  #include <istream>
  #include <sstream>
  using std::ofstream;
  using std::ostream;
  using std::ifstream;
  using std::istream;
  using std::istringstream;
  using std::streampos;
  using std::streambuf;
  using std::setw;
  using std::setprecision;
  using std::istringstream;
  using std::ios;
  using std::cerr;
  using std::cin;
  using std::cout;
  using std::endl;
#else
  #include <iomanip.h>
  #include <strstream.h>
#endif

#define BEGIN_MINIMIZATION(nvar, objective_function, ind_vars, gradient, \
cntrl) \
gradient_structure gs; \
while (cntrl.ireturn >= 0) \
{ \
  cntrl.fmin(objective_function,ind_vars,gradient ); \
  if (cntrl.ireturn > 0) \
  {
#define END_MINIMIZATION(nvar,gradient) \
    gradcalc(nvar, gradient); \
  } \
}

void default_evaluation4ind(void);
void default_evaluation(void);
void default_evaluation0(void);
void default_evaluation1(void);
void default_evaluation1m(void);
void default_evaluation2(void);
void default_evaluation3(void);
void default_evaluation4(void);
void default_evaluation4m(void);

void myheapcheck(char *);

void RETURN_ARRAYS_INCREMENT(void);
void RETURN_ARRAYS_DECREMENT(void);

void *farptr_norm(void *);
#ifdef DIAG
long int farptr_tolong(void *);
long int _farptr_tolong(void *);
#endif

class i3_array;

ostream & operator<<(const ostream & ostr, const dmatrix & z);
istream & operator>>(const istream & istr, const dmatrix & z);
uostream & operator<<(const uostream & ostr, const dmatrix & z);
uistream & operator>>(const uistream & istr, const dmatrix & z);

ostream & operator<<(const ostream & ostr, const d3_array & z);
istream & operator>>(const istream & istr, const d3_array & z);
uostream & operator<<(const uostream & ostr, const d3_array & z);
uistream & operator>>(const uistream & istr, const d3_array & z);

ostream & operator<<(const ostream & ostr, const dvar3_array & z);
istream & operator>>(const istream & istr, const dvar3_array & z);
uostream & operator<<(const uostream & ostr, const dvar3_array & z);
uistream & operator>>(const uistream & istr, const dvar3_array & z);

ostream & operator<<(const ostream & ostr, const ivector & z);
istream & operator>>(const istream & istr, const ivector & z);
uostream & operator<<(const uostream & ostr, const ivector & z);
uistream & operator>>(const uistream & istr, const ivector & z);

ostream & operator<<(const ostream & ostr, const lvector & z);
istream & operator>>(const istream & istr, const lvector & z);
uostream & operator<<(const uostream & ostr, const lvector & z);
uistream & operator>>(const uistream & istr, const lvector & z);

ostream & operator<<(const ostream & ostr, const dvector & z);
istream & operator>>(const istream & istr, const dvector & z);
uostream & operator<<(const uostream & ostr, const dvector & z);
uistream & operator>>(const uistream & istr, const dvector & z);

ostream & operator<<(const ostream & ostr, const dvar_vector & z);
istream & operator>>(const istream & istr, const dvar_vector & z);
uostream & operator<<(const uostream & ostr, const dvar_vector & z);
uistream & operator>>(const uistream & istr, const dvar_vector & z);

ostream & operator<<(const ostream & ostr, const dvar_matrix & z);
istream & operator>>(const istream & istr, const dvar_matrix & z);
uostream & operator<<(const uostream & ostr, const dvar_matrix & z);
uistream & operator>>(const uistream & istr, const dvar_matrix & z);


ostream & operator<<(const ostream & ostr, const prevariable & z);
istream & operator>>(const istream & istr, const prevariable & z);
uostream & operator<<(const uostream & ostr, const prevariable & z);
uistream & operator>>(const uistream & istr, const prevariable & z);

ostream & setscientific(const ostream & s);

//ostream& setshowpoint(const ostream& s);

class preshowpoint {};
preshowpoint setshowpoint(void);
ostream & operator <<(const ostream &, preshowpoint);
#if (__BORLANDC__  >= 0x0560)
  #define setfixed() std::fixed
#else
ostream & setfixed(const ostream & s);
class prefixed {};
prefixed setfixed(void);
ostream & operator<<(const ostream &, prefixed);
#endif

#if (__BORLANDC__  >= 0x0560)
  #define setscientific() std::scientific
#else
class prescientific {};
prescientific setscientific(void);
ostream & operator<<(const ostream &, prescientific);
#endif

istream & operator>>(const istream & istr, const imatrix & z);
ostream & operator<<(const ostream & istr, const imatrix & z);
istream & operator>>(const istream & istr, const i3_array & z);
ostream & operator<<(const ostream & istr, const i3_array & z);
class grad_stack;

/**
 Null class to allow specialized function overloads.
 Has no members; does nothing.
 Exists purely to coerce the compiler to generate a specific function call.
 */
class kkludge_object{};


#ifndef _VECTOR_SHAPE
#define _VECTOR_SHAPE
#include <dfpool.h>

/**
 * Description not yet available.
 * \param
 */
class vector_shape_pool:public dfpool
{
public:
  vector_shape_pool();
  vector_shape_pool(const size_t);
};

/**
 * Description not yet available.
 * \param
 */
class ts_vector_shape_pool:public tsdfpool
{
 public:
   ts_vector_shape_pool();
   ts_vector_shape_pool(int);
};
#endif

/**
 * Description not yet available.
 * \param
 */
class vector_shape
{
 public:
#if defined(USE_VECTOR_SHAPE_POOL)
   static vector_shape_pool *xpool;
   void *operator new(size_t);
   void operator delete(void *ptr, size_t)
   {
      xpool->free(ptr);
   }
#endif
   unsigned int ncopies;
   void shift(int min);
   int index_min;
   int index_max;
 private:
   friend class dvector;
   //friend class tdvector;
   friend class subdvector;
   friend class dvar_vector;
   friend class ivector;
   friend class lvector;
   friend class ptr_vector;
 public:
   unsigned int decr_ncopies(void)
   {
      return ncopies == 0 ? 0 : --ncopies;
   }
   unsigned int get_ncopies(void)
   {
      return ncopies;
   }
   unsigned int incr_ncopies(void)
   {
      return ++ncopies;
   }
   vector_shape(int lb, int lu)
   {
      index_min = lb;
      index_max = lu;
      ncopies = 0;
   }
   int indexmin() const
   {
      return index_min;
   }
   int indexmax() const
   {
      return index_max;
   }
};


/**
 * Description not yet available.
 * \param
 */
class ptr_vector
{
  void **v;
  vector_shape *shape;

public:
  ptr_vector();
  ptr_vector(const ptr_vector & t);
  ptr_vector(int ncl, int ncu);
  ~ptr_vector();

  // returns the minimum allowable index
  int indexmin() const
  {
    return shape->index_min;
  }
  // returns the maximum allowable index
  int indexmax() const
  {
    return shape->index_max;
  }
  // returns the maximum allowable index
  int size() const
  {
    return shape->index_max - shape->index_min + 1;
  }

  void shift(int min);
  void allocate(int, int);
  //operator void ** ();
  void *&operator[] (int i);
  void *&operator() (int i);
  //void*& elem(int i);
  void *&elem(int i)
  {
    return (*(v + i));
  }
  int operator!(void) const
  {
    return (shape == NULL);
  }
  int operator() (void) const
  {
    return (shape != NULL);
  }

  ptr_vector& operator=(const ptr_vector& t);
  void initialize();
};

/**
 * Description not yet available.
 * \param
 */
class preivector
{
   ivector *p;
   int lb;
   int ub;
   inline preivector(ivector * _p, int _lb, int _ub)
   {
      p = _p;
      lb = _lb, ub = _ub;
   }
   friend class ivector;
};

#include <ivector.h>

/**
 * Description not yet available.
 * \param
 */
class lvector_position
{
   int min;
   int max;
   int *v;
 public:
   lvector_position(void);
   lvector_position(const lvector & v);
   lvector_position(const lvector_position & dvp);
};

/**
 * Description not yet available.
 * \param
 */
class lvector
{
   AD_LONG_INT *v;
   vector_shape *shape;

 public:
   int operator!(void) const
   {
      return (shape == NULL);
   }

   inline AD_LONG_INT & elem(int i)
   {
      return (v[i]);
   }
   inline const AD_LONG_INT & elem(int i) const
   {
      return v[i];
   }
   // returns the minimum allowable index
   int indexmin() const
   {
      return shape->index_min;
   }
   // returns the maximum allowable index
   int indexmax() const
   {
      return shape->index_max;
   }
   // returns the maximum allowable index
   int size() const
   {
      return shape ? shape->index_max - shape->index_min + 1 : 0;
   }
   lvector& shift(int min);

   void fill(const char *s);
   void fill_seqadd(const AD_LONG_INT &, const AD_LONG_INT &);
   void fill_multinomial(const int &seed, const dvector & p);
   void fill_multinomial(const random_number_generator & rng,
     const dvector & p);

   //lvector(unsigned int sz); //makes an array [0..sz]

   lvector(const lvector &);

   lvector(const dvector &);

   lvector(const ivector &);

   lvector(void);

   lvector(int ncl, int ncu);
   void allocate(int ncl, int ncu);
   void allocate(const lvector &);
   void allocate(void);
   // makes an array [ncl..ncu]

   lvector(unsigned int sz, AD_LONG_INT * x);

   operator   AD_LONG_INT *();

   ~lvector();

   void write_on(const ostream & s) const;

   void read_from(const istream & s);

   void write_on(const uostream & s) const;

   void read_from(const uistream & s);

   AD_LONG_INT& operator[](int i);
   AD_LONG_INT& operator()(int i);
   const AD_LONG_INT& operator[](int i) const;
   const AD_LONG_INT& operator()(int i) const;

   lvector operator()(const ivector& indexes);

   lvector & operator=(const lvector & t);

   void initialize(void);
   friend class lmatrix;
};

#ifdef OPT_LIB
inline AD_LONG_INT& lvector::operator[](int i)
{
  return v[i];
}
inline AD_LONG_INT& lvector::operator()(int i)
{
  return v[i];
}
inline const AD_LONG_INT& lvector::operator[](int i) const
{
  return v[i];
}
inline const AD_LONG_INT& lvector::operator()(int i) const
{
  return v[i];
}
#endif

AD_LONG_INT sum(const lvector &);

/**
 * Description not yet available.
 * \param
 */
class dependent_variables_information
{
   int max_num_dependent_variables;
   int depvar_count;
   ptr_vector grad_buffer_position;
   lvector cmpdif_buffer_position;
   lvector grad_file_position;
   lvector cmpdif_file_position;
  ivector grad_file_count;
  ivector cmpdif_file_count;
   dependent_variables_information(int ndv);
   friend class gradient_structure;
};
dvar_vector_position restore_dvar_vector_position(void);
dvector restore_dvar_vector_value(const dvar_vector_position & tmp);
void arr_free(double_and_int *);
double_and_int *arr_new(unsigned int sz);

#include <gradient_structure.h>

void jacobcalc(int nvar, const dmatrix & g);
void jacobcalc(int nvar, const ofstream & ofs);
void jacobcalc(int nvar, const uostream & ofs);

#if defined(__BORLANDC__ )
#if defined(__GNUC__)
#if (__GNUC__ < 3)
#pragma interface
#endif
#else
#pragma interface
#endif
#endif

//class dvect_ptr_ptr { dvector **m; };

/**
Node in dlist
*/
class dlink
{
  double_and_int di;
  dlink* prev;

public:
  dlink* previous() const
  {
    return prev;
  }

  //access function
  inline double_and_int* get_address()
  {
    return &di;
  }

  //friend tempvar();
  //friend class prevariable;
  //friend class tempvar;
  friend class dlist;
  friend void gradcalc(int nvar, const dvector & g);
  friend void slave_gradcalc(void);
  friend void gradloop();
  friend double_and_int *gradnew();
  friend void allocate_dvariable_space(void);
};
/**
Link list
*/
class dlist
{
  dlink* last;
  unsigned int nlinks;
  dlink** dlink_addresses;
  char* ddlist_space;
  double* variables_save;

public:
  // constructor
  dlist();
  // destructor
  ~dlist();
  // create a new link
  dlink* create();
  // append link
  dlink* append(dlink* link);
  dlink* last_remove();
  void initialize();
  void save_variables();
  void restore_variables();

  // check list integrity
  void check_list(void);
  size_t total_addresses() const;

  friend double_and_int *gradnew();
  friend void df_check_derivative_values(void);
  friend void df_check_derivative_values_indexed(void);
  friend void df_check_derivative_values_indexed_break(void);
  friend void funnel_gradcalc(void);
  friend void slave_gradcalc(void);
  friend void gradcalc(int nvar, const dvector& g);
  friend void gradloop();
  friend void gradient_structure::restore_variables();
  friend void gradient_structure::save_variables();
  friend void gradient_structure::jacobcalc(int nvar,
    const dmatrix& jac);
  friend void allocate_dvariable_space(void);
  //friend void gradient_structure::funnel_jacobcalc(void);
  friend void gradient_structure::jacobcalc(int nvar,
    const ofstream& jac);
  friend void gradient_structure::jacobcalc(int nvar,
    const uostream& jac);
  friend void funnel_derivatives(void);
};

class indvar_offset_list;

/**
  Holds derivative information for arithmetic operators and math library
  functions.
  Used to record gradient information on the gradient stack for processing
  by gradcalc().
 */
class grad_stack_entry
{
 public:
   ///< Pointer to function (if any) to be used for derivative calculation
   void (*func) (void);
   double *dep_addr;    ///< Pointer to dependent variable
   double *ind_addr1;   ///< Pointer to first independent variable
   double mult1;        ///< First mutiplicand in chain rule multipication
   double *ind_addr2;   ///< Pointer to second independent variable
   double mult2;        ///< Second mutiplicand in chain rule multipication
 public:
   friend void gradcalc(int nvar, const dvector & g);
   friend void slave_gradcalc(void);
   friend void gradloop();
   friend void default_evaluation(void);
   friend class grad_stack;
   friend void gradient_structure::jacobcalc(int nvar,
     const dmatrix & jac);
   //friend void gradient_structure::funnel_jacobcalc(void);
};
void default_evaluation3ind(void);

/**
 * Description not yet available.
 * \param
 */
class grad_stack
{
   grad_stack_entry *true_ptr_first;
   grad_stack_entry *ptr_first;
   grad_stack_entry *ptr_last;
#ifdef __BORLANDC__
   long int length;
   long int true_length;
#else
   size_t length;
   size_t true_length;
#endif
 public:
   grad_stack_entry * ptr;
 private:
   //lvector * table;
   // js
   int _GRADFILE_PTR;  // should be int gradfile_handle;
   int _GRADFILE_PTR1;  // should be int gradfile_handle;
   int _GRADFILE_PTR2;  // should be int gradfile_handle;
   int _VARSSAV_PTR;  // should be int gradfile_handle;
   char gradfile_name[61];
   char gradfile_name1[61];
   char gradfile_name2[61];
   char var_store_file_name[61];
   void create_gradfile();
#ifdef __BORLANDC__
   long end_pos;
   long end_pos1;
   long end_pos2;
#else
   OFF_T end_pos;
   OFF_T end_pos1;
   OFF_T end_pos2;
#endif
   //dmatrix *table;
 public:
   friend void gradcalc(int nvar, const dvector & g);
   friend void slave_gradcalc(void);
   friend void funnel_gradcalc(void);
   friend void default_evaluation(void);
   friend void default_evaluation3ind(void);
   friend void reset_gradient_stack(void);
   friend void default_evaluation4ind(void);
   friend void grad_chk(void);
   friend void gradloop();
   friend void cleanup_temporary_files();
   ostream & operator  <<(grad_stack);
   void print();
   grad_stack();
   ~grad_stack();
   void write_grad_stack_buffer(void);

   void set_gradient_stack(void (*func) (void),
     double *dep_addr, double *ind_addr1 = NULL, double mult1 = 0,
     double *ind_addr2 = NULL, double mult2 = 0);

   void set_gradient_stack(void (*func) (void),
     double *dep_addr, double *ind_addr1,
     double *ind_addr2);


   void set_gradient_stack0(void (*func) (void), double *dep_addr);

   void set_gradient_stack1(void (*func) (void),
     double *dep_addr, double *ind_addr1);

   void set_gradient_stack2(void (*func) (void),
     double *dep_addr, double *ind_addr1, double mult1);

   void set_gradient_stack4(void (*func) (void),
     double *dep_addr, double *ind_addr1,
     double *ind_addr2);

   void set_gradient_stack(void (*func) (void),
     double *dep_addr, double *ind_addr1,
     double mult1, double *ind_addr2, double mult2,
     double *ind_addr3, double mult3,
     double *ind_addr4, double mult4);

   void set_gradient_stack(void (*func) (void),
     double *dep_addr, double *ind_addr1,
     double mult1, double *ind_addr2, double mult2,
     double *ind_addr3, double mult3);

   int read_grad_stack_buffer(OFF_T & lpos);
   void set_gradient_stack(void (*ptr) (void));
   void set_gbuffer_pointers(void);
   //js
   void increment_current_gradfile_ptr(void);
   int decrement_current_gradfile_ptr(void);
   //void open_gradfile();
   //void close_gradfile();
#ifdef _MSC_VER
   int gradfile_handle();
#else
   int &gradfile_handle();
#endif
   char *get_gradfile_name();
   friend class gradient_structure;
   //int get_ngradfiles();
};


#ifdef OPT_LIB
/**
 * Description not yet available.
 * \param
 */
inline void grad_stack::set_gradient_stack(void (*func) (void),
  double *dep_addr, double *ind_addr1, double mult1, double *ind_addr2,
  double mult2)
{
#ifdef NO_DERIVS
   if (!gradient_structure::no_derivatives)
   {
#endif
#     if defined(MYDEBUG)
      int wrote_buffer = 0;
#     endif
      if (ptr > ptr_last)
      {
        // current buffer is full -- write it to disk and reset pointer
        // and counter
        this->write_grad_stack_buffer();
#     if defined(MYDEBUG)
        wrote_buffer = 1;
#     endif
      }
#     if defined(MYDEBUG)
      if (wrote_buffer == 1)
      {
        cout << "WROTE BUFFER" << endl;
      }
#     endif
      ptr->func = func;
      ptr->dep_addr = dep_addr;
      ptr->ind_addr1 = ind_addr1;
      ptr->mult1 = mult1;
      ptr->ind_addr2 = ind_addr2;
      ptr->mult2 = mult2;
      ptr++;
#ifdef NO_DERIVS
   }
#endif
}
#else
  //  void grad_stack::set_gradient_stack(void (* func)(void),
   //   double * dep_addr,double * ind_addr1, double mult1, double * ind_addr2,
    //  double mult2);
#endif

/**
 * Description not yet available.
 * \param
 */
inline void grad_stack::set_gradient_stack(void (*func) (void),
  double *dep_addr, double *ind_addr1, double mult1, double *ind_addr2,
  double mult2, double *ind_addr3, double mult3)
{
#ifdef NO_DERIVS
   if (!gradient_structure::no_derivatives)
   {
#endif
      if (ptr > ptr_last)
      {
         // current buffer is full -- write it to disk and reset pointer
         // and counter
         this->write_grad_stack_buffer();
      }
      ptr->func = NULL;
      ptr->dep_addr = dep_addr;
      ptr->ind_addr1 = ind_addr1;
      ptr->mult1 = mult1;
      ptr->ind_addr2 = ind_addr2;
      ptr->mult2 = mult2;
      ptr++;
      if (ptr > ptr_last)
      {
         // current buffer is full -- write it to disk and reset pointer
         // and counter
         this->write_grad_stack_buffer();
      }
      ptr->func = func;
      ptr->ind_addr1 = ind_addr3;
      ptr->mult1 = mult3;
      ptr++;
#ifdef NO_DERIVS
   }
#endif
}

/**
 * Description not yet available.
 * \param
 */
inline void grad_stack::set_gradient_stack(void (*func) (void),
  double *dep_addr, double *ind_addr1, double mult1, double *ind_addr2,
  double mult2, double *ind_addr3, double mult3, double *ind_addr4,
  double mult4)
{
#ifdef NO_DERIVS
   if (!gradient_structure::no_derivatives)
   {
#endif
      if (ptr > ptr_last)
      {
         // current buffer is full -- write it to disk and reset pointer
         // and counter
         this->write_grad_stack_buffer();
      }
      ptr->func = NULL;
      ptr->dep_addr = dep_addr;
      ptr->ind_addr1 = ind_addr1;
      ptr->mult1 = mult1;
      ptr->ind_addr2 = ind_addr2;
      ptr->mult2 = mult2;
      ptr++;
      if (ptr > ptr_last)
      {
         // current buffer is full -- write it to disk and reset pointer
         // and counter
         this->write_grad_stack_buffer();
      }
      ptr->func = func;
      ptr->ind_addr1 = ind_addr3;
      ptr->mult1 = mult3;
      ptr->ind_addr2 = ind_addr4;
      ptr->mult2 = mult4;
      ptr++;
#ifdef NO_DERIVS
   }
#endif
}

/**
 * Description not yet available.
 * \param
 */
inline void grad_stack::set_gradient_stack(void (*func) (void),
  double *dep_addr, double *ind_addr1, double *ind_addr2)
{
#ifdef NO_DERIVS
   if (!gradient_structure::no_derivatives)
   {
#endif
      if (ptr > ptr_last)
      {
         // current buffer is full -- write it to disk and reset pointer
         // and counter
         this->write_grad_stack_buffer();
      }
      ptr->func = func;
      ptr->dep_addr = dep_addr;
      ptr->ind_addr1 = ind_addr1;
      ptr->ind_addr2 = ind_addr2;
      ptr++;
#ifdef NO_DERIVS
   }
#endif
}

/**
 * Description not yet available.
 * \param
 */
inline void grad_stack::set_gradient_stack2(void (*func) (void),
  double *dep_addr, double *ind_addr1, double mult1)
{
#ifdef NO_DERIVS
   if (!gradient_structure::no_derivatives)
   {
#endif
      if (ptr > ptr_last)
      {
         // current buffer is full -- write it to disk and reset pointer
         // and counter
         this->write_grad_stack_buffer();
      }
      ptr->func = func;
      ptr->dep_addr = dep_addr;
      ptr->ind_addr1 = ind_addr1;
      ptr->mult1 = mult1;
      ptr++;
#ifdef NO_DERIVS
   }
#endif
}

/**
 * Description not yet available.
 * \param
 */
inline void grad_stack::set_gradient_stack4(void (*func) (void),
  double *dep_addr, double *ind_addr1, double *ind_addr2)
{
#ifdef NO_DERIVS
   if (!gradient_structure::no_derivatives)
   {
#endif
      if (ptr > ptr_last)
      {
         // current buffer is full -- write it to disk and reset pointer
         // and counter
         this->write_grad_stack_buffer();
      }
      ptr->func = func;
      ptr->dep_addr = dep_addr;
      ptr->ind_addr1 = ind_addr1;
      ptr->ind_addr2 = ind_addr2;
      ptr++;
#ifdef NO_DERIVS
   }
#endif
}

/**
 * Description not yet available.
 * \param
 */
inline void grad_stack::set_gradient_stack(void (*func) (void))
{
#ifdef NO_DERIVS
   if (!gradient_structure::no_derivatives)
   {
#endif
      if (ptr > ptr_last)
      {
         // current buffer is full -- write it to disk and reset pointer
         // and counter
         this->write_grad_stack_buffer();
      }

      ptr->dep_addr = NULL;
      ptr->func = func;
      // want to put a long int into the memory space of a double
      ptr->ind_addr2 = NULL;
      ptr->mult2 = 0;
      ptr++;
#ifdef NO_DERIVS
   }
#endif
}

/**
 * Description not yet available.
 * \param
 */
class indvar_offset_list
{
   // The number of independent variables
   int nvar;
   double **address;

 public:
   friend class gradient_structure;
   inline double *get_address(const int &i)
   {
      return address[i];
   }
   void put_address(unsigned int &i, double *iaddress)
   {
      address[i] = iaddress;
      //  cerr << "In put_address i = " << i << "\n";
   }
};

void gradfree(dlink *);

class prevariable_position;

/**
Base class for dvariable.
Principle role is to avoid calling a destructor when a pevariable or dvariable
object is passed on the stack.
(There is no destructor, ~prevariable().)
\ingroup BAD
*/
class prevariable
{
protected:
#ifndef __SUN__
  /**
  Default constructor
  */
  prevariable()
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
dvar_vector & operator<<(const dvar_vector & v1, const dvar_vector & v2);
dvar_matrix & operator<<(const dvar_matrix & v1, const dvar_matrix & v2);

class df1_one_variable;
class df1_two_variable;
class df1_three_variable;

  /**
  Fundamental data type for reverse mode automatic differentiation.
  \ingroup BAD
 */
class dvariable:public prevariable
{
 public:
   dvariable();
   ~dvariable();
   dvariable(double t);
   dvariable(const int &t);
   dvariable(kkludge_object);
   dvariable(const prevariable &);
   dvariable & operator=(const prevariable &);
   dvariable & operator =(const df1_one_variable & v);
   dvariable & operator =(const df1_two_variable & v);
   dvariable & operator =(const df1_three_variable & v);
   dvariable & operator=(double);
#if defined(USE_DDOUBLE)
#  undef double
   dvariable & operator=(double);
#  define double dd_real
#endif
   dvariable(const dvariable &);
//#  if (__BORLANDC__  > 0x0520)
//     dvariable& operator+=(const prevariable&);
//#  endif
};

#if defined(max)
#undef max
#endif
#if defined(min)
#undef min
#endif

/**
 * Description not yet available.
 * \param
 */
class funnel_dvariable:public dvariable
{
 public:
   dvariable & operator=(const prevariable &);
};

dvar_vector operator*(const dvar_vector & t1, double x);
dvar_vector operator/(double x, const dvar_vector & t1);
dvar_vector operator/(const dvar_vector & t1, double x);
dvar_vector operator+(double x, const dvar_vector & t1);
dvar_vector operator+(const dvar_vector & t1, double x);
dvar_vector operator-(double x, const dvar_vector & t1);
dvar_vector operator-(const dvar_vector & t1, double x);
dvar_vector operator-(const dvar_vector & t1);
dvar_vector operator*(const dvar_vector & t1, const prevariable & x);
dvar_vector operator/(const prevariable & x, const dvar_vector & t1);
dvar_vector operator/(const dvar_vector & t1, const prevariable & x);
dvar_vector operator+(const prevariable & x, const dvar_vector & t1);
dvar_vector operator+(const dvar_vector & t1, const prevariable & x);
dvar_vector operator-(const prevariable & x, const dvar_vector & t1);
dvar_vector operator-(const dvar_vector & t1, const prevariable & x);
dvar_vector operator-(const dvector & t1, const prevariable & x);
dvar_vector operator*(const dvector & t1, const prevariable & x);
dvar_vector operator*(const prevariable & x, const dvector & t1);

dvector operator*(const dvector & t1, double x);
dvector operator/(double x, const dvector & t1);
dvector operator/(const dvector & t1, double x);
dvector operator+(double x, const dvector & t1);
dvector operator+(const dvector & t1, double x);
dvector operator-(double x, const dvector & t1);
dvector operator-(const dvector & t1, double x);
dvector operator-(const dvector & t1);

double min(const dmatrix &);
double max(const dmatrix &);
int max(const imatrix &);
double max(const dvector &);
dvariable max(const dvar_vector &);
dvariable min(const dvar_vector &);

dmatrix symmetrize(const dmatrix & m1);
dvector eigenvalues(const dmatrix & m1);
dmatrix eigenvectors(const dmatrix & m1);
dmatrix eigenvectors(const dmatrix & m1, const dvector & eigenvalues);

dvar_matrix symmetrize(const dvar_matrix & m1);
dvar_vector eigenvalues(const dvar_matrix & m1);
dvar_matrix eigenvectors(const dvar_matrix & m1);

dmatrix outer_prod(const dvector & t1, const dvector & t2);
dvar_matrix outer_prod(const dvar_vector & t1, const dvar_vector & t2);
dvar_matrix outer_prod(const dvector & t1, const dvar_vector & t2);
dvar_matrix outer_prod(const dvar_vector & t1, const dvector & t2);
dmatrix operator*(double x, const dmatrix & m);
dmatrix operator*(const dmatrix & m, double d);
dmatrix operator/(const dmatrix & m, double d);
dmatrix operator/(double d, const dmatrix & m);
dmatrix operator+(double x, const dmatrix & m);
dvar_matrix operator +(const dvariable & x, const dmatrix & m);
dvar_matrix operator -(const dvariable & x, const dmatrix & m);
dmatrix operator+(const dmatrix & m, double d);
dmatrix operator-(double x, const dmatrix & m);
dmatrix operator-(const dmatrix & m, double d);
dvar_matrix operator/(const dvar_matrix & m, const prevariable & x);
dvar_matrix operator/(const dmatrix & m, const prevariable & x);
dvar_matrix operator/(const dvar_matrix & m, double x);
dvar_matrix operator/(double x, const dvar_matrix & m);
dvar_matrix operator/(const prevariable & x, const dvar_matrix & m);

dvar_matrix operator*(const prevariable & x, const dmatrix & m);
dvar_matrix operator*(const dvar_matrix & m, const prevariable & x);
dvar_matrix operator*(const prevariable & x, const dvar_matrix & m);
dvar_matrix operator*(double x, const dvar_matrix & m);

dvector operator&(const dvector & t1, const dvector & t2);
dvar_vector operator&(const dvar_vector & t1, const dvar_vector & t2);

ivector column(const imatrix& m, int i);
dvector extract_column(const dmatrix & m, int i);
dvector column(const dmatrix & m, int i);
dvector extract_row(const dmatrix & m, int j);
dvector row(const dmatrix & m, int j);
dvar_vector extract_column(const dvar_matrix & m, int i);
dvar_vector column(const dvar_matrix & m, int i);
dvector column_value(const dvar_matrix & m, int i);
dvar_vector extract_row(const dvar_matrix & m, int j);
dvar_vector row(const dvar_matrix & m, int j);

// dvector mathematical functions
dvector sin(const dvector & t1);
dvector sqrt(const dvector & t1);
dvector sqr(const dvector & t1);
dvector exp(const dvector & t1);
dvector mfexp(const dvector & t1);
dvector mfexp(const dvector & t1, double d);
dvector atan(const dvector & t1);
dvector tan(const dvector & t1);
dvector tanh(const dvector & t1);
dvector atan2(const dvector & t1, const dvector & t2);
dvector atan2(const dvector & t1, double t2);
dvector atan2(double t1, const dvector & t2);
dvector acos(const dvector & t1);
dvector asin(const dvector & t1);
dvector cos(const dvector & t1);
dvector sinh(const dvector & t1);
dvector cosh(const dvector & t1);
dvector log(const dvector & t1);
dvector log10(const dvector & t1);
dvector pow(const dvector & t1, double);
dvector pow(const dvector & t1, int);
dvector pow(double, const dvector & t1);
ivector pow(const ivector & v1, int x);
ivector pow(int x, const ivector & v1);
// end of dvector mathematical functions

// dvar_vector mathematical functions
dvar_vector sin(const dvar_vector & t1);
dvar_vector sqrt(const dvar_vector & t1);
dvar_vector sqr(const dvar_vector & t1);
dvar_vector exp(const dvar_vector & t1);
dvar_vector mfexp(const dvar_vector & t1);
dvar_vector mfexp(const dvar_vector & t1, double d);
dvar_vector atan(const dvar_vector & t1);
dvar_vector tan(const dvar_vector & t1);
dvar_vector tanh(const dvar_vector & t1);
dvar_vector atan2(const dvar_vector & t1, const dvar_vector & t2);
dvar_vector atan2(const dvar_vector & t1, double t2);
dvar_vector atan2(double t1, const dvar_vector & t2);
dvar_vector acos(const dvar_vector & t1);
dvar_vector asin(const dvar_vector & t1);
dvar_vector cos(const dvar_vector & t1);
dvar_vector sinh(const dvar_vector & t1);
dvar_vector cosh(const dvar_vector & t1);
dvar_vector log(const dvar_vector & t1);
dvar_vector log10(const dvar_vector & t1);
dvar_vector pow(const dvar_vector &, const dvar_vector & t1);
dvar_vector pow(const dvar_vector &, const dvector & t1);
dvar_vector pow(const dvector &, const dvar_vector & t1);
dvector pow(const dvector &, const dvector & t1);
dvar_vector pow(const dvar_vector & t1, double);
dvar_vector pow(const dvar_vector & t1, int);
dvar_vector pow(const dvar_vector & t1, const prevariable &);
dvar_vector pow(const dvector & t1, const prevariable &);
dvar_vector pow(const prevariable &, const dvar_vector & t1);
dvar_vector pow(const dvector & x, const dvar_vector & a);
// end of dvar_vector mathematical functions

// dmatrix mathematical functions
dmatrix exp(const dmatrix & m);
dmatrix mfexp(const dmatrix & m);
dmatrix mfexp(const dmatrix & m, double d);
dmatrix sqrt(const dmatrix & m);
dmatrix sqr(const dmatrix & m);
dmatrix pow(const dmatrix & m, double e);
dmatrix pow(const dmatrix & m, int e);
dmatrix log(const dmatrix & m);
dmatrix sin(const dmatrix & m);
dmatrix cos(const dmatrix & m);
dmatrix tan(const dmatrix & m);
dmatrix elem_div(const dmatrix & m, const dmatrix & m2);
dmatrix elem_prod(const dmatrix & m, const dmatrix & m2);
// end of dmatrix mathematical functions

//  dvar_matrix mathematical functions
dvar_matrix exp(const dvar_matrix & m);
dvar_matrix mfexp(const dvar_matrix & m);
dvar_matrix mfexp(const dvar_matrix & m, double d);
dvar_matrix sqrt(const dvar_matrix & m);
dvar_matrix sqr(const dvar_matrix & m);
dvar_matrix log(const dvar_matrix & m);
dvar_matrix sin(const dvar_matrix & m);
dvar_matrix cos(const dvar_matrix & m);
dvar_matrix tan(const dvar_matrix & m);
dvar_matrix pow(const dvar_matrix & m, double e);
dvar_matrix pow(const dvar_matrix & m, const prevariable & e);
dvar_matrix pow(const dmatrix & m, const prevariable & e);
dvar_matrix pow(const dvar_matrix & m, int e);
dvar_matrix elem_prod(const dvar_matrix & m, const dvar_matrix & m2);
dvar_matrix elem_prod(const dvar_matrix & m, const dmatrix & m2);
dvar_matrix elem_prod(const dmatrix & m, const dvar_matrix & m2);
dvar_matrix elem_div(const dvar_matrix & m, const dvar_matrix & m2);
dvar_matrix elem_div(const dvar_matrix & m, const dmatrix & m2);
dvar_matrix elem_div(const dmatrix & m, const dvar_matrix & m2);
//  end of dvar_matrix mathematical functions

int min(const ivector & t1);
int max(const ivector & t1);
int Max(const ivector & t1);

double mfexp(double);
double mfexp(double, double bound);
dvariable mfexp(const prevariable &);
dvariable mfexp(const prevariable &, double bound);

#if defined(THREAD_SAFE)
/**
 * Description not yet available.
 */
class ts_vector_shapex
{
 public:
   void *trueptr;
   ts_vector_shapex(int lb, int ub, void *p):index_min(lb),
      index_max(ub), ncopies(0), trueptr(p)
   {
   }
   void *get_truepointer(void)
   {
      return trueptr;
   }
   //friend class dvector;
   friend class ivector;
   //friend class tdvector;
   friend class dvar_vector;

#  if defined(USE_VECTOR_SHAPE_POOL)
   static ts_vector_shape_pool **xpool;
   void *operator  new(size_t);
   void operator  delete(void *ptr, size_t n);
#  endif

   unsigned int ncopies;
   void shift(int min);
   int index_min;
   int index_max;
 private:
   friend class subdvector;
   friend class lvector;
   friend class ptr_vector;
 public:
   int decr_ncopies(void)
   {
      return --ncopies;
   }
   int get_ncopies(void)
   {
      return ncopies;
   }
   int incr_ncopies(void)
   {
      return ++ncopies;
   }
   int indexmin()
   {
      return index_min;
   }
   int indexmax()
   {
      return index_max;
   }
};
#endif

#include "vector_shapex.h"

/**
 * Description not yet available.
 * \param
 */
class predvector
{
   dvector *p;
   int lb;
   int ub;
   inline predvector(dvector * _p, int _lb, int _ub)
   {
      p = _p;
      lb = _lb, ub = _ub;
   }
   friend class dvector;
};

/**
 * Description not yet available.
 * \param
 */
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

#include "dvector.h"

/**
 * Description not yet available.
 * \param
 */
class independent_variables:public dvector
{
 public:
   independent_variables(const independent_variables & v):dvector(v)
   {
   }

   independent_variables(int ncl, int ncu):dvector(ncl, ncu)
   {
   }
   // makes an array [ncl..ncu]

   independent_variables(unsigned int sz, double *x):dvector(sz, x)
   {
   }

   independent_variables & operator=(const dvector & t);
};

dvariable dfatan1(dvariable, double, double, const prevariable & fpen);

double boundp(double x, double fmin, double fmax, const double &fpen);
double boundp(double x, double fmin, double fmax);

dvariable boundp(const prevariable & x, double fmin, double fmax,
  const prevariable & fpen);
dvariable boundp(const prevariable & x, double fmin, double fmax,
  const prevariable & fpen, double s);

double nd2fboundp(double x, double minb, double maxb, const double &pen);
double boundpin(double x, double fmin, double fmax);
double boundpin(const prevariable & x, double fmin, double fmax);
double boundpin(const prevariable & x, double fmin, double fmax, double s);

double dmin(double, double);

double dmax(double i, double j);

#include <stdlib.h>
#ifdef __TURBOC__
  #include <alloc.h>
#endif

double sigmoid(double t1);

/**
 * Description not yet available.
 * \param
 */
class mat_shape
{
   unsigned int ncopies;
   unsigned int nrows;
   unsigned int ncols;
   int row_min;
   int row_max;
   int col_min;
   int col_max;
   mat_shape(int rl, int ru, int cl = 0, int cu = -1);
   mat_shape()
   {
   };
   void colshift(int min);
   void rowshift(int min);

   //friend class const_dmatrix;
   friend class dmatrix;
   friend class sdmatrix;
   friend class dvar_matrix;
   friend class imatrix;
   friend class lmatrix;
   friend class i3_array;
};

/**
 * Description not yet available.
 * \param
 */
class mat_shapex
{
 public:
   void *trueptr;
   unsigned int ncopies;
   mat_shapex(const void *m)
   {
      trueptr = (void *) m;
      ncopies = 0;
   }
   mat_shapex()
   {
      trueptr = NULL;
      ncopies = 0;
   };

   void *get_pointer(void)
   {
      return trueptr;
   }
   friend class dmatrix;
   friend class sdmatrix;
   friend class dvar_matrix;
   friend class imatrix;
   friend class i3_array;
   friend class lmatrix;
};

class arr_link;

/**
 * Description not yet available.
 * \param
 */
class arr_list
{
   arr_link *last;
   arr_link *free_last;
   unsigned long int last_offset;
   unsigned long int max_last_offset;
 public:
   unsigned long int number_arr_links;
   friend class arr_link;

 public:
   arr_list(void)
   {
      last = 0;
      free_last = 0;
      last_offset = 0;
      max_last_offset = 0;
      number_arr_links = 0;
   }
   unsigned long int get_last_offset()
   {
      return last_offset;
   }
   unsigned long int get_number_arr_links()
   {
      return number_arr_links;
   }
   unsigned long int get_max_last_offset()
   {
      return max_last_offset;
   }
   void reset_max_last_offset()
   {
      max_last_offset = 0;
   }
   friend double_and_int *arr_new(unsigned int);
   friend void arr_free(double_and_int *);
   friend void arr_remove(arr_link **);
   friend void arr_free_list_remove(arr_link **);
   friend void arr_free_add(arr_link *);
   friend void arr_free_remove(arr_link *);
};

/**
 * Description not yet available.
 * \param
 */
class arr_link
{
#if defined(USE_VECTOR_SHAPE_POOL)
   static vector_shape_pool *xpool;
   void *operator new(size_t);
   void operator delete(void* ptr, size_t)
   {
      xpool->free(ptr);
   }
#endif
   arr_link *prev;
   arr_link *next;
   arr_link *free_prev;
   arr_link *free_next;
   unsigned int status;
   // unsigned int     free_list_status;
   unsigned int size;
   unsigned long int offset;
 public:
   arr_link();

   friend double_and_int *arr_new(unsigned int);
   friend void arr_free(double_and_int *);
   friend void arr_remove(arr_link **);
   friend void arr_free_remove(arr_link *);
   friend void arr_free_add(arr_link *);
};

#if defined(__NUMBERVECTOR__)
class param_init_number_vector;
class param_init_bounded_number_vector;
class param_init_bounded_number_matrix;
class param_init_vector_vector;
class param_init_bounded_vector_vector;
#endif

/**
ADMB variable vector
*/
class dvar_vector
{
public:
  double_and_int* va;
  int index_min;
  int index_max;
  arr_link* link_ptr;
  vector_shapex* shape;

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
  unsigned int size() const
  {
    return static_cast<unsigned int>(
      index_max < index_min ? 0 : index_max - index_min + 1);
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

 /*
    class funnel_dvar_vector : public dvar_vector
    {
    public:
    funnel_dvar_vector(int l,int u);
    dvar_vector& operator=(const dvar_vector&);
    };
  */

//class fvar_ptr { dvar_vector *p; };

/**
 * Class definition of matrix with derivitive information
  \index_min

 */
class dvar_matrix
{
   int index_min;
   int index_max;
   dvar_vector *m;
   mat_shapex *shape;

 public:
   dvar_matrix & operator --(void)
   {
      index_min--;
      index_max--;
      m++;
      return *this;
   }
   dvar_matrix & operator ++(void)
   {
      index_min++;
      index_max++;
      m--;
      return *this;
   }

   int operator!(void) const
   {
      return (shape == NULL);
   }
   inline dvar_vector & elem(int i)
   {
      return (m[i]);
   }
   inline prevariable elem(int i, int j)
   {
      return (elem(i).elem(j));
   }
   inline dvar_vector & elem(int i) const
   {
      return (m[i]);
   }
   inline prevariable elem(int i, int j) const
   {
      return (elem(i).elem(j));
   }

   friend class banded_symmetric_dvar_matrix;
   friend class banded_lower_triangular_dvar_matrix;
   friend class banded_symmetric_dmatrix;
   friend class banded_lower_triangular_dmatrix;
   friend class dvar3_array;
   void shallow_copy(const dvar_matrix &);
   dvar_matrix();
   void allocate(int nrl, int nrh, int ncl, int nch);
   void allocate(int nrl, int nrh);
   void allocate(ad_integer nrl, ad_integer nrh);
   void allocate(const dmatrix & m1);
   void allocate(const dvar_matrix & m1);
   void allocate(int nrl, int nrh, const ivector & ncl, const ivector & nch);
   void allocate(int nrl, int nrh, int ncl, const ivector & nch);
   void allocate(int nrl, int nrh, const ivector & ncl, int nch);
   void allocate(void);
   void deallocate();
   dvar_matrix(const banded_symmetric_dvar_matrix & v);
   dvar_matrix(const banded_lower_triangular_dvar_matrix & v);
# if defined(__NUMBERVECTOR__)
   dvar_matrix(const param_init_vector_vector &);
   dvar_matrix(const param_init_bounded_vector_vector &);
   dvar_matrix(const param_init_bounded_number_matrix &);
# endif
   dvar_matrix sub(int, int);

   double fill_seqadd(double, double);

   int colmin(void) const
   {
      return ((*this) (indexmin()).indexmin());
   }
   int colmax(void) const
   {
      return ((*this) (indexmin()).indexmax());
   }
   int rowmin(void) const
   {
      return (index_min);
   }
   int rowmax(void) const
   {
      return (index_max);
   }
   int indexmin(void) const
   {
      return (index_min);
   }
   int indexmax(void) const
   {
      return (index_max);
   }

  // returns the number of rows
  unsigned int rowsize() const
  {
    int size = rowmax() - rowmin() + 1;
    return static_cast<unsigned int>(size < 0 ? 0 : size);
  }
  // returns the number of columns
  unsigned int colsize() const
  {
    int size = rowsize() > 0 ? colmax() - colmin() + 1 : 0;
    return static_cast<unsigned int>(size < 0 ? 0 : size);
  }
   void colshift(int min);
   void rowshift(int min);

   friend char *fform(const char *, const dvar_matrix &);

   friend class dvar_vector;

   dvar_matrix(const ad_integer & nrl, const ad_integer & nrh,
     const index_type & ncl, const index_type & nch);

   void allocate(const ad_integer & nrl, const ad_integer & nrh,
     const index_type & ncl, const index_type & nch);

   dvar_matrix(int, int, int, int);
   dvar_matrix(int, int);
   dvar_matrix(int, int, kkludge_object kk);
   // makes a matrix [nrl..nrh][ncl..nch]

   dvar_matrix(int, int, const ivector &, const ivector &);
   // makes a ragged dvar_matrix [nrl..nrh][ncl..nch]

   dvar_matrix(int, int, int, const ivector &);
   // makes a ragged dvar_matrix [nrl..nrh][ncl..nch]

   dvar_matrix(const dvar_matrix &);
   // copy initializer
   void initialize(void);

   dvar_matrix(const dmatrix &);

   //dvar_matrix(char *);

   ~dvar_matrix();

   void save_dvar_matrix_position(void) const;
   void save_dvar_matrix_value(void) const;

   void fill(const char *);
   //void colfill(const int&n,...);
   //void rowfill(const int&n,...);

   void colfill_randu(const int &j, long int &n);
   void rowfill_randu(const int &i, long int &n);
   void colfill_randn(const int &j, long int &n);
   void rowfill_randn(const int &i, long int &n);
   void fill_randn(long int &n);
   void fill_randu(long int &n);

   void colfill_seqadd_ni(const int &, double, double);
   void colfill_randu_ni(const int &j, long int &n);
   void rowfill_randu_ni(const int &i, long int &n);
   void colfill_randn_ni(const int &j, long int &n);
   void rowfill_randn_ni(const int &i, long int &n);
   void fill_randn_ni(long int &n);
   void fill_randu_ni(long int &n);

   void colfill_seqadd(const int &, double, double);
   void rowfill_seqadd(const int &, double, double);
   void colfill(int j, const dvar_vector & v);
   void rowfill(int j, const dvar_vector & v);

   void write_on(const ostream &) const;
   void write_on(const uostream &) const;
   void read_from(const istream &);
   void read_from(const uistream &);

   dvar_vector& operator ()(int i);
   dvar_vector& operator[](int);
   const dvar_vector& operator()(int i) const;
   const dvar_vector& operator[](int) const;

#ifdef OPT_LIB
#ifdef __NDPX__
   prevariable operator () (register int i, register int j)
   {
      return (prevariable((m[i]).va + j));
   }
#else
   inline prevariable operator () (register int i, register int j)
   {
      return ((m[i]).va + j);
   }
#endif
#else
   prevariable operator () (int i, int j);
#endif

   inline double &elem_value(register int i, register int j)
   {
      return *(double *) ((m[i]).va + j);
   }

   inline const double &elem_value(register int i, register int j) const
   {
      return *(double *) ((m[i]).va + j);
   }
#ifdef OPT_LIB
#ifdef __NDPX__
   prevariable operator() (register int i, register int j) const
   {
      return (prevariable((m[i]).va + j));
   }
#else
   inline prevariable operator() (register int i, register int j) const
   {
      return ((m[i]).va + j);
   }
#endif
#else
   const prevariable operator() (int i, int j) const;
#endif

   dvar_matrix & operator+=(const dvar_matrix & x);
   dvar_matrix & operator-=(const dvar_matrix & x);
   dvar_matrix & operator+=(const dmatrix & x);
   dvar_matrix & operator-=(const dmatrix & x);


   dvar_matrix & operator=(const dvar_matrix &);

   dvar_matrix & operator=(const dmatrix &);
   dvar_matrix & operator =(double t);
   dvar_matrix & operator=(const prevariable & t);

   dvar_matrix & operator*=(const prevariable & t);
   dvar_matrix & operator *=(double t);
   dvar_matrix & operator/=(const prevariable & t);
   dvar_matrix & operator /=(double t);

   friend dvar_vector operator*(const dvar_vector &, const dvar_matrix &);

   friend dvar_vector operator*(const dvar_matrix &, const dvar_vector &);

   friend dvar_vector operator*(const dvector &, const dvar_matrix &);

   friend dvar_vector operator*(const dvar_matrix &, const dvector &);

   friend dvar_matrix operator*(const dvar_matrix &, const dvar_matrix &);

   friend dvar_matrix operator*(const dvar_matrix &, const dmatrix &);

   friend dvar_matrix operator*(const dmatrix &, const dvar_matrix &);

   friend dvar_matrix operator+(const dvar_matrix &, const dvar_matrix &);
   friend dvar_matrix operator+(const dvar_matrix &, const dmatrix &);
   friend dvar_matrix operator+(const dmatrix &, const dvar_matrix &);

   friend dvar_matrix operator+(double, const dvar_matrix &);
   friend dvar_matrix operator+(const dvar_matrix &, double);
   friend dvar_matrix operator-(double, const dvar_matrix &);
   friend dvar_matrix operator-(const dvar_matrix &, double);

   friend dvar_matrix operator+(const dvariable &, const dvar_matrix &);
   friend dvar_matrix operator+(const dvar_matrix &, const dvariable &);
   friend dvar_matrix operator-(const dvariable &, const dvar_matrix &);
   friend dvar_matrix operator-(const dvar_matrix &, const dvariable &);

   friend dvar_matrix operator-(const dvar_matrix &, const dvar_matrix &);
   friend dvar_matrix operator-(const dvar_matrix &, const dmatrix &);
   friend dvar_matrix operator-(const dmatrix &, const dvar_matrix &);

   friend dvar_matrix inv(const dvar_matrix &);

   friend dvariable det(const dvar_matrix &);
   friend dvariable ln_det(const dvar_matrix &, int& sgn);

   //friend dvar_matrix testsub(dvar_matrix);

   friend dvar_matrix trans(const dvar_matrix &);

   friend dvariable norm(const dvar_matrix &);
   friend dvariable norm2(const dvar_matrix &);
   friend dvariable sumsq(const dvar_matrix &);

   friend void copy_status(const ostream & s, const dvar_matrix & m1);
};

#ifdef OPT_LIB
inline dvar_vector& dvar_matrix::operator[](int i)
{
  if (!m)
    throw std::bad_alloc();
  else
    return m[i];
}
inline dvar_vector& dvar_matrix::operator()(int i)
{
  if (!m)
    throw std::bad_alloc();
  else
    return m[i];
}
inline const dvar_vector& dvar_matrix::operator[](int i) const
{
  return m[i];
}
inline const dvar_vector& dvar_matrix::operator()(int i) const
{
  return m[i];
}
#endif

dvariable ln_det(const dvar_matrix &);
dvar_matrix operator *(const dvar_matrix & t1, double x);
dmatrix value(const dvar_matrix & m);
d3_array value(const dvar3_array & a);
dvar_vector sort(const dvar_vector &, int NSTACK = 60);
dvector sort(const dvector &, int NSTACK = 60);
ivector sort(const ivector &, int NSTACK = 60);
dvector sort(const dvector &, const ivector & index, int NSTACK = 60);
ivector sort(const ivector &, const ivector & index, int NSTACK = 60);
dmatrix sort(const dmatrix &, int column, int NSTACK = 60);
imatrix sort(const imatrix &, int column, int NSTACK = 60);


#include "factors.h"
int count_factor(const dvector & v, const double &eps);
ivector as_factor(const dvector & v, const double eps = 1.0e-6);
int count_factor(const ivector & v);

 //void gradcalc( int , double *);
void gradcalc(int nvar, const dvector & g);
double gradcalc(int nvar, const dvector& g, dvariable& f);
void slave_gradcalc(void);

/**
 * Description not yet available.
 * \param
 */
class dmatrix
{
 protected:
   int index_min;
   int index_max;
   dvector *m;
   mat_shapex *shape;
   friend char *fform(const char *, const dmatrix &);
   friend class dvar_matrix;
 public:
   dmatrix & operator --(void)
   {
      index_min--;
      index_max--;
      m++;
      return *this;
   }
   dmatrix & operator ++(void)
   {
      index_min++;
      index_max++;
      m--;
      return *this;
   }
   void shallow_copy(const dmatrix &);
   int operator!(void) const
   {
      return (shape == NULL);
   }

   dmatrix sub(int, int);
   dmatrix(void);
   dmatrix(int, int, kkludge_object);
   dmatrix(int, int);
   void allocate(void);
   void allocate(const dmatrix & dm);
   void allocate(const dvar_matrix &);
   void allocate(int nrl, int nrh, int ncl, int nch);
   void allocate(int nrl, int nrh);
   void allocate(ad_integer nrl, ad_integer nrh);
   void allocate(int nrl, int nrh, int ncl, const ivector & nch);
   //void allocate(int nrl,int nrh,
   // const index_type& ncl,const index_type& nch);
   void allocate(int nrl, int nrh, const ivector & ncl, int nch);
   void deallocate();
   void allocate(const ad_integer & nrl, const ad_integer & nrh,
     const index_type & ncl, const index_type & nch);
   void allocate(int nrl, int nrh, const ivector & ncl,
     const ivector & nch);
   friend class banded_symmetric_dmatrix;
   friend class banded_lower_triangular_dmatrix;

   dmatrix(int, int, int, int);
   // makes a matrix [nrl..nrh][ncl..nch]

   dmatrix(const ad_integer & nrl, const ad_integer & nrh,
     const index_type & ncl, const index_type & nch);

   dmatrix(int, int, const ivector & coll, const ivector & colh);
   // makes a ragged dmatrix[nrl..nrh][ncl..nch]

   dmatrix(int, int, int coll, const ivector & colh);
   // makes a ragged dmatrix[nrl..nrh][ncl..nch]

   dmatrix(const dvar_matrix_position &);

   dmatrix(const dmatrix_position &);

   dmatrix(const dmatrix &);
   dmatrix(const banded_symmetric_dmatrix &);
   dmatrix(const banded_lower_triangular_dmatrix &);
   dmatrix(char *);
   void fill(const char *);
   double fill_seqadd(double, double);
   void initialize(void);
   // copy initializer

   ~dmatrix();

  dvector* begin() const
  {
    return m ? &m[rowmin()] : nullptr;
  }
  dvector* end() const
  {
    return m ? begin() + rowsize() : nullptr;
  }

   void save_dmatrix_derivatives(const dvar_matrix_position & pos) const;
   void save_dmatrix_derivatives_na(const dvar_matrix_position & pos)
      const;
   void save_dmatrix_value(void) const;
   void save_dmatrix_position(void) const;
   //void save_dmatrix_derivatives(void);

  int indexmin() const
  {
    return rowmin();
  }
  int indexmax() const
  {
    return rowmax();
  }
  int rowmin() const
  {
    return index_min;
  }
  int rowmax() const
  {
    return index_max;
  }
  // returns the number of rows
  unsigned int rowsize() const
  {
    return static_cast<unsigned int>(rowmax() - rowmin() + 1);
  }

   int colmin(void) const
   {
      return ((*this) (indexmin()).indexmin());
   }
   int colmax(void) const
   {
      return ((*this) (indexmin()).indexmax());
   }
  // returns the number of columns
  unsigned int colsize() const
  {
    int size = rowsize() > 0 ? colmax() - colmin() + 1 : 0;
    return static_cast<unsigned int>(size < 0 ? 0 : size);
  }
   void rowshift(int min);
   void colshift(int min);

   void write_on(const ostream &) const;
   uostream& write_on(const uostream&) const;
   void read_from(const istream &);
   uistream& read_from(const uistream&);

   //void colfill(const int&n,...);
   //void rowfill(const int&n,...);

   void colfill_randu(const int &j, long int &n);
   void rowfill_randu(const int &i, long int &n);
   void colfill_randn(const int &j, long int &n);
   void fill_randn(long int &n);
   void fill_randu(long int &n);
   void rowfill_randn(const int &i, long int &n);

   void colfill_randu(const int &j, const random_number_generator & rng);
   void rowfill_randu(const int &i, const random_number_generator & rng);
   void fill_randn(const random_number_generator & rng);
   void fill_randcau(const random_number_generator & rng);
   void fill_randu(const random_number_generator & rng);
   void colfill_randn(const int &j, const random_number_generator & rng);
   void rowfill_randn(const int &i, const random_number_generator & rng);

   void colfill_randu_ni(const int &j, long int &n);
   void rowfill_randu_ni(const int &i, long int &n);
   void colfill_randn_ni(const int &j, long int &n);
   void fill_randn_ni(long int &n);
   void fill_randu_ni(long int &n);
   void rowfill_randn_ni(const int &i, long int &n);

   void colfill_seqadd(const int &, const int &, const int &);
   void colfill_seqadd(const int &, double, double);
   void rowfill_seqadd(const int &, double, double);
   void colfill(int j, const dvector & v);
   void rowfill(int j, const dvector & v);

   dvector& operator()(int i);
   dvector& operator[](int);
   const dvector& operator()(int i) const;
   const dvector& operator[](int) const;

#if defined(OPT_LIB) && !defined(__INTEL_COMPILER)
   inline double &operator() (register int i, register int j)
   {
      return (*(m[i].v + j));
   }
   inline const double &operator() (register int i, register int j) const
   {
      return (*(m[i].v + j));
   }
#else
   double &operator() (int i, int j);
   const double &operator() (int i, int j) const;
#endif

   inline dvector & elem(int i)
   {
      return (*(m + i));
   }
   inline double &elem(int i, int j)
   {
      return (*((*(m + i)).v + j));
   }
   inline const dvector & elem(int i) const
   {
      return (*(m + i));
   }
   inline const double &elem(int i, int j) const
   {
      return (*((*(m + i)).v + j));
   }
   friend class d3_array;
   friend dvector operator*(const dvector &, const dmatrix &);

   friend dvector operator*(const dmatrix &, const dvector &);

   friend dvar_vector operator*(const dvar_vector &, const dmatrix &);

   friend dvar_vector operator*(const dmatrix &, const dvar_vector &);

   friend dmatrix operator*(const dmatrix &, const dmatrix &);

   friend dvar_matrix operator*(const dvar_matrix &, const dmatrix &);

   friend dvar_matrix operator*(const dmatrix &, const dvar_matrix &);

   friend dvar_matrix::dvar_matrix(const dmatrix &);

   friend dmatrix operator-(const dmatrix &, const dmatrix &);
   friend dmatrix operator+(const dmatrix &, const dmatrix &);

   friend dvar_matrix operator+(const dvar_matrix &, const dmatrix &);

   friend dvar_matrix operator+(const dmatrix &, const dvar_matrix &);

   friend dmatrix trans(const dmatrix & m1);

   friend dmatrix inv(const dmatrix &);
   friend dmatrix inv(const dmatrix & m1, const double &_ln_det,
     const int &_sgn);

   friend double det(const dmatrix &);
   friend double ln_det(const dmatrix & m1, int& sgn);

   friend double norm(const dmatrix &);
   friend double norm2(const dmatrix &);
   friend double sumsq(const dmatrix &);

   dmatrix & operator+=(const dmatrix & t);
   dmatrix & operator-=(const dmatrix & t);

   dmatrix & operator =(const dmatrix & t);
   dmatrix & operator =(double t);

   dmatrix operator() (const ivector & t);

   friend dvar_matrix & dvar_matrix::operator=(const dmatrix &);

   dmatrix(const tdmatrix & t);

   dmatrix & operator /=(double d);
   dmatrix & operator *=(double d);

  bool is_valid_row(const int i) const;
};

#if defined(OPT_LIB)
inline dvector& dmatrix::operator()(int i)
{
  return m[i];
}
inline dvector& dmatrix::operator[](int i)
{
  return m[i];
}
inline const dvector& dmatrix::operator()(int i) const
{
  return m[i];
}
inline const dvector& dmatrix::operator[](int i) const
{
  return m[i];
}
#endif

imatrix operator*(const imatrix &, const imatrix &);

dmatrix trans(const dmatrix & m1);

imatrix trans(const imatrix & m1);

dvariable dfatan1(dvariable, double, double, double *);

double dftinv(double, double, double);

dvariable boundp(double, double, double, double *);

dvariable dfboundp(double, double, double, double *);
dvariable dfboundp(const prevariable &, double, double);

double mean(const dvector &);
double mean(const dmatrix &);
double mean(const d3_array &);

double std_dev(const dvector &);
double var(const dvector &);

dvariable mean(const dvar_vector &);
dvariable mean(const dvar_matrix &);
dvariable mean(const dvar3_array &);

dvariable std_dev(const dvar_vector &);
dvariable var(const dvar_vector &);

dvariable sum(const dvar_vector &);
double sum(const dvector &);
int sum(const ivector &);

dvar_vector rowsum(const dvar_matrix &);
dvar_vector colsum(const dvar_matrix &);

dvector colsum(const dmatrix &);
dvector rowsum(const dmatrix &);

ivector colsum(const imatrix &);
ivector rowsum(const imatrix &);

int colsum(const imatrix &, int column);
double colsum(const dmatrix &, int column);
dvariable colsum(const dvar_matrix &, int column);

double sfabs(double t1); //"smoothed absolute value function

dvector sfabs(const dvector & t1); //"smoothed absolute value function

#include <imatrix.h>

dvariable regression(const dvector & obs, const dvar_vector & pred);
double regression(const dvector & obs, const dvector & pred);

dvariable robust_regression_fixed(const dvector& obs, const dvar_vector& pred,
  double a = 0.7);
dvariable robust_regression(const dvector & obs, const dvar_vector & pred,
  double a = 0.7);

dvariable robust_regression(const dvector & obs, const dvar_vector & pred,
  const dvariable & cutoff);

dmatrix column_vector(const dvector &);
dmatrix row_vector(const dvector &);

dvar_matrix column_vector(const dvar_vector &);
dvar_matrix row_vector(const dvar_vector &);

dmatrix identity_matrix(int min, int max);

istream & operator>>(const istream & s, const ptr_vector & v);
ostream & operator<<(const ostream & s, const ptr_vector & v);

/**
  Function minimizer control.
 */
class fmm_control
{
 public:
   int noprintx;
   long maxfn;
   long iprint;
   double crit;
   double fringe;
   long imax;
   double dfn;
   long ifn;
   long iexit;
   long ialph;
   long ihflag;
   long ihang;
   int scroll_flag;
   int maxfn_flag;
   int quit_flag;
   double min_improve;
   int ireturn;
   int dcheck_flag;
   int use_control_c;

   void set_defaults();
   fmm_control();
   fmm_control(const fmm_control &);
   fmm_control(const lvector & ipar);
   void writeon(const ostream & s) const;
};

/**
 * Description not yet available.
 * \param
 */
class sdmatrix:public dmatrix
{
 public:
   void allocate(int);
   void allocate();
   sdmatrix(int);
   sdmatrix();
   ~sdmatrix();
   void deallocate();
};

class dfsdmat;

uistream & operator>>(const uistream &, const dfsdmat &);
uostream & operator<<(const uostream &, const dfsdmat &);

/**
 * Description not yet available.
 * \param
 */
class dfsdmat
{
   int tmp_file;
   int disk_save_flag;
   double *ptr;
   double **m;
   double *minp;
   double *maxp;
   int shared_memory;
   int n;
 public:
   int disk_save(void)
   {
      return disk_save_flag;
   }
   void save(void);
   void restore(void);
   double *getminp(void)
   {
      return minp;
   }
   int operator!(void) const
   {
      return (ptr == NULL);
   }
   int size(void)
   {
      return n;
   }
   dfsdmat(int n);
   dfsdmat();
   dfsdmat(int n, const gradient_structure & gs);
   void allocate(int n);
   void allocate(int n, const gradient_structure & gs);
   void allocate(void);
   ~dfsdmat();
   void deallocate(void);
   friend uistream & operator>>(const uistream &, const dfsdmat &);
   friend uostream & operator<<(const uostream &, const dfsdmat &);

  double &elem(int i, int j);
  double &operator () (int i, int j);
};

#if defined(OPT_LIB) && !defined(__INTEL_COMPILER)
inline double& dfsdmat::elem(int i, int j)
{
  return *(m[i] + j);
}
inline double& dfsdmat::operator()(int i, int j)
{
  return *(m[i] + j);
}
#endif

/**
 Functions and variables for function minimizer.
 */
class fmm:public fmm_control
{
 private:
   dfsdmat h;
   dvector w;
   dvector funval;
 public:
   double dmin, fbest, df;

   long int llog, n1, ic, iconv, i1, xxlink;
   double z, zz, gys, gs, sig, gso, alpha, tot, fy, dgs;
   long int itn, icc, nn;
   int i, j, is, iu, iv, np, ib;
   double gmax; ///< maximum gradient
   double fsave;
   dvector xx;
   dvector gbest;
   dvector xsave;
   dvector gsave;

   int n;
   int disk_save;

 public:
   fmm(int nvar, int disk_save = 0);
   fmm(int nvar, const lvector & ipar, int disk_save = 0);
   double minimize(const independent_variables & x,
     double (*pf) (const dvar_vector &));

   /// Undefined
   double minimize(const independent_variables & x, const dvector & c,
     double (*pf) (const dvar_vector &, const dvector &));

 //void fmin(const double& f, const independent_variables &x, const dvector& g);
   void fmin(const double &f, const dvector & x, const dvector & g);

   dmatrix & hessian(); ///< Undefined
};

class function_minimizer;

/**
 * Description not yet available.
 * \param
 */
class fmmt1:public fmm_control
{
 private:
   dvector w;
   dvector funval;
   int xm;
   dmatrix xstep;
   dvector xrho;
   dvector rrr;
   dmatrix xy;
   dvector xold;
   dvector gold;
 public:
   double dmin, fbest, df;

   long int llog, n1, ic, iconv, i1, link;
   double z, zz, gys, gs, sig, gso, alpha, tot, fy, dgs;
   long int icc, np, nn, iv, ib;
   int i, j, iu, is, itn;
   double gmax;
   double fsave;
   dvector xx;
   dvector gbest;
   dvector xsave;
   dvector gsave;

   int n;

 public:
   fmmt1(int nvar, int _xm = 7);
   fmmt1(int nvar, const lvector & ipar);
   double minimize(const independent_variables & x,
     double (*pf) (const dvar_vector &));

   double minimize(const independent_variables & x, const dvector & c,
     double (*pf) (const dvar_vector &, const dvector &));

   void fmin2(const double &f, const independent_variables & x,
     const dvector & g, function_minimizer *);

   void fmin(const double &f, const dvector & x, const dvector & g);

//  dmatrix& hessian();
};

void derch(const double &f, const independent_variables & x,
  const dvector & g, int n, const int &ireturn);

void fmin(double f, const independent_variables & x, const dvector & g,
  const int &n, const dvector & w, const dvector & h, const fmm_control & fmc);

void fmmdisp(const dvector & x, const dvector & g, const int &nvar,
  int scroll_flag, int noprintx = 0);

void fmmdisp(const double *x, const double *g, const int &nvar,
  int scroll_flag, int noprintx = 0);

ostream & operator<<(const ostream & s, const fmm_control & fmc);

/**
 * Description not yet available.
 * \param
 */
class uostream:public ofstream
{
 public:
#if defined(__TURBOC__) && (__BORLANDC__  <= 0x0520)
  uostream(const char*, int = ios::out | ios::binary, int = filebuf::openprot);
  void open(const char*, int = ios::out | ios::binary, int = filebuf::openprot);
#endif
#if (__BORLANDC__  >= 0x0540)
   uostream(const char *, int = ios::out | ios::binary, int protection = 666);
   void open(const char *, int = ios::out | ios::binary, int protection = 666);
#endif
#if defined (_MSC_VER) || defined (__WAT32__)
  #if (_MSC_VER < 1300)
  uostream(const char*, int = ios::out | ios::binary, int = filebuf::openprot);
  void open(const char*, int = ios::out | ios::binary, int = filebuf::openprot);
  #else
  uostream(const char *, int = ios::out | ios::binary, int prot = 0664);
  void open(const char *, int = ios::out | ios::binary, int prot = 0664);
  #endif
#endif

#ifdef __ZTC__
   uostream(const char *, int = ios::out, int = filebuf::openprot);
   void open(const char *, int = ios::out, int = filebuf::openprot);
#endif

#ifdef __NDPX__
   uostream(const char *, int = ios::out, int = filebuf::openprot);
   void open(const char *, int = ios::out, int = filebuf::openprot);
#endif

#ifdef __SUN__
   //uostream(const char*, int = ios::out, int = openprot);
   //void open(const char*, int = ios::out, int = openprot);
#endif

#if !defined(_MSC_VER)
  #if defined(__ADSGI__)
  uostream(const char *name, int mode = ios::out, int prot = 0664);
  void open(const char *name, int mode = ios::out, int prot = 0664);
  #else
  uostream(const char *name, int mode = ios::out | ios::binary,
    int prot = 0664);
  void open(const char *name, int mode = ios::out | ios::binary,
    int prot = 0664);
  #endif
#endif

   // insert character
#ifndef __SUN__
   uostream & operator<<(signed char);
#endif
   uostream & operator<<(unsigned char);

   // insert numeric value
   uostream & operator<<(short);
   uostream & operator<<(unsigned short);
   uostream & operator<<(int);
   uostream & operator<<(unsigned int);
   uostream & operator<<(long);
   uostream & operator<<(unsigned long);
   uostream & operator<<(float);
   uostream & operator<<(double);
   uostream & operator<<(const char *)
   {
      return *this;
   };
#ifdef __TURBOC__
   uostream & operator<<(long double);
#endif

   // insert pointer
   uostream & operator<<(void *);
};


 // inline void uostream::open(const char* name, int m, int prot)
 // {
 // #if defined (__TURBOC__) &&   (__BORLANDC__  <= 0x0520)
 //   fstreambase::open(name, m, prot);
 // #endif
 // #if (__BORLANDC__  >= 0x0540 && __BORLANDC__  <= 0x0550)
 //   ofstream::open(name, m, prot);
 // #else
 // #  if defined(linux)
 // #    if (__GNUC__  >= 3)
 //        ofstream::open(name, std::_Ios_Openmode(m));
 // #    else
 //        ofstream::open(name, m);
 // #    endif
 // #  else
 //      ofstream::open(name, m);
 // #  endif
 // #endif
 //
 // #ifdef _MSC_VER
 // #  if (_MSC_VER >= 1400)
 //   ofstream::open(name, m);
 // #  else
 //   //fstreambase::open(name, m, prot);
 //   ofstream::open(name, m, prot);
 // #  endif
 // #endif
 // #ifdef __ZTC__
 //   fstream_common::open(name, m, prot);
 // #endif
 // #ifdef __NDPX__
 //   ofstream::open(name, m, prot);
 // #endif
 // #ifdef __SUN__
 //   ofstream::open(name, m, prot);
 // #endif
 // }

/**
 * Description not yet available.
 * \param
 */
class uistream:public ifstream
{
 public:
#if defined (__TURBOC__) &&   (__BORLANDC__  <= 0x0520)
   uistream(const char *, int = ios::in | ios::binary, int = filebuf::openprot);
  void open(const char *, int = ios::in | ios::binary, int = filebuf::openprot);
#endif
#if (__BORLANDC__  >= 0x0540)
   uistream(const char *, int = ios::in | ios::binary, int protection = 666);
   void open(const char *, int = ios::in | ios::binary, int protection = 666);
#endif
#if defined (_MSC_VER) || defined (__WAT32__)
  #if (_MSC_VER < 1300)
  uistream(const char *, int = ios::in | ios::binary, int = filebuf::openprot);
  void open(const char *, int = ios::in | ios::binary, int = filebuf::openprot);
  #else
  uistream(const char *, int = ios::in | ios::binary, int prot = 0664);
  void open(const char *, int = ios::in | ios::binary, int prot = 0664);
  #endif
#endif
#ifdef __ZTC__
   uistream(const char *, int = ios::in, int = filebuf::openprot);
   void open(const char *, int = ios::in, int = filebuf::openprot);
#endif

#ifdef __NDPX__
   uistream(const char *, int = ios::in, int = filebuf::openprot);
   void open(const char *, int = ios::in, int = filebuf::openprot);
#endif

#ifdef __SUN__
   // uistream(const char* name, int mode = ios::in, int prot=0664);
   // void open(const char* name, int mode = ios::in, int prot=0664);
#endif

#if !defined(_MSC_VER)
  #if defined(__ADSGI__)
  uistream(const char *name, int mode = ios::in, int prot = 0664);
  void open(const char *name, int mode = ios::in, int prot = 0664);
  #else
  uistream(const char *name, int mode = ios::in | ios::binary,
    int prot = 0664);
  void open(const char *name, int mode = ios::in | ios::binary,
    int prot = 0664);
  #endif
#endif

   // extract characters into an array
#ifndef __SUN__
   uistream & get(signed char *, int, char = '\n');
#endif
   uistream & get(unsigned char *, int, char = '\n');

   // extract a single character
   uistream & get(unsigned char &);
#ifndef __SUN__
   uistream & get(signed char &);
#endif
   int get();

   // extract and discard chars but stop at delim
   uistream & ignore(int = 1, int = EOF);

   uistream& operator>>(int&);

#ifndef __SUN__
   uistream & operator>>(const signed char *);
#endif
   uistream & operator>>(const unsigned char *);
   uistream & operator>>(const unsigned char &);
#ifndef __SUN__
   uistream & operator>>(const signed char &);
#endif
   uistream & operator>>(const short &);
   uistream & operator>>(const int &);
   uistream & operator>>(const long &);
   uistream & operator>>(const unsigned short &);
   uistream & operator>>(const unsigned int &);
   uistream & operator>>(const unsigned long &);
   uistream & operator>>(const float &);
   uistream & operator>>(const double &);
   uistream & operator>>(const char &);
#if defined(__TURBOC__) || defined (_MSC_VER)
   uistream & operator>>(const long double &);
#endif
};

  // inline void   uistream::open(const char* name, int m, int prot)
  // {
  // #if defined(__TURBOC__) && (__BORLANDC__  <= 0x0520)
  //   fstreambase::open(name, m, prot);
  // #endif
  // #ifdef __ZTC__
  //   fstream_common::open(name, m, prot);
  // #endif
  // #ifdef __NDPX__
  //   ifstream::open(name, m, prot);
  // #endif
  // #ifdef __SUN__
  //   ifstream::open(name, m, prot);
  // #endif
  // }

class fmmc;

void derch(const double &f, const dvector & x, const dvector & gg, int n,
  const int &ireturn);

/**
 * Description not yet available.
 * \param
 */
class fmmc
{
 public:
   int maxfn;
   double crit;
   double min_improve;
   int iprint;
   int scroll_flag;
   int j;
   int J;
   long int ifn;
   long int iter;
   int imax;
   long ihang;
   int quit_flag;
   dvector *funval;
   dvector *left_bracket_gradient;
   dvector *right_bracket_gradient;
   dvector *g;
   dvector *h;
   dvector *xi;
   dvector *d;
   dvector *extx;
   dvector *g2;
   dvector *grad;
   dvector *extg;
   dvector *theta;
   dvector *xbest;
   dvector *gbest;
   int lin_flag;
   int ext_flag;
   int int_flag;
   int ifnex;
   int ireturn;
   int frp_flag;
   double gg;
   double gam;
   double fp;
   double dgg;
   double rho_min;
   double converge_flag;
   double gamma;
   double Psi_0;
   double extf;
   double crit1;
   double rho_1;
   double Psi_1;
   double dir_deriv;
   double rho_i;
   double left_bracket;
   double left_bracket_value;
   double right_bracket;
   double right_bracket_value;
   double rho_0;
   double fbest;
   fmmc(const int &n);
   ~fmmc();
   void fmin(const double &f, const dvector & p, const dvector & gg);
   double dfn;
   int maxfn_flag;
   long iexit;
   long ihflag;
};

class dd3_array;

/**
 * Description not yet available.
 * \param
 */
class three_array_shape
{
   //unsigned int nslices;
   unsigned int ncopies;
   //unsigned int nrows;
   //unsigned int ncols;
   int slice_min;
   int slice_max;
   // int row_min;
   // int row_max;
   //int col_min;
   //int col_max;
   three_array_shape(int sl, int sh);
   //mat_shape(){};

   friend class i3_array;
   friend class d3_array;
   friend class dd3_array;
   friend class qd3_array;
   friend class dvar3_array;
};

//class dmatrix_ptr { dmatrix *p; };
//class dvar_matrix_ptr { dvar_matrix *p; };

/**
 * Description not yet available.
 * \param
 */
class d3_array
{
   dmatrix *t;
   three_array_shape *shape;
   friend class d4_array;
 public:
   int operator!(void) const
   {
      return (shape == NULL);
   }
   // conclass cgors
   d3_array(void);
   void save_d3_array_value(void) const;
   void shallow_copy(const d3_array &);
   d3_array sub(int, int);
   d3_array(int sl, int sh, int nrl, int nrh, int ncl, int nch);
   d3_array(int sl, int sh, int nrl, int nrh);
   d3_array(int sl, int sh, const index_type & nrl, const index_type & nrh);
   d3_array(int sl, int sh);
   d3_array(const d3_array_position &);

   void save_d3_array_position(void) const;

   d3_array(int sl, int sh, int nrl, int nrh, const ivector & ncl, int nch);

   d3_array(const ad_integer & sl, const ad_integer & sh,
     const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch);

   void allocate(const ad_integer & sl, const ad_integer & sh,
     const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch);

   d3_array(int sl, int sh, const ivector & nrl, const ivector & nrh,
     const imatrix & ncl, const imatrix & nch);
   d3_array(int sl, int sh, const ivector & nrl, const ivector & nrh,
     int ncl, const imatrix & nch);
   d3_array(int sl, int sh, int nrl, const ivector & nrh,
     int ncl, const imatrix & nch);
   d3_array(int sl, int sh, const ivector & nrl, const ivector & nrh,
     const ivector & ncl, const ivector & nch);
   d3_array(int sl, int sh, int nrl, int nrh, const ivector & ncl,
     const ivector & nch);
   d3_array(int sl, int sh, int nrl, const ivector & nrh,
     int ncl, const ivector & nch);
   d3_array(int sl, int sh, int nrl, const ivector & nrh,
     int ncl, int nch);
   d3_array(const d3_array & m2);
   ~d3_array();

   void allocate(const dvar3_array &);
   void allocate(const d3_array & d3v);
   void allocate(int sl, int sh, int nrl, int nrh, int ncl, int nch);
   void allocate(int sl, int sh, int nrl, int nrh);
   void allocate(int sl, int sh, const index_type & nrl,
     const index_type & nrh);
   void allocate(int sl, int sh);

   void allocate(int sl, int sh, int nrl, int nrh, const ivector& ncl, int nch);
   void allocate(int sl, int sh, const ivector & nrl, const ivector & nrh,
     const imatrix & ncl, const imatrix & nch);
   void allocate(int sl, int sh, int nrl, const ivector & nrh, int ncl,
     const imatrix & nch);
   void allocate(int sl, int sh, const ivector & nrl, const ivector & nrh,
     int ncl, const imatrix & nch);
   void allocate(int sl, int sh, const ivector & nrl, const ivector & nrh,
     int ncl, int nch);
   void allocate(int sl, int sh, const ivector& nrl, int nrh, int ncl, int nch);
   void allocate(int sl, int sh, int nrl, const ivector& nrh, int ncl, int nch);
   void allocate(int sl, int sh, const ivector & nrl, const ivector & nrh,
     const ivector & ncl, const ivector & nch);
   void allocate(int sl, int sh, int nrl, const ivector & nrh, int ncl,
     const ivector & nch);
   void allocate(int sl, int sh, int nrl, int nrh, const ivector & ncl,
     const ivector & nch);
   void allocate(int sl, int sh, int nrl, int nrh, int ncl,
     const ivector & nch);
   void allocate(void);
   void deallocate(void);
   void initialize(int sl, int sh, int nrl, const ivector & nrh,
     int ncl, const ivector & nch);

  dmatrix* begin() const
  {
    return t ? &t[slicemin()] : nullptr;
  }
  dmatrix* end() const
  {
    return t ? begin() + slicesize() : nullptr;
  }
  //access functions
  int indexmin() const
  {
    return slicemin();
  }
  int indexmax() const
  {
    return slicemax();
  }
  int slicemin() const
  {
    return shape ? shape->slice_min : 1;
  }
  int slicemax() const
  {
    return shape ? shape->slice_max : 0;
  }

   int colmin(void) const
   {
      return ((*this) (slicemin()).colmin());
   }
   int colmax(void) const
   {
      return ((*this) (slicemin()).colmax());
   }
   int rowmin(void) const
   {
      return ((*this) (slicemin()).rowmin());
   }
   int rowmax(void) const
   {
      return ((*this) (slicemin()).rowmax());
   }

  // returns the number of rows
  unsigned int slicesize() const
  {
    return static_cast<unsigned int>(slicemax() - slicemin() + 1);
  }

   // returns the number of rows
   int rowsize(void) const
   {
      return (rowmax() - rowmin() + 1);
   }
   // returns the number of columns
   int colsize(void) const
   {
      return (colmax() - colmin() + 1);
   }
   void initialize(void);

   dmatrix & elem(int k)
   {
      return (t[k]);
   }
   const dmatrix & elem(int k) const
   {
      return t[k];
   }
   double &operator () (int k, int i, int j);
   dvector & operator ()(int k, int i);
   dmatrix & operator[](int i);
   dmatrix & operator()(int i);
   const double &operator() (int k, int i, int j) const;
   const dvector & operator() (int k, int i) const;
   const dmatrix & operator[] (int i) const;
   const dmatrix & operator() (int i) const;

   d3_array & operator=(const d3_array & m1);
   d3_array & operator=(double x);
   friend d3_array value(const dvar3_array & ar);

   void fill_randn(const random_number_generator & rng);
   void fill_randcau(const random_number_generator & rng);
   void fill_randu(const random_number_generator & rng);

   void fill_randu(long int &n);
   void fill_randn(long int &n);

   void fill_randu_ni(long int &n);
   void fill_randn_ni(long int &n);
   double fill_seqadd(double, double);
   void operator /=(double d);

  unsigned int get_ncopies() const { return shape ? shape->ncopies : 0; }
};
#ifdef OPT_LIB
inline const double& d3_array::operator()(int k, int i, int j) const
{
  return ((t[k].m[i]).v)[j];
}
inline const dvector& d3_array::operator()(int k, int i) const
{
  return t[k].m[i];
}
inline const dmatrix& d3_array::operator()(int i) const
{
  return t[i];
}
inline const dmatrix& d3_array::operator[](int i) const
{
  return t[i];
}
inline double& d3_array::operator()(int k, int i, int j)
{
  return ((t[k].m[i]).v)[j];
}
inline dvector& d3_array::operator()(int k, int i)
{
  return t[k].m[i];
}
inline dmatrix& d3_array::operator()(int i)
{
  return t[i];
}
inline dmatrix& d3_array::operator[](int i)
{
  return t[i];
}
#endif

/**
 * Description not yet available.
 * \param
 */
class i3_array
{
   imatrix *t;
   three_array_shape *shape;
 public:
#  if defined(MFCL2_CONSTRUCTORS)
   i3_array(int sl, int sh, int nrl, int nrh, const ivector & nc);
   void allocate(int sl, int sh, int nrl, int nrh, const ivector & nc);
#  endif
   int operator!(void) const
   {
      return (shape == NULL);
   }
   // conclass cgors
   void shallow_copy(const i3_array &);
   i3_array(void);
   i3_array(int sl, int sh, const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch);

   i3_array(int _sl, int _sh, const imatrix & m1);

   i3_array(int sl, int sh);
   i3_array(int sl, int sh, int nrl, int nrh, int ncl, int nch);
   i3_array(int sl, int sh, int nrl, int nrh, const ivector & ncl, int nch);

   i3_array(int sl, int sh, const ivector & nrl, const ivector & nrh,
     const imatrix & ncl, const imatrix & nch);
   i3_array(int sl, int sh, const ivector & nrl, const ivector & nrh,
     int ncl, const imatrix & nch);
   i3_array(int sl, int sh, const ivector & nrl, const ivector & nrh,
     const ivector & ncl, const ivector & nch);
   i3_array(int sl, int sh, int nrl, int nrh, const ivector & ncl,
     const ivector & nch);
   i3_array(int sl, int sh, int nrl, const ivector & nrh, int ncl,
     const ivector & nch);
   i3_array(int sl, int sh, int nrl, const ivector & nrh, int ncl, int nch);
   i3_array(int sl, int sh, int nrl, const ivector & nrh, int ncl,
     const imatrix & nch);
   i3_array(const i3_array & m2);
   ~i3_array();

   void allocate(int sl, int sh, int nrl, const ivector& nrh, int ncl, int nch);
   void allocate(const dvar3_array &);
   void allocate(const i3_array & i3v);
   void allocate(int sl, int sh, int nrl, int nrh, int ncl, int nch);
   void allocate(int sl, int sh);

   void allocate(int sl, int sh, int nrl, int nrh, const ivector& ncl, int nch);

   void allocate(int sl, int sh, const index_type& nrl, const index_type& nrh,
     const index_type & ncl, const index_type & nch);

   void allocate(int sl, int sh, const ivector & nrl, const ivector & nrh,
     const imatrix & ncl, const imatrix & nch);
   void allocate(int sl, int sh, int nrl, const ivector & nrh, int ncl,
     const imatrix & nch);
   void allocate(int sl, int sh, const ivector & nrl, const ivector & nrh,
     int ncl, const imatrix & nch);
   void allocate(int sl, int sh, const ivector & nrl, const ivector & nrh,
     int ncl, int nch);
   void allocate(int sl, int sh, const ivector & nrl, int nrh,
     int ncl, int nch);
   //void allocate(int sl, int sh, int nrl, const ivector& nrh,
   //  int ncl,int nch);
   void allocate(int sl, int sh, const ivector & nrl, const ivector & nrh,
     const ivector & ncl, const ivector & nch);
   void allocate(int sl, int sh, int nrl, const ivector & nrh,
     int ncl, const ivector & nch);
   void allocate(int sl, int sh, int nrl, int nrh, const ivector & ncl,
     const ivector & nch);
   void allocate(int sl, int sh, int nrl, int nrh, int ncl, const ivector& nch);
   void allocate(void);
   void deallocate(void);
   void initialize(int sl, int sh, int nrl, const ivector & nrh, int ncl,
     const ivector & nch);

  //access functions
  int indexmin() const
  {
    return slicemin();
  }
  int indexmax() const
  {
    return slicemax();
  }
  int slicemin() const
  {
    return shape ? shape->slice_min : 1;
  }
  int slicemax() const
  {
    return shape ? shape->slice_max : 0;
  }
   int colmin(void) const
   {
      return ((*this) (slicemin()).colmin());
   }
   int colmax(void) const
   {
      return ((*this) (slicemin()).colmax());
   }
   int rowmin(void) const
   {
      return ((*this) (slicemin()).rowmin());
   }
   int rowmax(void) const
   {
      return ((*this) (slicemin()).rowmax());
   }
  // returns the number of rows
  unsigned int slicesize() const
  {
    return static_cast<unsigned int>(slicemax() - slicemin() + 1);
  }
   // returns the number of rows
   int rowsize() const
   {
      return (rowmax() - rowmin() + 1);
   }
   // returns the number of columns
   int colsize() const
   {
      return (colmax() - colmin() + 1);
   }
   void initialize();

  imatrix& elem(int i);
  const imatrix& elem(int i) const;
  int& operator()(int i, int j, int k);
  ivector& operator()(int i, int j);
  imatrix& operator[](int i);
  imatrix& operator()(int i);
  const int& operator()(int i, int j, int k) const;
  const ivector& operator()(int i, int j) const;
  const imatrix& operator[](int i) const;
  const imatrix& operator()(int i) const;

  i3_array& operator=(const i3_array& other);
  i3_array& operator=(int value);

   void fill_randu(long int &n);
   void fill_randn(long int &n);
   void fill_randu_ni(long int &n);
   void fill_randn_ni(long int &n);

  unsigned int get_ncopies() const { return shape ? shape->ncopies : 0; }
};
inline imatrix& i3_array::elem(int i)
{
#ifndef OPT_LIB
  if (i < slicemin())
  {
    cerr << "matrix bound exceeded -- row index too low in"
         << "ivector& i3_array::elem(int).\n";
    ad_exit(1);
  }
  if (i > slicemax())
  {
    cerr << "matrix bound exceeded -- row index too high in"
         << "ivector& i3_array::elem(int).\n";
    ad_exit(1);
  }
#endif
  return t[i];
}
inline const imatrix& i3_array::elem(int i) const
{
#ifndef OPT_LIB
  if (i < slicemin())
  {
    cerr << "matrix bound exceeded -- row index too low in"
         << "ivector& i3_array::elem(int).\n";
    ad_exit(1);
  }
  if (i > slicemax())
  {
    cerr << "matrix bound exceeded -- row index too high in"
         << "ivector& i3_array::elem(int).\n";
    ad_exit(1);
  }
#endif
  return t[i];
}
inline imatrix& i3_array::operator[](int i)
{
#ifdef OPT_LIB
  return t[i];
#else
  return elem(i);
#endif
}
inline imatrix& i3_array::operator()(int i)
{
#ifdef OPT_LIB
  return t[i];
#else
  return elem(i);
#endif
}
inline ivector& i3_array::operator()(int i, int j)
{
#ifdef OPT_LIB
  return t[i].m[j];
#else
  return elem(i)(j);
#endif
}
inline int& i3_array::operator()(int i, int j, int k)
{
#ifdef OPT_LIB
  return ((t[i].m[j]).v)[k];
#else
  return elem(i)(j, k);
#endif
}
inline const imatrix& i3_array::operator[](int i) const
{
#ifdef OPT_LIB
  return t[i];
#else
  return elem(i);
#endif
}
inline const imatrix& i3_array::operator()(int i) const
{
#ifdef OPT_LIB
  return t[i];
#else
  return elem(i);
#endif
}
inline const ivector& i3_array::operator()(int i, int j) const
{
#ifdef OPT_LIB
  return t[i].m[j];
#else
  return elem(i)(j);
#endif
}
inline const int& i3_array::operator()(int i, int j, int k) const
{
#ifdef OPT_LIB
  return ((t[i].m[j]).v)[k];
#else
  return elem(i)(j, k);
#endif
}

#   if defined(__NUMBERVECTOR__)
class param_init_matrix_vector;
class param_init_bounded_matrix_vector;
#   endif

/**
 * Description not yet available.
 * \param
 */
class dvar3_array
{
  dvar_matrix* t;
  three_array_shape* shape;

public:
   void shallow_copy(const dvar3_array &);
   dvar3_array sub(int, int);
   dvar3_array(int, int);
   int operator!(void) const
   {
      return (shape == NULL);
   }
   // conclass cgors

   void initialize(void);
   void allocate(int sl, int sh, int nrl, int nrh, int ncl, int nch);
   void allocate(int sl, int sh, int nrl, int nrh);
   void allocate(int sl, int sh, const index_type& nrl, const index_type& nrh);
   void allocate(int sl, int sh);

   void allocate(int sl, int sh, int nrl, int nrh, const ivector& ncl, int nch);
   void allocate(const d3_array & m1);
   void allocate(void);
   void allocate(const dvar3_array & m1);
   void allocate(int sl, int sh, int nrl, int nrh,
     const ivector & ncl, const ivector & nch);
   void allocate(int sl, int sh, const ivector & nrl, const ivector & nrh,
     const ivector & ncl, const ivector & nch);
   void allocate(int sl, int sh, const ivector & nrl, const ivector & nrh,
     int ncl, int nch);
   void allocate(int sl, int sh, const ivector & nrl, int nrh,
     int ncl, int nch);
   void allocate(int sl, int sh, int nrl, const ivector & nrh,
     int ncl, int nch);
   void allocate(int sl, int sh, int nrl, const ivector & nrh,
     int ncl, const ivector & nch);
   void allocate(int sl, int sh, int nrl, int nrh,
     int ncl, const ivector & nch);
   void allocate(ad_integer sl, ad_integer sh, const index_type & nrl,
     const index_type & nrh, const index_type & ncl, const index_type & nch);
   void allocate(ad_integer sl, ad_integer sh, const index_type & nrl,
     const index_type & nrh);
   void allocate(ad_integer sl, ad_integer sh);

   void deallocate();
   dvar3_array(int sl, int sh, int nrl, int nrh, int ncl, int nch);
   dvar3_array(int sl, int sh, int nrl, int nrh, const ivector & ncl, int nch);

   dvar3_array(int sl, int sh, const ivector & nrl, const ivector & nrh,
     ivector & ncl, const ivector & nch);

   dvar3_array(int sl, int sh, int nrl, const ivector & nrh, int ncl,
     const ivector & nch);

   dvar3_array(int sl, int sh, int nrl, const ivector & nrh, int ncl, int nch);

   dvar3_array(ad_integer sl, ad_integer sh, const index_type & nrl,
     const index_type & nrh, const index_type & ncl, const index_type & nch);

   dvar3_array(const d3_array & m2);
#   if defined(__NUMBERVECTOR__)
   dvar3_array(const param_init_matrix_vector & m2);
   dvar3_array(const param_init_bounded_matrix_vector & m2);
#   endif

   dvar3_array(const dvar3_array & m2);

   dvar3_array(void);

   ~dvar3_array();

   d3_array value(const dvar3_array &);

  //access functions
  int indexmin() const { return slicemin(); }
  int indexmax() const { return slicemax(); }
  int slicemin() const { return shape ? shape->slice_min : 1; }
  int slicemax() const { return shape ? shape->slice_max : 0; }
  // returns the number of rows
  unsigned int slicesize() const
  {
    //assert(slicemin() <= slicemax());
    return static_cast<unsigned int>(slicemax() - slicemin() + 1);
  }

   int colmin() const
   {
      return ((*this) (slicemin()).colmin());
   }
   int colmax(void) const
   {
      return ((*this) (slicemin()).colmax());
   }
   int rowmin(void) const
   {
      return ((*this) (slicemin()).rowmin());
   }
   int rowmax(void) const
   {
      return ((*this) (slicemin()).rowmax());
   }
   // returns the number of rows
   int rowsize() const
   {
      return (rowmax() - rowmin() + 1);
   }
   // returns the number of columns
   int colsize() const
   {
      return (colmax() - colmin() + 1);
   }
  /**
  \ingroup matop?
  Retrieves an element of a dvar3_array.
  \param i Integer specifying slice
  \return dvariable containing the desired element
  */
  dvar_matrix& elem(int i) { return t[i]; }
  /**
  \ingroup matop?
  Retrieves an element of a dvar3_array.
  \param i Integer specifying slice
  \param j Integer specifying row within slice
  \param k integer specifying column within row
  \return dvariable containing the desired element
  */
  prevariable elem(int i, int j, int k) { return t[i].elem(j, k); }
  /**
  \ingroup matop?
  Retrieves an element of a dvar3_array.
  \param i Integer specifying slice
  \return dvariable containing the desired element
  */
  const dvar_matrix& elem(int i) const { return t[i]; }
  /**
  \ingroup matop?
  Retrieves an element of a dvar3_array.
  \param i Integer specifying slice
  \param j Integer specifying row within slice
  \param k integer specifying column within row
  \return dvariable containing the desired element
  */
  const prevariable elem(int i, int j, int k) const { return t[i].elem(j, k); }

#ifdef OPT_LIB
   inline const prevariable operator() (int k, int i, int j) const
   {
      return (((t[k].m[i]).va) + j);
   }

   inline const dvar_vector & operator() (int k, int i) const
   {
      return (t[k].m[i]);
   }

   inline const dvar_matrix & operator() (int i) const
   {
      return (t[i]);
   }

   inline const dvar_matrix & operator[] (int i) const
   {
      return (t[i]);
   }

   inline prevariable operator () (int k, int i, int j)
   {
      return (((t[k].m[i]).va) + j);
   }

   inline dvar_vector & operator () (int k, int i)
   {
      return (t[k].m[i]);
   }

   inline dvar_matrix & operator() (int i)
   {
      return (t[i]);
   }

   inline dvar_matrix & operator[] (int i)
   {
      return (t[i]);
   }
#else
   prevariable operator () (int k, int i, int j);
   dvar_vector & operator ()(int k, int i);
   dvar_matrix & operator[](int i);
   dvar_matrix & operator()(int i);
   const prevariable operator() (int k, int i, int j) const;
   const dvar_vector & operator() (int k, int i) const;
   const dvar_matrix & operator[] (int i) const;
   const dvar_matrix & operator() (int i) const;
#endif

   dvar3_array & operator=(const d3_array & m1);
   dvar3_array & operator=(double x);
   dvar3_array & operator=(const dvar3_array & m1);

   void fill_randu(long int &n);
   void fill_randn(long int &n);

   void fill_randu_ni(long int &n);
   void fill_randn_ni(long int &n);
   double fill_seqadd(double, double);
   void operator/=(const prevariable &);
   void operator /=(double);

  unsigned int get_ncopies() const { return shape ? shape->ncopies : 0; }
};

dvariable inv_cumd_exponential(const prevariable & y);
dvariable cumd_exponential(const prevariable & x);

double inv_cumd_exponential(double y);
double cumd_exponential(double x);

double cumd_logistic(const double &x);
double inv_cumd_logistic(const double &x);

dvariable cumd_logistic(const prevariable & x);
dvariable inv_cumd_logistic(const prevariable & x);
double inv_cumd_norm(const double &x);
double cumd_norm(const double &x);
double cumd_norm(const double &x, double);
dvariable inv_cumd_norm(const prevariable & x);
dvar_vector inv_cumd_norm(const dvar_vector & x);
prevariable & cumd_norm(const prevariable & x);
prevariable & bounded_cumd_norm(const prevariable & x, double);
double bounded_cumd_norm(double x, double);
//dvariable& old_cumd_norm(const prevariable& x);
double normal_tail_right(const double &x);

dvariable inv_cumd_norm_logistic(const prevariable & x, double);
prevariable & cumd_norm_logistic(const prevariable & x, double);
double inv_cumd_norm_logistic(double x, double);
double cumd_norm_logistic(double x, double);

/**
 * Description not yet available.
 * \param
 */
class prevariable_position
{
   double_and_int *v;
 public:
   prevariable_position(const prevariable & x)
   {
      v = x.get_v();
   }
   prevariable_position(double_and_int * p)
   {
      v = p;
   }
   double &xval()
   {
      return ((v->x));
   }
};

double restore_prevariable_derivative(const prevariable_position & pre);
double restore_prevariable_derivative(void);
prevariable_position restore_prevariable_position(void);
void save_double_derivative(double x, const prevariable_position & pos);
double restore_prevariable_value(void);
void save_double_value(double x);
int sum(const imatrix &);
double sum(const dmatrix &);
double sum(const d3_array &);
double sum(const d4_array &);
double sum(const d5_array &);
double sum(const d6_array &);
double sum(const d7_array &);
dvariable sum(const dvar_matrix &);
dvariable sum(const dvar3_array &);
dvariable sum(const dvar4_array &);
dvariable sum(const dvar5_array &);
dvariable sum(const dvar6_array &);
dvariable sum(const dvar7_array &);

dmatrix fabs(const dmatrix & m);
//double& value(const  double& u);
   //const double& value(const double& u);
double norm(const d3_array &);
double norm2(const d3_array &);
double sumsq(const d3_array &);
d3_array exp(const d3_array & m);
d3_array mfexp(const d3_array & m);
d3_array mfexp(const d3_array & m, double d);
d3_array log(const d3_array & m);
d3_array fabs(const d3_array & m);
d3_array sin(const d3_array & m);
d3_array cos(const d3_array & m);
d3_array tan(const d3_array & m);
d3_array sqrt(const d3_array & m);
d3_array sqr(const d3_array & m);
d3_array elem_prod(const d3_array & m1, const d3_array & m2);
d3_array elem_div(const d3_array & m1, const d3_array & m2);
d3_array operator+(const d3_array & m1, const d3_array & m2);
d3_array operator+(const d3_array & m1, double m2);
d3_array operator/(const d3_array & m1, double m2);
d3_array operator/(double m2, const d3_array & m1);
d3_array operator+(double m1, const d3_array & m2);
d3_array operator-(const d3_array & m1, const d3_array & m2);
d3_array operator-(const d3_array & m1, double m2);
d3_array operator-(double m1, const d3_array & m2);
d3_array operator*(const d3_array & m1, const d3_array & m2);
dmatrix operator *(const d3_array & m1, const dvector & m2);
d3_array operator*(const d3_array & m1, double m2);
d3_array operator*(double m1, const d3_array & m2);

dvariable norm(const dvar3_array & m);
dvariable norm2(const dvar3_array & m);
dvariable sumsq(const dvar3_array & m);
dvar3_array exp(const dvar3_array & m);
dvar3_array mfexp(const dvar3_array & m);
dvar3_array mfexp(const dvar3_array & m, double d);
dvar3_array log(const dvar3_array & m);
dvar3_array fabs(const dvar3_array & m);
dvar3_array sin(const dvar3_array & m);
dvar3_array cos(const dvar3_array & m);
dvar3_array tan(const dvar3_array & m);
dvar3_array sqrt(const dvar3_array & m);
dvar3_array sqr(const dvar3_array & m);
dvar3_array elem_prod(const dvar3_array & m1, const dvar3_array & m2);
dvar3_array elem_div(const dvar3_array & m1, const dvar3_array & m2);
dvar3_array operator+(const dvar3_array & m1, const dvar3_array & m2);
dvar3_array operator-(const dvar3_array & m1, const dvar3_array & m2);
dvar3_array elem_prod(const d3_array & m1, const dvar3_array & m2);
dvar3_array elem_div(const d3_array & m1, const dvar3_array & m2);
dvar3_array operator+(const d3_array & m1, const dvar3_array & m2);
dvar3_array operator-(const d3_array & m1, const dvar3_array & m2);
dvar3_array elem_prod(const dvar3_array & m1, const d3_array & m2);
dvar3_array elem_div(const dvar3_array & m1, const d3_array & m2);
dvar3_array operator+(const dvar3_array & m1, const d3_array & m2);
dvar3_array operator+(const dvar3_array & m1, const dvariable & m2);
dvar3_array operator+(const dvariable & d1, const dvar3_array & m1);

dvar3_array operator/(const prevariable & m2, const dvar3_array & m1);
dvar3_array operator/(const prevariable & m2, const d3_array & m1);
dvar3_array operator/(double m2, const dvar3_array & m1);

dvar3_array operator/(const dvar3_array & m1, const prevariable & m2);
dvar3_array operator/(const d3_array & m1, const prevariable & m2);
dvar3_array operator/(const dvar3_array & m1, double m2);

dvar3_array operator+(const dvariable & m1, const d3_array & m2);
dvar3_array operator+(double m1, const dvar3_array & m2);
dvar3_array operator-(const dvar3_array & m1, const d3_array & m2);
dvar3_array operator-(const dvar3_array & m1, const dvariable & m2);
dvar3_array operator-(const dvariable & m1, const d3_array & m2);
dvar3_array operator-(const dvariable & m1, const dvar3_array & m2);
dvar3_array operator-(double m1, const dvar3_array & m2);
dvar3_array operator*(const dvar3_array & m1, const d3_array & m2);
dvar3_array operator*(const dvar3_array & m1, const dvariable & m2);
dvar3_array operator*(const dvariable & m1, const d3_array & m2);
dvar3_array operator*(const dvariable & m1, const dvar3_array & m2);
dvar3_array operator*(double m1, const dvar3_array & m2);

ivector square(const ivector& x);

double square(double x);
dvector square(const dvector & x);
dmatrix square(const dmatrix & x);
d3_array square(const d3_array & x);

dvariable & square(const prevariable & x);
dvar_vector square(const dvar_vector & x);
dvar_matrix square(const dvar_matrix & x);
dvar3_array square(const dvar3_array & x);

double cube(double x);
double fourth(double x);
dvector cube(const dvector & x);
dmatrix cube(const dmatrix & x);
d3_array cube(const d3_array & x);

d3_array pow(const d3_array & x, int e);
dvar3_array pow(const dvar3_array & x, int e);

prevariable & cube(const prevariable & x);
dvar_vector cube(const dvar_vector & x);
dvar_matrix cube(const dvar_matrix & x);
dvar3_array cube(const dvar3_array & x);

void set_value(const dvar_matrix & x, const dvar_vector & v, const int &_ii,
  double s);
void set_value(const dvar_matrix & x, const dvar_vector & v, const int &ii,
  double fmin, double fmax, const dvariable & fpen, double s);
void set_value_inv(const dvar_matrix & x, const dvector & v, const int &ii,
  double s);
void set_value_inv(const dvar_matrix & x, const dvector & v, const int &ii,
  double fmin, double fmax, double s);
void set_value(const dvar_vector & x, const dvar_vector & v, const int &_ii,
   double s);
void set_value(const dvar_vector & _x, const dvar_vector & v, const int &_ii,
  double fmin, double fmax, const dvariable & fpen, double s);
void set_value_inv(const dvar_vector & x, const dvector & _v, const int &_ii,
  double s);
void set_value_inv(const dvar_vector & x, const dvector & _v, const int &_ii,
  double fmin, double fmax, double s);
void set_value_inv(const dvar_matrix & x, const dvector & v, const int &ii);
void set_value_inv(const prevariable & x, const dvector & v, const int &ii,
  double s);
void set_value_inv(const prevariable & x, const dvector & v, const int &ii);
void set_value_inv(const dvar_matrix & x, const dvector & v, const int &ii);
void set_value_inv(const dvar_matrix & u, const dvector & x, const int &ii,
  double fmin, double fmax);
void set_value_inv(const dvar3_array & u, const dvector & x, const int &ii,
  double fmin, double fmax);
void set_value_inv(const dvar3_array & u, const dvector & x, const int &ii);

void set_value_inv(double x, const dvector & v, const int &ii);

void set_value_inv_exp(const prevariable & x, const dvector & _v,
  const int &_ii, double fmin, double fmax, double s);

void set_value_inv(const prevariable & x, const dvector & _v, const int &_ii,
  double fmin, double fmax, double s);

void set_value_inv(const prevariable & u, const dvector & x, const int &ii,
  double fmin, double fmax);
void set_value_inv(double u, const dvector & x, const int &ii, double fmin,
  double fmax);
void set_value_inv(const dvector & x, const dvector & v, const int &ii);
void set_value_inv(const dvar_vector & x, const dvector & v, const int &ii);
void set_value_inv(const dvar_vector & x, const dvector & v, const int &ii,
  double fmin, double fmax);
void set_value_inv(const dvector & x, const dvector & v, const int &ii,
  double fmin, double fmax);
void set_value_inv(const dmatrix & x, const dvector & v, const int &ii);
void set_value_inv(const dmatrix & x, const dvector & v, const int &ii,
  double fmin, double fmax);
void set_value_inv(const d3_array & x, const dvector & v, const int &ii);
void set_value_inv(const d3_array & x, const dvector & v, const int &ii,
  double fmin, double fmax);
void set_value(const prevariable & x, const dvar_vector & v, const int &ii);
void set_value(const prevariable & x, const dvar_vector & v, const int &ii,
  double s);
void set_value(const dvar_vector & x, const dvar_vector & v, const int &ii);

void set_value_exp(const prevariable & _x, const dvar_vector & v,
  const int &_ii, double fmin, double fmax, const dvariable & fpen, double s);
void set_value(const prevariable & _x, const dvar_vector & v, const int &_ii,
  double fmin, double fmax, const dvariable & fpen, double s);

void set_value(const prevariable & x, const dvar_vector & v, const int &ii,
  double fmin, double fmax, const dvariable & fpen);
void set_value(const dvar_vector & x, const dvar_vector & v, const int &ii,
  double fmin, double fmax, const dvariable & fpen);
void set_value(const dvar_matrix & x, const dvar_vector & v,
  const int &ii);
void set_value(const dvar_matrix & x, const dvar_vector & v, const int &ii,
  double fmin, double fmax, const dvariable & fpen);
void set_value(dvar3_array & x, const dvar_vector & v, const int &ii);
void set_value(dvar3_array & x, const dvar_vector & v, const int &ii,
  double fmin, double fmax, const dvariable & fpen);

void set_value_inv_partial(const dvector & x, const dvector & v, const int &ii,
  int n);
void set_value_inv_partial(const dvector & x, const dvector & v, const int &ii,
  int n, double fmin, double fmax);
void set_value_inv_partial(const dmatrix & x, const dvector & v, const int &ii,
  int n);
void set_value_inv_partial(const dvar_matrix & x, const dvector & v,
  const int &ii, int n);
void set_value_inv_partial(const d3_array & x, const dvector& v, const int &ii,
  int n);

void set_value_inv_partial(const dvar_vector & x, const dvector & v,
  const int &ii, int n);
void set_value_inv_partial(const dvar_vector & x, const dvector & v,
  const int &ii, int n, double fmin, double fmax);

void set_value_partial(const dvar_vector & x, const dvar_vector & v,
  const int &ii, int n);
void set_value_partial(const dvar_vector & x, const dvar_vector & v,
  const int &ii, int n, double fmin, double fmax, const dvariable & fpen);
void set_value_partial(const dvar_matrix & x, const dvar_vector & v,
  const int &ii, int n);
void set_value_partial(dvar3_array & x, const dvar_vector & v, const int &ii,
  int n);

unsigned int size_count(const dvar_vector& x);
unsigned int size_count(const dvar_matrix& x);
unsigned int size_count(const dvar3_array& x);
unsigned int size_count(const dvar4_array& x);
unsigned int size_count(const dvector& x);
unsigned int size_count(const dmatrix& x);
unsigned int size_count(const d3_array& x);
unsigned int size_count(const d4_array& x);

int size_count_partial(const dvar_vector & x, int);
int size_count_partial(const dvar_matrix & x, int);
int size_count_partial(const dvar3_array & x, int);
int size_count_partial(const dvector & x, int);
int size_count_partial(const dmatrix & x, int);
int size_count_partial(const d3_array & x, int);

int min(int, int);
// ********************************************************
// Prototypes for compiled derivative calculations
void dfinvpret(void);
void dvdv_dot(void);
void dmdm_prod(void);
void dv_init(void);


// ********************************************************
int save_identifier_string(const char *);
void insert_identifier_string(const char *s);
void verify_identifier_string(const char *);


ivector restore_ivector_value(const ivector_position &);
ivector_position restore_ivector_position(void);
dvar_matrix_position restore_dvar_matrix_position(void);
dvector restore_dvar_matrix_derivative_row(const dvar_matrix_position& pos,
  const int &ii);
dvector restore_dvar_matrix_derivative_column(const dvar_matrix_position& pos,
  const int &ii);
dmatrix restore_dvar_matrix_derivatives(const dvar_matrix_position & pos);
dmatrix restore_dvar_matrix_derivatives(void);
double restore_prevariable_derivative(void);
double restore_double_value(void);
int restore_int_value(void);
void save_double_value(double x);
void save_int_value(int x);
void save_pointer_value(void *ptr);
void *restore_pointer_value(void);
dvar_matrix nograd_assign_trans(const dmatrix & m);
dvar_matrix nograd_assign(const dmatrix &);
dvariable nograd_assign(double tmp);
dvar_vector nograd_assign(dvector tmp);
dmatrix restore_dvar_matrix_value(const dvar_matrix_position & mpos);
dmatrix_position restore_dmatrix_position(void);
dvector_position restore_dvector_position(void);
dvector restore_dvector_value(const dvector_position &);
dmatrix restore_dmatrix_value(const dmatrix_position &);
dvector restore_dvar_matrix_derivatives(const dvar_matrix_position & pos,
  const int &ii);
dvector restore_dvar_vector_derivatives(const dvar_vector_position & tmp);
dmatrix restore_dvar_matrix_derivatives(const dvar_matrix_position & pos);
void save_dmatrix_derivatives(const dvar_matrix_position & pos, double x,
  const int &i, int &j);
dmatrix restore_dvar_matrix_der_nozero(const dvar_matrix_position & pos);
dvector restore_dvar_vector_der_nozero(const dvar_vector_position & tmp);
d3_array_position restore_d3_array_position(void);
d3_array restore_d3_array_value(const d3_array_position &);
void nograd_assign_row(const dvar_matrix & m, const dvector & v,
  const int &ii);
void nograd_assign_column(const dvar_matrix & m, const dvector & v,
  const int &ii);

long int reset_gs_stack(void);
void reset_gs_stack(long int);

dvar_vector solve(const dvar_matrix & aa, const dvar_vector & z);
dvar_vector solve(const dvar_matrix & aa, const dvar_vector & z,
  prevariable & ln_unsigned_det, const prevariable & sign);

//dvar_vector solve(const dvar_matrix& aa, const dvar_vector& z,
 // prevariable& ln_unsigned_det, const prevariable& sign);

dvector csolve(const dmatrix & aa, const dvector & z);
dvector solve(const dmatrix & aa, const dvector & z);
dvector solve(const dmatrix & aa, const dvector & z,
  const double &ln_unsigned_det, double &sign);

dmatrix choleski_decomp(const dmatrix & M);
dmatrix choleski_decomp_error(const dmatrix & M, int &ierror);
dmatrix choleski_decomp_neghess_error(const dmatrix & M, int &ierror);
dmatrix choleski_decomp_positive(const dmatrix & MM, const int &ierr);
dmatrix choleski_decomp_positive(const dmatrix & MM, double bound);
dvar_matrix choleski_decomp(const dvar_matrix & M);

dvar_matrix solve(const dvar_matrix & aa, const dvar_matrix & zz);
dmatrix expm(const dmatrix & A);
dvar_matrix expm(const dvar_matrix & A);

dvariable factln(const dvariable & n);
double factln(double n);
dvar_vector factln(const dvar_vector & n);
dvector factln(const dvector & n);

dvariable invlogit(dvariable x);


dvar_vector posfun(const dvar_vector & x, double eps, const prevariable & pen);
dvariable posfun(const dvariable& x, const double eps, const prevariable & pen);
dvariable posfun2(const dvariable& x, const double eps, const prevariable& pen);
double posfun(const double &x, const double eps, const double &_pen);
double posfun2(const double &x, const double eps, const double &_pen);
double dfposfun(const double &x, const double eps);
dvariable dfposfun(const prevariable & x, const double eps);
double dfposfun1(const double &x, const double eps);
dvar_vector log_comb(const dvar_vector & n, const dvector & k);
dvariable log_comb(double n, const dvariable & k);
dvar_vector log_comb(const dvar_vector & n, const dvar_vector & k);
dvar_vector log_comb(const dvector & n, const dvar_vector & k);
dvar_vector log_comb(double n, const dvar_vector & k);
dvar_vector log_comb(const dvariable & n, const dvector & k);
dvar_vector log_comb(const dvariable & n, const dvar_vector & k);
dvariable log_comb(const dvariable & n, double k);
dvariable log_comb(const dvariable & n, const dvariable & k);
dvector log_comb(const dvector & n, const dvector & k);
dvector log_comb(double n, const dvector & k);
double log_comb(double n, double k);
dmatrix orthpoly(int n, int deg);
dmatrix orthpoly(int n, int deg, int skip);
dvar_vector gammln(const dvar_vector & n);
dvector gammln(const dvector & n);

/**
 * Description not yet available.
 * \param
 */
class dvar_vector_position
{
public:
  dvar_vector_position();
  dvar_vector_position(const dvar_vector& v);
  dvar_vector_position(const dvar_vector_position& dvp);

  double &operator() (const int &i);

  int min;
  int max;
  double_and_int* va;
  int indexmin() const
  {
    return min;
  }
  int indexmax() const
  {
    return max;
  }

  friend class dvar_matrix_position;
};

/**
 * Description not yet available.
 * \param
 */
class dvar_matrix_position
{
 public:
   int row_min;
   int row_max;
   ivector lb;
   ivector ub;
   ptr_vector ptr;
   dvar_matrix_position(const dvar_matrix &, int);
   dvar_matrix_position(int min, int max);
   dvar_matrix_position(const dvar_matrix_position &);
   dvar_vector_position operator () (int i);
   int &rowmin(void)
   {
      return row_min;
   }
   int &rowmax(void)
   {
      return row_max;
   }
   ivector & colmin(void)
   {
      return lb;
   }
   ivector & colmax(void)
   {
      return ub;
   }
   friend ostream & operator<<(const ostream &, const dvar_matrix_position &);
   friend class dmatrix_position;
   friend class dmatrix;
};

dvar_matrix use_shape(const dvar_matrix & m);
dmatrix use_shape(const dmatrix & m);

/**
 * Description not yet available.
 * \param
 */
class dmatrix_position
{
 public:
   int row_min;
   int row_max;
   ivector lb;
   ivector ub;
   ptr_vector ptr;
   dmatrix_position(const dmatrix &);
   dmatrix_position(int min, int max);
   dmatrix_position(const dmatrix_position &);
   dvector_position operator () (int i);
   friend class dmatrix;
};

/**
 * Description not yet available.
 * \param
 */
class d3_array_position
{
   int min;
   int max;
 public:
   d3_array_position(int mmin, int mmax);

   int indexmin() const
   {
      return min;
   }
   int indexmax() const
   {
      return max;
   }
};

/**
 * Description not yet available.
 * \param
 */
class dvector_position
{
   int min;
   int max;
   double *v;
 public:
   dvector_position(const dvector & v);
   dvector_position(const dvector_position & dvp);
   dvector_position(void);
   int indexmin() const
   {
      return min;
   }
   int indexmax() const
   {
      return max;
   }
   friend class dmatrix_position;
};

/**
 * Description not yet available.
 * \param
 */
class ivector_position
{
   int min;
   int max;
   int *v;
 public:
   ivector_position(void);
   ivector_position(const ivector & v);
   ivector_position(const ivector_position & dvp);
   int indexmin() const
   {
      return min;
   }
   int indexmax() const
   {
      return max;
   }
};

ostream & operator<<(const ostream & s, const ptr_vector & ptr);
ostream & operator<<(const ostream &, const dvar_matrix_position &);

char which_library();

/**
 * Description not yet available.
 * \param
 */
class fmmq:public fmm_control
{
 private:
   dvector h;
   dvector w;
   dvector funval;

   double dmin, fbest, df;
   long int llog, n1, ic, iconv, i1, link;
   double z, zz, gys, gs, sig, gso, alpha, tot, fy, dgs;
   long int itn, icc, np, nn, is, iu, iv, ib, ifn;
   int i, j;
   double gmax;
   double fsave;
   dvector gbest;
   dvector xbest;
   dvector xsave;
   dvector gsave;
   dvector scale;
   dvector xa;
   dvector xb;
   dvector d;
   dvector ga;
   dvector gb;
   int mode;
   int igwindow;
   int ir;
   int isfv;
   int istart;
   int istop;
   double c;
   double cc;
   double dff;
   double fa;
   double fb;
   double dga;
   double dgb;
   double stmin;
   double stepbd;
   double tfmin;
   double gmin;
   double step;
   double gl1;
   double gl2;
   unsigned int k;
   int ititle;
   int print;
   int ipra;
   int ip;
   int n;
 public:
   fmmq(int nvar);
   fmmq(int nvar, const lvector & ipar);
   double minimize(const dvector & x, double (*pf) (const dvar_vector &));
   double minimize(const independent_variables & x, const dvector & c,
     double (*pf) (const dvar_vector &, const dvector &));
   void fmin(const double &f, const dvector & x, const dvector & g);
   void va13c(const dvector & x, double f, const dvector & g);
};

/**
 * Description not yet available.
 * \param
 */
class vcubic_spline_function
{
   dvector x; // indep variables values
   dvar_vector y; // dep variable values
   dvar_vector y2; // second derivatives
 public:
   vcubic_spline_function(const dvector & _x, const dvar_vector & _y,
     double yp1 = 0.0, double ypn = 0.0);
   vcubic_spline_function(const dvector & _x, const dvar_vector & _y,
     dvariable yp1, dvariable ypn);
   vcubic_spline_function(const dvector & _x, const dvar_vector & _y,
     dvariable yp1);
   dvariable operator   () (double u);
   dvar_vector operator () (const dvector & u);
   dvar_vector operator () (const dvar_vector & u);
};

/**
 * Description not yet available.
 * \param
 */
class cubic_spline_function
{
   dvector x; // indep variables values
   dvector y; // dep variable values
   dvector y2; // second derivatives
 public:
   cubic_spline_function(const dvector & _x, const dvector & _y,
     double yp1 = 0.0, double ypn = 0.0);
   double operator () (double u);
   dvector operator() (const dvector & u);
};

#ifdef __ZTC__
void *cdecl _farptr_norm(void *);
void *cdecl _farptr_fromlong(unsigned long int);
#endif
/*
#if DOS386==1
  #ifdef __NDPX__
    void * farptr_fromlong(long int);
    void * _farptr_fromlong(long int i);
  #elif __SUN__
    void * farptr_fromlong(long int);
  #elif __GNU__
    void * farptr_fromlong(long int);
  #elif __ZTC__
    void * _farptr_fromlong(unsigned long int i);
    void * _farptr_norm(void *);
  #else
    void * farptr_fromlong(long int);
  #endif
#else
  #ifdef __ZTC__
    void * _farptr_norm(void *);
    void * _farptr_fromlong(unsigned long int);
  #else
    void * farptr_fromlong(long int);
  #endif
#endif
*/

// this is the speical version with an index for reordering the matrix
void ludcmp_index(const dmatrix & a, const ivector & indx, const double &d);

void ludcmp(const dmatrix & a, const ivector & indx, const double &d);

/**
 * Description not yet available.
 * \param
 */
class function_tweaker
{
   double mult;
   double eps;
   dvector coffs;
 public:
   function_tweaker(double eps, double mult);
   double operator () (double);
};

/**
 * Description not yet available.
 * \param
 */
class dfunction_tweaker
{
   double mult;
   double eps;
   dvector coffs;
 public:
   dfunction_tweaker(double eps, double mult);
   dvariable operator () (const prevariable &);
};

/**
 * Description not yet available.
 * \param
 */
class four_array_shape
{
   unsigned int ncopies;
   int hslice_min;
   int hslice_max;
   //int slice_min;
   //int slice_max;
   //int row_min;
   //int row_max;
   //int col_min;
   //int col_max;
   four_array_shape(int hsl, int hsu);//, int sl,int sh,int rl,
   // int ru,int cl,int cu);
   //mat_shape(){};

   friend class d4_array;
   friend class dvar4_array;
};

/**
 * Description not yet available.
 * \param
 */
class d4_array
{
   four_array_shape *shape;
   d3_array *t;
 public:
   void shallow_copy(const d4_array &);
   d4_array(int, int);
   d4_array sub(int, int);
   void allocate(int hsl, int hsu, int sl, int sh, int nrl, int nrh, int ncl,
     int nch);
   void allocate(int hsl, int hsu, int sl, const ivector & sh, int nrl,
     const imatrix & nrh, int ncl, const imatrix & nch);
   void allocate(int hsl, int hsu, int sl, const ivector & sh, int nrl,
     const imatrix & nrh, int ncl, const i3_array & nch);
   void allocate(int hsl, int hsu, int sl, int sh, int nrl,
     int nrh, const ivector & ncl, const ivector & nch);
   void allocate(int hsl, int hsu, int sl, int sh, const ivector & nrl,
     const ivector & nrh, const ivector & ncl, const ivector & nch);
   void allocate(int hsl, int hsu, int sl, const ivector & sh, int nrl,
     const imatrix & nrh, int ncl, int nch);
   void deallocate(void);
   void allocate(void);
   void allocate(const d4_array &);
   void allocate(const dvar4_array &);
   int operator!(void) const
   {
      return (shape == NULL);
   }
   d4_array(int hsl, int hsu, int sl, int sh, ivector nrl, ivector nrh,
     ivector ncl, ivector nch);

   d4_array(int hsl, int hsu, int sl, const ivector & sh, int nrl,
     const imatrix & nrh, int ncl, const i3_array & nch);

   d4_array(int hsl, int hsu, const index_type & sl, const index_type & sh,
     const index_type & nrl, const index_type & nrh, const index_type & ncl,
     const index_type & nch);

   void allocate(int hsl, int hsu, const index_type & sl, const index_type& sh,
     const index_type & nrl, const index_type & nrh, const index_type & ncl,
     const index_type & nch);
   void allocate(ad_integer hsl, ad_integer hsu, const index_type & sl,
     const index_type & sh, const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch);

   void allocate(ad_integer hsl, ad_integer hsu, const index_type & sl,
     const index_type & sh, const index_type & nrl, const index_type & nrh);
   void allocate(ad_integer hsl, ad_integer hsu, const index_type & sl,
     const index_type & sh);
   void allocate(ad_integer hsl, ad_integer hsu);

   d4_array & operator=(const d4_array &);
   d4_array(const d4_array & m2);
   d4_array(int, int, int, int, int, int, int, int);
   //d4_array(int,int,int,ivector,int,imatrix,int,int);
   d4_array(int hsl, int hsu, int sl, const ivector & sh, int nrl,
     const imatrix & nrh, int ncl, int nch);
   d4_array();
   ~d4_array();
   d3_array & elem(int i)
   {
      return t[i];
   }
   dmatrix & elem(int i, int j)
   {
      return ((*this) (i)) (j);
   }
   dvector & elem(int i, int j, int k)
   {
      return (((*this) (i, j)) (k));
   }
   double &elem(int i, int j, int k, int l)
   {
      return (((*this) (i, j, k)) (l));
   }
   const d3_array & elem(int i) const
   {
      return t[i];
   }
   const dmatrix & elem(int i, int j) const
   {
      return ((*this) (i)) (j);
   }
   const dvector & elem(int i, int j, int k) const
   {
      return (((*this) (i, j)) (k));
   }
   const double &elem(int i, int j, int k, int l) const
   {
      return (((*this) (i, j, k)) (l));
   }
   const d3_array& operator()(int i) const;
   const d3_array& operator[](int i) const;
   const dmatrix& operator()(int i, int j) const;
   const dvector& operator()(int i, int j, int k) const;
   const double& operator()(int i, int j, int k, int l) const;
   d3_array& operator()(int);
   d3_array& operator[](int);
   dmatrix& operator()(int, int);
   dvector& operator()(int, int, int);
   double& operator()(int, int, int, int);

   //access functions
   friend class four_array_shape;

   int slicemin(void)
   {
      return ((*this) (hslicemin()).slicemin());
   }
   int slicemax(void)
   {
      return ((*this) (hslicemin()).slicemax());
   }
   int rowmin(void)
   {
      return ((*this) (hslicemin(), slicemin()).rowmin());
   }
   int rowmax(void)
   {
      return ((*this) (hslicemin(), slicemin()).rowmax());
   }
   int colmin(void)
   {
      return ((*this) (hslicemin(), slicemin(), rowmax()).indexmin());
   }
   int colmax(void)
   {
      return ((*this) (hslicemin(), slicemin(), rowmax()).indexmax());
   }
   // returns the number of rows
   int slicesize()
   {
      return (slicemax() - slicemin() + 1);
   }
   // returns the number of rows
   int rowsize()
   {
      return (rowmax() - rowmin() + 1);
   }
   // returns the number of columns
   int colsize()
   {
      return (colmax() - colmin() + 1);
   }
  int indexmin() const
  {
    return hslicemin();
  }
  int indexmax() const
  {
    return hslicemax();
  }
  int hslicemin() const
  {
    return shape ? shape->hslice_min : 1;
  }
  int hslicemax() const
  {
    return shape ? shape->hslice_max : 0;
  }
   int slicemin(void) const
   {
      return ((*this) (hslicemin()).slicemin());
   }
   int slicemax(void) const
   {
      return ((*this) (hslicemin()).slicemax());
   }
   int rowmin(void) const
   {
      return ((*this) (hslicemin(), slicemin()).rowmin());
   }
   int rowmax(void) const
   {
      return ((*this) (hslicemin(), slicemin()).rowmax());
   }
   int colmin(void) const
   {
      return ((*this) (hslicemin(), slicemin(), rowmax()).indexmin());
   }
   int colmax(void) const
   {
      return ((*this) (hslicemin(), slicemin(), rowmax()).indexmax());
   }

   //int hslicemin(void) const { return(shape->hslice_min);}
   //int hslicemax(void) const { return(shape->hslice_max);}
   //int slicemin(void) const { return(shape->slice_min);}
   //int slicemax(void) const { return(shape->slice_max);}
   //int colmin(void) const { return(shape->col_min);}
   //int colmax(void) const { return(shape->col_max);}
   //int rowmin(void) const { return(shape->row_min);}
   //int rowmax(void) const { return(shape->row_max);}

  // returns the number of rows
  unsigned int hslicesize() const
  {
    return static_cast<unsigned int>(hslicemax() - hslicemin() + 1);
  }

   // returns the number of rows
   int slicesize() const
   {
      return (slicemax() - slicemin() + 1);
   }
   // returns the number of rows
   int rowsize() const
   {
      return (rowmax() - rowmin() + 1);
   }
   // returns the number of columns
   int colsize() const
   {
      return (colmax() - colmin() + 1);
   }
   void operator /=(double d);
  void initialize();
  unsigned int get_ncopies() const { return shape ? shape->ncopies : 0; }
};
#ifdef OPT_LIB
inline d3_array& d4_array::operator()(int i)
{
  return t[i];
}
inline d3_array& d4_array::operator[](int i)
{
  return t[i];
}
inline dmatrix& d4_array::operator()(int i, int j)
{
  return ((*this)(i))(j);
}
inline dvector& d4_array::operator()(int i, int j, int k)
{
  return ((*this)(i, j))(k);
}
inline double& d4_array::operator()(int i, int j, int k, int l)
{
  return ((*this)(i, j, k))(l);
}
inline const d3_array& d4_array::operator()(int i) const
{
  return t[i];
}
inline const d3_array& d4_array::operator[](int i) const
{
  return t[i];
}
inline const dmatrix& d4_array::operator()(int i, int j) const
{
  return ((*this)(i))(j);
}
inline const dvector& d4_array::operator()(int i, int j, int k) const
{
  return ((*this)(i, j))(k);
}
inline const double& d4_array::operator()(int i, int j, int k, int l) const
{
  return ((*this)(i, j, k))(l);
}
#endif

d4_array operator/(const d4_array & m, double d);
d4_array operator/(double d, const d4_array & m);
#ifndef D4ARR_HPP
#define D4ARR_HPP
#endif

/**
 * Description not yet available.
 * \param
 */
class dvar4_array
{
   four_array_shape *shape;
   dvar3_array *t;
 public:
   void shallow_copy(const dvar4_array &);
   dvar4_array(int, int);
   dvar4_array sub(int, int);
   void allocate(int hsl, int hsu, int sl, int sh, int nrl, int nrh, int ncl,
     int nch);
   void allocate(int hsl, int hsu, int sl, int sh, int nrl, int nrh,
     const ivector & ncl, const ivector & nch);
   void allocate(int hsl, int hsu, int sl, int sh, const ivector & nrl,
     const ivector & nrh, const ivector & ncl, const ivector & nch);
   void allocate(ad_integer, ad_integer, const index_type&, const index_type&,
    const index_type&, const index_type&, const index_type&, const index_type&);
   void allocate(ad_integer, ad_integer, const index_type &, const index_type &,
     const index_type &, const index_type &);
   void allocate(ad_integer, ad_integer, const index_type&, const index_type &);
   void allocate(ad_integer, ad_integer);

   void deallocate(void);
   void allocate(void);
   void allocate(const d4_array &);
   void allocate(const dvar4_array &);
   int operator!(void) const
   {
      return (shape == NULL);
   }
   dvar4_array(int hsl, int hsu, int sl, int sh, ivector nrl, ivector nrh,
     ivector ncl, ivector nch);
   dvar4_array(const d4_array & m1);
   dvar4_array(const dvar4_array & m2);
   dvar4_array(int, int, int, int, int, int, int, int);

   dvar4_array(ad_integer, ad_integer, const index_type &, const index_type &,
     const index_type &, const index_type &, const index_type &,
     const index_type &);

   dvar4_array(int hsl, int hsu, int sl, const ivector & sh, int nrl,
     const imatrix & nrh, int ncl, int nch);
   void allocate(int hsl, int hsu, int sl, const ivector & sh, int nrl,
     const imatrix & nrh, int ncl, int nch);
   //dvar4_array(int,int,int,ivector,int,imatrix,int,int);
   dvar4_array();
   ~dvar4_array();
   dvar3_array & elem(int i)
   {
      return t[i];
   }
   dvar_matrix & elem(int i, int j)
   {
      return ((*this) (i)) (j);
   }
   dvar_vector & elem(int i, int j, int k)
   {
      return (((*this) (i, j)) (k));
   }
   prevariable elem(int i, int j, int k, int l)
   {
      return (((*this) (i, j, k)) (l));
   }
   const dvar3_array & elem(int i) const
   {
      return t[i];
   }
   const dvar_matrix & elem(int i, int j) const
   {
      return ((*this) (i)) (j);
   }
   const dvar_vector & elem(int i, int j, int k) const
   {
      return (((*this) (i, j)) (k));
   }
   const prevariable elem(int i, int j, int k, int l) const
   {
      return (((*this) (i, j, k)) (l));
   }

   d4_array vale(d4_array &);
   dvar4_array & operator=(const d4_array &);
   dvar4_array & operator=(const dvar4_array &);
#ifdef OPT_LIB
   dvar3_array & operator ()(int i)
   {
      return t[i];
   }
   dvar3_array & operator [](int i)
   {
      return t[i];
   }
   dvar_matrix & operator ()(int i, int j)
   {
      return ((*this) (i)) (j);
   }
   dvar_vector & operator ()(int i, int j, int k)
   {
      return (((*this) (i, j)) (k));
   }
   prevariable operator () (int i, int j, int k, int l)
   {
      return (((*this) (i, j, k)) (l));
   }
   inline const dvar3_array & operator() (int i) const
   {
      return t[i];
   }
   inline const dvar3_array & operator[] (int i) const
   {
      return t[i];
   }
   inline const dvar_matrix & operator() (int i, int j) const
   {
      return ((*this) (i)) (j);
   }
   inline const dvar_vector & operator() (int i, int j, int k) const
   {
      return (((*this) (i, j)) (k));
   }
   inline const prevariable operator() (int i, int j, int k, int l) const
   {
      return (((*this) (i, j, k)) (l));
   }
#else
   const dvar3_array & operator() (int i) const;
   const dvar3_array & operator[] (int i) const;
   const dvar_matrix & operator() (int i, int j) const;
   const dvar_vector & operator() (int i, int j, int k) const;
   const prevariable operator() (int i, int j, int k, int l) const;
   dvar3_array & operator ()(int);
   dvar3_array & operator [](int);
   dvar_matrix & operator ()(int, int);
   dvar_vector & operator ()(int, int, int);
   prevariable operator () (int, int, int, int);
#endif
   //access functions
   friend class four_array_shape;

   int slicemin(void)
   {
      return ((*this) (hslicemin()).slicemin());
   }
   int slicemax(void)
   {
      return ((*this) (hslicemin()).slicemax());
   }
   int rowmin(void)
   {
      return ((*this) (hslicemin(), slicemin()).rowmin());
   }
   int rowmax(void)
   {
      return ((*this) (hslicemin(), slicemin()).rowmax());
   }
   int colmin(void)
   {
      return ((*this) (hslicemin(), slicemin(), rowmax()).indexmin());
   }
   int colmax(void)
   {
      return ((*this) (hslicemin(), slicemin(), rowmax()).indexmax());
   }

   //int hslicemin(void) { return(shape->hslice_min);}
   //int hslicemax(void) { return(shape->hslice_max);}
   //int slicemin(void) { return(shape->slice_min);}
   //int slicemax(void) { return(shape->slice_max);}
   //int colmin(void) { return(shape->col_min);}
   //int colmax(void) { return(shape->col_max);}
   //int rowmin(void) { return(shape->row_min);}
   //int rowmax(void) { return(shape->row_max);}

   // returns the number of rows
   int slicesize()
   {
      return (slicemax() - slicemin() + 1);
   }
   // returns the number of rows
   int rowsize()
   {
      return (rowmax() - rowmin() + 1);
   }
   // returns the number of columns
   int colsize()
   {
      return (colmax() - colmin() + 1);
   }

  int indexmin() const { return hslicemin(); }
  int indexmax() const { return hslicemax(); }
  int hslicemin() const { return shape ? shape->hslice_min : 1; }
  int hslicemax() const { return shape ? shape->hslice_max : 0; }

   int slicemin(void) const
   {
      return ((*this) (hslicemin()).slicemin());
   }
   int slicemax(void) const
   {
      return ((*this) (hslicemin()).slicemax());
   }
   int rowmin(void) const
   {
      return ((*this) (hslicemin(), slicemin()).rowmin());
   }
   int rowmax(void) const
   {
      return ((*this) (hslicemin(), slicemin()).rowmax());
   }
   int colmin(void) const
   {
      return ((*this) (hslicemin(), slicemin(), rowmax()).indexmin());
   }
   int colmax(void) const
   {
      return ((*this) (hslicemin(), slicemin(), rowmax()).indexmax());
   }
   //int hslicemin(void) const { return(shape->hslice_min); }
   //int hslicemax(void) const { return(shape->hslice_max); }
   //int slicemin(void) const { return(shape->slice_min); }
   //int slicemax(void) const { return(shape->slice_max); }
   //int colmin(void) const { return(shape->col_min); }
   //int colmax(void) const { return(shape->col_max); }
   //int rowmin(void) const { return(shape->row_min); }
   //int rowmax(void) const { return(shape->row_max); }

  // returns the number of rows
  unsigned int hslicesize() const
  {
    return static_cast<unsigned int>(hslicemax() - hslicemin() + 1);
  }

   // returns the number of rows
   int slicesize() const
   {
      return (slicemax() - slicemin() + 1);
   }
   // returns the number of rows
   int rowsize() const
   {
      return (rowmax() - rowmin() + 1);
   }
// returns the number of columns
   int colsize() const
   {
      return (colmax() - colmin() + 1);
   }
   void initialize(void);
   void operator/=(const prevariable & d);
   void operator/=(const double &d);

  unsigned int get_ncopies() const { return shape ? shape->ncopies : 0; }
};

dvar4_array operator/(const d4_array & m, const prevariable & d);
dvar4_array operator/(const dvar4_array & m, double d);
dvar4_array operator/(const dvar4_array & m, const prevariable & d);

dvar5_array operator/(const d5_array & m, const prevariable & d);
dvar5_array operator/(const dvar5_array & m, double d);
dvar5_array operator/(const dvar5_array & m, const prevariable & d);

d4_array log(const d4_array & x);
dvar4_array log(const dvar4_array & x);
d4_array mfexp(const d4_array & x);
dvar4_array mfexp(const dvar4_array & x);
d4_array exp(const d4_array & x);
dvar4_array exp(const dvar4_array & x);
d4_array sqrt(const d4_array & x);
dvar4_array sqrt(const dvar4_array & x);

d5_array log(const d5_array & x);
dvar5_array log(const dvar5_array & x);
d5_array mfexp(const d5_array & x);
dvar5_array mfexp(const dvar5_array & x);
d5_array exp(const d5_array & x);
dvar5_array exp(const dvar5_array & x);
d5_array sqrt(const d5_array & x);
dvar5_array sqrt(const dvar5_array & x);

ostream & operator<<(const ostream & ostr, const d4_array & z);
ostream & operator<<(const ostream & ostr, const d5_array & z);
ostream & operator<<(const ostream & ostr, const d6_array & z);
istream & operator>>(const istream & istr, const d4_array & z);
istream & operator>>(const istream & istr, const d5_array & z);
istream & operator>>(const istream & istr, const d6_array & z);
ostream & operator<<(const ostream & ostr, const dvar4_array & z);
ostream & operator<<(const ostream & ostr, const dvar5_array & z);
ostream & operator<<(const ostream & ostr, const dvar6_array & z);
istream & operator>>(const istream & istr, const dvar4_array & z);
istream & operator>>(const istream & istr, const dvar5_array & z);
istream & operator>>(const istream & istr, const dvar6_array & z);

/**
 * Description not yet available.
 * \param
 */
class fmmt:public fmm_control
{
 private:
   dvector w;
   dvector funval;
   int m;
   int diagco;
 public:
   double dmin, fbest, df;
   double gmax;
   dvector gbest;
   dvector xbest;
   dvector diag;
   double eps;
   double xtol;
   double gtol;
   int nvar;
   long int iter;
   int ireturn1;
   int curriter;
   ivector iprint1;

 public:
   double minimize(const independent_variables & x,
     double (*pf) (const dvar_vector &));
   fmmt(int _nvar, int _m = 7);

   double minimize(const independent_variables & x, const dvector & c,
     double (*pf) (const dvar_vector &, const dvector &));

   void fmin(const double &f, const dvector & x, const dvector & g);

   dmatrix & hessian();
};

/**
 * Description not yet available.
 * \param
 */
class i4_array
{
   vector_shapex *shape;
   i3_array *t;
 public:
   void allocate(int hsl, int hsu, int sl, int sh, int nrl, int nrh, int ncl,
     int nch);

   void allocate(const ad_integer & hsl, const ad_integer & hsu,
     const index_type & sl, const index_type & sh,
     const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch);

   void shallow_copy(const i4_array &);
   void deallocate(void);
   void allocate(void);
   void allocate(const i4_array &);
   void allocate(const dvar4_array &);
   int operator!(void) const
   {
      return (shape == NULL);
   }
   i4_array(int hsl, int hsu, int sl, int sh, ivector nrl, ivector nrh,
     ivector ncl, ivector nch);

   i4_array(int hsl, int hsu);
   void allocate(int hsl, int hsu);

   i4_array(int hsl, int hsu, int sl, const ivector & sh, int nrl,
     const imatrix & nrh, int ncl, const i3_array & nch);

   i4_array(const ad_integer & hsl, const ad_integer & hsh,
     const index_type & sl, const index_type & sh,
     const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch);

   i4_array & operator=(const i4_array &);
   i4_array(const i4_array & m2);
   i4_array(int, int, int, int, int, int, int, int);
   //i4_array(int,int,int,ivector,int,imatrix,int,int);
   i4_array(int hsl, int hsu, int sl, const ivector & sh,
     int nrl, const imatrix & nrh, int ncl, int nch);
   i4_array();
   ~i4_array();

  i3_array& elem(int i);
  const i3_array& elem(int i) const;

  imatrix& elem(int i, int j)
  {
    return elem(i)(j);
  }
  ivector& elem(int i, int j, int k)
  {
    return elem(i)(j, k);
  }
  int& elem(int i, int j, int k, int l)
  {
    return elem(i)(j, k, l);
  }

  i3_array& operator()(int i);
  i3_array& operator[](int j);
  imatrix& operator()(int i, int j);
  ivector& operator()(int i, int j, int k);
  int& operator()(int i, int j, int k, int l);
  const i3_array& operator()(int i) const;
  const i3_array& operator[](int i) const;
  const imatrix& operator()(int i, int j) const;
  const ivector& operator()(int i, int j, int k) const;
  const int& operator()(int i, int j, int k, int l) const;

   //access functions
   friend class four_array_shape;

   int slicemin(void)
   {
      return ((*this) (hslicemin()).slicemin());
   }
   int slicemax(void)
   {
      return ((*this) (hslicemin()).slicemax());
   }
   int rowmin(void)
   {
      return ((*this) (hslicemin(), slicemin()).rowmin());
   }
   int rowmax(void)
   {
      return ((*this) (hslicemin(), slicemin()).rowmax());
   }
   int colmin(void)
   {
      return ((*this) (hslicemin(), slicemin(), rowmax()).indexmin());
   }
   int colmax(void)
   {
      return ((*this) (hslicemin(), slicemin(), rowmax()).indexmax());
   }
   // returns the number of rows
   int hslicesize()
   {
      return (hslicemax() - hslicemin() + 1);
   }
   // returns the number of rows
   int size()
   {
      return (indexmax() - indexmin() + 1);
   }
   // returns the number of rows
   int slicesize()
   {
      return (slicemax() - slicemin() + 1);
   }
   // returns the number of rows
   int rowsize()
   {
      return (rowmax() - rowmin() + 1);
   }
   // returns the number of columns
   int colsize()
   {
      return (colmax() - colmin() + 1);
   }
  int indexmin() const
  {
    return hslicemin();
  }
  int indexmax() const
  {
    return hslicemax();
  }
  int hslicemin() const
  {
    return shape ? shape->indexmin() : 1;
  }
  int hslicemax() const
  {
    return shape ? shape->indexmax() : 0;
  }
   int slicemin(void) const
   {
      return ((*this) (hslicemin()).slicemin());
   }
   int slicemax(void) const
   {
      return ((*this) (hslicemin()).slicemax());
   }
   int rowmin(void) const
   {
      return ((*this) (hslicemin(), slicemin()).rowmin());
   }
   int rowmax(void) const
   {
      return ((*this) (hslicemin(), slicemin()).rowmax());
   }
   int colmin(void) const
   {
      return ((*this) (hslicemin(), slicemin(), rowmax()).indexmin());
   }
   int colmax(void) const
   {
      return ((*this) (hslicemin(), slicemin(), rowmax()).indexmax());
   }
  int hslicesize() const
  {
    return indexmax() - indexmin() + 1;
  }
   int size() const
   {
      return (indexmax() - indexmin() + 1);
   }
   // returns the number of rows
   int slicesize() const
   {
      return (slicemax() - slicemin() + 1);
   }
   // returns the number of rows
   int rowsize() const
   {
      return (rowmax() - rowmin() + 1);
   }
   // returns the number of columns
   int colsize() const
   {
      return (colmax() - colmin() + 1);
   }
  void initialize();
  unsigned int get_ncopies() const { return shape ? shape->ncopies : 0; }
};
inline i3_array& i4_array::elem(int i)
{
  if (i < indexmin() || i > indexmax())
  {
    cerr << "Index out of bounds in "
         << "i4_array::elem(int).\n";
    ad_exit(1);
  }
  return t[i];
}
inline const i3_array& i4_array::elem(int i) const
{
  if (i < indexmin() || i > indexmax())
  {
    cerr << "Index out of bounds in "
         << "i4_array::elem(int).\n";
    ad_exit(1);
  }
  return t[i];
}
inline i3_array& i4_array::operator()(int i)
{
#ifdef OPT_LIB
  return t[i];
#else
  return elem(i);
#endif
}
inline i3_array& i4_array::operator[](int i)
{
#ifdef OPT_LIB
  return t[i];
#else
  return elem(i);
#endif
}
inline imatrix& i4_array::operator()(int i, int j)
{
#ifdef OPT_LIB
  return t[i](j);
#else
  return elem(i)(j);
#endif
}
inline ivector& i4_array::operator()(int i, int j, int k)
{
#ifdef OPT_LIB
  return t[i](j, k);
#else
  return elem(i)(j, k);
#endif
}
inline int& i4_array::operator()(int i, int j, int k, int a)
{
#ifdef OPT_LIB
  return t[i](j, k, a);
#else
  return elem(i)(j, k, a);
#endif
}
inline const i3_array& i4_array::operator()(int i) const
{
#ifdef OPT_LIB
  return t[i];
#else
  return elem(i);
#endif
}
inline const i3_array& i4_array::operator[](int i) const
{
#ifdef OPT_LIB
  return t[i];
#else
  return elem(i);
#endif
}
inline const imatrix& i4_array::operator()(int i, int j) const
{
#ifdef OPT_LIB
  return t[i](j);
#else
  return elem(i)(j);
#endif
}
inline const ivector& i4_array::operator()(int i, int j, int k) const
{
#ifdef OPT_LIB
  return t[i](j, k);
#else
  return elem(i)(j, k);
#endif
}
inline const int& i4_array::operator()(int i, int j, int k, int a) const
{
#ifdef OPT_LIB
  return t[i](j, k, a);
#else
  return elem(i)(j, k, a);
#endif
}

ostream& operator<<(const ostream& output, const i4_array& iarray);
istream& operator>>(const istream& input, const i4_array& iarray);

/**
 * Description not yet available.
 * \param
 */
class i5_array
{
   vector_shapex *shape;
   i4_array *t;
 public:
   void allocate(int hhsl, int hhsu);

   void allocate(int hhsl, int hhsu, int hsl, int hsu, int sl, int sh, int nrl,
     int nrh, int ncl, int nch);

   void allocate(const ad_integer & hsl, const ad_integer & hsu,
     const index_type & sl, const index_type & sh, const index_type & nrl,
     const index_type & nrh, const index_type & ncl, const index_type & nch,
     const index_type & aa, const index_type & bb);

   void shallow_copy(const i5_array&);
   void deallocate(void);
   void allocate(void);
   void allocate(const i5_array &);
   //void allocate(const dvar4_array&);
   int operator!(void) const
   {
      return (shape == NULL);
   }
   i5_array(int hsl, int hsu);
   i5_array(int hsl, int hsu, int sl, int sh, ivector nrl, ivector nrh,
     ivector ncl, ivector nch);

   i5_array(int hsl, int hsu, int sl, const ivector & sh, int nrl,
     const imatrix & nrh, int ncl, const i3_array & nch);

   i5_array(const ad_integer & hsl, const ad_integer & hsh,
     const index_type & sl, const index_type & sh,
     const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch,
     const index_type & aa, const index_type & bb);

   i5_array & operator=(const i5_array &);
   i5_array(const i5_array & m2);
   i5_array(int, int, int, int, int, int, int, int);
   //i5_array(int,int,int,ivector,int,imatrix,int,int);
   i5_array(int hsl, int hsu, int sl, const ivector & sh,
     int nrl, const imatrix & nrh, int ncl, int nch);
   i5_array();
   ~i5_array();

  i4_array& elem(int i);
  const i4_array& elem(int i) const;

  i4_array& operator[](int);
  i4_array& operator()(int);
  i3_array& operator()(int, int);
  imatrix& operator()(int, int, int);
  ivector& operator()(int, int, int, int);
  int& operator()(int, int, int, int, int);
  const i4_array& operator[](int) const;
  const i4_array& operator()(int) const;
  const i3_array& operator()(int, int) const;
  const imatrix& operator()(int, int, int) const;
  const ivector& operator()(int, int, int, int) const;
  const int& operator()(int, int, int, int, int) const;

   //access functions
   friend class four_array_shape;

   int slicemin(void)
   {
      return ((*this) (hslicemin()).slicemin());
   }
   int slicemax(void)
   {
      return ((*this) (hslicemin()).slicemax());
   }
   int rowmin(void)
   {
      return ((*this) (hslicemin(), slicemin()).rowmin());
   }
   int rowmax(void)
   {
      return ((*this) (hslicemin(), slicemin()).rowmax());
   }
   int colmin(void)
   {
      return ((*this) (hslicemin(), slicemin(), rowmax()).indexmin());
   }
   int colmax(void)
   {
      return ((*this) (hslicemin(), slicemin(), rowmax()).indexmax());
   }

   // returns the number of rows
   int hslicesize()
   {
      return (hslicemax() - hslicemin() + 1);
   }
   // returns the number of rows
   int size()
   {
      return (indexmax() - indexmin() + 1);
   }
   // returns the number of rows
   int slicesize()
   {
      return (slicemax() - slicemin() + 1);
   }
   // returns the number of rows
   int rowsize()
   {
      return (rowmax() - rowmin() + 1);
   }
   // returns the number of columns
   int colsize()
   {
      return (colmax() - colmin() + 1);
   }
  int hslicemin() const
  {
    return shape ? shape->indexmin() : 1;
  }
  int hslicemax() const
  {
    return shape ? shape->indexmax() : 0;
  }
  int indexmin() const
  {
    return hslicemin();
  }
  int indexmax() const
  {
    return hslicemax();
  }
   int slicemin(void) const
   {
      return ((*this) (hslicemin()).slicemin());
   }
   int slicemax(void) const
   {
      return ((*this) (hslicemin()).slicemax());
   }
   int rowmin(void) const
   {
      return ((*this) (hslicemin(), slicemin()).rowmin());
   }
   int rowmax(void) const
   {
      return ((*this) (hslicemin(), slicemin()).rowmax());
   }
   int colmin(void) const
   {
      return ((*this) (hslicemin(), slicemin(), rowmax()).indexmin());
   }
   int colmax(void) const
   {
      return ((*this) (hslicemin(), slicemin(), rowmax()).indexmax());
   }
  int hslicesize() const
  {
    return indexmax() - indexmin() + 1;
  }
   int size() const
   {
      return (indexmax() - indexmin() + 1);
   }
   // returns the number of rows
   int slicesize() const
   {
      return (slicemax() - slicemin() + 1);
   }
   // returns the number of rows
   int rowsize() const
   {
      return (rowmax() - rowmin() + 1);
   }
   // returns the number of columns
   int colsize() const
   {
      return (colmax() - colmin() + 1);
   }
  void initialize();
  unsigned int get_ncopies() const { return shape ? shape->ncopies : 0; }
};
inline i4_array& i5_array::elem(int i)
{
#ifndef OPT_LIB
  if (i < indexmin() || i > indexmax())
  {
    cerr << "Index out of bounds in i5_array::elem(int).\n";
    ad_exit(1);
  }
#endif
  return t[i];
}
inline const i4_array& i5_array::elem(int i) const
{
#ifndef OPT_LIB
  if (i < indexmin() || i > indexmax())
  {
    cerr << "Index out of bounds in i5_array::elem(int).\n";
    ad_exit(1);
  }
#endif
  return t[i];
}
#ifdef OPT_LIB
inline i4_array& i5_array::operator()(int i)
{
  return t[i];
}
inline i4_array& i5_array::operator[](int i)
{
  return t[i];
}
inline i3_array& i5_array::operator()(int i, int j)
{
  return t[i](j);
}
inline imatrix& i5_array::operator()(int i, int j, int k)
{
  return t[i](j, k);
}
inline ivector& i5_array::operator()(int i, int j, int k, int l)
{
  return t[i](j, k, l);
}
inline int& i5_array::operator()(int i, int j, int k, int l, int m)
{
  return t[i](j, k, l, m);
}
inline const i4_array& i5_array::operator()(int i) const
{
  return t[i];
}
inline const i4_array& i5_array::operator[](int i) const
{
  return t[i];
}
inline const i3_array& i5_array::operator()(int i, int j) const
{
  return t[i](j);
}
inline const imatrix& i5_array::operator()(int i, int j, int k) const
{
  return t[i](j, k);
}
inline const ivector& i5_array::operator()(int i, int j, int k, int l) const
{
  return t[i](j, k, l);
}
inline const int& i5_array::operator()(int i, int j, int k, int l, int m) const
{
  return t[i](j, k, l, m);
}
#endif

ostream& operator<<(const ostream& output, const i5_array& iarray);
istream& operator>>(const istream& input, const i5_array& iarray);

// ***************************************************************
// ***************************************************************
// ***************************************************************
/**
 * Description not yet available.
 * \param
 */
class d5_array
{
   vector_shape *shape;
   d4_array *t;
 public:
   d5_array(int hhsl, int hhsu, int hsl, int hsu, int sl, int sh, int nrl,
     int nrh, int ncl, int nch);
   void allocate(int hhsl, int hhsu, int hsl, int hsu, int sl, int sh,
     int nrl, int nrh, int ncl, int nch);

   void allocate(int imin, int imax);

  void shallow_copy(const d5_array&);

   d5_array(int imin, int imax);

   d5_array(const ad_integer & hhsl, const ad_integer & hhsu,
     const index_type & hsl, const index_type & hsu, const index_type & sl,
     const index_type & sh, const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch);

   void allocate(const ad_integer & hhsl, const ad_integer & hhsu,
     const index_type & hsl, const index_type & hsu,
     const index_type & sl, const index_type & sh,
     const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch);

   void deallocate(void);
   void allocate(void);
   void allocate(const d5_array &);
   //void allocate(const dvar5_array&);
   int operator!(void) const
   {
      return (shape == NULL);
   }

   d5_array & operator=(const d5_array &);
   d5_array(const d5_array & m2);
   d5_array();
   ~d5_array();
   d4_array & elem(int i)
   {
      return t[i];
   }
   d3_array & elem(int i, int j)
   {
      return ((*this) (i)) (j);
   }
   dmatrix & elem(int i, int j, int k)
   {
      return (((*this) (i, j)) (k));
   }
   dvector & elem(int i, int j, int k, int l)
   {
      return (((*this) (i, j, k)) (l));
   }
   double &elem(int i, int j, int k, int l, int _m)
   {
      return (((*this) (i)) (j, k, l, _m));
   }
   const d4_array & elem(int i) const
   {
      return t[i];
   }
   const d3_array & elem(int i, int j) const
   {
      return ((*this) (i)) (j);
   }
   const dmatrix & elem(int i, int j, int k) const
   {
      return (((*this) (i, j)) (k));
   }
   const dvector & elem(int i, int j, int k, int l) const
   {
      return (((*this) (i, j, k)) (l));
   }
   const double &elem(int i, int j, int k, int l, int _m) const
   {
      return (((*this) (i)) (j, k, l, _m));
   }
#ifdef OPT_LIB
   d4_array & operator () (int i)
   {
      return t[i];
   }
   d4_array & operator [](int i)
   {
      return t[i];
   }
   d3_array & operator ()(int i, int j)
   {
      return ((*this) (i)) (j);
   }
   dmatrix & operator ()(int i, int j, int k)
   {
      return (((*this) (i, j)) (k));
   }
   dvector & operator ()(int i, int j, int k, int l)
   {
      return (((*this) (i)) (j, k, l));
   }
   double &operator () (int i, int j, int k, int l, int _m)
   {
      return (((*this) (i)) (j, k, l, _m));
   }
   inline const d4_array & operator() (int i) const
   {
      return t[i];
   }
   inline const d4_array & operator[] (int i) const
   {
      return t[i];
   }
   inline const d3_array & operator() (int i, int j) const
   {
      return ((*this) (i)) (j);
   }
   inline const dmatrix & operator() (int i, int j, int k) const
   {
      return (((*this) (i)) (j, k));
   }
   inline const dvector & operator() (int i, int j, int k, int l) const
   {
      return (((*this) (i)) (j, k, l));
   }
   inline const double &operator () (int i, int j, int k, int l, int _m) const
   {
      return (((*this) (i)) (j, k, l, _m));
   }
#else
   const d4_array & operator() (int i) const;
   const d4_array & operator[] (int i) const;
   const d3_array & operator() (int i, int j) const;
   const dmatrix & operator() (int i, int j, int k) const;
   const dvector & operator() (int i, int j, int k, int l) const;
   const double &operator() (int i, int j, int k, int l, int _m) const;
   d4_array & operator ()(int);
   d4_array & operator [](int);
   d3_array & operator ()(int, int);
   dmatrix & operator ()(int, int, int);
   dvector & operator ()(int, int, int, int);
   double &operator () (int, int, int, int, int);
#endif
  //access functions
  int indexmin() const
  {
    return shape ? shape->indexmin() : 1;
  }
  int indexmax() const
  {
    return shape ? shape->indexmax() : 0;
  }
  unsigned int size() const
  {
    return static_cast<unsigned int>(indexmax() - indexmin() + 1);
  }
  void initialize();
  void operator/=(double d);
  unsigned int get_ncopies() const { return shape ? shape->ncopies : 0; }
};

d5_array operator/(const d5_array & m, double d);

/**
 * Description not yet available.
 * \param
 */
class dvar5_array
{
  vector_shape* shape;
  dvar4_array* t;
public:
  dvar5_array();
  dvar5_array(const d5_array& darray);
  dvar5_array(const dvar5_array& other);
  dvar5_array(int hhsl, int hhsu);
  dvar5_array(int hhsl, int hhsu, int hsl, int hsu, int sl, int sh,
     int nrl, int nrh, int ncl, int nch);
  ~dvar5_array();

   dvar5_array sub(int hhsl, int hhsu);
   void shallow_copy(const dvar5_array &);
   void allocate(int hhsl, int hhsu, int hsl, int hsu, int sl, int sh,
     int nrl, int nrh, int ncl, int nch);

   dvar5_array(const ad_integer & hhsl, const ad_integer & hhsu,
     const index_type & hsl, const index_type & hsu,
     const index_type & sl, const index_type & sh,
     const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch);

   void allocate(int imin, int imax);

   void allocate(const ad_integer & hhsl, const ad_integer & hhsu,
     const index_type & hsl, const index_type & hsu,
     const index_type & sl, const index_type & sh,
     const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch);

   void deallocate(void);
   void allocate(void);
   void allocate(const d5_array &);
   void allocate(const dvar5_array &);
   int operator!(void) const
   {
      return (shape == NULL);
   }

   dvar5_array & operator=(const d5_array &);
   dvar5_array & operator=(const dvar5_array & m);
   dvar4_array & elem(int i)
   {
      return t[i];
   }
   dvar3_array & elem(int i, int j)
   {
      return ((*this) (i)) (j);
   }
   dvar_matrix & elem(int i, int j, int k)
   {
      return (((*this) (i, j)) (k));
   }
   dvar_vector & elem(int i, int j, int k, int l)
   {
      return (((*this) (i, j, k)) (l));
   }
   prevariable elem(int i, int j, int k, int l, int _m)
   {
      return (((*this) (i)) (j, k, l, _m));
   }
   const dvar4_array & elem(int i) const
   {
      return t[i];
   }
   const dvar3_array & elem(int i, int j) const
   {
      return ((*this) (i)) (j);
   }
   const dvar_matrix & elem(int i, int j, int k) const
   {
      return (((*this) (i, j)) (k));
   }
   const dvar_vector & elem(int i, int j, int k, int l) const
   {
      return (((*this) (i, j, k)) (l));
   }
   const prevariable elem(int i, int j, int k, int l, int _m) const
   {
      return (((*this) (i)) (j, k, l, _m));
   }
#ifdef OPT_LIB
   dvar4_array & operator () (int i)
   {
      return t[i];
   }
   dvar4_array & operator [](int i)
   {
      return t[i];
   }
   dvar3_array & operator ()(int i, int j)
   {
      return ((*this) (i)) (j);
   }
   dvar_matrix & operator ()(int i, int j, int k)
   {
      return (((*this) (i, j)) (k));
   }
   dvar_vector & operator ()(int i, int j, int k, int l)
   {
      return (((*this) (i)) (j, k, l));
   }
   prevariable operator () (int i, int j, int k, int l, int _m)
   {
      return (((*this) (i)) (j, k, l, _m));
   }
   inline const dvar4_array & operator() (int i) const
   {
      return t[i];
   }
   inline const dvar4_array & operator[] (int i) const
   {
      return t[i];
   }
   inline const dvar3_array & operator() (int i, int j) const
   {
      return ((*this) (i)) (j);
   }
   inline const dvar_matrix & operator() (int i, int j, int k) const
   {
      return (((*this) (i)) (j, k));
   }
   inline const dvar_vector & operator() (int i, int j, int k, int l) const
   {
      return (((*this) (i)) (j, k, l));
   }
   inline const prevariable operator() (int i, int j, int k, int l, int _m)
     const
   {
      return (((*this) (i)) (j, k, l, _m));
   }
#else
   const dvar4_array & operator() (int i) const;
   const dvar4_array & operator[] (int i) const;
   const dvar3_array & operator() (int i, int j) const;
   const dvar_matrix & operator() (int i, int j, int k) const;
   const dvar_vector & operator() (int i, int j, int k, int l) const;
   const prevariable operator() (int i, int j, int k, int l, int _m) const;
   dvar4_array & operator ()(int);
   dvar4_array & operator [](int);
   dvar3_array & operator ()(int, int);
   dvar_matrix & operator ()(int, int, int);
   dvar_vector & operator ()(int, int, int, int);
   prevariable operator () (int, int, int, int, int);
#endif
  //access functions
  int indexmin() const
  {
    return shape ? shape->indexmin() : 1;
  }
  int indexmax() const
  {
    return shape ? shape->indexmax() : 0;
  }
  unsigned int size() const
  {
    return static_cast<unsigned int>(indexmax() - indexmin() + 1);
  }
  void initialize();
  void operator/=(const prevariable& d);
  void operator/=(const double& d);

  unsigned int get_ncopies() const { return shape ? shape->ncopies : 0; }
};

dvar5_array operator/(const d5_array & m, const prevariable & d);
dvar5_array operator/(const dvar5_array & m, double d);
dvar5_array operator/(const dvar5_array & m, const prevariable & d);

/**
 * Description not yet available.
 * \param
 */
class d6_array
{
   vector_shape *shape;
   d5_array *t;
public:
  void shallow_copy(const d6_array&);
   d6_array(int hhsl, int hhsu, int hsl, int hsu, int sl, int sh, int nrl,
     int nrh, int ncl, int nch, int l6, int u6);
   void allocate(int hhsl, int hhsu, int hsl, int hsu, int sl, int sh,
     int nrl, int nrh, int ncl, int nch, int l6, int u6);
   void allocate(int hhsl, int hhsu);

   d6_array(const ad_integer & hhsl, const ad_integer & hhsu,
     const index_type & hsl, const index_type & hsu,
     const index_type & sl, const index_type & sh,
     const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch,
     const index_type & l6, const index_type & u6);

   void allocate(const ad_integer & hhsl, const ad_integer & hhsu,
     const index_type & hsl, const index_type & hsu,
     const index_type & sl, const index_type & sh,
     const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch,
     const index_type & l6, const index_type & u6);

   void deallocate(void);
   void allocate(void);
   void allocate(const d6_array &);
   //void allocate(const dvar5_array&);
   int operator!(void) const
   {
      return (shape == NULL);
   }

   d6_array & operator=(const d6_array &);
   d6_array(const d6_array & m2);
   d6_array();
   ~d6_array();
  d5_array& elem(int i);
  d4_array& elem(int i, int j)
  {
    return elem(i)(j);
  }
  d3_array& elem(int i, int j, int k)
  {
    return elem(i)(j, k);
  }
  dmatrix& elem(int i, int j, int k, int l)
  {
    return elem(i)(j, k, l);
  }
  dvector& elem(int i, int j, int k, int l, int _m)
  {
    return elem(i)(j, k, l, _m);
  }
  double &elem(int i, int j, int k, int l, int _m, int _n)
  {
     return elem(i)(j, k, l, _m, _n);
  }
  const d5_array& elem(int i) const;
  const d4_array& elem(int i, int j) const
  {
    return elem(i)(j);
  }
  const d3_array& elem(int i, int j, int k) const
  {
    return elem(i)(j, k);
  }
  const dmatrix& elem(int i, int j, int k, int l) const
  {
    return elem(i)(j, k, l);
  }
  const dvector& elem(int i, int j, int k, int l, int _m) const
  {
    return elem(i)(j, k, l, _m);
  }
  const double& elem(int i, int j, int k, int l, int _m, int _n) const
  {
    return elem(i)(j, k, l, _m, _n);
  }
  d5_array& operator()(int i)
  {
    return elem(i);
  }
  d5_array& operator[](int i)
  {
    return elem(i);
  }
  d4_array& operator()(int i, int j)
  {
    return elem(i)(j);
  }
  d3_array& operator ()(int i, int j, int k)
  {
    return elem(i)(j, k);
  }
  dmatrix& operator ()(int i, int j, int k, int l)
  {
    return elem(i)(j, k, l);
  }
  dvector& operator ()(int i, int j, int k, int l, int _m)
  {
    return elem(i)(j, k, l, _m);
  }
  double& operator()(int i, int j, int k, int l, int _m, int _n)
  {
    return elem(i)(j, k, l, _m, _n);
  }
  inline const d5_array& operator()(int i) const
  {
    return elem(i);
  }
  inline const d5_array& operator[](int i) const
  {
    return elem(i);
  }
  inline const d4_array& operator()(int i, int j) const
  {
    return elem(i)(j);
  }
  inline const d3_array& operator()(int i, int j, int k) const
  {
    return elem(i)(j, k);
  }
  inline const dmatrix& operator()(int i, int j, int k, int l) const
  {
    return elem(i)(j, k, l);
  }
  inline const dvector& operator()(int i, int j, int k, int l, int _m) const
  {
    return elem(i)(j, k, l, _m);
  }
  inline const double& operator()(int i, int j, int k, int l, int _m, int _n)
     const
  {
    return elem(i)(j, k, l, _m, _n);
  }
  //access functions
  int indexmin() const
  {
    return shape ? shape->indexmin() : 1;
  }
  int indexmax() const
  {
    return shape ? shape->indexmax() : 0;
  }
  unsigned int size() const
  {
    return static_cast<unsigned int>(indexmax() - indexmin() + 1);
  }
  void initialize();
  void operator/=(double d);
  unsigned int get_ncopies() const { return shape ? shape->ncopies : 0; }
};
inline d5_array& d6_array::elem(int i)
{
#ifndef OPT_LIB
  if (i < indexmin() || i > indexmax())
  {
    cerr << "Error: Index is out of bounds in"
         << " d5_array& d6_array::elem(int).\n";
    ad_exit(1);
  }
#endif

  return t[i];
}
inline const d5_array& d6_array::elem(int i) const
{
#ifndef OPT_LIB
  if (i < indexmin() || i > indexmax())
  {
    cerr << "Error: Index is out of bounds in"
         << " d5_array& d6_array::elem(int).\n";
    ad_exit(1);
  }
#endif

  return t[i];
}

d6_array operator/(const d6_array & m, double d);

/**
 * Description not yet available.
 * \param
 */
class dvar6_array
{
   vector_shape *shape;
   dvar5_array *t;
 public:
   void shallow_copy(const dvar6_array &);
   dvar6_array(int hhsl, int hhsu);
   void allocate(int hhsl, int hhsu);
   dvar6_array(int hhsl, int hhsu, int hsl, int hsu, int sl, int sh,
     int nrl, int nrh, int ncl, int nch, int l6, int u6);
   void allocate(int hhsl, int hhsu, int hsl, int hsu, int sl, int sh,
     int nrl, int nrh, int ncl, int nch, int l6, int u6);

   dvar6_array(const ad_integer & hhsl, const ad_integer & hhsu,
     const index_type & hsl, const index_type & hsu,
     const index_type & sl, const index_type & sh,
     const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch,
     const index_type & l6, const index_type & u6);

   void allocate(const ad_integer & hhsl, const ad_integer & hhsu,
     const index_type & hsl, const index_type & hsu,
     const index_type & sl, const index_type & sh,
     const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch,
     const index_type & l6, const index_type & u6);

   void deallocate(void);
   void allocate(void);
   void allocate(const d6_array &);
   void allocate(const dvar6_array &);
   int operator!(void) const
   {
      return (shape == NULL);
   }

   dvar6_array & operator=(const d6_array &);
   dvar6_array & operator=(const dvar6_array & m);
   dvar6_array(const d6_array & m2);
   dvar6_array(const dvar6_array & m2);
   dvar6_array();
   ~dvar6_array();
   dvar5_array & elem(int i)
   {
      return t[i];
   }
   dvar4_array & elem(int i, int j)
   {
      return ((*this) (i)) (j);
   }
   dvar3_array & elem(int i, int j, int k)
   {
      return (((*this) (i, j)) (k));
   }
   dvar_matrix & elem(int i, int j, int k, int l)
   {
      return (((*this) (i, j, k)) (l));
   }
   dvar_vector & elem(int i, int j, int k, int l, int _m)
   {
      return (((*this) (i)) (j, k, l, _m));
   }
   prevariable elem(int i, int j, int k, int l, int _m, int _n)
   {
      return (((*this) (i)) (j, k, l, _m, _n));
   }
   const dvar5_array & elem(int i) const
   {
      return t[i];
   }
   const dvar4_array & elem(int i, int j) const
   {
      return ((*this) (i)) (j);
   }
   const dvar3_array & elem(int i, int j, int k) const
   {
      return (((*this) (i, j)) (k));
   }
   const dvar_matrix & elem(int i, int j, int k, int l) const
   {
      return (((*this) (i, j, k)) (l));
   }
   const dvar_vector & elem(int i, int j, int k, int l, int _m) const
   {
      return (((*this) (i)) (j, k, l, _m));
   }
   const prevariable elem(int i, int j, int k, int l, int _m, int _n) const
   {
      return (((*this) (i)) (j, k, l, _m, _n));
   }
#ifdef OPT_LIB
   dvar5_array & operator () (int i)
   {
      return t[i];
   }
   dvar5_array & operator [](int i)
   {
      return t[i];
   }
   dvar4_array & operator ()(int i, int j)
   {
      return ((*this) (i)) (j);
   }
   dvar3_array & operator ()(int i, int j, int k)
   {
      return (((*this) (i, j)) (k));
   }
   dvar_matrix & operator ()(int i, int j, int k, int l)
   {
      return (((*this) (i)) (j, k, l));
   }
   dvar_vector & operator ()(int i, int j, int k, int l, int _m)
   {
      return (((*this) (i)) (j, k, l, _m));
   }
   prevariable operator () (int i, int j, int k, int l, int _m, int _n)
   {
      return (((*this) (i)) (j, k, l, _m, _n));
   }
   inline const dvar5_array & operator() (int i) const
   {
      return t[i];
   }
   inline const dvar5_array & operator[] (int i) const
   {
      return t[i];
   }
   inline const dvar4_array & operator() (int i, int j) const
   {
      return ((*this) (i)) (j);
   }
   inline const dvar3_array & operator() (int i, int j, int k) const
   {
      return (((*this) (i)) (j, k));
   }
   inline const dvar_matrix & operator() (int i, int j, int k, int l) const
   {
      return (((*this) (i)) (j, k, l));
   }
   inline const dvar_vector & operator() (int i, int j, int k, int l, int _m)
     const
   {
      return (((*this) (i)) (j, k, l, _m));
   }
   inline const prevariable operator() (int i, int j, int k, int l, int _m,
     int _n) const
   {
      return (((*this) (i)) (j, k, l, _m, _n));
   }
#else
   const dvar5_array & operator() (int i) const;
   const dvar5_array & operator[] (int i) const;
   const dvar4_array & operator() (int i, int j) const;
   const dvar3_array & operator() (int i, int j, int k) const;
   const dvar_matrix & operator() (int i, int j, int k, int l) const;
   const dvar_vector & operator() (int i, int j, int k, int l, int _m) const;
   const prevariable operator() (int i, int j, int k, int l, int _m, int _n)
     const;
   dvar5_array & operator ()(int);
   dvar5_array & operator [](int);
   dvar4_array & operator ()(int, int);
   dvar3_array & operator ()(int, int, int);
   dvar_matrix & operator ()(int, int, int, int);
   dvar_vector & operator ()(int, int, int, int, int);
   prevariable operator () (int, int, int, int, int, int);
#endif
  //access functions
  int indexmin() const
  {
    return shape ? shape->indexmin() : 1;
  }
  int indexmax() const
  {
    return shape ? shape->indexmax() : 0;
  }
  unsigned int size() const
  {
    return static_cast<unsigned int>(indexmax() - indexmin() + 1);
  }
  void initialize();
  void operator/=(const prevariable& d);
  void operator/=(const double& d);
  unsigned int get_ncopies() const { return shape ? shape->ncopies : 0; }
};

dvar6_array operator/(const d6_array & m, const prevariable & d);
dvar6_array operator/(const dvar6_array & m, double d);
dvar6_array operator/(const dvar6_array & m, const prevariable & d);

/**
 * Description not yet available.
 * \param
 */
class d7_array
{
   vector_shape *shape;
   d6_array *t;
 public:
   void allocate(int l7, int u7);
   d7_array(int l7, int u7, int hhsl, int hhsu, int hsl, int hsu, int sl,
     int sh, int nrl, int nrh, int ncl, int nch, int l6, int u6);
   void allocate(int l7, int u7, int hhsl, int hhsu, int hsl, int hsu,
     int sl, int sh, int nrl, int nrh, int ncl, int nch, int l6, int u6);

   d7_array(const ad_integer & hhsl, const ad_integer & hhsu,
     const index_type & l7, const index_type & u7,
     const index_type & hsl, const index_type & hsu,
     const index_type & sl, const index_type & sh,
     const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch,
     const index_type & l6, const index_type & u6);

   void allocate(const ad_integer & hhsl, const ad_integer & hhsu,
     const index_type & l7, const index_type & u7,
     const index_type & hsl, const index_type & hsu,
     const index_type & sl, const index_type & sh,
     const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch,
     const index_type & l6, const index_type & u6);

   void deallocate(void);
   void allocate(void);
   void allocate(const d7_array &);
   //void allocate(const dvar5_array&);
   int operator!(void) const
   {
      return (shape == NULL);
   }

  d7_array();
  d7_array(const d7_array&);
  ~d7_array();

   d7_array & operator=(const d7_array &);

  d6_array& elem(int i);
  d5_array& elem(int i, int j)
  {
    return elem(i)(j);
  }
  d4_array& elem(int i, int j, int k)
  {
    return elem(i)(j, k);
  }
  d3_array& elem(int i, int j, int k, int l)
  {
    return elem(i)(j, k, l);
  }
  dmatrix& elem(int i, int j, int k, int l, int _m)
  {
    return elem(i)(j, k, l, _m);
  }
  dvector& elem(int i, int j, int k, int l, int _m, int _n)
  {
    return elem(i)(j, k, l, _m, _n);
  }
  double& elem(int i, int j, int k, int l, int _m, int _n, int _p)
  {
    return elem(i)(j, k, l, _m, _n, _p);
  }
  const d6_array& elem(int i) const;
  const d5_array& elem(int i, int j) const
  {
    return elem(i)(j);
  }
  const d4_array& elem(int i, int j, int k) const
  {
    return elem(i)(j, k);
  }
  const d3_array& elem(int i, int j, int k, int l) const
  {
    return elem(i)(j, k, l);
  }
  const dmatrix& elem(int i, int j, int k, int l, int _m) const
  {
    return elem(i)(j, k, l, _m);
  }
  const dvector& elem(int i, int j, int k, int l, int _m, int _n) const
  {
    return elem(i)(j, k, l, _m, _n);
  }
  const double& elem(int i, int j, int k, int l, int _m, int _n, int _p) const
  {
    return elem(i)(j, k, l, _m, _n, _p);
  }
  d6_array& operator()(int i)
  {
    return elem(i);
  }
  d6_array& operator[](int i)
  {
    return elem(i);
  }
  d5_array& operator()(int i, int j)
  {
    return elem(i)(j);
  }
  d4_array& operator()(int i, int j, int k)
  {
    return elem(i, j)(k);
  }
  d3_array& operator ()(int i, int j, int k, int l)
  {
    return elem(i)(j, k, l);
  }
  dmatrix& operator()(int i, int j, int k, int l, int _m)
  {
    return elem(i)(j, k, l, _m);
  }
  dvector & operator ()(int i, int j, int k, int l, int _m, int _n)
  {
    return elem(i)(j, k, l, _m, _n);
  }
  double& operator()(int i, int j, int k, int l, int _m, int _n, int _p)
  {
    return elem(i)(j, k, l, _m, _n, _p);
  }
  inline const d6_array& operator()(int i) const
  {
    return elem(i);
  }
  inline const d6_array& operator[](int i) const
  {
    return elem(i);
  }
  inline const d5_array& operator()(int i, int j) const
  {
    return elem(i)(j);
  }
  inline const d4_array& operator()(int i, int j, int k) const
  {
    return elem(i)(j, k);
  }
  inline const d3_array & operator() (int i, int j, int k, int l) const
  {
    return elem(i)(j, k, l);
  }
  inline const dmatrix& operator()(int i, int j, int k, int l, int _m) const
  {
    return elem(i)(j, k, l, _m);
  }
  inline const dvector& operator()(int i, int j, int k, int l, int _m,
     int _n) const
  {
    return elem(i)(j, k, l, _m, _n);
  }
  inline const double& operator()(int i, int j, int k, int l, int _m, int _n,
     int _p) const
  {
    return elem(i)(j, k, l, _m, _n, _p);
  }

   //access functions
  int indexmin() const
  {
    return shape ? shape->indexmin() : 1;
  }
  int indexmax() const
  {
    return shape ? shape->indexmax() : 0;
  }
  unsigned int size() const
  {
    return static_cast<unsigned int>(indexmax() - indexmin() + 1);
  }
  void initialize();
  void operator/=(double d);
  void shallow_copy(const d7_array&);
  unsigned int get_ncopies() const { return shape ? shape->ncopies : 0; }
};
inline d6_array& d7_array::elem(int i)
{
#ifndef OPT_LIB
  if (i < indexmin() || i > indexmax())
  {
    cerr << "Error index out of bounds in\n"
            "d5_array& d6_array::elem(int)" << endl;
    ad_exit(1);
  }
#endif
  return t[i];
}
inline const d6_array& d7_array::elem(int i) const
{
#ifndef OPT_LIB
  if (i < indexmin() || i > indexmax())
  {
    cerr << "Error index out of bounds in\n"
            "d5_array& d6_array::elem(int)" << endl;
    ad_exit(1);
  }
#endif
  return t[i];
}

d7_array operator/(const d7_array & m, double d);

/**
 * Description not yet available.
 * \param
 */
class dvar7_array
{
   vector_shape *shape;
   dvar6_array *t;
 public:
   dvar7_array(int hhsl, int hhsu, int hsl, int hsu, int sl, int sh,
     int nrl, int nrh, int ncl, int nch, int l6, int u6, int l7, int u7);
   void allocate(int hhsl, int hhsu);
   void allocate(int hhsl, int hhsu, int hsl, int hsu, int sl, int sh,
     int nrl, int nrh, int ncl, int nch, int l6, int u6, int l7, int u7);

   dvar7_array(const ad_integer & hhsl, const ad_integer & hhsu,
     const index_type & l7, const index_type & u7,
     const index_type & hsl, const index_type & hsu,
     const index_type & sl, const index_type & sh,
     const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch,
     const index_type & l6, const index_type & u6);

   void allocate(const ad_integer & hhsl, const ad_integer & hhsu,
     const index_type & l7, const index_type & u7,
     const index_type & hsl, const index_type & hsu,
     const index_type & sl, const index_type & sh,
     const index_type & nrl, const index_type & nrh,
     const index_type & ncl, const index_type & nch,
     const index_type & l6, const index_type & u6);

   void deallocate(void);
   void allocate(void);
   void allocate(const d7_array &);
   void allocate(const dvar7_array &);
   int operator!(void) const
   {
      return (shape == NULL);
   }

   dvar7_array & operator=(const d7_array &);
   dvar7_array & operator=(const dvar7_array & m);
   dvar7_array(d7_array & m2);
   dvar7_array(dvar7_array & m2);
   dvar7_array();
   ~dvar7_array();
   void shallow_copy(const dvar7_array&);
   dvar6_array & elem(int i)
   {
      return t[i];
   }
   dvar5_array & elem(int i, int j)
   {
      return ((*this) (i)) (j);
   }
   dvar4_array & elem(int i, int j, int k)
   {
      return (((*this) (i, j)) (k));
   }
   dvar3_array & elem(int i, int j, int k, int l)
   {
      return (((*this) (i, j, k)) (l));
   }
   dvar_matrix & elem(int i, int j, int k, int l, int _m)
   {
      return (((*this) (i)) (j, k, l, _m));
   }
   dvar_vector & elem(int i, int j, int k, int l, int _m, int _n)
   {
      return (((*this) (i)) (j, k, l, _m, _n));
   }
   prevariable elem(int i, int j, int k, int l, int _m, int _n, int _p)
   {
      return (((*this) (i)) (j, k, l, _m, _n, _p));
   }
   const dvar6_array & elem(int i) const
   {
      return t[i];
   }
   const dvar5_array & elem(int i, int j) const
   {
      return ((*this) (i)) (j);
   }
   const dvar4_array & elem(int i, int j, int k) const
   {
      return (((*this) (i, j)) (k));
   }
   const dvar3_array & elem(int i, int j, int k, int l) const
   {
      return (((*this) (i, j, k)) (l));
   }
   const dvar_matrix & elem(int i, int j, int k, int l, int _m) const
   {
      return (((*this) (i)) (j, k, l, _m));
   }
   const dvar_vector & elem(int i, int j, int k, int l, int _m, int _n) const
   {
      return (((*this) (i)) (j, k, l, _m, _n));
   }
   const prevariable elem(int i, int j, int k, int l, int _m, int _n, int _p)
     const
   {
      return (((*this) (i)) (j, k, l, _m, _n, _p));
   }
#ifdef OPT_LIB
   dvar6_array & operator () (int i)
   {
      return t[i];
   }
   dvar6_array & operator [](int i)
   {
      return t[i];
   }
   dvar5_array & operator ()(int i, int j)
   {
      return ((*this) (i)) (j);
   }
   dvar4_array & operator ()(int i, int j, int k)
   {
      return (((*this) (i, j)) (k));
   }
   dvar3_array & operator ()(int i, int j, int k, int l)
   {
      return (((*this) (i)) (j, k, l));
   }
   dvar_matrix & operator ()(int i, int j, int k, int l, int _m)
   {
      return (((*this) (i)) (j, k, l, _m));
   }
   dvar_vector & operator ()(int i, int j, int k, int l, int _m, int _n)
   {
      return (((*this) (i)) (j, k, l, _m, _n));
   }
   prevariable operator () (int i, int j, int k, int l, int _m, int _n, int _p)
   {
      return (((*this) (i)) (j, k, l, _m, _n, _p));
   }
   inline const dvar6_array & operator() (int i) const
   {
      return t[i];
   }
   inline const dvar6_array & operator[] (int i) const
   {
      return t[i];
   }
   inline const dvar5_array & operator() (int i, int j) const
   {
      return ((*this) (i)) (j);
   }
   inline const dvar4_array & operator() (int i, int j, int k) const
   {
      return (((*this) (i)) (j, k));
   }
   inline const dvar3_array & operator() (int i, int j, int k, int l) const
   {
      return (((*this) (i)) (j, k, l));
   }
   inline const dvar_matrix & operator() (int i, int j, int k, int l, int _m)
     const
   {
      return (((*this) (i)) (j, k, l, _m));
   }
   inline const dvar_vector & operator() (int i, int j, int k, int l, int _m,
     int _n) const
   {
      return (((*this) (i)) (j, k, l, _m, _n));
   }
   inline const prevariable operator()(int i, int j, int k, int l, int _m,
     int _n, int _p) const
   {
      return (((*this) (i)) (j, k, l, _m, _n, _p));
   }
#else
   const dvar6_array & operator() (int i) const;
   const dvar6_array & operator[] (int i) const;
   const dvar5_array & operator() (int i, int j) const;
   const dvar4_array & operator() (int i, int j, int k) const;
   const dvar3_array & operator() (int i, int j, int k, int l) const;
   const dvar_matrix & operator() (int i, int j, int k, int l, int _m) const;
   const dvar_vector & operator() (int i, int j, int k, int l, int _m, int _n)
     const;
   const prevariable operator() (int i, int j, int k, int l, int _m, int _n,
     int _p) const;
   dvar6_array & operator ()(int);
   dvar6_array & operator [](int);
   dvar5_array & operator ()(int, int);
   dvar4_array & operator ()(int, int, int);
   dvar3_array & operator ()(int, int, int, int);
   dvar_matrix & operator ()(int, int, int, int, int);
   dvar_vector & operator ()(int, int, int, int, int, int);
   prevariable operator () (int, int, int, int, int, int, int);
#endif
  //access functions
  int indexmin() const
  {
    return shape ? shape->indexmin() : 1;
  }
  int indexmax() const
  {
    return shape ? shape->indexmax() : 0;
  }
  unsigned int size() const
  {
    return static_cast<unsigned int>(indexmax() - indexmin() + 1);
  }
  void initialize();
  void operator/=(const prevariable& d);
  void operator/=(const double& d);
  unsigned int get_ncopies() const { return shape ? shape->ncopies : 0; }
};

dvar7_array operator/(const d7_array & m, const prevariable & d);
dvar7_array operator/(const dvar7_array & m, double d);
dvar7_array operator/(const dvar7_array & m, const prevariable & d);

class lmatrix;

/**
 * Description not yet available.
 * \param
 */
class lmatrix_position
{
 public:
   int row_min;
   int row_max;
   ivector lb;
   ivector ub;
   ptr_vector ptr;
   lmatrix_position(const lmatrix &);
   lmatrix_position(int min, int max);
   lmatrix_position(const lmatrix_position &);
   lvector_position operator () (int i);
};

lmatrix_position restore_lmatrix_position(void);
lmatrix restore_lmatrix_value(const lmatrix_position &);

/**
 * Description not yet available.
 * \param
 */
class lmatrix
{
 protected:
   lvector * m;
   mat_shape *shape;
   friend char *fform(const char *, const dmatrix &);

 public:
   int operator!(void) const
   {
      return (shape == NULL);
   }

   lmatrix(int, int);
   // makes a matrix [0..nr][0..nc]

   lmatrix(int, int, int, int);
   // makes a matrix [nrl..nrh][ncl..nch]
   lmatrix(int, int, int, const ivector &);
   lmatrix(int, int, const ivector &, const ivector &);
   lmatrix(const ad_integer & nrl, const ad_integer & nrh,
     const index_type & ncl, const index_type & nch);

   lmatrix & operator=(const lmatrix & t);
   lmatrix & operator=(const imatrix & t);
   lmatrix(const lmatrix &);
   // copy initializer
   lmatrix(const lmatrix_position &);
   lmatrix(void);

   ~lmatrix();

   void save_lmatrix_value(void);
   void save_lmatrix_position(void);
   lmatrix restore_lmatrix_value(const lmatrix_position & mpos);
   lmatrix_position restore_lmatrix_position(void);

   void allocate(const lmatrix & dm);
   void allocate(int nrl, int nrh, int ncl, int nch);
   void allocate(int nrl, int nrh, int ncl, const ivector & nch);
   void allocate(int nrl, int nrh, const ivector & ncl,
     const ivector & nch);
   void allocate(const ad_integer & nrl, const ad_integer & nrh,
     const index_type & ncl, const index_type & nch);
   void deallocate();

#ifdef OPT_LIB
   inline lvector & operator() (int i)
   {
      return m[i];
   }
   inline AD_LONG_INT & operator() (int i, int j)
   {
      return (*((*(m + i)).v + j));
   }
   inline lvector & operator[] (int i)
   {
      return m[i];
   }
#else
   lvector & operator [] (int);
   lvector & operator () (int);
   AD_LONG_INT & operator () (int, int);
#endif

#ifdef OPT_LIB
   inline const lvector & operator() (int i) const
   {
      return m[i];
   }
   inline const AD_LONG_INT & operator() (int i, int j) const
   {
      return (*((*(m + i)).v + j));
   }
   inline const lvector & operator[] (int i) const
   {
      return m[i];
   }
#else
   const lvector & operator[] (int) const;
   const lvector & operator() (int) const;
   const AD_LONG_INT & operator() (int, int) const;
#endif

   int colmin(void) const
   {
      return (shape->col_min);
   }
   int colmax(void) const
   {
      return (shape->col_max);
   }
   int rowmin(void) const
   {
      return (shape->row_min);
   }
   int rowmax(void) const
   {
      return (shape->row_max);
   }
   // returns the number of rows
   unsigned int rowsize() const
   {
      return shape->nrows;
   }
   // returns the number of columns
   unsigned int colsize() const
   {
      return shape->ncols;
   }

   void write_on(const ostream &) const;
   void write_on(const uostream &) const;
   void read_from(const istream &);
   void read_from(const uistream &);
   void initialize(void);
   friend class i3_array;
};

// void dmatrix::allocate(int nrl,int nrh,const index_type& ncl,
// const index_type& nch)
class index_guts;
class index_type;
class number_index;
class vector_index;
class matrix_index;
class i3_index;

/**
 * Description not yet available.
 * \param
 */
class adkludge{};

/**
 * Description not yet available.
 * \param
 */
class pre_index_type
{
   const index_type *a;
   int i;
 public:
   pre_index_type(const index_type * _a, int _i):a(_a), i(_i)
   {
   }
   friend class index_type;
};

class data_int;

/**
Stores integer.
*/
class ad_integer
{
protected:
  int d;

public:
  operator int() const
  {
    return d;
  }
  ad_integer(const int &_d, const adkludge&): d(_d)
  {
  }
  ad_integer(const data_int& di);
  ad_integer(const int _d): d(_d)
  {
  }
  ad_integer(const index_type& it);

  ad_integer make_ad_integer(int _d)
  {
    adkludge adk;

    return ad_integer(_d, adk);
  }
};

/// Abstract base class for different index types.
class index_guts
{
protected:
  int* ncopies;

public:
  index_guts();
  index_guts(const index_guts& ig);
  virtual ~index_guts();

  virtual index_guts* operator[](int) = 0;
  virtual int indexmin() const = 0;
  virtual int indexmax() const = 0;

  virtual int isinteger() const
  {
    return 1;
  }
  virtual int dimension() const
  {
    return -1;
  }
  virtual operator int()
  {
    cerr << "Error in index_type"
    " -- object not dereferenced enough" << endl;
    ad_exit(1);
    return 1;
  }

  friend class ad_integer;
  friend class index_type;
};
/// Keeps track of total number of copies.
class smart_counter
{
  int* ncopies;

public:
  smart_counter();
  smart_counter(const smart_counter& sc);
  ~smart_counter();

  int* get_ncopies();
};
/**
Uses polymorphism to get index information from various data types
to be used in constructing and allocating admb matrices and vectors.
*/
class index_type: public smart_counter
{
  index_guts* p;

public:
  index_type(const int x);
  index_type(const ivector& x);
  index_type(const imatrix& x);
  index_type(const i3_array& x);
  index_type(const i4_array& x);
  index_type(const pre_index_type& pit);
  index_type(const index_type& pit);
  //index_type (i4_array& x) { p = new i4_index(x);}
  ~index_type();

  index_type operator[](int i);
  index_type operator()(int i);
  index_type operator[](int i) const;
  index_type operator()(int i) const;

  int integer() const;
  int isinteger() const
  {
    return p->isinteger();
  }
  int dimension() const
  {
    return p->dimension();
  }
  int indexmin() const
  {
    return p->indexmin();
  }
  int indexmax() const
  {
    return p->indexmax();
  }

  friend class ad_integer;
};
/// Derived class of index types for ad_integer.
class number_index: public ad_integer, public index_guts
{
private:
  virtual int isinteger() const
  {
    return 0;
  }
  virtual int dimension() const
  {
    return 0;
  }
  virtual index_guts* operator[](int i);
  virtual int indexmin() const
  {
    return 1;
  }
  virtual int indexmax() const
  {
    return 1;
  }
public:
  number_index(int i): ad_integer(i)
  {
  }
  /// Destructor
  virtual ~number_index()
  {
  }
  /// only overload this for number_index ... will fail for other classes
  virtual operator int()
  {
    return d;
  }

  friend class index_type;
};
/// Derived class of index types for ivector.
class vector_index: public ivector, public index_guts
{
  virtual index_guts* operator[](int i)
  {
    return new number_index(ivector::operator[](i));
  }
public:
  //vector_index(const ivector& v) : ivector(v){}

  vector_index(const ivector& v);
  virtual ~vector_index();

  virtual int dimension() const
  {
    return 1;
  }
  virtual int indexmin() const
  {
    return ivector::indexmin();
  }
  virtual int indexmax() const
  {
    return ivector::indexmax();
  }

  friend class index_type;
};
/// Derived class of index types for imatrix.
class matrix_index: public imatrix, public index_guts
{
private:
  virtual index_guts* operator[](int i);
  //{
  //  return new vector_index(imatrix::operator [](i));
  //}
public:
  matrix_index(const imatrix& v): imatrix(v)
  {
  }
  virtual ~matrix_index();

  virtual int dimension() const
  {
    return 2;
  }
  virtual int indexmin() const
  {
    return imatrix::rowmin();
  }
  virtual int indexmax() const
  {
    return imatrix::rowmax();
  }

  friend class index_type;
};
/// Derived class of index types for i3_array.
class i3_index: public i3_array, public index_guts
{
  virtual index_guts* operator[](int i)
  {
    return new matrix_index(i3_array::operator[](i));
  }
public:
  i3_index(i3_array& v): i3_array(v)
  {
  }

  virtual int dimension() const
  {
    return 3;
  }
  virtual int indexmin() const
  {
    return i3_array::slicemin();
  }
  virtual int indexmax() const
  {
    return i3_array::slicemax();
  }

  friend class index_type;
};
/// Derived class of index types for i4_array.
class i4_index: public i4_array, public index_guts
{
  virtual index_guts* operator[](int i)
  {
    return new i3_index(i4_array::operator[](i));
  }
public:
  i4_index(i4_array& v): i4_array(v)
  {
  }

  virtual int dimension() const
  {
    return 4;
  }
  virtual int indexmin() const
  {
    return i4_array::slicemin();
  }
  virtual int indexmax() const
  {
    return i4_array::slicemax();
  }

  friend class index_type;
};

void ad_begin_funnel(void);

/**
 * Description not yet available.
 * \param
 */
class vector_range_exception
{
   vector_range_exception(int i, int imin, int imax);
   friend class dvector;
   friend class dvar_vector;
};

/**
 * Description not yet available.
 * \param
 */
class spdll_exception
{
 public:
   int e;
   spdll_exception(int _e = 0)
   {
      e = _e;
   }
};

/**
 * Description not yet available.
 * \param
 */
class random_number_generator /// Random number generator
{
  unsigned long* mt; ///< the array for the state vector
  int mti; ///< mti==N+1 means mt[N] is not initialized
public:
  random_number_generator(const int seed);
  ~random_number_generator();

  double better_rand();
  void reinitialize(const int seed);
};

double randpoisson(double lambda, const random_number_generator & rng);

// note that od is the overdispersion od >1
double randnegbinomial(double mu, double tau,
  const random_number_generator & rng);
double randn(const random_number_generator & rng);
double randu(const random_number_generator & rng);
double gasdev(const random_number_generator & _rng);
double expdev(const random_number_generator & _rng);
double sgamma(double a, const random_number_generator & _rng);
banded_symmetric_dmatrix value(const banded_symmetric_dvar_matrix & v);
banded_symmetric_dmatrix restore_banded_symmetric_dvar_matrix_value(
  const dvar_matrix_position& mpos);

/**
 * Description not yet available.
 * \param
 */
class banded_symmetric_dmatrix
{
   int bw;
   dmatrix d;
 public:
   const dmatrix & get_dmatrix(void) const
   {
      return d;
   }
   void initialize(void);
   int bandwidth(void) const
   {
      return bw;
   }
   int indexmin(void) const
   {
      return d(0).indexmin();
   }
   int indexmax(void) const
   {
      return d(0).indexmax();
   }
   int rowmin(void) const
   {
      return d.rowmin();
   }
   int rowmax(void) const
   {
      return d.rowmax();
   }

   banded_symmetric_dmatrix(void):bw(-1), d()
   {
   }
   banded_symmetric_dmatrix(const banded_symmetric_dmatrix &, int, int);

   banded_symmetric_dmatrix sub(int l, int u);

   void shift(int);

   banded_symmetric_dmatrix & operator =(const banded_symmetric_dmatrix &);
   banded_symmetric_dmatrix(int _min, int _max, int _bw);

   banded_symmetric_dmatrix(const dvar_matrix_position & mpos);
   void save_dmatrix_value(void) const;
   void save_dmatrix_position(void) const;
   void save_dmatrix_derivatives(const dvar_matrix_position &) const;

#if defined(OPT_LIB)
   inline double &operator () (register int i, register int j)
   {
      return (*((d.m[i - j]).v + i));
   }
   inline dvector operator () (register int i)
   {
      return (d.m[i]);
   }
   inline const double &operator() (register int i, register int j) const
   {
      return (*((d.m[i - j]).v + i));
   }
   inline const dvector operator() (register int i) const
   {
      return (d.m[i]);
   }
#else
   double &operator () (int i, int j);
   dvector operator () (int i);
   const double &operator() (int i, int j) const;
   const dvector operator() (int i) const;
#endif
   friend banded_symmetric_dmatrix value(
     const banded_symmetric_dvar_matrix& v);
   friend banded_symmetric_dmatrix
      restore_banded_symmetric_dvar_matrix_value(
        const dvar_matrix_position& mpos);
   friend double norm2(const banded_symmetric_dmatrix & B);
   friend double sumsq(const banded_symmetric_dmatrix & B);
};

/**
 * Description not yet available.
 * \param
 */
class banded_symmetric_dvar_matrix
{
   int bw;
   dvar_matrix d;
 public:
   void initialize(void);
   int bandwidth(void) const
   {
      return bw;
   }
   int indexmin(void) const
   {
      return d(0).indexmin();
   }
   int indexmax(void) const
   {
      return d(0).indexmax();
   }
   int rowmin(void) const
   {
      return d.rowmin();
   }
   int rowmax(void) const
   {
      return d.rowmax();
   }

   void save_dvar_matrix_value(void) const;
   void save_dvar_matrix_position(void) const;
   banded_symmetric_dvar_matrix(int _min, int _max, int _bw);
   banded_symmetric_dvar_matrix(const banded_symmetric_dvar_matrix &);

#if defined(OPT_LIB)
   prevariable operator () (int i, int j)
   {
      return ((d.m[i - j]).va + i);
   }
   dvar_vector operator () (int i)
   {
      return (d.m[i]);
   }
#else
   prevariable operator () (int i, int j);
   dvar_vector operator () (int i);
#endif
   friend banded_symmetric_dmatrix value(const banded_symmetric_dvar_matrix& v);
   friend dvariable norm(const banded_symmetric_dvar_matrix & B);
   friend dvariable norm2(const banded_symmetric_dvar_matrix & B);
   friend dvariable sumsq(const banded_symmetric_dvar_matrix & B);
};

/**
 * Description not yet available.
 * \param
 */
class banded_lower_triangular_dmatrix
{
   int bw;
   dmatrix d;
 public:
   void initialize(void);
   void shift(int);
   int bandwidth(void) const
   {
      return bw;
   }
   int indexmin(void) const
   {
      return d(0).indexmin();
   }
   int indexmax(void) const
   {
      return d(0).indexmax();
   }
   int rowmin(void) const
   {
      return d.rowmin();
   }
   int rowmax(void) const
   {
      return d.rowmax();
   }

   void save_dmatrix_value(void) const;
   void save_dmatrix_position(void) const;
   banded_lower_triangular_dmatrix(const dvar_matrix_position & mpos);
   banded_lower_triangular_dmatrix(int _min, int _max, int _bw);
   banded_lower_triangular_dmatrix(const banded_lower_triangular_dmatrix &);
   banded_lower_triangular_dmatrix & operator=(
     const banded_lower_triangular_dmatrix &);
   void save_dmatrix_derivatives(const dvar_matrix_position &) const;
   friend banded_lower_triangular_dmatrix
      restore_banded_lower_triangular_dvar_matrix_value(
        const dvar_matrix_position& mpos);
#if defined(OPT_LIB)
   inline double &operator () (register int i, register int j)
   {
      return (*((d.m[i - j]).v + i));
   }
   inline dvector operator () (register int i)
   {
      return (d.m[i]);
   }
   inline const double &operator() (register int i, register int j) const
   {
      return (*((d.m[i - j]).v + i));
   }
   inline const dvector operator() (register int i) const
   {
      return (d.m[i]);
   }
#else
   double &operator () (int i, int j);
   dvector operator () (int i);
   const double &operator() (int i, int j) const;
   const dvector operator() (int i) const;
#endif
   friend banded_lower_triangular_dmatrix value
      (const banded_lower_triangular_dvar_matrix & v);
};

/**
 * Description not yet available.
 * \param
 */
class banded_lower_triangular_dvar_matrix
{
   int bw;
   dvar_matrix d;
 public:
   int bandwidth(void) const
   {
      return bw;
   }
   int indexmin(void) const
   {
      return d(0).indexmin();
   }
   int indexmax(void) const
   {
      return d(0).indexmax();
   }
   int rowmin(void) const
   {
      return d.rowmin();
   }
   int rowmax(void) const
   {
      return d.rowmax();
   }
   void initialize(void);
   void save_dvar_matrix_value(void) const;
   void save_dvar_matrix_position(void) const;

   banded_lower_triangular_dvar_matrix(int _min, int _max, int _bw);
   banded_lower_triangular_dvar_matrix
      (const banded_lower_triangular_dvar_matrix &);

#if defined(OPT_LIB)
   inline prevariable operator () (register int i, register int j)
   {
      return ((d.m[i - j]).va + i);
   }
   inline dvar_vector operator () (register int i)
   {
      return (d.m[i]);
   }
   inline const prevariable operator() (register int i, register int j) const
   {
      return ((d.m[i - j]).va + i);
   }
   inline const dvar_vector operator() (register int i) const
   {
      return (d.m[i]);
   }
#else
   prevariable operator () (int i, int j);
   dvar_vector operator () (int i);
   const prevariable operator() (int i, int j) const;
   const dvar_vector operator() (int i) const;
#endif
   inline double &elem_value(register int i, register int j)
   {
      return *(double *) ((d.m[i - j]).va + i);
   }
   inline const double &elem_value(register int i, register int j) const
   {
      return *(double *) ((d.m[i - j]).va + i);
   }
   friend banded_lower_triangular_dmatrix value
      (const banded_lower_triangular_dvar_matrix & v);
};

ostream & operator<<(const ostream & ofs,
  const banded_symmetric_dmatrix & S);
ostream & operator<<(const ostream & ofs,
  const banded_symmetric_dvar_matrix & S);
ostream & operator<<(const ostream & ofs,
  const banded_lower_triangular_dmatrix & S);
ostream & operator<<(const ostream & ofs,
  const banded_lower_triangular_dvar_matrix & S);

// check to see how this is transposed before using
dmatrix solve(const banded_symmetric_dmatrix & m, const dmatrix & M);
dmatrix solve(const dmatrix & m, const dmatrix & M);
dvector solve(const banded_symmetric_dmatrix & m, const dvector & v);

banded_lower_triangular_dmatrix choleski_decomp(
  const banded_symmetric_dmatrix& S,
  int& ierr
);

banded_lower_triangular_dvar_matrix choleski_decomp_positive
   (const banded_symmetric_dvar_matrix & S, double eps, dvariable & fpen);

dvariable ln_det_choleski(
  const banded_symmetric_dvar_matrix& S,
  int &ierr
);
double ln_det_choleski(
  const banded_symmetric_dmatrix& S,
  int& ierr
);
banded_lower_triangular_dvar_matrix choleski_decomp(
  const banded_symmetric_dvar_matrix& S,
  int &ierr
);

banded_lower_triangular_dmatrix
   restore_banded_lower_triangular_dvar_matrix_derivatives
   (const dvar_matrix_position & pos);

banded_lower_triangular_dmatrix
   restore_banded_lower_triangular_dvar_matrix_value
   (const dvar_matrix_position & pos);

banded_symmetric_dmatrix restore_bounded_symmetric_dvar_matrix_derivatives
   (const dvar_matrix_position & pos);

unsigned long max(unsigned long u, unsigned long v);
unsigned long min(unsigned long u, unsigned long v);
double max(const double u, const double v);
double min(const double u, const double v);
int max(int i, int j, int k);
int max(int i, int j);

dvar_vector solve(const banded_lower_triangular_dvar_matrix & m,
  const dvar_vector & v);

void check_choleski_decomp(const banded_symmetric_dvar_matrix & MM,
  int &ierr);

dvector solve(const banded_lower_triangular_dmatrix & m,
  const dvector & v);
dvector solve_trans(const banded_lower_triangular_dmatrix & m,
  const dvector & v);
int admax(int i, int j);

dmatrix diagonal_matrix(const dvector & v);
dvar_matrix diagonal_matrix(const dvar_vector & v);
dvector diagonal(const dmatrix &);
ivector diagonal(const imatrix &);
dvar_vector diagonal(const dvar_matrix &);

double gammln(double xx);
//dvariable gammln(const dvariable& xx);
dvariable gammln(const prevariable& xx);
ivector histogram(double min, double max, int nbin, const dvector& input);

double cumd_cauchy(const double &x);
double density_cauchy(const double &x);
double log_density_cauchy(const double &x);
double inv_cumd_cauchy(const double &x);
dvariable inv_cumd_cauchy(const prevariable & x);
dvariable cumd_cauchy(const prevariable & x);
dvariable kludge_cumd_cauchy(const prevariable & x);

double log_negbinomial_density(double x, double mu, double tau);

dvariable log_negbinomial_density(double x, const prevariable & mu,
  const prevariable & tau);

dvariable log_density_poisson(double x, const prevariable & mu);
double log_density_poisson(double x, double mu);

//double negbinomial_density(double x,double r, double mu);

/**
 * Description not yet available.
 * \param
 */
class pre_column_print
{
   dvector *ptr;
 public:
   pre_column_print(const dvector & v)
   {
      ptr = (dvector *) (&v);
   }
   friend ostream & operator<<(const ostream &, const pre_column_print &);
};

/**
 * Description not yet available.
 * \param
 */
class pre_zero_print
{
   dvector *ptr;
 public:
   pre_zero_print(const dvector & v)
   {
      ptr = (dvector *) (&v);
   }
   friend ostream & operator<<(const ostream &, const pre_zero_print &);
};

ostream & operator<<(const ostream &, const pre_column_print &);
ostream & operator<<(const ostream &, const pre_zero_print &);

pre_column_print column_print(const dvector & v);
pre_zero_print zero_print(const dvector & v);

dvector VEC(const dmatrix &);
dmatrix MAT(const dvector &, int i, int j);

dvar_vector VEC(const dvar_matrix &);
dvar_matrix MAT(const dvar_vector &, int i, int j);

dmatrix operator-(const dmatrix & m);
dvar_matrix operator-(const dvar_matrix & m);

ivector sgn(const dvector &);
ivector sgn(const dvar_vector &);

int allocated(const ivector & v);
int allocated(const lvector & v);
int allocated(const dvector & v);
int allocated(const dvar_vector & v);

int allocated(const imatrix & v);
int allocated(const dmatrix & v);
int allocated(const dvar_matrix & v);

int allocated(const i3_array & v);
int allocated(const d3_array & v);
int allocated(const dvar3_array & v);

int allocated(const i4_array & v);
int allocated(const d4_array & v);
int allocated(const dvar4_array & v);

int allocated(const i5_array& iarr5);
int allocated(const d5_array & v);
int allocated(const dvar5_array & v);

int allocated(const d6_array & v);
int allocated(const dvar6_array & v);

int allocated(const d7_array & v);
int allocated(const dvar7_array & v);

dvar_matrix positive_definite_matrix(const dvar_matrix & MM, double eps,
  dvariable & fpen);

dvar_matrix empirical_covariance(const dvar_matrix & v1);
dvar_matrix empirical_covariance(const dvar_matrix & v1,
  const imatrix & missflags);

void gauss_hermite(const dvector & _x, const dvector & _w);
void normalized_gauss_hermite(const dvector & _x, const dvector & _w);
void gauss_legendre(double x1, double x2, const dvector & _x,
  const dvector & _w);
void gauss_legendre(const dvector & _x, const dvector & _w);

//dvariable beta(const prevariable&,const prevariable&);

double betacf(const double a, const double b, double x, int maxit = 100);
dvariable betacf(const dvariable& a, const dvariable& b, const dvariable& x, int maxit = 100);

dvariable betai(const dvariable a, const dvariable b, const dvariable x, int maxit = 100);
double betai(const double a,const double b,const double x, int maxit=100);
dvariable pbeta( const dvariable x, const dvariable a, const dvariable b, int maxit = 100);
double pbeta(const double x, const double a,const double b, int maxit=100);

dvariable besselI(dvariable x, int nu);
dvariable besselK(dvariable x, int nu);
dvariable besselJ(dvariable x, int nu);
dvariable besselY(dvariable x, int nu);

double besselI(double x, int nu);
double besselK(double x, int nu);
double besselJ(double x, int nu);
double besselY(double x, int nu);

/*
double betai(double _aa, double _bb, double _xx);
dvariable betai(const dvariable & _a, const dvariable & _b,
  const dvariable & _x);
double incbet(const double a, const double b, const double x);
dvariable incbet(const dvariable & _a, const dvariable & _b,
  const dvariable & _x);

df1_three_variable incbet(const df1_three_variable & _aa,
  const df1_three_variable & _bb, const df1_three_variable & _xx);
*/

dvar_matrix tensor_prod(const dvar_matrix & a, const dvar_matrix & b);

extern "C" void exit_handler(int k);

class double_index_guts;
class double_index_type;
class double_number_index;
class double_vector_index;
class double_matrix_index;
class double_i3_index;

/**
 * Description not yet available.
 * \param
 */
class pre_double_index_type
{
   const double_index_type *a;
   int i;
 public:
   pre_double_index_type(const double_index_type * _a, int _i):a(_a), i(_i)
   {
   }
   friend class double_index_type;
};

/**
Stores double value.
*/
class ad_double
{
protected:
  double d;
public:
  operator double () const
  {
    return d;
  }
  ad_double(const double& _d, const adkludge&):d(_d)
  {
  }
  ad_double(double _d):d(_d)
  {
  }
  ad_double(const double_index_type& it);
  ad_double make_ad_double(double _d)
  {
    adkludge adk;
    //??Should parameter be d or _d?
    return ad_double(d, adk);
  }
  ad_double& operator=(const ad_double&);
};

/**
 * Description not yet available.
 * \param
 */
class double_index_guts
{
   friend class ad_double;
 protected:
   int *ncopies;
 public:
   virtual double_index_guts * operator [] (int) = 0;
   virtual int isdouble(void) const
   {
      return 1;
   }
   virtual operator  double ()
   {
      cerr << "Error in double_index_type"
      " -- object not dereferenced enough" << endl;
      ad_exit(1);
      return 1;
   }
   virtual int indexmin(void) = 0;
   virtual int indexmax(void) = 0;
   double_index_guts();
   double_index_guts(const double_index_guts & ig);
   virtual ~ double_index_guts();
   friend class double_index_type;
};

/**
 * Description not yet available.
 * \param
 */
class double_index_type
{
   double_index_guts *p;
 public:
   double ddouble(void) const;
   int isdouble(void) const
   {
      return p->isdouble();
   }
   double_index_type(double x);
   //index_type(const data_int& x);
   double_index_type(const dvector & x);
   double_index_type(const dmatrix & x);
   double_index_type(const d3_array & x);
   double_index_type(const pre_double_index_type & pit);
   double_index_type(const double_index_type & pit);
   //index_type (i4_array& x) { p = new i4_index(x);}
   ~double_index_type();
   double_index_type operator [] (int i);
   double_index_type operator () (int i);
   double_index_type operator [] (int i) const;
   double_index_type operator () (int i) const;
   int indexmin(void) const
   {
      return p->indexmin();
   }
   int indexmax(void) const
   {
      return p->indexmax();
   }
   friend class ad_integer;
};

/**
 * Description not yet available.
 * \param
 */
class double_index:public ad_double, public double_index_guts
{
 private:
   virtual int isdouble_(void) const
   {
      return 0;
   }
   virtual double_index_guts *operator [] (int i);
   virtual int indexmin(void)
   {
      return 1;
   }
   virtual int indexmax(void)
   {
      return 1;
   }
 public:
   virtual ~ double_index()
   {
   }
 double_index(double i):ad_double(i)
   {
   }
   // only overload this for number_index ... will fail for other classes
   virtual operator  double ()
   {
      return d;
   }
   friend class double_index_type;
};

/**
 * Description not yet available.
 * \param
 */
class dvector_index:public dvector, public double_index_guts
{
   virtual double_index_guts *operator [] (int i)
   {
      return new double_index(dvector::operator [](i));
   }
 public:
   //vector_index(const ivector& v) : ivector(v){}
   dvector_index(const dvector & v);
   virtual ~ dvector_index();
   virtual int indexmin(void)
   {
      return dvector::indexmin();
   }
   virtual int indexmax(void)
   {
      return dvector::indexmax();
   }
   friend class double_index_type;
};

/**
 * Description not yet available.
 * \param
 */
class dmatrix_index:public dmatrix, public double_index_guts
{
 private:
   virtual double_index_guts * operator [] (int i);
   //{
   //return new dvector_index(dmatrix::operator [](i));
   //}
 public:
   virtual ~ dmatrix_index();
   dmatrix_index(const dmatrix & v):dmatrix(v)
   {
   }
   virtual int indexmin(void)
   {
      return dmatrix::rowmin();
   }
   virtual int indexmax(void)
   {
      return dmatrix::rowmax();
   }
   friend class double_index_type;
};

/**
 * Description not yet available.
 * \param
 */
class d3_index:public d3_array, public double_index_guts
{
   virtual double_index_guts *operator [] (int i)
   {
      return new dmatrix_index(d3_array::operator [](i));
   }
 public:
   d3_index(d3_array & v):d3_array(v)
   {
   }
   virtual int indexmin(void)
   {
      return d3_array::slicemin();
   }
   virtual int indexmax(void)
   {
      return d3_array::slicemax();
   }
   friend class index_type;
};

dvariable mf_upper_bound(const prevariable & x, double M, prevariable & fpen);
double mf_upper_bound(const double &x, double M, prevariable & fpen);

int operator==(double v0, const prevariable & v1);
int operator<=(double v0, const prevariable & v1);
int operator>=(double v0, const prevariable & v1);
int operator>(double v0, const prevariable & v1);
int operator<(double v0, const prevariable & v1);
int operator!=(double v0, const prevariable & v1);

dvariable cumd_bivariate_normal(const prevariable & xu, const prevariable & yu,
  const prevariable & rho, int nbox);

dvariable cumbvn(const dvariable& x, const dvariable& y, const dvariable& rho);

dvariable cumbvn(const dvariable & xl, const dvariable & yl,
  const dvariable & xu, const dvariable & yu, const dvariable & rho);

double ghk(const dvector & lower, const dvector & upper,
  const dmatrix & Sigma, const dmatrix & eps);

double ghk_choleski(const dvector & lower, const dvector & upper,
  const dmatrix & ch, const dmatrix & eps);

dvariable ghk_choleski_m(const dvar_vector & upper,
  const dvar_matrix & ch, const dmatrix & eps);

double ghk(const dvector & lower, const dvector & upper,
  const dmatrix & Sigma, const dmatrix & eps, int i);

dvariable ghk(const dvar_vector & lower, const dvar_vector & upper,
  const dvar_matrix & Sigma, const dmatrix & eps);

dvariable ghk(const dvar_vector & lower, const dvar_vector & upper,
  const dvar_matrix & Sigma, const dmatrix & eps, int i);

dvariable ghk_choleski_m_cauchy(const dvar_vector & upper,
  const dvar_matrix & ch, const dmatrix & eps);

dvariable ghk_choleski_m_logistic(const dvar_vector & upper,
  const dvar_matrix & ch, const dmatrix & eps);

/**
 * Description not yet available.
 * \param
 */
class function_minimizer_exception
{
 public:
   function_minimizer_exception(void)
   {
   }
};

void tracing_message(int traceflag, const char *s);
void tracing_message(int traceflag, const char *s, int *pn);
void tracing_message(int traceflag, const char *s, double *pd);
void tracing_message(int traceflag, const char *s, double d);

int sub_unallocated(const dvar_vector&);
int sub_unallocated(const dvar_matrix&);
int sub_unallocated(const dvar3_array&);
int sub_unallocated(const dvar4_array&);
int sub_unallocated(const dvar5_array&);
int sub_unallocated(const dvector&);
int sub_unallocated(const dmatrix&);
int sub_unallocated(const d3_array&);
int sub_unallocated(const d4_array&);
int sub_unallocated(const d5_array&);
int sub_unallocated(const ivector&);
int sub_unallocated(const imatrix&);
int sub_unallocated(const i3_array&);
int sub_unallocated(const i4_array&);
int sub_unallocated(const i5_array&);

void check_derivative_values(const char *s);
void check_derivative_values(const char *s, int i);
void check_derivative_values_break(const char *s, int i, int b);
void df_check_derivative_values(void);
void df_check_derivative_values_indexed(void);
void df_check_derivative_values_indexed_break(void);
extern int ad_kill_flag;
void reset_gradient_stack(void);

#define AD_SET_DERIVATIVES1(depvar,indvar,df)  \
     gradient_structure::GRAD_STACK1->set_gradient_stack2(default_evaluation2,\
       &(value(depvar)), &(value(indvar)),df);

#define AD_SET_DERIVATIVES2(depvar,indvar1,df1,indvar2,df2)  \
     gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation3,\
       &(value(depvar)), &(value(indvar1)),df1,&(value(indvar2)),df2);

#define AD_SET_DERIVATIVES3(depvar,indvar1,df1,indvar2,df2,indvar3,df3)  \
    gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation3ind,\
      &(value(depvar)), &(value(indvar1)),df1,&(value(indvar2)),df2, \
      &(value(indvar3)),df3);

#define AD_SET_DERIVATIVES4(depvar,indvar1,df1,indvar2,df2,indvar3,df3, \
  indvar4, df4)  \
    gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation4ind,\
      &(value(depvar)), &(value(indvar1)),df1,&(value(indvar2)),df2, \
      &(value(indvar3)),df3, \
      &(value(indvar4)),df4);

#define ADJOINT_CODE(x) \
     gradient_structure::GRAD_STACK1->set_gradient_stack(x);

int make_sub_directory(const char *s);
#include <adstring.hpp>
adstring get_string_marker(void);
#if defined(USE_ADPVM)
class adpvm_manager;
#endif
class adtimer;

/**
 * Description not yet available.
 * \param
 */
class ad_comm
{
protected:
  ad_comm();
  ad_comm(int argc, char *argv[]);
  virtual ~ad_comm();

  void allocate();
 public:
   static int time_flag;
   static int bandwidth;
   static int print_hess_and_exit_flag;
   static int no_pvm_flag;
   static int no_atlas_flag;
   static int no_ln_det_choleski_flag;
   static adtimer *ptm;
   static adtimer *ptm1;
#if defined(USE_ADPVM)
   virtual void get_slave_assignments(void);
   static adpvm_manager *pvm_manager;
#endif
   static adstring subdir;
   static streampos change_datafile_name(const adstring & s,
     const streampos & off = 0);
   static streampos change_pinfile_name(const adstring & s,
     const streampos & off = 0);
   static cifstream *global_datafile;
   static cifstream *global_parfile;
   static ofstream *global_logfile;
   static uistream *global_bparfile;
   static adstring adprogram_name;
   static adstring working_directory_path;
   static char option_flags[];
   static int argc;
   static unsigned int wd_flag;
   static unsigned char directory_prefix;
   static char **argv;
};

int option_match(int argc, char *argv[], const char *string);
int option_match(int argc, char *argv[], const char *string, int& nopt);
int option_match(char *s, const char *string, int& nopt);
int option_match(char *s, const char *string);
int ad_chdir(const char *s);
void ad_getcd(const adstring & s);
void grad_chk(void);
void send_dv3_to_master(const dvar3_array & v);

inline dvariable inv(const prevariable & x)
{
   return 1.0 / x;
}

double gamma_density(double _x, double r, double mu);
dvariable gamma_density(const prevariable & _x, double r, double mu);
dvariable gamma_density(const dvariable & _x, const dvariable & _r,
  const dvariable & _mu);

double log_gamma_density(double _x, double r, double mu);
dvariable log_gamma_density(const prevariable & _x, double r, double mu);
dvariable log_gamma_density(const dvariable & _x, const dvariable & _r,
  const dvariable & _mu);

#if !defined(_WIN32)
#include <sys/time.h>
#include <iostream>

/**
 * Description not yet available.
 * \param
 */
class adtimer
{
   timeval tv;
   timeval tvold;
 public:
   double get_elapsed_time_and_reset(void);// return time in milliseconds;
   double get_elapsed_time(void);// return time in milliseconds;
   adtimer(void);
};

#else
#include <windows.h>

/**
 * Description not yet available.
 * \param
 */
class adtimer
{
#ifdef _MSC_VER
  unsigned long long t;
  unsigned long long told;
#else
  DWORD t;
  DWORD told;
#endif
public:
  adtimer();

  // return time in milliseconds;
  double get_elapsed_time_and_reset();
  // return time in milliseconds;
  double get_elapsed_time();
};

#endif
#if defined(max)
#undef max
#endif
#if defined(min)
#undef min
#endif

// M is a postiive definite symmetric matrix
dvariable ln_det_choleski(const dvar_matrix & M);
dvariable ln_det_choleski_error(const dvar_matrix &, int &ierr);

// the autodif wrapper to the ATLAS routines

// M is a postiive definite symmetric matrix
dvector atlas_solve_spd(const dmatrix & M, const dvector & x);
dvector atlas_solve_spd(const dmatrix & M, const dvector & x, int &ierr);
dmatrix atlas_solve_spd(const dmatrix & M, const dmatrix & x);
dmatrix atlas_solve_spd_trans(const dmatrix & M, const dmatrix & x);

/**
 * Description not yet available.
 * \param
 */
class lower_triangular_dmatrix:public dmatrix
{
 public:
   lower_triangular_dmatrix(int, int);
};
dmatrix symmetrize(const lower_triangular_dmatrix & M);
dvector solve(const lower_triangular_dmatrix & M, const dvector & v);
dvector lower_triangular_solve(const dmatrix & M, const dvector & v);
dvar_vector lower_triangular_solve(const dvar_matrix& M, const dvar_vector& v);
dvector solve_trans(const lower_triangular_dmatrix & M, const dvector & v);
dmatrix fillout(const lower_triangular_dmatrix & M);
dmatrix fillout_trans(const lower_triangular_dmatrix & M);

lower_triangular_dmatrix lower_triangular_choleski_decomp_positive
   (const dmatrix & MM, const int &_ierr);

dvar_vector solve_trans(const banded_lower_triangular_dvar_matrix & M,
  const dvector & y);

inline int admax(int i, int j)
{
   if (i > j)
      return i;
   else
      return j;
}

inline int admin(int i, int j)
{
   if (i > j)
      return j;
   else
      return i;
}

d4_array orthpoly2(int n, int m, int d1, int d2);
double dot(const dmatrix & M, const dmatrix & d2);

double norm(const banded_symmetric_dmatrix & B);
double norm2(const banded_symmetric_dmatrix & B);
double sumsq(const banded_symmetric_dmatrix & B);
dvariable norm(const banded_symmetric_dvar_matrix & B);
dvariable norm2(const banded_symmetric_dvar_matrix & B);
dvariable sumsq(const banded_symmetric_dvar_matrix & B);

double lower_triangular_ln_det(const dmatrix & m);
double lower_triangular_ln_det(const dmatrix & m, int &sgn);

dvariable lower_triangular_ln_det(const dvar_matrix & m);
dvariable lower_triangular_ln_det(const dvar_matrix & m, int &sgn);
double bounder(double x, double min, double max, double scale);
dvariable bounder(const prevariable & x, double min, double max, double scale);
dmatrix inv(const dmatrix & m1, const double &_ln_det, const int &_sgn);

double gamma_deviate(double _x, double _a);
dvariable gamma_deviate(const prevariable & _x, const prevariable & _a);
void ad_set_new_handler(void);

dvariable inv_cumd_gamma(const prevariable & _y, const prevariable & _a);
double inv_cumd_gamma(double _y, double _a);
extern int just_to_link_fvar1;

dvector inv_cumd_pareto(const dvector & _y, double alpha, double xm);

dvector cumd_upper_trunc_pareto(const dvector & _y, double alpha, double xm);

dvector cumd_pareto(const dvector & _y, double alpha, double xm);

dvector inv_cumd_upper_trunc_pareto(const dvector & _y, double alpha,
  double xmin, double xmax);

dvar_vector inv_cumd_upper_trunc_pareto(const dvar_vector & _y,
  const prevariable & alpha, const prevariable & xmin, const prevariable& xmax);

dvar_vector inv_cumd_pareto(const dvar_vector & _y, const prevariable & alpha,
  const prevariable & xm);

dvar_vector ln_upper_trunc_pareto_density(const dvar_vector & _y,
  const prevariable & alpha, const prevariable & xm);

dvar_vector ln_pareto_density(const dvar_vector & _y, const prevariable & alpha,
  const prevariable & xm);

dvar_vector ln_pareto_upper_trunc_density(const dvar_vector & y,
  const prevariable & alpha, const prevariable& xmin, const prevariable& xmax);

dvar_vector pareto_density(const dvar_vector & _y, const prevariable & alpha,
  const prevariable & xm);

dvariable ln_upper_trunc_pareto_density(const prevariable & _y,
  const prevariable & alpha, const prevariable & xmin, const prevariable& xmax);

dvariable ln_pareto_density(const prevariable & _y, const prevariable & alpha,
  const prevariable & xm);

dvariable pareto_density(const prevariable & _y, const prevariable & alpha,
  const prevariable & xm);

dvar_vector cumd_pareto(const dvar_vector & _y, const prevariable & alpha,
  const prevariable & xm);

dvar_vector cumd_upper_trunc_pareto(const dvar_vector & _y,
  const prevariable & alpha, const prevariable & xmin, const prevariable& xmax);

dvariable inv_cumd_pareto(const prevariable& _y, const prevariable& alpha,
  const prevariable & xm);

dvariable cumd_upper_trunc_pareto(const prevariable & _y,
  const prevariable& alpha, const prevariable& xmin, const prevariable& xmax);

dvariable cumd_pareto(const prevariable & _y, const prevariable & alpha,
  const prevariable & xm);

dvariable inv_cumd_pareto(const prevariable & _y, const prevariable & alpha,
  const prevariable & xm);

dvariable cumd_pareto(const prevariable & _y, const prevariable & alpha,
  const prevariable & xm);

double inv_cumd_upper_trunc_pareto(double _y, double alpha, double xmin,
  double xmax);

double inv_cumd_pareto(double _y, double alpha, double xm);

double cumd_pareto(double _y, double alpha, double xm);

double robust_normal_logistic_mixture_deviate(double x, double spread = 3.0);
double robust_normal_mixture_deviate(double x, double spread = 3.0);
dvariable robust_normal_mixture_deviate(const prevariable & x,
  double spread = 3.0);

dvector lower_triagnular_solve_trans(const dmatrix & M, const dvector & y);
dvector lower_triagular_solve(const dmatrix & m, const dvector & v);
dvector choleski_solve_error(dmatrix M, dvector & v, int &ierror);
dvector choleski_solve_neghess_error(dmatrix M, dvector & v, int &ierror);

dvariable cumd_gamma(const dvariable & x, const dvariable & a);
double cumd_gamma(double x, double a);

dvariable cumd_normal_cauchy_mixture(const prevariable & _x, double _a);
dvar_vector cumd_normal_cauchy_mixture(const dvar_vector & _x, double _a);

dvariable cumd_normal_mixture(const prevariable & _x, double _a);
dvar_vector cumd_normal_mixture(const dvar_vector & _x, double _a);

dvariable inv_cumd_normal_mixture(const prevariable & _x, double _a);
dvariable inv_cumd_normal_logistic_mixture(const prevariable & _x, double _a);

double inv_cumd_normal_mixture(double _x, double _a);
double inv_cumd_normal_logistic_mixture(double _x, double _a);

double inv_cumd_t(double n, double y, double eps = 1.e-7);

dvariable inv_cumd_t(const prevariable & n, const prevariable & y,
  double eps = 1.e-7);

double old_inv_cumd_beta_stable(double a, double b, double y, double eps = 1.e-7);
double inv_cumd_beta_stable(double a, double b, double y, double eps = 0);
dvariable inv_cumd_beta_stable(const prevariable & _a, const prevariable & _b, const prevariable & _y, double eps = 0);

double qbeta(double x, double a, double b, double eps = 0);
dvariable qbeta(dvariable x, dvariable a, dvariable b, double eps = 0);

dvariable norm_to_gamma(const prevariable & v, const prevariable & alpha,
  double bound = 0.999999);

double norm_to_gamma(double v, double alpha, double bound = 0.999999);

dmatrix eigenvectors(const banded_symmetric_dmatrix & _SS,
  const dvector & e);
dvector eigenvalues(const banded_symmetric_dmatrix & _SS);
dvector get_eigen_values(const dvector & _d, const dvector & _e);
dvar_vector get_eigen_values(const dvar_vector & _d,
  const dvar_vector & _e);
dvector get_eigen_values(const dvector & _d, const dvector & _e,
  const dmatrix & _z);

dvariable beta_deviate(const prevariable & _x, const prevariable & _a,
  const prevariable & _b, double eps = 1.e-7);
double beta_deviate(double x, double a, double b, double eps = 1.e-7);

#ifdef __cplusplus
extern "C"
{
#endif
//#include <f2c.h>
int smbfct_(int *neqns, ivector & xadj, ivector & adjncy, ivector & perm,
  ivector & invp, ivector & xlnz, int *maxlnz, ivector & xnzsub,
  ivector & nzsub, int *maxsub, ivector & rchlnk, ivector & mrglnk,
  ivector & marker, int *flag__);

//  int smbfct_(int *neqns, int *xadj, int *adjncy,
//      int *perm, int *invp, int *xlnz, int *maxlnz, int
//      *xnzsub, int *nzsub, int *maxsub, int *rchlnk, int *
//      mrglnk, int *marker, int *flag__);
#ifdef __cplusplus
}
#endif

dmatrix orthpoly_constant_begin(int n, int deg, int nconst);
dmatrix orthpoly_constant_begin_end(int n, int deg, int nconst_begin,
  int enddeg, int nconst_end);
#if defined(USE_DD)
#  include <ddfvar.hpp>
#  include <qdfvar.hpp>
#endif

#ifdef DIAG
void test_the_pointer(void);
#endif

// stuff for debugging the grad stack
void set_gradstack_flag(char *str, int i, int j);
void set_gradstack_flag(char *str);
void report_gradstack_flag(void);

dvariable log_der_logistic(double a, double b, const prevariable & x);
double logistic(double a, double b, const double &x);
double dflogistic(double a, double b, const double &x);
dvariable logistic(double a, double b, const prevariable & x);
dvariable dflogistic(double a, double b, const prevariable & x);
double log_density_negbinomial(double x, double mu, double tau);

/**
 * Description not yet available.
 * \param
 */
class sing_val_decomp
{
   dmatrix a;
   dvector w;
   dmatrix v;
 public:
   sing_val_decomp()
   {
   };
   sing_val_decomp(const dmatrix & _a, const dvector & _w, const dmatrix & _v);
   dmatrix get_u(void)
   {
      return a;
   }
   dvector get_w(void)
   {
      return w;
   }
   dmatrix get_v(void)
   {
      return v;
   }
};

sing_val_decomp singval_decomp(const dmatrix & _a);
banded_lower_triangular_dmatrix choleski_decomp_trust_bound(
  const banded_symmetric_dmatrix& _M, const int &_ierr);

dvariable avg(const prevariable & x, const prevariable & y);
double avg(double x, double y);

/**
 * Description not yet available.
 * \param
 */
class multi_index
{
   int mind;
   int maxd;
   int depth;
   ivector index;
 public:
   multi_index(int min, int max, int dim);
   ivector & operator () (void)
   {
      return index;
   }
   void operator ++(void);
   int get_depth(void)
   {
      return depth;
   }
   int get_offset(void);
   void initialize();
};

inline void ADMB_getcallindex(int)
{
}

inline void ADMB_getcallindex(double)
{
}

inline void ADMB_getcallindex(const dvector&)
{
}

inline void ADMB_getcallindex(const dmatrix&)
{
}

inline void ADMB_getcallindex(const d3_array&)
{
}

inline void ADMB_getcallindex(const d4_array&)
{
}

inline void ADMB_getcallindex(const prevariable&)
{
}

inline void ADMB_getcallindex(const dvar_vector&)
{
}

inline void ADMB_getcallindex(const dvar_matrix&)
{
}

inline void ADMB_getcallindex(const dvar3_array&)
{
}

inline void ADMB_getcallindex(dvar4_array&)
{
}

void clean(ivector & v, int level);

/**
 * Description not yet available.
 * \param
 */
class dvar_compressed_triplet
{
   int n;
   int m;
   imatrix coords;
   dvar_vector x;
 public:
   int indexmin(void)
   {
      return x.indexmin();
   }
   int indexmax(void)
   {
      return x.indexmax();
   }
   prevariable operator [] (int i)
   {
      return x[i];
   }
   prevariable operator () (int i)
   {
      return x(i);
   }
   int &operator () (int i, int j)
   {
      return coords(i, j);
   }
   dvar_compressed_triplet(int mmin, int mmax, int n, int m);
   void allocate(int mmin, int mmax, int n, int m);
   void deallocate(void);
   imatrix & get_coords(void)
   {
      return coords;
   }
   dvar_vector & get_x(void)
   {
      return x;
   }
   int get_n()
   {
      return n;
   }
   int get_m()
   {
      return m;
   }
};

/**
 * Description not yet available.
 * \param
 */
class dcompressed_triplet
{
   // number of rows
   int n;
   // number of columns
   int m;
   imatrix coords;
   dvector x;
 public:
   int indexmin(void)
   {
      return x.indexmin();
   }
   int indexmax(void)
   {
      return x.indexmax();
   }
   double &operator [] (int i)
   {
      return x[i];
   }
   double &operator () (int i)
   {
      return x(i);
   }
   int &operator () (int i, int j)
   {
      return coords(i, j);
   }
   dcompressed_triplet(int mmin, int mmax, int n, int m);
   //dcompressed_triplet make_dcompressed_triplet(const dmatrix & );
   void allocate(int mmin, int mmax, int n, int m);
   void deallocate(void);
   imatrix & get_coords(void)
   {
      return coords;
   }
   dvector & get_x(void)
   {
      return x;
   }
   int get_n()
   {
      return n;
   }
   int get_m()
   {
      return m;
   }
   void initialize(void);
};

 /*
    ostream& operator <<  (const ostream&,const dcompressed_triplet& );
    istream& operator >>  (const istream&,const dcompressed_triplet& );
    ostream& operator <<  (const ostream&,const dvar_compressed_triplet& );
    istream& operator >>  (const istream&,const dvar_compressed_triplet& );
  */

typedef struct cs_symbolic css;

/**
 * Description not yet available.
 * \param
 */
class hs_symbolic // Info for symbolic cholesky
{
 public:
   // Dimension of underlying pos. def. matrix
   int n;
   // Dimension of underlying pos. def. matrix
   int m;
   // inverse row perm. for QR, fill red. perm for Chol
   ivector pinv;
   // elimination tree for Cholesky and QR
   ivector parent;
   // column pointers for Cholesky, row counts for QR
   ivector cp;
   // # entries in L for LU or Cholesky; in V for QR
   double lnz;
   hs_symbolic(int, css *);
   hs_symbolic(int n, dmatrix & T, int order);
   hs_symbolic(const dcompressed_triplet & T, int order);

   hs_symbolic(const dvar_compressed_triplet & T, int order);
   int is_null();
   int cmp(hs_symbolic & S);
   hs_symbolic(void);
};

class hs_smatrix;
class dvar_hs_smatrix;


hs_smatrix *return_choleski_decomp(dcompressed_triplet & st);

dvector return_choleski_factor_solve(hs_smatrix * PL, dvector & eps);

dvar_vector return_choleski_factor_solve(dvar_hs_smatrix * PL,
  dvector & eps);

dvector return_choleski_decomp_solve(dcompressed_triplet & dct,
  dvector & eps);

dvar_hs_smatrix *return_choleski_decomp(dvar_compressed_triplet & st);

int allocated(const dcompressed_triplet & t);
int allocated(const dvar_compressed_triplet & t);

dvector solve(const dcompressed_triplet &, const dmatrix &,
  const dvector &);
dvector solve(const dcompressed_triplet &, const dvector &,
  const hs_symbolic &, int &ierr);
dvector solve(const dcompressed_triplet &, const dvector &,
  const hs_symbolic &);
dvector solve(const dcompressed_triplet &, const dmatrix &,
  const dvector &, const hs_symbolic &);
double ln_det(const dcompressed_triplet &);
double ln_det(const dcompressed_triplet &, const hs_symbolic &);
double ln_det(const dcompressed_triplet &, int &ierr);
dvariable ln_det(const dvar_compressed_triplet &, int &ierr);

dvar_vector return_choleski_factor_solve(dvar_hs_smatrix * PL,
  dvector & eps);
void save_ad_pointer(void *);
void *restore_ad_pointer(void);

class laplace_approximation_calculator;

dvariable ln_det(dvar_compressed_triplet &, hs_symbolic &,
  laplace_approximation_calculator *);

dvariable ln_det(dvar_compressed_triplet &);
dvariable ln_det(dvar_compressed_triplet &, hs_symbolic &);
dvariable ln_det(dvar_compressed_triplet &, hs_symbolic &,
  dcompressed_triplet &);

dmatrix make_dmatrix(dcompressed_triplet & M);
int norm2(const ivector &);
int sumsq(const ivector & v);

#endif//#ifndef FVAR_HPP
