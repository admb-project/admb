//$Id: msimple.tpl 3054M 2013-01-11 20:23:43Z (local) $

GLOBALS_SECTION
  #include <pthread.h>
  #include <fvar.hpp>
  #include <adthread.h>
  //#include "pt_trace.h"
  pthread_mutex_t trace_mutex= PTHREAD_MUTEX_INITIALIZER;
  ofstream clogf;

  int NSLAVES = 7;

  void * mp_ptr = NULL;
  //adpthread_manager * ad_comm::pthread_manager= NULL;
  void* simple_thread(void * ptr);
  //int __thread thread_data::id=-1;



DATA_SECTION
  init_int nobs
  int nslaves
  !! nslaves = NSLAVES;
  matrix Y(1,nslaves,1,nobs)
  matrix x(1,nslaves,1,nobs)
  number A
  number B

 LOCAL_CALCS
    //TTRACE(nobs,nslaves)
    A = 2.0;
    B = 4.0;
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
  //TRACE(x)
  //TRACE(Y)
  a = 1.0;
  b = 2.0;
  mp_ptr = (void*)this;
  //TTRACE(mp_ptr,((void*)this));
  //TRACE(NSLAVES)


  pthread_mutex_unlock(&ad_comm::pthread_manager->start_mutex);



PROCEDURE_SECTION
  for (int kk=1;kk<=NSLAVES;kk++)
  {
     ad_comm::pthread_manager->cwrite_lock_buffer(kk);
     ad_comm::pthread_manager->send_int(1,kk); 
     ad_comm::pthread_manager->cwrite_unlock_buffer(kk);
     ad_comm::pthread_manager->write_lock_buffer(kk);
     ad_comm::pthread_manager->send_dvariable(a,kk); 
     ad_comm::pthread_manager->send_dvariable(b,kk); 
     ad_comm::pthread_manager->write_unlock_buffer(kk);
     //TTRACE(kk,sum(x(kk)))
  
  }

  for (int kk=1;kk<=NSLAVES;kk++)
  {
      //TRACE(kk)
      ad_comm::pthread_manager->read_lock_buffer(kk);
      ff(kk) = ad_comm::pthread_manager->get_dvariable(kk);
      ad_comm::pthread_manager->read_unlock_buffer(kk);
      //TTRACE(kk,ff(kk))
  }
  f = sum(ff);
  //TRACE(f)

TOP_OF_MAIN_SECTION
  adstring logname("mymsimple.log");
  clogf.open(logname);
  if ( !clogf ) 
  {
    cerr << "Cannot open file " << logname << endl;
    ad_exit(1);
  }
  cout << "Opened " << logname << endl;

  int ngroups=1;
  ivector ng(1,ngroups);
  ng(1)=NSLAVES;
  //TTRACE(NSLAVES,sum(ng))

  ad_comm::pthread_manager = new adpthread_manager(ngroups,ng,500);
  new_thread_data* data1 = new new_thread_data[NSLAVES+1];
  // initialize data to pass to thread 1
  for (int i=1;i<=NSLAVES;i++)
  {
    data1[i].thread_no = i;
    data1[i].m=0;
  }

  ad_comm::pthread_manager->attach_code(&simple_thread);

  pthread_mutex_lock(&ad_comm::pthread_manager->start_mutex);
  ad_comm::pthread_manager->create_all(data1);
  ad_comm::pthread_manager->set_old_buffer_flag(0);
  
REPORT_SECTION
  //TTRACE(a,b)
  report << "A = " << A << "; B = " << B <<endl;
  report << "a = " << a << "; b = " << b <<endl;

FINAL_SECTION
  //TTRACE(a,b)
  //TRACE(NSLAVES)
  for (int k = 1; k <= NSLAVES;k++)
  {
    ad_comm::pthread_manager->write_lock_buffer(k);
    ad_comm::pthread_manager->send_int(0,k);
    ad_comm::pthread_manager->write_unlock_buffer(k);
  }
  sleep(1);
  delete ad_comm::pthread_manager;
  ad_comm::pthread_manager=0;
  HERE

  clogf.close(); 
