/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include <admodel.h>


void named_dvar5_array::allocate(
    const ad_integer& hhsl,const ad_integer& hhsu,
    const index_type& hsl,const index_type& hsu,
    const index_type& sl,const index_type& sh,
    const index_type& nrl,const index_type& nrh,
    const index_type& ncl,const index_type& nch,const char * s)
{
  dvar5_array::allocate(hhsl,hhsu,hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
  model_name_tag::allocate(s);
}

void named_dvar5_array::allocate(
  int l5,int h5,
  int hhsl,int hhsu,
  int hsl,int hsu,
  int rmin,int rmax,
  int cmin,int cmax,
  const char * _s)
{
  dvar5_array::allocate(l5,h5,hhsl,hhsu,hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(_s);
}

void named_d5_array::allocate(const ad_integer& hhsl,const ad_integer& hhsu,
    const index_type& hsl,const index_type& hsu, const index_type& sl,
    const index_type& sh,const index_type& nrl,const index_type& nrh,
    const index_type& ncl,const index_type& nch,const char * _s)
{
  d5_array::allocate(hhsl,hhsu,hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
  model_name_tag::allocate(_s);
}

void named_d5_array::allocate(int l5,int h5,int hhsl,int hhsu,int hsl,
  int hsu,int rmin,int rmax,int cmin,int cmax,const char * _s)
{
  d5_array::allocate(l5,h5,hhsl,hhsu,hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(_s);
}

named_d5_array& named_d5_array::operator = (_CONST d5_array& m)
{
  this->d5_array::operator=(m);
  return *this;
}

named_dvar5_array& named_dvar5_array::operator = (_CONST dvar5_array& m)
{
  this->dvar5_array::operator=(m);
  return *this;
}

named_dvar5_array& named_dvar5_array::operator = (_CONST d5_array& m)
{
  this->dvar5_array::operator=(m);
  return *this;
}

