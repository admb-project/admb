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

/**
 * Description not yet available.
 * \param
 */
  void dvar_vector::initialize(void)
  {
    if (!(!(*this)))  // only initialize allocated objects
    {
      for (int i=indexmin();i<=indexmax();i++)
      {
        //this->elem(i)=0.0;
        va[i].x=0.0;
      }
      save_identifier_string("b");
      this->save_dvar_vector_position();
      save_identifier_string("a");
      gradient_structure::GRAD_STACK1->
        set_gradient_stack(dv_init);
    }
  }


/**
 * Description not yet available.
 * \param
 */
void dv_init(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("a");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  verify_identifier_string("b");
  dvector dftmp(tmp_pos.indexmin(),tmp_pos.indexmax());
  for (int i=dftmp.indexmin();i<=dftmp.indexmax();i++)
  {
    //vtmp.elem(i)=value(v1.elem(i))+value(v2.elem(i));
    dftmp.elem(i)=0.0;
  }
  dftmp.save_dvector_derivatives_na(tmp_pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}


/**
 * Description not yet available.
 * \param
 */
void dvar_vector::initialize(const dvector& ww)
  {
      if (indexmin() != ww.indexmin() ||  indexmax() != ww.indexmax())
      {
        cerr << "Index bounds do not match in "
              "void dvar_vector::initialize(const dvector& ww)"<<endl;
        ad_exit(1);
      }

    for (int i=indexmin();i<=indexmax();i++)
    {
      //this->elem(i)=0.0;
      va[i].x=ww.elem(i);
    }
    save_identifier_string("b");
    this->save_dvar_vector_position();
    save_identifier_string("a");
    gradient_structure::GRAD_STACK1->
      set_gradient_stack(dv_init);
  }
