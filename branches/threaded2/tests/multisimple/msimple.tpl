//$Id: msimple.tpl 3054M 2013-01-11 20:23:43Z (local) $

GLOBALS_SECTION
  #include <pthread.h>
  #include <fvar.hpp>
  #include <adthread.h>
  //#include "pt_trace.h"
  pthread_mutex_t trace_mutex= PTHREAD_MUTEX_INITIALIZER;
  ofstream clogf;


  void * mp_ptr = NULL;
  void* simple_thread(void * ptr);

DATA_SECTION
  init_int nobs
  init_int nrow
  matrix Y(1,nrow,1,nobs)
  matrix x(1,nrow,1,nobs)
  number A
  number B

 LOCAL_CALCS
    //TTRACE(nobs,nrow)
    A = 2.0;
    B = 4.0;
    random_number_generator rng(101);
    dvector err(1,nobs);
    for (int i = 1; i <= nrow; i++)
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
       TTRACE(nobs,nrow)
       TTRACE(A,B)
       TRACE(x)
       TRACE(Y)
       ad_exit(1);
    }
    */

PARAMETER_SECTION
  init_number a   
  init_number b   
  //matrix pred_Y(1,nrow, 1,nobs)
  vector ff(1,nrow)
  objective_function_value f

PRELIMINARY_CALCS_SECTION
  //TRACE(x)
  //TRACE(Y)
  a = 1.0;
  b = 2.0;
  mp_ptr = (void*)this;
  //TTRACE(mp_ptr,((void*)this));

  int ngroups=1;
  ivector ng(1,ngroups);
  ng(1)=nrow;

  ad_comm::pthread_manager = new adpthread_manager(ngroups,ng,500);
  new_thread_data* data1 = new new_thread_data[nrow+1];
  // initialize data to pass to thread 1
  for (int i=1;i<=nrow;i++)
  {
    data1[i].thread_no = i;
    data1[i].m=0;
  }

  ad_comm::pthread_manager->attach_code(&simple_thread);

  pthread_mutex_lock(&ad_comm::pthread_manager->start_mutex);
  ad_comm::pthread_manager->create_all(data1);
  ad_comm::pthread_manager->set_old_buffer_flag(0);
  
  pthread_mutex_unlock(&ad_comm::pthread_manager->start_mutex);



PROCEDURE_SECTION
  for (int kk=1;kk<=nrow;kk++)
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

  for (int kk=1;kk<=nrow;kk++)
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

REPORT_SECTION
  //TTRACE(a,b)
  report << "A = " << A << "; B = " << B <<endl;
  report << "a = " << a << "; b = " << b <<endl;

FINAL_SECTION
  //TTRACE(a,b)
  for (int k = 1; k <= nrow;k++)
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
