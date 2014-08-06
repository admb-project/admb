/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#include <admodel.h>

void data_4array::allocate(int hhsl,int hhsu,int hsl,int hsu,
    int rmin,int rmax,int cmin,int cmax,const char * s)
{
  named_d4_array::allocate(hhsl,hhsu,hsl,hsu,rmin,rmax,cmin,cmax,s);
  *(ad_comm::global_datafile) >> d4_array(*this);
}

void data_4array::allocate(ad_integer hhsl,ad_integer hhsu,
  const index_type& hsl, const index_type& hsu,
  const index_type& rmin, const index_type& rmax,
  const index_type& cmin, const index_type& cmax, const char *s)
{
  named_d4_array::allocate(hhsl,hhsu,hsl,hsu,rmin,rmax,cmin,cmax,s);
  *(ad_comm::global_datafile) >> d4_array(*this);
}

void data_4iarray::allocate(int hhsl,int hhsu,int hsl,int hsu,
    int rmin,int rmax,int cmin,int cmax,const char * s)
{
  named_i4_array::allocate(hhsl,hhsu,hsl,hsu,rmin,rmax,cmin,cmax,s);
  *(ad_comm::global_datafile) >> i4_array(*this);
}

void data_4iarray::allocate(ad_integer hhsl,ad_integer hhsu,
  const index_type& hsl, const index_type& hsu,
  const index_type& rmin, const index_type& rmax,
  const index_type& cmin, const index_type& cmax, const char *s)
{
  named_i4_array::allocate(hhsl,hhsu,hsl,hsu,rmin,rmax,cmin,cmax,s);
  *(ad_comm::global_datafile) >> i4_array(*this);
}
