#if !defined(__ADPTHREAD__)
#define __ADPTHREAD__ 
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */

/* struct to hold data to be passed to a thread
 *    this shows how multiple data items can be passed to a thread */
  union a_union 
  {
    char * p;
    double d;
  };
 //     //
 // /* prototype for thread routine */
 void admb_thread(void * ptr);
 // 
  class thread_data
  {
  public:
    static __thread int id;
    int thread_no;
    int bufsize;
    pthread_mutex_t *inlock;
    pthread_mutex_t *outlock;
    void * transfer_buffer;
    char message[100];
  };
 // 
 typedef char * pchar;
 // 
 /*
  class adpthread_manager
  {
    static __ADMBTHREAD__ int slave_number;
  public:
    static int is_slave(void) { if (slave_number)
                                  return 1;
                                else
                                  return 0; }
    static int is_master(void) { if (slave_number)
                                  return 0;
                                else
                                  return 1; }
    static int get_slave_number(void) { return slave_number; }
    static void set_slave_number(int n) { slave_number=n; }

    char ** transfer_buffer;
    char ** current_bptr;
    char ** buffend;
    int nslaves;
    int bs;
    int * mflag;
    int * sflag;
    ivector buffer_size;
    pthread_mutex_t * smutex;
    pthread_cond_t * scondition;
    pthread_cond_t *mcondition;
    pthread_t * thread1;  // thread variables 
    adpthread_manager(int ns,int bs);
    void send_double_to_slave(const double &x,int sno);
    void send_double_to_master(double &x,int sno);
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
    double get_double_from_master_nl(int sno);
    //void send_dvar_vector_to_slave(const dvar_vector &x,int sno);
    void writebuffer(const void *x,int nbytes,int sno);
    void readbuffer(const void *x,int nbytes,int sno);
    void pthread_join_all(void);
    void create_all(void*f,thread_data * ptr);
    void check_buffer_size(int, int);
    void check_buffer_size_read(int, int);
    void memcpy(const double &x,int sno);
    void send_double_to_slave_nl(const double &x,int sno);
    void read_lock_buffer_slave(int sno);
    void write_lock_buffer_slave(int sno);
    void read_lock_buffer_master(int sno);
    void write_lock_buffer_master(int sno);
    void read_unlock_buffer_slave(int sno);
    void write_unlock_buffer_slave(int sno);
    void read_unlock_buffer_master(int sno);
    void write_unlock_buffer_master(int sno);
    void adjoint_slave_write_unlock(int sno);
    void adjoint_slave_write_lock(int sno);
    void adjoint_master_write_lock(int sno);
    void verify_id_string_from_master_nl(const char * s,int sno);
    void send_id_string_to_slave_nl(const char * s,int sno);
    void verify_id_string_from_slave_nl(const char * s,int sno);
    void send_id_string_to_master_nl(const char * s,int sno);
    void adjoint_send_dvariable_to_master(void);
    void adjoint_get_dvariable_from_slave(void);
    void adjoint_get_dvar_vector_from_master(void);
    void adjoint_send_dvar_vector_to_slave(void);
    void adjoint_write_unlock_buffer_master(void);
    void adjoint_read_lock_buffer_master(void);
    void adjoint_read_lock_buffer_slave(void);
    void adjoint_write_unlock_buffer_slave(void);
    void adjoint_read_unlock_buffer_slave(void);
    void adjoint_read_unlock_buffer_master(void);
    void adjoint_write_lock_buffer_slave(void);
    void adjoint_write_lock_buffer_master(void);
    void send_dvar_matrix_to_slave(const dvar_matrix &x,int sno);
    void adjoint_send_dvar_matrix_to_slave(void);
  };
 */
  extern adpthread_manager * test_thread_manager;

#endif  // if !defined(__ADPTHREAD__)
