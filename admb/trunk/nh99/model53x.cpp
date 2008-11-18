/**
  * $Id$
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */



//#define HOME_VERSION
#include <admodel.h>


  void param_init_d3array::sd_vscale(const dvar_vector& _d,
    const dvar_vector& x,const int& _ii)
  {
    if (allocated(*this))
    {  
      int& ii=(int&) _ii;
      dvar_vector& d=(dvar_vector&) _d;
      int mmin=indexmin();
      int mmax=indexmax();
      for (int i=mmin;i<=mmax;i++)
      {
        if (allocated((*this)(i)))
        {
          int rmin=((*this)(i)).indexmin();
          int rmax=((*this)(i)).indexmax();
          for (int j=rmin;j<=rmax;j++)
          {
            if (allocated((*this)(i,j)))
            {
              int cmin=(*this)(i,j).indexmin();	
              int cmax=(*this)(i,j).indexmin();	
              for (int k=cmin;k<=cmax;k++)
              {
                d(ii)=0.0;
                ii++;
              }
            }
          }
	}  
      }
    }
  }


#undef HOME_VERSION
