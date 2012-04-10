/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */

#include <admodel.h>

  void data_5array::allocate(int hhhsl,int hhhsu,
    int hhsl,int hhsu,
    int hsl,int hsu,
    int rmin,int rmax,int cmin,int cmax,const char * s)
  {
    named_d5_array::allocate(hhhsl,hhhsu,hhsl,hhsu,hsl,hsu,rmin,
      rmax,cmin,cmax,s);
    *(ad_comm::global_datafile) >> d5_array(*this);
  }

  void data_5array::allocate(ad_integer hhhsl,ad_integer hhhsu,
    _CONST index_type&  hhsl,_CONST index_type& hhsu,
    _CONST index_type& hsl,_CONST index_type& hsu,_CONST index_type& rmin,_CONST index_type& rmax,
    _CONST index_type& cmin,_CONST index_type& cmax,const char * s)
  {
    named_d5_array::allocate(hhhsl,hhhsu,hhsl,hhsu,hsl,hsu,rmin,rmax,
      cmin,cmax,s);
    *(ad_comm::global_datafile) >> d5_array(*this);
  }
