#include <admodel.h>
#include <cstddef>
#include "adthread.h"
#if !defined(OPT_LIB)
#  if !defined(CHK_ID_STRING)
#    define CHK_ID_STRING
#  endif
#endif


void adjoint_send_dvar5_array_to_master(void)
{
  verify_identifier_string("CV");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_send_dvar5_array_to_master();
}

void adpthread_manager::adjoint_send_dvar5_array_to_master(void)
{
  verify_identifier_string("HH");
  int sno=restore_int_value();
  verify_id_string_from_master("FDG",sno);
  int h5min;
  int h5max;
  readbuffer(&h5min,sizeof(int),sno);
  readbuffer(&h5max,sizeof(int),sno);
  d5_array M(h5min,h5max);
  ivector hsmin(h5min,h5max);
  ivector hsmax(h5min,h5max);
  imatrix smin(h5min,h5max);
  imatrix smax(h5min,h5max);
  i3_array rmin(h5min,h5max);
  i3_array rmax(h5min,h5max);
  for (int l5=h5min;l5<=h5max;l5++)
  {
    readbuffer(&(hsmin(l5)),sizeof(int),sno);
    readbuffer(&(hsmax(l5)),sizeof(int),sno);
    M(l5).allocate(hsmin(l5),hsmax(l5));
    int l;
    rmin(l5).allocate(hsmin(l5),hsmax(l5));
    rmax(l5).allocate(hsmin(l5),hsmax(l5));
    smin(l5).allocate(hsmin(l5),hsmax(l5));
    smax(l5).allocate(hsmin(l5),hsmax(l5));
    for (l=hsmin(l5);l<=hsmax(l5);l++)
    {
      readbuffer(&(smin(l5,l)),sizeof(int),sno);
      readbuffer(&(smax(l5,l)),sizeof(int),sno);
      M(l5,l).allocate(smin(l5,l),smax(l5,l));
      rmin(l5,l).allocate(smin(l5,l),smax(l5,l));
      rmax(l5,l).allocate(smin(l5,l),smax(l5,l));
      for (int i=smin(l5,l);i<=smax(l5,l);i++)
      {
        readbuffer(&(rmin(l5,l,i)),sizeof(int),sno);
        readbuffer(&(rmax(l5,l,i)),sizeof(int),sno);
        M(l5,l,i).allocate(rmin(l5,l,i),rmax(l5,l,i));
        for (int j=rmin(l5,l,i);j<=rmax(l5,l,i);j++)
        { 
          int cmin,cmax;
          readbuffer(&cmin,sizeof(int),sno);
          readbuffer(&cmax,sizeof(int),sno);
          M(l5,l,i,j).allocate(cmin,cmax);
          int sz=cmax-cmin+1;
          readbuffer(&(M(l5,l,i,j)(cmin)),sz*sizeof(double),sno);
        }
      }
    }
  }
  verify_identifier_string("OP");
  for (int l5=h5max;l5>=h5min;l5--)
  {
    for (int l=hsmax(l5);l>=hsmin(l5);l--)
    {
      for (int i=smax(l5,l);i>=smin(l5,l);i--)
      {
        dvar_matrix_position dmpos=restore_dvar_matrix_position();
        M(l5,l,i).save_dmatrix_derivatives(dmpos);
      }
    }
  }
  verify_identifier_string("VC");
}

void adpthread_manager::send_dvar5_array_to_master(const dvar5_array &x,int sno)
{
  send_id_string_to_master("HYD",sno);

  int h5min=x.indexmin();
  int h5max=x.indexmax();
  writebuffer(&h5min,sizeof(int),sno);
  writebuffer(&h5max,sizeof(int),sno);
  int l5;

  ivector hsmin(h5min,h5max);
  ivector hsmax(h5min,h5max);
  imatrix smin(h5min,h5max);
  imatrix smax(h5min,h5max);

  for (l5=h5min;l5<=h5max;l5++)
  {
    hsmin(l5)=x(l5).indexmin();
    hsmax(l5)=x(l5).indexmax();
    writebuffer(&(hsmin(l5)),sizeof(int),sno);
    writebuffer(&(hsmax(l5)),sizeof(int),sno);
    int l;
  
    smin(l5).allocate(hsmin(l5),hsmax(l5));
    smax(l5).allocate(hsmin(l5),hsmax(l5));
    for (l=hsmin(l5);l<=hsmax(l5);l++)
    {
      smin(l5,l)=x(l5,l).indexmin();
      smax(l5,l)=x(l5,l).indexmax();
      int i;
      writebuffer(&(smin(l5,l)),sizeof(int),sno);
      writebuffer(&(smax(l5,l)),sizeof(int),sno);
      for (i=smin(l5,l);i<=smax(l5,l);i++)
      {
        int rmin=x(l5,l,i).indexmin();
        int rmax=x(l5,l,i).indexmax();
        writebuffer(&rmin,sizeof(int),sno);
        writebuffer(&rmax,sizeof(int),sno);
        for (int j=rmin;j<=rmax;j++)
        {
          int cmin=x(l5,l,i,j).indexmin();
          int cmax=x(l5,l,i,j).indexmax();
          writebuffer(&cmin,sizeof(int),sno);
          writebuffer(&cmax,sizeof(int),sno);
          int sz=cmax-cmin+1;
          writebuffer(&(value(x(l5,l,i,j)(cmin))),sz*sizeof(double),sno);
        }
      }
    }
  }
  save_identifier_string("VC");
  // !!! should we optimize this ?
  for (int l5=h5min;l5<=h5max;l5++)
  {
    for (int l=hsmin(l5);l<=hsmax(l5);l++)
    {
      for (int i=smin(l5,l);i<=smax(l5,l);i++)
      {
        x(l5,l,i).save_dvar_matrix_position();
      }
    }
  }
  save_identifier_string("OP");
  save_int_value(sno);
  save_identifier_string("HH");
  save_pointer_value(this);
  save_identifier_string("CV");
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(::adjoint_send_dvar5_array_to_master);
}

void adpthread_manager::send_dvar5_array(const dvar5_array &x,int sno)
{
  send_id_string_to_master("HYD",sno);

  int h5min=x.indexmin();
  int h5max=x.indexmax();
  writebuffer(&h5min,sizeof(int),sno);
  writebuffer(&h5max,sizeof(int),sno);
  int l5;

  ivector hsmin(h5min,h5max);
  ivector hsmax(h5min,h5max);
  imatrix smin(h5min,h5max);
  imatrix smax(h5min,h5max);

  for (l5=h5min;l5<=h5max;l5++)
  {
    hsmin(l5)=x(l5).indexmin();
    hsmax(l5)=x(l5).indexmax();
    writebuffer(&(hsmin(l5)),sizeof(int),sno);
    writebuffer(&(hsmax(l5)),sizeof(int),sno);
    int l;
  
    smin(l5).allocate(hsmin(l5),hsmax(l5));
    smax(l5).allocate(hsmin(l5),hsmax(l5));
    for (l=hsmin(l5);l<=hsmax(l5);l++)
    {
      smin(l5,l)=x(l5,l).indexmin();
      smax(l5,l)=x(l5,l).indexmax();
      int i;
      writebuffer(&(smin(l5,l)),sizeof(int),sno);
      writebuffer(&(smax(l5,l)),sizeof(int),sno);
      for (i=smin(l5,l);i<=smax(l5,l);i++)
      {
        int rmin=x(l5,l,i).indexmin();
        int rmax=x(l5,l,i).indexmax();
        writebuffer(&rmin,sizeof(int),sno);
        writebuffer(&rmax,sizeof(int),sno);
        for (int j=rmin;j<=rmax;j++)
        {
          int cmin=x(l5,l,i,j).indexmin();
          int cmax=x(l5,l,i,j).indexmax();
          writebuffer(&cmin,sizeof(int),sno);
          writebuffer(&cmax,sizeof(int),sno);
          int sz=cmax-cmin+1;
          writebuffer(&(value(x(l5,l,i,j)(cmin))),sz*sizeof(double),sno);
        }
      }
    }
  }
  save_identifier_string("VC");
  // !!! should we optimize this ?
  for (int l5=h5min;l5<=h5max;l5++)
  {
    for (int l=hsmin(l5);l<=hsmax(l5);l++)
    {
      for (int i=smin(l5,l);i<=smax(l5,l);i++)
      {
        x(l5,l,i).save_dvar_matrix_position();
      }
    }
  }
  save_identifier_string("OP");
  save_int_value(sno);
  save_identifier_string("HH");
  save_pointer_value(this);
  save_identifier_string("CV");
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(::adjoint_send_dvar5_array_to_master);
}

void adpthread_manager::send_d5_array(const d5_array &x,int sno)
{
  send_id_string_to_master("LOZ",sno);

  int h5min=x.indexmin();
  int h5max=x.indexmax();
  writebuffer(&h5min,sizeof(int),sno);
  writebuffer(&h5max,sizeof(int),sno);
  int l5;

  ivector hsmin(h5min,h5max);
  ivector hsmax(h5min,h5max);
  imatrix smin(h5min,h5max);
  imatrix smax(h5min,h5max);

  for (l5=h5min;l5<=h5max;l5++)
  {
    hsmin(l5)=x(l5).indexmin();
    hsmax(l5)=x(l5).indexmax();
    writebuffer(&(hsmin(l5)),sizeof(int),sno);
    writebuffer(&(hsmax(l5)),sizeof(int),sno);
    int l;
  
    smin(l5).allocate(hsmin(l5),hsmax(l5));
    smax(l5).allocate(hsmin(l5),hsmax(l5));
    for (l=hsmin(l5);l<=hsmax(l5);l++)
    {
      smin(l5,l)=x(l5,l).indexmin();
      smax(l5,l)=x(l5,l).indexmax();
      int i;
      writebuffer(&(smin(l5,l)),sizeof(int),sno);
      writebuffer(&(smax(l5,l)),sizeof(int),sno);
      for (i=smin(l5,l);i<=smax(l5,l);i++)
      {
        int rmin=x(l5,l,i).indexmin();
        int rmax=x(l5,l,i).indexmax();
        writebuffer(&rmin,sizeof(int),sno);
        writebuffer(&rmax,sizeof(int),sno);
        for (int j=rmin;j<=rmax;j++)
        {
          int cmin=x(l5,l,i,j).indexmin();
          int cmax=x(l5,l,i,j).indexmax();
          writebuffer(&cmin,sizeof(int),sno);
          writebuffer(&cmax,sizeof(int),sno);
          int sz=cmax-cmin+1;
          writebuffer(&(x(l5,l,i,j)(cmin)),sz*sizeof(double),sno);
        }
      }
    }
  }
}

void adjoint_get_dvar5_array_from_slave(void)
{
  verify_identifier_string("I5");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_get_dvar5_array_from_slave();
}

void adpthread_manager::adjoint_get_dvar5_array_from_slave(void)
{
  verify_identifier_string("LG");
  int sno=restore_int_value();
  verify_identifier_string("W8");
  int h5min=restore_int_value();
  int h5max=restore_int_value();
  verify_identifier_string("GF");
  int l;
  d5_array dv(h5min,h5max);
  ivector hsmin(h5min,h5max);
  ivector hsmax(h5min,h5max);
  imatrix smin(h5min,h5max);
  imatrix smax(h5min,h5max);
  for (int l5=h5max;l5>=h5min;l5--)
  {
    hsmin(l5)=restore_int_value();
    hsmax(l5)=restore_int_value();
    smin(l5).allocate(hsmin(l5),hsmax(l5));
    smax(l5).allocate(hsmin(l5),hsmax(l5));
    dv(l5).allocate(hsmin(l5),hsmax(l5));
    for (l=hsmax(l5);l>=hsmin(l5);l--)
    {
      smin(l5,l)=restore_int_value();
      smax(l5,l)=restore_int_value();
      dv(l5,l).allocate(smin(l5,l),smax(l5,l));
      for (int i=smax(l5,l);i>=smin(l5,l);i--)
      {
        dvar_matrix_position dvpos=restore_dvar_matrix_position();
        dv(l5,l,i)=restore_dvar_matrix_derivatives(dvpos);
      }
    }
  }
  verify_identifier_string("Y5");
  send_id_string_to_slave("FDG",sno);
  writebuffer(&h5min,sizeof(int),sno);
  writebuffer(&h5max,sizeof(int),sno);
  for (int l5=h5min;l5<=h5max;l5++)
  {
    writebuffer(&(hsmin(l5)),sizeof(int),sno);
    writebuffer(&(hsmax(l5)),sizeof(int),sno);
    for (l=hsmin(l5);l<=hsmax(l5);l++)
    {
      writebuffer(&(smin(l5,l)),sizeof(int),sno);
      writebuffer(&(smax(l5,l)),sizeof(int),sno);
      int i;
      for (i=smin(l5,l);i<=smax(l5,l);i++)
      {
        int rmin=dv(l5,l,i).indexmin();
        int rmax=dv(l5,l,i).indexmax();
        writebuffer(&rmin,sizeof(int),sno);
        writebuffer(&rmax,sizeof(int),sno);
        for (int j=rmin;j<=rmax;j++)
        {
          int cmin=dv(l5,l,i,j).indexmin();
          int cmax=dv(l5,l,i,j).indexmax();
          writebuffer(&cmin,sizeof(int),sno);
          writebuffer(&cmax,sizeof(int),sno);
          int sz=cmax-cmin+1;
          writebuffer(&(dv(l5,l,i,j)(cmin)),sz*sizeof(double),sno);
        }
      }
    }
  }
}
dvar5_array adpthread_manager::get_dvar5_array_from_slave(int sno)
{
  verify_id_string_from_slave("HYD",sno);
 // &***********************************************************
 // &***********************************************************

  int h5min;
  int h5max;
  readbuffer(&h5min,sizeof(int),sno);
  readbuffer(&h5max,sizeof(int),sno);
  int l5;
  dvar5_array M(h5min,h5max);

  ivector hsmin(h5min,h5max);
  ivector hsmax(h5min,h5max);
  imatrix smin(h5min,h5max);
  imatrix smax(h5min,h5max);

  for (l5=h5min;l5<=h5max;l5++)
  {
    readbuffer(&(hsmin(l5)),sizeof(int),sno);
    readbuffer(&(hsmax(l5)),sizeof(int),sno);
    M(l5).allocate(hsmin(l5),hsmax(l5));
    int l;
  
    smin(l5).allocate(hsmin(l5),hsmax(l5));
    smax(l5).allocate(hsmin(l5),hsmax(l5));
    for (l=hsmin(l5);l<=hsmax(l5);l++)
    {
      int i;
      readbuffer(&(smin(l5,l)),sizeof(int),sno);
      readbuffer(&(smax(l5,l)),sizeof(int),sno);
      M(l5,l).allocate(smin(l5,l),smax(l5,l));
      for (i=smin(l5,l);i<=smax(l5,l);i++)
      {
        int rmin,rmax;
        readbuffer(&rmin,sizeof(int),sno);
        readbuffer(&rmax,sizeof(int),sno);
        M(l5,l,i).allocate(rmin,rmax);
        for (int j=rmin;j<=rmax;j++)
        {
          int cmin,cmax;
          readbuffer(&cmin,sizeof(int),sno);
          readbuffer(&cmax,sizeof(int),sno);
          M(l5,l,i,j).allocate(cmin,cmax);
          int sz=cmax-cmin+1;
          readbuffer(&(value(M(l5,l,i,j)(cmin))),sz*sizeof(double),sno);
        }
      }
    }
  }

  save_identifier_string("Y5");
  for (l5=h5min;l5<=h5max;l5++)
  {
    for (int l=hsmin(l5);l<=hsmax(l5);l++)
    {
      for (int i=smin(l5,l);i<=smax(l5,l);i++)
      {
        M(l5,l,i).save_dvar_matrix_position();
      }
      save_int_value(smax(l5,l));
      save_int_value(smin(l5,l));
    }
    save_int_value(hsmax(l5));
    save_int_value(hsmin(l5));
  }
  save_identifier_string("GF");
  save_int_value(h5max);
  save_int_value(h5min);
  save_identifier_string("W8");
  save_int_value(sno);
  save_identifier_string("LG");
  save_pointer_value(this);
  save_identifier_string("I5");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(::adjoint_get_dvar5_array_from_slave);
  return M;
}

dvar5_array adpthread_manager::get_dvar5_array(int sno)
{
  verify_id_string_from_slave("HYD",sno);
 // &***********************************************************
 // &***********************************************************

  int h5min;
  int h5max;
  readbuffer(&h5min,sizeof(int),sno);
  readbuffer(&h5max,sizeof(int),sno);
  int l5;
  dvar5_array M(h5min,h5max);

  ivector hsmin(h5min,h5max);
  ivector hsmax(h5min,h5max);
  imatrix smin(h5min,h5max);
  imatrix smax(h5min,h5max);

  for (l5=h5min;l5<=h5max;l5++)
  {
    readbuffer(&(hsmin(l5)),sizeof(int),sno);
    readbuffer(&(hsmax(l5)),sizeof(int),sno);
    M(l5).allocate(hsmin(l5),hsmax(l5));
    int l;
  
    smin(l5).allocate(hsmin(l5),hsmax(l5));
    smax(l5).allocate(hsmin(l5),hsmax(l5));
    for (l=hsmin(l5);l<=hsmax(l5);l++)
    {
      int i;
      readbuffer(&(smin(l5,l)),sizeof(int),sno);
      readbuffer(&(smax(l5,l)),sizeof(int),sno);
      M(l5,l).allocate(smin(l5,l),smax(l5,l));
      for (i=smin(l5,l);i<=smax(l5,l);i++)
      {
        int rmin,rmax;
        readbuffer(&rmin,sizeof(int),sno);
        readbuffer(&rmax,sizeof(int),sno);
        M(l5,l,i).allocate(rmin,rmax);
        for (int j=rmin;j<=rmax;j++)
        {
          int cmin,cmax;
          readbuffer(&cmin,sizeof(int),sno);
          readbuffer(&cmax,sizeof(int),sno);
          M(l5,l,i,j).allocate(cmin,cmax);
          int sz=cmax-cmin+1;
          readbuffer(&(value(M(l5,l,i,j)(cmin))),sz*sizeof(double),sno);
        }
      }
    }
  }

  save_identifier_string("Y5");
  for (l5=h5min;l5<=h5max;l5++)
  {
    for (int l=hsmin(l5);l<=hsmax(l5);l++)
    {
      for (int i=smin(l5,l);i<=smax(l5,l);i++)
      {
        M(l5,l,i).save_dvar_matrix_position();
      }
      save_int_value(smax(l5,l));
      save_int_value(smin(l5,l));
    }
    save_int_value(hsmax(l5));
    save_int_value(hsmin(l5));
  }
  save_identifier_string("GF");
  save_int_value(h5max);
  save_int_value(h5min);
  save_identifier_string("W8");
  save_int_value(sno);
  save_identifier_string("LG");
  save_pointer_value(this);
  save_identifier_string("I5");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(::adjoint_get_dvar5_array_from_slave);
  return M;
}

d5_array adpthread_manager::get_d5_array(int sno)
{
  verify_id_string_from_slave("LOZ",sno);

  int h5min;
  int h5max;
  readbuffer(&h5min,sizeof(int),sno);
  readbuffer(&h5max,sizeof(int),sno);
  int l5;
  d5_array M(h5min,h5max);

  ivector hsmin(h5min,h5max);
  ivector hsmax(h5min,h5max);
  imatrix smin(h5min,h5max);
  imatrix smax(h5min,h5max);

  for (l5=h5min;l5<=h5max;l5++)
  {
    readbuffer(&(hsmin(l5)),sizeof(int),sno);
    readbuffer(&(hsmax(l5)),sizeof(int),sno);
    M(l5).allocate(hsmin(l5),hsmax(l5));
    int l;
  
    smin(l5).allocate(hsmin(l5),hsmax(l5));
    smax(l5).allocate(hsmin(l5),hsmax(l5));
    for (l=hsmin(l5);l<=hsmax(l5);l++)
    {
      int i;
      readbuffer(&(smin(l5,l)),sizeof(int),sno);
      readbuffer(&(smax(l5,l)),sizeof(int),sno);
      M(l5,l).allocate(smin(l5,l),smax(l5,l));
      for (i=smin(l5,l);i<=smax(l5,l);i++)
      {
        int rmin,rmax;
        readbuffer(&rmin,sizeof(int),sno);
        readbuffer(&rmax,sizeof(int),sno);
        M(l5,l,i).allocate(rmin,rmax);
        for (int j=rmin;j<=rmax;j++)
        {
          int cmin,cmax;
          readbuffer(&cmin,sizeof(int),sno);
          readbuffer(&cmax,sizeof(int),sno);
          M(l5,l,i,j).allocate(cmin,cmax);
          int sz=cmax-cmin+1;
          readbuffer(&(M(l5,l,i,j)(cmin)),sz*sizeof(double),sno);
        }
      }
    }
  }
  return M;
}

