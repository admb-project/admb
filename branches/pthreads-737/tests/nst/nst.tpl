//$Id: $

GLOBALS_SECTION
  #include <admodel.h>
  #include "adthread.h"

  int __thread thread_data::id;
  void admb_thread(void * ptr);

  #include "pt_trace.h"
  pthread_mutex_t trace_mutex=PTHREAD_MUTEX_INITIALIZER;

  pthread_mutex_t mp_ptr_mutex;
  pthread_cond_t mp_ptr_cond;
  ofstream clogf;

  void * mp_ptr = NULL;
  int NSLAVES=10;


DATA_SECTION
  int m
  int m2
  int n
  vector x
  //int NSLAVES
 LOCAL_CALCS
   m=25;
   m2 = m*m;
   //NSLAVES=2;
   n = NSLAVES;
   TTTRACE(m,m2,NSLAVES)
   x.allocate(1,m2);
   TTRACE(x.indexmin(),x.indexmax())
   random_number_generator rng(101);
   x.fill_randn(rng);


PARAMETER_SECTION
  init_vector vx(1,m2)
  objective_function_value f
  vector yy(1,NSLAVES)

PRELIMINARY_CALCS_SECTION
  TTTRACE(m,m2,n)
  TTRACE(mp_ptr,((void*)this));
  pthread_mutex_lock(&mp_ptr_mutex);
  mp_ptr = (void*)this;
  pthread_mutex_unlock(&mp_ptr_mutex);
  pthread_cond_broadcast(&mp_ptr_cond);
  TTRACE(mp_ptr,((void*)this));
  /*
  for (int i = 1; i <= NSLAVES; i++)
  {
    pthread_mutex_unlock(&test_thread_manager->smutex[i]);
    pthread_cond_signal(&test_thread_manager->scondition[i]);
  }
  */
  TRACE(NSLAVES)
  vx = dvar_vector(x); 

PROCEDURE_SECTION
  double cf=0.0;
  int nloop=3;
  adtimer adt;
  dvector w(1,5);
  w.fill_seqadd(1.5,1.5);
  for (int kk=1;kk<=n;kk++)
  {
     test_thread_manager->write_lock_buffer_master(kk);
     test_thread_manager->send_id_string_to_slave_nl("abcx",kk);
     test_thread_manager->send_double_to_slave_nl(2.4,kk);
     test_thread_manager->send_dvar_vector_to_slave(vx,kk);

     test_thread_manager->send_dvector_to_slave(w,kk);

     test_thread_manager->write_unlock_buffer_master(kk);
  }
       
  for (int kk=1;kk<=n;kk++)
  {
    test_thread_manager->read_lock_buffer_master(kk);
    test_thread_manager->verify_id_string_from_slave_nl("X1",kk); 
    yy(kk)=test_thread_manager->get_dvariable_from_slave(kk);
    test_thread_manager->read_unlock_buffer_master(kk);
  }
       
  f=sum(yy);
 

TOP_OF_MAIN_SECTION
  add_slave_suffix("xxx");
  adstring logname("nstlog.log");
  clogf.open(logname);
  if ( !clogf ) 
  {
    cerr << "Cannot open file " << logname << endl;
    ad_exit(1);
  }
  cout << "Opened " << logname << endl;


  //           33681152
  arrmblsize = 35000000;
  //gradient_structure::set_MAX_NVAR_OFFSET(30000);

  test_thread_manager = new adpthread_manager(NSLAVES,500000);
  ad_comm::pthread_manager=test_thread_manager;

  thread_data* data1 = new thread_data[NSLAVES+1];
  // initialize data to pass to thread 1
  for (int i=1;i<=NSLAVES;i++)
  {
    data1[i].thread_no = i;
    TTRACE(i,data1[i].thread_no)
  }
  test_thread_manager->create_all(&admb_thread,data1);
 
FINAL_SECTION

  clogf.close(); 
