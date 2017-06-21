/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Returns a selected vector of values from ivector using positions
in indexes.

Note: Assumes positions are in range [indexmin() to indexmax()]. 

\param indexes contains vector of valid index values
*/
ivector ivector::operator()(const ivector& indexes)
{
  ivector values(indexes.indexmin(), indexes.indexmax());
  for (int i = values.indexmin(); i <= values.indexmax(); ++i)
  {
     values(i) = operator()(indexes(i));
  }
  return values;
}
/**
Returns a selected vector of values from lvector using positions
in indexes.

Note: Assumes positions are in range [indexmin() to indexmax()]. 

\param indexes contains vector of valid index values
*/
lvector lvector::operator()(const ivector& indexes)
{
  lvector values(indexes.indexmin(),indexes.indexmax());
  for (int i = values.indexmin(); i <= values.indexmax(); ++i)
  {
    values(i) = operator()(indexes(i));
  }
  return values;
}
