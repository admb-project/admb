/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */



#include <admodel.h>



  void data_4array::allocate(int hhsl,int hhsu,int hsl,int hsu,
    int rmin,int rmax,int cmin,int cmax,const char * s)
  {
    named_d4_array::allocate(hhsl,hhsu,hsl,hsu,rmin,rmax,cmin,cmax,s);
    *(ad_comm::global_datafile) >> d4_array(*this);
  }

  void data_4array::allocate(ad_integer hhsl,ad_integer hhsu,_CONST index_type& hsl,_CONST index_type& hsu,_CONST index_type& rmin,_CONST index_type& rmax,
    _CONST index_type& cmin,_CONST index_type& cmax,const char * s)
  {
    named_d4_array::allocate(hhsl,hhsu,hsl,hsu,rmin,rmax,cmin,cmax,s);
    *(ad_comm::global_datafile) >> d4_array(*this);
  }

