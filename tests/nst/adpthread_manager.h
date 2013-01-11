// $Id: adpthread_manager.h 3054 2013-01-10 22:54:36Z jsibert $
#ifndef __admb__adpthread_manager__
#define __admb__adpthread_manager__ 1.0

//#include <admodel.h>
#include <fvar.hpp>
#include <pthread.h>


/*
extern pthread_mutex_t * smutex;
extern pthread_cond_t * scondition;
extern pthread_cond_t *mcondition;
extern int * mflag;
extern int * sflag;
*/
  
class thread_data
{
public:
  static int __thread id;
  int thread_no;
  int bufsize;
  pthread_mutex_t *inlock;
  pthread_mutex_t *outlock;
  void * transfer_buffer;
  char message[100];
};

typedef char * pchar;

class adpthread_manager
{
public:
  char ** transfer_buffer;
  char ** buffend;
  char ** tb_save;
  int nslaves;
  int bs;

  /** Indicates state of "master" tranfer buffer; thread-specific.
  0 => able to receive data; 1 => buffer contains data.
  Set to 1 by "send to slave" functions; 
  set to 0 by "get from master" functions.
  Integer vector with the same number of entries as the thread vector;
  one flag for each thread.
  */
  int * mflag;

  /** Indicates state of "slave" tranfer buffer; thread-specific. 
  0 => able to receive data; 1 => buffer contains data.
  Set to 1 by "send to master" and "slave pack derivative" functions; 
  set to 0 by get from slave functions.
  Integer vector with the same number of entries as the thread vector;
  one flag for each thread.
  */
  int * sflag;
  //pthread_rwlock_t * tb_lock;
  pthread_mutex_t * smutex;
  pthread_cond_t * scondition;
  pthread_cond_t *mcondition;
  pthread_t * thread1;  // thread variables
  static int pt_res;
  static void pt_result(const char *string, const char* file, const int line);

  adpthread_manager(int ns,int bs);
 ~adpthread_manager();
  void initialize(void);

  void send_int_to_slave(const int z,int sno);
  void send_ivector_to_slave(const ivector &x,int sno);
  ivector get_ivector_from_slave(int sno);
  ivector get_ivector_from_master(int sno);
  int get_int_from_master(int sno);
  void send_double_to_slave(const double x,int sno);
  void send_double_to_master(const double x,int sno);
  double get_double_from_slave(int sno);
  double get_double_from_master(int sno);
  void send_dvariable_to_slave(const prevariable &x,int sno);
  void send_dvariable_to_master(const prevariable &x,int sno);
  dvariable get_dvariable_from_slave(int sno);
  dvariable get_dvariable_from_master(int sno);
  void send_dvector_to_slave(const dvector &x,int sno);
  void send_dvector_to_master(const dvector &x,int sno);
  dvector get_dvector_from_slave(int sno);
  dvector get_dvector_from_master(int sno);
  dvar_vector get_dvar_vector_from_slave(int sno);
  dvar_vector get_dvar_vector_from_master(int sno);
  void send_dvar_vector_to_slave(const dvar_vector &x,int sno);
  void send_dvar_vector_to_master(const dvar_vector &x,int sno);
  void send_dvar_matrix_to_slave(const dvar_matrix &x,int sno);
  dvar_matrix get_dvar_matrix_from_master(int sno);
  dmatrix get_dmatrix_from_master(int sno);
  void pthread_join_all(void);
  void create_all(void*f,thread_data * ptr);

};

/**
\mainpage
   \author John Sibert
   \author Extends new_sim_thread3 example by Dave Fournier.

   \todo Stuff
   \todo More stuff
*/
#endif
