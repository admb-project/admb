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
 extern const int NSLAVES;
 // 
 typedef char * pchar;
 // 
  class adpthread_manager
  {
  public:
    char ** transfer_buffer;
    char ** buffend;
    int nslaves;
    int bs;
    int * mflag;
    int * sflag;
    pthread_mutex_t * smutex;
    pthread_cond_t * scondition;
    pthread_cond_t *mcondition;
    pthread_t * thread1;  /* thread variables */
    adpthread_manager(int ns,int bs)
    {
      int i;
      nslaves=ns;
      transfer_buffer=new pchar[ns];
      buffend=new pchar[ns];
      transfer_buffer--;
      buffend--;
      for (i=1;i<=ns;i++)
      {
        transfer_buffer[i]=new char[bs];
        buffend[i]=transfer_buffer[i]+bs-1;
      }
      mflag=new int[ns];
      mflag--;
      sflag=new int[ns];
      sflag--;
      smutex=new pthread_mutex_t[ns];
      smutex--;
      for (i=1;i<=ns;i++)
      {
        pthread_mutex_init(smutex+i,NULL);
      }
      scondition=new pthread_cond_t[ns];
      scondition--;
      mcondition=new pthread_cond_t[ns];
      mcondition--;
      thread1=new pthread_t[ns];
      thread1--;
    }
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
    void pthread_join_all(void);
    void create_all(void*f,thread_data * ptr);
  };
  extern adpthread_manager * test_thread_manager;

#endif  // if !defined(__ADPTHREAD__)
