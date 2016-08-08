/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

/**
Allocate init_adstring with id name, then assign input string from
opened ad_comm::global_datafile.
*/
void init_adstring::allocate(const char* name)
{
  check_datafile_pointer(ad_comm::global_datafile);
  model_name_tag::allocate(name);
  *(ad_comm::global_datafile) >> *this;
}
/**
Allocate init_line_adstring with id name, then assign input string from
opened ad_comm::global_datafile.
*/
void init_line_adstring::allocate(const char* name)
{
  check_datafile_pointer(ad_comm::global_datafile);
  model_name_tag::allocate(name);
  *(ad_comm::global_datafile) >> (const init_line_adstring&)(*this);
}
