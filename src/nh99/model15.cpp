/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include <admodel.h>


void named_dvar4_array::allocate(
  ad_integer hhsl,ad_integer hhsu,
  const index_type& hsl,const index_type& hsu,
  const index_type& rmin,const index_type& rmax,
  const index_type& cmin,const index_type& cmax,const char *s)
{
  dvar4_array::allocate(hhsl,hhsu,hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_dvar4_array::allocate(
  ad_integer hhsl,ad_integer hhsu,
  const index_type& hsl,const index_type& hsu,
  const index_type& rmin,const index_type& rmax,
  const char *s)
{
  dvar4_array::allocate(hhsl,hhsu,hsl,hsu,rmin,rmax);
  model_name_tag::allocate(s);
}

void named_dvar4_array::allocate(
  ad_integer hhsl,ad_integer hhsu,
  const index_type& hsl,const index_type& hsu,
  const char *s)
{
  dvar4_array::allocate(hhsl,hhsu,hsl,hsu);
  model_name_tag::allocate(s);
}

void named_dvar4_array::allocate(
  ad_integer hhsl,ad_integer hhsu,const char *s)
{
  dvar4_array::allocate(hhsl,hhsu);
  model_name_tag::allocate(s);
}

void named_dvar4_array::allocate(const char *s)
{
  dvar4_array::allocate();
  model_name_tag::allocate(s);
}


void named_dvar4_array::allocate(int hhsl,int hhsu,int hsl,int hsu,
  int rmin,int rmax, int cmin,int cmax,const char * s)
{
  dvar4_array::allocate(hhsl,hhsu,hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_dvar4_array::allocate(int hhsl,int hhsu,int hsl,int hsu,
  int rmin,int rmax,const char * s)
{
  dvar4_array::allocate(hhsl,hhsu,hsl,hsu,rmin,rmax);
  model_name_tag::allocate(s);
}

void named_dvar4_array::allocate(int hhsl,int hhsu,int hsl,int hsu,
  const char * s)
{
  dvar4_array::allocate(hhsl,hhsu,hsl,hsu);
  model_name_tag::allocate(s);
}

void named_dvar4_array::allocate(int hhsl,int hhsu,const char * s)
{
  dvar4_array::allocate(hhsl,hhsu);
  model_name_tag::allocate(s);
}

void named_d4_array::allocate(int hhsl,int hhsu,int hsl,int hsu,
  int rmin,int rmax,int cmin,int cmax,const char * s)
{
  d4_array::allocate(hhsl,hhsu,hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_d4_array::allocate(int hhsl,int hhsu,int hsl,int hsu,
  int rmin,int rmax,const char * s)
{
  d4_array::allocate(hhsl,hhsu,hsl,hsu,rmin,rmax);
  model_name_tag::allocate(s);
}

void named_d4_array::allocate(int hhsl,int hhsu,int hsl,int hsu,
  const char * s)
{
  d4_array::allocate(hhsl,hhsu,hsl,hsu);
  model_name_tag::allocate(s);
}

void named_d4_array::allocate(int hhsl,int hhsu,const char * s)
{
  d4_array::allocate(hhsl,hhsu);
  model_name_tag::allocate(s);
}

void named_d4_array::allocate(const char * s)
{
  d4_array::allocate();
  model_name_tag::allocate(s);
}

void named_d4_array::allocate(ad_integer hhsl,ad_integer hhsu,_CONST index_type& hsl,_CONST index_type& hsu,
  _CONST index_type& rmin,_CONST index_type& rmax,_CONST index_type& cmin,_CONST index_type& cmax,const char * s)
{
  d4_array::allocate(hhsl,hhsu,hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_d4_array::allocate(ad_integer hhsl,ad_integer hhsu,_CONST index_type& hsl,_CONST index_type& hsu,const char * s)
{
  d4_array::allocate(hhsl,hhsu,hsl,hsu);
  model_name_tag::allocate(s);
}

void named_d4_array::allocate(ad_integer hhsl,ad_integer hhsu,const char * s)
{
  d4_array::allocate(hhsl,hhsu);
  model_name_tag::allocate(s);
}


void named_d4_array::allocate(ad_integer hhsl,ad_integer hhsu,_CONST index_type& hsl,_CONST index_type& hsu,
  _CONST index_type& rmin,_CONST index_type& rmax,const char * s)
{
  d4_array::allocate(hhsl,hhsu,hsl,hsu,rmin,rmax);
  model_name_tag::allocate(s);
}

named_d4_array& named_d4_array::operator = (_CONST d4_array& m)
{
  this->d4_array::operator=(m);
  return *this;
}

named_dvar4_array& named_dvar4_array::operator = (_CONST dvar4_array& m)
{
  this->dvar4_array::operator=(m);
  return *this;
}

named_dvar4_array& named_dvar4_array::operator = (_CONST d4_array& m)
{
  this->dvar4_array::operator=(m);
  return *this;
}

