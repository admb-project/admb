//$Id: $

#include "pt_trace.h"

#include <admodel.h>
#include "adpthread_manager.h"
#include "nst.htp"

extern adpthread_manager * nst_thread_manager;
extern void * mp_ptr; 
 

void admb_thread(void * ptr)
{
  thread_data * tptr = (thread_data *) ptr;
  thread_data::id=tptr->thread_no;
  int sno=tptr->thread_no;
  {
    gradient_structure::set_MAX_NVAR_OFFSET(10000);
    gradient_structure::set_GRADSTACK_BUFFER_SIZE(100000000);
    gradient_structure::set_CMPDIF_BUFFER_SIZE   (100000000);
    //gradient_structure::set_MAX_NVAR_OFFSET(10000);
    gradient_structure gs(2000000);
 
    dvar_vector v= nst_thread_manager->get_dvar_vector_from_master(sno);
    int mmin=v.indexmin();
    int mmax=v.indexmax();
    model_parameters * mp = (model_parameters*)mp_ptr;
    const int m = mp->m;
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
  
    nst_thread_manager->send_dvariable_to_master(z,sno);
    slave_gradcalc();
  }
}

