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
#include "fvar.hpp"

void dmdv_prod(void);
void cmdv_prod(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator*(const dvar_matrix& m, const dvar_vector& x)
{
  gradient_structure* gs = gradient_structure::_instance;
  gs->RETURN_ARRAYS_INCREMENT();

#ifndef OPT_LIB
  if (x.indexmin() != m.colmin() || x.indexmax() != m.colmax())
  {
     cerr << " Incompatible array bounds in "
     "dvar_vector operator*(const dvar_matrix& m, const dvar_vector& x)\n";
     ad_exit(21);
  }
#endif

  kkludge_object kkk;
  dvar_vector tmp(m.rowmin(),m.rowmax(),kkk);
  for (int i=m.rowmin(); i<=m.rowmax(); i++)
  {
    double sum = 0.0;
    for (int j=x.indexmin(); j<=x.indexmax(); j++)
    {
       //sum+=m[i][j]*x[j];
       sum+=(m.elem(i)).elem_value(j)*x.elem_value(j);
    }
    tmp.elem_value(i)=sum;
  }

  DF_FILE* fp = gradient_structure::fp;
#ifndef OPT_LIB
  save_identifier_string("PLACE4");
#endif
  fp->save_dvar_vector_value(x);
  fp->save_dvar_vector_position(x);
#ifndef OPT_LIB
  save_identifier_string("PLACE3");
#endif
  fp->save_dvar_matrix_value(m);
  fp->save_dvar_matrix_position(m);
#ifndef OPT_LIB
  save_identifier_string("PLACE2");
#endif
  fp->save_dvar_vector_position(tmp);
#ifndef OPT_LIB
  save_identifier_string("PLACE1");
#endif
  gs->GRAD_STACK1->set_gradient_stack(dmdv_prod);
  gs->RETURN_ARRAYS_DECREMENT();
  return(tmp);
}

/**
 * Description not yet available.
 * \param
 */
void dmdv_prod(void)
{
  DF_FILE* fp = gradient_structure::fp;

#ifndef OPT_LIB
  verify_identifier_string("PLACE1");
#endif
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
#ifndef OPT_LIB
  verify_identifier_string("PLACE2");
#endif
  dvar_matrix_position m_pos=fp->restore_dvar_matrix_position();
  dmatrix m=fp->restore_dvar_matrix_value(m_pos);
#ifndef OPT_LIB
  verify_identifier_string("PLACE3");
#endif
  dvar_vector_position x_pos=fp->restore_dvar_vector_position();
  dvector x=restore_dvar_vector_value(x_pos);
#ifndef OPT_LIB
  verify_identifier_string("PLACE4");
#endif
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);

  dmatrix dfm(m_pos);
  dvector dfx(x_pos.indexmin(),x_pos.indexmax());
  dfm.initialize();
  dfx.initialize();

  for (int i=m.rowmax(); i>=m.rowmin(); i--)
  {
    //tmp.elem_value(i)=sum;
    double dfsum=dftmp.elem(i);
    for (int j=x.indexmax(); j>=x.indexmin(); j--)
    {
      //sum+=(m.elem(i)).elem_value(j)*x.elem_value(j);
      dfm.elem(i,j)+=dfsum*x.elem(j);
      dfx.elem(j)+=dfsum*m.elem(i,j);
    }
    //sum=0.0;
    dfsum=0.0;
  }
  dfx.save_dvector_derivatives(x_pos);
  dfm.save_dmatrix_derivatives(m_pos);
}

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator*(const dmatrix& m, const dvar_vector& x)
{
  gradient_structure* gs = gradient_structure::_instance;

  gs->RETURN_ARRAYS_INCREMENT();

#ifndef OPT_LIB
  if (x.indexmin() != m.colmin() || x.indexmax() != m.colmax())
  {
    cerr << " Incompatible array bounds in "
    "dvar_vector operator*(const dvar_matrix& m, const dvar_vector& x)\n";
    ad_exit(21);
  }
#endif

  kkludge_object kkk;
  dvar_vector tmp(m.rowmin(),m.rowmax(),kkk);
  for (int i=m.rowmin(); i<=m.rowmax(); i++)
  {
    double sum=0.0;
    for (int j=x.indexmin(); j<=x.indexmax(); j++)
    {
      //sum+=m[i][j]*x[j];
      sum+=(m.elem(i)).elem(j)*x.elem_value(j);
    }
    tmp.elem_value(i)=sum;
  }

  DF_FILE* fp = gradient_structure::fp;
#ifndef OPT_LIB
  save_identifier_string("PLACE4");
#endif
  fp->save_dvar_vector_value(x);
  fp->save_dvar_vector_position(x);
  fp->save_dmatrix_value(m);
  fp->save_dmatrix_position(m);
#ifndef OPT_LIB
  save_identifier_string("PLACE2");
#endif
  fp->save_dvar_vector_position(tmp);
#ifndef OPT_LIB
  save_identifier_string("PLACE1");
#endif
  gs->GRAD_STACK1->set_gradient_stack(cmdv_prod);
  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void cmdv_prod(void)
{
  DF_FILE* fp = gradient_structure::fp;

#ifndef OPT_LIB
  verify_identifier_string("PLACE1");
#endif
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
#ifndef OPT_LIB
  verify_identifier_string("PLACE2");
#endif
  dmatrix_position m_pos=fp->restore_dmatrix_position();
  dmatrix m=fp->restore_dmatrix_value(m_pos);
  dvar_vector_position x_pos=fp->restore_dvar_vector_position();
  dvector x=restore_dvar_vector_value(x_pos);
#ifndef OPT_LIB
  verify_identifier_string("PLACE4");
#endif
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);

  dvector dfx(x_pos.indexmin(),x_pos.indexmax());
  dfx.initialize();
  for (int i=m.rowmax(); i>=m.rowmin(); i--)
  {
    // tmp.elem_value(i)=sum;
    double dfsum=dftmp.elem(i);
    for (int j=x.indexmax(); j>=x.indexmin(); j--)
    {
      //sum+=(m.elem(i)).elem(j)*x.elem_value(j);
      dfx.elem(j)+=dfsum*m.elem(i,j);
    }
    //sum=0.0;
    dfsum=0.0;
  }
  dfx.save_dvector_derivatives(x_pos);
}
