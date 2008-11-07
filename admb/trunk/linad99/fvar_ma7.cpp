/**
  * $Id:   $
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */

#define HOME_VERSION
#include "fvar.hpp"

/*
void dvar_matrix::initialize(void)
{
  if (!(!(*this)))  // only initialize allocated objects
  {
    for (int i=rowmin();i<=rowmax();i++)
    {
      elem(i).initialize();
    }
  }
} 
*/


void dfmatinit(void)
{
  verify_identifier_string("q");
  dvar_matrix_position tmp_pos=restore_dvar_matrix_position();
  verify_identifier_string("p");
  dmatrix tmp(tmp_pos);
  tmp.initialize();
  tmp.save_dmatrix_derivatives_na(tmp_pos);
}



void dvar_matrix::initialize(void)
{
  if (!(!(*this)))  // only initialize allocated objects
  {
    if (indexmin()>indexmax())
       cout << "error" << endl;
    int imin=indexmin();
    int imax=indexmax();
    for (int i=imin;i<=imax;i++)
    {
      if (allocated(elem(i)))
      {
        dvar_vector& tmp=elem(i);
        int jmin=tmp.indexmin();
        int jmax=tmp.indexmax();
        double * pd=&(tmp.elem_value(jmin));
        for (int j=jmin;j<=jmax;j++)
        {
          *pd++=0.0;
        }
      }
    }
    save_identifier_string("p");
    save_dvar_matrix_position();
    gradient_structure::GRAD_STACK1->
      set_gradient_stack(dfmatinit);
    save_identifier_string("q");
  }
} 

#undef HOME_VERSION
