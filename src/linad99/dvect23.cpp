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
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
ostream& operator<<(const ostream& _ofs, const pre_column_print& p)
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

/**
 * Description not yet available.
 * \param
 */
pre_column_print column_print(const dvector& v)
{
  return pre_column_print(v);
}

/**
 * Description not yet available.
 * \param
 */
ostream& operator << (const ostream& _ofs, const pre_zero_print& p)
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

/**
 * Description not yet available.
 * \param
 */
pre_zero_print zero_print(const dvector& v)
{
  return pre_zero_print(v);
}
