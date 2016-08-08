/**
\file
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/
#include "fvar.hpp"

/**
Default constructor
*/
dvar3_array::dvar3_array()
{
  allocate();
}
/**
Does not allocte, but initialize class members.
*/
void dvar3_array::allocate()
{
  shape = NULL;
  t = NULL;
}
