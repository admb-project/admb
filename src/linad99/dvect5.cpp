/*
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Initialze all elements of dvector to zero.
*/
void dvector::initialize()
{
  if (allocated())  // only initialize allocated objects
  {
    memset(&elem(indexmin()), 0, size() * sizeof(double));
/*
    for (int i=indexmin();i<=indexmax();i++)
    {
      elem(i)=0.0;
    }
*/
  }
}
/*
Ir   I1mr ILmr         Dr D1mr DLmr         Dw    D1mw    DLmw

Improved
7,747,070 18,376  179 1,367,130    0    0 1,822,840    0    0      memset(&elem(indexmin()), 0, size() * sizeof(double));

Iterating
116,625,194      0    0 38,571,258    0    0 13,768,506       0       0      for (int i=indexmin();i<=indexmax();i++)
          .      .    .          .    .    .          .       .       .      {
 86,809,632 18,376  179 24,802,752    0    0 24,802,752 678,899 574,142        elem(i)=0.0;
          .      .    .          .    .    .          .       .       .      }
*/
