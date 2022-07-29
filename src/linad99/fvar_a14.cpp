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

#ifdef DEBUG
  #include <cassert>
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
  gradient_structure* gs = gradient_structure::get();
  gs->RETURN_ARRAYS_INCREMENT();

  int min=v1.indexmin();
  int max=v1.indexmax();
#ifdef OPT_LIB
  if (min != v2.indexmin() || max != v2.indexmax())
  {
    cerr << "Incompatible bounds in prevariable operator*(const dvar_vector&, const dvar_vector&)\n";
    ad_exit(1);
  }
#endif

  double tmp{0};
  double_and_int* pva1 = v1.va + min;
  double_and_int* pva2 = v2.va + min;
  for (int i = min; i <= max; ++i)
  {
    tmp += pva1->x * pva2->x;
    ++pva1;
    ++pva2;
  }

  dvariable vtmp=nograd_assign(tmp);

  grad_stack* GRAD_STACK1 = gradient_structure::get_GRAD_STACK1();
  DF_FILE* fp = gradient_structure::get_fp();
  // The derivative list considerations
  //save_identifier_string("bbbb");
  fp->save_dvar_vector_value(v1);
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_value(v2);
  fp->save_dvar_vector_position(v2);
  fp->save_prevariable_position(vtmp);
  //save_identifier_string("aaaa");
  GRAD_STACK1->set_gradient_stack(dvdv_dot);
  gs->RETURN_ARRAYS_DECREMENT();
  return vtmp;
}

/*
 * Description not yet available.
 * \param
 */
void dvdv_dot(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  //verify_identifier_string("aaaa");
  double dftmp=fp->restore_prevariable_derivative();
  dvar_vector_position v2pos=fp->restore_dvar_vector_position();
  dvector cv2=restore_dvar_vector_value(v2pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  dvector cv1=restore_dvar_vector_value(v1pos);
  //verify_identifier_string("bbbb");

  int min = cv1.indexmin();
  int max = cv1.indexmax();

#ifdef DEBUG
  assert(min == cv2.indexmin() && max == cv2.indexmax());
#endif

  dvector dfv1(min, max);
  dvector dfv2(min, max);

  double* pcv1 = cv1.get_v() + min;
  double* pcv2 = cv2.get_v() + min;
  double* pdfv1 = dfv1.get_v() + min;
  double* pdfv2 = dfv2.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    //tmp+=cv1(i)*cv2(i);
    *pdfv1 = dftmp * *pcv2;
    *pdfv2 = dftmp * *pcv1;
    ++pdfv1;
    ++pdfv2;
    ++pcv2;
    ++pcv1;
  }
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
  dvariable vtmp = 0.0;
  if (allocated(v1))
  {
    int min = v1.indexmin();
    int max = v1.indexmax();
    //dvector cv1=value(v1);
    double_and_int* pv1 = v1.va + min;
    double tmp=0;
    for (int i = min; i <= max; ++i)
    {
      //tmp+=cv1.elem(i);
      tmp += pv1->x;
      ++pv1;
    }

    vtmp = nograd_assign(tmp);

    gradient_structure* gs = gradient_structure::get_GRAD_STACK1();
    DF_FILE* fp = gradient_structure::get_fp();
    // The derivative list considerations
    save_identifier_string("bbbb");
    fp->save_dvar_vector_position(v1);
    fp->save_prevariable_position(vtmp);
    save_identifier_string("aaaa");
    GRAD_STACK1->set_gradient_stack(X_dv_sum);
  }
  return vtmp;
}

/*
 * Description not yet available.
 *
 */
void X_dv_sum(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  verify_identifier_string("aaaa");
  double dftmp=fp->restore_prevariable_derivative();
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  verify_identifier_string("bbbb");
  int min = v1pos.indexmin();
  int max = v1pos.indexmax();
  dvector dfv1(min, max);
  double* pdfv1 = dfv1.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    //tmp+=cv1(i)*cv2(i);
    //dfv1(i)=dftmp;
    *pdfv1 = dftmp;
    ++pdfv1;
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
  gradient_structure* gs = gradient_structure::get();
  gs->RETURN_ARRAYS_INCREMENT();

  int min = m.rowmin();
  int max = m.rowmax();
  dvariable tmp{0.0};
  if (min <= max)
  {
    const dvar_vector* pmi = &m(min);
    for (int i = min; i <= max; ++i)
    {
      tmp += sum(*pmi);
      ++pmi;
    }
  }
  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}
