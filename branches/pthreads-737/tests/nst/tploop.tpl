DATA_SECTION
  int m
  int m2
  int NSLAVES
 LOC_CALCS
  m=150;
  m2=m*m;
  NSLAVES=24;
PARAMETER_SECTION
  init_vector x(1,m2)
  objective_function_value f
 LOC_CALCS
  random_number_generator rng(101);
  dvector tmp(1,m2);
  tmp.fill_randn(rng);
  x=tmp;

PROCEDURE_SECTION

  double cf=0.0;
  int nloop=3;
  adtimer adt;
  for (int kk=1;kk<=NSLAVES;kk++)
  {
    test_thread_manager->send_double_to_slave(1.0,kk);
    test_thread_manager->send_dvar_vector_to_slave(x,kk);
  }
  dvar_vector yy(1,NSLAVES);
  for (int kk=1;kk<=NSLAVES;kk++)
  {
    yy(kk)=test_thread_manager->get_dvariable_from_slave(kk);
  }
     
  f=sum(yy);
  

GLOBALS_SECTION
  #include <admodel.h>
  #include "adthread.h"

 int __thread thread_data::id;

  void admb_thread(void * ptr)
  {
    int m=150;
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



TOP_OF_MAIN_SECTION
  test_thread_manager=new adpthread_manager(NSLAVES,200000);
  int i;

  thread_data data1[NSLAVES+1];         /* structs to be passed to threads */
  /* initialize data to pass to thread 1 */
  for (i=1;i<=NSLAVES;i++)
  {
    data1[i].thread_no=i;
  }

  test_thread_manager->create_all(&admb_thread,data1);
  //test_thread_manager->pthread_join_all();

  
