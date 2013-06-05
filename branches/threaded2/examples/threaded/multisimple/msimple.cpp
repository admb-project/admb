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
#include <admodel.h>
#include <contrib.h>

  extern "C"  {
    void ad_boundf(int i);
  }
#include <msimple.htp>

model_data::model_data(int argc,char * argv[]) : ad_comm(argc,argv)
{
  nobs.allocate("nobs");
 nslaves = NSLAVES;
  Y.allocate(1,nslaves,1,nobs);
  x.allocate(1,nslaves,1,nobs);
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
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 model_data(argc,argv) , function_minimizer(sz)
{
  initializationfunction();
  a.allocate("a");
  b.allocate("b");
  ff.allocate(1,nslaves,"ff");
  #ifndef NO_AD_INITIALIZE
    ff.initialize();
  #endif
  f.allocate("f");
  prior_function_value.allocate("prior_function_value");
  likelihood_function_value.allocate("likelihood_function_value");
}

void model_parameters::preliminary_calculations(void)
{

  admaster_slave_variable_interface(*this);
  //TRACE(x)
  //TRACE(Y)
  a = 1.0;
  b = 2.0;
  mp_ptr = (void*)this;
  //TTRACE(mp_ptr,((void*)this));
  //TRACE(NSLAVES)
  pthread_mutex_unlock(&ad_comm::pthread_manager->start_mutex);
}

void model_parameters::userfunction(void)
{
  f =0.0;
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
}

void model_parameters::report()
{
 adstring ad_tmp=initial_params::get_reportfile_name();
  ofstream report((char*)(adprogram_name + ad_tmp));
  if (!report)
  {
    cerr << "error trying to open report file"  << adprogram_name << ".rep";
    return;
  }
  //TTRACE(a,b)
  report << "A = " << A << "; B = " << B <<endl;
  report << "a = " << a << "; b = " << b <<endl;
}

void model_parameters::final_calcs()
{
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
}

model_data::~model_data()
{}

model_parameters::~model_parameters()
{}

void model_parameters::set_runtime(void){}

#ifdef _BORLANDC_
  extern unsigned _stklen=10000U;
#endif


#ifdef __ZTC__
  extern unsigned int _stack=10000U;
#endif

  long int arrmblsize=0;

int main(int argc,char * argv[])
{
    ad_set_new_handler();
  ad_exit=&ad_boundf;
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
  
    gradient_structure::set_NO_DERIVATIVES();
    gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
    if (!arrmblsize) arrmblsize=15000000;
    model_parameters mp(arrmblsize,argc,argv);
    mp.iprint=10;
    mp.preliminary_calculations();
    mp.computations(argc,argv);
    return 0;
}

extern "C"  {
  void ad_boundf(int i)
  {
    /* so we can stop here */
    exit(i);
  }
}
