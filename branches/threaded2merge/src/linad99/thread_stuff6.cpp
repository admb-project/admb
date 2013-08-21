
#include <admodel.h>
#include <cstddef>
#include "adthread.h"
#if !defined(OPT_LIB)
#  if !defined(CHK_ID_STRING)
#    define CHK_ID_STRING
#  endif
#endif

void adjoint_send_dvar4_array_to_slave(void)
{
  verify_identifier_string("CV");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_send_dvar4_array_to_slave();
}

void adpthread_manager::adjoint_send_dvar4_array_to_slave(void)
{
  verify_identifier_string("HH");
  int sno=restore_int_value();
  verify_id_string_from_slave("FDG",sno);
  int hsmin;
  int hsmax;
  readbuffer(&hsmin,sizeof(int),sno);
  readbuffer(&hsmax,sizeof(int),sno);
  d4_array M(hsmin,hsmax);
  int l;
  ivector smin(hsmin,hsmax);
  ivector smax(hsmin,hsmax);
  for (l=hsmin;l<=hsmax;l++)
  {
    readbuffer(&(smin(l)),sizeof(int),sno);
    readbuffer(&(smax(l)),sizeof(int),sno);
    M(l).allocate(smin(l),smax(l));
    for (int i=smin(l);i<=smax(l);i++)
    {
      int rmin,rmax;
      readbuffer(&rmin,sizeof(int),sno);
      readbuffer(&rmax,sizeof(int),sno);
      M(l,i).allocate(rmin,rmax);
      for (int j=rmin;j<=rmax;j++)
      { 
        int cmin,cmax;
        readbuffer(&cmin,sizeof(int),sno);
        readbuffer(&cmax,sizeof(int),sno);
        M(l,i,j).allocate(cmin,cmax);
        int sz=cmax-cmin+1;
        readbuffer(&(M(l,i,j)(cmin)),sz*sizeof(double),sno);
      }
    }
  }
  verify_identifier_string("OP");
  for (int l=hsmax;l>=hsmin;l--)
  {
    for (int i=smax(l);i>=smin(l);i--)
    {
      dvar_matrix_position dmpos=restore_dvar_matrix_position();
      M(l,i).save_dmatrix_derivatives(dmpos);
    }
  }
  verify_identifier_string("VC");
}

void adpthread_manager::send_dvar4_array_to_slave(const dvar4_array &x,int sno)
{
  send_id_string_to_slave("HYD",sno);
  int hsmin=x.indexmin();
  int hsmax=x.indexmax();
  writebuffer(&hsmin,sizeof(int),sno);
  writebuffer(&hsmax,sizeof(int),sno);
  int l;
  ivector smin(hsmin,hsmax);
  ivector smax(hsmin,hsmax);
  for (l=hsmin;l<=hsmax;l++)
  {
    smin(l)=x(l).indexmin();
    smax(l)=x(l).indexmax();
    int i;
    writebuffer(&(smin(l)),sizeof(int),sno);
    writebuffer(&(smax(l)),sizeof(int),sno);
    for (i=smin(l);i<=smax(l);i++)
    {
      int rmin=x(l,i).indexmin();
      int rmax=x(l,i).indexmax();
      writebuffer(&rmin,sizeof(int),sno);
      writebuffer(&rmax,sizeof(int),sno);
      for (int j=rmin;j<=rmax;j++)
      {
        int cmin=x(l,i,j).indexmin();
        int cmax=x(l,i,j).indexmax();
        writebuffer(&cmin,sizeof(int),sno);
        writebuffer(&cmax,sizeof(int),sno);
        int sz=cmax-cmin+1;
        writebuffer(&(value(x(l,i,j)(cmin))),sz*sizeof(double),sno);
      }
    }
  }

  save_identifier_string("VC");
  // !!! should we optimize this ?
  for (l=hsmin;l<=hsmax;l++)
  {
    for (int i=smin(l);i<=smax(l);i++)
    {
      x(l,i).save_dvar_matrix_position();
    }
  }
  save_identifier_string("OP");
  save_int_value(sno);
  save_identifier_string("HH");
  save_pointer_value(this);
  save_identifier_string("CV");
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(::adjoint_send_dvar4_array_to_slave);
}

void adjoint_get_dvar4_array_from_master(void)
{
  verify_identifier_string("I5");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_get_dvar4_array_from_master();
}

void adpthread_manager::adjoint_get_dvar4_array_from_master(void)
{
  verify_identifier_string("LG");
  int sno=restore_int_value();
  verify_identifier_string("W8");
  int hsmin=restore_int_value();
  int hsmax=restore_int_value();
  verify_identifier_string("Y8");
  int l;
  d4_array dv(hsmin,hsmax);
  ivector smin(hsmin,hsmax);
  ivector smax(hsmin,hsmax);
  for (l=hsmax;l>=hsmin;l--)
  {
    smin(l)=restore_int_value();
    smax(l)=restore_int_value();
    dv(l).allocate(smin(l),smax(l));
    for (int i=smax(l);i>=smin(l);i--)
    {
      dvar_matrix_position dvpos=restore_dvar_matrix_position();
      dv(l,i)=restore_dvar_matrix_derivatives(dvpos);
    }
  }
  verify_identifier_string("L2");
  send_id_string_to_master("FDG",sno);
  writebuffer(&hsmin,sizeof(int),sno);
  writebuffer(&hsmax,sizeof(int),sno);
  for (l=hsmin;l<=hsmax;l++)
  {
    writebuffer(&(smin(l)),sizeof(int),sno);
    writebuffer(&(smax(l)),sizeof(int),sno);
    int i;
    for (i=smin(l);i<=smax(l);i++)
    {
      int rmin=dv(l,i).indexmin();
      int rmax=dv(l,i).indexmax();
      writebuffer(&rmin,sizeof(int),sno);
      writebuffer(&rmax,sizeof(int),sno);
      for (int j=rmin;j<=rmax;j++)
      {
        int cmin=dv(l,i,j).indexmin();
        int cmax=dv(l,i,j).indexmax();
        writebuffer(&cmin,sizeof(int),sno);
        writebuffer(&cmax,sizeof(int),sno);
        int sz=cmax-cmin+1;
        writebuffer(&(dv(l,i,j)(cmin)),sz*sizeof(double),sno);
      }
    }
  }
}
dvar4_array adpthread_manager::get_dvar4_array_from_master(int sno)
{
  verify_id_string_from_master("HYD",sno);

  int hsmin;
  int hsmax;
  int l;
  readbuffer(&hsmin,sizeof(int),sno);
  readbuffer(&hsmax,sizeof(int),sno);
  dvar4_array M(hsmin,hsmax);
  ivector smin(hsmin,hsmax);
  ivector smax(hsmin,hsmax);
  for (l=hsmin;l<=hsmax;l++)
  {
    int i;
    readbuffer(&(smin(l)),sizeof(int),sno);
    readbuffer(&(smax(l)),sizeof(int),sno);
    M(l).allocate(smin(l),smax(l));
    for (i=smin(l);i<=smax(l);i++)
    {
      int rmin,rmax;
      readbuffer(&rmin,sizeof(int),sno);
      readbuffer(&rmax,sizeof(int),sno);
      M(l,i).allocate(rmin,rmax);
      for (int j=rmin;j<=rmax;j++)
      {
        int cmin,cmax;
        readbuffer(&cmin,sizeof(int),sno);
        readbuffer(&cmax,sizeof(int),sno);
        M(l,i,j).allocate(cmin,cmax);
        int sz=cmax-cmin+1;
        readbuffer(&(value(M(l,i,j)(cmin))),sz*sizeof(double),sno);
      }
    }
  }

  save_identifier_string("L2");
  for (l=hsmin;l<=hsmax;l++)
  {
    for (int i=smin(l);i<=smax(l);i++)
    {
      M(l,i).save_dvar_matrix_position();
    }
    save_int_value(smax(l));
    save_int_value(smin(l));
  }
  save_identifier_string("Y8");
  save_int_value(hsmax);
  save_int_value(hsmin);
  save_identifier_string("W8");
  save_int_value(sno);
  save_identifier_string("LG");
  save_pointer_value(this);
  save_identifier_string("I5");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(::adjoint_get_dvar4_array_from_master);
  return M;
}

