/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>
#ifdef __TURBOC__
  #pragma hdrstop
#endif

#include <string.h>
int save_identifier_string(const char*);
void verify_identifier_string(const char*);

//struct dvar_matrix_position;
//struct dvector_position;
long int reset_gs_stack(void);
void reset_gs_stack(long int);

#ifndef OPT_LIB
  #define CHK_ID_STRING
#endif

/**
Default constructor
*/
dvar_vector_position::dvar_vector_position():
  min(0),
  max(-1),
  va(nullptr)
{
}
/**
Copy constructor
*/
dvar_vector_position::dvar_vector_position(const dvar_vector_position& dvp):
  min(dvp.min),
  max(dvp.max),
  va(dvp.va)
{
}
/**
Copies vector min and max indexes and pointer to values from v.

\param v dvar_vector
*/
dvar_vector_position::dvar_vector_position(const dvar_vector& v):
  min(v.indexmin()),
  max(v.indexmax()),
  va(v.get_va())
{
}
/**
Get element i from dvar_vector_position.
\param i index
*/
double& dvar_vector_position::operator()(const int& i)
{
  if (i < min || i > max)
  {
    cerr << "Error -- Index out of bounds in "
     "double& dvar_vector_position::operator()(const int& i)\n";
    ad_exit(1);
  }
  return va[i].x;
}
/**
Copy index and pointer to values from vv.

\param vv a dvector
*/
dvector_position::dvector_position(const dvector& vv)
{
  min=vv.indexmin();
  max=vv.indexmax();
  v=vv.get_v();
}
/**
Copy constructor
*/
dvector_position::dvector_position(const dvector_position& dvp)
{
  min=dvp.min;
  max=dvp.max;
  v=dvp.v;
}
/**
Default constructor
*/
dvector_position::dvector_position(void)
{
  min=0;
  max=-1;
  v=0;
}

/**
 * Description not yet available.
 * \param
 */
ivector_position::ivector_position(const ivector& iv)
{
  min=iv.indexmin();
  max=iv.indexmax();
  v=iv.get_v();
}
/**
Copy constructor
*/
ivector_position::ivector_position(const ivector_position& dvp)
{
  min=dvp.min;
  max=dvp.max;
  v=dvp.v;
}
/**
Default constructor
*/
ivector_position::ivector_position(void)
{
  min=0;
  max=-1;
  v=0;
}
/**
 * Description not yet available.
 * \param
 */
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

/**
 * Description not yet available.
 * \param
 */
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

/**
 * Description not yet available.
 * \param
 */
dvar_matrix_position::dvar_matrix_position(const dvar_matrix& m,int x)
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

/**
 * Description not yet available.
 * \param
 */
dmatrix_position::dmatrix_position(const dmatrix& m)
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

/**
 * Description not yet available.
 * \param
 */
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

/**
 * Description not yet available.
 * \param
 */
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

/**
 * Description not yet available.
 * \param
 */
dvar_matrix_position::dvar_matrix_position(const dvar_matrix_position& p)
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
/**
Copy constructor
*/
dmatrix_position::dmatrix_position(const dmatrix_position& p)
  : lb(p.row_min,p.row_max), ub(p.row_min,p.row_max),
    ptr(p.row_min,p.row_max)
{
  row_min=p.row_min;
  row_max=p.row_max;
  lb=p.lb;
  ub=p.ub;
  ptr=p.ptr;
}
/**
\ingroup DEVEL
Writes a gradient stack verification string.
Writes a character string to the adjoint code variable stack.
Only available in the "safe" library.
Used primarily for debugging adjoint coide.
\param str Character sting to saved on the stack.
*/
int save_identifier_string(const char* str)
{
#if defined(CHK_ID_STRING)
  //int wsize=sizeof(char);
  size_t length=strlen(str);
  gradient_structure::get_fp()->fwrite(str,length);
#endif
  return 0;
}
