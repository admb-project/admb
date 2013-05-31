#if !defined(__ADXTHREAD__)
#define __ADXTHREAD__ 
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
 typedef char * pchar;
 typedef ofstream * pofstream;
 typedef void (*pthreadfun)(void*);
 typedef pthreadfun * ppthreadfun;
 typedef pthread_mutex_t * ppthread_mutex_t;  
 typedef pthread_cond_t * ppthread_cond_t;


  class thread_data
  {
  public:
    int thread_no;
    int bufsize;
    int m;
  };
  class dvar_fish_stock_history;
  class dvar_len_fish_stock_history;
  class new_thread_data
  {
  public:
    int thread_no;
    int m;
    dvar_len_fish_stock_history * pfsh;
    new_thread_data(void);
  };
 // 
 typedef char * pchar;
 // 
  class adpthread_manager
  {
    int num_code;
    static int old_buffer_flag;
    int logflag;
    static __ADMBTHREAD__ int slave_number;
    adtimer * adt;
    pofstream * logfiles;
    ppthreadfun ppf;
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
    static void set_old_buffer_flag(int n) { old_buffer_flag=n;}

    char ** transfer_buffer;
    char ** current_bptr;
    char ** buffend;
    int nslaves;
    int initial_buffer_size;
    int ngroups;
    ivector gmin;
    ivector gmax;
    int nfun;
    ivector num_in_group;
    int bs;
    ivector mflag;
    ivector sflag;
    ivector buffer_size;
    pthread_mutex_t copy_mutex;
    pthread_mutex_t start_mutex;
    pthread_mutex_t * smutex;
    pthread_cond_t * scondition;
    pthread_cond_t * mcondition;
    imatrix sbuffer_size;
    char *** stransfer_buffer;
    char *** scurrent_bptr;
    char *** sbuffend;
    imatrix smflag;
    imatrix ssflag;
    pthread_mutex_t ** ssmutex;
    pthread_cond_t ** sscondition;
    pthread_cond_t ** smcondition;
    pthread_t * thread1;  /* thread variables */
    adpthread_manager(int ns,int bs);
   ~adpthread_manager();
    adpthread_manager(int ngroups,ivector& group_num,int bs);
    void send_dvector_to_slave(const dvector &x,int sno);
    void send_dvector(const dvector &x,int sno);
    void send_dvector_to_master(const dvector &x,int sno);
    dvector get_dvector_from_slave(int sno);
    dvector get_dvector(int sno);
    dvector get_dvector_from_master(int sno);
    dvar_vector get_dvar_vector_from_slave(int sno);
    dvar_vector get_dvar_vector(int sno);
    dvar_vector get_dvar_vector_from_master(int sno);
    void send_dvar_vector_to_slave(const dvar_vector &x,int sno);
    void send_dvar_vector(const dvar_vector &x,int sno);
    void send_dvar_vector_to_master(const dvar_vector &x,int sno);
    double get_double_from_master_nl(int sno);
    //void send_dvar_vector_to_slave(const dvar_vector &x,int sno);
    void writebuffer(const void *x,int nbytes,int sno);
    void readbuffer(const void *x,int nbytes,int sno);
    void pthread_join_all(void);
    void create_all(pthreadfun pf,void * ptr);
    void create_all(pthreadfun pf,new_thread_data * ptr);
    void create_all(pthreadfun pf,thread_data * ptr);
    void attach_code(pthreadfun pf);
    void create_all(void * ptr);
    void check_buffer_size(int, int);
    void check_buffer_size(int, int,int);
    void check_buffer_size_read(int, int);
    void check_buffer_size_read(int, int,int);
    void memcpy(const double &x,int sno);
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
    void verify_id_string_from_master(const char * s,int sno);
    void send_id_string_to_slave(const char * s,int sno);
    void verify_id_string_from_slave(const char * s,int sno);
    void send_id_string_to_master(const char * s,int sno);
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
    void adjoint_get_dvar_matrix_from_master(void);
    dvar_matrix get_dvar_matrix_from_master(int sno);
    dmatrix get_dmatrix_from_master(int sno);
    dvar_matrix get_dvar_matrix(int sno);
    dmatrix get_dmatrix(int sno);
    imatrix get_imatrix(int sno);
    ivector get_ivector(int sno);
    dvar_matrix get_dvar_matrix_from_slave(int sno);
    void adjoint_get_dvar_matrix_from_slave(void);
    void send_dvar_matrix_to_master(const dvar_matrix &x,int sno);
    void send_dvar_matrix(const dvar_matrix &x,int sno);
    void send_dmatrix(const dmatrix &x,int sno);
    void send_imatrix(const imatrix &x,int sno);
    void send_ivector(const ivector &x,int sno);
    void adjoint_send_dvar_matrix_to_master(void);
    void send_int_to_slave(int, int);
    void send_int(int, int);
    void send_pointer(void*, int);
    void send_int_to_master(int, int);
    int get_int_from_master(int);
    int get_int(int);
    void * get_pointer(int);
    int get_int_from_slave(int);
    void send_dvariable_to_slave(const prevariable &x,int sno);
    void send_dvariable(const prevariable &x,int sno);
    void send_dvariable_to_master(const prevariable &x,int sno);
    dvariable get_dvariable_from_slave(int sno);
    dvariable get_dvariable(int sno);
    dvariable get_dvariable_from_master(int sno);
    void adjoint_send_dvariable_to_slave(void);
    void send_double_to_master(const double&, int);
    void send_double(const double&, int);
    void send_double_to_slave(const double &x,int sno);
    double get_double_from_slave(int sno);
    double get_double(int sno);
    double get_double_from_master(int sno);

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

    void adjoint_adwrite_lock_buffer_1(void);
    void adjoint_adwrite_lock_buffer_2(void);
    void adjoint_adwrite_unlock_buffer_1(void);
    void adjoint_adwrite_unlock_buffer_2(void);
    void write_unlock_buffer(int sno);
    void cwrite_unlock_buffer(int sno);
    void write_lock_buffer(int sno);
    void cwrite_lock_buffer(int sno);

    void adjoint_adread_lock_buffer_1(void);
    void adjoint_adread_lock_buffer_2(void);
    void adjoint_adread_unlock_buffer_1(void);
    void adjoint_adread_unlock_buffer_2(void);
    void read_lock_buffer(int sno);
    void cread_lock_buffer(int sno);
    void read_unlock_buffer(int sno);
    void cread_unlock_buffer(int sno);
    long int get_offset(int sno);

  };  //end class
  extern adpthread_manager * test_thread_manager;

#endif  // if !defined(__ADXTHREAD__)
