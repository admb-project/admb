  #include <admodel.h>
  #include "adthread.h"
 int M=10;
  void admb_thread_1(void * ptr)
  {
    pthread_mutex_lock(&ad_comm::pthread_manager->start_mutex);
    pthread_mutex_unlock(&ad_comm::pthread_manager->start_mutex);
    new_thread_data * tptr = (new_thread_data *) ptr;
    
    int m=tptr->m;
    int sno=tptr->thread_no;
    {
      gradient_structure::set_MAX_NVAR_OFFSET(10000);
      gradient_structure::set_GRADSTACK_BUFFER_SIZE(20000000);
      gradient_structure::set_CMPDIF_BUFFER_SIZE(20000000);
      gradient_structure::set_MAX_NVAR_OFFSET(10000);
      //gradient_structure::set_ARRAY_MEMBLOCK_SIZE(20000);
      gradient_structure gs(1000000);
      ad_comm::pthread_manager->set_slave_number(tptr->thread_no);
      do
      {
        ad_comm::pthread_manager->read_lock_buffer(0);
        int lflag=ad_comm::pthread_manager->get_int(0);
        if (lflag==0.0) break;
        dvar_vector v= ad_comm::pthread_manager->get_dvar_vector(0);
        ad_comm::pthread_manager->read_unlock_buffer(0);
        //cout << "NNN " << norm2(value(v)) << endl;
        int mmin=v.indexmin();
        int mmax=v.indexmax();
        dvar_matrix M(1,m,1,m);
        int ii=0;
        for (int i=1;i<=m;i++)
        {
          for (int j=1;j<=m;j++)
          {
            M(i,j)=v(++ii);
          }
        }
        dvector u(1,m);
        u.fill_seqadd(sno,1.0/sno);
        
        dvariable z=0.0;
        for (int i=1;i<=50;i++)
        {
          z+=norm2(solve(M,u+double(i)));
        }
      
        // send to group 2 thread with the same offset
        int is=ad_comm::pthread_manager->gmin(2)+
          +ad_comm::pthread_manager->get_slave_number()-1;
        ad_comm::pthread_manager->write_lock_buffer(is);
        ad_comm::pthread_manager->send_int(1,is); 
        ad_comm::pthread_manager->send_dvariable(z,is); 
        ad_comm::pthread_manager->send_dvar_matrix(M,is); 
        ad_comm::pthread_manager->write_unlock_buffer(is);
        slave_gradcalc();
      }
      while(1);
    }
    pthread_exit(ptr);
  }
  void admb_thread_2(void * ptr)
  {
    pthread_mutex_lock(&ad_comm::pthread_manager->start_mutex);
    pthread_mutex_unlock(&ad_comm::pthread_manager->start_mutex);
    new_thread_data * tptr = (new_thread_data *) ptr;
    
    int m=tptr->m;
    int sno=tptr->thread_no;
    {
      gradient_structure::set_MAX_NVAR_OFFSET(10000);
      gradient_structure::set_GRADSTACK_BUFFER_SIZE(20000000);
      gradient_structure::set_CMPDIF_BUFFER_SIZE(20000000);
      gradient_structure::set_MAX_NVAR_OFFSET(10000);
      //gradient_structure::set_ARRAY_MEMBLOCK_SIZE(20000);
      gradient_structure gs(1000000);
      ad_comm::pthread_manager->set_slave_number(tptr->thread_no);
      do
      {
        // send to group 2 thread with the same offset
        int is=ad_comm::pthread_manager->get_slave_number()
          -ad_comm::pthread_manager->gmin(2)+1;
        ad_comm::pthread_manager->read_lock_buffer(is);
        int lflag=ad_comm::pthread_manager->get_int(is);
        if (lflag==0.0) break;
        dvariable z= ad_comm::pthread_manager->get_dvariable(is);
        dvar_matrix M = ad_comm::pthread_manager->get_dvar_matrix(is);
        ad_comm::pthread_manager->read_unlock_buffer(is);
        z+=norm2(M);
        // send to group 2 thread with the same offset
        ad_comm::pthread_manager->write_lock_buffer(0);
        ad_comm::pthread_manager->send_dvariable(z,0); 
        ad_comm::pthread_manager->write_unlock_buffer(0);
        slave_gradcalc();
      }
      while(1);
    }
    pthread_exit(ptr);
  }
#include <admodel.h>
#include <contrib.h>

  extern "C"  {
    void ad_boundf(int i);
  }
#include <newertpl.htp>

model_data::model_data(int argc,char * argv[]) : ad_comm(argc,argv)
{
  m=M;
  m2=m*m;
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 model_data(argc,argv) , function_minimizer(sz)
{
  initializationfunction();
  x.allocate(1,m2,"x");
  f.allocate("f");
  prior_function_value.allocate("prior_function_value");
  likelihood_function_value.allocate("likelihood_function_value");
  random_number_generator rng(101);
  dvector tmp(1,m2);
  tmp.fill_randn(rng);
  x=tmp;
}

void model_parameters::userfunction(void)
{
  f =0.0;
  double cf=0.0;
  int nloop=3;
  adtimer adt;
  int mmin=ad_comm::pthread_manager->gmin(1);
  int mmax=ad_comm::pthread_manager->gmax(1);
  for (int kk=mmin;kk<=mmax;kk++)
  {
    ad_comm::pthread_manager->write_lock_buffer(kk);
    ad_comm::pthread_manager->send_int(7,kk);
    ad_comm::pthread_manager->send_dvar_vector(x,kk);
    ad_comm::pthread_manager->write_unlock_buffer(kk);
  }
  mmin=ad_comm::pthread_manager->gmin(2);
  mmax=ad_comm::pthread_manager->gmax(2);
  dvar_vector yy(mmin,mmax);
  for (int kk=mmin;kk<=mmax;kk++)
  {
    ad_comm::pthread_manager->read_lock_buffer(kk);
    yy(kk)=ad_comm::pthread_manager->get_dvariable(kk);
    //cout << "TTT " << yy(kk) << endl;
    ad_comm::pthread_manager->read_unlock_buffer(kk);
  }
  f=sum(yy);
}

void model_parameters::preliminary_calculations(void)
{

  admaster_slave_variable_interface(*this);
  pthread_mutex_unlock(&ad_comm::pthread_manager->start_mutex);
}

void model_parameters::final_calcs()
{
  int mmin=ad_comm::pthread_manager->gmin(1);
  int mmax=ad_comm::pthread_manager->gmax(1);
  for (int kk=mmin;kk<=mmax;kk++)
  {
    ad_comm::pthread_manager->write_lock_buffer(kk);
    ad_comm::pthread_manager->send_int(0,kk);
    ad_comm::pthread_manager->write_unlock_buffer(kk);
  }
  sleep(1);
  delete ad_comm::pthread_manager;
  ad_comm::pthread_manager=0;
}

model_data::~model_data()
{}

model_parameters::~model_parameters()
{}

void model_parameters::report(void){}

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
  int ngroups=2;
  ivector ng(1,ngroups);
  ng(1)=1;
  if (ngroups>1)
  {
    ng(2)=1;
  }
  ad_comm::pthread_manager = new adpthread_manager(ngroups,ng,500);
  int NSLAVES=sum(ng);
  new_thread_data* data1 = new new_thread_data[NSLAVES+1];
  // initialize data to pass to thread 1
  for (int i=1;i<=NSLAVES;i++)
  {
    data1[i].thread_no = i;
    data1[i].m=M;
  }
  ad_comm::pthread_manager->attach_code(&admb_thread_1);
  if (ngroups>1)
  {
    ad_comm::pthread_manager->attach_code(&admb_thread_2);
  }
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
