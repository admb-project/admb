/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
#endif

#if !defined(OPT_LIB)

/**
Return reference to integer element at imatrix(i, j).
Checked for valid bounds.

\param i row index
\param j column index
*/
int& imatrix::operator()(int i, int j)
{
  if (i < rowmin())
  {
    cerr << "matrix bound exceeded -- row index too low in "
         << "imatrix::operator()(int, int)\n"
         << "value was \"" << i << "\".\n";
    ad_exit(1);
  }
  if (i > rowmax())
  {
    cerr << "matrix bound exceeded -- row index too high in "
         << "imatrix::operator()(int, int)\n"
         << "value was \"" << i << "\".\n";
    ad_exit(1);
  }
  if (j < elem(i).indexmin())
  {
    cerr << "matrix bound exceeded -- column index too low in "
         << "imatrix::operator()(int, int)\n"
         << "value was \"" << j << "\".\n";
    ad_exit(1);
  }
  if (j > elem(i).indexmax())
  {
    cerr << "matrix bound exceeded -- column index too high in "
         << "imatrix::operator()(int, int)\n"
         << "value was \"" << j << "\".\n";
    ad_exit(1);
  }
  return *((*(m+i)).v+j);
}
/**
Return const reference to integer element at imatrix(i, j).
Checked for valid bounds.

\param i row index
\param j column index
*/
const int& imatrix::operator()(int i, int j) const
{
  if (i < rowmin())
  {
    cerr << "matrix bound exceeded -- row index too low in "
         << "imatrix::operator()(int, int)\n"
         << "value was \"" << i << "\".\n";
    ad_exit(1);
  }
  if (i > rowmax())
  {
    cerr << "matrix bound exceeded -- row index too high in "
         << "imatrix::operator()(int, int)\n"
         << "value was \"" << i << "\".\n";
    ad_exit(1);
  }
  if (j < elem(i).indexmin())
  {
    cerr << "matrix bound exceeded -- column index too low in "
         << "imatrix::operator()(int, int)\n"
         << "value was \"" << j << "\".\n";
    ad_exit(1);
  }
  if (j > elem(i).indexmax())
  {
    cerr << "matrix bound exceeded -- column index too high in "
         << "imatrix::operator()(int, int)\n"
         << "value was \"" << j << "\".\n";
    ad_exit(1);
  }
  return *((*(m+i)).v+j);
}
#endif
