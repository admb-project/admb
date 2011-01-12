/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>

void named_i3_array::allocate(int hsl,int hsu,int rmin,int rmax,
  int cmin,int cmax,const char * s)
{
  i3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_i3_array::allocate(int hsl,int hsu,_CONST index_type& rmin,
  _CONST index_type& rmax,_CONST index_type& cmin,_CONST index_type& cmax,
  const char * s)
{
  i3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}


named_i3_array& named_i3_array::operator = (_CONST i3_array& m)
{
  i3_array::operator=(m);
  return *this;
}

void data_3iarray::allocate(int hsl,int hsu,int rmin,int rmax,
  int cmin,int cmax,const char * s)
{
  check_datafile_pointer(ad_comm::global_datafile);
  named_i3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax,s);
  *(ad_comm::global_datafile) >> i3_array(*this);
}

void data_3iarray::allocate(int hsl,int hsu,_CONST index_type& rmin,
  _CONST index_type& rmax,_CONST  index_type& cmin,
   _CONST index_type& cmax,const char * s)
{
  check_datafile_pointer(ad_comm::global_datafile);
  named_i3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax,s);
  *(ad_comm::global_datafile) >> i3_array(*this);
}
