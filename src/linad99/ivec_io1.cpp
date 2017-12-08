/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
  #include <iomanip.h>
  #include <fstream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
  #include <iomanip.hpp>
  #include <fstream.hpp>
#endif

#ifndef OPT_LIB
  #include <cassert>
#endif

/**
Read from input to values.

\param input uistream
\param values ivector
*/
uistream& operator>>(const uistream& input, const ivector& values)
{
  const_cast<ivector&>(values).read_from(input);
  return const_cast<uistream&>(input);
}
/**
Read values from input into ivector.

\param input uistream
*/
void ivector::read_from(const uistream& input)
{
#ifndef OPT_LIB
  assert(indexmax() >= indexmin());
#endif

  char* p = (char*)(v + indexmin());
  int n = indexmax() - indexmin() + 1;
  n *= (int)sizeof(int);

  const_cast<uistream&>(input).read(p, n);
}
/**
Write values to output.

\param output uostream
\param values ivector
*/
uostream& operator<<(const uostream& output, const ivector& values)
{
  const_cast<ivector&>(values).write_on(output);
  return const_cast<uostream&>(output);
}
/**
Write ivector values to output.

\param output uostream
*/
void ivector::write_on(const uostream& output) const
{
#ifndef OPT_LIB
  assert(indexmax() >= indexmin());
#endif

  char* p = (char*)(v + indexmin());
  int n = indexmax() - indexmin() + 1;
  n *= (int)sizeof(int);

  const_cast<uostream&>(output).write(p, n);
}
