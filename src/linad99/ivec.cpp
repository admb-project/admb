/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>

/**
Shift current dimensions of ivector using to_indexmin
as the new lower index value.

ie [1 to 5] shift to_indexmin 2 will change to [2 to 5]

Note: Size and data are unchanged.

\param to_indexmin lower index changed to
*/
ivector& ivector::shift(int to_indexmin)
{
  v += indexmin() - to_indexmin;

  shape->shift(to_indexmin);
  index_max = shape->index_max;
  index_min = shape->index_min;

  return *this;
}
/**
Shift current dimensions of lvector using to_indexmin
as the new lower index value.

ie [1 to 5] shift to_indexmin 2 will change to [2 to 5]

Note: Size and data are unchanged.

\param to_indexmin lower index changed to
*/
lvector& lvector::shift(int to_indexmin)
{
  v += indexmin() - to_indexmin;

  shape->shift(to_indexmin);

  return *this;
}
