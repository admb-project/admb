/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <string.h>

/**
 * Description not yet available.
 * \param
 */
void nograd_assign_row(_CONST dvar_matrix& m,_CONST dvector& v,BOR_CONST int& ii)
{
  // cout << "Entering nograd assign"<<endl;
  //kkludge_object kg;
  if (ii<m.rowmin()||ii>m.rowmax()  ||
   (v.indexmin()!=m(ii).indexmin()) ||
   (v.indexmax()!=m(ii).indexmax()) )
  {
    cerr << "Error -- Index out of bounds in\n"
      "void nograd_assign(_CONST dvar_matrix& m,_CONST dvector& v,BOR_CONST int& ii)"
      << endl;
    ad_exit(1);
  }
  int min=v.indexmin();
  int max=v.indexmax();
  for (int j=min;j<=max;j++)
  {
    value(m(ii,j))=v(j);
  }
    // out(i)=nograd_assign(m(i));
  }

/**
 * Description not yet available.
 * \param
 */
  dvariable nograd_assign(double tmp)
{
  kkludge_object kg;
  dvariable tmpout(kg);
  value(tmpout)=tmp;
  return tmpout;
}
