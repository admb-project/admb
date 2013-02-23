//$Id: $

GLOBALS_SECTION
  #include <pthread.h>
  #include "adpthread_manager.h"
  #include "pt_trace.h"
  pthread_mutex_t trace_mutex= PTHREAD_MUTEX_INITIALIZER;
  ofstream clogf;
  const int NSLAVES=24;


  void * mp_ptr = NULL;
  adpthread_manager * nst_thread_manager= NULL;
  void* admb_thread(void * ptr);
  int __thread thread_data::id=-1;

  adtimer adt;

DATA_SECTION
  init_int m
  int m2
  int n
  vector x
 LOCAL_CALCS
   m2 = m*m;
   n = NSLAVES;
   TTTRACE(m,m2,NSLAVES)
   x.allocate(1,m2);
   TTRACE(x.indexmin(),x.indexmax())
   random_number_generator rng(101);
   x.fill_randn(rng);
   TRACE(x)


PARAMETER_SECTION
  init_vector vx(1,m2)
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
  vx = dvar_vector(x); 

PROCEDURE_SECTION
  double cf=0.0;
  int nloop=3;
  { 
    dvector g(1,m2);
    for (int ii = 1; ii <= nloop; ii++)
    {
      for (int kk=1;kk<=n;kk++)
      {
        TTRACE(kk,vx)
        nst_thread_manager->send_double_to_slave(1.0,kk);
        nst_thread_manager->send_dvar_vector_to_slave(vx,kk);
      }
       
      for (int kk=1;kk<=n;kk++)
      {
        yy(kk)=nst_thread_manager->get_dvariable_from_slave(kk);
      }
       
      f=sum(yy);
      TRACE(f)
    
      cf = value(f);
  
      gradcalc(m2,g);
    }
    ofstream ofs1("zzz-nst");
    ofs1<<" f = " << cf<<endl;
    ofs1<<g<<endl;
    cout << adt.get_elapsed_time_and_reset()<<endl; 
 
  }
  for (int kk=1;kk<=n;kk++)
  {
    nst_thread_manager->send_double_to_slave(0.0,kk);
  }
  nst_thread_manager->pthread_join_all();

  if (1)
    exit(0);
 

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
  gradient_structure::set_MAX_NVAR_OFFSET(30000);
 
FINAL_SECTION

  clogf.close(); 
