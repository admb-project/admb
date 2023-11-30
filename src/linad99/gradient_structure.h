/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2014 Regents of the University of California
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
#ifndef __ADMB_GRADIENT_STRUCTURE_H__
#define __ADMB_GRADIENT_STRUCTURE_H__

#include <thread>
#include <fstream>
using std::ofstream;

#ifdef __BORLANDC__
  #define size_t long int
#endif

class dvariable;
class DF_FILE;
class dvector;
class dmatrix;
class dlink;
class double_and_int;
class arr_list;
class dvar_vector;
class dvar_vector_position;
class prevariable;
class indvar_offset_list;
class dependent_variables_information;
class grad_stack;
class uostream;
class dlist;
class imatrix_position;
class prevariable_position;

/**
 * Description not yet available.
 * \param
 */
class humungous_pointer
{
  size_t adjustment;
public:
  humungous_pointer();
  ~humungous_pointer() {}

  char* ptr;
  void free();
  void adjust(const size_t);
  humungous_pointer operator+(unsigned long int& offset);
  humungous_pointer& operator+=(unsigned long int& offset);
  humungous_pointer& operator=(void* p);
  int operator==(void* p);
  int operator!=(void* p);
  operator char*();
  operator void*();
  operator double_and_int*();
  operator double*();
};

#ifdef USE_THREAD
#define THREAD __thread
#define THREAD_LOCAL thread_local
  #ifdef _MSC_VER
    #define __thread __declspec(thread)
  #endif
#else
#define THREAD
#define THREAD_LOCAL
#endif
/**
 * class for things related to the gradient structures, including dimension of
 * arrays, size of buffers, etc.
 */
class gradient_structure
{
  DF_FILE* _fp;
  grad_stack* _GRAD_STACK1;

public:
  static THREAD_LOCAL DF_FILE* fp;
  static THREAD_LOCAL gradient_structure* _instance;
  static THREAD_LOCAL grad_stack* GRAD_STACK1;

  static gradient_structure* get() { return _instance; }

  DF_FILE* get_fp() { return _fp; }
  grad_stack* get_GRAD_STACK1() { return _GRAD_STACK1; }

  static gradient_structure* reset(gradient_structure*);

  dvariable* RETURN_PTR;
  dvariable* MIN_RETURN;
  dvariable* MAX_RETURN;
  static dvariable* next_RETURN_PTR();

  gradient_structure** gradients;
  unsigned int gradients_size;
  void create(const unsigned int size);
  gradient_structure* set(const unsigned int id);
  void clean();

  void gradcalc(int nvar, const dvector& g);
  void funnel_gradcalc();

#if defined(NO_DERIVS)
  static THREAD_LOCAL int no_derivatives;
#endif

   static long int USE_FOR_HESSIAN;
  long int NVAR;
   static unsigned int NUM_RETURN_ARRAYS;
  dvariable **RETURN_ARRAYS;
  unsigned int RETURN_ARRAYS_PTR;
  dvariable** RETURN_PTR_CONTAINER;
  size_t TOTAL_BYTES;
  size_t PREVIOUS_TOTAL_BYTES;
   static unsigned long ARRAY_MEMBLOCK_SIZE;//js
public:
  friend class arr_list;

   static size_t CMPDIF_BUFFER_SIZE;
   static size_t GRADSTACK_BUFFER_SIZE;
   static unsigned int MAX_NVAR_OFFSET;
  int save_var_file_flag;
   static int save_var_flag;

   static unsigned int MAX_DLINKS;
  indvar_offset_list* INDVAR_LIST;
   static int NUM_DEPENDENT_VARIABLES;
  dependent_variables_information* DEPVARS_INFO;

   // this needs to be a static member function so other static
   // member functions can call it
   static void check_set_error(const char *variable_name);

 public:

#ifdef USE_THREAD
   static unsigned int id;
#endif

   unsigned int x;

   // exception class
   class arrmemblerr
   {
   };

   static int Hybrid_bounded_flag;
  double* hessian_ptr;
   static long int get_USE_FOR_HESSIAN()
   {
      return USE_FOR_HESSIAN;
   }
   static void set_USE_FOR_HESSIAN(const long int i)
   {
      USE_FOR_HESSIAN = i;
   }
   friend class dfsdmat;

   gradient_structure(): gradient_structure(100000L) {}
   gradient_structure(const unsigned long int size);
   gradient_structure(const unsigned long int size, const unsigned int id);
   gradient_structure(const gradient_structure&) = delete;
   gradient_structure(gradient_structure&&) = delete;
   virtual ~gradient_structure();

   gradient_structure& operator=(const gradient_structure&) = delete;
   gradient_structure& operator=(gradient_structure&&) = delete;

  void save_variables();
  void restore_variables();
  void save_arrays();
  void restore_arrays();

  size_t totalbytes(void);

   friend dvector restore_dvar_vector_value(
     const dvar_vector_position& tmp);
   friend void cleanup_temporary_files();
   //friend dvector restore_dvar_vector_value(const dvar_vector_position&);
   friend dvector restore_dvar_vector_derivatives(void);
   friend dmatrix restore_dvar_matrix_derivatives(void);
   friend dmatrix restore_dvar_matrix_value(void);
   //friend dmatrix restore_derivatives(void);
   friend void gradfree(dlink * v);

  void make_indvar_list(const dvar_vector& t);

   //friend void gradcalc( int , double *);
   friend void gradcalc(int nvar, const dvector & g);
   friend void slave_gradcalc(void);
   friend void funnel_gradcalc(void);
   friend void allocate_dvariable_space(void);
   friend void wide_funnel_gradcalc(void);
   friend dvar_vector_position restore_dvar_vector_position(void);
   friend double_and_int *gradnew();
  dlist* GRAD_LIST;
   static unsigned int RETURN_ARRAYS_SIZE;
   //static int RETURN_INDEX;
  arr_list* ARR_LIST1;
   //static arr_list *ARR_FREE_LIST1;
   //static void funnel_jacobcalc(void);
  void jacobcalc(int nvar, const dmatrix& jac);
  void jacobcalc(int nvar, const ofstream& jac);
  void jacobcalc(int nvar, const uostream& jac);

   friend void default_evaluation(void);
   //access functions

   friend class DF_FILE;
   static void set_NUM_RETURN_ARRAYS(unsigned int i);
#if defined(NO_DERIVS)
   static void set_NO_DERIVATIVES(void);
   static void set_YES_DERIVATIVES(void);
#endif
   static void set_YES_SAVE_VARIABLES_VALUES();
   static void set_NO_SAVE_VARIABLES_VALUES();
   //static int _GRADFILE_PTR; // should be int gradfile_handle;
   //static int _GRADFILE_PTR1; // should be int gradfile_handle;
   //static int _GRADFILE_PTR2; // should be int gradfile_handle;
   //static int _VARSSAV_PTR; // should be int gradfile_handle;
   static void set_NUM_DEPENDENT_VARIABLES(int i);
   static void set_RETURN_ARRAYS_SIZE(unsigned int i);
   static void set_ARRAY_MEMBLOCK_SIZE(unsigned long i);
   static unsigned long get_ARRAY_MEMBLOCK_SIZE()
     { return ARRAY_MEMBLOCK_SIZE; }
   static void set_CMPDIF_BUFFER_SIZE(const size_t i);
   static void set_GRADSTACK_BUFFER_SIZE(const size_t i);
   static size_t get_GRADSTACK_BUFFER_SIZE()
     { return GRADSTACK_BUFFER_SIZE; }
   static void set_GRADSTACK_BUFFER_BYTES(const size_t i);
   static void set_MAX_NVAR_OFFSET(unsigned int i);
   static void set_MAX_DLINKS(int i);

  size_t NUM_GRADSTACK_BYTES_WRITTEN();

   static unsigned int get_MAX_DLINKS() { return MAX_DLINKS; }
  void save_dependent_variable_position(const prevariable&);
  unsigned long int max_last_offset;

  void RETURN_ARRAYS_DECREMENT();
  void RETURN_ARRAYS_INCREMENT();

   friend class dlist;
   friend class grad_stack;
   friend class function_minimizer;
   friend void funnel_derivatives(void);
};

/**
Stores the adjoint gradient data that will be processed
by gradcalc.
*/
class DF_FILE
{
public:
#ifdef USE_THREAD
  static unsigned int id;
#endif

  /// Default uses gradient_structure::CMPDIF_BUFFER_SIZE
  DF_FILE(): DF_FILE(gradient_structure::CMPDIF_BUFFER_SIZE) {}
  /// Do not allow copy contructor
  DF_FILE(const DF_FILE&) = delete;
  /// User defined size with default id
  DF_FILE(const size_t nbytes);
  DF_FILE(const size_t nbytes, const unsigned int id);
  ~DF_FILE();

  /// Do not allow assignment operator
  DF_FILE& operator=(const DF_FILE&) = delete;

  char* buff;
  OFF_T toffset;
  union
  {
    OFF_T offset;
    char fourb[sizeof(OFF_T)];
  };
  char cmpdif_file_name[81];
  int file_ptr;

  void fwrite(const void *s, const size_t num_bytes);
  void fread(void *s, const size_t num_bytes);

  void fwrite(const int &);
  void fread(const int &);

  void fwrite(double);
  void fread(const double &);

  void fread(void *&ptr);
  void fwrite(void *ptr);

  void write_cmpdif_stack_buffer();
  void read_cmpdif_stack_buffer(OFF_T & lpos);

  void save_double_value(double x);
  double restore_double_value();

  void save_int_value(int x);
  int restore_int_value();

  void save_pointer_value(void *ptr);
  void* restore_pointer_value();

  double restore_prevariable_value();

  d3_array_position restore_d3_array_position();

  void save_dvar_vector_value(const dvar_vector& v);

  dvector restore_dvector_value(const dvector_position& tmp);
  dmatrix restore_dmatrix_value(const dmatrix_position& mpos);
  d3_array restore_d3_array_value(const d3_array_position& mpos);
  dmatrix_position restore_dmatrix_position();
  dvector restore_dvar_vector_value(const dvar_vector_position& tmp);
  ivector restore_ivector_value(const ivector_position& tmp);
  dvector_position restore_dvector_position();

  void save_dvector_value(const dvector& v);
  void save_dvector_position(const dvector& v);

  void save_dvar_vector_position(const dvar_vector& v);
  dvar_vector_position restore_dvar_vector_position();

  dmatrix restore_dvar_matrix_value(const dvar_matrix_position& mpos);
  imatrix restore_imatrix_value(const imatrix_position& mpos);
  imatrix_position restore_imatrix_position();
  dvar_matrix_position restore_dvar_matrix_position();
  double restore_prevariable_derivative();
  prevariable_position restore_prevariable_position();
  void save_dmatrix_value(const dmatrix& m);
  void save_d3_array_value(const d3_array& a);
  void save_dmatrix_position(const dmatrix& m);

  void save_ivector_position(const ivector& v);
  ivector_position restore_ivector_position();

  void save_ivector_value(const ivector& v);
  void save_imatrix_value(const imatrix& m);

  void save_imatrix_position(const imatrix& m);
  void save_dvar_matrix_position(const dvar_matrix& m);
  void save_dvar_matrix_value(const dvar_matrix& m);

  void save_prevariable_position(const prevariable& v);
  void save_prevariable_value(const prevariable& v);

  void save_d3_array_position(const d3_array& a);

private:
  OFF_T buff_end;
#if defined(_MSC_VER) || defined(__MINGW64__)
  unsigned int buff_size;
#else
  size_t buff_size;
#endif
};
#endif
