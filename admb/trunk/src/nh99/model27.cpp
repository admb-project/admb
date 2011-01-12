/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>

void named_dvar6_array::allocate(
    const ad_integer& hhsl,const ad_integer& hhsu,
    const index_type& hsl,const index_type& hsu,
    const index_type& sl,const index_type& sh,
    const index_type& nrl,const index_type& nrh,
    const index_type& ncl,const index_type& nch,
    const index_type& ncl6,const index_type& nch6,const char * _s)
{
  dvar6_array::allocate(hhsl,hhsu,hsl,hsu,sl,sh,nrl,nrh,ncl,nch,
    ncl6,nch6);
  model_name_tag::allocate(_s);
}

void named_dvar6_array::allocate(int l5,int h5,
  int hhsl,int hhsu,
  int hsl,int hsu,
  int rmin,int rmax,
  int cmin,int cmax,
  int cmin6,int cmax6,
  const char * _s)
{
  dvar6_array::allocate(l5,h5,hhsl,hhsu,hsl,hsu,rmin,rmax,cmin,cmax,
    cmin6,cmax6);
  model_name_tag::allocate(_s);
}

void named_d6_array::allocate(
    const ad_integer& hhsl,const ad_integer& hhsu,
    const index_type& hsl,const index_type& hsu,
    const index_type& sl,const index_type& sh,
    const index_type& nrl,const index_type& nrh,
    const index_type& ncl,const index_type& nch,
    const index_type& ncl6,const index_type& nch6,const char * _s)
{
  d6_array::allocate(hhsl,hhsu,hsl,hsu,sl,sh,nrl,nrh,ncl,nch,
    ncl6,nch6);
  model_name_tag::allocate(_s);
}


void named_d6_array::allocate(int l5,int h5,int hhsl,int hhsu,int hsl,
  int hsu,int rmin,int rmax,int cmin,int cmax,int l6,int u6,
  const char * s)
{
  d6_array::allocate(l5,h5,hhsl,hhsu,hsl,hsu,rmin,rmax,cmin,cmax,l6,u6);
  model_name_tag::allocate(s);
}

named_d6_array& named_d6_array::operator = (_CONST d6_array& m)
{
  this->d6_array::operator=(m);
  return *this;
}

named_dvar6_array& named_dvar6_array::operator = (_CONST dvar6_array& m)
{
  this->dvar6_array::operator=(m);
  return *this;
}

named_dvar6_array& named_dvar6_array::operator = (_CONST d6_array& m)
{
  this->dvar6_array::operator=(m);
  return *this;
}
