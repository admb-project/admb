/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Function for adstring atoi.
*/

#include <sstream>
using std::istringstream;

#include <fvar.hpp>

/**
Returns a integer converted from input s.

@param s input adstring
@return converted integer
*/
int atoi(adstring& s)
{
  istringstream is((char*)s);
  int i = 0;
  is >> i;
  return i;
}
