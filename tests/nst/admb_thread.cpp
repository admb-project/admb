//$Id: $

#include "pt_trace.h"

#include <admodel.h>
//#include "adpthread_manager.h"
#include "adthread.h"
#include "nst.htp"

extern adpthread_manager * test_thread_manager;
extern void * mp_ptr; 
//extern pthread_mutex_t * smutex;
//extern pthread_cond_t * scondition; 

void admb_thread(void * ptr)
{
  thread_data * tptr = (thread_data *) ptr;
  thread_data::id=tptr->thread_no;
  int sno=tptr->thread_no;
  pthread_mutex_lock(&test_thread_manager->smutex[sno]);
  while (mp_ptr == NULL) pthread_cond_wait(&test_thread_manager->scondition[sno],
                                           &test_thread_manager->smutex[sno]);
  pthread_mutex_unlock(&test_thread_manager->smutex[sno]);
  model_parameters * mp = (model_parameters*)mp_ptr;
  const int m = mp->m;
  {
    //arrmblsize = 35000000;
 
    gradient_structure::set_MAX_NVAR_OFFSET(10000);
    gradient_structure::set_GRADSTACK_BUFFER_SIZE(20000000);
    gradient_structure::set_CMPDIF_BUFFER_SIZE(20000000);
    gradient_structure::set_MAX_NVAR_OFFSET(30000);
    gradient_structure gs(1000000);
    do
    {
       double lflag = test_thread_manager->get_double_from_master(sno); 
       if (lflag == 0.0) break;
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
       for (int i=1;i<=20;i++)
       {
         z+=norm2(solve(M,u+double(i)));
       }
  
       test_thread_manager->send_dvariable_to_master(z,sno);
       slave_gradcalc();
    }
    while(1);
  }
}

