/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Dot-product fpor dvar_vector and sum for dvar_vector and dvar_matrix.
 */
// file fvar.cpp
// constructors, destructors and misc functions involving class prevariable

#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif


/** Compute the dot product of two variable type vectors. The minimum and maxium
  legal subscripts of the arguments must agree; otherwize an error message
   is printed and execution terminates.
  \ingroup matop
  \param v1 A dvar_vector, \f$a\f$.
  \param v2 A dvar_vector, \f$b\f$.
  \return A dvariable, \f$z = a\cdot b = \sum_i a_i\cdot b_i\f$  containing
  the value of the dot product of the two arguments.
*/
dvariable operator*(const dvar_vector& v1, const dvar_vector& v2)
{
  RETURN_ARRAYS_INCREMENT();
  if (v1.indexmin()!=v2.indexmin()||v1.indexmax()!=v2.indexmax())
  {
    cerr << "Incompatible bounds in "
      "prevariable operator * (const dvar_vector& v1, const dvar_vector& v2)"
    << endl;
    ad_exit(1);
  }
  double tmp=0;

  #ifndef USE_ASSEMBLER
    int mmin=v1.indexmin();
    int mmax=v1.indexmax();
  #ifdef OPT_LIB
    double * pt1=&v1.elem_value(mmin);
    double * pt1m=&v1.elem_value(mmax);
    double * pt2=&v2.elem_value(mmin);
    do
    {
      tmp+= *pt1++ * *pt2++;
    }
    while (pt1<=pt1m);
  #else
    for (int i=mmin;i<=mmax;i++)
    {
      tmp+=v1.elem_value(i)*v2.elem_value(i);
    }
  #endif
  #else
    int mmin=v1.indexmin();
    int n=v1.indexmax()-mmin+1;
    dp_dotproduct(&tmp,&(v1.elem_value(mmin)),&(v2.elem_value(mmin)),n);
  #endif

  dvariable vtmp=nograd_assign(tmp);

  // The derivative list considerations
  save_identifier_string("bbbb");
  v1.save_dvar_vector_value();
  v1.save_dvar_vector_position();
  v2.save_dvar_vector_value();
  v2.save_dvar_vector_position();
  vtmp.save_prevariable_position();
  save_identifier_string("aaaa");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(dvdv_dot);
  RETURN_ARRAYS_DECREMENT();
  return vtmp;
}

/*
 * Description not yet available.
 * \param
 */
void dvdv_dot(void)
{
  verify_identifier_string("aaaa");
  double dftmp=restore_prevariable_derivative();
  dvar_vector_position v2pos=restore_dvar_vector_position();
  dvector cv2=restore_dvar_vector_value(v2pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
  dvector cv1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("bbbb");
  dvector dfv1(cv1.indexmin(),cv1.indexmax());
  dvector dfv2(cv2.indexmin(),cv2.indexmax());
#ifdef OPT_LIB
  double * pdf1=&dfv1(cv1.indexmin());
  double * pdf1m=&dfv1(cv1.indexmax());
  double * pdf2=&dfv2(cv1.indexmin());
  double * pc1=&cv1(cv1.indexmin());
  double * pc2=&cv2(cv1.indexmin());
  do
  {
    *pdf1++ = dftmp * *pc2++;
    *pdf2++ = dftmp * *pc1++;
  }
  while (pdf1<=pdf1m);
#else
  for (int i=cv1.indexmin();i<=cv1.indexmax();i++)
  {
    //tmp+=cv1(i)*cv2(i);
    dfv1(i)=dftmp*cv2.elem(i);
    dfv2(i)=dftmp*cv1.elem(i);
  }
#endif
  dfv1.save_dvector_derivatives(v1pos);
  dfv2.save_dvector_derivatives(v2pos);
}

void X_dv_sum(void);

/** Compute the sum of a variable type vector.
  \ingroup matop
  \param v1 A dvar_vector, \f$a\f$.
  \return A dvariable, \f$s = \sum a \f$  containing the sum of the vector.
*/
dvariable sum(const dvar_vector& v1)
{
  if (allocated(v1))
  {
    dvector cv1=value(v1);
    double tmp=0;
    for (int i=cv1.indexmin();i<=cv1.indexmax();i++)
    {
      tmp+=cv1.elem(i);
    }

    dvariable vtmp=nograd_assign(tmp);

    // The derivative list considerations
    save_identifier_string("bbbb");
    v1.save_dvar_vector_position();
    vtmp.save_prevariable_position();
    save_identifier_string("aaaa");
    gradient_structure::GRAD_STACK1->
              set_gradient_stack(X_dv_sum);
    return vtmp;
  }
  else
  {
    dvariable vtmp=0.0;
    return vtmp;
  }
}

/*
 * Description not yet available.
 *
 */
void X_dv_sum(void)
{
  verify_identifier_string("aaaa");
  double dftmp=restore_prevariable_derivative();
  dvar_vector_position v1pos=restore_dvar_vector_position();
  verify_identifier_string("bbbb");
  dvector dfv1(v1pos.indexmin(),v1pos.indexmax());
  for (int i=dfv1.indexmin();i<=dfv1.indexmax();i++)
  {
    //tmp+=cv1(i)*cv2(i);
    dfv1(i)=dftmp;
  }
  dfv1.save_dvector_derivatives(v1pos);
}

/** Compute the sum of a variable type matrix.
  \ingroup matop
  \param v1 A dvar_matrix, \f$A\f$.
  \return A dvariable, \f$s = \sum A \f$  containing the sum of the matrix.
*/

dvariable sum(const dvar_matrix& m)
{
  RETURN_ARRAYS_INCREMENT();
  dvariable tmp=0.;
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp+=sum(m.elem(i));
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}
