#include <admodel.h>
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */

#include "adpthread_manager.h"

//extern int NSLAVES;

/* prototype for thread routine */
void admb_thread(void * ptr);
adpthread_manager * test_thread_manager=0;

void add_slave_suffix(const adstring& _tmpstring)
{
  ADUNCONST(adstring,tmpstring)
  if (test_thread_manager)
  {
    if (thread_data::id>0)
    {
      tmpstring += "_";
      tmpstring += str(thread_data::id);
       cout << "In slave " << tmpstring << endl;
    }
    else
    {
      tmpstring += "_master";
       cout << "In master " << tmpstring << endl;
    }
  }
}

int __thread thread_data::id=-1;

extern "C"  {
  void ad_boundf(int i)
  {
    // so we can stop here
    exit(i);
  }
}

const int m=150;
const int m2=m*m;

int main3()
{
  ad_exit=&ad_boundf;
  test_thread_manager=new adpthread_manager(NSLAVES,200000);
  int i;

  thread_data data1[NSLAVES+1];         /* structs to be passed to threads */
  /* initialize data to pass to thread 1 */
  for (i=1;i<=NSLAVES;i++)
  {
    data1[i].thread_no=i;
  }

  test_thread_manager->create_all(&admb_thread,data1);
  const int n=NSLAVES;
  {
    gradient_structure::set_MAX_NVAR_OFFSET(30000);
    //gradient_structure::set_ARRAY_MEMBLOCK_SIZE(20000);
    //gradient_structure::set_GRADSTACK_BUFFER_SIZE(200);
    gradient_structure gs(2000000);
    independent_variables x(1,m2);
    random_number_generator rng(101);
    x.fill_randn(rng);
    adtimer adt;
    dvar_vector vx=dvar_vector(x);
    //int offset=0;
    for (int kk=1;kk<=n;kk++)
    {
      //dvar_vector u=vx(1+offset,m2+offset).shift(1);
      //offset+=m2;
      test_thread_manager->send_dvar_vector_to_slave(vx,kk);
    }
    dvar_vector yy(1,n);
    for (int kk=1;kk<=n;kk++)
    {
      yy(kk)=test_thread_manager->get_dvariable_from_slave(kk);
    }
   
    dvariable f=sum(yy);
  
    ofstream ofs1("zzz");
  
    dvector g(1,m2);
    ofs1<<" f = " << f<<endl;
    gradcalc(m2,g);
  
    ofs1<<g<<endl;
    cout << adt.get_elapsed_time_and_reset()<<endl; 
  
  }
  test_thread_manager->pthread_join_all();
  return 0;
}

void admb_thread(void * ptr)
{
  thread_data * tptr = (thread_data *) ptr;
  thread_data::id=tptr->thread_no;
  int sno=tptr->thread_no;
  {
    gradient_structure::set_MAX_NVAR_OFFSET(10000);
    gradient_structure::set_GRADSTACK_BUFFER_SIZE(20000000);
    gradient_structure::set_CMPDIF_BUFFER_SIZE(20000000);
    gradient_structure::set_MAX_NVAR_OFFSET(10000);
    //gradient_structure::set_ARRAY_MEMBLOCK_SIZE(20000);
    gradient_structure gs(1000000);
    dvar_vector v= test_thread_manager->get_dvar_vector_from_master(sno);
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
  
    test_thread_manager->send_dvariable_to_master(z,sno);
    slave_gradcalc();
  }
}
