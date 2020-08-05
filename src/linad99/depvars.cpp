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
// file fvar.cpp
// constructors, destructors and misc functions involving class prevariable
#include "fvar.hpp"

#ifndef _MSC_VER
  #include <unistd.h>
#endif

/**
 * Description not yet available.
 * \param
 */
prevariable& operator<<(const prevariable& _v1, const prevariable& v2)
  {
    ADUNCONST(prevariable,v1)
    v1=v2;
    gradient_structure::save_dependent_variable_position(v1);
    return (prevariable&)v1;
  }

/**
 * Description not yet available.
 * \param
 */
dvar_vector& operator<<(const dvar_vector& v1, const dvar_vector& v2)
  {
    RETURN_ARRAYS_INCREMENT();

    int mmin=v1.indexmin();
    int mmax=v1.indexmax();
    if (mmin != v2.indexmin() || mmax != v2.indexmax())
    {
      cerr << " Incompatible bounds in dvar_vector& operator"
        " << (const dvar_vector& v1, const dvar_vector& v2)" << endl;
      ad_exit(21);
    }

    for (int i=mmin;i<=mmax;i++)
    {
      v1(i) << v2(i);
    }
    RETURN_ARRAYS_DECREMENT();
    return (dvar_vector&) v1;
  }

/**
 * Description not yet available.
 * \param
 */
dvar_matrix& operator<<(const dvar_matrix& v1, const dvar_matrix& v2)
  {
    int mmin=v1.rowmin();
    int mmax=v1.rowmax();
    RETURN_ARRAYS_INCREMENT();
    if (mmin != v2.rowmin() || mmax != v2.rowmax())
    {
      cerr << " Incompatible bounds in dvar_matrix& operator"
        " << (const dvar_matrix& v1, const dvar_matrix& v2)" << endl;
      ad_exit(21);
    }
    for (int i=mmin;i<=mmax;i++)
    {
      v1(i) << v2(i);
    }
    RETURN_ARRAYS_DECREMENT();
    return (dvar_matrix&)v1;
  }

/**
 * Description not yet available.
 * \param
 */
  dependent_variables_information::dependent_variables_information(int ndv) :
    grad_buffer_position(1,ndv),
    cmpdif_buffer_position(1,ndv),
    grad_file_position(1,ndv),
    cmpdif_file_position(1,ndv),
    grad_file_count(1,ndv),
    cmpdif_file_count(1,ndv)
  {
     max_num_dependent_variables=ndv;
     depvar_count=0;
     grad_buffer_position.initialize();
     cmpdif_buffer_position.initialize();
     grad_file_count.initialize();
     cmpdif_file_count.initialize();
     grad_file_position.initialize();
     cmpdif_file_position.initialize();
  }

/**
 * Description not yet available.
 * \param
 */
void gradient_structure::save_dependent_variable_position(const prevariable& v1)
    {
      int depvar_count=++DEPVARS_INFO->depvar_count;
      //max_num_dependent_variables=ndv;
      if (depvar_count>DEPVARS_INFO->max_num_dependent_variables)
      {
        cout << "maximum number of depdendent variables of "
           << DEPVARS_INFO->max_num_dependent_variables << " exceeded "
           << endl
           << "use gradient_structure::set_NUM_DEPENDENT_VARIABLES(int i);"
           << endl << "to increase the number of dependent variables"
           << endl;
        ad_exit(1);
      }
      DEPVARS_INFO->grad_buffer_position(depvar_count)=GRAD_STACK1->ptr;
      DEPVARS_INFO->cmpdif_buffer_position(depvar_count)=fp->offset;
      DEPVARS_INFO->grad_file_count(depvar_count)=
                                GRAD_STACK1->_GRADFILE_PTR;
      DEPVARS_INFO->cmpdif_file_count(depvar_count)=fp->file_ptr;
      DEPVARS_INFO->grad_file_position(depvar_count)
        =LSEEK(GRAD_STACK1->_GRADFILE_PTR,0,SEEK_CUR);
      DEPVARS_INFO->cmpdif_file_position(depvar_count)
        =LSEEK(fp->file_ptr,0,SEEK_CUR);
    }
