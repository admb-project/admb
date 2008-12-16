/*
 * $Id$
 * Author: David Fournier
 * Copyright (c) 2008 Regents of the University of California 
 */

#include <fvar.hpp>

ostream& operator << (_CONST ostream& _ofs,_CONST pre_column_print& p)
{
  ostream& ofs= (ostream&) _ofs;
  int mmin=p.ptr->indexmin();
  int mmax=p.ptr->indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    ofs << double((*(p.ptr))[i]) << endl;
  }
  return ofs;
}

pre_column_print column_print(_CONST dvector& v)
{
  return pre_column_print(v); 
}

ostream& operator << (_CONST ostream& _ofs,_CONST pre_zero_print& p)
{
  ostream& ofs= (ostream&) _ofs;
  int mmin=p.ptr->indexmin();
  int mmax=p.ptr->indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    double tmp= double((*(p.ptr))[i]);
    if (tmp ==0)
      ofs << "0 ";
    else
      ofs << tmp << " ";
  }
  return ofs;
}

pre_zero_print zero_print(_CONST dvector& v)
{
  return pre_zero_print(v); 
}
