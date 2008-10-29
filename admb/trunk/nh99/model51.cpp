
#include <admodel.h>


// char cc[43]={"Copyright (c) 1993,2001 Otter Research Ltd"};


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


