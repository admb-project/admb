//$Id: $

GLOBALS_SECTION
  #include <pthread.h>
  #include "adpthread_manager.h"
  #include "pt_trace.h"
  pthread_mutex_t trace_mutex= PTHREAD_MUTEX_INITIALIZER;
  ofstream clogf;
  const int NSLAVES=16;


  void * mp_ptr = NULL;
  adpthread_manager * nst_thread_manager= NULL;
  void* admb_thread(void * ptr);
  int __thread thread_data::id=-1;


DATA_SECTION
  init_int m
  int m2
  int n
 LOCAL_CALCS
   m2 = m*m;
   n = NSLAVES;
   TTTRACE(m,m2,NSLAVES)


PARAMETER_SECTION
  init_vector x(1,m2)
  vector vx(1,m2)
  objective_function_value f
  vector yy(1,NSLAVES)

PRELIMINARY_CALCS_SECTION
  TTTRACE(m,m2,n)
  TTRACE(mp_ptr,((void*)this));
  mp_ptr = (void*)this;
  TTRACE(mp_ptr,((void*)this));
  TRACE(NSLAVES)
  nst_thread_manager = new adpthread_manager(NSLAVES,50000);
  thread_data* data1 = new thread_data[NSLAVES+1];
  data1 --;
  // initialize data to pass to thread 1
  for (int i=1;i<=NSLAVES;i++)
  {
    data1[i].thread_no = i;
    TTRACE(i,data1[i].thread_no)
  }
  //const int n=NSLAVES;
  nst_thread_manager->create_all(&admb_thread,data1);
 
  TTRACE(x.indexmin(),x.indexmax())

  dvector tx(1,m2);
  random_number_generator rng(101);
  tx.fill_randn(rng);
  x = tx;
  TRACE(x)

PROCEDURE_SECTION
  vx = x;
  for (int kk=1;kk<=n;kk++)
  {
    TTRACE(kk,vx)
    nst_thread_manager->send_dvar_vector_to_slave(vx,kk);
  }
     
    
  for (int kk=1;kk<=n;kk++)
  {
    yy(kk)=nst_thread_manager->get_dvariable_from_slave(kk);
  }
   
  f=sum(yy);
  TRACE(f)
  
  ofstream ofs1("zzz-nst");
  ofs1<<" f = " << f<<endl;
 
  //dvector g(1,m2);
  //gradcalc(m2,g);
  //ofs1<<g<<endl;

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
  gradient_structure::set_MAX_NVAR_OFFSET(10000);
 
FINAL_SECTION
  nst_thread_manager -> pthread_join_all();

  clogf.close(); 
