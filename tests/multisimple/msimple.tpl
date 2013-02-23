//$Id: msimple.tpl 3054M 2013-01-11 20:23:43Z (local) $

GLOBALS_SECTION
  #include <pthread.h>
  #include "adpthread_manager.h"
  #include "pt_trace.h"
  pthread_mutex_t trace_mutex= PTHREAD_MUTEX_INITIALIZER;
  ofstream clogf;
  int NSLAVES=0;


  void * mp_ptr = NULL;
  adpthread_manager * thread_manager= NULL;
  void* simple_thread(void * ptr);
  int __thread thread_data::id=-1;



DATA_SECTION
  init_int nobs
  init_int nslaves

  matrix Y(1,nslaves,1,nobs)
  matrix x(1,nslaves,1,nobs)

 LOCAL_CALCS
    double A = 2.0;
    double B = 4.0;
    random_number_generator rng(101);
    dvector err(1,nobs);
    for (int i = 1; i <= nslaves; i++)
    {
       x(i).fill_randu(rng);
       x(i) *= 100.0;
       Y(i) = A*x(i) + B;
       err.fill_randn(rng);
       Y(i) += 5.0*err;
    }
    NSLAVES = nslaves;
    /*
    if (1)
    {
       TTRACE(nobs,NSLAVES)
       TTRACE(A,B)
       TRACE(x)
       TRACE(Y)
       ad_exit(1);
    }
    */

PARAMETER_SECTION
  init_number a   
  init_number b   
  //matrix pred_Y(1,nslaves, 1,nobs)
  vector ff(1,nslaves)
  objective_function_value f

PRELIMINARY_CALCS_SECTION
  TRACE(x)
  TRACE(Y)
  a = 1.0;
  b = 2.0;
  mp_ptr = (void*)this;
  TTRACE(mp_ptr,((void*)this));
  TRACE(NSLAVES)

  thread_manager = new adpthread_manager(NSLAVES,50000);
  thread_data* data1 = new thread_data[NSLAVES+1];
  data1 --;
  // initialize data to pass to thread 1
  for (int i=1;i<=NSLAVES;i++)
  {
    data1[i].thread_no = i;
    TTRACE(i,data1[i].thread_no)
  }
  thread_manager->create_all(&simple_thread,data1);


PROCEDURE_SECTION
  //thread_manager->initialize();
  thread_manager->reset();
  /*
  for (int i=1;i<=NSLAVES;i++)
  {
      pthread_mutex_ulock(smutex+i);
      TTTRACE(i,mflag[i],sflag[i])
      mflag[i] = 0;
      sflag[i] = 0;
      TTTRACE(i,mflag[i],sflag[i])
      pthread_cond_broadcast(scondition[i])
      pthread_cond_broadcast(mcondition[i])
      pthread_mutex_unlock(smutex+i);
  }
  */
  for (int i=1;i<=NSLAVES;i++)
  {
      ff(i) = thread_manager->get_dvariable_from_slave(i);
      TTRACE(i,ff(i))
  }
  f = sum(ff);
  TRACE(f)

TOP_OF_MAIN_SECTION
  adstring logname("mymsimple.log");
  clogf.open(logname);
  if ( !clogf ) 
  {
    cerr << "Cannot open file " << logname << endl;
    ad_exit(1);
  }
  cout << "Opened " << logname << endl;
  

FINAL_SECTION
  HERE
  thread_manager -> pthread_join_all();

  clogf.close(); 
