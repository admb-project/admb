/*
 * $Id: model51.cpp 945 2011-01-12 23:03:57Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>

void init_adstring::allocate(const char * s)
{
  check_datafile_pointer(ad_comm::global_datafile);
  model_name_tag::allocate(s);
  *(ad_comm::global_datafile) >> *this;
}

void init_line_adstring::allocate(const char * s)
{
  check_datafile_pointer(ad_comm::global_datafile);
  model_name_tag::allocate(s);
  *(ad_comm::global_datafile) >> (const init_line_adstring&)(*this);
}
