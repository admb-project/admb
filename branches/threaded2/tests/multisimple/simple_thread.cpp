//$Id: simple_thread.cpp 3054 2013-01-10 22:54:36Z jsibert $
//#include "pt_trace.h"
#include <admodel.h>
#include <adthread.h>
#include "msimple.htp"
//extern adpthread_manager * thread_manager;
extern void * mp_ptr; 
//extern  pthread_mutex_t trace_mutex;
//static int nentries = 0;
 
void simple_thread(void * ptr)
{
   pthread_mutex_lock(&ad_comm::pthread_manager->start_mutex);
   pthread_mutex_unlock(&ad_comm::pthread_manager->start_mutex);
   new_thread_data * tptr = (new_thread_data *) ptr;

   model_parameters * mp = (model_parameters*)mp_ptr; 
   //TRACE((void*)mp)
   //TTTRACE(mp->a,mp->b,mp->nobs)

   //int m=tptr->m;
   int sno=tptr->thread_no;
   //TRACE(sno)
   { 
      gradient_structure::set_MAX_NVAR_OFFSET(10000);
      gradient_structure::set_GRADSTACK_BUFFER_SIZE(20000000);
      gradient_structure::set_CMPDIF_BUFFER_SIZE   (20000000);
      gradient_structure gs(10000000);
   
      ad_comm::pthread_manager->set_slave_number(tptr->thread_no);
      do
      {
         ad_comm::pthread_manager->cread_lock_buffer(0);
         int lflag=ad_comm::pthread_manager->get_int(0);
         ad_comm::pthread_manager->cread_unlock_buffer(0);
         //TRACE(lflag)
         if (lflag == 0) break;
         ad_comm::pthread_manager->read_lock_buffer(0);
         dvariable a =ad_comm::pthread_manager->get_dvariable(0);
         dvariable b =ad_comm::pthread_manager->get_dvariable(0);
         ad_comm::pthread_manager->read_unlock_buffer(0);

         dvar_vector pred_Y(mp->x(sno).indexmin(),mp->x(sno).indexmax());
   //PROCEDURE_SECTION
     //pred_Y=a*x+b;
     //f=(norm2(pred_Y-Y)); 
     //f=nobs/2.*log(f);    // make it a likelihood function so that
                            // covariance matrix is correct
         //TTRACE(sno,sum(mp->x(sno)))
         //pred_Y = mp->a * mp->x(sno) + mp-> b; // does not work
         pred_Y = a * mp->x(sno) +  b;
   
         dvariable f=norm2(pred_Y-mp->Y(sno)); 
         //TTRACE(sno,f)
         f=mp->nobs/2.*log(f);    // make it a likelihood function so that
                                  // covariance matrix is correct
   
         ad_comm::pthread_manager->write_lock_buffer(0);
         //TTRACE(sno,f)
         ad_comm::pthread_manager->send_dvariable_to_master(f, 0);
         ad_comm::pthread_manager->write_unlock_buffer(0);
   
         slave_gradcalc();
      }
      while (1);
   }
   pthread_exit(ptr);
}
  
