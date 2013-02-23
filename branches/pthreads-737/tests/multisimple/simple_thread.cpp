//$Id: simple_thread.cpp 3054 2013-01-10 22:54:36Z jsibert $
#include "pt_trace.h"
#include <admodel.h>
#include "adpthread_manager.h"
#include "msimple.htp"
extern adpthread_manager * thread_manager;
extern void * mp_ptr; 
extern  pthread_mutex_t trace_mutex;
static int nentries = 0;
 
void* simple_thread(void * ptr)
{
   nentries ++;
   thread_data * tptr = (thread_data *) ptr;
   thread_data::id=tptr->thread_no;
   const int sno=tptr->thread_no;
   model_parameters * mp = (model_parameters*)mp_ptr;
   TTTRACE(nentries,sno, ((void*)mp))

   gradient_structure::set_MAX_NVAR_OFFSET(200);
   gradient_structure::set_GRADSTACK_BUFFER_SIZE(2200);
   gradient_structure::set_CMPDIF_BUFFER_SIZE   (32000L);
   gradient_structure gs;//(2000000);

//PROCEDURE_SECTION
  //pred_Y=a*x+b;
  //f=(norm2(pred_Y-Y)); 
  //f=nobs/2.*log(f);    // make it a likelihood function so that
                         // covariance matrix is correct
   TTTRACE(sno,mp->a, mp->b)
   TTTRACE(sno,mp->x(sno).indexmin(),mp->x(sno).indexmax());
   TTRACE(sno,mp->x(sno))

   dvar_vector pred_Y(mp->x(sno).indexmin(),mp->x(sno).indexmax());
   TTTRACE(sno,pred_Y.indexmin(),pred_Y.indexmax())
   pred_Y = mp->a * mp->x(sno) + mp-> b;
   TTTRACE(sno,pred_Y.indexmin(),pred_Y.indexmax());
   TTRACE(sno,pred_Y);

   dvariable f=norm2(pred_Y-mp->Y(sno)); 
   f=mp->nobs/2.*log(f);    // make it a likelihood function so that
                            // covariance matrix is correct
   TTRACE(sno,f)

   thread_manager->send_dvariable_to_master(f, sno);
   slave_gradcalc();
   return;
}
  
