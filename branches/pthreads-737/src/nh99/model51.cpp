/*
 * $Id: model51.cpp 542 2012-07-10 21:04:06Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California 
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
