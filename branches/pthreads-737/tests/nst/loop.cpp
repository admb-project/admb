
#include <admodel.h>
#include "adthread.h"

 int __thread thread_data::id;

extern "C"  {
  void ad_boundf(int i)
  {
    // so we can stop here
    exit(i);
  }
}

const int m=150;
const int m2=m*m;

int main()
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
  double cf=0.0;
  int nloop=3;
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
    dvector g(1,m2);
    for (int ii=1;ii<=nloop;ii++)
    {
      dvar_vector vx=dvar_vector(x);
      //int offset=0;
      for (int kk=1;kk<=n;kk++)
      {
        //dvar_vector u=vx(1+offset,m2+offset).shift(1);
        //offset+=m2;
        test_thread_manager->send_double_to_slave(1.0,kk);
        test_thread_manager->send_dvar_vector_to_slave(vx,kk);
      }
      dvar_vector yy(1,n);
      for (int kk=1;kk<=n;kk++)
      {
        yy(kk)=test_thread_manager->get_dvariable_from_slave(kk);
      }
     
      dvariable f=sum(yy);
      cf=value(f);
    
    
      gradcalc(m2,g);
    
    } 
    ofstream ofs1("zzz");
    ofs1<<" f = " << cf<<endl;
    ofs1<<g<<endl;
    cout << adt.get_elapsed_time_and_reset()<<endl; 
  }
  for (int kk=1;kk<=n;kk++)
  {
    test_thread_manager->send_double_to_slave(0.0,kk);
  }
  test_thread_manager->pthread_join_all();
  exit(0);
} /* main() */

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
    do
    {
      double lflag=test_thread_manager->get_double_from_master(sno);
      if (lflag==0.0) break;
      cout << "lflag = " << lflag << " in thread " << sno << endl;
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
    while(1);
  }
}

