//$Id: $

#include "pt_trace.h"

#include <admodel.h>
//#include "adpthread_manager.h"
#include "adthread.h"
#include "nst.htp"

extern adpthread_manager * test_thread_manager;
extern void * mp_ptr; 
extern pthread_mutex_t mp_ptr_mutex;
extern pthread_cond_t mp_ptr_cond;
  
__ADMBTHREAD__ int  adpthread_manager::slave_number=0;


void admb_thread(void * ptr)
{
  pthread_mutex_lock(&mp_ptr_mutex);
  while (mp_ptr == NULL) pthread_cond_wait(&mp_ptr_cond, &mp_ptr_mutex);
  pthread_mutex_unlock(&mp_ptr_mutex);
  thread_data * tptr = (thread_data *) ptr;
  thread_data::id=tptr->thread_no;
  int sno=tptr->thread_no;
  cout << "TT sno " << sno << endl;
  adpthread_manager::set_slave_number(sno);
  cout << "XX slavenumber = " << adpthread_manager::get_slave_number()
   << endl;
  pthread_mutex_unlock(&test_thread_manager->smutex[sno]);
  model_parameters * mp = (model_parameters*)mp_ptr;
  const int m = mp->m;
  TTRACE(sno,m)
  {
    //arrmblsize = 35000000;
    gradient_structure::set_MAX_NVAR_OFFSET(10000);
    gradient_structure::set_GRADSTACK_BUFFER_SIZE(200);
    gradient_structure::set_CMPDIF_BUFFER_SIZE(2000);
    gradient_structure::set_MAX_NVAR_OFFSET(30000);
    gradient_structure gs(1000000);
    do
    {
      test_thread_manager->read_lock_buffer_slave(sno); 
      test_thread_manager->verify_id_string_from_master_nl("abcx",sno); 
      double lflag = test_thread_manager->get_double_from_master_nl(sno); 
      //cout << "IN thread " << sno << " read " << lflag << endl;
      if (lflag == 0.0) break;
      dvar_vector v= test_thread_manager->get_dvar_vector_from_master(sno);
      dvector w= test_thread_manager->get_dvector_from_master(sno);
      //cout << w << endl;
      test_thread_manager->read_unlock_buffer_slave(sno); 
      int mmin=v.indexmin();
      int mmax=v.indexmax();
      TTRACE(mmin,mmax)
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
      TTRACE(sno,sum(u))
   
      dvariable z=0.0;
      for (int i=1;i<=20;i++)
      {
        z+=norm2(solve(M,u+double(i)));
      }
 
      test_thread_manager->write_lock_buffer_slave(sno); 
      test_thread_manager->send_id_string_to_master_nl("X1",sno);
      test_thread_manager->send_dvariable_to_master(z,sno);
      test_thread_manager->write_unlock_buffer_slave(sno); 
      slave_gradcalc();
    }
    while(1);
  }
}

