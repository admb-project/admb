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


DATA_SECTION
  int m
  int m2
  int n
  vector x
  int NSLAVES
 LOCAL_CALCS
   m=150;
   m2 = m*m;
   NSLAVES = 24;
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
  for (int kk=1;kk<=n;kk++)
  {
     TRACE(kk)
     test_thread_manager->send_double_to_slave(1.0,kk);
     test_thread_manager->send_dvar_vector_to_slave(vx,kk);
  }
       
  for (int kk=1;kk<=n;kk++)
  {
     TTRACE(kk,yy(kk))
     yy(kk)=test_thread_manager->get_dvariable_from_slave(kk);
     TTRACE(kk,yy(kk))
  }
       
  f=sum(yy);
 

TOP_OF_MAIN_SECTION
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
