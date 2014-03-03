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
void dfbltsolve(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector solve(const banded_lower_triangular_dvar_matrix& m,
  const dvar_vector &v)
{
  int bw=m.bandwidth();
  int imin=m.indexmin();
  int imax=m.indexmax();
  dvar_vector x(imin,imax);
  x.elem_value(imin)=v.elem_value(imin)/m.elem_value(imin,imin);
  for (int i=imin+1;i<=imax;i++)
  {
    int jmin=admax(imin,i-bw+1);
    double ssum=0.0;
    for (int j=jmin;j<=i-1;j++)
    {
      ssum+=m.elem_value(i,j)*x.elem_value(j);
    }
    x.elem_value(i)=(v.elem_value(i)-ssum)/m.elem_value(i,i);
  }
  save_identifier_string("rt");
  m.save_dvar_matrix_value();
  m.save_dvar_matrix_position();
  v.save_dvar_vector_value();
  v.save_dvar_vector_position();
  x.save_dvar_vector_position();
  save_identifier_string("ww");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(dfbltsolve);
  return x;
}

/*
dvar_vector solve(const banded_lower_triangular_dvar_matrix& m,
  const dvar_vector &v, dvariable& lndet)
{
  int bw=m.bandwidth();
  int imin=m.indexmin();
  int imax=m.indexmax();
  dvar_vector x(imin,imax);
  value(x(imin))=value(v(1))/value(m(1,1));
  for (int i=2;i<=imax;i++)
  {
    int jmin=admax(1,i-bw+1);
    double ssum=0.0;
    for (int j=jmin;j<=i-1;j++)
    {
      ssum+=value(m(i,j))*value(x(j));
    }
    value(x(i))=(value(v(i))-ssum)/value(m(i,i));
  }
  save_identifier_string("rt");
  m.save_dvar_matrix_value();
  m.save_dvar_matrix_position();
  v.save_dvar_vector_value();
  v.save_dvar_vector_position();
  x.save_dvar_vector_position();
  save_identifier_string("ww");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(dfbltsolve);
  return x;
}
*/

/**
 * Description not yet available.
 * \param
 */
void dfbltsolve(void)
{
  verify_identifier_string("ww");
  dvar_vector_position xpos=restore_dvar_vector_position();
  dvar_vector_position vpos=restore_dvar_vector_position();
  dvector v=restore_dvar_vector_value(vpos);
  dvar_matrix_position mpos=restore_dvar_matrix_position();
  banded_lower_triangular_dmatrix m=
    restore_banded_lower_triangular_dvar_matrix_value(mpos);
  verify_identifier_string("rt");
  dvector dfx=
    restore_dvar_vector_derivatives(xpos);

  int bw=m.bandwidth();
  int imin=m.indexmin();
  int imax=m.indexmax();

  banded_lower_triangular_dmatrix dfm(imin,imax,bw);
  dvector x(imin,imax);
  dvector dfv(imin,imax);
  dfm.initialize();
  dfv.initialize();
  x(imin)=v(1)/m(1,1);
  dvector dfsum(imin,imax);
  dfsum.initialize();
  dvector ssum(imin,imax);
  ssum.initialize();
  int i;
  for (i=2;i<=imax;i++)
  {
    int jmin=admax(1,i-bw+1);
    for (int j=jmin;j<=i-1;j++)
    {
      ssum(i)+=m(i,j)*x(j);
    }
    x(i)=(v(i)-ssum(i))/m(i,i);
  }

  for (i=imax;i>=2;i--)
  {
    int jmin=admax(1,i-bw+1);
    //x(i)=(v(i)-ssum(i))/m(i,i);
    dfv(i)+=dfx(i)/m(i,i);
    dfsum(i)-=dfx(i)/m(i,i);
    dfm(i,i)-=dfx(i)*(v(i)-ssum(i))/(m(i,i)*m(i,i));
    dfx(i)=0.0;
    for (int j=i-1;j>=jmin;j--)
    {
      //ssum(i)+=m(i,j)*x(j);
      dfm(i,j)+=dfsum(i)*x(j);
      dfx(j)+=dfsum(i)*m(i,j);
    }
  }
  //x(imin)=v(1)/m(1,1);
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //dfm(imax,imax)=0.0;
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //x.elem_value(imin)=v.elem_value(imin)/m.elem_value(imin,imin);
  dfv(imin)+=dfx(imin)/m(imin,imin);
  dfm(imin,imin)-=dfx(imin)*v(imin)/(m(imin,imin)*m(imin,imin));
  dfx(imin)=0.0;

  dfm.save_dmatrix_derivatives(mpos);
  dfv.save_dvector_derivatives(vpos);
}
