/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Member function for class adstring_array operator=(const adstring_array&).
*/

#include "adstring.hpp"

/**
Assigment operator for adstring_array.

@param a adstring_array to copy
@return adstring_array
*/
adstring_array& adstring_array::operator=(const adstring_array& a)
{
  if (this != &a)
  {
    const int min = a.indexmin();
    const int max = a.indexmax();
    allocate(min, max);
    for (int i = min; i <= max; i++)
    {
      (*this)[i] = a[i];
    }
  }
  return *this;
}
