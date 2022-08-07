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

void DF_dvexp(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector mfexp(const dvar_vector& v1, const double d)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    if (v1.elem_value(i)<d)
    {
      vtmp.elem_value(i)=exp(v1.elem_value(i));
    }
    else
    {
      vtmp.elem_value(i)=exp(d);
      cout << "In mfexp d =" << d << " mfexp(x) = " << vtmp(i)  << endl;
    }
  }

  DF_FILE* fp = gradient_structure::fp;
  save_identifier_string("ddd");
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_value(vtmp);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("hee");
  gradient_structure::GRAD_STACK1->set_gradient_stack(DF_dvexp);
  return vtmp;
}
