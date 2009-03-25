/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include <admodel.h>


void named_dvar7_array::allocate(
    const ad_integer& hhsl,const ad_integer& hhsu,
    const index_type& hsl,const index_type& hsu,
    const index_type& sl,const index_type& sh,
    const index_type& nrl,const index_type& nrh,
    const index_type& ncl,const index_type& nch,
    const index_type& ncl6,const index_type& nch6,
    const index_type& ncl7,const index_type& nch7,
    const char * _s)
{
  dvar7_array::allocate(hhsl,hhsu,hsl,hsu,sl,sh,nrl,nrh,ncl,nch,
    ncl6,nch6,ncl7,nch7);
  model_name_tag::allocate(_s);
}

void named_dvar7_array::allocate(
  int l5,int h5,
  int hhsl,int hhsu,
  int hsl,int hsu,
  int rmin,int rmax,
  int cmin,int cmax,
  int cmin6,int cmax6,
  int cmin7,int cmax7,
  const char * _s)
{
  dvar7_array::allocate(l5,h5,hhsl,hhsu,hsl,hsu,rmin,rmax,cmin,cmax,
    cmin6,cmax6,cmin7,cmax7);
  model_name_tag::allocate(_s);
}

void named_d7_array::allocate(
    const ad_integer& hhsl,const ad_integer& hhsu,
    const index_type& hsl,const index_type& hsu,
    const index_type& sl,const index_type& sh,
    const index_type& nrl,const index_type& nrh,
    const index_type& ncl,const index_type& nch,
    const index_type& ncl6,const index_type& nch6,
    const index_type& ncl7,const index_type& nch7,
    const char * _s)
{
  d7_array::allocate(hhsl,hhsu,hsl,hsu,sl,sh,nrl,nrh,ncl,nch,
    ncl6,nch6,ncl7,nch7);
  model_name_tag::allocate(_s);
}


void named_d7_array::allocate(
  int l5,int h5,
  int hhsl,int hhsu,
  int hsl,int hsu,
  int rmin,int rmax,
  int cmin,int cmax,
  int l6,int u6,
  int l7,int u7,
  const char * s)
{
  d7_array::allocate(
    l5,h5,
    hhsl,hhsu,
    hsl,hsu,
    rmin,rmax,
    cmin,cmax,
    l6,u6,
    l7,u7);
  model_name_tag::allocate(s);
}

named_d7_array& named_d7_array::operator = (_CONST d7_array& m)
{
  this->d7_array::operator=(m);
  return *this;
}

named_dvar7_array& named_dvar7_array::operator = (_CONST dvar7_array& m)
{
  this->dvar7_array::operator=(m);
  return *this;
}

named_dvar7_array& named_dvar7_array::operator = (_CONST d7_array& m)
{
  this->dvar7_array::operator=(m);
  return *this;
}

