/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

void named_i4_array::allocate(int hhsl,int hhsu,int hsl,int hsu,
  int rmin,int rmax,int cmin,int cmax,const char * s)
{
  i4_array::allocate(hhsl,hhsu,hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

/*
void named_i4_array::allocate(int hhsl,int hhsu,int hsl,int hsu,
  int rmin,int rmax,const char * s)
{
  i4_array::allocate(hhsl,hhsu,hsl,hsu,rmin,rmax);
  model_name_tag::allocate(s);
}

void named_i4_array::allocate(int hhsl,int hhsu,int hsl,int hsu, const char* s)
{
  i4_array::allocate(hhsl,hhsu,hsl,hsu);
  model_name_tag::allocate(s);
}
*/

void named_i4_array::allocate(int hhsl,int hhsu,const char* s)
{
  i4_array::allocate(hhsl,hhsu);
  model_name_tag::allocate(s);
}

void named_i4_array::allocate(const char* s)
{
  i4_array::allocate();
  model_name_tag::allocate(s);
}

void named_i4_array::allocate(ad_integer hhsl, ad_integer hhsu,
  const index_type& hsl, const index_type& hsu, const index_type& rmin,
  const index_type& rmax, const index_type& cmin, const index_type& cmax,
  const char *s)
{
  i4_array::allocate(hhsl,hhsu,hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

/*
void named_i4_array::allocate(ad_integer hhsl,ad_integer hhsu,
  const index_type& hsl, const index_type& hsu,const char* s)
{
  i4_array::allocate(hhsl,hhsu,hsl,hsu);
  model_name_tag::allocate(s);
}
*/

void named_i4_array::allocate(ad_integer hhsl,ad_integer hhsu,const char* s)
{
  i4_array::allocate(hhsl,hhsu);
  model_name_tag::allocate(s);
}

/*
void named_i4_array::allocate(ad_integer hhsl,ad_integer hhsu,
  const index_type& hsl, const index_type& hsu, const index_type& rmin,
  const index_type& rmax, const char *s)
{
  i4_array::allocate(hhsl,hhsu,hsl,hsu,rmin,rmax);
  model_name_tag::allocate(s);
}
*/

named_i4_array& named_i4_array::operator=(const i4_array& m)
{
  const int min = this->i4_array::indexmin();
  const int max = this->i4_array::indexmax();
  for (int i = min; i <= max; i++)
  {
    this->i4_array::operator()(i) = m(i);
  }
  return *this;
}
