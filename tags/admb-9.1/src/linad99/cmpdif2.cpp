/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <fvar.hpp>
#ifdef __TURBOC__
  #pragma hdrstop
#endif
#if !defined (__NDPX__) && !defined(__SUN__) && !defined(__GNU__)
#endif


#include <string.h>
int save_identifier_string(char*);
void verify_identifier_string(char*);

struct dvar_matrix_position;
struct dvector_position;
long int reset_gs_stack(void);
void reset_gs_stack(long int);

dvar_vector_position::dvar_vector_position(_CONST dvar_vector& v)
{
  min=v.indexmin();
  max=v.indexmax();
  va=v.get_va();
}

dvector_position::dvector_position(_CONST dvector& vv)
{
  min=vv.indexmin();
  max=vv.indexmax();
  v=vv.get_v();
}

dvar_vector_position::dvar_vector_position(BOR_CONST dvar_vector_position& dvp)
{
  min=dvp.min;
  max=dvp.max;
  va=dvp.va;
}

dvector_position::dvector_position(BOR_CONST dvector_position& dvp)
{
  min=dvp.min;
  max=dvp.max;
  v=dvp.v;
}

dvar_vector_position::dvar_vector_position(void)
{
  min=0;
  max=-1;
  va=0;
}

dvector_position::dvector_position(void)
{
  min=0;
  max=-1;
  v=0;
}

ivector_position::ivector_position(_CONST ivector& iv)
{
  min=iv.indexmin();
  max=iv.indexmax();
  v=iv.get_v();
}

ivector_position::ivector_position(BOR_CONST ivector_position& dvp)
{
  min=dvp.min;
  max=dvp.max;
  v=dvp.v;
}

ivector_position::ivector_position(void)
{
  min=0;
  max=-1;
  v=0;
}

double& dvar_vector_position::operator () (BOR_CONST int& i)
{
  if (i<min||i>max)
  {
    cerr << "Error -- Index out of bounds in\n"
     "double_and_int& dvar_vector_position::operator () (BOR_CONST int& i)"
     << endl;
     ad_exit(1);
   }
   return va[i].x;
}

dvar_vector_position dvar_matrix_position::operator () (int i)
{
  if (i<row_min||i>row_max)
  {
    cerr << "Index out of range in\n"
        "  dvar_vector_position dvar_matrix_position::operator () (int i)"
      << endl;
  }
  dvar_vector_position tmp;
  tmp.min=lb(i);
  tmp.max=ub(i);
  tmp.va=(double_and_int *) ptr(i);
  return tmp;
}

dvector_position dmatrix_position::operator () (int i)
{
  if (i<row_min||i>row_max)
  {
    cerr << "Index out of range in\n"
        "  dvector_position dmatrix_position::operator () (int i)"
      << endl;
  }
  dvector_position tmp;
  tmp.min=lb(i);
  tmp.max=ub(i);
  tmp.v=(double *) ptr(i);
  return tmp;
}

dvar_matrix_position::dvar_matrix_position(_CONST dvar_matrix& m,int x)
  : lb(m.rowmin(),m.rowmax()), ub(m.rowmin(),m.rowmax()),
  ptr(m.rowmin(),m.rowmax())

{
  row_min=m.rowmin();
  row_max=m.rowmax();
  for (int i=row_min;i<=row_max;i++)
  {
    if (allocated(m(i)))
    {
      lb(i)=m(i).indexmin();
      ub(i)=m(i).indexmax();
      ptr(i)=m(i).get_va();
    }
    else
    {
      lb(i)=0;
      ub(i)=-1;
      ptr(i)=0;
    }
  }
}

dmatrix_position::dmatrix_position(_CONST dmatrix& m)
  : lb(m.rowmin(),m.rowmax()), ub(m.rowmin(),m.rowmax()),
  ptr(m.rowmin(),m.rowmax())
{
  row_min=m.rowmin();
  row_max=m.rowmax();
  for (int i=row_min;i<=row_max;i++)
  {
    lb(i)=m(i).indexmin();
    ub(i)=m(i).indexmax();
    ptr(i)=m(i).get_v();
  }
}

dvar_matrix_position::dvar_matrix_position(int min,int max)
  : lb(min,max), ub(min,max), ptr(min,max)
{
  row_min=min;
  row_max=max;
  for (int i=row_min;i<=row_max;i++)
  {
    lb(i)=0;
    ub(i)=-1;
    ptr(i)=0;
  }
}

dmatrix_position::dmatrix_position(int min,int max)
  : lb(min,max), ub(min,max), ptr(min,max)
{
  row_min=min;
  row_max=max;
  for (int i=row_min;i<=row_max;i++)
  {
    lb(i)=0;
    ub(i)=-1;
    ptr(i)=0;
  }
}

dvar_matrix_position::dvar_matrix_position(BOR_CONST dvar_matrix_position& p)
  : lb(p.row_min,p.row_max), ub(p.row_min,p.row_max),
    ptr(p.row_min,p.row_max)
{
  row_min=p.row_min;
  row_max=p.row_max;
  lb=p.lb;
  ub=p.ub;
  ptr=p.ptr;
  // cout << "ptr= " << ptr ;
}

dmatrix_position::dmatrix_position(BOR_CONST dmatrix_position& p)
  : lb(p.row_min,p.row_max), ub(p.row_min,p.row_max),
    ptr(p.row_min,p.row_max)
{
  row_min=p.row_min;
  row_max=p.row_max;
  lb=p.lb;
  ub=p.ub;
  ptr=p.ptr;
  // cout << "ptr= " << ptr ;
}

int save_identifier_string(char* str)
{
#if defined(CHK_ID_STRING)
  int wsize=sizeof(char);
  int length=strlen(str);
  gradient_structure::get_fp()->fwrite(str,length);
#endif
  return 0;
}

