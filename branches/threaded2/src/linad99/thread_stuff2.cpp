#include <admodel.h>
#include <cstddef>
#include "adthread.h"
#if !defined(OPT_LIB)
#  if !defined(CHK_ID_STRING)
#    define CHK_ID_STRING
#  endif
#endif

void adjoint_send_dvar_matrix_to_master(void)
{
  verify_identifier_string("YN");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_send_dvar_matrix_to_master();
}

void adpthread_manager::adjoint_send_dvar_matrix_to_master(void)
{
  verify_identifier_string("KH");
  int sno=restore_int_value();
  verify_identifier_string("OP");
  verify_id_string_from_master("OV",sno);
  int rmin;
  int rmax;
  readbuffer(&rmin,sizeof(int),sno);
  readbuffer(&rmax,sizeof(int),sno);
  dmatrix M(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int mmin,mmax;
    readbuffer(&mmin,sizeof(int),sno);
    readbuffer(&mmax,sizeof(int),sno);
    M(i).allocate(mmin,mmax);
    int sz=mmax-mmin+1;
    readbuffer(&(M(i)(mmin)),sz*sizeof(double),sno);
  }
  dvar_matrix_position dmpos=restore_dvar_matrix_position();
  verify_identifier_string("Y2");
  M.save_dmatrix_derivatives(dmpos);
}

void adpthread_manager::send_dvar_matrix_to_master(const dvar_matrix &x,int sno)
{
  int rmin=x.indexmin();
  int rmax=x.indexmax();
  send_id_string_to_master("WTZ",sno);
  writebuffer(&rmin,sizeof(int),sno);
  writebuffer(&rmax,sizeof(int),sno);
  for (int i=rmin;i<=rmax;i++)
  {
    int mmin=x(i).indexmin();
    int mmax=x(i).indexmax();
    int sz=mmax-mmin+1;
    writebuffer(&mmin,sizeof(int),sno);
    writebuffer(&mmax,sizeof(int),sno);
    writebuffer(&(value(x(i)(mmin))),sz*sizeof(double),sno);
  }
  save_identifier_string("Y2");
  // !!! should we optimize this ?
  x.save_dvar_matrix_position();
  save_identifier_string("OP");
  save_int_value(sno);
  save_identifier_string("KH");
  save_pointer_value(this);
  save_identifier_string("YN");
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(::adjoint_send_dvar_matrix_to_master);
}

void adjoint_get_dvar_matrix_from_slave(void)
{
  verify_identifier_string("T4");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_get_dvar_matrix_from_slave();
}

void adpthread_manager::adjoint_get_dvar_matrix_from_slave(void)
{
  verify_identifier_string("K6");
  int sno=restore_int_value();
  verify_identifier_string("Y7");
  dvar_matrix_position dvpos=restore_dvar_matrix_position();
  verify_identifier_string("C2");
  dmatrix dv=restore_dvar_matrix_derivatives(dvpos);
  send_id_string_to_slave("OV",sno);
  int rmin=dv.indexmin();
  int rmax=dv.indexmax();
  writebuffer(&rmin,sizeof(int),sno);
  writebuffer(&rmax,sizeof(int),sno);
  for (int i=rmin;i<=rmax;i++)
  {
    int mmin=dv(i).indexmin();
    int mmax=dv(i).indexmax();
    int sz=mmax-mmin+1;
    writebuffer(&mmin,sizeof(int),sno);
    writebuffer(&mmax,sizeof(int),sno);
    writebuffer(&(dv(i)(mmin)),sz*sizeof(double),sno);
  }
}
dvar_matrix adpthread_manager::get_dvar_matrix_from_slave(int sno)
{
  verify_id_string_from_slave("WTZ",sno);
  int rmin;
  int rmax;
  readbuffer(&rmin,sizeof(int),sno);
  readbuffer(&rmax,sizeof(int),sno);
  dvar_matrix x(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int mmin;
    int mmax;
    readbuffer(&mmin,sizeof(int),sno);
    readbuffer(&mmax,sizeof(int),sno);
    int sz=mmax-mmin+1;
    x(i).allocate(mmin,mmax);
    readbuffer(&(value(x(i)(mmin))),sz*sizeof(double),sno);
  }
  save_identifier_string("C2");
  x.save_dvar_matrix_position();
  save_identifier_string("Y7");
  save_int_value(sno);
  save_identifier_string("K6");
  save_pointer_value(this);
  save_identifier_string("T4");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(::adjoint_get_dvar_matrix_from_slave);
  return x;
}

