#if !defined(__ADXTHREAD__)
#define __ADXTHREAD__

#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */

typedef ofstream * pofstream;
typedef void* (*pthreadfun)(void*);
typedef pthreadfun* ppthreadfun;
typedef pthread_mutex_t* ppthread_mutex_t;
typedef pthread_cond_t* ppthread_cond_t;

class new_thread_data
{
public:
  new_thread_data(void)
  {
    thread_no = 0;
  }
public:
  int thread_no;
};
class adthread_buffer
{
public:
  adthread_buffer();
  adthread_buffer(const adthread_buffer& other);
  virtual ~adthread_buffer();

public:
  void lock();
  void unlock();

  bool islocked() const { return locked; }

private:
  bool locked;
  pthread_mutex_t mutex;
  pthread_cond_t condition;
};
class adpthread_manager
{
private:
  int num_code;
  int logflag;
  static __thread int slave_number;
  adtimer* adt;
  pofstream* logfiles;
  ppthreadfun ppf;
public:
  adpthread_manager(int ns, int bs);
  adpthread_manager(int ngroups, ivector& group_num, int bs);
  virtual ~adpthread_manager() {}

public:
  static bool is_slave(void) { return slave_number ? true : false; }
  static bool is_master(void) { return !is_slave(); }
  static void set_slave_number(int n) { slave_number = n; }
  static int get_slave_number(void) { return slave_number; }

  int nslaves;
  int initial_buffer_size;
  int ngroups;
  ivector gmin;
  ivector gmax;
  ivector num_in_group;
  int bs;
  ivector mflag;
  ivector sflag;
  ivector buffer_size;
  pthread_mutex_t copy_mutex;
  pthread_mutex_t* smutex;
  pthread_cond_t* scondition;
  pthread_cond_t* mcondition;
  imatrix sbuffer_size;
  char*** stransfer_buffer;
  char*** scurrent_bptr;
  char*** sbuffend;
  imatrix smflag;
  imatrix ssflag;
  pthread_mutex_t** ssmutex;
  pthread_cond_t** sscondition;
  pthread_cond_t** smcondition;
  pthread_t* thread1;

  void attach_code(pthreadfun pf);
  void check_buffer_size(int, int,int);
  void check_buffer_size_read(int, int,int);
  void create_all(pthreadfun pf,new_thread_data * ptr);
  void create_all(void * ptr);
  void pthread_join_all(void);
  void writebuffer(const void *x,int nbytes,int sno);
  void readbuffer(const void *x,int nbytes,int sno);
  void send_id_string(const char * s,int sno);
  void verify_id_string(const char * s,int sno);
  long int get_offset(int sno);
  double get_double(int sno);
  int get_int(int);
  dvector get_dvector(int sno);
  dmatrix get_dmatrix(int sno);
  imatrix get_imatrix(int sno);
  dvariable get_dvariable(int sno);
  ivector get_ivector(int sno);
  adstring get_adstring(int sno);
  dvar_vector get_dvar_vector(int sno);
  dvar_matrix get_dvar_matrix(int sno);
  void send_double(const double&, int);
  void send_int(int, int);
  void send_dvector(const dvector &x,int sno);
  void send_dmatrix(const dmatrix &x,int sno);
  void send_imatrix(const imatrix &x,int sno);
  void send_dvariable(const prevariable &x,int sno);
  void send_ivector(const ivector &x,int sno);
  void send_adstring(const adstring &x,int sno);
  void send_dvar_vector(const dvar_vector &x,int sno);
  void send_dvar_matrix(const dvar_matrix &x,int sno);
  void adjoint_get_dvariable(void);
  void adjoint_get_dvar_vector(void);
  void adjoint_get_dvar_matrix(void);
  void adjoint_send_dvariable(void);
  void adjoint_send_dvar_vector(void);
  void adjoint_send_dvar_matrix(void);

  void write_lock_buffer(int sno);
  void write_unlock_buffer(int sno);
  void cwrite_lock_buffer(int sno);
  void cwrite_unlock_buffer(int sno);
  void adjoint_adwrite_lock_buffer_1(void);
  void adjoint_adwrite_unlock_buffer_1(void);
  void adjoint_adwrite_lock_buffer_2(void);
  void adjoint_adwrite_unlock_buffer_2(void);

  void read_lock_buffer(int sno);
  void read_unlock_buffer(int sno);
  void cread_lock_buffer(int sno);
  void cread_unlock_buffer(int sno);
  void adjoint_adread_lock_buffer_1(void);
  void adjoint_adread_unlock_buffer_1(void);
  void adjoint_adread_lock_buffer_2(void);
  void adjoint_adread_unlock_buffer_2(void);
/*
  void send_dvar_vector_to_master(const dvar_vector &x,int sno);
  void create_all(pthreadfun pf,void * ptr);
  void memcpy(const double &x,int sno);
  dvar_matrix get_dvar_matrix_from_master(int sno);
  dmatrix get_dmatrix_from_master(int sno);
  dvar_matrix get_dvar_matrix_from_slave(int sno);
  void adjoint_get_dvar_matrix_from_slave(void);
  void send_dvar_matrix_to_master(const dvar_matrix &x,int sno);
  void adjoint_send_dvar_matrix_to_master(void);
  void send_pointer(void*, int);
  void * get_pointer(int);

  void adjoint_send_dvar3_array_to_slave(void);
  void send_dvar3_array_to_slave(const dvar3_array &x,int sno);
  void send_dvar3_array(const dvar3_array &x,int sno);
  void send_d3_array(const d3_array &x,int sno);
  void send_i3_array(const i3_array &x,int sno);
  void adjoint_get_dvar3_array_from_master(void);
  dvar3_array get_dvar3_array_from_master(int sno);
  dvar3_array get_dvar3_array(int sno);
  d3_array get_d3_array(int sno);
  i3_array get_i3_array(int sno);
  dvar3_array get_dvar3_array_from_slave(int sno);
  void adjoint_get_dvar3_array_from_slave(void);
  void send_dvar3_array_to_master(const dvar3_array &x,int sno);
  void adjoint_send_dvar3_array_to_master(void);

  void adjoint_send_dvar4_array_to_slave(void);
  void send_dvar4_array_to_slave(const dvar4_array &x,int sno);
  void send_dvar4_array(const dvar4_array &x,int sno);
  void send_d4_array(const d4_array &x,int sno);
  void send_i4_array(const i4_array &x,int sno);
  void adjoint_get_dvar4_array_from_master(void);
  dvar4_array get_dvar4_array_from_master(int sno);
  dvar4_array get_dvar4_array_from_slave(int sno);
  dvar4_array get_dvar4_array(int sno);
  d4_array get_d4_array(int sno);
  i4_array get_i4_array(int sno);
  void adjoint_get_dvar4_array_from_slave(void);
  void send_dvar4_array_to_master(const dvar4_array &x,int sno);
  void adjoint_send_dvar4_array_to_master(void);

  void adjoint_send_dvar5_array_to_slave(void);
  void send_dvar5_array_to_slave(const dvar5_array &x,int sno);
  void send_d5_array(const d5_array &x,int sno);
  void send_dvar5_array(const dvar5_array &x,int sno);
  void adjoint_get_dvar5_array_from_master(void);
  dvar5_array get_dvar5_array_from_master(int sno);
  dvar5_array get_dvar5_array(int sno);
  d5_array get_d5_array(int sno);
  dvar5_array get_dvar5_array_from_slave(int sno);
  void adjoint_get_dvar5_array_from_slave(void);
  void send_dvar5_array_to_master(const dvar5_array &x,int sno);
  void adjoint_send_dvar5_array_to_master(void);
*/
};
#endif
