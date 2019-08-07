/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#include <admodel.h>

void data_7array::allocate(
  int l7, int u7,
  int l6, int u6,
  int l5, int u5,
  int hhsl, int hhsu,
  int hsl, int hsu,
  int rmin, int rmax,
  int cmin, int cmax,
  const char* s)
{
  named_d7_array::allocate(l7, u7, l6, u6, l5, u5, hhsl, hhsu, hsl, hsu,
    rmin, rmax, cmin, cmax, s);
  *(ad_comm::global_datafile) >> d7_array(*this);
}
void data_6array::allocate(
  int l6, int u6,
  int l5, int u5,
  int hhsl, int hhsu,
  int hsl, int hsu,
  int rmin, int rmax,
  int cmin,int cmax,
  const char * s)
{
  named_d6_array::allocate(l6, u6, l5, u5, hhsl, hhsu, hsl, hsu, rmin, rmax, cmin, cmax, s);
  *(ad_comm::global_datafile) >> d6_array(*this);
}
void data_5array::allocate(
  int hhhsl, int hhhsu,
  int hhsl, int hhsu,
  int hsl, int hsu,
  int rmin, int rmax,
  int cmin, int cmax,
  const char * s)
{
  named_d5_array::allocate(hhhsl,hhhsu,hhsl,hhsu,hsl,hsu,rmin, rmax,cmin,cmax,s);
  *(ad_comm::global_datafile) >> d5_array(*this);
}
void data_5array::allocate(
  ad_integer hhhsl, ad_integer hhhsu,
  const index_type& hhsl, const index_type& hhsu,
  const index_type& hsl, const index_type& hsu,
  const index_type& rmin, const index_type& rmax,
  const index_type& cmin, const index_type& cmax,
  const char* s)
{
  named_d5_array::allocate(hhhsl,hhhsu,hhsl,hhsu,hsl,hsu,rmin,rmax, cmin,cmax,s);
  *(ad_comm::global_datafile) >> d5_array(*this);
}
